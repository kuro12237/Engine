#include"LineDraw.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"

StructuredBuffer<float32_t4> colors : register(t0);

PSOutput main(VSOutput input)
{
    PSOutput output;
 
    output.color = colors[input.instanceId];
    
    return output;
}
