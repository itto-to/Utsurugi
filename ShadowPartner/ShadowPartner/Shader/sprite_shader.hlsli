uint order_in_rayer;

struct VSOutput
{
	float4 pos : POSITION;
	float4 z : TEXCOORD0;
};

VSOutput vsmain(float pos:POSITION)
{
	VSOutput out;



	return out;
}

float4 psmain(float4 z:TEXCOORD0):COLOR
{
	return float4(1.0f,1.0f,1.0f,1.0f);
}