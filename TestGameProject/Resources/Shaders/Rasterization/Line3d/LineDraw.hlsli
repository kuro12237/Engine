struct VSInput
{
    float32_t4 position : POSITION0;
    uint vertexId : SV_VertexID;
};
struct VSOutput
{
    float32_t4 position : SV_POSITION;
    float32_t3 noamal : NORMAL0;
    float32_t2 texCooad : TEXCOORD0;
    uint32_t instanceId : INSTANCEID0;
};

struct PSOutput
{
    float32_t4 color : SV_TARGET0;
};