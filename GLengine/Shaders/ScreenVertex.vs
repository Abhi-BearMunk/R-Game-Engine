#version 420 core

// Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Outputs
out vec2 texCoords;

void main()
{   
    texCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}