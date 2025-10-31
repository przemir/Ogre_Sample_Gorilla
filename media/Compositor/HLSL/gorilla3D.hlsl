struct VS_INPUT
{
	float4 vertex	: POSITION;
	float2 uv		: TEXCOORD0;
	float4 color	: COLOR0;
};

struct PS_INPUT
{
	float4 gl_Position	: SV_Position;
	float2 uv 			: TEXCOORD0;
	float4 color 		: TEXCOORD1;
};

PS_INPUT main_vp(VS_INPUT input, uniform matrix worldViewProj )
{
	PS_INPUT outVs;

	outVs.gl_Position = mul(worldViewProj, input.vertex);
	outVs.uv = input.uv;
	outVs.color = input.color;
	
	return outVs;
}

Texture2D atlas	: register(t0);
SamplerState samplerState : register(s0);

float4 main_fp(	PS_INPUT inPs) : SV_Target
{
	return atlas.Sample(samplerState, inPs.uv) * inPs.color;	
}
