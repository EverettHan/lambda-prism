#if defined(Sectioning) && (defined(GLES2Platform) || !defined(SectioningAllowed))
// Disable sectioning for mobile and some passes (like mirroring)
  #undef Sectioning
#endif

#ifdef Sectioning


  //uniform samplerBuffer sectionProfileData;

  void PerformSectioningDiscard()
  {
    ivec2 screenSize = vTextureSize(sectionProfileTex, 0).xy;
    vec2 screenCoord = vec2(gl_FragCoord.x/float(screenSize.x), gl_FragCoord.y/float(screenSize.y));

  #ifdef SectioningMapAsArray
    int offsetInt = vTexture(sectionProfileTex, vec3(screenCoord, float(cb_ClippingAdvanced.u_SectionMapID))).r;
  #else
    int offsetInt = vTexture(sectionProfileTex, screenCoord).r;
  #endif

    vec4 clipData = vTexelFetch(sectionProfileData, offsetInt);
    int nbSection = int(floor(clipData.x+0.5));
    int clipping = int(floor(clipData.y+0.5));

    if (nbSection <= 0)
    {
      if (clipping != 0)
        discard;
    }
    else
    {
      vec4 pos = vec4(vGetViewPosition(), 1.0);
      vec4 clipEq = vec4(0.0);
      int i = 0;
      for(i = 0; i < nbSection; i++)
      {
        offsetInt += 1;
        clipEq = vTexelFetch(sectionProfileData, offsetInt);
        float res = dot(clipEq, pos);

        if (clipping != 0)
        {
          if (res >= 0.0)
            discard;
          clipping = 0;
        }
        else
        {
          if (res > 0.0)
            break;
          else
          {
            if (i == (nbSection-1))
              discard;
          }
          clipping = 1;
        }
      }
    }
  }

#endif
