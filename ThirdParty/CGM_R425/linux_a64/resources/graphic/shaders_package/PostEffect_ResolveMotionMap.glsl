
void main()
{
  #ifdef MSAA
    ivec2 iTexCoord = ivec2(vTexCoord * textureSize(s_MotionVectorMap));
    vec2 maxVec = vec2(0);
    float velocity = 0.0;
    for (int i=0; i<MSAA; i++)
    {
        vec2 tmpVec = vTexelFetch(s_MotionVectorMap, iTexCoord, i).xy;
        float tmpVelocity = length(tmpVec);
        maxVec = tmpVelocity > velocity ? tmpVec : maxVec;
    }
    FRAGCOLOR  = vec4(maxVec, 0, 1);
  #else
    FRAGCOLOR  = vec4(vTexelFetch(s_MotionVectorMap, iTexCoord).xy, 0, 1);
  #endif
}
