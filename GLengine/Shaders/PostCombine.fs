#version 420 core
out vec4 FragColor;
  
in vec2 texCoords;

uniform sampler2D Source_Texture;
uniform sampler2D Source_Texture2;

void main()
{ 
    FragColor = vec4(texture(Source_Texture, texCoords).xyz + texture(Source_Texture2, texCoords).xyz, 1);
}