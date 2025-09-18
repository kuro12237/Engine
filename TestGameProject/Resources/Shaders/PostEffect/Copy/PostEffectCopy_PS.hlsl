#include"PostEffectCopy_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/DirectionLight.hlsli"

Texture2D<float32_t4> gAlbed : register(t0);
Texture2D<float32_t4> gNormal : register(t1);
Texture2D<float32_t> gDepth : register(t2);

SamplerState gSampler : register(s0);
SamplerState gSamplerPoint : register(s1);


ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<DirectionLight> gDirectionLight : register(b1);

PS_OUTPUT main(VS_OUTPUT input)
{
    PS_OUTPUT output;

    // --- 深度を NDC に変換 ---
    float32_t depth = gDepth.Sample(gSamplerPoint, input.texcoord);
    float32_t z = depth * 2.0f - 1.0f;
    float32_t4 ndcPos = float4(input.texcoord * 2.0f - 1.0f, z, 1.0f);
    float32_t4 worldPos = mul(ndcPos, gCamera.mtxProjInv);
    worldPos /= worldPos.w;
    
    
    float32_t4 albedColor = gAlbed.Sample(gSampler, input.texcoord);
    float32_t3 N = normalize(gNormal.Sample(gSamplerPoint, input.texcoord).xyz * 2.0f - 1.0f);
  
    //ライト計算
    float32_t3 cameraPos = gCamera.pos.xyz;
    
    float32_t3 lightDir = normalize(gDirectionLight.direction);
    float32_t3 lightColor = gDirectionLight.color.rgb;
    
    float32_t3 toEye = normalize(cameraPos - worldPos.xyz);
    float32_t3 hallfVector = normalize(-lightDir + toEye);
    
    float32_t NdotH = saturate(dot(N, hallfVector));
    float32_t spec = pow(saturate(NdotH), 90.0f);
 
    float32_t Ndol = saturate(dot(N, -lightDir));
    float32_t cos = pow(Ndol * 0.5f + 0.5f, 2.0f);
    
    float32_t3 deffiseColor = albedColor.rgb * lightColor * cos * gDirectionLight.intencity;
    float32_t3 specularColor = lightColor * gDirectionLight.intencity * spec;
  

    float32_t3 color = deffiseColor + specularColor;
    
    
    //fog
    float fogStart = 20.0f; // フォグが始まる距離
    float fogEnd = 125.0f; // フォグが完全にかかる距離
    float fogWeight = 0.0f;
    if (worldPos.z > fogStart)
    {
        fogWeight = saturate((worldPos.z - fogStart) / (fogEnd - fogStart));
        fogWeight *= 0.5f * max(0.0f, 1.0f - exp(-0.1f * worldPos.z));
    }
    float32_t3 fogColor = float32_t3(0.8f, 0.8f, 0.8f);
    
    color = lerp(color.rgb, fogColor, fogWeight);
    

    output.color = float32_t4(color, 1.0f);
   //output.color = float4(N, 1.0f);

    return output;
}