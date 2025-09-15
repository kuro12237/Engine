#include"PostEffectCopy_InOut.hlsli"

Texture2D<float32_t4> gAlbed : register(t0);
SamplerState gSampler : register(s0);

PS_OUTPUT main(VS_OUTPUT input)
{
    PS_OUTPUT output;
    
    float32_t4 color = gAlbed.Sample(gSampler, input.texcoord);
    
    output.color = color;

    return output;
}