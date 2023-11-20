#version 460 core
#define M_PI 3.1415926535897932384626433832795
#define gravity 9.81


#define COMPUTE_WORK_GROUP_DIM 32

layout(local_size_x = 32, local_size_y = 32) in;
layout(binding = 0, rgba32f)  uniform image2D hkt;
layout(binding = 1, rgba32f)  uniform image2D dy;
layout(binding = 2, rgba32f)  uniform image2D dx;
layout(binding = 3, rgba32f)  uniform image2D dz;

uniform int N;
uniform int L;
uniform float t;

float Dispersion(vec2 k)
{
    float w_0 = M_PI / 100.0;
    return floor(sqrt(gravity * length(k)) / w_0) * w_0;
}

vec2 ComplexMul(vec2 a, vec2 b)
{
    return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}


void main()
{
    vec2 x = vec2(gl_GlobalInvocationID.xy) - float(N) / 2;

    vec2 htilde0 = imageLoad(hkt, ivec2(gl_GlobalInvocationID.xy)).rg;
    vec2 htilde0mkconj = imageLoad(hkt, ivec2(gl_GlobalInvocationID.xy)).ba;

    vec2 k = vec2(M_PI * (2.0 * float(gl_GlobalInvocationID.x) - N) / L, M_PI * (2.0 * float(gl_GlobalInvocationID.y) - N) / L);

    float omegat = Dispersion(k) * t;

    float cos_ = cos(omegat);
    float sin_ = sin(omegat);

    vec2 c0 = vec2(cos_, sin_);
    vec2 c1 = vec2(cos_, -sin_);

    vec2 result = ComplexMul(htilde0, c0) + ComplexMul(htilde0mkconj, c1);

    //displacementY[DTid] = result;
    imageStore(dy, ivec2(gl_GlobalInvocationID.xy), vec4(result, 0, 1));

    float len = length(k);

    if (len < 0.0000001)
    {

        result = ComplexMul(result, vec2(0.0, 0.0));
        imageStore(dx, ivec2(gl_GlobalInvocationID.xy), vec4(result, 0, 1));
        imageStore(dz, ivec2(gl_GlobalInvocationID.xy), vec4(result, 0, 1));
       // displacementX[DTid] = ComplexMul(result, vec2(0.0, 0.0));
       // displacementZ[DTid] = ComplexMul(result, vec2(0.0, 0.0));
    }
    else
    {
        imageStore(dx, ivec2(gl_GlobalInvocationID.xy), vec4(ComplexMul(result, vec2(0.0, -k.x / len)), 0, 1));
        imageStore(dz, ivec2(gl_GlobalInvocationID.xy), vec4(ComplexMul(result, vec2(0.0, -k.y / len)), 0, 1));

      //  displacementX[DTid] = ComplexMul(result, vec2(0.0, -k.x / len));
       // displacementZ[DTid] = ComplexMul(result, vec2(0.0, -k.y / len));
    }
}