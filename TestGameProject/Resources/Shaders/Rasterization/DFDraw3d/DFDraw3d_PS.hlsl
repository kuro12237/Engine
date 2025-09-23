#include"../VS_InOut.hlsli"
#include"../PS_Output.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

#include"../../Common/DirectionLight.hlsli"


Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct ColorData
{
    float32_t4 color_;
    
};


ConstantBuffer<DirectionLight> gDirectionLight : register(b0);
ConstantBuffer<SCamera> gCamera : register(b2);
StructuredBuffer<ColorData> gColor : register(t3);

PSOutput main(VSOutput input)
{
    PSOutput output;
 
    
    float32_t4 outColor;
    
    
    float32_t3 N = input.normal;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    

    outColor.rgb = textureColor.rgb * gColor[input.instanceId].color_.a;
    outColor.a = textureColor.a * gColor[input.instanceId].color_.a;
    output.color = outColor;
    output.normal = float32_t4((input.normal * 0.5f + 0.5f), 1.0f);
    
    return output;
}
