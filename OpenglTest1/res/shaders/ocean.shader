#shader vertex
#version 440 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(binding = 0) uniform sampler2D u_displacementMap;

layout(binding = 1) uniform sampler2D u_normal;

//out vec2 textureCoord;
out vec4 verNormal;
out vec3 FragPos;

out vec3 vdir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eyePos;

void main()
{
	vec3 displacementX = vec3(texture(u_displacementMap, aTexCoord).x, 0.0, 0.0);
	vec3 displacementY = vec3(0.0, texture(u_displacementMap, aTexCoord).y, 0.0);
	vec3 displacementZ = vec3(0.0, 0.0, texture(u_displacementMap, aTexCoord).z);

	vec4 normal = texture(u_normal, aTexCoord).rgba;

	gl_Position = projection * view * model * vec4(aPos + displacementX + displacementY + displacementZ, 1.0);


	//textureCoord = aTexCoord;
	verNormal = normal;
	FragPos = (model * vec4(aPos + displacementX + displacementY + displacementZ, 1.0)).xyz;

	vdir = eyePos - FragPos.xyz;

}
#shader fragment
#version 440 core

#define ONE_OVER_4PI	0.0795774715459476

//in vec2 textureCoord;
in vec4 verNormal;
in vec3 FragPos;
in vec3 vdir;


uniform samplerCube envmap;

out vec4 FragColor;

void main()
{
	const vec3 sundir = vec3(0.603, 0.240, -0.761);
	const vec3 sunColor = vec3(1.0, 1.0, 0.47);
	const vec3 oceanColor = vec3(0.0000, 0.2307, 0.3613);


	float dist = length(vdir.xz);
	float factor = (1024 - dist) / (1024 - 50);

	factor = clamp(factor * factor * factor, 0.0, 1.0);



	vec3 n = normalize(verNormal.xyz);
	vec3 v = normalize(vdir);
	vec3 l = reflect(-v, n);



	float F0 = 0.020018673;
	float F = F0 + (1.0 - F0) * pow(1.0 - dot(n, l), 5.0);

	vec3 refl = texture(envmap, l).rgb;


	float turbulence = max(1.6 - verNormal.w, 0.0);
	float color_mod = 1.0 + 3.0 * smoothstep(1.2, 1.8, turbulence);

	color_mod = mix(1.0, color_mod, factor);

	const float rho = 0.3;
	const float ax = 0.2;
	const float ay = 0.1;

	vec3 h = sundir + v;
	vec3 x = cross(sundir, n);
	vec3 y = cross(x, n);

	float mult = (ONE_OVER_4PI * rho / (ax * ay * sqrt(max(1e-5, dot(sundir, n) * dot(v, n)))));
	float hdotx = dot(h, x) / ax;
	float hdoty = dot(h, y) / ay;
	float hdotn = dot(h, n);

	float spec = mult * exp(-((hdotx * hdotx) + (hdoty * hdoty)) / (hdotn * hdotn));
//	FragColor = vec4(mix(oceanColor, refl * color_mod, F) + sunColor * spec, 1.0);
	FragColor = vec4(mix(oceanColor, refl * color_mod, F) + sunColor * spec, 1.0);
}