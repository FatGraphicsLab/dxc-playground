struct a2v {
    float4 Position : SV_Position;
};

struct v2p {
    float4 Position : SV_Position;
};

struct v2p main(struct a2v IN, uniform float4x4 ModelViewMatrix)
{
    v2p OUT;
    OUT.Position = mul(IN.Position, ModelViewMatrix);
    return OUT;
}
