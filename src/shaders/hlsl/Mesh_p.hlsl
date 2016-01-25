cbuffer ConstantData : register(b0)
{
	float uvScale;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 texcoord : TEXCOORD0;
	float3 viewdir : TEXCOORD1;
	float3 lightpos : TEXCOORD2;
	float3 worldPos : TEXCOORD3;
};

Texture2D diffuseMap;
Texture2D normalMap;
Texture2D specularMap;
TextureCube skybox;

SamplerState sampleType;

static const float3 ambientColor = float3(0.1, 0.1, 0.1);
static const float3 lightColor = float3(0.6, 0.6, 0.6);
static const float3 specularLight = float3(1.0, 1.0, 1.0);

float4 main(VS_OUTPUT input) : SV_TARGET
{
	input.texcoord *= uvScale;

	float dist = length(input.lightpos- input.worldPos) * 0.005;

	// Color applied by light (diffuse + lightColor)
	float3 diffuseColor = diffuseMap.Sample(sampleType, input.texcoord).xyz;

	float3 normal = normalize(input.normal);
	normal += normalMap.Sample(sampleType, input.texcoord).xyz;

	float3 lightDir = normalize(input.lightpos - input.worldPos);
	float lambertian = max(dot(lightDir, normal), 0.0) - dist;

	// Specularity
	float3 specularMaterial = specularMap.Sample(sampleType, input.texcoord).xyz;
	float shininess = 0;

	if (lambertian > 0)
	{
		float3 halfDir = normalize(lightDir + input.viewdir);
		shininess = pow(max(dot(halfDir, normal), 0.0), 2.0) - dist;
	}

	// #reflections from environment map
	float3 I = normalize(input.worldPos);// - cameraPos
	float3 R = reflect(-I, normalize(input.normal));
	float3 reflectionColor = skybox.Sample(sampleType, R).xyz;

	//--

	// Combine the lights 
//ambientColor * diffuseColor + 
	float4 finalColor = float4(float3(ambientColor * diffuseColor +
		diffuseColor * lambertian +
		specularMaterial * reflectionColor * shininess 
		), 1);

	return finalColor;
		//lambertian * diffuseColor * lightColor +
}