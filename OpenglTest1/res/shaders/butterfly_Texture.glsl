#version 460 core

#define COMPUTE_WORK_GROUP_DIM 32

const float PI = 3.14159265359;


layout(local_size_x = 1, local_size_y = 32) in;
layout(binding = 0, rgba32f)  uniform image2D butterfly;

//反序后的索引
layout(binding = 1, std430) buffer indices {
	int j[512];
}bit_reversed;

struct complex {
	float real;
	float im;
};

uniform int N;

void main() {
	vec2 x = gl_GlobalInvocationID.xy;
	float k = mod(x.y * (float(N) / pow(2, x.x + 1)),N);

	//旋转因子
	complex twiddle = complex(cos(2.0 * PI * k / float(N)), sin(2.0 * PI * k / float(N)));
	
	int stage = int(pow(2, x.x));

	int top_bot;
	  
	if (mod(x.y, pow(2, x.x + 1)) < pow(2, x.x))
		top_bot = 1;
	else top_bot = 0;
	
	
	//初始输入
	if (x.x == 0) {
		if (top_bot == 1) {
			imageStore(butterfly, ivec2(x),
				vec4(twiddle.real, twiddle.im,
					bit_reversed.j[int(x.y)],
					bit_reversed.j[int(x.y + 1)]));
		}
		else {
			imageStore(butterfly, ivec2(x),
				vec4(twiddle.real, twiddle.im,
					bit_reversed.j[int(x.y - 1)],
					bit_reversed.j[int(x.y)]));
		}
	}
	else {
		if (top_bot == 1) {
			imageStore(butterfly, ivec2(x),
				vec4(twiddle.real, twiddle.im,
					x.y, x.y + stage));
		}
		else {
			imageStore(butterfly, ivec2(x),
				vec4(twiddle.real, twiddle.im,
					x.y - stage, x.y));
		}
	}
}