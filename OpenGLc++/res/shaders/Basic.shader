#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Pro;

void main()
{
    gl_Position = u_Pro*u_View *u_Model *position;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform float mixValue;
uniform vec4 u_Color; 
uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;
uniform vec3 lightColor;
void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = vec4(lightColor,1.0)*mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, vec2(1.0 - v_TexCoord.x, v_TexCoord.y)), mixValue);
};

