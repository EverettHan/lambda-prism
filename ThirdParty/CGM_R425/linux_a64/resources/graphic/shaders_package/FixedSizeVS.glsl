vec3 ComputeObjectPosition()
{
  mat4 worldViewMatrix = vGetWorldViewMatrix();
  vec4 originAndLengthInMM = vGetFixedSizeOriginAndLengthInMM(); // cb_FixedSize.u_FixedSizeOrigin;
  // originAndLengthInMM.xyz : origin   ;   originAndLengthInMM.w : lengthInMM
  vec3 origin = originAndLengthInMM.xyz;
  vec3 positionInVertexBuffer = vGetAttribPosition();



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


  mat4 worldViewInverseMatrix = inverse(worldViewMatrix);
  // vec3 viewPositionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, 0, 1)).xyz; // equivalent to next line
  vec3 viewPositionInObjectSpace = vec3(worldViewInverseMatrix[3][0], worldViewInverseMatrix[3][1], worldViewInverseMatrix[3][2]);
  // vec3 viewDirectionInObjectSpace = (worldViewInverseMatrix * vec4(0, 0, -1, 0)).xyz; // equivalent to next line
  vec3 viewDirectionInObjectSpace = vec3(-worldViewInverseMatrix[2][0], -worldViewInverseMatrix[2][1], -worldViewInverseMatrix[2][2]);
  float viewDirectionLengthInObjectSpace = length(viewDirectionInObjectSpace);
  viewDirectionInObjectSpace *= (1.0 / viewDirectionLengthInObjectSpace);


  float scaleFactor = cb_FixedSize.u_FixedSizeScaleFactor * originAndLengthInMM.w;
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
  vec3 positionInObjectSpace = scaleFactor * positionInVertexBuffer + (1.0 - scaleFactor) * origin; // s*p + (1-s)*o = o + s*(p-o)

  if(hasWorldScale)
    positionInObjectSpace = (worldScaleCancelMatrix * vec4(positionInObjectSpace, 1.0)).xyz;

  return positionInObjectSpace;

}

