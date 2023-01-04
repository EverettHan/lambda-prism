//////  TWEAKABLES /////////////////////////////////////////////

// positionnement 

samplerCUBE s_SkyMap
<
>;

float Intensity
<
> = float(1);

//////  UNTWEAKABLES /////////////////////////////////////////////

float4x4  wvp                    : WorldViewProjection;
float4x4  world                  : World;
float4x4  viewIT                 : ViewIT;

struct appdata 
{
    float3 Position         : POSITION;
};

struct vertexOutput2 
{
    float4 HPosition        : POSITION;
    float3 Position			: TEXCOORD5;
};

//------------------------------------------
//  Vertex Shader
//------------------------------------------

vertexOutput2 GraphicMaterialVS( appdata IN,
                                uniform float4x4 iWorldViewProj) 
{
    vertexOutput2 OUT;
    
    OUT.Position = IN.Position;

    // screen clipspace coords
    //------------------------
    float4 position = float4( IN.Position.xyz, 1.0 );
    float4 screenPosition= mul( iWorldViewProj, position );
    OUT.HPosition = screenPosition;

    return OUT;
}

//------------------------------------------
//  Pixel Shader
//------------------------------------------

float4 GraphicMaterialPS( vertexOutput2 IN,
						             uniform float4x4 iWorld, 
                         uniform float4x4 iViewIT): COLOR 
{
  float4 result;

  float4 position = float4(IN.Position.xyz, 1.0);
  float3 Pw = mul( iWorld, position).xyz;
  float3 n = normalize(iViewIT[3].xyz - Pw );
  
  n.xyz = n.xzy;

  result = texCUBE(s_SkyMap, n); 
  
  result.xyz *= Intensity;

  return result;
}

////////////////////////////////////////////////////////////////////
/// TECHNIQUES /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

technique GraphicMaterial_GLSL
{
    pass p0 
    {
        VertexProgram = compile glslv GraphicMaterialVS(wvp);
        FragmentProgram = compile glslf GraphicMaterialPS(world, viewIT);
    }
}

technique GraphicMaterial_NV30
{
    pass p0 
    {
        VertexProgram = compile vp30 GraphicMaterialVS(wvp);
        FragmentProgram = compile fp30 GraphicMaterialPS(world, viewIT);
    }
}

technique GraphicMaterial_arb
{
    pass p0 
    {
        VertexProgram = compile arbvp1 GraphicMaterialVS(wvp);
        FragmentProgram = compile arbfp1 GraphicMaterialPS(world, viewIT);
    }
}
