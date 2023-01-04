//---------------------------------------------
// IBL
//#ifdef ImageBasedLighting
//  uniform samplerCube IBLDiffuseTexture;
//  uniform samplerCube IBLSpecularTexture;
//#endif

//---------------------------------------------
// Mirror
#if defined (GROUND_MIRRORING)

  vec4 GetGroundMirrorColor(const vec3 iWorldNormal)
  {
  #ifdef MultiviewSinglePass
    ivec3 tsize = vTextureSize(mirrorMapTex, 0);
    vec3 texCoord = vec3(gl_FragCoord.x / float(tsize.x), gl_FragCoord.y / float(tsize.y), float(vGetViewID()));
  #else
    ivec2 tsize = vTextureSize(mirrorMapTex, 0);
    vec2 texCoord = vec2(gl_FragCoord.x / float(tsize.x), gl_FragCoord.y / float(tsize.y));
  #endif

    texCoord.xy *= cb_Ground.u_MirrorScaleFactor;
    texCoord.xy += ComputeMirrorDeviationFromNormal(iWorldNormal);
    return vTexture(mirrorMapTex, texCoord);
  }

  vec4 GetGroundMirrorColor()
  {
  #ifdef MultiviewSinglePass
    ivec3 tsize = vTextureSize(mirrorMapTex, 0);
    vec3 textCoord = vec3(gl_FragCoord.x/float(tsize.x), gl_FragCoord.y/float(tsize.y), float(vGetViewID()));
  #else
    ivec2 tsize = vTextureSize(mirrorMapTex, 0);
    vec2 textCoord = vec2(gl_FragCoord.x/float(tsize.x), gl_FragCoord.y/float(tsize.y));
  #endif

    textCoord.xy *= cb_Ground.u_MirrorScaleFactor;
    return vTexture(mirrorMapTex, textCoord);
  }
#endif 

//---------------------------------------------
// color

layout(location = 0) out vec4 fragColor;
#define FRAGCOLOR fragColor
  
#ifdef SO_MRT_LOCATION_FRAGDEPTHWA
  layout(location = SO_MRT_LOCATION_FRAGDEPTHWA) out vec4 fragDepthWA;
#endif
  
#ifdef SO_MRT_LOCATION_FRAGNORMAL
  layout(location = SO_MRT_LOCATION_FRAGNORMAL) out vec4 fragNormal;
  #define FRAGNORMAL fragNormal
#endif
  
#ifdef SO_MRT_LOCATION_FRAGIBLREFL
  layout(location = SO_MRT_LOCATION_FRAGIBLREFL) out vec4 fragIBLRefl;
  #define FRAGREFLECT fragIBLRefl
#endif
  
#ifdef SO_MRT_LOCATION_FRAGF0ROUGH
  layout(location = SO_MRT_LOCATION_FRAGF0ROUGH) out vec4 fragF0Rough;
  #define FRAGMATPROP fragF0Rough
#endif
  
#ifdef SO_MRT_LOCATION_FRAGUV
  layout(location = SO_MRT_LOCATION_FRAGUV) out vec2 fragUV;
#endif
  
#ifdef SO_MRT_LOCATION_FRAGWORLDPOS
  layout(location = SO_MRT_LOCATION_FRAGWORLDPOS) out uvec4 fragWorldPos;
#endif
  
#ifdef SO_MRT_LOCATION_GBUFFERADDITIONALDATA
  layout(location = SO_MRT_LOCATION_GBUFFERADDITIONALDATA) out float fragGBufferAdditionalData;
#endif
  
#ifdef SO_MRT_LOCATION_FRAGMOTIONVECTOR
  layout(location = SO_MRT_LOCATION_FRAGMOTIONVECTOR) out vec2 fragMotionVector;
#endif
  
