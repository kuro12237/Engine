


struct PS_OUTPUT
{
    float32_t4 color : SV_TARGET0;
};

struct VS_INPUT
{
    float32_t4 position : POSITION0;
    float32_t2 texCoord : TEXCOORD0;
    
    float32_t3 normal : NORMAL0;
};

struct VS_OUTPUT
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};