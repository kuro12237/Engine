#include"LineDraw.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/Vert.hlsli"
#include"../../Common/WtTransform.hlsli"
ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);

StructuredBuffer<float32_t3> gLine : register(t0);


VSOutput main(VSInput input, uint32_t instanceId : SV_InstanceID)
{
    VSOutput output;
    
    float32_t4x4 camera = mul(gCamera.mtxView, gCamera.mtxProj);
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, camera);

    output.position = mul(float32_t4(gLine[input.vertexId + (instanceId * 2)].xyz, 1.0f), resultMatrix);
    output.noamal = gLine[input.vertexId + (instanceId * 2)].xyz;
    output.texCooad = float32_t2(0.0f, 0.0f);
    output.instanceId = input.vertexId + instanceId * 2;
    
    return output;
}