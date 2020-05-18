#version 420 core

#include Includes/Transforms.inc

// Inputs
in vec2 texCoords;
in vec4 vertexPos;
in vec4 normal;

// Output
out vec4 FragColor;

// Uniforms
uniform vec4 outlineColor;

void main()
{      
    //gl_FragDepth = 0;
    FragColor = outlineColor;
}
