#ifndef GeometryStage


#if (defined(VertexStage) && defined(PDSFX1_PVL_AdvancedBRDFUser_PhysicalMaterial)) || (defined(FragmentStage) && defined(PDSFX1_FS_AdvancedBRDFUser_PhysicalMaterial))
void pmProcessBRDFParameters(inout BRDFParameters oParameters)
#else
void ProcessBRDFParameters(inout BRDFParameters oParameters)
#endif
{ 
  oParameters.transparency = vClamp(_transparency, 0.0, 1.0);

#ifdef Flakes
  oParameters.metallicFlakesRoughness =  1.0 - _metallicFlakesGlossiness;
  oParameters.metallicFlakesF0 = _metallicFlakesFresnel;
  oParameters.metalRoughness = 1 - _metalGlossiness;
  oParameters.metalF0 = _metalFresnel;
  //
  oParameters.pearlFlakesRoughness =  1.0 - _pearlFlakesGlossiness;
  oParameters.pearlFlakesF0 = _pearlFlakesFresnel;
  oParameters.pearlRoughness = 1 - _pearlGlossiness;
  oParameters.pearlF0 = _pearlFresnel;
#endif // Flakes

  oParameters.roughness = 1.0-_glossiness;

#ifdef Fabrics
  oParameters.f0 = SpecularF0 * _fresnelCoefficient.xyz;
  oParameters.f90 = SpecularF90 * _fresnelCoefficient.xyz;
#else
  oParameters.f0 = _fresnelCoefficient.xyz;  
  oParameters.f90 = vec3(1.0);
#endif 

#ifdef Coating
  oParameters.coatingRoughness = 1.0 - _coatingGlossiness;
  oParameters.coatingF0 = _coatingFresnelCoefficient.xyz;
#endif // Coating

#if defined(AnisotropicDistribution)
  oParameters.anisotropy = _anisotropy;
  oParameters.anisotropyAngle = _anisotropyAngle;
#endif // AnisotropicDistribution
}  



/****************************************** Compute Common Values ***************************************************************/
void TransformUv();
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ);
void PMComputeCommonValuesFrag();
vec3 _worldNormal;

/******************************************* PHYSICAL MATERIAL GRAMMAR OPTION ***************************************************/
#if defined GPUMappingOperator || defined DecalLighting

#if defined(PMUniformAsTexture) || defined(AnisotropicDistribution) || defined(normalMapEnabled) || defined(heightMapEnabled) || defined(Flakes) || defined(coatingNormalMapEnabled) || defined(occlusionMapEnabled)
#define PMComputeTexCoords 
#endif // defined(PMUniformAsTexture) || defined(AnisotropicDistribution) || defined(normalMapEnabled) || defined(heightMapEnabled) || defined(Flakes) || defined(coatingNormalMapEnabled)

#if defined(AnisotropicDistribution) || defined(normalMapEnabled) || defined(Flakes) || defined(coatingNormalMapEnabled)
#define PMComputeTB //Anisotropic, Bump
#endif // defined(AnisotropicDistribution) || defined(normalMapEnabled) || defined(Flakes) || defined(coatingNormalMapEnabled)

#endif // GPUMappingOperator

void pmComputeCommonValues()
{
#if defined(PMComputeTexCoords) && (defined(FragmentStage) || defined(RayHitStage))

  #ifndef DecalLighting //decals are done earlier in ComputeDecals()
    vec3 localPosition = (PMat.world2Object * vec4(v_ObjectSpacePosition, 1.0)).xyz;
    vec3 localNormal = normalize((PMat.world2Object * vec4(normalize(v_ObjectSpaceNormal), 0.0)).xyz);
    mat3 mat = transpose(mat3(PMat.world2Object));
    vec3 x = mat * vec3(1.0, 0.0, 0.0);
    vec3 y = mat * vec3(0.0, 1.0, 0.0);
    vec3 z = mat * vec3(0.0, 0.0, 1.0);
    ComputeMapping(localPosition, localNormal, x, y, z);  
  #endif

  TransformUv();
#endif // defined PMComputeTexCoords && defined FragmentStage
   
  {//ComonValuesForLighting
#ifdef LightingStage
    const float kThreshold0 = 0.+ kEpsilon;
    const float kThreshold1 = 1.- kEpsilon;
    _glossiness = pmGetGlossiness();
	#ifdef Coating
	_coatingGlossiness = pmGetCoatingGlossiness();
	#endif
#ifdef AnisotropicDistribution
    _anisotropy = pmGetAnisotropy();
    _anisotropyAngle = pmGetAnisotropyAngle();
#endif // AnisotropicDistribution    
    _bumpScale = pmGetBumpScale();  

    {/*MAD MODIFIERS*/
#ifdef glossinessMadModified
    _glossiness = vFma(PMadMat.m_glossiness, _glossiness, PMadMat.a_glossiness);
#endif // glossinessMadModified
#ifdef AnisotropicDistribution
#ifdef anisotropyMadModified 
      _anisotropy = vFma(PMadMat.m_anisotropy, _anisotropy, PMadMat.a_anisotropy);
#endif // anisotropyMadModified
#ifdef anisotropyAngleMadModified
      _anisotropyAngle = vFma(PMadMat.m_anisotropyAngle, _anisotropyAngle, PMadMat.a_anisotropyAngle);
#endif // anisotropyAngleMadModified
#endif // AnisotropicDistribution
#ifdef bumpScaleMadModified
      _bumpScale = vFma(PMadMat.m_bumpScale, _bumpScale, PMadMat.a_bumpScale);
#endif //bumpScaleMadModified
    }
    {//clamping parameters
      _glossiness = vClamp(_glossiness, 0.0, kThreshold1); 
#ifdef AnisotropicDistribution
      _anisotropy = vClamp(_anisotropy, 0.0, kThreshold1);
#endif //AnisotropicDistribution
    }  
#endif // LightingStage
  }
  {
#if defined(LightingStage) || defined(FragmentStage)
    _fresnelCoefficient = pmGetFresnelCoefficient();
  #if defined(UseVelvet)
    _fresnelCoefficient.xyz = vec3(1.0);
  #endif
  #if defined(fresnelCoefficientMadModified) && !defined(Fabrics)
    _fresnelCoefficient.xyz = vFma(PMadMat.m_fresnelCoefficient.xyz, _fresnelCoefficient.xyz, PMadMat.a_fresnelCoefficient.xyz).xyz;
	#endif //fresnelCoefficientMadModified
#ifdef Coating
	_coatingFresnelCoefficient = pmGetCoatingFresnelCoefficient();
	#ifdef coatingFresnelCoefficientMadModified
		_coatingFresnelCoefficient.xyz = vFma(PMadMat.m_coatingFresnelCoefficient.xyz, _coatingFresnelCoefficient.xyz, PMadMat.a_coatingFresnelCoefficient.xyz).xyz;
	#endif //coatingFresnelCoefficientMadModified
#endif //Coating
#endif //defined(LightingStage) || defined(FragmentStage)
  }

#if defined(FragmentStage) || defined(RayHitStage)
  PMComputeCommonValuesFrag();  
#endif
}


#if !(defined(VertexStage) && defined(PDSFX1_VS_CommonValues_PhysicalMaterial)) || !(defined(FragmentStage) && defined(PDSFX1_FS_CommonValues_PhysicalMaterial))
void ComputeCommonValues()
{
  pmComputeCommonValues();
}
#endif
#endif
