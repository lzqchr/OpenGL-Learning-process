#version 430

#define PI		3.1415926535897932
#define TWO_PI	6.2831853071795864

#define DISP_MAP_SIZE 512
#define LOG2_DISP_MAP_SIZE 9

layout(rg32f, binding = 0) uniform readonly image2D readbuff;
layout(rg32f, binding = 1) uniform writeonly image2D writebuff;

vec2 ComplexMul(vec2 z, vec2 w) {
	return vec2(z.x * w.x - z.y * w.y, z.y * w.x + z.x * w.y);
}

shared vec2 pingpong[2][DISP_MAP_SIZE];

layout(local_size_x = DISP_MAP_SIZE) in;
void main()
{
	const float N = float(DISP_MAP_SIZE);

	int z = int(gl_WorkGroupID.x);
	int x = int(gl_LocalInvocationID.x);

	// STEP 1: load row/column and reorder
	int nj = (bitfieldReverse(x) >> (32 - LOG2_DISP_MAP_SIZE)) & (DISP_MAP_SIZE - 1);
	pingpong[0][nj] = imageLoad(readbuff, ivec2(z, x)).rg;

	barrier();

	// STEP 2: perform butterfly passes
	int src = 0;

	for (int s = 1; s <= LOG2_DISP_MAP_SIZE; ++s) {
		int m = 1 << s;				// butterfly group height
		int mh = m >> 1;			// butterfly group half height

		int k = (x * (DISP_MAP_SIZE / m)) & (DISP_MAP_SIZE - 1);
		int i = (x & ~(m - 1));		// butterfly group starting offset
		int j = (x & (mh - 1));		// butterfly index in group

		// twiddle factor W_N^k
		float theta = (TWO_PI * float(k)) / N;
		vec2 W_N_k = vec2(cos(theta), sin(theta));

		vec2 input1 = pingpong[src][i + j + mh];
		vec2 input2 = pingpong[src][i + j];

		src = 1 - src;
		pingpong[src][x] = input2 + ComplexMul(W_N_k, input1);

		barrier();
	}

	// STEP 3: write output
	vec2 result = pingpong[src][x];
	imageStore(writebuff, ivec2(x, z), vec4(result, 0.0, 1.0));

	// NOTE: do sign correction later
}