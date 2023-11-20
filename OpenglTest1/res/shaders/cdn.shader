#shader vertex
#version 440 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(binding = 0) uniform sampler2D u_displacementMapX;
layout(binding = 1) uniform sampler2D u_displacementMapY;
layout(binding = 2) uniform sampler2D u_displacementMapZ;
layout(binding = 3) uniform sampler2D u_normal;

out vec2 textureCoord;
out vec3 verNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 displacementX = vec3(texture(u_displacementMapX, aTexCoord).r, 0.0, 0.0);
	vec3 displacementY = vec3(0.0, texture(u_displacementMapY, aTexCoord).r, 0.0);
	vec3 displacementZ = vec3(0.0, 0.0, texture(u_displacementMapZ, aTexCoord).r);

	vec3 normal = texture(u_normal, aTexCoord).rgb;

	gl_Position = projection * view * model * vec4(aPos + displacementX + displacementY + displacementZ, 1.0);
	textureCoord = aTexCoord;
	verNormal = normal;
	FragPos = (model * vec4(aPos + displacementX + displacementY + displacementZ, 1.0)).xyz;
}
