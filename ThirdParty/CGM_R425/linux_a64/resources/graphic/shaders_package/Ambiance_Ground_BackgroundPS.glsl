
void main()
{	
  vec4 color = vec4(cb_Ground.u_GroundBackgroundColor.xyz, 0);
  color.xyz *= cb_Ground.u_GroundBackgroundIntensity;

#ifdef GROUND_SPHERE
  vec3 viewDir = GetWorldCameraRay(vTexCoord, cb_Camera.u_BufferToViewNearPlane, cb_Camera.u_NearFarLogFactor.x, cb_Camera.u_ViewInverseMatrix, cb_Camera.u_PixelSize);
  viewDir = vNormalize(viewDir);
  
  vec3 eyePos = vec3(0,0,0);
  eyePos = ConvertViewToEarthCoord(eyePos);
  eyePos = UpdateEarthPosition(eyePos);
    
  float t = IntersectSphere(eyePos, viewDir, vec3(0), g_AtmosphereRadiusGround);
  if (t>0.0)
  {
    vec3 pos    = t*viewDir+eyePos;

#ifdef GROUND_CLIPPING
    vec3 groundPosition = cb_Ground_Auto.u_GroundNormal * cb_Ground_Auto.u_GroundHeight;
    groundPosition *= g_RatioToKm;
    
    if (vDot(pos-groundPosition, cb_Ground_Auto.u_GroundNormal)<0.0)
      discard;
#endif

    vec3 normal = vNormalize(pos);
       
    float diff = vDot(normal, cb_Sun.u_SunDirection.xyz);
    if (diff<0.0) diff = 0.0;

#ifdef GROUND_TEXTURE_CYLINDERMAP
    float u = vClamp((vAtan(normal.y, normal.x) + PI) * INV_PI *0.5, 0.0, 1.0);
    float v = vClamp(vAcos(normal.z) * INV_PI, 0.0, 1.0);

    /*float tmp = vAbs((v-0.5)*2);
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    tmp = tmp*tmp;
    float deltau = 0.001 + 0.999*tmp;

    if (u<deltau || u>(1-deltau))
    {
      color *= vTexture(s_TextureMap, vec2(0, v));
    }
    else
    {
      color *= vTexture(s_TextureMap, vec2(u,v));   
    }*/

    color *= vTexture(s_TextureMap, vec2(u,v));
#endif
    
    color.xyz *= (diff*cb_Sun.u_SunIntensity+0.1);
    color.w = cb_Ground.u_GroundBackgroundColor.w;
  }
#else
  vec3 viewDir = vNormalize(vRay.xyz);
    
#ifdef GROUND_TEXTURE_CYLINDERMAP
  float u = vClamp((vAtan(viewDir.y, viewDir.x) + PI) * INV_PI *0.5, 0.0, 1.0);
  float v = vClamp(vAcos(viewDir.z) * INV_PI, 0.0, 1.0);

  color *= vTexture(s_TextureMap, vec2(u,v)); 
#endif

  color.w = cb_Ground.u_GroundBackgroundColor.w * vClamp(1-vDot(cb_Ground_Auto.u_GroundNormal, viewDir) * cb_Ground.u_GroundBackgroundRatio,0.0,1.0);

#endif
  
  FRAGCOLOR = color;
}
