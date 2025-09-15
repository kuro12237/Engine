#include"PostEffectCopy_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.orthographics);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texCoord;
 
    return output;
}