#ifndef GLES2Platform
  layout(location = 0) out vec4 fragColor;
#endif
#ifdef OutputGPUPicking
  layout(location = 1) out uint gpuPickingMap;
#endif

#ifndef GLES2Platform
  #define FRAGCOLOR fragColor
#else
  #define FRAGCOLOR gl_FragColor
#endif

vec4 gammaCorrectAlphaBlend(vec4 color, float alpha, float gamma)
{
	// approximates gamma correction with alpha blending
	// c = cs*a + cd*(1-a)
	// c = pow(c, 1/gamma)
	// we do am approximate alpha blend in gamma space with
	// preserving destination alpha for the cases where the 
	// text gets drawn onto an alpha texture
	// cf ~= (cs*a)^1/g + cd*(1-a)^1/g
	// af ~= as*as + ad*(1-as)
	vec4 res;
	res.rgb	= color.rgb*color.a*alpha;
	res.rgb = pow(res.rgb, vec3(1.0/gamma));
	
	// aproximate (1-a)^(1/g) by 1 - (1/g)a
	res.a = color.a*alpha/gamma;

	// blend with (1,1-a)
	return res;
}

void main()
{
#if defined(HighlightAdvanced) 
  discard;
#endif
  float alpha = vTexture(atlasTexture, vTexCoord.xy).r;

  FRAGCOLOR = gammaCorrectAlphaBlend(cb_cbText_2D.u_Color, alpha, cb_cbText_2D.u_Gamma);

#ifdef OutputGPUPicking
	gpuPickingMap = GetGPUPickingID();
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif
}
