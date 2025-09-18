#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
StructuredBuffer<WtTransform> gTransformform : register(t1);


VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    float32_t4x4 resultMatrix = mul(gTransformform[instanceId].worldmat, gCamera.mtxVP);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texCoord;
    float32_t3 N = normalize(mul(input.normal, (float32_t3x3) gTransformform[instanceId].worldMatInvTranspose));
    output.normal = float32_t3(N.xy, N.z);
    output.instanceId = instanceId;
    
    return output;
}