#ifndef GLES2Platform
layout (location = 0) out vec4 fragColor;
#ifdef OutputGPUPicking
  layout(location = 1) out uint gpuPickingMap;
#endif //OutputGPUPicking

#else
#define fragColor gl_FragColor
#endif

#ifdef VID_TEXTURE_ARRAY 
#ifndef STEREO_MODE
#define STEREO_MODE 0
#endif
//uniform sampler2DArray vidTexture;
#else
//uniform sampler2D vidTexture;
#endif

//uniform sampler2D vidFreeTypeTexture;


void main()
{
#if defined(OutputGPUPicking)
  gpuPickingMap = GetGPUPickingID();
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif

  vec4 finalColor = vFrontColor;
  vec4 texelValue = vec4(1,0,0,1);

  if(cb_cbVidMaterial.u_TexturingOnOff > 0)
  {
    // Both textures are sampled outside the following condition
    // Required to avoid Apple shader compiler crash on iPad Air 2 with iOS 9
#ifdef VID_TEXTURE_ARRAY
    texelValue = vTexture(vidTexture, vec3(vTexCoord.xy, STEREO_MODE));
#else
    texelValue = vTexture(vidTexture, vTexCoord.xy);
#endif
    float mask = vTexture(vidFreeTypeTexture,vTexCoord.xy).r;

    if(vUsingFreeTypeTexture < 0.5)
    {
      texelValue.a = vMix(1.0, texelValue.a, float(cb_cbVidMaterial.u_TextureAlphaOnOff));
      finalColor = texelValue * finalColor;
    }
    else
    {
      mask = vPow(mask, cb_cbVidMaterial.u_Gamma);
      finalColor.a *= mask;
    }
  }

  fragColor = finalColor;

#ifdef LogDepth
  float projPos = -vGetViewPosPostTransform().z;
  float depth = ComputeLogDepth(projPos);
  vSetFragDepth(depth);
#endif
}
