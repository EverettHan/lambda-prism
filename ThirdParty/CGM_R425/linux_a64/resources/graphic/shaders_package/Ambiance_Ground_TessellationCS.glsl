
layout (vertices = 1) out;

float GetTessLevel2(float iDistanceToPatch)
{
  float tessLevel = 1.0;

  float beRadius = cb_Ground.u_Radius;

  const float nbStep = 6.0;
  const float stepFactor = 1.0/nbStep;

  float step1 = beRadius * 1 * stepFactor;
  float step2 = beRadius * 2 * stepFactor;
  float step3 = beRadius * 3 * stepFactor;
  float step4 = beRadius * 4 * stepFactor;
  float step5 = beRadius * 5 * stepFactor;
  float step6 = beRadius * 6 * stepFactor;


  if(iDistanceToPatch < step1)
    tessLevel = 32;
  else if(iDistanceToPatch < step2)
    tessLevel = 32;
  else if(iDistanceToPatch < step3)
    tessLevel = 16;
  else if(iDistanceToPatch < step4)
    tessLevel = 8;
  else if(iDistanceToPatch < step5)
    tessLevel = 8;
  else if(iDistanceToPatch < step6)
    tessLevel = 8;


  return tessLevel;
}

precise patch out vec3 oPatchPoints[4]; //Ensure precise computation to have crack free code.


vec2 _ComputeTexCoord(const vec3 iPoint)
{
  return iPoint.xy;
}


void ComputeTessellation()
{	

  oPatchPoints[0] = gl_in[0].gl_Position.xyz;
  oPatchPoints[1] = gl_in[1].gl_Position.xyz;
  oPatchPoints[2] = gl_in[2].gl_Position.xyz;
  oPatchPoints[3] = gl_in[3].gl_Position.xyz;

  vec3 oEdge1 = (oPatchPoints[0] + oPatchPoints[1]) * 0.5;
  vec3 oEdge2 = (oPatchPoints[1] + oPatchPoints[2]) * 0.5;
  vec3 oEdge3 = (oPatchPoints[2] + oPatchPoints[3]) * 0.5;
  vec3 oEdge4 = (oPatchPoints[3] + oPatchPoints[0]) * 0.5;

  vec3 vPoint1 = vGetViewPos(0);
  vec3 vPoint2 = vGetViewPos(1);
  vec3 vPoint3 = vGetViewPos(2);
  vec3 vPoint4 = vGetViewPos(3);

  vec3 vEdge1 = (vPoint1 + vPoint2) * 0.5;
  vec3 vEdge2 = (vPoint2 + vPoint3) * 0.5;
  vec3 vEdge3 = (vPoint3 + vPoint4) * 0.5;
  vec3 vEdge4 = (vPoint4 + vPoint1) * 0.5;


  vec3 eyePosView      = _vPrivGetViewEyePos();





  //// ----- Compute outer Tessellation ----- ////

  // Only the outer tessellation will contain the patch discard. Useless to do it for inner too.

  vec4 distancePatchCamera;

  distancePatchCamera.x = distance(vEdge1, eyePosView);
  distancePatchCamera.y = distance(vEdge2, eyePosView);
  distancePatchCamera.z = distance(vEdge3, eyePosView);
  distancePatchCamera.w = distance(vEdge4, eyePosView);


  vec4 fading;

  fading.x = ComputeFading(vLength(_ComputeTexCoord(oEdge1)), cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  fading.y = ComputeFading(vLength(_ComputeTexCoord(oEdge2)), cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  fading.z = ComputeFading(vLength(_ComputeTexCoord(oEdge3)), cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  fading.w = ComputeFading(vLength(_ComputeTexCoord(oEdge4)), cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  

  vec4 outerTesselation;
    
  outerTesselation.x = GetTessLevel2(distancePatchCamera.x);
  outerTesselation.y = GetTessLevel2(distancePatchCamera.y);
  outerTesselation.z = GetTessLevel2(distancePatchCamera.z);
  outerTesselation.w = GetTessLevel2(distancePatchCamera.w);
      
  //We cull the patch only and only if all tessellation are 0 else, we keep the patch
  float keepThisPatch = float(vAny(vGreaterThan(fading, vec4(1e-5))));


  //now we will cull every patch that is behind the camera.
  // to do that, we check the dot product sign with the view vector.
  vec3 lookAt = vec3(0, 0, -1);

  vec4 dots;
  dots.x = vSign(vDot(lookAt, vEdge1 - eyePosView));
  dots.y = vSign(vDot(lookAt, vEdge2 - eyePosView));
  dots.z = vSign(vDot(lookAt, vEdge3 - eyePosView));
  dots.w = vSign(vDot(lookAt, vEdge4 - eyePosView));


  //we keep the patch if we have at least one dot product >0.
  keepThisPatch *= float(vAny(vGreaterThan(dots, vec4(0))));


  //If we are close to the edge, we reduce the tessellation (this is the outerTesselation.y * fading.y)
  vec4 outerTessRes = keepThisPatch * vMax(outerTesselation * fading, vec4(1));


  gl_TessLevelOuter[0] = outerTessRes.y; //right
  gl_TessLevelOuter[1] = outerTessRes.x; //bot
  gl_TessLevelOuter[2] = outerTessRes.w; //left
  gl_TessLevelOuter[3] = outerTessRes.z; //top

    //// ----- Compute inner Tessellation ----- ////

  vec3 vCenter = (vEdge1 + vEdge3) * 0.5;
  vec3 oCenter = (oEdge1 + oEdge3) * 0.5;

  float distanceCenterPatchCamera = distance(vCenter, eyePosView);


  float innerTesselation = GetTessLevel2(distanceCenterPatchCamera);
  float centerFading     = ComputeFading(vLength(_ComputeTexCoord(oCenter)), cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);

  innerTesselation = centerFading * vMax(innerTesselation, 1);

  gl_TessLevelInner[0] = innerTesselation;
  gl_TessLevelInner[1] = innerTesselation;
}

