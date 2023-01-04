// SCALE_MODE:
// 0: l'image est étendue sur tout l'ecran, les ratio ne sont pas forcement conservé                              -> pas de marge
// 1: PAN_SCAN    (on conserve les ratio de l'image et l'ecran est entierement rempli)                            -> pas de marge
// 2: LETTER_BOX  (on conserve les ratio de l'image et toute l'image est visible a l'ecran)                       -> marges potentielles
// 3: FIT_WIDTH   (on conserve les ratio de l'image et la largeur de l'image prend toute la largeur de l'ecran)   -> marges potentielles
// 4: FIT_HEIGHT  (on conserve les ratio de l'image et la HAUTEUR de l'image prend toute la hauteur de l'ecran)   -> marges potentielles

#ifndef SCALE_MODE
#define SCALE_MODE 0
#endif

vec2 ComputePictureCoord(const vec2 iCoord, const vec2 iPicSize, const vec2 iVpSize)
{
  vec2 coord;

  float vpRatio   = iVpSize.x/iVpSize.y;
  float picRatio  = iPicSize.x/iPicSize.y;
  float ratio     = vpRatio/picRatio;

  vec2 scale = vec2(1.0); 

#if SCALE_MODE==1 || SCALE_MODE==2
#if SCALE_MODE==2
  if (ratio>=1.0)
#else
  if (ratio<=1.0)
#endif
  {
    scale.x = ratio;
  }
  else
  {
    scale.y = 1.0/ratio;
  }
#elif  SCALE_MODE==3
  scale.y = 1.0 / ratio;
#elif  SCALE_MODE==4
  scale.x = ratio;
#endif
  vec2 delta = 0.5*(vec2(1.0) - scale.xy);

  coord = vFma(iCoord, scale, delta);

  return coord;
}

//------------------------------------------------------------------------------------------------------------------
// Cube

vec3 ComputeCubeMapPictureCoord(const vec2 iCoord)
{
  vec3 coord;

  float x = iCoord.x;
  float y = iCoord.y;

  if (3 * iCoord.y < 1)
  {
    y = y * 3;
    y = y * 2 - 1;

    if (iCoord.x>0.25 && iCoord.x<0.5)
    {
      x = x * 4 - 1;
      x = x * 2 - 1;

      coord = vec3(x, 1.0, y);
    }
    else
    {
      discard;
    }
  }
  else if (3 * iCoord.y <= 2)
  {
    y = y * 3 - 1;
    y = y * 2 - 1;

    if (iCoord.x<0.25)
    {
      x = x * 4;
      x = x * 2 - 1;

      coord = vec3(-1.0, -y, x);
    }
    else if (iCoord.x<0.5)
    {
      x = x * 4 - 1;
      x = x * 2 - 1;

      coord = vec3(x, -y, 1.0);
    }
    else if (iCoord.x<0.75)
    {
      x = x * 4 - 2;
      x = x * 2 - 1;

      coord = vec3(1.0, -y, -x);
    }
    else if (iCoord.x<1.0)
    {
      x = x * 4 - 3;
      x = x * 2 - 1;

      coord = vec3(-x, -y, -1.0);
    }
  }
  else
  {
    y = y * 3 - 2;
    y = y * 2 - 1;

    if (iCoord.x>0.25 && iCoord.x<0.5)
    {
      x = x * 4 - 1;
      x = x * 2 - 1;

      coord = vec3(x, -1.0, -y);
    }
    else
    {
      discard;
    }
  }

  return vNormalize(coord);
}

ivec2 ComputeUnfoldedGridDimensions(int iNbElements)
{
  int columnSize = int(sqrt(iNbElements));
  int rowSize = int((iNbElements - 1) / columnSize) + 1;

  return ivec2(rowSize, columnSize);
}

ivec3 ComputeUnfoldedGridTexCoord(const ivec2 iGridDim, const ivec3 iTextureSize, const vec2 iCoord)
{
  ivec2 cell = min(ivec2(iGridDim * iCoord), iGridDim - 1);

  int layer = (iGridDim.y - 1 - cell.y) * iGridDim.x + cell.x;
  if (layer >= iTextureSize.z)
    discard;

  vec2 cellCoord = iGridDim * iCoord - cell;

  return ivec3(cellCoord * iTextureSize.xy, layer);
}

vec4 DrawPicture(samplerCube iTexture, const vec2 iCoord, const vec2 iVpSize, int iMip)
{ 
  vec2 coord = iCoord;

#if SCALE_MODE>0
  ivec2 textureSize = vTextureSize(iTexture, iMip).xy;
  coord = ComputePictureCoord(coord, vec2(textureSize.x * 4, textureSize.y * 3), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  return vTextureLod(iTexture, ComputeCubeMapPictureCoord(coord), iMip);
}

vec4 DrawPicture(samplerCubeArray iTexture, const vec2 iCoord, const vec2 iVpSize, int iMip, const int iLayer)
{
  vec2 coord = iCoord;

#if SCALE_MODE>0
  ivec2 textureSize = vTextureSize(iTexture, iMip).xy;
  coord = ComputePictureCoord(coord, vec2(textureSize.x * 4, textureSize.y * 3), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif
  
  vec3 coordRes = ComputeCubeMapPictureCoord(coord);
  return vTextureLod(iTexture, vec4(coordRes.xyz, iLayer), iMip);
}

//------------------------------------------------------------------------------------------------------------------
// 3D

vec4 DrawPicture(sampler3D iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip, const int iLayer)
{
  // NB: pour le moment on ne voit que la slice 0,
  // il faudra coder un mode unfolded pour voir toutes les slices
  vec2 coord = iCoord;
  ivec3 textureSize = vTextureSize(iTexture, iMip).xyz;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize.xy), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif
  
  ivec3 coordPic = ivec3(textureSize.x*coord.x, textureSize.y*coord.y, iLayer);
  return vTexelFetch(iTexture, coordPic, iMip);
}

vec4 DrawPictureUnfolded(sampler3D iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
  vec2 coord = iCoord;
  ivec3 textureSize = vTextureSize(iTexture, iMip);
  ivec2 gridDim = ComputeUnfoldedGridDimensions(textureSize.z);

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize.xy * gridDim), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x < 0 || coord.x > 1.f || coord.y < 0 || coord.y > 1.f)
    discard;
#endif

  ivec3 unfoldedCoord = ComputeUnfoldedGridTexCoord(gridDim, textureSize, coord);

  return vTexelFetch(iTexture, unfoldedCoord, iMip);
}

// because default arguments are managed by glsl
vec4 DrawPicture(sampler3D iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
#ifdef UNFOLD_ARRAY
  return DrawPictureUnfolded(iTexture, iCoord, iVpSize, iMip);
#else
  return DrawPicture(iTexture, iCoord, iVpSize, iMip, 0);
#endif
}

//------------------------------------------------------------------------------------------------------------------
// 1D

vec4 DrawPicture(sampler1D iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
  vec2 coord = iCoord;
  int textureSize = vTextureSize(iTexture, iMip).x;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize, 1.0), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  int coordPic = int(textureSize*coord.x);
  return vTexelFetch(iTexture, coordPic, iMip);
}

//------------------------------------------------------------------------------------------------------------------
// 2D

vec4 DrawPicture(sampler2D iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
  vec2 coord = iCoord;
  ivec2 textureSize = vTextureSize(iTexture, iMip).xy;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  ivec2 coordPic = ivec2(textureSize*coord);
  return vTexelFetch(iTexture, coordPic, iMip);
}

vec4 DrawPicture(sampler2DArray iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip, const int iLayer)
{
  vec2 coord = iCoord;
  ivec2 textureSize = vTextureSize(iTexture, iMip).xy;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  ivec3 coordPic = ivec3(textureSize*coord, iLayer);
  return vTexelFetch(iTexture, coordPic, iMip);
}

vec4 DrawPictureUnfolded(sampler2DArray iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
  vec2 coord = iCoord;
  ivec3 textureSize = vTextureSize(iTexture, iMip);
  ivec2 gridDim = ComputeUnfoldedGridDimensions(textureSize.z);

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize.xy * gridDim), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x < 0 || coord.x > 1.f || coord.y < 0 || coord.y > 1.f)
    discard;
#endif

  ivec3 unfoldedCoord = ComputeUnfoldedGridTexCoord(gridDim, textureSize, coord);

  return vTexelFetch(iTexture, unfoldedCoord, iMip);
}

vec4 DrawPicture(sampler2DArray iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
#ifdef UNFOLD_ARRAY
  return DrawPictureUnfolded(iTexture, iCoord, iVpSize, iMip);
#else
  return DrawPicture(iTexture, iCoord, iVpSize, iMip, 0);
#endif
}

vec4 DrawPicture(sampler2DMS iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip)
{
  vec2 coord = iCoord;
  ivec2 textureSize = vTextureSize(iTexture).xy;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  ivec2 coordPic = ivec2(textureSize*coord);
  return vTexelFetch(iTexture, coordPic, iMip);
}

vec4 DrawPicture(sampler2DMSArray iTexture, const vec2 iCoord, const vec2 iVpSize, const int iMip, const int iLayer)
{
  vec2 coord = iCoord;
  ivec2 textureSize = vTextureSize(iTexture).xy;

#if SCALE_MODE>0
  coord = ComputePictureCoord(coord, vec2(textureSize), iVpSize);
#endif
#if SCALE_MODE>1
  if (coord.x<0 || coord.x>1.f || coord.y<0 || coord.y>1.f)
    discard;
#endif

  ivec3 coordPic = ivec3(textureSize*coord, iLayer);
  return vTexelFetch(iTexture, coordPic, iMip);
}

