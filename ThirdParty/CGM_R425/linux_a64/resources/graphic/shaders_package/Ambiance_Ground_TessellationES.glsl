
layout(quads, equal_spacing, cw) in;

precise patch in vec3 oPatchPoints[4];



vec3 g_VertexPos;


vec3 vGetPosition(){return g_VertexPos;}

vec3 vGetNormal(){return vec3(0);} //Our normal is computed and is a veying

#ifdef NeedUVs
  #ifndef TexCoordAsVec2
    vec3 vGetTexCoord0() {return vec3(0);} //Our Uvs are computed and are a varying
  #else
    vec2 vGetTexCoord0() {return vec2(0);}
  #endif
#endif


vec3 _GetVertexPosition()
{
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  vec3 cp1 = oPatchPoints[0];
  vec3 cp2 = oPatchPoints[1];
  vec3 cp3 = oPatchPoints[2];
  vec3 cp4 = oPatchPoints[3];

  vec3 p1 = mix(cp2, cp1, u);
  vec3 p2 = mix(cp3, cp4, u);

  return mix(p1, p2, v);
}

