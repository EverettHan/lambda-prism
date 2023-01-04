//-------------------------------------------------------------------------------------------

float g_Ratio    = 0.5;

vec3 DisplacePos(const vec3 iPos)
{
  vec3 pos = iPos;
    
  float distance = vLength(pos.xy);
  float fading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x*cb_Ground.u_GroundRadiusRatio.y, cb_Ground.u_RadiusRatio.y*cb_Ground.u_GroundRadiusRatio.y);
  
  float totalDisplace = 0;
  float displace[2] = float[](0.0, 0.0);

  float displacementStrength  = cb_Ground_Physical.u_DisplacementStrength*cb_Ground.u_GroundScaling.y;
  float displacementDelta     = cb_Ground_Physical.u_DisplacementDelta*cb_Ground.u_GroundScaling.y;
  
  vec2 uv = pos.xy*cb_Ground.u_GroundScaling.x;

  vec2 uv1 = TransformUV(uv, cb_Ground_Physical.u_Matrix1_UVTransfo);
  displace[0] = vTexture(s_DisplacementMap, uv1).x;
  displace[0] = vFma(displace[0], displacementStrength, displacementDelta);

  vec2 uv2 = TransformUV(uv, cb_Ground_Physical.u_Matrix2_UVTransfo);
  displace[1] = vTexture(s_DisplacementMap, uv2).x;
  displace[1] = vFma(displace[1], displacementStrength, displacementDelta);
  
  totalDisplace += vMix(displace[0], displace[1], g_Ratio);

  pos.z += totalDisplace*fading;

  return pos;
}

void ComputeCommonValues()
{

#ifdef TessEvaluationStage
  g_VertexPos = _GetVertexPosition();
#endif



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

  vGroundWorldNormal    = (vGetWorldMatrix()*vec4(vGroundWorldNormal, 0.0)).xyz;
  vGroundWorldTangent   = (vGetWorldMatrix()*vec4(vGroundWorldTangent, 0.0)).xyz;
  vGroundWorldBiNormal  = (vGetWorldMatrix()*vec4(vGroundWorldBiNormal, 0.0)).xyz;
  
  //-----------------------
  // Mirroring

#ifdef GROUND_MIRRORING
  // Calcul des perturbations de la map de mirroring
  vMirrorTexCoord = vec2(0);

  // deplacement en fonction de la hauteur
  vec4 pos1 = vGetViewProjMatrix() * vGetWorldMatrix() * vec4(vGetPosition(),1);
  pos1.xyz /= pos1.w;
  vec4 pos2 = vGetViewProjMatrix() * vGetWorldMatrix() * g_LocalPos;
  pos2.xyz /= pos2.w;
  
  vMirrorTexCoord = pos1.xy - pos2.xy;
#endif
  
  //-----------------------
  // UV

  vGroundUV = vGetPosition().xy;
}


