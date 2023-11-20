#version 460 core

#define COMPUTE_WORK_GROUP_DIM 32

const float PI = 3.14159265359;
const float g = 9.81;

layout(local_size_x = 32, local_size_y = 32) in;
layout(binding = 0, rgba32f)  uniform image2D h0_k_h0_minusk;
layout(binding = 1, rgba32f)  uniform image2D noise;

uniform int N;//512
uniform int L;//1024
uniform float A;
uniform vec2 windDirection;
uniform float windspeed;

vec4 gaussRnd() {
    ivec2 texCoord = ivec2(gl_GlobalInvocationID.xy);

    vec4 rnd = imageLoad(noise, texCoord);
    return rnd;
}

float getPhillip(vec2 k)
{
    float len = length(k);

    if (len < 0.00001)
        return 0.00001;

    float len2 = len * len;
    float len4 = len2 * len2;

    float kDotw = dot(normalize(k), normalize(windDirection));

    float kDotw6 = kDotw * kDotw * kDotw * kDotw * kDotw * kDotw;

    float L_ = windspeed * windspeed / g;

    float L2 = L_ * L_;

    float damping = 0.001;

    float l2 = L2 * damping * damping;
    return A * exp(-1.0 / (len2 * L2)) / len4 * kDotw6 * exp(-len2 * l2);
}

vec2 conj(vec2 a)
{
    return vec2(a.x, -a.y);
}
void main()
{
    vec2 x = vec2(gl_GlobalInvocationID.xy) - float(N) / 2;
    vec2 k = vec2(2 * PI * x.x / L, 2 * PI * x.y / L);
    vec4 rnd = gaussRnd();
  
    float p1 = getPhillip(k);
    float p2 = getPhillip(-k);
    imageStore(h0_k_h0_minusk, ivec2(gl_GlobalInvocationID.xy),
         vec4(rnd.xy * sqrt(p1 / 2.0), conj( rnd.zw * sqrt(p2 / 2.0))));
}