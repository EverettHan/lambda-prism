vec3 ComputeObjectPosition()
{

  vec4 arrowXAxisAndXValue = vGetArrowXAxisAndXValue();
  vec4 arrowOriginAndYValue = vGetArrowOriginAndYValue();

  vec3 origin = arrowOriginAndYValue.xyz;
  vec3 xAxis = arrowXAxisAndXValue.xyz;
  float xCoord = arrowXAxisAndXValue.w;
  float yCoord = arrowOriginAndYValue.w;

  mat4 worldViewMatrix = vGetWorldViewMatrix();

  #ifdef FixedSize

  vec3 wsi = cb_FixedSize.u_FixedSizeWorldScaleInverse;
  bool hasWorldScale = (wsi.x != 1.0 || wsi.y != 1.0 || wsi.z != 1.0);
  mat4 worldScaleCancelMatrix;
  if(hasWorldScale) // there is some world scale: need to alter the worldViewMatrix to cancel the effect of the world scale, to guarantee fixed size
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
    worldScaleCancelMatrix = originTranslation * worldRotationInverseMatrix * worldScaleInverseMatrix * worldRotationMatrix * originInverseTranslation;
    worldViewMatrix = worldViewMatrix * worldScaleCancelMatrix;
    // now the effect of the world scale, which was already contained in worldViewMatrix, is canceled by this update of the modelViewMatrix, while guaranteeing that 
    // the point at coordinate origin in object space will be transformed with the same result as with the former worldViewMatrix
  }

  #endif // ifdef FixedSize

  mat4 worldViewInverseMatrix = inverse(worldViewMatrix);
  // vec3 viewPositionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, 0, 1)).xyz; // equivalent to next line
  vec3 viewPositionInObjectSpace = vec3(worldViewInverseMatrix[3][0], worldViewInverseMatrix[3][1], worldViewInverseMatrix[3][2]);
  // vec3 viewDirectionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, -1, 0)).xyz; // equivalent to next line
  vec3 viewDirectionInObjectSpace = vec3(-worldViewInverseMatrix[2][0], -worldViewInverseMatrix[2][1], -worldViewInverseMatrix[2][2]);
  float viewDirectionLengthInObjectSpace = length(viewDirectionInObjectSpace);
  viewDirectionInObjectSpace *= (1.0 / viewDirectionLengthInObjectSpace);

  vec3 yAxis = cross(xAxis, viewDirectionInObjectSpace); // not normalized to mimic the computations in CAT3DFixedArrowGP::ImmediateDraw

  float scaleFactor = 1.0;

  
  #ifdef FixedSize

    scaleFactor = cb_FixedSize.u_FixedSizeScaleFactor; // * originAndLengthInMM.w;
    if(cb_FixedSize.u_FixedSizeOrthographicProjectionScaleFactor != 0.f) // if we are in orthographic projection
    {
      scaleFactor *= cb_FixedSize.u_FixedSizeOrthographicProjectionScaleFactor;
      scaleFactor *= viewDirectionLengthInObjectSpace; // compensates uniform scale in model matrix
    }
    else // perspective projection
    {
      float zDistanceToCameraInObjectSpace = dot(origin - viewPositionInObjectSpace, viewDirectionInObjectSpace);
      scaleFactor *= zDistanceToCameraInObjectSpace;
    }
  //  return scaleFactor * vertexPosition + (1.0 - scaleFactor) * origin; // s*p + (1-s)*o = o + s*(p-o)
    scaleFactor *= 2.f; // tmp test: to counter-balance the arbitrary "*0.5f" done for CAT3DPlanRep??
  #endif // ifdef FixedSize
  
  vec3 positionInObjectSpace = origin + (scaleFactor * xCoord) * xAxis + (scaleFactor * yCoord) * yAxis;

  #ifdef FixedSize
  if(hasWorldScale)
    positionInObjectSpace = (worldScaleCancelMatrix * vec4(positionInObjectSpace, 1.0)).xyz;
  #endif // ifdef FixedSize

  return positionInObjectSpace;

}

void ProcessClipSpacePosition(inout vec4 ioPosition)
{

#ifdef TextureFontText
  ioPosition /= ioPosition.w;
  // ioPosition.xy is the anchor point in clip space coordinates, between -1 and 1.
  ioPosition.xy = 0.5f * (ioPosition.xy + vec2(1.f, 1.f)) * vGetViewportSize(); // turn into float pixel coordinates
  ioPosition.xy += vGetTextScreenAndTextureCoord().xy; // shift in pixel coordinates
  ioPosition.xy = floor(ioPosition.xy); // snap to exact pixel intersection location
  ioPosition.xy = ioPosition.xy / vGetViewportSize() * 2.f - vec2(1.f, 1.f); // back to clip space coordinates
#endif
}



vec4 ComputeObjectTexCoord0()
{
#ifdef TextureFontText
  return vec4(vGetTextScreenAndTextureCoord().zw, 0.f, 0.f);
#endif
  return vec4(0.f);
}

