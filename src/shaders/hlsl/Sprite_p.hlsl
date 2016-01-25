cbuffer ConstantData : register(b0)
{
	float r_width;
	float r_height;
	float4 ambientLight;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

Texture2D shaderTexture;
Texture2D lightData;
SamplerState sampleType;

float4 main(VS_OUTPUT input) : SV_TARGET
{
	float2 screenspace = input.pos.xy;
	screenspace.x /= r_width;
	screenspace.y /= r_height;

	float4 light = lightData.Sample(sampleType, screenspace);

	light += ambientLight;

	float4 color = shaderTexture.Sample(sampleType, input.texcoord.xy);   //TODO texcoord.xy * textureScale   -> needs constantBuffer

	//NOTE: LIGHTS DISABLED TEMPORARILY!
	//return color * light;

	return color;
}