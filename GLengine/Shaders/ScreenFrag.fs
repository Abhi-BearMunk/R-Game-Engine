#version 420 core
out vec4 FragColor;
  
in vec2 texCoords;

uniform float gamma;
uniform sampler2D Source_Texture;

void main()
{ 
    float g = gamma;
    vec3 col = texture(Source_Texture, texCoords).xyz;
    FragColor = vec4(col, 1);
}