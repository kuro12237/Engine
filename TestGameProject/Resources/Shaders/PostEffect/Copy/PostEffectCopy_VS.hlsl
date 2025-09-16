#include"PostEffectCopy_InOut.hlsli"

#include"../../Common/Camera.hlsli"
#include"../../Common/WtTransform.hlsli"

ConstantBuffer<SCamera> gCamera : register(b0);
ConstantBuffer<WtTransform> gTransformform : register(b1);


static const uint32_t kNumVertex = 3;

static const float32_t4 kPositions[kNumVertex] =
{
    { -1.0f, 1.0f, 0.0f, 1.0f },
    { 3.0f, 1.0f, 0.0f, 1.0f },
    { -1.0f, -3.0f, 0.0f, 1.0f }
};

static const float32_t2 kTexCoords[kNumVertex] =
{
    { 0.0f, 0.0f },
    { 2.0f, 0.0f },
    { 0.0f, 2.0f }
};
VS_OUTPUT main(VS_INPUT input, uint32_t vertexId : SV_VertexID)
{
    VS_OUTPUT output;
    float32_t4x4 resultMatrix = mul(gTransformform.worldmat, gCamera.orthographics);
  
    output.position = kPositions[vertexId];
    output.texcoord = kTexCoords[vertexId];
    return output;
}