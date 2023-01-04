float g_RatioToKm                         = 1e-6 * cb_Ground_Auto.u_UnitRatio;
float g_AtmosphereRadiusGround            = cb_Ground_Auto.u_GroundHeight*g_RatioToKm;
float g_AtmosphereRadiusGroundLimit       = g_AtmosphereRadiusGround*(1.0 + 1.5e-6);
float g_AtmosphereRadiusGroundLimitSqare  = g_AtmosphereRadiusGroundLimit*g_AtmosphereRadiusGroundLimit;

vec3 ConvertViewToEarthCoord(const vec3 iPos)
{
  vec3 pos = (cb_Ground_Auto.u_GroundMatrixViewToPlanet * vec4(iPos, 1.0)).xyz;

  return pos;
}

vec3 ConvertToEarthCoord(const vec3 iPos)
{
  vec3 pos = iPos;

#ifndef EARTH_REFERENTIAL_SYSTEM
  // on se place dans le repere du sol
  pos -= (cb_Ground_Auto.u_GroundPosition);
#endif
  
  // conversion en km
  pos *= g_RatioToKm;
  
#ifndef EARTH_REFERENTIAL_SYSTEM
  // on deplace le sol dans le repere de la planete
  pos += g_AtmosphereRadiusGround*cb_Ground_Auto.u_GroundNormal;
#endif

  return pos;
}

vec3 UpdateEarthPosition(const vec3 iPos)
{
  vec3 pos = iPos;

  // Fix CK for view under 0
  if (vDot(pos, pos) < g_AtmosphereRadiusGroundLimitSqare)
  {
		pos = vNormalize(pos) * g_AtmosphereRadiusGroundLimit; 
  }

  return pos;
}

