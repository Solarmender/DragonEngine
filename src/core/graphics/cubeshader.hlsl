cbuffer transform_buffer : register(b0)
{
    matrix modelMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct vs_in {
    float3 position_local : POS;
};

struct vs_out {
    float4 position_clip : SV_POSITION;
};

vs_out vs_main(vs_in input) {
  vs_out output = (vs_out)0;

  matrix mvp = mul(projectionMatrix, mul(viewMatrix, modelMatrix));
  output.position_clip = mul(float4(input.position_local, 1.0f), mvp);
  return output;
}

float4 ps_main(vs_out input) : SV_TARGET {
  return float4( 0.5, 0.0, 1.0, 1.0 );
}