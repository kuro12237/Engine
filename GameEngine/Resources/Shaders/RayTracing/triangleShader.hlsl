
struct Vertex
{
    float4 Position;
    float3 normal;
};


RaytracingAccelerationStructure gRtScene : register(t0);

struct SCamera
{
    float32_t4x4 mtxProj;
    float32_t4x4 mtxProjInv;
    float32_t4x4 mtxView;
    float32_t4x4 mtxViewInv;
    float32_t4x4 mtxVP;
};

ConstantBuffer<SCamera> gCamera : register(b0);
RWTexture2D<float4> gOutput : register(u3,space0);


// Local Root Signature (for HitGroup)
StructuredBuffer<uint32_t> indexBuffer : register(t1, space0);
StructuredBuffer<Vertex> vertexBuffer : register(t2, space0);

struct Payload
{
    float32_t3 color;
};
struct MyAttribute
{
    float32_t2 barys;
};

//レイの処理
[shader("raygeneration")]
void mainRayGen()
{
    uint32_t2 launchIndex = DispatchRaysIndex().xy;
    float32_t2 dims = float2(DispatchRaysDimensions().xy);
    
    float32_t2 d = (launchIndex.xy + 0.5) / dims.xy * 2.0 - 1.0;
    float32_t aspect = dims.x / dims.y;

    float32_t4x4 mtxViewInv = gCamera.mtxViewInv;
    float32_t4x4 mtxProjInv = gCamera.mtxProjInv;

    RayDesc rayDesc;
    rayDesc.Origin = mul(mtxViewInv, float32_t4(0, 0, 0, 1)).xyz;

    float32_t4 target = mul(mtxProjInv, float32_t4(d.x, -d.y, 1, 1));
    rayDesc.Direction = mul(mtxViewInv, float32_t4(target.xyz, 0)).xyz;

    rayDesc.TMin = 0;
    rayDesc.TMax = 100000;

    Payload payload;
    payload.color = (float32_t3)0;

    RAY_FLAG flags = RAY_FLAG_NONE;
    uint32_t rayMask = 0xFF;

    TraceRay(
        gRtScene,
        flags,
        rayMask,
        0,
        1,
        0,
        rayDesc,
        payload);
    float3 col = payload.color;
    // 結果格納.
    gOutput[launchIndex.xy] = float4(col, 1);
}

//外れたとき
[shader("miss")]
void mainMS(inout Payload payload)
{
    payload.color = float3(0.1f, 0.25f, 0.5f);
}


float3 CalcBarycentrics(float2 barys)
{
    return float3(
        1.0 - barys.x - barys.y,
        barys.x,
        barys.y);
}

Vertex GetHitVertex(MyAttribute attrib)
{
    Vertex v = (Vertex) 0;
    float3 barycentrics = CalcBarycentrics(attrib.barys);
    uint vertexId = PrimitiveIndex() * 3; // Triangle List のため.

    float weights[3] =
    {
        barycentrics.x, barycentrics.y, barycentrics.z
    };
    for (int i = 0; i < 3; ++i)
    {
        uint index = indexBuffer[vertexId + i];
        float w = weights[i];
        v.Position += vertexBuffer[index].Position * w;
        v.normal = (float32_t3) 0;

    }
    return v;
}

//当たった時
[shader("closesthit")]
void mainCHS(inout Payload payload, MyAttribute attrib)
{
    Vertex vtx = GetHitVertex(attrib);
    payload.color.rgb = float3(0.1f, 0.25f, 0.5f);

}
