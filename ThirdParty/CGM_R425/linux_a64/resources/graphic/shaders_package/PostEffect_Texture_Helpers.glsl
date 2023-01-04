//----------------------------------------------------------------------------------------
// Gestion des textures (MSAA ou non)


vec4 GetEffectTexture(sampler2D iTexture, const vec2 iCoord, int iSampleID)
{
  return vTexture(iTexture, iCoord);
}

vec4 GetEffectTexture(sampler2D iTexture, const vec2 iCoord)
{
  return vTexture(iTexture, iCoord);
}

#if !defined(GLES2Platform) && (GLSLVersion >= 400)

//----------------------------------------------------------------------------------------
// Passage du monde coordonees de texture au monde pixel
// C'est necessaire dans le cas du texelFetch qui ne gere pas de sampler
// on fait donc l'equivalent par shader pour gerer les depassement de taille
// On fait du ClampToEdge au final

ivec2 TranslateToTexelCoord(const vec2 iCoord, const ivec2 iTextureSize)
{
  ivec2 coord = ivec2(int(iCoord.x * float(iTextureSize.x)), int(iCoord.y * float(iTextureSize.y)));
  coord = vClamp(coord, ivec2(0, 0), iTextureSize - ivec2(1));
  return coord;
}

ivec2 TranslateToTexelCoord(const vec2 iCoord, const ivec2 iTextureSize, const vec2 iPixelOffset)
{
  ivec2 coord = ivec2(int(iCoord.x*float(iTextureSize.x) + iPixelOffset.x), int(iCoord.y*float(iTextureSize.y) + iPixelOffset.y));
  coord = vClamp(coord, ivec2(0, 0), iTextureSize - ivec2(1));
  return coord;
}

// sampler2DMS, sampler2DArray, sampler2DArrayMS ne sont pas supporte par iOS

// Dans le cas MSSA, vTexelFetch ne tient pas compte du sampler
// on doit donc resoudre le wraping nous-meme
// cela explique la presence du vClamp

#if !defined(GLES3Platform) && (GLSLVersion >= 400)

vec4 GetEffectTexture(sampler2DMS iTexture, const vec2 iCoord, int iSampleID)
{
  ivec2 coord = TranslateToTexelCoord(iCoord, vTextureSize(iTexture).xy);
  return vTexelFetch(iTexture, coord, iSampleID);
}

vec4 GetEffectTexture(sampler2DMS iTexture, const vec2 iCoord)
{
  int sampleID = 0;
#ifdef FragmentStage
  sampleID = gl_SampleID;
#endif
  return GetEffectTexture(iTexture, iCoord, sampleID);
}

vec4 GetEffectTexture(sampler2DMSArray iTexture, const vec3 iCoord, int iSampleID)
{
  ivec2 coord = TranslateToTexelCoord(iCoord.xy, vTextureSize(iTexture).xy);
  return vTexelFetch(iTexture, ivec3(coord, iCoord.z), iSampleID);
}

vec4 GetEffectTexture(sampler2DMSArray iTexture, const vec3 iCoord)
{
  int sampleID = 0;
#ifdef FragmentStage
  sampleID = gl_SampleID;
#endif
  return GetEffectTexture(iTexture, iCoord, sampleID);
}

#endif // !GLES3Platform && (GLSLVersion >= 400)

// Attention pour les array la dernier coordonee est le numero de layer
vec4 GetEffectTexture(sampler2DArray iTexture, const vec3 iCoord, int iSampleID)
{
  return vTexture(iTexture, iCoord);
}

vec4 GetEffectTexture(sampler2DArray iTexture, const vec3 iCoord)
{
  return vTexture(iTexture, iCoord);
}

#endif // !GLES2Platform && (GLSLVersion >= 400)

#ifndef POSTEFFECT_NO_MAINCB
// les methodes suivantes ne sont accessible que le constant buffer cbPostEffect_Main_Auto a ete inclu
// pour avoir acces a : cb_PostEffectAuto

//----------------------------------------------------------------------------------------
// Gestion des textures avec offset en pixel
//

vec4 GetEffectTexture(sampler2D iTexture, const vec2 iCoord, vec2 iPixelOffset)
{
#if !defined(GLES2Platform) && (GLSLVersion >= 400)
  ivec2 coord = TranslateToTexelCoord(iCoord.xy, vTextureSize(iTexture, 0).xy, iPixelOffset);
  return vTexelFetch(iTexture, coord, 0);
#else
  // openGLES ne supporte ni textureSize ni texelFetch
  vec2 coord = iCoord + iPixelOffset * cb_PostEffectAuto.u_PixelSize;
  return vTexture(iTexture, coord);
#endif
}

#if !defined(GLES2Platform) && (GLSLVersion >= 400)

#if !defined(GLES3Platform)  && (GLSLVersion >= 400)
// sampler2DMS n'est pas supporte par iOS

vec4 GetEffectTexture(sampler2DMS iTexture, const vec2 iCoord, vec2 iPixelOffset)
{
  ivec2 coord = TranslateToTexelCoord(iCoord.xy, vTextureSize(iTexture).xy, iPixelOffset);
   
#ifdef FragmentStage
  return vTexelFetch(iTexture, coord, gl_SampleID);
#else
  return vTexelFetch(iTexture, coord, 0);
#endif
}


vec4 GetEffectTexture(sampler2DMSArray iTexture, const vec3 iCoord, vec2 iPixelOffset)
{
  ivec2 coord = TranslateToTexelCoord(iCoord.xy, vTextureSize(iTexture).xy, iPixelOffset);
  
#ifdef FragmentStage
  return vTexelFetch(iTexture, ivec3(coord, iCoord.z), gl_SampleID);
#else
  return vTexelFetch(iTexture, ivec3(coord, iCoord.z), 0);
#endif
}

#endif // !GLES3Platform && (GLSLVersion >= 400)

vec4 GetEffectTexture(sampler2DArray iTexture, const vec3 iCoord, vec2 iPixelOffset)
{
  ivec2 coord = TranslateToTexelCoord(iCoord.xy, vTextureSize(iTexture, 0).xy, iPixelOffset);
  return vTexelFetch(iTexture, ivec3(coord, iCoord.z), 0);
}

#endif // !GLES2Platform && (GLSLVersion >= 400)

#endif // POSTEFFECT_NO_MAINCB
