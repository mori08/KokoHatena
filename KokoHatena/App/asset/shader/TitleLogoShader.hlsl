Texture2D    g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_internal;
}

cbuffer Shift : register(b1)
{
	float2 g_rShift;
	float2 g_gShift;
	float2 g_bShift;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
	float2 ra = g_texture0.Sample(g_sampler0, input.uv + g_rShift).ra;
	float2 ga = g_texture0.Sample(g_sampler0, input.uv + g_gShift).ga;
	float2 ba = g_texture0.Sample(g_sampler0, input.uv + g_bShift).ba;

	float a = (ra.y + ga.y + ba.y) / 3;
	float4 texColor = float4(ra.x, ga.x, ba.x, a);

	return (texColor * input.color) + g_colorAdd;
}