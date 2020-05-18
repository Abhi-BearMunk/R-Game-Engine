#version 420 core

#include Includes/Transforms.inc

// Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Outputs
out vec4 vertexPos;
out vec4 normal;
out vec2 texCoords;

void main()
{   
    texCoords = aTexCoords;
    vertexPos = R_MATRIX_M * vec4(aPos, 1.0);
    normal = normalize(R_MATRIX_NORMAL * vec4(aNormal, 0));
    gl_Position = R_MATRIX_MVP * vec4(aPos, 1.0);
}