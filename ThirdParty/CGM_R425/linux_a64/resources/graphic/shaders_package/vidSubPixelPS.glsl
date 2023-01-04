#ifdef VID_TEXTURE_ARRAY 
#ifndef STEREO_MODE
#define STEREO_MODE 0
#endif
//uniform sampler2DArray vidTexture;
#else
//uniform sampler2D vidTexture;
#endif
//uniform sampler2D vidFreeTypeTexture;


layout (location = 0) out vec4 oFragColor0;

#ifdef OutputGPUPicking
    layout(location = 1) out uint gpuPickingMap;
#else
    layout (location = 1) out vec4 oFragColor1;
#endif //OutputGPUPicking

vec3 GammaCorrect(in vec3 iColor, in float iGamma);
vec4 GammaCorrect(in vec4 iColor, in float iGamma);
vec4 SubpixelFilter(in vec2 iTexCoord, in sampler2D iFreeTypeTextureUnit, in mat4 iFilterWeights);


void main()
{
  vec4 finalColor0 = vFrontColor; 
  vec4 finalColor1 = vec4(vFrontColor.a);

  if(cb_cbVidMaterial.u_TexturingOnOff > 0)
  {
    if(vUsingFreeTypeTexture < 0.5)
    {
#ifdef VID_TEXTURE_ARRAY
      vec4 texelValue = vTexture(vidTexture, vec3(vTexCoord.xy, STEREO_MODE));
#else
      vec4 texelValue = vTexture(vidTexture, vTexCoord.xy);
#endif
      texelValue.a = vMix(1.0, texelValue.a, float(cb_cbVidMaterial.u_TextureAlphaOnOff));
      finalColor0 *= texelValue;
      finalColor1 *= texelValue.a;
    }
    else
    {
      //subpixel text
      vec4 alpha4 = SubpixelFilter(vTexCoord.xy, vidFreeTypeTexture, cb_cbVidMaterial.u_LcdFilter);
      
      finalColor0.a *= alpha4.a;
      finalColor1 = alpha4 * vFrontColor.a;

      finalColor0.rgb = GammaCorrect(finalColor0.rgb, cb_cbVidMaterial.u_Gamma);
      finalColor1.rgb = GammaCorrect(finalColor1.rgb, cb_cbVidMaterial.u_Gamma);

    }
  }

  oFragColor0 = finalColor0;

#if defined(OutputGPUPicking)
  gpuPickingMap = GetGPUPickingID();
#else
  oFragColor1 = finalColor1;
#endif

#ifdef OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif

#ifdef LogDepth
  float projPos = -vGetViewPosPostTransform().z;
  float depth = ComputeLogDepth(projPos);
  vSetFragDepth(depth);
#endif
}


vec3 GammaCorrect(in vec3 iColor, in float iGamma)
{
  return pow(iColor, vec3(iGamma));
}

vec4 GammaCorrect(in vec4 iColor, in float iGamma)
{
  return pow(iColor, vec4(iGamma));
}

vec4 SubpixelFilter(in vec2 iTexCoord, in sampler2D iFreeTypeTextureUnit, in mat4 iFilterWeights)
{
  // subpixel sampling from a 3x resolution alpha texture w optional filtering
	// sample 3 subpixel values
 	vec4 alpha;
	alpha.r = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(-1,0)).r;
	alpha.g = vTexture(iFreeTypeTextureUnit, iTexCoord).r; 
	alpha.b = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(1,0)).r; 
	
	// sample adjacent texels for inter pixel filtering
	float rp = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(-2,0)).r; 
	float bn = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(2,0)).r;
	
	// sample further subpixels for 5-tap filtering
	float rpp = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(-3,0)).r;
	float bnn = vTextureOffset(iFreeTypeTextureUnit, iTexCoord, ivec2(3,0)).r;
	
	// first order filtering
	vec4 alpha4;

	alpha4.r = vDot(vec3(alpha.r, rp, alpha.g), iFilterWeights[0].xyz) + vDot(vec2(rpp,alpha.b),iFilterWeights[0].ww);
	alpha4.g = vDot(vec3(alpha.g, alpha.r, alpha.b), iFilterWeights[1].xyz) + vDot(vec2(rp,bn),iFilterWeights[1].ww);
	alpha4.b = vDot(vec3(alpha.b, alpha.g, bn), iFilterWeights[2].xyz) + vDot(vec2(alpha.r,bnn),iFilterWeights[2].ww);
	
	// an average alpha value for the cases when we need to preserve dst alpha
	// e.g. when being rendered onto a texture for blending
	// which means that there won't be per channel alpha blending
	alpha4.a = (alpha.r + alpha.g + alpha.b) / 3.0;
		
	return alpha4;
}
