//-------------------------------------------------------------------------------------------

float g_Ratio    = 0.5;

vec3 MainDisplacePos(const vec3 iPos)
{
  vec3 pos = iPos;
    
#ifdef DISPLACEMENT_MAP
  float distance = vLength(pos.xy);
  float fading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x*cb_Ground.u_GroundRadiusRatio.y, cb_Ground.u_RadiusRatio.y*cb_Ground.u_GroundRadiusRatio.y);
    
  vec2 uv = pos.xy*cb_Ground.u_GroundScaling.x;
  uv = TransformUV(uv, cb_Ground_Physical.u_MainMatrix_UVTransfo);

  float displace = vTexture(s_DisplacementMap, uv).x;
  displace = vFma(displace, cb_Ground_Physical.u_DisplacementStrength*cb_Ground.u_GroundScaling.y, cb_Ground_Physical.u_DisplacementDelta*cb_Ground.u_GroundScaling.y);

  pos.z += displace*fading;
#endif

  return pos;
}

vec3 DisplacePos(const vec3 iPos)
{
  vec3 pos = iPos;
    
#if defined(DISPLACEMENT_MAP1) || defined (DISPLACEMENT_MAP2) || defined (DISPLACEMENT_MAP)
  
  float distance = vLength(pos.xy);
  float fading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x*cb_Ground.u_GroundRadiusRatio.y, cb_Ground.u_RadiusRatio.y*cb_Ground.u_GroundRadiusRatio.y);
  
  float totalDisplace = 0;
  float displace[2] = {0.0, 0.0};
  vec2 uv = pos.xy*cb_Ground.u_GroundScaling.x;
  
#ifdef DISPLACEMENT_MAP
  vec2 uvMain = TransformUV(uv, cb_Ground_Physical.u_MainMatrix_UVTransfo);
  totalDisplace = vTexture(s_DisplacementMap, uvMain).x; 
  totalDisplace = vFma(totalDisplace, cb_Ground_Physical.u_DisplacementStrength*cb_Ground.u_GroundScaling.y, cb_Ground_Physical.u_DisplacementDelta*cb_Ground.u_GroundScaling.y);
#endif

#ifdef DISPLACEMENT_MAP1
  vec2 uv1 = TransformUV(uv, cb_Ground_Physical.u_Matrix1_UVTransfo);
  displace[0] = vTexture(s_DisplacementMap1, uv1).x;
  displace[0] = vFma(displace[0], cb_Ground_Physical.u_DisplacementStrength1*cb_Ground.u_GroundScaling.y, cb_Ground_Physical.u_DisplacementDelta1*cb_Ground.u_GroundScaling.y);
#endif

#ifdef DISPLACEMENT_MAP2
  vec2 uv2 = TransformUV(uv, cb_Ground_Physical.u_Matrix2_UVTransfo);
  displace[1] = vTexture(s_DisplacementMap2, uv2).x;
  displace[1] = vFma(displace[1], cb_Ground_Physical.u_DisplacementStrength2*cb_Ground.u_GroundScaling.y, cb_Ground_Physical.u_DisplacementDelta2*cb_Ground.u_GroundScaling.y);
#endif
  
#if defined(DISPLACEMENT_MAP1) || defined(DISPLACEMENT_MAP2)
  totalDisplace += vMix(displace[0], displace[1], g_Ratio);
#endif

  pos.z += totalDisplace*fading;
#endif

  return pos;
}

void ComputeCommonValues()
{
  vec2 uv = vGetPosition().xy*cb_Ground.u_GroundScaling.x;
  uv = TransformUV(uv, cb_Ground_Physical.u_MainMatrix_UVTransfo);
  g_Ratio     = vTexture(s_MaterialMap, uv).x;

  g_LocalPos  = vec4(DisplacePos(vGetPosition()), 1.0);
}

void ProcessVertexCustom()
{
  //-----------------------
  // Shadow  
#ifdef GROUND_SHADOW
  ComputeGroundShadowTexCoord();
#endif


  //-----------------------
  // N,T,B
  
  vGroundWorldNormal    = vec3(0,0,1.0);
  vGroundWorldTangent   = vec3(1.0, 0.0, 0.0);
  vGroundWorldBiNormal  = vec3(0.0, 1.0, 0.0);

#ifdef DISPLACEMENT_MAP
  float delta = cb_Ground_Physical.u_NumTesselation.y*0.5*cb_Ground.u_GroundScaling.y;

  // NB: le delta*0.01 est juste la car on a des artefact qui ressemblent a du "ZFight" 
  // Aucune idee de pourquoi cela corrige le probleme
  vec3 posT   = MainDisplacePos(vGetPosition()+vec3( delta,delta*0.01,0));
  vec3 posT2  = MainDisplacePos(vGetPosition()+vec3(-delta,delta*0.01,0));
  vGroundWorldTangent = (posT-posT2);

  vec3 posB   = MainDisplacePos(vGetPosition()+vec3(0, delta,0));
  vec3 posB2  = MainDisplacePos(vGetPosition()+vec3(0,-delta,0));
  vGroundWorldBiNormal = (posB-posB2);

  vGroundWorldNormal = vCross(vGroundWorldTangent, vGroundWorldBiNormal);
 
#endif

  vGroundWorldNormal    = (vGetWorldMatrix()*vec4(vGroundWorldNormal, 0.0)).xyz;

#if defined(NORMAL_MAP1) || defined (NORMAL_MAP2)
  vGroundWorldTangent   = (vGetWorldMatrix()*vec4(vGroundWorldTangent, 0.0)).xyz;
  vGroundWorldBiNormal  = (vGetWorldMatrix()*vec4(vGroundWorldBiNormal, 0.0)).xyz;
#endif
  
  //-----------------------
  // Mirroring

#ifdef GROUND_MIRRORING
  // Calcul des perturbations de la map de mirroring
    vMirrorTexCoord = vec2(0);

  // deplacement en fonction de la hauteur
#if defined(DISPLACEMENT_MAP1) || defined(DISPLACEMENT_MAP2)
  vec4 pos1 = vGetViewProjMatrix() * vGetWorldMatrix() * vec4(vGetPosition(),1);
  pos1.xyz /= pos1.w;
  vec4 pos2 = vGetViewProjMatrix() * vGetWorldMatrix() * g_LocalPos;
  pos2.xyz /= pos2.w;
  
  vMirrorTexCoord = pos1.xy - pos2.xy;
#endif
  
#endif
  
  //-----------------------
  // UV

  vGroundUV = vGetPosition().xy;
}


