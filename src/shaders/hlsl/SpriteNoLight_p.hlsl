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
	float4 color = shaderTexture.Sample(sampleType, input.texcoord.xy);   //TODO texcoord.xy * textureScale   -> needs constantBuffer

	return color;
}