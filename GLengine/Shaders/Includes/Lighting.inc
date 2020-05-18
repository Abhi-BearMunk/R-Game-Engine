#define MAX_DIR_LIGHTS 100
#define MAX_POINT_LIGHTS 100

struct LightingInput
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
    vec3 position; 
    vec3 normal;
    vec3 viewDir;
};

struct DirLight {
    vec4 direction;	
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight {
    vec4 position;	

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;	
	
    float constant;
    float linear;
    float quadratic;
	float padding;
};


layout (std140, binding = 1) uniform DirLights
{
    DirLight dirlights[MAX_DIR_LIGHTS];
	uint numDirLights;
};

layout (std140, binding = 2) uniform PointLights
{
    PointLight pointLights[MAX_POINT_LIGHTS];
	uint numPointLights;
};

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, LightingInput input)
{
    vec3 lightDir = normalize(-light.direction.xyz);
    // diffuse shading
    float diff = max(dot(input.normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, input.normal);
    float spec = pow(max(dot(input.viewDir, reflectDir), 0.0), input.shininess);
    // combine results
    vec3 ambient_out = light.ambient.xyz * vec3(input.diffuse);
    vec3 diffuse_out = light.diffuse.xyz * diff * vec3(input.diffuse);
    vec3 specular_out = light.specular.xyz * spec * vec3(input.specular);
    return ambient_out + diffuse_out + specular_out;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, LightingInput input)
{
    vec3 lightDir = normalize(light.position.xyz - input.position);
    // diffuse shading
    float diff = max(dot(input.normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, input.normal);
    float spec = pow(max(dot(input.viewDir, reflectDir), 0.0), input.shininess);
    // attenuation
    float distance = length(light.position.xyz - input.position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   
    // combine results
    vec3 ambient_out = light.ambient.xyz * vec3(input.diffuse);
    vec3 diffuse_out = light.diffuse.xyz * diff * vec3(input.diffuse);
    vec3 specular_out = light.specular.xyz * spec * vec3(input.specular);

    ambient_out *= attenuation;
    diffuse_out *= attenuation ;
    specular_out *= attenuation;

    return ambient_out + diffuse_out + specular_out;
}

vec3 CalculateLighting(LightingInput input)
{
	vec3 result = vec3(0,0,0);

    // phase 1: directional lighting
	for(int i = 0; i < numDirLights; i++)
	{
	    result += CalcDirLight(dirlights[i], input);
	}
    
    // phase 2: point lights
    for(int i = 0; i < numPointLights; i++)
	{
        result += CalcPointLight(pointLights[i], input);    
	}

    return result;
}
