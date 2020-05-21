layout (std140, binding = 5) uniform Utils
{
    vec4 R_Time;
    vec4 R_SinTime;
    vec4 R_CosTime;
};

float LinearDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

float Linear01Depth(float depth) 
{
    return LinearDepth(depth) / (far - near);	
}