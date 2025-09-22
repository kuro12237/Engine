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
    float4 clip = float4(uv * 2 - 1, depth, 1.0f); // DirectX: z = depth 0~1
    clip.y *= -1.0f; // Y反転

    float4 viewPos = mul(clip, gCamera.mtxProjInv);
    viewPos /= viewPos.w;

    float4 worldPos4 = mul(viewPos, gCamera.mtxViewInv);
    return worldPos4.xyz;
}
PS_OUTPUT main(VS_OUTPUT input)
{
    PS_OUTPUT output;

    // --- depth からワールド位置 ---
    float depth = gDepth.Sample(gSamplerPoint, input.texcoord);
    float3 worldPos = PositionFromDepth(depth, input.texcoord);

    // --- テクスチャ ---
    float4 albedColor = gAlbed.Sample(gSampler, input.texcoord);

    // --- スクリーンサイズから逆解像度 ---
    float2 invRTSize = 1.0f / float2(1280.0f, 720.0f);

    // --- 隣接ピクセルのワールド位置差から法線再構築 ---
    float depthRight = gDepth.Sample(gSamplerPoint, input.texcoord + float2(invRTSize.x, 0)).r;
    float depthDown = gDepth.Sample(gSamplerPoint, input.texcoord + float2(0, invRTSize.y)).r;
    float3 posRight = PositionFromDepth(depthRight, input.texcoord + float2(invRTSize.x, 0));
    float3 posDown = PositionFromDepth(depthDown, input.texcoord + float2(0, invRTSize.y));

    float3 positionDX = posRight - worldPos;
    float3 positionDY = posDown - worldPos;
    float3 N_reconstructed = normalize(cross(positionDX, positionDY));

    float3 cameraPos = gCamera.pos.xyz;
    float3 toEye = normalize(cameraPos - worldPos);
    float3 color = 0.0f;

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
        float NdotL = saturate(dot(N_reconstructed, L));
        float NdotH = saturate(dot(N_reconstructed, halfV));

        float3 lightColor = float3(1, 1, 1) * pl.intensity * att;

        float3 diffuse = albedColor.rgb * lightColor * NdotL;
        float3 specular = lightColor * pow(NdotH, 90.0f);

        color += diffuse + specular;
    }

    ////fog
    //float fogStart = 20.0f;
    //float fogEnd = 125.0f;
    //float fogWeight = saturate((worldPos.z - fogStart) / (fogEnd - fogStart));
    //float3 fogColor = float3(0.8f, 0.8f, 0.8f);
    //color = lerp(color, fogColor, fogWeight);

    output.color = float4(color, 1.0f);
    return output;
}
