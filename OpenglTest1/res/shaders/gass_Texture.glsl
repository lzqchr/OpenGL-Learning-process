#version 460 core
//³õÊ¼»¯ÆµÆ×
#define COMPUTE_WORK_GROUP_DIM 32
const float PI = 3.14159265359;

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;


layout(binding = 0, rgba32f)  uniform image2D u_gass;

layout(binding = 1, std430) buffer indices {
	vec4 j[512][512];
}gass;

void main() {

	vec2 x = gl_GlobalInvocationID.xy;
	imageStore(u_gass, ivec2(x),
		vec4(j[x.x][x.y]));
}