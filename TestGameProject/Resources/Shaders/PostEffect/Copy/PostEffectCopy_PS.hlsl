#include "PostEffectCopy_InOut.hlsli"

#include "../../Common/Camera.hlsli"
#include "../../Common/DirectionLight.hlsli"
#include "../../Common/PointLight.hlsli"

Texture2D<float4> gAlbed : register(t0);
Texture2D<float4> gNormal : register(t1);
Texture2D<float> gDepth : register(t2);
StructuredBuffer<PointLight> gPointLight : register(t3);

SamplerState gSampler : register(s0);
SamplerState gSamplerPoint : register(s1);

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<DirectionLight> gDirectionLight : register(b1);

PS_OUTPUT main(VS_OUTPUT input)
{
    PS_OUTPUT output;

    //depth
    float depth = gDepth.Sample(gSamplerPoint, input.texcoord);
    float z = depth * 2.0f - 1.0f;
    float4 ndcPos = float4(input.texcoord * 2.0f - 1.0f, z, 1.0f);

    // View
    float4 viewPos = mul(ndcPos, gCamera.mtxProjInv);
    viewPos /= viewPos.w;

    // World
    float4 worldPos4 = mul(viewPos, gCamera.mtxViewInv);
    worldPos4 /= worldPos4.w;
    float3 worldPos = worldPos4.xyz;

    //Tex
    float4 albedColor = gAlbed.Sample(gSampler, input.texcoord);
    float3 N = normalize(gNormal.Sample(gSamplerPoint, input.texcoord).xyz * 2.0f - 1.0f);
    
    float3 cameraPos = gCamera.pos.xyz;
    float3 color = 0.0f;
    
    float3 toEye = normalize(cameraPos - worldPos);
    
    //direction
    {
        float3 lightDir = normalize(gDirectionLight.direction);
        float3 lightColor = gDirectionLight.color.rgb * gDirectionLight.intencity;
        
        float3 halfVector = normalize(-lightDir + toEye);

        float NdotL = saturate(dot(N, -lightDir));
        float NdotH = saturate(dot(N, halfVector));

        float3 diffuse = albedColor.rgb * lightColor * NdotL;
        float3 specular = lightColor * pow(NdotH, 64.0f);

        //color += diffuse + specular;
    }

    //point
    [loop]
    for (uint i = 0; i < 32; i++)
    {
        PointLight pl = gPointLight[i];

        
        float3 Lw = pl.pos - worldPos;
        float dist = length(Lw);
        float3 L = Lw / max(dist, 1e-6);

        // 減衰
        float att = saturate(1.0f - dist / pl.rad);
        att = pow(att, max(pl.decay, 1.0f));

        // ハーフベクトル
        float3 halfV = normalize(L + toEye);
        float NdotL = saturate(dot(N, L));
        float NdotH = saturate(dot(N, halfV));

 
        float3 lightColor = float3(1, 1, 1) * pl.intensity * att;

        float3 diffuse = albedColor.rgb * lightColor * NdotL;
        float3 specular = lightColor * pow(NdotH, 64.0f);

        color += diffuse + specular;
    }

    //fog
    float fogStart = 20.0f;
    float fogEnd = 125.0f;
    float fogWeight = saturate((worldPos.z - fogStart) / (fogEnd - fogStart));
    float3 fogColor = float3(0.8f, 0.8f, 0.8f);
    color = lerp(color, fogColor, fogWeight);

    output.color = float4(color, 1.0f);
    return output;
}
