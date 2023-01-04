//////  TWEAKABLES /////////////////////////////////////////////
sampler2D shadowTexture
<
>;

float4x4 shadowMatrix
<
>;

float3 lightPosition
<
>;

float textureSizeInv
<
> = 0.001953125;

float4 shadowColor
<
>;


//////  UNTWEAKABLES /////////////////////////////////////////////
float4x4  wvp                    : WorldViewProjection;
float4x4  world                  : World;
float4x4  worldIT                : WorldIT;
float4x4  worldView              : WorldView;
float4x4  worldViewIT            : WorldViewIT;

/* Clipping Planes Begin */
float4 ClippingPlane[6] : state.clip[].plane;

struct appdata 
{
  float3 Position : POSITION;
  float4 Normal   : NORMAL;
};

struct vertexOutput2 
{
  float4 HPosition        : POSITION;
  float3 WorldPosition    : TEXCOORD1;
  float3 WorldNormal      : TEXCOORD2;
};

struct vertexOutputClip 
{
  float4 HPosition        : POSITION;
  float3 WorldPosition    : TEXCOORD1;
  float3 WorldNormal      : TEXCOORD2;
	float  clip[6]          : CLP0;	
};


#define NUM_BLUR_12 12
#define INV_NUM_BLUR_12 0.08333334
float2 filterBlurData12[NUM_BLUR_12]=
{
  {-0.326212f, -0.405805f},
  {-0.840144f, -0.07358f},
  {-0.695914f, 0.457137f},
  {-0.203345f, 0.620716f},
  {0.96234f,   -0.194983f},
  {0.473434f,  -0.480026f},
  {0.519456f, 0.767022f},
  {0.185461f, -0.893124f},
  {0.507431f, 0.064425f},
  {0.89642f,  0.412458f},
  {-0.32194f, -0.932615f},
  {0.791559f, -0.597705f}
};


#define NUM_BLUR_24 24
#define INV_NUM_BLUR_24 0.04166667
float2 filterBlurData24[NUM_BLUR_24]=
{
  { -0.263427f, 0.161844f },
  { 0.364205f, -0.183763f },
  { 0.769506f, 0.337566f },
  { -0.396600f, -0.679442f },
  { 0.138958f, 0.792672f },
  { 0.614946f, -0.837699f },
  { -0.818982f, 0.310674f },
  { 0.327291f, 0.275727f },
  { -0.102761f, -0.262793f },
  { -0.908414f, -0.810217f },
  { 0.754156f, -0.276544f },
  { -0.669333f, -0.122617f },
  { -0.032408f, -0.708766f },
  { -0.427981f, 0.490042f },
  { -0.550439f, 0.914856f },
  { 0.952578f, 0.873104f },
  { -0.082245f, 0.465535f },
  { 0.420011f, -0.556384f },
  { 0.494269f, 0.823803f },
  { -0.742092f, -0.506239f },
  { 0.916728f, 0.026635f },
  { 0.073574f, 0.034764f },
  { -0.166879f, 0.945482f },
  { 0.269445f, -0.883196f },
};

#define NUM_BLUR_36 36
#define INV_NUM_BLUR_36 0.02777778
float2 filterBlurData36[NUM_BLUR_36]=
{
  { -0.466033f, -0.727281f },
  { 0.691773f, -0.706676f },
  { 0.286636f, 0.235710f },
  { 0.486633f, 0.782249f },
  { -0.176839f, 0.076096f },
  { 0.810617f, 0.290002f },
  { -0.971155f, 0.112898f },
  { -0.630735f, -0.227280f },
  { 0.255289f, -0.189793f },
  { -0.814581f, -0.503924f },
  { -0.046754f, 0.650071f },
  { -0.491923f, 0.864871f },
  { -0.314016f, 0.583050f },
  { -0.202227f, -0.945657f },
  { -0.624561f, 0.101344f },
  { 0.918883f, 0.649321f },
  { 0.858319f, 0.923524f },
  { -0.890432f, -0.769116f },
  { -0.606553f, 0.599720f },
  { 0.774406f, -0.230223f },
  { -0.064338f, -0.493898f },
  { -0.037779f, -0.175662f },
  { 0.163211f, -0.667066f },
  { 0.450942f, -0.553212f },
  { 0.090658f, 0.938944f },
  { 0.468751f, -0.011492f },
  { -0.328237f, -0.285611f },
  { 0.499174f, 0.422268f },
  { -0.918321f, -0.210840f },
  { -0.874533f, 0.412825f },
  { 0.865957f, -0.498458f },
  { -0.764313f, 0.850431f },
  { 0.232528f, 0.657770f },
  { 0.417316f, -0.910964f },
  { -0.045487f, 0.317588f },
  { -0.434723f, 0.328398f },
};

#define PENOMBRA 0.1f
#define INV_PENOMBRA 10

float offset_lookupATI(sampler2D i_map, float4 i_position, float2 i_offset, float i_textureSizeInv)
{
  float result = tex2Dproj(i_map, float4(i_position.xy + i_offset * float2(i_textureSizeInv, i_textureSizeInv) * i_position.w, i_position.z, i_position.w));
  if (result >= i_position.z/i_position.w) return 1;
  else return 0;
}

float offset_lookup(sampler2D i_map, float4 i_position, float2 i_offset, float i_textureSizeInv)
{
  return tex2Dproj(i_map, float4(i_position.xy + i_offset * float2(i_textureSizeInv, i_textureSizeInv) * i_position.w, i_position.z, i_position.w));
}

// Hard shadows
// ----------------------------------------------------------------------------
float GetSpotShadowCoeffHard(sampler2D i_shadowTexture, float4 i_texCoordLight)
{
  float shadowCoeff = 1.0;
  shadowCoeff = offset_lookup(i_shadowTexture, i_texCoordLight, float2(0, 0), 1);
  return shadowCoeff;
}
// Brute force shadows
// ----------------------------------------------------------------------------
float GetSpotShadowCoeffBruteForce(sampler2D i_shadowTexture, float4 i_texCoordLight, float i_textureSizeInv)
{
  float shadowCoeff = 1.0;

  // Brute force method
  // ------------------
  float sum = 0.0;
  float x=0.0, y=0.0;

  float maxValue = 2.5;
  float minValue = -2.5;
  for (y = minValue; y <= maxValue; y += 1.0)
  {
    for (x = minValue; x <= maxValue; x += 1.0)
    {
      sum += offset_lookup(i_shadowTexture, i_texCoordLight, float2(x, y), i_textureSizeInv);
    }
  }
  shadowCoeff = sum/36.0;

  return shadowCoeff;
}

float GetSpotShadowCoeffPoisson(sampler2D i_shadowTexture, float4 i_texCoordLight, float i_textureSizeInv, int i_nbPoints, float i_inv, float2 i_filterData[])
{
  float shadowCoeff = 1.0;

  // Soft with poisson filter
  // ------------------------
  float k = 2.5;
  for(int i=0; i<i_nbPoints; i++)
  {
    float2 coord = k * i_filterData[i];
    shadowCoeff += offset_lookup(i_shadowTexture, i_texCoordLight, coord, i_textureSizeInv);
  }
  shadowCoeff *= i_inv;

  return shadowCoeff;
}

//------------------------------------------
//  Vertex Shader
//------------------------------------------
vertexOutputClip ShadowVS( appdata IN,
    uniform float4x4 iWorldViewProj,
    uniform float4x4 iWorld,
    uniform float4x4 iWorldIT,
    uniform float4x4 iWorldView
    ) 
{
  vertexOutputClip OUT;

  // object coordinates
  //-------------------
  float4 position = float4( IN.Position.xyz, 1.0 );
  OUT.HPosition = mul( iWorldViewProj, position );
  
  // world position
  //---------------
  float3 WorldPosition = mul( iWorld, position ).xyz;
  OUT.WorldPosition = WorldPosition;

  float3 N = mul( iWorldIT, IN.Normal ).xyz;
  OUT.WorldNormal = N;

  // Clipping
  //------------------------
  float4 WVposition = mul(iWorldView, position);	        
  for (int i=0; i<6; i++)
  {
    OUT.clip[i] = dot(ClippingPlane[i],WVposition);	
	}
	  
  return OUT;
}

vertexOutput2 ShadowVS_2( appdata IN,
    uniform float4x4 iWorldViewProj,
    uniform float4x4 iWorld,
    uniform float4x4 iWorldIT,
    uniform float4x4 iWorldView,
    uniform float4x4 iWorldViewIT
    ) 
{
  vertexOutput2 OUT;

  // object coordinates
  //-------------------
  float4 position = float4( IN.Position.xyz, 1.0 );
  OUT.HPosition = mul( iWorldViewProj, position );

  // view position
  //---------------
  float3 viewPosition = mul( iWorldView, position ).xyz;
  float3 viewNormal = mul( iWorldViewIT, IN.Normal ).xyz;
  
  // world position
  //---------------
  float3 WorldPosition = mul( iWorld, position ).xyz;
  OUT.WorldPosition = WorldPosition;

  float3 N = mul( iWorldIT, IN.Normal ).xyz;
  OUT.WorldNormal = N*-sign(dot(viewPosition, viewNormal));

  return OUT;
}


//------------------------------------------
//  Pixel Shader
//------------------------------------------
float4 ShadowPS_1( vertexOutput2 IN,
    uniform sampler2D i_shadowTexture,
    uniform float4x4  i_shadowMatrix,
    uniform float4    i_shadowColor,
    uniform float3    i_lightPosition,
    uniform float i_shadowtextureSizeInv,
    float iVf : FACE
    ): COLOR 
{
  float4 result = float4(i_shadowColor.xyz, 1.0);
  float shadowCoeff = 1.;

  float3 Ln = normalize(i_lightPosition - IN.WorldPosition);
  float3 Nn = normalize( IN.WorldNormal );
  Nn = sign(iVf)*Nn;

  float dotProduct = dot(Ln, Nn);
  if (dotProduct > 0.f)
  {
    if (dotProduct <= PENOMBRA)
      result.a = (PENOMBRA-dotProduct)*INV_PENOMBRA;
    else
      result.a = 0.0;

    float4 texCoordLight = mul(i_shadowMatrix,float4(IN.WorldPosition, 1));
    if (texCoordLight.z > 0) 
    {
      shadowCoeff = GetSpotShadowCoeffBruteForce(i_shadowTexture, texCoordLight, i_shadowtextureSizeInv);
    }
    result.a =  max(1-shadowCoeff, result.a);
  }
  
  result.a *= i_shadowColor.a;
  
  return result;
}

float4 ShadowPS_2( vertexOutput2 IN,
    uniform sampler2D i_shadowTexture,
    uniform float4x4  i_shadowMatrix,
    uniform float4    i_shadowColor,
    uniform float3    i_lightPosition,
    uniform float i_shadowtextureSizeInv
    ): COLOR 
{
  float4 result = float4(i_shadowColor.xyz, 1.0);
  float shadowCoeff = 1.;

  float3 Ln = normalize(i_lightPosition - IN.WorldPosition);
  float3 Nn = normalize( IN.WorldNormal );

  float dotProduct = dot(Ln, Nn);
  if (dotProduct > 0.f)
  {
    if (dotProduct <= PENOMBRA)
      result.a = (PENOMBRA-dotProduct)*INV_PENOMBRA;
    else
      result.a = 0.0;

    float4 texCoordLight = mul(i_shadowMatrix,float4(IN.WorldPosition, 1));
    if (texCoordLight.z > 0) 
    {
      shadowCoeff = GetSpotShadowCoeffBruteForce(i_shadowTexture, texCoordLight, i_shadowtextureSizeInv);
    }
    result.a =  max(1-shadowCoeff, result.a);
  }
  
  result.a *= i_shadowColor.a;
  
  return result;
}

float4 ShadowPS_3( vertexOutput2 IN,
    uniform sampler2D i_shadowTexture,
    uniform float4x4  i_shadowMatrix,
    uniform float4    i_shadowColor,
    uniform float3    i_lightPosition,
    uniform float i_shadowtextureSizeInv
    ): COLOR 
{
  float4 result = float4(i_shadowColor.xyz, 1.0);
  float shadowCoeff = 1.;

  float3 Ln = normalize(i_lightPosition - IN.WorldPosition);
  float3 Nn = normalize( IN.WorldNormal );

  float dotProduct = dot(Ln, Nn);
  if (dotProduct > 0.f)
  {
    if (dotProduct <= PENOMBRA)
      result.a = (PENOMBRA-dotProduct)*INV_PENOMBRA;
    else
      result.a = 0.0;

    float4 texCoordLight = mul(i_shadowMatrix,float4(IN.WorldPosition, 1));
    if (texCoordLight.z > 0) 
    {
      shadowCoeff = GetSpotShadowCoeffPoisson(i_shadowTexture, texCoordLight, i_shadowtextureSizeInv, NUM_BLUR_24, INV_NUM_BLUR_24, filterBlurData24);
    }
    result.a =  max(1-shadowCoeff, result.a);
  }
  
  result.a *= i_shadowColor.a;
  
  return result;
}

float4 ShadowPS_4( vertexOutput2 IN,
    uniform sampler2D i_shadowTexture,
    uniform float4x4  i_shadowMatrix,
    uniform float4    i_shadowColor,
    uniform float3    i_lightPosition,
    uniform float i_shadowtextureSizeInv
    ): COLOR 
{
  float4 result = float4(i_shadowColor.xyz, 1.0);
  float shadowCoeff = 1.;

  float3 Ln = normalize(i_lightPosition - IN.WorldPosition);
  float3 Nn = normalize( IN.WorldNormal );

  float dotProduct = dot(Ln, Nn);
  if (dotProduct > 0.f)
  {
    if (dotProduct <= PENOMBRA)
      result.a = (PENOMBRA-dotProduct)*INV_PENOMBRA;
    else
      result.a = 0.0;

    float4 texCoordLight = mul(i_shadowMatrix,float4(IN.WorldPosition, 1));
    if (texCoordLight.z > 0) 
    {
      // Soft with poisson filter
      // ------------------------
      float k = 2.5;
      for(int i=0; i<NUM_BLUR_12; i++)
      {
        float2 coord = k * filterBlurData12[i];
        shadowCoeff += offset_lookupATI(i_shadowTexture, texCoordLight, coord, i_shadowtextureSizeInv);
      }
      shadowCoeff *= INV_NUM_BLUR_12;
    }
    result.a =  max(1-shadowCoeff, result.a);
  }
  
  result.a *= i_shadowColor.a;
  
  return result;
}

////////////////////////////////////////////////////////////////////
/// TECHNIQUES /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
technique Shadow_NV40
{
  pass p0 
  {
    LightingEnable = false;
    BlendEnable = true;
    BlendFunc = { One, Zero };
    DepthTestEnable = true;
    DepthFunc = LEqual;
    DepthMask = true;        
    VertexProgram = compile vp40 ShadowVS( wvp, world, worldIT, worldView);
    FragmentProgram = compile fp40 ShadowPS_1( shadowTexture, shadowMatrix, shadowColor, lightPosition,  textureSizeInv);
  }
}

technique Shadow_GLSL
{
  pass p0 
  {
    LightingEnable = false;
    BlendEnable = true;
    BlendFunc = { One, Zero };
    DepthTestEnable = true;
    DepthFunc = LEqual;
    DepthMask = true;        
    VertexProgram = compile glslv ShadowVS_2( wvp, world, worldIT, worldView, worldViewIT);
    FragmentProgram = compile glslf ShadowPS_2( shadowTexture, shadowMatrix, shadowColor, lightPosition,  textureSizeInv);
  }
}

technique Shadow_NV30
{
  pass p0 
  {
    LightingEnable = false;
    BlendEnable = true;
    BlendFunc = { One, Zero };
    DepthTestEnable = true;
    DepthFunc = LEqual;
    DepthMask = true;        
    VertexProgram = compile vp30 ShadowVS_2( wvp, world, worldIT, worldView, worldViewIT);
    FragmentProgram = compile fp30 ShadowPS_3( shadowTexture, shadowMatrix, shadowColor, lightPosition, textureSizeInv);
  }
}

technique Shadow_arb
{
  pass p0 
  {
    LightingEnable = false;
    BlendEnable = true;
    BlendFunc = { One, Zero };
    DepthTestEnable = true;
    DepthFunc = LEqual;
    DepthMask = true;        
    VertexProgram = compile arbvp1 ShadowVS_2( wvp, world, worldIT, worldView, worldViewIT);
    FragmentProgram = compile arbfp1 ShadowPS_4( shadowTexture, shadowMatrix, shadowColor, lightPosition, textureSizeInv);
  }
}
