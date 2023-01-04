layout(location = 0, index = 0) out vec4 fragColor;
layout(location = 0, index = 1) out vec4 srcColor1;

vec3 GammaCorrect(vec3 color, float gamma)
{
  return vPow(color, vec3(gamma));
}

vec4 SubpixelFilter(vec2 texcoord, sampler2D tex, mat4 filterWeights)
{
  vec4 alpha;

  alpha.r = vTextureOffset(tex, texcoord, ivec2(-1,0)).r;
  alpha.g = vTexture(tex, texcoord).r; 
  alpha.b = vTextureOffset(tex, texcoord, ivec2(1,0)).r; 
  
  float rp = vTextureOffset(tex, texcoord, ivec2(-2,0)).r; 
  float bn = vTextureOffset(tex, texcoord, ivec2(2,0)).r;
  
  float rpp = vTextureOffset(tex, texcoord, ivec2(-3,0)).r;
  float bnn = vTextureOffset(tex, texcoord, ivec2(3,0)).r;
  
  vec4 alpha4;

  alpha4.r = vDot(vec3(alpha.r, rp,      alpha.g), filterWeights[0].xyy) + vDot(vec2(rpp,    alpha.b), filterWeights[0].zz);
  alpha4.g = vDot(vec3(alpha.g, alpha.r, alpha.b), filterWeights[1].xyy) + vDot(vec2(rp,     bn),      filterWeights[1].zz);
  alpha4.b = vDot(vec3(alpha.b, alpha.g, bn),      filterWeights[2].xyy) + vDot(vec2(alpha.r,bnn),     filterWeights[2].zz);
  
  alpha4.a = (alpha.r + alpha.g + alpha.b) / 3.0;
  	
  return alpha4;
}

void main()
{
#if defined(HighlightAdvanced) 
  discard;
#endif
  vec4 scolor0;
  vec4 scolor1;

	vec4 alpha4 = SubpixelFilter(vTexCoord.xy, atlasTexture, cb_cbText_2D_Subpixel.u_Filter);

	scolor0 = vec4(cb_cbText_2D_Subpixel.u_Color.rgb,            cb_cbText_2D_Subpixel.u_Color.a * alpha4.a);
	scolor1 = vec4(alpha4.rgb * cb_cbText_2D_Subpixel.u_Color.a, cb_cbText_2D_Subpixel.u_Color.a * alpha4.a);

	scolor0.rgb = GammaCorrect(scolor0.rgb, cb_cbText_2D_Subpixel.u_Gamma);
	scolor1.rgb = GammaCorrect(scolor1.rgb, cb_cbText_2D_Subpixel.u_Gamma);

  fragColor = scolor0;
  srcColor1 = scolor1;

#if defined(OutputGPUPickingImage)
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif
}
