cbuffer ConstantData : register(b0)
{
	float4x4 worldMatrix;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float3 cameraPosition;
	float3 lightPos;
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

VS_OUTPUT main(float4 pos : SV_POSITION, float3 normal : NORMAL, float4 texcoord : TEXCOORD0)
{
	VS_OUTPUT output;

	output.pos = mul(worldMatrix, pos);
	output.pos = mul(viewMatrix, output.pos);
	output.pos = mul(projectionMatrix, output.pos);

	output.normal = mul(worldMatrix, normal);

	output.texcoord = texcoord;

	output.worldPos = mul(pos, worldMatrix);
	output.viewdir = output.worldPos.xyz - cameraPosition;

	output.lightpos = lightPos;

	return output;
}