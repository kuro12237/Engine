
struct WtTransform
{
    float32_t4x4 worldmat;
    float32_t4x4 worldMatInv_;
    float32_t4x4 VPV;
    float32_t4 pos;
};