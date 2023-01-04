#if defined(MultiviewSinglePass) && (MultiviewSinglePass == 2) && defined(Use_sb_cbSinglePassStereo)
#define SinglePassStereoCameras
#endif

/************************************************** cbAmbiance_Background_Camera ***************************************************/

#ifdef SinglePassStereoCameras

mat4 vGetViewInverseMatrix() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInv; }

vec3 vGetNearFarLogFactor() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].NearFarLogFactor.xyz; }

vec4 vGetBufferToViewNearPlane() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].BufferToViewNearPlane; }

vec3 vGetWorldEyePos() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePos.xyz; }

vec3 vGetWorldEyePosLow() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePosLow.xyz; }

#elif defined(Use_sb_cbAmbiance_Background_Camera)

mat4 vGetViewInverseMatrix() { return cb_Camera.u_ViewInverseMatrix; }

vec3 vGetNearFarLogFactor() { return cb_Camera.u_NearFarLogFactor; }

vec4 vGetBufferToViewNearPlane() { return cb_Camera.u_BufferToViewNearPlane; }

vec3 vGetWorldEyePos() { return cb_Camera.u_EyePosition; }

vec3 vGetWorldEyePosLow() { return cb_Camera.u_EyePositionLow; }

#endif

/************************************************** cbViewTransition ***************************************************/

#ifdef SinglePassStereoCameras

#define UsePassThroughTransition

mat4 vGetViewTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewTransition; }

mat4 vGetViewInverseTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInvTransition; }

mat4 vGetViewInverseTransposeTransition() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].ViewInvTranspTransition; }

vec3 vGetEyeWorldPosOffset() { return _sbCbSinglePassStereo.Cameras[vGetViewID()].WorldEyePosOffset.xyz; }

#elif defined(Use_sb_cbViewTransition) && defined(PassThroughTransition)

#define UsePassThroughTransition

mat4 vGetViewTransition() { return _sbCbViewTransition.View; }

mat4 vGetViewInverseTransition() { return _sbCbViewTransition.ViewInv; }

mat4 vGetViewInverseTransposeTransition() { return _sbCbViewTransition.ViewInvTransp; }

vec3 vGetEyeWorldPosOffset() { return _sbCbViewTransition.WorldEyePos.xyz; }

#else

mat4 vGetViewTransition() { return mat4(1.0); }

mat4 vGetViewInverseTransition() { return mat4(1.0); }

mat4 vGetViewInverseTransposeTransition() { return mat4(1.0); }

vec3 vGetEyeWorldPosOffset() { return vec3(0.0); }

#endif
