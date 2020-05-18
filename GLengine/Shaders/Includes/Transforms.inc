// Uniforms
layout (std140, binding = 0) uniform Camera
{
    vec4 viewPos;
    vec4 lookDir;
    mat4 R_MATRIX_P;
    mat4 R_MATRIX_V;
    mat4 R_MATRIX_VP;
    mat4 R_MATRIX_VP_INV;
    float near;
    float far;
};

uniform mat4 R_MATRIX_M;
uniform mat4 R_MATRIX_MVP;
uniform mat4 R_MATRIX_MVP_INV;
uniform mat4 R_MATRIX_NORMAL;