bool g_isBackFace = false;

bool g_hasWorldScale = false;
mat4 g_worldScaleCancelMatrix;

#if defined(FixedSize) || defined(TextureFontText)
float g_scaleFactor = 1.0;
vec3 g_viewDirRight;
vec3 g_viewDirUp;
#endif

void ComputeCommonValues()
{
  vec3 origin = vGetFixedSizeOriginAndLengthInMM().xyz; 

  mat4 worldViewMatrix = vGetWorldViewMatrix();
  vec3 wsi = cb_FixedSize.u_FixedSizeWorldScaleInverse;
  g_hasWorldScale = (wsi.x != 1.0 || wsi.y != 1.0 || wsi.z != 1.0);
  if(g_hasWorldScale) // there is some world scale: need to alter the worldViewMatrix to cancel the effect of the world scale, to guarantee fixed size
  {
    mat4 worldRotationMatrix = vGetViewInverseMatrix() * worldViewMatrix; // result is equal to worldMatrix for now (aka model matrix)
    worldRotationMatrix[3][0] = worldRotationMatrix[3][1] = worldRotationMatrix[3][2] = 0.0; // we remove the translation component to get only the rotation part
    mat4 worldRotationInverseMatrix = inverse(worldRotationMatrix);
    mat4 worldScaleInverseMatrix = mat4(
        wsi.x, 0.0, 0.0, 0.0,
        0.0, wsi.y, 0.0, 0.0,
        0.0, 0.0, wsi.z, 0.0,
        0.0, 0.0, 0.0, 1.0); // world scale matrix, which operates in world space
    mat4 originTranslation = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        origin.x, origin.y, origin.z, 1.0);
    mat4 originInverseTranslation = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        -origin.x, -origin.y, -origin.z, 1.0);
    g_worldScaleCancelMatrix = originTranslation * worldRotationInverseMatrix * worldScaleInverseMatrix * worldRotationMatrix * originInverseTranslation;
    worldViewMatrix = worldViewMatrix * g_worldScaleCancelMatrix;
    // now the effect of the world scale, which was already contained in worldViewMatrix, is canceled by this update of the modelViewMatrix, while guaranteeing that 
    // the point at coordinate origin in object space will be transformed with the same result as with the former worldViewMatrix
  }


  mat4 worldViewInverseMatrix = inverse(worldViewMatrix);
  // vec3 viewPositionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, 0, 1)).xyz; // equivalent to next line
  vec3 viewPositionInObjectSpace = vec3(worldViewInverseMatrix[3][0], worldViewInverseMatrix[3][1], worldViewInverseMatrix[3][2]);
  // vec3 viewDirectionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, -1, 0)).xyz; // equivalent to next line
  vec3 viewDirectionInObjectSpace = vec3(-worldViewInverseMatrix[2][0], -worldViewInverseMatrix[2][1], -worldViewInverseMatrix[2][2]);
  float viewDirectionLengthInObjectSpace = length(viewDirectionInObjectSpace);
  viewDirectionInObjectSpace *= (1.0 / viewDirectionLengthInObjectSpace);

#if defined(FixedSize) || defined(TextureFontText)
  g_viewDirRight = normalize(vec3(worldViewInverseMatrix[0][0], worldViewInverseMatrix[0][1], worldViewInverseMatrix[0][2]));
  g_viewDirUp = normalize(vec3(worldViewInverseMatrix[1][0], worldViewInverseMatrix[1][1], worldViewInverseMatrix[1][2]));

  g_scaleFactor = cb_FixedSize.u_FixedSizeScaleFactor;
  if(cb_FixedSize.u_FixedSizeOrthographicProjectionScaleFactor != 0.f) // if we are in orthographic projection
  {
    g_scaleFactor *= cb_FixedSize.u_FixedSizeOrthographicProjectionScaleFactor;
    g_scaleFactor *= viewDirectionLengthInObjectSpace; // compensates uniform scale in model matrix
  }
  else // perspective projection
  {
    float zDistanceToCameraInObjectSpace = dot(origin - viewPositionInObjectSpace, viewDirectionInObjectSpace);
    g_scaleFactor *= zDistanceToCameraInObjectSpace;
  }
#endif // FixedSize || TextureFontText

  vec3 viewDirToOrigine = origin - viewPositionInObjectSpace;
  if(0.0 < dot(viewDirToOrigine, vGetAttribNormal()))
    g_isBackFace = true;

}

vec3 ComputeObjectPosition()
{
#ifdef RefPlaneLabel
  vec3 origin = vGetFixedSizeOriginAndLengthInMM().xyz; 
  float lenU = vGetFixedSizeOriginAndLengthInMM().w; 

  vec3 vecV = vGetAttribPosition();
  vec3 dirN = vGetAttribNormal();

  vec3 dirV = normalize(vecV);
  vec3 dirU = cross(dirV, dirN);
  float lenV = length(vecV);

  if(g_isBackFace)
    dirV *= -1.0;

  float dotU_Right = dot(dirU, g_viewDirRight);
  float dotU_Up    = dot(dirU, g_viewDirUp);

  int rotIndex = 0;
  if(abs(dotU_Right) > abs(dotU_Up))
  {
    rotIndex = (dotU_Right > 0.0) ? 0 : 2; 
  }
  else
  {
    rotIndex = (dotU_Up > 0.0) ? 1 : 3; 

    float tmpLen = lenU;
    lenU = lenV;
    lenV = tmpLen;
  }

  vec3 textU = dirU;
  vec3 textV = dirV;

  switch(rotIndex)
  {
    case 0: // u is right.. //no need to change anything
    break;

    case 1: // u is up
    {
      textU = -dirV;
      textV = dirU;
    }  
    break;

    case 2: // u is left
    {
      textU = -dirU;
      textV = -dirV;
    }  
    break;

    case 3: // u is down
    {
      textU = dirV;
      textV = -dirU;
    }  
    break;
  }

  float textScale = 10.0 / vGetAttribTexCoord0().y; // 10 px high

#ifdef FixedSize
  vec3 textOrigin = origin - g_scaleFactor * lenU * normalize(textU + textV);
  if(g_hasWorldScale)
    textOrigin = (g_worldScaleCancelMatrix * vec4(textOrigin, 1.0)).xyz;
  vec2 textPxDim = vGetAttribTexCoord0().xy * textScale;
#else
  vec3 textOrigin = origin - (textU * lenU + textV * lenV) * 0.5;
  vec2 textPxDim = vGetAttribTexCoord0().xy * textScale * g_scaleFactor;
#endif // FixedSize

  if(textPxDim.x > lenU || textPxDim.y > lenV)
  {
    return vec3(0.0);
  }
  else
  {
    mat4 textTrfMat = mat4(textU, 0.0, textV, 0.0, dirN, 0.0, textOrigin, 1.0); 
    return (textTrfMat * vec4(textScale * g_scaleFactor * vGetTextScreenAndTextureCoord().xy, 0.0, 1.0)).xyz;
  }
  
#elif defined(TextureFontText)


  vec3 origin = vGetFixedSizeOriginAndLengthInMM().xyz; 
  float lenU = vGetFixedSizeOriginAndLengthInMM().w; 

  vec3 vecV = vGetAttribPosition();
  vec3 dirN = vGetAttribNormal();

  vec3 dirV = normalize(vecV);
  vec3 dirU = cross(dirV, dirN);
  float lenV = length(vecV);

  float textScale = g_scaleFactor * 10.0 / vGetAttribTexCoord0().y; // 10 px high
#ifdef FixedSize
  vec3 anchor = origin + g_scaleFactor * sqrt(lenU * lenU * 0.5) * dirU;
  if(g_hasWorldScale)
    anchor = (g_worldScaleCancelMatrix * vec4(anchor, 1.0)).xyz;
#else
  vec3 anchor = origin + lenU * 0.5 * dirU;
#endif // FixedSize

  vec2 textPxDim = vGetAttribTexCoord0().xy * textScale;
  if(textPxDim.x > lenU * 0.5 || textPxDim.y > lenV)
  {
    return vec3(0.0);
  }
  else
  {
    mat4 textTrfMat = mat4(dirU, 0.0, dirV, 0.0, dirN, 0.0, anchor, 1.0); 
    vec2 textXY = vGetTextScreenAndTextureCoord().xy - vec2(vGetAttribTexCoord0().x, 1.0);
    return (textTrfMat * vec4(textScale * textXY, 0.0, 1.0)).xyz;
  }

#elif defined(FixedSize)
  vec3 origin = vGetFixedSizeOriginAndLengthInMM().xyz; 
  float lenMM = vGetFixedSizeOriginAndLengthInMM().w; 

  float scale = g_scaleFactor * lenMM;
  vec3 positionInObjectSpace = scale * vGetAttribPosition() + (1.0 - scale) * origin; // s*p + (1-s)*o = o + s*(p-o)

  if(g_hasWorldScale)
    positionInObjectSpace = (g_worldScaleCancelMatrix * vec4(positionInObjectSpace, 1.0)).xyz;

  return positionInObjectSpace;
#endif 

  return vGetAttribPosition();

}

vec4 ComputeObjectTexCoord0()
{
#ifdef TextureFontText
  return vec4(vGetTextScreenAndTextureCoord().zw, 0.f, 0.f);
#endif
  return vec4(0.f);
}

void ComputeVaryingValues()
{
#ifdef VertexColor
  if(g_isBackFace)
    vColorToUse = vGetAttribColor().xyz;
  else 
#endif
    vColorToUse = cb_cbVolMaterial.u_DiffuseColor.rgb;
}
