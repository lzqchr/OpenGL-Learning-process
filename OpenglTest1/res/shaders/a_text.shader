#shader vertex
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
uniform float m;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(-0.75+aPos.x*0.25+m*0.51,0.75+ aPos.y*0.25, 0.0, 1.0);
}


#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D heightMap;

void main()
{
    vec3 col = texture(heightMap, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}