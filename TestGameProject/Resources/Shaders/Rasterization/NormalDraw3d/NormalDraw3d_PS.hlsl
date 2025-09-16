#include"../VS_InOut.hlsli"
#include"../PS_Output.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

#include"../../Common/DirectionLight.hlsli"




struct ColorData
{
    float32_t4 color_;
    
};


ConstantBuffer<DirectionLight> gDirectionLight : register(b0);
ConstantBuffer<SCamera> gCamera : register(b2);

Texture2D<float32_t4> gTexture : register(t1);

StructuredBuffer<ColorData> gColor : register(t2);
Texture2D<float32_t4> gNormalTexture : register(t3);

SamplerState gSampler : register(s0);

PSOutput main(VSOutput input)
{
    PSOutput output;
 
    
    float32_t4 outColor;
    
    
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float32_t4 normalTexture = gNormalTexture.Sample(gSampler, input.texcoord);

    outColor.rgb = textureColor.rgb * gColor[input.instanceId].color_.a;
    outColor.a = textureColor.a * gColor[input.instanceId].color_.a;
    output.color = outColor;
    output.normal = float32_t4(normalize(normalTexture.rgb * input.normal), 1.0f);
    
    return output;
}