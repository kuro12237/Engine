struct VSInput
{
    float32_t4 position : POSITION0;
    float32_t3 normal : NORMAL0;
    float32_t2 texCoord : TEXCOORD0;
    uint32_t instancedId : INSTANCEID0;
};

struct VSOutput
{
    float32_t4 position : SV_POSITION;
    float32_t3 normal : NORMAL0;
    float32_t2 texcoord : TEXCOORD0;
    
    float32_t3 worldPos : WORLDPOS0;
    uint32_t instanceId : INSTANCEID0;
};


struct VS2dInput
{
    float32_t4 position : POSITION0;
    float32_t2 texCoord : TEXCOORD0;
};

struct VS2dOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    
};

