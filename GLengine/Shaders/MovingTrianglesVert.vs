#version 420 core

#include Includes/Transforms.inc

// Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Outputs
out VS_OUT
{
    vec4 vertexPos;
    vec4 normal;
    vec2 texCoords;
}vs_out;

void main()
{   
    vs_out.texCoords = aTexCoords;
    vs_out.vertexPos = R_MATRIX_M * vec4(aPos, 1.0);
    vs_out.normal = normalize(R_MATRIX_NORMAL * vec4(aNormal, 0));
    gl_Position = vs_out.vertexPos;
}