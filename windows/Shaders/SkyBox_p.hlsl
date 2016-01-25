struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 eyeDir : TEXCOORD0;
};

TextureCube skybox;
SamplerState sampleType;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	//float4 color = shaderTexture.Sample(sampleType, input.texcoord.xy);
	//return color;

	return skybox.Sample(sampleType, input.eyeDir);

	//return float4(input.eyeDir, 1.f);
}