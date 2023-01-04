
float ComputeOutline(void)
{    
  float ratio = 0.0;
  vec2 coord = vTexCoord;

#ifdef OUTLINE_DISPLACEMENT
  //----------------
  // displacement

  coord = ConvertViewportToViewpoint(coord);
  vec3 displacement = vTexture(s_DisplacementMap, coord*cb_Displacement.u_DisplacementScale).xyz;
  displacement.xy = cb_Displacement.u_DisplacementStrength*(displacement.xy - vec2(0.5));
  coord = vTexCoord + cb_PostEffectAuto.u_PixelSize * displacement.xy;

#endif

  vec4 n = GetNormal(coord);
  int backgroundFlag = int(n.w);

#if defined(OUTLINE_SILHOUETTE) || defined(OUTLINE_NORMAL)
  vec4 n1 = GetNormal(coord, vec2(1,0));
  vec4 n2 = GetNormal(coord, vec2(0,1));
  vec4 n3 = GetNormal(coord, vec2(1,1));
#endif
  
  //----------------------
  // Silhouette
#ifdef OUTLINE_SILHOUETTE
  if (backgroundFlag!=int(n2.w) || backgroundFlag!=int(n2.w) || backgroundFlag!=int(n3.w))
  {
    ratio = 1.0;
  }
#if defined(OUTLINE_NORMAL) || defined(OUTLINE_Z)
  else if (backgroundFlag!=0)
#endif
#else
#if defined(OUTLINE_NORMAL) || defined(OUTLINE_Z)
  if (backgroundFlag!=0)
#endif
#endif

#if defined(OUTLINE_NORMAL) || defined(OUTLINE_Z)
  {
    float ratioN = 0.0;
#ifdef OUTLINE_NORMAL
    //----------------------
    // Normal

    ratioN  = 1.0-vDot(n.xyz, n1.xyz);
    ratioN = vMax(ratioN, 1.0-vDot(n.xyz, n2.xyz));
    ratioN = vMax(ratioN, 1.0-vDot(n.xyz, n3.xyz));

    ratioN = vClamp(ratioN*cb_OutlineNormal.u_NormalStrength, cb_OutlineNormal.u_NormalMin, cb_OutlineNormal.u_NormalMax) - cb_OutlineNormal.u_NormalMin;
    ratioN *= cb_OutlineNormal.u_NormalStrength2;
#endif

    float ratioZ = 0.0;
#ifdef OUTLINE_Z
    //----------------------
    // Z

    float z  = GetLinearZ(coord);
    float z1 = GetLinearZ(coord, ivec2(1,0));
    float z2 = GetLinearZ(coord, ivec2(0,1));
    float z3 = GetLinearZ(coord, ivec2(1,1));

    ratioZ  = vAbs(z-z1);
    ratioZ  = vMax(vAbs(z-z2), ratioZ);
    ratioZ  = vMax(vAbs(z-z3), ratioZ);

    ratioZ = vClamp(ratioZ*cb_OutlineZ.u_ZStrength, cb_OutlineZ.u_ZMin, cb_OutlineZ.u_ZMax) - cb_OutlineZ.u_ZMin;
    ratioZ *= cb_OutlineZ.u_ZStrength2;

    // supprime l'effet bande noir quand on se trouve sur un face rasante
    float filterZ = (vClamp(vAbs(n.z), cb_OutlineZ.u_ZFilterLimit, 1.0) - cb_OutlineZ.u_ZFilterLimit)/(1.0 - cb_OutlineZ.u_ZFilterLimit);
    ratioZ *= filterZ; 
#endif

    ratio += vClamp(vMax(ratioZ, ratioN), 0.0, 1.0);	
  }
#endif

#ifdef OUTLINE_DISPLACEMENT
  ratio *= displacement.z;
#endif

 return ratio*cb_Outline.u_RatioVisibility;
}

