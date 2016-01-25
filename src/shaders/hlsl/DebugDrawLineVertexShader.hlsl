cbuffer ConstantData : register(b0)
{
	float4x4 world;
	float3 color;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT main(float4 pos : SV_POSITION)
{
	VS_OUTPUT output;
	output.pos = mul(world, pos);
	output.color = float4(color, 1);

	return output;
}