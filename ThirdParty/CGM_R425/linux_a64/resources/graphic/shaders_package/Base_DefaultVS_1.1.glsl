////////////////////////////////
// Client Code Basic Skeleton //
////////////////////////////////
//#define USE_TANGENT_SPACE

// customize this function to handle additionnal vertex transformations
// 'Pos' in vOut will already have been written when this function is called, and can be modified is desired
void basicComputeVaryingValues()
{
  { //Computing vTexCoord
    vec4 texCoord = vec4(0.0, 0.0, 0.0, 1.0);

#ifdef VolMaterial_TextureProjection
    
  #if VolMaterial_TextureProjection == 1
    {
      vec4 pos = vec4(vGetAttribPosition(), 1.0);

      texCoord.s = vDot(cb_cbVolMaterial.u_MaterialTextureProjPlaneS, pos);
      texCoord.t = vDot(cb_cbVolMaterial.u_MaterialTextureProjPlaneT, pos);
    }
  #elif VolMaterial_TextureProjection == 2
    {
      vec4 pos = vec4(vGetAttribPosition(), 1.0);
      pos = vGetWorldViewMatrix() * pos;

      mat4 modelViewInv = vTranspose(vGetViewInverseTransposeMatrix() * vGetWorldInverseTransposeMatrix()); 
      texCoord.s = vDot(modelViewInv*cb_cbVolMaterial.u_MaterialTextureProjPlaneS, pos);
      texCoord.t = vDot(modelViewInv*cb_cbVolMaterial.u_MaterialTextureProjPlaneT, pos);
    }
  #elif VolMaterial_TextureProjection == 3
    {
      //ftp://ftp.sgi.com/opengl/contrib/blythe/advanced99/notes/node177.html  
      //Maybe a performance hit here : compute the matrix on cpu if needed
      texCoord.xyz = vNormalize((vGetWorldViewMatrix()*vec4(vGetAttribPosition(),1.)).xyz);      
    }
  #else // VolMaterial_TextureProjection == 0
    {
      texCoord = vec4(vGetAttribTexCoord0().xyz, 1.0);
    }
  #endif
    
#else
    {
      texCoord = vec4(vGetAttribTexCoord0().xyz, 1.0);
    }
#endif

#ifdef TextureMatrix
    texCoord = vGetTextureMatrix() * texCoord;
#endif

    vTexCoord = texCoord.xyz;
  }

#ifdef VertexColor
  vColor = vGetColor();
#endif // VertexColor
}

#ifndef PDSFX1_VS_Varyings_BaseShaded
void ComputeVaryingValues()
{
  basicComputeVaryingValues();
}
#endif

void basicProcessClipSpacePosition(inout vec4 ioPosition)
{
#ifdef WorldMatrixOnly
  ioPosition = vec4(vGetPosition(),1.0);
#endif    
}

#ifndef PDSFX1_VS_ClipSpacePos_BaseShaded
void ProcessClipSpacePosition(inout vec4 ioPosition)
{
  basicProcessClipSpacePosition(ioPosition);
}
#endif
