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

vec3 CalcDirLight(DirLight light, LightingInput LInput)
{
    vec3 lightDir = normalize(-light.direction.xyz);

    // diffuse shading
    float diff = max(dot(LInput.normal, lightDir), 0.0);

    // specular shading
    vec3 halfWay = normalize(lightDir + LInput.viewDir);
    //vec3 reflectDir = reflect(-lightDir, LInput.normal);
    float spec = pow(max(dot(LInput.normal, halfWay), 0.0), LInput.shininess);

    // combine results
    vec3 ambient_out = light.ambient.xyz * vec3(LInput.diffuse);
    vec3 diffuse_out = light.diffuse.xyz * diff * vec3(LInput.diffuse);
    vec3 specular_out = light.specular.xyz * spec * vec3(LInput.specular);

    return ambient_out + diffuse_out + specular_out;
}

vec3 CalcPointLight(PointLight light, LightingInput LInput)
{
    vec3 lightDir = normalize(light.position.xyz - LInput.position);

    // diffuse shading
    float diff = max(dot(LInput.normal, lightDir), 0.0);

    // specular shading
    vec3 halfWay = normalize(lightDir + LInput.viewDir);
    //vec3 reflectDir = reflect(-lightDir, LInput.normal);
    float spec = pow(max(dot(LInput.normal, halfWay), 0.0), LInput.shininess);

    // attenuation
    float distance = length(light.position.xyz - LInput.position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
    
    // combine results
    vec3 ambient_out = light.ambient.xyz * vec3(LInput.diffuse);
    vec3 diffuse_out = light.diffuse.xyz * diff * vec3(LInput.diffuse);
    vec3 specular_out = light.specular.xyz * spec * vec3(LInput.specular);

    ambient_out *= attenuation;
    diffuse_out *= attenuation ;
    specular_out *= attenuation;

    return ambient_out + diffuse_out + specular_out;
}

vec3 CalculateLighting(LightingInput LInput)
{
	vec3 result = vec3(0,0,0);

    // phase 1: directional lighting
	for(int i = 0; i < numDirLights; i++)
	{
	    result += CalcDirLight(dirlights[i], LInput);
	}
    
    // phase 2: point lights
    for(int i = 0; i < numPointLights; i++)
	{
        result += CalcPointLight(pointLights[i], LInput);    
	}

    return result;
    //return pow(result, vec3(1.0 / 2.2));
}
