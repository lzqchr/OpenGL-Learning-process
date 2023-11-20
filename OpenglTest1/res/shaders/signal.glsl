
#version 430

layout(rg32f, binding = 0) uniform readonly image2D displacementX;
layout(rg32f, binding = 1) uniform readonly image2D displacementY;
layout(rg32f, binding = 2) uniform readonly image2D displacementZ;


layout(rgba32f, binding = 3) uniform writeonly image2D displacementXYZ;

layout(local_size_x = 32, local_size_y = 32) in;
void main()
{
	const float lambda = 1.3f;

	ivec2 loc = ivec2(gl_GlobalInvocationID.xy);

	// required due to interval change
	float sign = ((((loc.x + loc.y) & 1) == 1) ? -1.0 : 1.0);

	

	float v0 = imageLoad(displacementY, loc).x * sign;
	float v1 = -imageLoad(displacementX, loc).x * sign;
	float v2 = -imageLoad(displacementZ, loc).x * sign;


	imageStore(displacementXYZ, loc, vec4(v1, v0, v2, 1.0));
}