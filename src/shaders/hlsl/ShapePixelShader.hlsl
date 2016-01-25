// This shader is deprecrated
cbuffer ConstantData : register(b0)
{
	float2 position;
	float scale;
	float r;
	float g;
	float b;
};

float4 main(float4 pos : SV_POSITION) : SV_TARGET
{
	/*
	float2 target = float2(400, 300);
	float2 position = float2(input.pos.x, input.pos.y);

	float distance = length(target - position);

	float4(distance/800, 0, 0, 1);
	*/

	return float4(r, g, b, 1);
}