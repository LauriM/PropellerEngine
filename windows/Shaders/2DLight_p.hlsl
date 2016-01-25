cbuffer ConstantData : register(b0)
{
	float2 lightPos; // position where the "light" is positioned in the world (screenspace)
	float3 lightcolor;
	float lightDistance;
	//TODO: Add some specifications about the light here
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

// generating light data from light sources
float4 main(VS_OUTPUT output) : SV_TARGET
{
	//TODO: CLEAN UP THIS SHADER ! Useless variables, etc.
	// Lightposition is in the screenspace
	// Texcoord is the whole screen pos

	float d = distance(lightPos, output.texcoord.xy);

	float power = 0.f;

	power = (1 / d * 5) / 100;

	if (d < 0.03) // inner circle that gets full light
		power = 1.f;

	power *= 1;

	if (d > 0.5) //TODO: light distance to screenspace ?!?
		power = 0;

	// use the light data to filter info that gets rendered
	//float4(power, power, power, 1.f);

	float3 result = lightcolor;

		// DISABLING THE USAGE OF lightcolor, because some flickering and stuff
	result = float3(1.f, 1.f, 1.f);

	if (power < 0.4)
		discard;

	return float4(result * power, 1.0f);
}