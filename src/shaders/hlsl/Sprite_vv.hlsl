struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

VS_OUTPUT main(float4 pos : SV_POSITION, float2 texcoord : TEXCOORD0)
{
	VS_OUTPUT output;

	output.pos = float4(pos.xyz, 1.f);
	output.texcoord = texcoord;

	return output;
}