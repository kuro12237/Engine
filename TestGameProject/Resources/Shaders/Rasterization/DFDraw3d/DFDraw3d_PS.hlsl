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
ConstantBuffer<WtTransform> gTransformform : register(b1);
ConstantBuffer<SCamera> gCamera : register(b2);
ConstantBuffer<ColorData> gColor : register(b3);

PSOutput main(VSOutput input)
{
    PSOutput output;
 
    
    float32_t4 outColor;
    
    
    float32_t3 N = normalize(input.normal);
    float32_t3 worldPos = input.worldPos;
    float32_t3 cameraPos = gCamera.pos.xyz;
    
    float32_t3 lightDir = normalize(gDirectionLight.direction);
    float32_t3 lightColor = gDirectionLight.color.rgb;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    
    
    float32_t3 toEye = normalize(cameraPos - worldPos);
    float32_t3 hallfVector = normalize(-lightDir + toEye);
    
    float NdotH = saturate(dot(N, hallfVector));
    float spec = pow(saturate(NdotH), 90.0f);
 
    float Ndol = saturate(dot(N, -lightDir));
    float cos = pow(Ndol * 0.5f + 0.5f, 2.0f);
    
    float32_t3 deffiseColor = textureColor.rgb*gColor.color_.rgb * lightColor * cos * gDirectionLight.intencity;
    float32_t3 specularColor = lightColor * gDirectionLight.intencity * spec;
    outColor.rgb = deffiseColor + specularColor;
    outColor.a = textureColor.a*gColor.color_.a;
    output.color = outColor;
    
    return output;
}
