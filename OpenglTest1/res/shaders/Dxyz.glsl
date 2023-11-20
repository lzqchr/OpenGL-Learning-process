#version 460 core

#define COMPUTE_WORK_GROUP_DIM 32

layout(local_size_x = 32, local_size_y = 32) in;

layout(binding = 0, rgba32f)  uniform image2D DX;
layout(binding = 1, rgba32f)  uniform image2D DY;
layout(binding = 2, rgba32f)  uniform image2D DZ;
layout(binding = 3, rgba32f)  uniform image2D Dxyz;

uniform int pingpong;
uniform int N;

void main(void) {
	ivec2 x = ivec2(gl_GlobalInvocationID.xy);
	float X = imageLoad(DX, x).x;
	float Y = imageLoad(DY, x).y;
	float Z = imageLoad(DZ, x).x;

	imageStore(Dxyz, x, vec4(X,Y, Z, 1));
}