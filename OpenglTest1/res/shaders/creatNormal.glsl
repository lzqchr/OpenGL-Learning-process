
#version 460 core

#define N 512

layout(local_size_x = 32, local_size_y = 32) in;
layout(rgba32f, binding = 0) uniform readonly image2D dxyz;

layout(rgba16f, binding = 1) uniform writeonly image2D Normal;

void main()
{
	ivec2 loc = ivec2(gl_GlobalInvocationID.xy);

	float uintLength =1024/512;

	// 取点
	ivec2 left = (loc - ivec2(1, 0)) & (N - 1);
	ivec2 right = (loc + ivec2(1, 0)) & (N - 1);
	ivec2 bottom = (loc - ivec2(0, 1)) & (N - 1);
	ivec2 top = (loc + ivec2(0, 1)) & (N - 1);


	vec3 center = vec3( imageLoad(dxyz, loc).xyz);
	vec3 disp_left    = vec3(imageLoad(dxyz, left).xyz);
	vec3 disp_right   = vec3(imageLoad(dxyz, right).xyz);
	vec3 disp_bottom  = vec3(imageLoad(dxyz, bottom).xyz);
	vec3 disp_top     = vec3(imageLoad(dxyz, top).xyz);
	
	vec3 x1 = vec3(disp_left.x - uintLength, disp_left.yz) - center;
	vec3 x2 = vec3(disp_right.x + uintLength, disp_right.yz) - center;
	vec3 z1 = vec3(disp_bottom.xy , disp_bottom.z - uintLength) - center;
	vec3 z2 = vec3(disp_top.xy,     disp_top.z + uintLength) - center;
	//两个切线
	vec3 dx = x2 - x1;
	vec3 dz = z2 - z1 ;

	vec3 normal = normalize(cross(x2,z1)+ cross(z1, x1) + cross(x1, z2) + cross(z2, x2) );


	vec2 gradient = vec2(disp_left.y - disp_right.y, disp_bottom.y - disp_top.y);
	
	// Jacobian
	vec2 dDx = (disp_right.xz - disp_left.xz) * (512 / 1000);
	vec2 dDy = (disp_top.xz - disp_bottom.xz) * (512 / 1000);

	float J = (1.0 + dDx.x) * (1.0 + dDy.y) - dDx.y * dDy.x;

	// NOTE: normals are in tangent space for now
	imageStore(Normal, loc, vec4(normalize(vec3(gradient.x,1, gradient.y)), J));
	//imageStore(Normal, loc, vec4(normal, 1));
	//imageStore(Normal, loc, vec4(normalize(vec3 ( - center.x, 1, -center.z)), 1));
}