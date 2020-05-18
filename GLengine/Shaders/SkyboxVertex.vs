#version 420 core

#include Includes/Transforms.inc
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;
uniform mat4 R_MAT;

void main()
{
    TexCoords = aPos;
    vec4 pos = R_MAT * vec4(aPos, 1.0);
    pos.z = pos.w * 0.9999;
    gl_Position = pos;
}  