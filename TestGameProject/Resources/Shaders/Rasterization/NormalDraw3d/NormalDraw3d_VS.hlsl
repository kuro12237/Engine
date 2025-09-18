#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
StructuredBuffer<WtTransform> gTransformform : register(t0);


VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    float32_t4x4 resultMatrix = mul(gTransformform[instanceId].worldmat, gCamera.mtxVP);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texCoord;
    output.normal = normalize(mul(input.normal, (float32_t3x3) gTransformform[instanceId].worldmat));
    output.instanceId = instanceId;
    
    return output;
}