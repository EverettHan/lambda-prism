//-------------------------------------------------------------------------------------------

vec3 DisplacePos(const vec3 iPos)
{
  vec3 pos = iPos;

#ifdef DISPLACEMENT_MAP
  float distance = vLength(pos.xy);
  float fading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x*cb_Ground.u_GroundRadiusRatio.y, cb_Ground.u_RadiusRatio.y*cb_Ground.u_GroundRadiusRatio.y);
  
  vec2 uv = pos.xy*cb_Ground.u_GroundScaling.x;
  uv = TransformUV(uv, cb_Ground_Physical.u_Matrix_UVTransfo);
  
  float displace = vFma(vTexture(s_DisplacementMap, uv).x, cb_Ground_Physical.u_DisplacementStrength*cb_Ground.u_GroundScaling.y, cb_Ground_Physical.u_DisplacementDelta*cb_Ground.u_GroundScaling.y);
  
  pos.z += displace*fading;
#endif

  return pos;
}

void ComputeCommonValues()
{
#ifdef TessEvaluationStage
  g_VertexPos = _GetVertexPosition();
#endif


  g_LocalPos = vec4(DisplacePos(vGetPosition()), 1.0);
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
  
#if defined(DISPLACEMENT_MAP) && !defined(NORMAL_MAP)
  float delta = cb_Ground_Physical.u_NumTesselation.y*0.5*cb_Ground.u_GroundScaling.y;

  vec3 posT   = DisplacePos(vGetPosition()+vec3( delta,delta*0.01,0));
  vec3 posT2  = DisplacePos(vGetPosition()+vec3(-delta,delta*0.01,0));
  vec3 posB   = DisplacePos(vGetPosition()+vec3(0, delta,0));
  vec3 posB2  = DisplacePos(vGetPosition()+vec3(0,-delta,0));

  vGroundWorldNormal = vCross((posT-posT2), (posB-posB2));
#else
  vGroundWorldNormal = vec3(0,0,1.0);
#endif

  vGroundWorldNormal = (vGetWorldMatrix()*vec4(vGroundWorldNormal, 0.0)).xyz;

#ifdef NORMAL_MAP
  vGroundWorldTangent   = (vGetWorldMatrix()*vec4(1.0, 0.0, 0.0, 0.0)).xyz;
  vGroundWorldBiNormal  = (vGetWorldMatrix()*vec4(0.0, 1.0, 0.0, 0.0)).xyz;
#endif
  
  //-----------------------
  // Mirroring

#ifdef GROUND_MIRRORING
  // Calcul des perturbations de la map de mirroring
  vMirrorTexCoord = vec2(0);

  // 1. deplacement en fonction de la hauteur
#ifdef DISPLACEMENT_MAP
  vec4 pos1 = vGetProjMatrix() * vGetWorldViewMatrix() * vec4(vGetPosition(),1);
  pos1.xyz /= pos1.w;
  vec4 pos2 = vGetProjMatrix() * vGetWorldViewMatrix() * g_LocalPos;
  pos2.xyz /= pos2.w;
  
  vMirrorTexCoord = pos1.xy - pos2.xy;
#endif
  
  // 2. modification en fonction de la normal
#if defined(DISPLACEMENT_MAP) && !defined(NORMAL_MAP)
  vMirrorTexCoord.xy += ComputeMirrorDeviationFromNormal(vGroundWorldNormal); 
#endif

#endif
  
  //-----------------------
  // UV

  vGroundUV = vGetPosition().xy;
}



