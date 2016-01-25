cbuffer ConstantData : register(b0)
{
	float4x4 worldMatrix;
	float4x4 projectionMatrix;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 eyeDir : TEXCOORD0;
};

//TODO: do something about this ugly function
float4x4 inverse(float4x4 input)
{
#define minor(a,b,c) determinant(float3x3(input.a, input.b, input.c))
	//determinant(float3x3(input._22_23_23, input._32_33_34, input._42_43_44))

	float4x4 cofactors = float4x4(
		minor(_22_23_24, _32_33_34, _42_43_44),
		-minor(_21_23_24, _31_33_34, _41_43_44),
		minor(_21_22_24, _31_32_34, _41_42_44),
		-minor(_21_22_23, _31_32_33, _41_42_43),

		-minor(_12_13_14, _32_33_34, _42_43_44),
		minor(_11_13_14, _31_33_34, _41_43_44),
		-minor(_11_12_14, _31_32_34, _41_42_44),
		minor(_11_12_13, _31_32_33, _41_42_43),

		minor(_12_13_14, _22_23_24, _42_43_44),
		-minor(_11_13_14, _21_23_24, _41_43_44),
		minor(_11_12_14, _21_22_24, _41_42_44),
		-minor(_11_12_13, _21_22_23, _41_42_43),

		-minor(_12_13_14, _22_23_24, _32_33_34),
		minor(_11_13_14, _21_23_24, _31_33_34),
		-minor(_11_12_14, _21_22_24, _31_32_34),
		minor(_11_12_13, _21_22_23, _31_32_33)
		);
#undef minor
	return transpose(cofactors) / determinant(input);
}

VS_OUTPUT main(float4 pos : SV_POSITION, float2 texcoord : TEXCOORD0)
{
	VS_OUTPUT output;

	float4x4 inverseProjection = inverse(projectionMatrix);
	float4x4 inverseModelView = transpose(worldMatrix);
	float4 unprojected = (mul(inverseProjection,pos)); //TODO: flip mul if error

	output.eyeDir = (mul(inverseModelView, unprojected)).xyz;
	output.pos = pos;

	return output;
}