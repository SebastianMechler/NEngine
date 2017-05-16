Texture2D myTexture : register(t0);
Texture2D textureHeight : register(t1);

cbuffer Static : register ( cb1 )
{
	float2 ScreenSize;
};

cbuffer DynamicBuffer : register ( cb0 )
{
	float4x4 wvp;
	float timer;
};

SamplerState samplerState
{
  Filter = MIN_MAG_MIP_POINT;
  AddressU = WRAP;
  AddressV = WRAP;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct PS_INPUT
{
	float4 position : SV_POSITION; //pixel shader NEEDS SV_POSITION
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.position = input.position;
	//output.position.x = (output.position.x / (ScreenSize.x / 2)) - 1.0f;
	//output.position.y = -((output.position.y / (ScreenSize.y / 2)) - 1.0f);
	
	float result = textureHeight.Load(int3(input.uv.x*256, input.uv.y*256, 0)).r;
	
	if (result < 0.3)
	{
		output.position.y += sin(timer*0.4 + (input.position.x*0.1)) * 2;
    }
	else
	{
		output.position.y += result * 5;	
	}
	
	
	
	output.position = mul(output.position, wvp);
	
	output.color = input.color;
	
	output.uv = input.uv;
	return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 textureColor = myTexture.Sample(samplerState, input.uv).rgba;
	float4 vertexColor = input.color;
	
	float4 color = textureColor * vertexColor;
	return float4(color.r, color.g, color.b, color.a);
}