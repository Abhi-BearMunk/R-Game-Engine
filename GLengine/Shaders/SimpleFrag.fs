#version 420 core

#include Includes/Transforms.inc
#include Includes/Utils.inc
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
    LightingInput LInput;

	// properties
    vec4 albedo = texture(Texture_Diffuse, texCoords * tiling);
    LInput.diffuse = vec3(albedo);
    LInput.specular = vec3(texture(Texture_Specular, texCoords * tiling));
    LInput.shininess = shininess;
    LInput.position = vertexPos.xyz;
    LInput.normal = normalize(normal.xyz);
    LInput.viewDir = normalize(viewPos.xyz - vertexPos.xyz);
    
    FragColor = vec4(CalculateLighting(LInput), albedo.w);
}
