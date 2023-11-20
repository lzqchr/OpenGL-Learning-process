#version 460 core
//��ʼ��Ƶ��
#define COMPUTE_WORK_GROUP_DIM 32
const float PI = 3.14159265359;

layout(local_size_x = 32,local_size_y = 32, local_size_z = 1) in;


layout(binding = 0, rgba32f)  uniform image2D u_gass;

uint rngState;
int u_resolution = 512;

//�������

uint wangHash(uint seed)
{
    seed = (seed^61)^(seed >> 16);
    seed *= 9;
    seed = seed^(seed >> 4);
    seed *= 0x27d4eb2d;
    seed = seed^(seed >> 15);
    return seed;
}
//������ȷֲ������[0,1)
float rand()
{
    // Xorshift�㷨
    rngState ^= (rngState << 13);
    rngState ^= (rngState >> 17);
    rngState ^= (rngState << 5);
    return (float(rngState) / 4294967296.0f);
}

//�����˹�����
vec4 gaussian(float x,float y)
{
    
    //���ȷֲ������
    rngState = wangHash(uint(y * 6.77 + x));
    
    float x1 = rand();
    float x2 = rand();

    float x3 = rand();
    float x4 = rand();

    x1 = max(1e-6f, x1);
    x2 = max(1e-6f, x2);
    x3 = max(1e-6f, x3);
    x4 = max(1e-6f, x4);
    //���������໥�����ĸ�˹�����
    float g1 = sqrt(-2.0f * log(x1)) * cos(2.0f * PI * x2);
    float g2 = sqrt(-2.0f * log(x1)) * sin(2.0f * PI * x2);
    float g3 = sqrt(-2.0f * log(x3)) * cos(2.0f * PI * x4);
    float g4 = sqrt(-2.0f * log(x3)) * sin(2.0f * PI * x4);

    return vec4(g1, g2, g3, g4);
}

void main() {

    ivec2 pixel_coord = ivec2(gl_GlobalInvocationID.xy);

    vec4 value = vec4(0.0, 0.0, 0.0, 1.0);
    value.x = float(pixel_coord.x)/(gl_NumWorkGroups.x);
    value.y = float(pixel_coord.y)/(gl_NumWorkGroups.y);
    imageStore(u_gass, pixel_coord, gaussian(pixel_coord.x, pixel_coord.y));
    //imageStore(u_gass, pixel_coord, value);
}