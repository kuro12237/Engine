#include"../VS_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VS2dOutput main(VS2dInput input, uint32_t instanceId : SV_InstanceID)
{
    VS2dOutput output;
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.orthographics);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texCoord;
 
    
    return output;
}