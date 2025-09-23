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
float3 PositionFromDepth(float depth, float2 uv)
{
    float4 clip = float4(uv * 2 - 1, depth, 1.0f);
    clip.y *= -1.0f; // Y反転

    float4 viewPos = mul(clip, gCamera.mtxProjInv);
    viewPos /= viewPos.w;

    float4 worldPos4 = mul(viewPos, gCamera.mtxViewInv);
    return worldPos4.xyz;
}
PS_OUTPUT main(VS_OUTPUT input)
{
    PS_OUTPUT output;
    
    //depth
    float depth = gDepth.Sample(gSamplerPoint, input.texcoord);
    float3 worldPos = PositionFromDepth(depth, input.texcoord);
    //albed
    float4 albedColor = gAlbed.Sample(gSampler, input.texcoord);

    //法線
    float3 N = gNormal.Sample(gSamplerPoint, input.texcoord).xyz * 2.0f - 1.0f;
    N = normalize(N);
    
    float3 cameraPos = gCamera.pos.xyz;
    float3 toEye = normalize(cameraPos - worldPos);
    float3 color = 0.0f;
       //fog
    float fogStart = cameraPos.z;
    float fogEnd = cameraPos.z + 125.0f;
    float fogWeight = saturate((worldPos.z - fogStart) / (fogEnd - fogStart));
    float3 fogColor = float3(0.8f, 0.8f, 0.8f);
    //color = lerp(color, fogColor, fogWeight);

    //point
    [loop]
    for (uint i = 0; i < 128; i++)
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

        float3 lightColor = pl.color.rgb * pl.intensity * att;

        float3 diffuse = albedColor.rgb * lightColor * NdotL;
        float3 specular = lightColor * pow(NdotH, 90.0f);

        color += diffuse + specular;
    }

 
    output.color = float4(color, 1.0f);
    return output;
}
