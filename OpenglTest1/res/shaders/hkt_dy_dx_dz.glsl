#version 460 core

#define COMPUTE_WORK_GROUP_DIM 32

layout(local_size_x = 32, local_size_y = 32) in;
layout(binding = 0, rgba32f)  uniform image2D hkt;
layout(binding = 1, rgba32f)  uniform image2D dy;
layout(binding = 2, rgba32f)  uniform image2D dx;
layout(binding = 3, rgba32f)  uniform image2D dz;

uniform int N;
uniform int L;
uniform float t;
const float PI = 3.14159265359;

////
float w_0 = PI / 100.0;


struct complex {
	float real;
	float im;
};

complex mul(complex c0, complex c1) {
	complex c;
	c.real = c0.real * c1.real - c0.im * c1.im;
	c.im   = c0.real * c1.im + c0.im * c1.real;
	return c;
}
complex add(complex c0, complex c1) {
	complex c;
	c.real = c0.real + c1.real;
	c.im = c0.im + c1.im;
	return c;
}

complex conj(complex c) {
	complex conj = complex(c.real,-c.im);
	
	return conj;
}

void main() {
	vec2 x = vec2(gl_GlobalInvocationID.xy) - float(N) / 2;
	 vec2 k = vec2(2 * PI * x.x / L, 2 * PI * x.y / L);
	//vec2 k = vec2(PI * (2.0 * x.x - N) / L, PI * (2.0 * x.y - N) / L);

	float l_k = length(k);
	if (l_k < 0.00001) l_k = 0.00001;

//	float w = sqrt(9.81 * l_k);

	float w = floor(sqrt(9.81 * l_k)/ w_0)* w_0;

	vec2 h0k = imageLoad(hkt, ivec2(gl_GlobalInvocationID.xy)).rg;
	complex fourier_cmp = complex(h0k.x, h0k.y);

	vec2 h0k_minus = imageLoad(hkt, ivec2(gl_GlobalInvocationID.xy)).ba;
	complex fourier_cmp_conj = complex(h0k_minus.x, h0k_minus.y);
	
	//euler formula
	float cos_wt = cos(w * t);
	float sin_wt = sin(w * t);

	complex exp_iwt = complex(cos_wt, sin_wt);
	complex exp_iwt_minus = complex(cos_wt, -sin_wt);


	complex hkt_dy = add(mul(fourier_cmp, exp_iwt), mul(fourier_cmp_conj, exp_iwt_minus));

	complex hkt_dx = mul(complex(0, -k.x / l_k), hkt_dy);

	complex hkt_dz = mul(complex(0, -k.y / l_k), hkt_dy);

	imageStore(dy, ivec2(gl_GlobalInvocationID.xy),vec4(hkt_dy.real,hkt_dy.im, 0, 1));

	imageStore(dx, ivec2(gl_GlobalInvocationID.xy), vec4(hkt_dx.real, hkt_dx.im, 0, 1));

	imageStore(dz, ivec2(gl_GlobalInvocationID.xy), vec4(hkt_dz.real, hkt_dz.im, 0, 1));
}