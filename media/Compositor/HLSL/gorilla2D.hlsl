struct VS_INPUT
{
	float4 vertex	: POSITION;
	float4 uv		: TEXCOORD0;
	float4 color	: COLOR0;
};

struct PS_INPUT
{
	float4 gl_Position	: SV_POSITION;
	float4 uv 			: TEXCOORD0;
	float4 color 		: TEXCOORD1;
};

PS_INPUT main_vp( VS_INPUT input )
{
	PS_INPUT outVs;

	outVs.gl_Position = input.vertex; 
	outVs.uv = input.uv;
	outVs.color = input.color;
	
	return outVs;
}

Texture2D atlasTex : register(t0);
SamplerState atlas : register(s0);

float4 main_fp(	PS_INPUT inPs ) : SV_Target
{
	return atlasTex.Sample(atlas, inPs.uv.xy) * inPs.color;	
}
