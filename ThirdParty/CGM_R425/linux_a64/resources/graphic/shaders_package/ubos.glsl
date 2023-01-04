
/***************************************************** UBO Wrapper *************************************************/

#if defined(MultiviewSinglePass) && (MultiviewSinglePass == 2) && defined(Use_sb_cbSinglePassStereo)
#define SinglePassStereoCameras
#endif

#ifdef GlobalGASColor
  vec4 vGetGlobalGASColor()
  {
    return PushConstants;
  }
#endif

#if defined(OutputGPUPicking) || defined(OutputGPUPickingImage)
  uint GetGPUPickingID()
  {
    #if defined(GPUNoPick) || defined(GPUPickingDontWrite)
      return 0xFFFFFFFE; // fallback ID  
    #endif

    return vFloatBitsToUint(PushConstants.x);
  }
#endif

/************************************************** cbCamera ***************************************************/

#ifdef SinglePassStereoCameras

mat4 vGetViewMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].View; }

mat4 vGetProjMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].Proj; }

mat4 vGetViewProjMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewProj; }

mat4 vGetPrevViewProjMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].PrevViewProj; }

mat4 vGetViewInverseMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInv; }

mat4 vGetProjInverseMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ProjInv; }

mat4 vGetViewProjInverseMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewProjInv; }

//ViewInverseTransposeMatrix is expected to be View Matrix 
mat4 vGetViewInverseTransposeMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInvTransp; }

vec3 _vPrivGetWorldEyePos() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePos.xyz; }

vec3 _vPrivGetViewEyePos() { return vec3(0.0); }

vec3 vGetNearFarLogFactor() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].NearFarLogFactor.xyz; }

#elif defined(Use_sb_cbCamera)

mat4 vGetViewMatrix(){return _sbCbCamera.ViewMatrix;}

mat4 vGetProjMatrix(){return _sbCbCamera.ProjMatrix;}

mat4 vGetViewProjMatrix(){return _sbCbCamera.ViewProjMatrix;}

mat4 vGetPrevViewProjMatrix() { return _sbCbCamera.PrevViewProjMatrix; }

mat4 vGetViewDeltaMatrix() { return _sbCbCamera.ViewDeltaMatrix; }

mat4 vGetUnjitteredProjMatrix() { return _sbCbCamera.UnjitteredProjMatrix; }

mat4 vGetViewInverseMatrix(){return _sbCbCamera.ViewInverseMatrix;}

mat4 vGetProjInverseMatrix(){return _sbCbCamera.ProjInverseMatrix;}

mat4 vGetViewProjInverseMatrix(){return _sbCbCamera.ViewProjInverseMatrix;}

//ViewInverseTransposeMatrix is expected to be View Matrix 
mat4 vGetViewInverseTransposeMatrix(){return _sbCbCamera.ViewInverseTransposeMatrix;}

vec3 _vPrivGetWorldEyePos() { return _sbCbCamera.EyeWorldPos; }

vec3 _vPrivGetViewEyePos() { return vec3(0.0); }

vec3 vGetNearFarLogFactor() { return _sbCbCamera.NearFarLogFactor; }

#else

mat4 vGetViewMatrix(){return mat4(0.);}

mat4 vGetProjMatrix(){return mat4(0.);}

mat4 vGetViewProjMatrix(){return mat4(0.);}

mat4 vGetPrevViewProjMatrix() { return mat4(0.); }

mat4 vGetViewDeltaMatrix() { return mat4(0.); }

mat4 vGetViewInverseMatrix(){return mat4(0.);}

mat4 vGetProjInverseMatrix(){return mat4(0.);}

mat4 vGetViewProjInverseMatrix(){return mat4(0.);}

//ViewInverseTransposeMatrix is expected to be View Matrix 
mat4 vGetViewInverseTransposeMatrix(){return mat4(0.);}

vec3 _vPrivGetWorldEyePos(){return vec3(0.);}

vec3 _vPrivGetViewEyePos(){return vec3(0.);}

vec3 vGetNearFarLogFactor(){return vec3(0.);}

#endif

mat4 vGetProjectionMatrix(){return vGetProjMatrix();}

mat4 vGetViewProjectionMatrix(){return vGetViewProjMatrix();}

mat4 vGetViewInvMatrix(){return vGetViewInverseMatrix();}

mat4 vGetProjectionInvMatrix(){return vGetProjInverseMatrix();}

mat4 vGetViewProjectionInvMatrix(){return vGetViewProjInverseMatrix();}

mat4 vGetViewInvTranspMatrix(){return vGetViewInverseTransposeMatrix();}

#ifndef PDSFX1
vec3 vGetWorldEyePos(){return _vPrivGetWorldEyePos();}

vec3 vGetViewEyePos(){return _vPrivGetViewEyePos();}
#endif

/************************************************** cbViewTransition ***************************************************/

#ifdef SinglePassStereoCameras

#define UsePassThroughTransition

mat4 _vPrivGetViewTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewTransition; }

mat4 _vPrivGetViewInverseTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInvTransition; }

mat4 _vPrivGetViewInverseTransposeTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInvTranspTransition; }

vec3 _vPrivGetEyeWorldPosOffset() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePosOffset.xyz; }

#elif defined(Use_sb_cbViewTransition) && defined(PassThroughTransition)

#define UsePassThroughTransition

mat4 _vPrivGetViewTransition() { return _sbCbViewTransition.View; }

mat4 _vPrivGetViewInverseTransition() { return _sbCbViewTransition.ViewInv; }

mat4 _vPrivGetViewInverseTransposeTransition() { return _sbCbViewTransition.ViewInvTransp; }

vec3 _vPrivGetEyeWorldPosOffset() { return _sbCbViewTransition.WorldEyePos.xyz; }

#else

mat4 _vPrivGetViewTransition() { return mat4(1.0); }

mat4 _vPrivGetViewInverseTransition() { return mat4(1.0); }

mat4 _vPrivGetViewInverseTransposeTransition() { return mat4(1.0); }

vec3 _vPrivGetEyeWorldPosOffset() { return vec3(0.0); }

#endif

/************************************************** cbHighPrecisionCamera ***************************************************/
#if !defined(GLESPlatform) && (GLSLVersion > 410)
#if defined(Use_sb_cbHighPrecisionCamera) && defined(HighPrecisionCamera)

#ifdef SinglePassStereoCameras
  dvec3 vGetWorldEyePosHighPrecision() 
  {
    return dvec3(_sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePos.xyz) + dvec3(_sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePosLow.xyz);
  }
#else
  dvec3 vGetWorldEyePosHighPrecision() 
  {
    return dvec3(_sbCbHighPrecisionCamera.EyeWorldPosHigh) + dvec3(_sbCbHighPrecisionCamera.EyeWorldPosLow);
  }
#endif

#else

  dvec3 vGetWorldEyePosHighPrecision() 
  {
    return dvec3(_vPrivGetWorldEyePos());
  }

#endif
#endif

/************************************************** cbViewport ***************************************************/

#ifdef Use_sb_cbViewport
ivec2 vGetViewportSize() { return ivec2(int(cb_Viewport.u_ViewportSize.x), int(cb_Viewport.u_ViewportSize.y)); }
#else
ivec2 vGetViewportSize() { return ivec2(0,0); }
#endif

/************************************************** cbLight ***************************************************/

#ifdef Use_sb_LightsSB2

vec3 _vPrivGetAmbientColor(){return _sbLightsSB2.AmbientColor;}
vec3 vGetLowlightColor(){return _sbLightsSB2.LowlightColor;}

#else

vec3 _vPrivGetAmbientColor(){return  vec3(0.);}
vec3 vGetLowlightColor(){return vec3(0.);}

#endif

/************************************************** cbNode ***************************************************/

#ifdef Use_sb_cbNode

mat4 _vPrivGetWorldMatrix()
{
#ifdef RayHitStage
  return mat4(gl_ObjectToWorldEXT);
#else
  return _sbCbNode.WorldMatrix;
#endif
}

mat4 _vPrivGetWorldInverseTransposeMatrix()
{
#ifdef RayHitStage
  return mat4(gl_WorldToObject3x4EXT);
#else
  return _sbCbNode.WorldInverseTransposeMatrix;
#endif
}

#ifdef UsePassThroughTransition

mat4 vGetWorldViewMatrix() { return _vPrivGetViewTransition() * _sbCbNode.WorldViewMatrix; }

mat4 vGetWorldViewInverseTransposeMatrix() { return _vPrivGetViewInverseTransposeTransition() * _sbCbNode.WorldViewInverseTransposeMatrix; }

#else

mat4 vGetWorldViewMatrix()
{
#ifdef RayHitStage
  return vGetViewMatrix() * mat4(gl_ObjectToWorldEXT);
#else
  return _sbCbNode.WorldViewMatrix;
#endif
}

mat4 vGetWorldViewInverseTransposeMatrix()
{
#ifdef RayHitStage
  return transpose(mat4(gl_WorldToObjectEXT) * vGetViewInverseMatrix());
#else
  return _sbCbNode.WorldViewInverseTransposeMatrix;
#endif
}

#endif

#else

mat4 _vPrivGetWorldMatrix(){return mat4(0.);}

mat4 _vPrivGetWorldInverseTransposeMatrix(){return mat4(0.);}

mat4 vGetWorldViewMatrix(){return mat4(0.);}

mat4 vGetWorldViewInverseTransposeMatrix(){return mat4(0.);}

#endif

#ifdef PDSFX1
mat4 vGetWorldViewInvTranspMatrix(){return vGetWorldViewInverseTransposeMatrix();}
#else
mat4 vGetWorldMatrix(){return _vPrivGetWorldMatrix();}

mat4 vGetWorldInverseTransposeMatrix(){return _vPrivGetWorldInverseTransposeMatrix();}
#endif

/*********************************************** cbVolMaterial ***********************************************/

#ifdef Use_sb_cbVolMaterial

  float vGetPointSize() { return cb_cbVolMaterial.u_PointSize; }

mat4 vGetTextureMatrix(){return cb_cbVolMaterial.u_TextureMatrix;}

  #ifdef GlobalGASColor
    vec4 vGetMaterialAmbientColor() { return vGetGlobalGASColor(); }
  #else
    vec4 vGetMaterialAmbientColor() { return cb_cbVolMaterial.u_AmbientColor; }
  #endif

#else

  mat4 vGetTextureMatrix() { return mat4(0.0); }

  vec4 vGetMaterialAmbientColor() { return vec4(0.0); }

  float vGetPointSize() { return 1.0; }

#endif
