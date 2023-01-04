vec4 diffuseSample;

void basicComputeCommonValues()
{
#ifdef UseTexture
  #ifdef DecalLighting //Fetch tex coords from the decal mapping
    vec2 texCoords = vGetUvs().xy;
  #else
    vec2 texCoords = vTexCoord.xy;
  #endif

  #if defined(VolMaterial_TextureProjection) && (VolMaterial_TextureProjection==3)
    vec3 orientedViewNormal = vGetViewNormal();
    vec3 dir = vReflect(vTexCoord, orientedViewNormal);
    texCoords = ComputeSphereMapCoord(dir).st;           
  #endif
    vec4 fullTexel;

  #if (UseTexture == 2)
    diffuseSample =  vTexture(V_GET_TEXTURE_2D(diffuseTexture), vec2(texCoords.s,1.0)); 
  #else
    diffuseSample =  vTexture(V_GET_TEXTURE_2D(diffuseTexture), texCoords.st);   
  #endif
#endif
}

/*
** Multiple Render Targets support. The default is to output the lit or (unlit if lighting disabled)
** fragment color (the 'fragColor' input parameter) to the first render target, but additionnal 
** value may be added here
*/
#define CATModulateTexture 0
#define CATBlendTexture 1
#define CATDecalTexture 2
#define CATReplaceTexture 3
#define CATDecalTextureWithoutAlpha 4

void basicProcessFinalColor(inout vec4 finalColor)
{
#if defined(HLSecondPolite) || defined(HLFirstPolite)
#if defined Lighting
  vec3 norm = ComputeViewNormal();
  float d = vDot(norm, vec3(0.0,0.0,1.0));

  #ifdef GlobalGASColor
    finalColor.xyz = vGetGlobalGASColor().rgb*(1/PI) + vGetGlobalGASColor().rgb * d;
  #else
    finalColor.xyz = cb_cbVolMaterial.u_AmbientColor.rgb*(1/PI) +cb_cbVolMaterial.u_DiffuseColor.rgb*d;
  #endif
#else
  #ifdef GlobalGASColor
    finalColor.xyz = vGetGlobalGASColor().rgb;
  #else
    finalColor.xyz = cb_cbVolMaterial.u_AmbientColor.rgb;
  #endif

#endif
#elif defined(VolMaterial_TextureFunction)
#if VolMaterial_TextureFunction == CATReplaceTexture
  finalColor.xyz = diffuseSample.xyz;
#endif
#endif 
}
 
 

vec3 basicComputeAlbedo()
{
#ifdef VertexColor
  vec3 albedo = vColor.xyz;
#else
  #ifdef DecalLighting
    vec3 albedo = vec3(1.0);
  #else
    #ifdef GlobalGASColor
      vec3 albedo = vGetGlobalGASColor().xyz;
    #else
      vec3 albedo = cb_cbVolMaterial.u_DiffuseColor.rgb;
    #endif
  #endif
#endif

#if defined(UseTexture) && defined(VolMaterial_TextureFunction)
#if  VolMaterial_TextureFunction == CATModulateTexture
  {
    albedo *= diffuseSample.xyz;
  }
#elif VolMaterial_TextureFunction == CATBlendTexture
  {
    albedo *= 1. - diffuseSample.xyz;
    albedo += diffuseSample.xyz;
  }
#elif VolMaterial_TextureFunction == CATDecalTexture //GL_DECAL 
  {     
    albedo *= 1. - diffuseSample.w;
    albedo += diffuseSample.xyz * diffuseSample.w;    
  }
#elif VolMaterial_TextureFunction == CATDecalTextureWithoutAlpha
  {
    albedo = diffuseSample.xyz;
  }
#elif VolMaterial_TextureFunction != CATReplaceTexture
// WARNING: For "VolMaterial_TextureFunction == CATReplaceTexture" case, see ProcessFinalColor
  {
    albedo *= diffuseSample.xyz;
  }
#endif
#endif

  return albedo;
}


// for transparency (1 is completely opaque material)
float basicComputeOpacity()
{
#ifdef VertexColor
  return vColor.w;
#else
 
  #ifdef GlobalGASColor
    float val = vGetGlobalGASColor().w;
  #else
    float val = cb_cbVolMaterial.u_AmbientColor.w;
  #endif

  #if defined UseTexture && defined VolMaterial_TextureFunction
    #if VolMaterial_TextureFunction == 1
    {
      val *= diffuseSample.w;
    }
    #elif VolMaterial_TextureFunction == 3
    {
      val = diffuseSample.w;
    }
    #elif VolMaterial_TextureFunction != 2
    {
      val *= diffuseSample.w;
    }
    #endif
  #endif

  return val;
#endif
}


vec3 basicComputeSpecularReflectance()
{
#if defined Lighting
  return vec3(0.04) * cb_cbVolMaterial.u_SpecularColor.rgb;
#else
  return vec3(0.0);
#endif
}


vec3 basicComputeViewNormal()
{
#ifdef NoNormal
   vec3 hardCodedNormal = vNormalize(vec3(1,1,1));
   return hardCodedNormal;
#else
  // can use tangent space here to do bump mapping
  return vNormalize(vGetViewNormal());
#endif
}


int ResolveAlphaTest(float value);

bool basicComputeDiscard()
{
  // additionnal clip instruction go here (example : alpha test)
#if defined(Dialog) || defined(VertexColor)
  return false;
#endif  

#ifdef AlphaTest
  // additionnal discard instruction go here (example : alpha test)
  if(cb_cbVolMaterial.u_AlphaFunc != 0) // alpha test enabled
  {
    int alphaTest = ResolveAlphaTest(ComputeOpacity());

    if(alphaTest == 0)
      return true;
  }
#endif // AlphaTest

  return false;
}


#ifdef CUSTOM_COVERAGE
void PerformCustomCoverage()
{
}
#endif

//Keep the int value this way, bitfield used
//bit 0 LOWER,bit 1 : EQUAL, bit 2 : GREATER 

const int GL_NEVER = 0;    //000
const int GL_LESS = 1;     //001
const int GL_EQUAL = 2;    //010
const int GL_LEQUAL = 3;   //011
const int GL_GREATER = 4;  //100
const int GL_NOTEQUAL = 5; //101
const int GL_GEQUAL = 6;   //110
const int GL_ALWAYS = 7;   //111


//Custom func
#ifndef GLES2Platform
int ResolveAlphaTest(float value)
{
  int alphaDifference = ((value-cb_cbVolMaterial.u_AlphaLimit)>=0.0) ? 1 : -1;
  return ((1<<(1+alphaDifference)) & cb_cbVolMaterial.u_AlphaFunc); 
}
#else
int ResolveAlphaTest(float value)
{  
  int result = 0;

  if(cb_cbVolMaterial.u_AlphaFunc ==  GL_NEVER)
  {
    result = 0;
  }
  else
  {
    if(cb_cbVolMaterial.u_AlphaFunc == GL_LESS)
    {
      if(value < cb_cbVolMaterial.u_AlphaLimit)
        result = 1;
      else
        result = 0;
    }
    else
    {
      if(cb_cbVolMaterial.u_AlphaFunc == GL_EQUAL)
      {
        if(value == cb_cbVolMaterial.u_AlphaLimit)
          result = 1;
        else
          result = 0;
      }
      else
      {
        if(cb_cbVolMaterial.u_AlphaFunc == GL_LEQUAL)
        {
          if(value <= cb_cbVolMaterial.u_AlphaLimit)
            result = 1;
          else
            result = 0;
        }
        else
        {
          if(cb_cbVolMaterial.u_AlphaFunc == GL_GREATER)
          {
            if(value > cb_cbVolMaterial.u_AlphaLimit)
              result = 1;
            else
              result = 0;
          }
          else
          {
            if(cb_cbVolMaterial.u_AlphaFunc == GL_NOTEQUAL)
            {
              if(value != cb_cbVolMaterial.u_AlphaLimit)
                result = 1;
              else
                result = 0;
            }
            else
            {
              if(cb_cbVolMaterial.u_AlphaFunc == GL_GEQUAL)
              {
                if(value >= cb_cbVolMaterial.u_AlphaLimit)
                  result = 1;
                else
                  result = 0;
              }
              else
              {
                if(cb_cbVolMaterial.u_AlphaFunc == GL_ALWAYS)
                  result = 1;
                else
                  result = 0;  
              }
            }
          }
        }
      }
    }
  }

  return result;
}
#endif

#ifndef PDSFX1_FS_CommonValues_BaseShaded
void ComputeCommonValues()
{
  basicComputeCommonValues();
}
#endif
#ifndef PDSFX1_FS_FinalColor_BaseShaded
void ProcessFinalColor(inout vec4 finalColor)
{
  basicProcessFinalColor(finalColor);
}
#endif
#ifndef PDSFX1_FS_Albedo_BaseShaded
vec3 ComputeAlbedo()
{
  return basicComputeAlbedo();
}
#endif
#ifndef PDSFX1_FS_Opacity_BaseShaded
float ComputeOpacity()
{
  return basicComputeOpacity();
}
#endif
#ifndef PDSFX1_FS_F0_BaseShaded
vec3 ComputeSpecularReflectance()
{
  return basicComputeSpecularReflectance();
}
#endif
#ifndef PDSFX1_FS_Normal_BaseShaded
vec3 ComputeViewNormal()
{
  return basicComputeViewNormal();
}
#endif
#ifndef PDSFX1_FS_Discard_BaseShaded
bool ComputeDiscard()
{
  return basicComputeDiscard();
}
#endif
