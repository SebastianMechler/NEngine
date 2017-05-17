cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
	float totalTime;
};

SamplerState DefaultSampler : register(s0);
Texture2D defaultTexture : register(t0);
Texture2D textureHeight : register(t1);

SamplerState Sampler2D
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	
	float result = textureHeight.Load(int3(input.uv.x*256, input.uv.y*256, 0)).r;

	input.position.y += sin(totalTime + (input.position.x*0.1));
	
	output.position = mul(mul(mul(float4(input.position.xyz, 1), world), view), projection);
	output.color = input.color;
	output.normal = input.normal;
	output.uv = input.uv;
	return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
  float3 texColor = defaultTexture.Sample(DefaultSampler, input.uv);
  
  return float4(texColor, 1);
}