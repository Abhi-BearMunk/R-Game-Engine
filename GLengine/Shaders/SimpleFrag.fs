#version 420 core

#include Includes/Transforms.inc
#include Includes/Fragment.inc
#include Includes/Lighting.inc

// Uniforms
uniform sampler2D Texture_Diffuse;
uniform sampler2D Texture_Specular;
uniform float shininess;
uniform vec2 tiling;

// Inputs
in vec2 texCoords;
in vec4 vertexPos;
in vec4 normal;

// Output
out vec4 FragColor;

void main()
{    
    LightingInput input;

	// properties
    vec4 albedo = texture(Texture_Diffuse, texCoords * tiling);
    input.diffuse = vec3(albedo);
    input.specular = vec3(texture(Texture_Specular, texCoords * tiling));
    input.shininess = shininess;
    input.position = vertexPos.xyz;
    input.normal = normalize(normal.xyz);
    input.viewDir = normalize(viewPos.xyz - vertexPos.xyz);
    
    FragColor = vec4(CalculateLighting(input), albedo.w);
}
