////////////////////////////////
// Client Code Basic Skeleton //
////////////////////////////////

void PMComputeCommonValuesFrag()
{
  _transparency = pmGetTransparency();
  _opacity = pmGetOpacity();    
  _diffuse = pmGetDiffuse();
  _emissive = pmGetEmissive();

#ifdef UseEdgeColor
  _edgeColorBias = pmGetEdgeColorBias();
  _edgeColor = pmGetEdgeColor();
#endif // UseEdgeColor

#ifdef transparencyMadModified
  _transparency = vFma(PMadMat.m_transparency, _transparency, PMadMat.a_transparency);
#endif // transparencyMadModified

#ifdef opacityMadModified
  _opacity = vFma(PMadMat.m_opacity, _opacity, PMadMat.a_opacity);
#endif // opacityMadModified

#ifdef diffuseMadModified
  _diffuse.xyz = vFma(PMadMat.m_diffuse, _diffuse.xyz, PMadMat.a_diffuse);
#endif // diffuseMadModified

#ifdef emissiveMadModified
      _emissive.xyz = vFma(PMadMat.m_emissive, _emissive.xyz, PMadMat.a_emissive);
#endif // emissiveMadModified

#ifdef UseEdgeColor

#ifdef edgeColorMadModified
  _edgeColor.xyz = vFma(PMadMat.m_edgeColor.xyz, _edgeColor.xyz, PMadMat.a_edgeColor.xyz).xyz;
	#endif // edgeColorMadModified

#ifdef edgeColorBiasMadModified
  _edgeColorBias = vFma(PMadMat.m_edgeColorBias, _edgeColorBias, PMadMat.a_edgeColorBias);
	#endif // edgeColorBiasMadModified

#endif // UseEdgeColor

#if defined(Coating) && defined(coatingNormalMapEnabled) 
	  _coatingNormal = pmGetCoatingNormalMap().xyz;
#endif // defined(Coating) && defined(coatingNormalMapEnabled) 

#ifdef heightMapEnabled
  _heightMap = pmGetHeightMap();
#endif // heightMapEnabled

#ifdef bumpMapEnabled
  _bumpMap = pmGetBumpMap();
#endif // bumpMapEnabled

#ifdef occlusionMapEnabled
  _occlusionMap = pmGetOcclusionMap().x;
#endif

#ifdef LightingStage
   
  _worldNormal = (vGetViewInvMatrix() * vec4(vGetViewNormal(), 0.0)).xyz;  

#ifdef Coating //Coating takes normal before NormalMap
  _coatingNormal = _worldNormal;

	#ifdef coatingNormalMapEnabled  
    vec3 coatingnormal = vFma(_coatingNormal.xyz,vec3(2.0),vec3(-1.0));
    coatingnormal.xy *= PMat.coatingBump;
    #ifdef DecalLighting
      _coatingNormal = coatingnormal;
    #else
      _coatingNormal = vNormalize(coatingnormal.x*vGetTangent() + coatingnormal.y*vGetBinormal() + coatingnormal.z*_worldNormal);  
    #endif
  #endif // coatingNormalMapEnabled
#endif // Coating

#ifdef normalMapEnabled  
  _normalMap = pmGetNormalMap();
  vec3 normal = vFma(_normalMap.xyz, vec3(2.0),vec3(-1.0));
  normal.xy *= _bumpScale;

  #ifdef DecalLighting
    _worldNormal = normal;
  #else
    _worldNormal = vNormalize(normal.x*vGetTangent() + normal.y*vGetBinormal()*PMat.normalMapBinormalScale + normal.z*_worldNormal);  
  #endif
#endif // normalMapEnabled

#ifdef bumpMapEnabled
    vec2 bump = vFma(bumpMap.xy, vec2(2.0), vec2(-1.0));
  _worldNormal += bump.x*vGetTangent() + bump.y*vGetBinormal();
	_worldNormal = vNormalize(_worldNormal);
#endif // bumpMapEnabled

#ifdef Flakes
		doFlakes();
#endif // Flakes

#ifdef ProceduralCoating
		doOrangePeel();
#endif
#endif // LightingStage
} 

vec3 pmComputeAlbedo()
{
  vec3 albedo = vec3(0.0);
#ifdef UseEdgeColor
  {
    vec3 V = vNormalize((vGetViewInvMatrix() * vec4(vGetViewPosition(), 0.0)).xyz);
    float NdotV = vDot(_worldNormal, V);      
    float colorVariationCursorEdge = vPow(vAbs(NdotV), _edgeColorBias); // Normal could lead to 0.0 > dot
    albedo = vMix(_diffuse.rgb, vMix(_edgeColor.rgb, _diffuse.rgb, colorVariationCursorEdge), _edgeColorBias);
  }
#else
  {
    albedo = _diffuse.xyz; 
  }
#endif

#ifdef occlusionMapEnabled
  albedo *= _occlusionMap;
#endif

  return albedo;
}

// customize these functions to change the material look
vec3 pmComputeEmissive()
{  
  return _emissive.xyz;
}

// for transparency (1 is completely opaque material)
float pmComputeOpacity()
{
  float opacitySource;

#ifdef UseAlphaDiffuseChannel
  opacitySource = _diffuse.a * PMat.DiffuseAlphaMultiplier;
#else
  opacitySource = _opacity;
#endif // defined(UseAlphaDiffuseChannel)
  return opacitySource;
}

vec3 pmComputeViewNormal()
{   
#ifdef DecalLighting
  return _worldNormal;
#else
  return (vGetViewInvTranspMatrix() * vec4(_worldNormal, 0.0)).xyz;
#endif
}

#ifdef Coating
  vec3 ComputeWorldCoatingN()
  {
     return _coatingNormal;
  }
#endif

#ifdef Flakes
vec3 ComputeWorldPearlFlakesN()
{
   return _pearlFlakesNormal;
}
vec3 ComputeWorldMetalFlakesN()
{
   return _metallicFlakesNormal;
}
#endif

void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ);

bool pmComputeDiscard()
{
  return (ComputeOpacity() <= 0.001);
}

#ifndef PDSFX1_FS_Albedo_PhysicalMaterial
vec3 ComputeAlbedo()
{
  return pmComputeAlbedo();
}
#endif

#ifndef PDSFX1_FS_Emissive_PhysicalMaterial
vec3 ComputeEmissive()
{
  return pmComputeEmissive();
}
#endif

#ifndef PDSFX1_FS_Opacity_PhysicalMaterial
float ComputeOpacity()
{
  return pmComputeOpacity();
}
#endif

#ifndef PDSFX1_FS_Normal_PhysicalMaterial
vec3 ComputeViewNormal()
{
  return pmComputeViewNormal();
}
#endif

#ifndef PDSFX1_FS_Discard_PhysicalMaterial
bool ComputeDiscard()
{
  return pmComputeDiscard();
}
#endif
