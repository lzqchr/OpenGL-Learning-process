#shader vertex
#version 410 core


layout(location = 0) in vec3 aPos;

layout(location = 1) in vec2 aTex;

out vec2 TexCoord;

void main()
{
   
    gl_Position = vec4(aPos, 1.0);
 
    TexCoord = aTex;
}

#shader fragment
#version 410 core

in float Height;

out vec4 FragColor;

void main()
{
    float h = (Height + 16) / 64.0f;
    FragColor = vec4(h, h, h, 1.0);
}


#shader tessContral

#version 410 core


layout(vertices = 4) out;

// varying input from vertex shader
in vec2 TexCoord[];
// varying output to evaluation shader
out vec2 TextureCoord[];

void main()
{
  
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    TextureCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

  
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = 512;
        gl_TessLevelOuter[1] = 512;
        gl_TessLevelOuter[2] = 512;
        gl_TessLevelOuter[3] = 512;

        gl_TessLevelInner[0] = 512;
        gl_TessLevelInner[1] = 512;
    }
}


#shader tessEva
#version 410 core

layout(quads, fractional_odd_spacing, ccw) in;

uniform sampler2D dxyz; 
uniform mat4 model;           // the model matrix
uniform mat4 view;            // the view matrix
uniform mat4 projection;      // the projection matrix



in vec2 TextureCoord[];


out float Height;

void main()
{
    // get patch coordinate
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // ----------------------------------------------------------------------
    vec2 t00 = TextureCoord[0];
    vec2 t01 = TextureCoord[1];
    vec2 t10 = TextureCoord[2];
    vec2 t11 = TextureCoord[3];

    // bilinearly interpolate texture coordinate across patch
    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;

    // lookup texel at patch coordinate for height and scale + shift as desired
    Height = texture(dxyz, texCoord).y;
   
    vec3 disp = texture(dxyz, texCoord).xyz;
    // ----------------------------------------------------------------------
    // retrieve control point position coordinates
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    // compute patch surface normal
    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0));

    // bilinearly interpolate position coordinate across patch
    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0;

    // displace point along normal
    p +=  (disp,0);

    // ----------------------------------------------------------------------
    // output patch point position in clip space
    gl_Position = projection * view * model * p;
}