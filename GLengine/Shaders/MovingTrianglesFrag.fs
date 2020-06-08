#version 420 core

#include Includes/Transforms.inc
#include Includes/Utils.inc
#include Includes/Lighting.inc

// Uniforms
uniform sampler2D Texture_Diffuse;
uniform sampler2D Texture_Specular;
uniform samplerCube Texture_Reflection;
uniform float shininess;
uniform vec2 tiling;

// LInputs
in vec2 texCoords;
in vec4 vertexPos;
in vec4 normal;

// Output
out vec4 FragColor;

void main()
{    
    // Reflection
    vec3 I = normalize(vertexPos.xyz - viewPos.xyz);
    vec3 N = normalize(normal.xyz);
    vec3 R = reflect(I, N);

    // Light
    LightingInput LInput;
    vec4 albedo = texture(Texture_Diffuse, texCoords * tiling);
    LInput.diffuse = vec3(albedo);
    LInput.diffuse = vec3(0.3f);
    LInput.specular = vec3(texture(Texture_Specular, texCoords * tiling));
    LInput.shininess = shininess;
    LInput.position = vertexPos.xyz;
    LInput.normal = N;
    LInput.viewDir = -I;

    vec3 light = CalculateLighting(LInput);
    
    FragColor = vec4(light * texture(Texture_Reflection, R).rgb, albedo.w);
}
