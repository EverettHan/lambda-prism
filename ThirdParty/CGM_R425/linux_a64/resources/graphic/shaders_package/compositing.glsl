// Update the color with lowlight
vec3 DoLowlighting(in vec3 iColor)
{
  float coef = 0.55; // arbitrary coefficient to give a darker look when lowlight is activated

#ifdef LowLight_Black // Mode specific for ODT snapshot to be compliant with ORE behavior
  #ifndef Lighting
  coef = 0.0;
  #endif
#endif

  return iColor * coef;
}

#ifdef Lighting

  #if defined(FragmentStage) || defined(RayHitStage)
      // Compute the data for the standard lighting
      LightingData ComputeStdLightingData(in vec3 iP, in vec3 iN, in vec3 iView)
      {
        LightingData data;
        data.P = iP;
        data.N = iN;
        data.V = iView;
        data.visibility = 1.0;
        data.minVisibility = 0.0;

        return data;
      }

      // Fragment lighting compositing
      vec4 DoFragmentLightingCompositing(inout LightingData data, in BRDFParameters brdf, out vec3 iblSpecContrib, out vec3 iFresnel)
      {
        LightingResult localRadiance = DoStdLighting(data, brdf);
        iFresnel = localRadiance.fresnel;

        vec3 finalColor = localRadiance.radiance;
      #ifdef EVisuPBR
        float finalAlpha = localRadiance.alpha;
      #else
        float finalAlpha = 1.0 - localRadiance.transparency;
      #endif

        data.lightID = 0;

        #ifdef ImageBasedLighting
          vec3 iblDiffuseContrib = vec3(0.0);
          vec3 iblTotalContrib = ComputeIBL(data, brdf, iblSpecContrib, iblDiffuseContrib);
          vec3 iblContrib = iblTotalContrib;


          #if defined(SO_HRTAO_ENABLE_AO) && !defined(RayHitStage)
            #ifdef SO_HRTAO_ENABLE_AO_IBL
              #define AO_TYPE vec3
              #define AO_INIT 0.0
            #else
              #define AO_TYPE float
              #define AO_INIT 1.0
            #endif

            AO_TYPE ao = AO_TYPE(AO_INIT);

            #ifdef SO_HRTAO_AS_ARRAY
              ivec3 hrtaoCoords = ivec3(gl_FragCoord.xy, 0);
            #else
              ivec2 hrtaoCoords = ivec2(gl_FragCoord.xy);
            #endif

            #ifdef IS_MSAA
              ao = AO_TYPE(vTexelFetch(RTAOOutput, hrtaoCoords, gl_SampleID));
            #else
              ao = AO_TYPE(vTexelFetch(RTAOOutput, hrtaoCoords, 0));
            #endif

            #ifdef SO_HRTAO_ENABLE_AO_IBL
              // in this mode AO is actually the irradiance
              // (similar to the prefiltered diffuse IBL)
              // We compute the diffuse BRDF from that

              #ifndef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
                //**HACK ALERT**
                //The Cyril Ratio™: we compute the ratio of raytraced diffuse (which has shadows) vs prefiltered diffuse (which doesn't have shadows)
                //This produces a value reprenting only the "shadowy" parts of the diffuse ibl, which we use to dim the specular contrib (not raytraced in this mode)
                const vec3 coefL = vec3(0.2126, 0.7152, 0.0722);
                float aoL = dot(coefL, ao);

                float iblDiffuseContribL = dot(coefL, iblDiffuseContrib);
                float visibilityRatio = aoL / iblDiffuseContribL;
              #else
                //cut the precomputed specular IBL entirely, replace it with the raytraced version (which has shadows)
                #ifdef IS_MSAA
                  iblSpecContrib = AO_TYPE(vTexelFetch(RTAOGlossyOutput, hrtaoCoords, gl_SampleID));
                #else
                  iblSpecContrib = AO_TYPE(vTexelFetch(RTAOGlossyOutput, hrtaoCoords, 0));
                #endif

                //Cyril Ratio not required
                float visibilityRatio = 1.0;

              #endif

              #ifdef EVisuPBR
                fresnel_dielectric_parameters params;
                params.specularTint = brdf.specularTint;
                params.ior = brdf.ior;
                params.albedo = brdf.albedo;
                params.specular = brdf.specular;
                params.metallic = brdf.metallic;

                const float NoV = max(0.0, dot(data.Nworld, data.Vworld));

                const vec3 F = fresnel_dielectric(params, NoV);
            
                float sheenDiffuseWeight = 1.0;

                #if defined(EVisuPBR) && defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver19x)
                  sheenDiffuseWeight = vPow5(1.0 - brdf.sheen);
                #endif

                vec3 rho_d = brdf.albedo * (1.0 - brdf.metallic) * (1.0 - brdf.transparency) * sheenDiffuseWeight;
                vec3 diffuse = (vec3(1.0) - F) * rho_d * ao;
              #else
                #ifdef XRiteCarPaint2
                  // not implemented
                  vec3 diffuse = vec3(0.0, 0.0, 0.0);
                #else
                  vec3 diffuse = brdf.albedo * ao;
                 #endif
              #endif // EVisuPBR

              iblContrib = iblSpecContrib*visibilityRatio + diffuse;
            #else
              iblContrib *= ao;
            #endif // SO_HRTAO_ENABLE_AO_IBL

          #endif //SO_HRTAO_ENABLE_AO

          finalColor += iblContrib;
        #endif //ImageBasedLighting

        #ifdef LightMap
          #if (LightMap == LightMapIlluminanceMode)
            finalColor += brdf.albedo * vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz;
          #elif (LightMap == LightMapLuminosityMode)
            finalColor *= vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz;
          #endif
        #endif

        #ifndef XRiteCarPaint2
        #ifdef LegacyGlobalIllumination
          finalColor += brdf.albedo * _vPrivGetAmbientColor();;
        #endif
        #endif // XRiteCarPaint2

        #if !defined(PDSFX1) || defined(_PDSFX1_FS_Emissive)
          finalColor += ComputeEmissive();
        #endif

        #ifdef SO_EVISUPBR_SUBSURFACE
          finalColor += localRadiance.translucency;
        #endif

        #ifdef EVisuPBR
          if(finalAlpha > 0.0)
            finalColor /= finalAlpha;
        #endif

        #if defined(SO_REFLECTIONS) && !defined(RayHitStage)
          if(brdf.roughness <= 0.13)
          {
            #ifdef IS_MSAA
              vec4 reflections = vTexelFetch(reflectionsOutput, ivec2(gl_FragCoord.xy), gl_SampleID);
            #else
              vec4 reflections = vTexelFetch(reflectionsOutput, ivec2(gl_FragCoord.xy), 0);
            #endif

            vec3 diff = finalColor - iblSpecContrib;

            data.L = normalize(reflect(-data.V, data.N));
            data.irradiance = vec3(reflections);
            ComputeRenderingEquation(data, brdf, localRadiance);

            #ifdef EVisuPBR
              fresnel_dielectric_parameters params;
	            fresnel_dielectric_init(params, brdf.albedo, brdf.ior, brdf.specularTint, brdf.specular, brdf.metallic);
          
              const float NoV = max(0.0, dot(data.N, data.V));
          
              vec3 F = fresnel_dielectric(params, NoV);
            #else
              const float NoV = max(0.0, dot(data.Nworld, data.Vworld));

	            const vec3 F = OptimizedSchlickFresnel(brdf.f0, brdf.f90, NoV);
            #endif

            vec3 reflCol = vec3(reflections) * F;

            finalColor = mix(finalColor, diff+reflCol, reflections.w);
          }
        #endif
        

        return vec4(finalColor, finalAlpha);
      }

  #endif // FragmentStage
#endif // Lighting
