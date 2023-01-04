void main()
{
  vec2 uv = vTexCoord.xy;

  vec4 rDistorsion = vTexture(rComponentDistorsionMap, uv);
  vec4 gDistorsion = vTexture(gComponentDistorsionMap, uv);
  vec4 bDistorsion = vTexture(bComponentDistorsionMap, uv);

  vec4 result;

  if (rDistorsion.w < 0.9)
    result = vec4(0.0, 0.0, 0.0, 1.0);
  else
  {
    if (gDistorsion.w < 0.9)
      result = vec4(0.0, 0.0, 0.0, 1.0);
    else
    {
      if (bDistorsion.w < 0.9)
        result = vec4(0.0, 0.0, 0.0, 1.0);
      else
      {
        vec2 factor = ub_Distorsion.u_DistorsionFactor;
        vec2 rDisplacement;
        vec2 gDisplacement;
        vec2 bDisplacement;
        rDisplacement.x = ( rDistorsion.x - 0.5 ) / factor.x + uv.x;
        rDisplacement.y = ( rDistorsion.y - 0.5 ) / factor.y + uv.y;
        gDisplacement.x = ( gDistorsion.x - 0.5 ) / factor.x + uv.x;
        gDisplacement.y = ( gDistorsion.y - 0.5 ) / factor.y + uv.y;
        bDisplacement.x = ( bDistorsion.x - 0.5 ) / factor.x + uv.x;
        bDisplacement.y = ( bDistorsion.y - 0.5 ) / factor.y + uv.y;
        vec2 displacement = rDisplacement.xy;
        if (any(bvec2(clamp(displacement, vec2(0.0,0.0), vec2(1.0,1.0))-displacement)))
          result = vec4(0.0, 0.0, 0.0, 1.0);
        else
        {
          displacement = gDisplacement.xy;
          if (any(bvec2(clamp(displacement, vec2(0.0,0.0), vec2(1.0,1.0))-displacement)))
            result = vec4(0.0, 0.0, 0.0, 1.0);
          else
          {
            displacement = bDisplacement.xy;
            if (any(bvec2(clamp(displacement, vec2(0.0,0.0), vec2(1.0,1.0))-displacement)))
              result = vec4(0.0, 0.0, 0.0, 1.0);
            else
            {
              result.x = vTexture(colorMap, rDisplacement.xy).x;
              result.y = vTexture(colorMap, gDisplacement.xy).y;
              result.z = vTexture(colorMap, bDisplacement.xy).z;
            }
          }
        }
      }
    }
  }
  FRAGCOLOR = result;
}


