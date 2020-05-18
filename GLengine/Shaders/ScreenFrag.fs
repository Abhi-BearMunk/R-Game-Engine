#version 420 core
out vec4 FragColor;
  
in vec2 texCoords;

uniform sampler2D Source_Texture;

void main()
{ 
    vec3 col = texture(Source_Texture, texCoords).xyz;
    float g = (col.x + col.y + col.z) * 0.33333;
    FragColor = vec4(texture(Source_Texture, texCoords).xyz, 1);
}