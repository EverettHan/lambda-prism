//------------------------------------------------------
// premiere passe de calcul du blur,
// si a==1 on est sur le fond
// si a!=1 on est sur la scene 3D
// on fait donc un blur sur (a==1 ? 1 : 0) ce qui epxlique le vFloor

vec4 ComputeFirstPassHalo(const sampler2D iTexture)
{
#ifdef MultiColorHighlight
  vec4  result    = vec4(0, 0, 0, 0);
  int   numColor  = 0;
#else
  float result    = 0;
#endif

  int i;
  for (i = 0; i < NUM_BLUR; i++)
  {
    vec4 col = GetEffectTexture(iTexture, vTexCoord, cb_PostEffect_Highlight_Advanced.u_HaloSize*g_FilterBlurData[i]);

#ifdef MultiColorHighlight
    if (col.a < 1.0)
    {
      result.xyz += col.xyz;
      numColor++;
    }
    else
    {
      result.a += 1.0;
    }
#else
    result += vFloor(col.a);
#endif
  }

#ifdef MultiColorHighlight
  result.a    *= INV_NUM_BLUR;
  result.xyz  /= numColor;

  return result;
#else
  result *= INV_NUM_BLUR;
  return vec4(result);
#endif
}

//------------------------------------------------------
// pass supplementaire de calcul de blur

vec4 ComputeHalo(const sampler2D iTexture)
{
#ifdef MultiColorHighlight
  vec4  result    = vec4(0, 0, 0, 0);
  int   numColor  = 0;
#else
  float result    = 0;
#endif

  int i;
  for (i = 0; i < NUM_BLUR; i++)
  {
    vec4 col = GetEffectTexture(iTexture, vTexCoord, cb_PostEffect_Highlight_Advanced.u_HaloSize*g_FilterBlurData[i]);
#ifdef MultiColorHighlight
    if (col.a < 1.0)
    {
      result.xyz += col.xyz;
      numColor++;
    }

    result.a += col.a;
#else
    result += col.x;
#endif
  }

#ifdef MultiColorHighlight
  result.a   *= INV_NUM_BLUR;
  result.xyz /= numColor;

  return result;
#else
  result *= INV_NUM_BLUR;
  return vec4(result);
#endif
}






