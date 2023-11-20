#version 460 core

#define COMPUTE_WORK_GROUP_DIM 32

const float PI = 3.14159265359;
const float g = 9.81;

layout(local_size_x = 32, local_size_y = 32) in;
layout(binding = 0, rgba32f)  uniform image2D h0_k_h0_minusk;
layout(binding = 1, rgba32f)  uniform image2D noise;

uniform int N;
uniform int L;
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

    float L = windspeed * windspeed / g;

    float L2 = L * L;

    float damping = 0.001;

    float l2 = L2 * damping * damping;

    //if (kDotw < 0.0)
    //{
    //    return amplitude * exp(-1.0 / (len2 * L2)) / len4 * kDotw6 * exp(-len2 * l2) * 0.07;
    //}
    return A * exp(-1.0 / (len2 * L2)) / len4 * kDotw6 * exp(-len2 * l2);
}
void main()
{
    vec2 x = vec2(gl_GlobalInvocationID.xy) - float(N) / 2;
    vec2 k = vec2(2 * PI * x.x / L, 2 * PI * x.y / L);
    /*
    float L_ = (windspeed * windspeed) / g;
    float mag = length(k);
    if (mag < 0.00001) mag = 0.00001;
    float magSq = mag * mag;

    float h0k = clamp(sqrt((A / (magSq * magSq))
        * pow(dot(normalize(k), normalize(windDirection)), 6.0)
        * exp(-(1.0 / (magSq * L_ * L_)))
        * exp(-magSq * pow(L / 2000.0, 2.0))) / sqrt(2.0), -4000, 4000);

    float h0_minusk = clamp(sqrt((A / (magSq * magSq))
        * pow(dot(normalize(-k), normalize(windDirection)), 6.0)
        * exp(-(1.0 / (magSq * L_ * L_)))
        * exp(-magSq * pow(L / 2000.0, 2.0))) / sqrt(2.0), -4000, 4000);
    vec4 rnd = gaussRnd();
    */
    float p1 = getPhillip(k);
    imageStore(h0_k_h0_minusk, ivec2(gl_GlobalInvocationID.xy),
        vec4(rnd.xy * p1, 0, 1));
    //  vec4(rnd.xy* h0k, rnd.zw* h0_minusk));   
}