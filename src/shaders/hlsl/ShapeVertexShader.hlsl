// This shader is deprecrated
cbuffer ConstantData : register(b0)
{
	float2 position;
	float scale;
	float r;
	float g;
	float b;
};

float4 main( float4 pos : SV_POSITION ) : SV_POSITION
{
	pos.x *= scale;
	pos.y *= scale;

	return float4(pos.xy + position, 1.f, 1.f);
}