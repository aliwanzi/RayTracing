// Flat Color Shader

#type vertex
#version 420 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out VS_OUT{
    vec2 texCoord;
} vs_out;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vs_out.texCoord = aTexCoord;
}

#type fragment
#version 420 core
out vec4 FragColor;

in VS_OUT{
    vec2 texCoord;
} fs_in;

uniform sampler2D sparseTex;
uniform int Level;

void main()
{
    FragColor = textureLod(sparseTex, fs_in.texCoord, Level);
}