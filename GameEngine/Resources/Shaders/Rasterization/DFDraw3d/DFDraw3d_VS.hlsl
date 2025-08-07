#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.mtxVP);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texCoord;
    output.normal = normalize(mul(input.normal, (float32_t3x3) gTransformform.worldmat));
    output.worldPos = mul(input.position, gTransformform.worldmat).xyz;
    output.instanceId = 0;
    
    return output;
}