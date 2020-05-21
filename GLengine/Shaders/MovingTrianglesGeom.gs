#version 420 core
#include Includes/Transforms.inc
#include Includes/Utils.inc

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec4 vertexPos;
    vec4 normal;
    vec2 texCoords;
} gs_in[];

// Outputs
out vec4 vertexPos;
out vec4 normal;
out vec2 texCoords;

vec4 explode(vec4 position, vec3 c, vec3 n, float r) 
{ 
    float magnitude = 2;
    float v = ((sin(R_Time.y * 8 + r * 2 * 3.14) + 1.0) / 2.0) * magnitude;
    vec3 direction = n * v; 
    direction += (position.xyz - c) * v * 0.4;
    return position + vec4(direction, 0.0);
}

vec3 GetNormal() 
{ 
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    vec3 n = GetNormal();

    vec4 c = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
    
    n = normalize(gs_in[0].normal.xyz + gs_in[1].normal.xyz + gs_in[2].normal.xyz);

    vec4 pos = explode(gl_in[0].gl_Position, c.xyz, n, gs_in[0].texCoords.y);
    gl_Position = R_MATRIX_VP * pos;
    vertexPos = pos;
    normal = gs_in[0].normal;
    texCoords = gs_in[0].texCoords;
    EmitVertex();
    pos = explode(gl_in[1].gl_Position, c.xyz, n, gs_in[1].texCoords.y);
    gl_Position = R_MATRIX_VP * pos;
    vertexPos = pos;
    normal = gs_in[1].normal;
    texCoords = gs_in[1].texCoords;
    EmitVertex();
    pos = explode(gl_in[2].gl_Position, c.xyz, n, gs_in[2].texCoords.y);
    gl_Position = R_MATRIX_VP * pos;
    vertexPos = pos;
    normal = gs_in[2].normal; 
    texCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
}  