/***** Abstractive layer for glsl / glsl es intrinsics *****
* This file (along with its VS specific and FS specific counterparts) provide indirections for GLSL and GLSL ES intrinsics. Native intrisics can't be used directly in your glsl code, you must use 
* v* ones.
* Thus, all OpenGL 4.4 intrinsics are listed these files. For each intrinsic, you call fall in one of those three cases :
* => If an intrinsics has not been used in GLSL ES yet and an equivalent can be implemented. In that case, the intrinsic has been #defined 
*    in the common section and you have to implement the GLSL ES version and #define it in the GLSL section. Don't forget to comment the 
*    #define in the common section.
* => If an intrinsic is supported the same way by both GLSL versions, it is still redefined here in the common section since we want to 
*    expose an uniform intrisic API at user level. So, in case you have to add a new intrinsic (for GLSL 4.4+ versions), you MUST #define 
*    it here. All these common definitions are regrouped at the bottom.
* => An intrinsic in only defined on GLSL version and there is no way to implement its equivalent in GLSL ES, it is still #defined in the 
*    lastest section as above. It will raise an error at compile time on GLSL ES platforms.
*/

const float INV_PI = 0.31830988618;
const float PI = 3.14159265359;

#ifndef GLES2Platform
/**************************************/
/********** GLSL 4.4 SECTION **********/
/**************************************/

#define	vMin min
#define	vMax max
#define	vTextureLod			textureLod
#define	vTextureProjLod		textureProjLod
#define	vTexture			texture
#define	vTextureProj		textureProj
#define vTextureCubeLod		textureLod

#if !defined(GLES3Platform) && (GLSLVersion >= 400)

//Matrix functions
#define	vMatrixCompMult matrixCompMult
#define	vOuterProduct	outerProduct
#define	vTranspose		transpose
#define	vDeterminant	determinant
#define	vInverse		inverse

#define vEvaluatedTextureCubeMap(Sampler, iRay) \
vSamplingCubeMap_##Sampler(iRay)

#define vTextureCubeMap(Sampler, iRay) \
vEvaluatedTextureCubeMap(Sampler, iRay)

#define vEvaluatedTextureCubeMapLod(Sampler, iRay, iLod) \
vSamplingCubeMapLod_##Sampler(iRay, iLod)

#define vTextureCubeMapLod(Sampler, iRay, iLod) \
vEvaluatedTextureCubeMapLod(Sampler, iRay, iLod)

#define vEvaluatedTextureCubeMapArray(Sampler, iRay) \
vSamplingCubeMapArray_##Sampler(iRay)

#define vTextureCubeMapArray(Sampler, iRay) \
vEvaluatedTextureCubeMapArray(Sampler, iRay)

#define vEvaluatedTextureCubeMapArrayLod(Sampler, iRay, iLod) \
vSamplingCubeMapArrayLod_##Sampler(iRay, iLod)

#define vTextureCubeMapArrayLod(Sampler, iRay, iLod) \
vEvaluatedTextureCubeMapArrayLod(Sampler, iRay, iLod)

#define vFma fma

#else // !GLES3Platform
//function like macro is not working on OpenGL ES 3.0
vec4 vTextureCubeMap(samplerCube iSampler, vec3 iRay)
{
  const mat3 passageMatrix = mat3(0.0,  0.0, -1.0,
                                  1.0,  0.0,  0.0,
                                  0.0, -1.0,  0.0);
  return vTexture(iSampler, passageMatrix * iRay);
}

vec4 vTextureCubeMapLod(samplerCube iSampler, vec3 iRay, float iLod)
{
  const mat3 passageMatrix = mat3(0.0,  0.0, -1.0,
                                  1.0,  0.0,  0.0,
                                  0.0, -1.0,  0.0);
  return vTextureLod(iSampler, passageMatrix * iRay, iLod);
}

float	vFma(float a, float b, float c)
{
  return a*b+c;
}

vec2 vFma(vec2 a, vec2 b, vec2 c)
{
  return a*b+c;
}

vec3 vFma(vec3 a, vec3 b, vec3 c)
{
  return a*b+c;
}

vec4 vFma(vec4 a, vec4 b, vec4 c)
{
  return a*b+c;
}

mat4 vTranspose(in mat4 inMatrix)
{
  vec4 i0 = inMatrix[0];
  vec4 i1 = inMatrix[1];
  vec4 i2 = inMatrix[2];
  vec4 i3 = inMatrix[3];
  mat4 outMatrix = mat4(
    vec4(i0.x, i1.x, i2.x, i3.x),
    vec4(i0.y, i1.y, i2.y, i3.y),
    vec4(i0.z, i1.z, i2.z, i3.z),
    vec4(i0.w, i1.w, i2.w, i3.w));
  return outMatrix;
}

mat3 vTranspose(in mat3 inMatrix)
{
  vec3 i0 = inMatrix[0];
  vec3 i1 = inMatrix[1];
  vec3 i2 = inMatrix[2];
  mat3 outMatrix = mat3(
    vec3(i0.x, i1.x, i2.x),
    vec3(i0.y, i1.y, i2.y),
    vec3(i0.z, i1.z, i2.z));
  return outMatrix;
}

#endif // !GLES3Platform

#else // !GLES2Platform

/**************************************/
/********** GLSL ES SECTION **********/
/**************************************/

// Min/Max
int vMin(int x, int y)
{
  if (x<=y)
    return x;
  else
    return y;
}

float vMin(float x, float y)
{
  return min(x,y);
}

vec2 vMin(vec2 x, vec2 y)
{
  return min(x,y);
}

vec3 vMin(vec3 x, vec3 y)
{
  return min(x,y);
}

vec4 vMin(vec4 x, vec4 y)
{
  return min(x,y);
}

vec2 vMin(vec2 x, float y)
{
  return min(x,y);
}

vec3 vMin(vec3 x, float y)
{
  return min(x,y);
}

vec4 vMin(vec4 x, float y)
{
  return min(x,y);
}

int vMax(int x, int y)
{
  if (x>y)
    return x;
  else
    return y;
}

float vMax(float x, float y)
{
  return max(x,y);
}

vec2 vMax(vec2 x, vec2 y)
{
  return max(x,y);
}

vec3 vMax(vec3 x, vec3 y)
{
  return max(x,y);
}

vec4 vMax(vec4 x, vec4 y)
{
  return max(x,y);
}

vec2 vMax(vec2 x, float y)
{
  return max(x,y);
}

vec3 vMax(vec3 x, float y)
{
  return max(x,y);
}

vec4 vMax(vec4 x, float y)
{
  return max(x,y);
}

//function like macro is not working on ios
float	vFma(float a, float b, float c)
{
  return a*b+c;
}

vec2 vFma(vec2 a, vec2 b, vec2 c)
{
  return a*b+c;
}

vec3 vFma(vec3 a, vec3 b, vec3 c)
{
  return a*b+c;
}

vec4 vFma(vec4 a, vec4 b, vec4 c)
{
  return a*b+c;
}

mat4 vTranspose(in mat4 inMatrix)
{
  vec4 i0 = inMatrix[0];
  vec4 i1 = inMatrix[1];
  vec4 i2 = inMatrix[2];
  vec4 i3 = inMatrix[3];
  mat4 outMatrix = mat4(
    vec4(i0.x, i1.x, i2.x, i3.x),
    vec4(i0.y, i1.y, i2.y, i3.y),
    vec4(i0.z, i1.z, i2.z, i3.z),
    vec4(i0.w, i1.w, i2.w, i3.w));
  return outMatrix;
}

mat3 vTranspose(in mat3 inMatrix)
{
  vec3 i0 = inMatrix[0];
  vec3 i1 = inMatrix[1];
  vec3 i2 = inMatrix[2];
  mat3 outMatrix = mat3(
    vec3(i0.x, i1.x, i2.x),
    vec3(i0.y, i1.y, i2.y),
    vec3(i0.z, i1.z, i2.z));
  return outMatrix;
}

// WARNING: textureCubeLod, textureGrad, dFdx and dFdy are not in OpenGL ES 2.0 standards
// Should be available as standard on OpenGL ES 3.0
// Temporary dummy functions set to avoid shader compilation issue on mobile platforms without the required extension

#ifndef GL_OES_standard_derivatives
// Will provoke some errors in physical material computation!
vec2 dFdx(in vec2 iVec)
{
  return vec2(0.0);
}
vec2 dFdy(in vec2 iVec)
{
  return vec2(0.0);
}
#endif // GL_OES_standard_derivatives

#ifdef GL_EXT_shader_texture_lod
#define textureGrad texture2DGradEXT
#else // !GL_EXT_shader_texture_lod
// Will provoke some errors in physical material computation!
vec4 textureGrad(in sampler2D iTexture, in vec2 iP, in vec2 dPdx, in vec2 dPdy)
{
  return texture2D(iTexture, iP);
}
#endif // GL_EXT_shader_texture_lod


#ifdef VertexStage
// These functions are defined for VS in GLSL 4.4 but not allowed in VS in GLSL ES 2.0
// If they are used in a VS, this shader will raise a compilation error on those platforms
// We can activate following dummy functions if we wish to by-pass some compilation errors

vec4 vTextureLod(sampler2D iSampler, vec2 iCoord, float iLod)
{
  return vec4(0.0);
}

vec4 vTexture(sampler2D iSampler, vec2 iCoord, float iBias)
{
  return vec4(0.0);
}

vec4 vTexture(sampler2D iSampler, vec2 iCoord)
{
  return vec4(0.0);
}

vec4 vTexture(samplerCube iSampler, vec3 iCoord, float iBias)
{
  return vec4(0.0);
}

vec4 vTexture(samplerCube iSampler, vec3 iCoord)
{
  return vec4(0.0);
}

vec4 vTextureProj(sampler2D iSampler, vec3 iCoord, float iBias)
{
  return vec4(0.0);
}

vec4 vTextureProj(sampler2D iSampler, vec3 iCoord)
{
  return vec4(0.0);
}

vec4 vTextureProj(sampler2D iSampler, vec4 iCoord, float iBias)
{
  return vec4(0.0);
}

vec4 vTextureProj(sampler2D iSampler, vec4 iCoord)
{
  return vec4(0.0);
}

vec4 vTextureCubeLod(samplerCube sampler, vec3 coord, float lod)
{
  return vec4(0.0);
}

#ifdef ShadowMap
float vTextureProj(sampler2DShadow iSampler, vec4 iCoord)
{
  return 0.0;
}
#endif // ShadowMap

#endif // VertexStage

#ifdef FragmentStage
//these functions are defined for FS in GLSL 4.4 but not allowed in FS in GLSL ES 1.0
//if they are used in a FS, this shader will raise a compilation error on ogles 2 platforms

//Texture functions
//LOD version doesn't exist for fragment stage in GLSLES, so let's ignore LOD parameter :(
vec4 vTextureLod(sampler2D iSampler, vec2 iCoord, float iLod)
{
  return texture2D(iSampler,iCoord);
}

vec4 vTextureLod(samplerCube iSampler, vec3 iCoord, float iLod)
{
  return textureCube(iSampler,iCoord);
}

vec4 vTexture(sampler2D iSampler, vec2 iCoord, float iBias)
{
  return texture2D(iSampler,iCoord,iBias);
}

vec4 vTexture(sampler2D iSampler, vec2 iCoord)
{
  return texture2D(iSampler,iCoord);
}

vec4 vTexture(samplerCube iSampler, vec3 iCoord, float iBias)
{
  return textureCube(iSampler,iCoord,iBias);
}

vec4 vTexture(samplerCube iSampler, vec3 iCoord)
{
  return textureCube(iSampler,iCoord);
}

vec4 vTextureProj(sampler2D iSampler, vec3 iCoord, float iBias)
{
  return texture2DProj(iSampler,iCoord,iBias);
}

vec4 vTextureProj(sampler2D iSampler, vec3 iCoord)
{
  return texture2DProj(iSampler,iCoord);
}

vec4 vTextureProj(sampler2D iSampler, vec4 iCoord, float iBias)
{
  return texture2DProj(iSampler,iCoord,iBias);
}

vec4 vTextureProj(sampler2D iSampler, vec4 iCoord)
{
  return texture2DProj(iSampler,iCoord);
}

#ifdef ShadowMap
float vTextureProj(sampler2DShadow iSampler, vec4 iCoord)
{
  return shadow2DProjEXT(iSampler,iCoord);
}
#endif // ShadowMap

#ifdef GL_EXT_shader_texture_lod
#define vTextureCubeLod textureCubeLodEXT
#else // GL_EXT_shader_texture_lod
// Will provoke some errors in lighting computation!
vec4 vTextureCubeLod(samplerCube sampler, vec3 coord, float lod)
{
  return textureCube(sampler, coord);
}
#endif // GL_EXT_shader_texture_lod

vec4 vTextureCubeMap(samplerCube iSampler, vec3 iRay)
{
  const mat3 passageMatrix = mat3(0.0,  0.0, -1.0,
                                  1.0,  0.0,  0.0,
                                  0.0, -1.0,  0.0);
  return vTexture(iSampler, passageMatrix * iRay);
}

vec4 vTextureCubeMapLod(samplerCube iSampler, vec3 iRay, float iLod)
{
  const mat3 passageMatrix = mat3(0.0,  0.0, -1.0,
                                  1.0,  0.0,  0.0,
                                  0.0, -1.0,  0.0);
  return vTextureLod(iSampler, passageMatrix * iRay, iLod);
}

#endif // FragmentStage


#endif // // !GLES2Platform

// Common or not yet reimplemented intrisics redefinitions.
// Order based on OpenGL 4.4 API Reference Card : https://www.khronos.org/files/opengl44-quick-reference-card.pdf
// Thanks to follow that order for further versions.

//Angle & Trig. functions
#define vRadians	radians 

#define vDegrees	degrees 
#define vSin		sin		
#define vCos		cos		
#define vTan		tan		
#define vAsin		asin	
#define vAcos		acos	
#define vAtan		atan		
#define vSinh		sinh	
#define vCosh		cosh	
#define vTanh		tanh	
#define vAsinh		asinh	
#define vAtanh		atanh	

//Exponential functions
#define	vPow			pow			
#define	vExp			exp			
#define	vLog			log			
#define	vExp2			exp2		
#define	vLog2			log2		
#define	vSqrt			sqrt		
#define	vInversesqrt	inversesqrt 

//Common functions
#define	vAbs		abs				

//fl9 : sign is badly implemented and in most of the case we do not care about the zero case
#define	vSign		sign			
float vSignf(float iValue) 
{
  return ((iValue>=0.)?1.:-1.);
}

int vSigni(int iValue) 
{
  return ((iValue>=0)?1:-1);
}

#define	vFloor		floor			
#define	vTrunc		trunc			
#define	vRound		round			
#define	vRoundEven	roundEven		
#define	vCeil		ceil			
#define	vFract		fract			
#define	vMod		mod				
#define	vModf		modf			
//#define	 vMin		min		** specialized	**
//#define	 vMax		max		** specialized	**	
#define	vClamp		clamp			
#define	vMix		mix				
#define	vStep		step			
#define	vSmoothstep smoothstep		
#define	vIsnan		isnan			
#define	vIsinf		isinf			
#define	vFloatBitsToInt		floatBitsToInt	
#define	vFloatBitsToUint	floatBitsToUint 
#define	vIntBitsToFloat		intBitsToFloat  
#define	vUintBitsToFloat	uintBitsToFloat 			
#define	vFrexp		frexp			
#define	vLdexp		ldexp			

//Floating point pack/unpack
#define	vPackUnorm2x16		packUnorm2x16		
#define	vPackSnorm2x16		packSnorm2x16		
#define	vPackUnorm4x8		packUnorm4x8		
#define	vPackSnorm4x8		packSnorm4x8		
#define	vUnpackUnorm2x16	unpackUnorm2x16		
#define	vUnpackSnorm2x16	unpackSnorm2x16		
#define	vUnpackUnorm4x8		unpackUnorm4x8		
#define	vUnpackSnorm4x8		unpackSnorm4x8		
#define	vPackDouble2x32		packDouble2x32		
#define	vUnpackDouble2x32	unpackDouble2x32	
#define	vPackHalf2x16		packHalf2x16		

//Geometric functions
#define	vLength			length		
#define	vDistance		distance	
#define	vDot			dot			
#define	vCross			cross		
#define	vNormalize		normalize	
#define	vFaceforward	faceforward	
#define	vReflect		reflect		
#define	vRefract		refract		

//Vector relational functions
#define	vLessThan			lessThan			
#define	vLessThanEqual		lessThanEqual		
#define	vGreaterThan		greaterThan			
#define	vGreaterThanEqual	greaterThanEqual	
#define	vEqual				equal				
#define	vNotEqual			notEqual			
#define	vAny				any					
#define	vAll				all					
#define	vNot				not					

//Integer functions
#define	vUaddCarry			uaddCarry			
#define	vUsubBorrow			usubBorrow			
#define	vUmulExtended		umulExtended		
#define	vImulExtended		imulExtended		
#define	vBitFieldExtract	bitfieldExtract		
#define	vBitFieldReverse	bitfieldReverse		
#define	vBitFieldInverse	bitfieldInverse		
#define	vBitCount			bitCount			
#define	vFindLSB			findLSB				
#define	vFindMSB			findMSB				

//Atomic-counter functions
#define vAtomicCounterIncrement atomicCounterIncrement	
#define vatomicCounterDecrement atomicCounterDecrement	
#define vAtomicCounter			atomicCounter			

//Atomic memory functions
#define	vAtomicOP atomicOP	

//Image functions
#define	vImageSize				imageSize			
#define	vImageLoad				imageLoad			
#define	vImageStore				imageStore			
#define	vImageAtomicAdd			imageAtomicAdd		
#define	vImageAtomicMin			imageAtomicMin		
#define	vImageAtomicMax			imageAtomicMax		
#define	vImageAtomicAnd			imageAtomicAnd		
#define	vImageAtomicOr			imageAtomicOr		
#define	vImageAtomicXor			imageAtomicXor		
#define	vImageAtomicExchange	imageAtomicExchange	
#define	vImageAtomicCompSwap	imageAtomicCompSwap	

//Fragment processing functions
#ifdef RayHitStage
  vec2 vDFdx(in vec2 iVec)
  {
    return vec2(0.0);
  }

  vec3 vDFdx(in vec3 iVec)
  {
    return vec3(0.0);
  }

  vec2 vDFdy(in vec2 iVec)
  {
    return vec2(0.0);
  }

  vec3 vDFdy(in vec3 iVec)
  {
    return vec3(0.0);
  }
#else
#define	vDFdx					dFdx					
#define	vDFdy					dFdy					
#define	vFwidth					fwidth					
#define	vInterpolateAtCentroid	interpolateAtCentroid	
#define	vInterpolateAtSample	interpolateAtSample		
#define	vInterpolateAtOffset	interpolateAtOffset		
#endif

//Noise functions
#define vNoise1	noise1
#define vNoisen	noisen

//Geometry shader functions
#define	vEmitStreamVertex	EmitStreamVertex	
#define	vEndStreamPrimitive EndStreamPrimitive	
#define	vEmitVertex			EmitVertex			
#define	vEndPrimitive		EndPrimitve			

//Other shader functions
#define	vBarrier					barrier						
#define	vMemoryBarrier				memoryBarrier				
#define	vGroupMemoryBarrier			groupMemoryBarrier			
#define	vMemoryBarrierAtomicCounter memoryBarrierAtomicCounter	
#define	vMemoryBarrierShared		memoryBarrierShared			
#define	vMemoryBarrierBuffer		memoryBarrierBuffer			
#define	vMemoryBarrierImage			memoryBarrierImage			

//Texture query functions
#define	vTextureSize			textureSize				
#define	vTextureQueryLoad		textureQueryLoad		
#define	vTextureQueryLevels		textureQueryLevels		
//#define	vTexture				texture			** specialized in VS/FS	specifics**
//#define	vTextureProj			textureProj		** specialized in VS/FS	specifics	**
//#define	vTextureLod				textureLod		** specialized in VS/FS	specifics	**
#define	vTextureOffset			textureOffset			
#define	vTexelFetch				texelFetch				
#define	vTexelFetchOffset		texelFetchOffset		
#define	vTextureProjOffset		textureProjOffset		
#define	vTextureLodOffset		textureLodOffset		
//#define	vTextureProjLod			textureProjLod	** specialized in VS/FS	specifics	**	
#define	vTextureProjLodOffset	textureProjLodOffset	
#define	vTextureGrad			textureGrad				
#define	vTextureGradOffset		textureGradOffset		
#define	vTextureProjGrad		textureProjGrad			
#define	vTextureProjGradOffset	textureProjGradOffset	
#define	vTextureGather			textureGather			
#define	vTextureGatherOffset	textureGatherOffset		
#define	vTextureGatherOffsets	textureGatherOffsets	

//Built-in variables
//Vertex language
#ifdef VertexStage
#ifndef GLES2Platform
int vGetVertexID()
{
  return gl_VertexID;
}

int vGetInstanceID()
{
  return gl_InstanceID;
}
#endif

#if !defined(GLESPlatform) && defined(Supports_GL_ARB_shader_draw_parameters) // gf8: have to verify this, but spec says its core in 4.3
int vGetDrawID()
{
  return gl_DrawIDARB;
}

int vGetBaseInstance()
{
  return gl_BaseInstanceARB;
}

int vGetBaseVertex()
{
  return gl_BaseVertexARB;
}
#endif
#endif // VertexStage

//Fragment language
#if defined(FragmentStage) || defined(RayHitStage)
#ifndef GLES2Platform
void vSetFragDepth(in float iDepth)
{
#ifdef RayHitStage
  //?
#else
  gl_FragDepth = iDepth;
#endif
}
#endif

#if !defined(GLESPlatform) && (GLSLVersion >= 400)
// Only exists in OpenGL ES 3.2 which is currently not integrated
int vGetSampleID()
{
#ifdef RayHitStage
  return 0;
#else
  return gl_SampleID;
#endif
}

vec2 vGetSamplePosition()
{
#ifdef RayHitStage
  return vec2(0.5);
#else
  return gl_SamplePosition;
#endif
}

int vGetPrimitiveID()
{
  return gl_PrimitiveID;
}
#endif

vec4 vGetFragCoord()
{
#ifdef RayHitStage
  return vec4(0.0);
#else
  return gl_FragCoord;
#endif
}

bool vIsFrontFacing()
{
#ifdef RayHitStage
  return gl_HitKindEXT == gl_HitKindFrontFacingTriangleEXT;
#else
  return gl_FrontFacing;
#endif
}

vec2 vGetPointCoord()
{
#ifdef RayHitStage
  return vec2(0.0);
#else
  return gl_PointCoord;
#endif
}
#endif // FragmentStage

// Multiview single pass
#if defined(MultiviewSinglePass) && (MultiviewSinglePass > 1)

#if defined(VertexStage) || defined(GeometryStage) || defined(TessControlStage) || defined(TessEvaluationStage)
layout(num_views = MultiviewSinglePass) in;
#endif

uint vGetViewID()
{
  return gl_ViewID_OVR;
}

uint vGetViewsCount()
{
  return MultiviewSinglePass;
}

#else

#undef MultiviewSinglePass

uint vGetViewID()
{
  return uint(0);
}

uint vGetViewsCount()
{
  return uint(1);
}

#endif

// Compute language
#ifdef ComputeStage
uvec3 vGetNumWorkGroups()
{
  return gl_NumWorkGroups;
}

uvec3 vGetWorkGroupID()
{
  return gl_WorkGroupID;
}

uvec3 vGetLocalInvocationID()
{
  return gl_LocalInvocationID;
}

uvec3 vGetGlobalInvocationID()
{
  return gl_GlobalInvocationID;
}

uint vGetLocalInvocationIndex()
{
  return gl_LocalInvocationIndex;
}
#endif // ComputeStage

#ifdef RaygenStage

uvec3 vGetLaunchID()
{
  return gl_LaunchIDEXT;
}

uvec3 vGetLaunchSize()
{
  return gl_LaunchSizeEXT;
}
#endif

#ifdef ClosestHitStage
  int vGetInstanceID()
  {
    return gl_InstanceID;
  }

  int vGetInstanceCustomIndex()
  {
    return gl_InstanceCustomIndexEXT;
  }

  mat4x3 vGetObjectToWorld()
  {
    return gl_ObjectToWorldEXT;
  }

  mat4x3 vGetWorldToObject()
  {
    return gl_WorldToObjectEXT;
  }

  #define V_GET_TEXTURE_2D(x)         (GlobalTextures2D[nonuniformEXT(x)])
  //#define V_GET_TEXTURE_2D_ARRAY(x)   (GlobalTextures2DArray[nonuniformEXT(x)])
  //#define V_GET_TEXTURE_CUBE(x)       (GlobalTexturesCube[nonuniformEXT(x)])
  //#define V_GET_TEXTURE_CUBE_ARRAY(x) (GlobalTexturesCubeArray[nonuniformEXT(x)])
#else
  #define V_GET_TEXTURE_2D(x)         (x)
  //#define V_GET_TEXTURE_2D_ARRAY(x)   (x)
  //#define V_GET_TEXTURE_CUBE(x)       (x)
  //#define V_GET_TEXTURE_CUBE_ARRAY(x) (x)
#endif
