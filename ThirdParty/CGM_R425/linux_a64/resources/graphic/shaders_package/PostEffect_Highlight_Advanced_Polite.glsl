bool IsOutlinePolite()
{ 
  int i;
  int thickness = int(cb_PostEffect_Advanced_Polite.u_FaceThickness);

  for(i=1; i <= thickness; i++)
  {
    if(  GetEffectTexture(s_EyeMapHL, vTexCoord, ivec2( 0,-i)).a == 1.0
      || GetEffectTexture(s_EyeMapHL, vTexCoord, ivec2( 0, i)).a == 1.0
      || GetEffectTexture(s_EyeMapHL, vTexCoord, ivec2( i, 0)).a == 1.0
      || GetEffectTexture(s_EyeMapHL, vTexCoord, ivec2(-i, 0)).a == 1.0)
    {
      return true;
    }
  }
   
  return false;
}

bool IsHighlightVisible(ivec2 iOffset)
{
  vec2 coord = vTexCoord + iOffset * cb_PostEffectAuto.u_PixelSize;

#ifdef NORMAL_Z_MSAA
  float zHL = 1.0;
  float zScene = 0;
  for (int i = 0; i < NORMAL_Z_MSAA; i++)
  {
    zScene  = vMax(zScene, GetZSample(coord, i));
    zHL     = vMin(zHL, GetEffectTexture(s_ZMapHL, coord, i).x);
  }
#else
  float zHL     = GetEffectTexture(s_ZMapHL, coord).x;
  float zScene  = GetZ(coord);
#endif

  return (zHL <= zScene);
}

#ifdef HIGHLIGHT_LINE_AND_MARKER_POLITE

void ComputeHighlight(ivec2 iOffset, inout int ioType
  , inout float ioDistance, inout float ioHiddenDistance
#ifdef MultiColorHighlight
  , inout vec4  ioCol,      inout  vec4  ioHiddenCol
#endif
)
{
  vec4 col = GetEffectTexture(s_EyeMapHL, vTexCoord, iOffset);

  if (col.a <1 && col.a>0.9)
  {
    if (IsHighlightVisible(iOffset))
    {
      ioType = 2;
      float distance = vDot(iOffset, iOffset);
      if (distance < ioDistance)
      {
        ioDistance = distance; 
#ifdef MultiColorHighlight
        ioCol      = col;
#endif
      }
    }
    else
    {
      if (ioType < 2)
      {
        ioType = 1;
        float distance = vDot(iOffset, iOffset);
        if (distance < ioHiddenDistance)
        {
          ioHiddenDistance = distance; 
#ifdef MultiColorHighlight
          ioHiddenCol      = col;
#endif
        }
      }
    }
  }
}

vec4 ComputeHighlightColor(vec4 iColor, float iRatio)
{
#ifdef MultiColorHighlight
  vec4 col        = vec4(iColor.rgb, 0.6);
  vec4 outlineCol = vec4(iColor.rgb*1.142f, 1.0f);
#else
  vec4 col        = vec4(cb_PostEffect_Advanced_Polite.u_PolitnessColor.rgb, 0.6f);
  vec4 outlineCol = vec4(cb_PostEffect_Advanced_Polite.u_OutlineColor.rgb, 1.0f);
#endif

  return vMix(col, outlineCol, iRatio);
}

#endif

void main()
{
#ifdef HIGHLIGHT_LINE_AND_MARKER_POLITE
  float distance        = 9;
  float hiddenDistance  = 9;
  int type              = 0;

  vec4  visibleCol;
  vec4  hiddenCol;

  for (int i = -2; i <= 2; i++)
  {
    for (int j = -2; j <= 2; j++)
    {
      ComputeHighlight(ivec2(i, j), type
        , distance, hiddenDistance
#ifdef MultiColorHighlight
        , visibleCol, hiddenCol
#endif
      );
    }
  }

  if (type == 2)
  {
    if (distance <= 6.25f)
    {
      FRAGCOLOR = ComputeHighlightColor(visibleCol, vSmoothstep(1.5f, 3.f, distance));
             
      return;
    }
  }
  else if (type == 1)
  {
    if (hiddenDistance <= 2.25f)
    {
      FRAGCOLOR = ComputeHighlightColor(hiddenCol, vSmoothstep(0.25f, 1.f, hiddenDistance));
      return;
    }
  }
#endif

  
  vec4 col = GetEffectTexture(s_EyeMapHL, vTexCoord); 
  
  if (col.a == 1.0)
  {
    //--------------------------
    // Halo 

#ifdef MultiColorHighlight
    col.xyz = vec3(0, 0, 0);
#else
    col.xyz = cb_PostEffect_Advanced_Polite.u_HaloColor.xyz;
#endif

    col.a = 0;

    int i;
    for (i = 0; i < NUM_BLUR; i++)
    {
      vec4 value = GetEffectTexture(s_EyeMapHL, vTexCoord, cb_PostEffect_Advanced_Polite.u_HaloSize*g_FilterBlurData[i]);

#ifdef MultiColorHighlight
      if (value.a != 1.0)
      {
        col.rgb += value.rgb;
      }
#endif
      col.a += value.a != 1.0 ? 1.0 : 0.0; // Halo for visible and hidden geometry
    }

#ifdef MultiColorHighlight
    col.rgb /= col.a;
#endif

    col.a *= INV_NUM_BLUR * cb_PostEffect_Advanced_Polite.u_HaloIntensity;
  }
  else
  {
    if (IsOutlinePolite())
    {
      //--------------------------
      // Outline

#ifdef MultiColorHighlight
      col = vec4(col.rgb*1.142, 1.0);
#else
      col = cb_PostEffect_Advanced_Polite.u_OutlineColor;
#endif
    }
    else
    {
      //--------------------------
      // Politness
            
#ifndef MultiColorHighlight
      col.rgb = cb_PostEffect_Advanced_Polite.u_PolitnessColor.rgb;
#endif

      if (IsHighlightVisible(ivec2(0,0)))
      {
        // Visible
        float ratio = (col.a > 0.9) ? (1.0) : (0.682 * (1.0 - (col.a / 0.9)) + 0.318); //  (1-1/pi) * (1-x/0.9) + 1/pi
        col = vec4(col.rgb* ratio, cb_PostEffect_Advanced_Polite.u_VisibleFaceAlpha);
      }
      else
      {
        // Occluded
        col = vec4(col.rgb, cb_PostEffect_Advanced_Polite.u_OccludedAlpha);
      }
    }
  }

  FRAGCOLOR = col;
}
