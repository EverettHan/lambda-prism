#version 130
// single shader for cid widgets and subpixel text rendering
// shader output:
// SrcColor0 = [ Crgb, Ca*Ma ]
// SrcColor1 = [ Mrgb*Ca, Ca*Ma ]
// for subpixel rendering, it requires a dual source blend function + separate color/alpha blend
// SrcBlend = (SrcColor1, 1)
// DstBlend = (1 - src1)
// for render to texture, blend function = (1,1) (fake grayscale)
uniform sampler2D u_textureUnit;
uniform sampler2D u_freeTypeTextureUnit;
uniform int       u_texturing2DEnable;
uniform int       u_alphaTexturing2DEnable;

// text rendering parameters
uniform float u_gamma = 1.0;
uniform mat3 u_lcdFilter = mat3(1.0/3.0, 2.0/9.0, 1.0/9.0,
						   1.0/3.0, 2.0/9.0, 1.0/9.0,
						   1.0/3.0, 2.0/9.0, 1.0/9.0);
// interpolated inputs						   
in vec4 v_frontcolor;
in vec2 v_texcoord;
in float v_usingFreeTypeTexture;
// two outputs for dual source blending
out vec4 oFragColor0;
out vec4 oFragColor1;
			
vec3 gammaCorrect(in vec3 color, in float gamma);
vec4 gammaCorrect(in vec4 color, in float gamma);
vec4 subpixelFilter(in vec2 texcoord, in sampler2D u_freeTypeTextureUnit, in mat3 filterWeights);

void main()
{
  // untextured output - the second color is just alpha splattered
  vec4 scolor0 = vec4(v_frontcolor.rgb, v_frontcolor.a);
  vec4 scolor1 = vec4(v_frontcolor.a);
  
  if(u_texturing2DEnable > 0)
  {
	if (v_usingFreeTypeTexture < 0.5)
	{

		// textured widget
		vec4 texelValue = texture2D(u_textureUnit, v_texcoord.xy);
    if (u_alphaTexturing2DEnable == 0)
    {
      texelValue.a=1.0;
    }

		scolor0 *= texelValue;
		scolor1 *= texelValue.a;
	}
	else
	{
    // subpixel text
		// obtain filtered alpha values from the texture
		vec4 alpha4 = subpixelFilter(v_texcoord.xy, u_freeTypeTextureUnit, u_lcdFilter);
		scolor0.a *= alpha4.a;
		scolor1 = alpha4 * v_frontcolor.a;
		scolor0.rgb = gammaCorrect(scolor0.rgb, u_gamma);
		scolor1.rgb = gammaCorrect(scolor1.rgb, u_gamma);
    	}
  }
  
  // output two colors for the dual source blending
  oFragColor0 = scolor0;
  oFragColor1 = scolor1;
}
 
vec3 gammaCorrect(vec3 color, float gamma)
{
	return pow(color, vec3(gamma));
}

 vec4 gammaCorrect(vec4 color, float gamma)
{
	return pow(color, vec4(gamma));
}

vec4 subpixelFilter(vec2 texcoord, sampler2D u_freeTypeTextureUnit, mat3 filterWeights)
{
	// subpixel sampling from a 3x resolution alpha texture w optional filtering
	// sample 3 subpixel values
	vec4 alpha;
	alpha.r = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(-1,0)).r;
	alpha.g = texture2D(u_freeTypeTextureUnit, texcoord).r; 
	alpha.b = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(1,0)).r; 
	
	// sample adjacent texels for inter pixel filtering
	float rp = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(-2,0)).r; 
	float bn = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(2,0)).r;
	
	// sample further subpixels for 5-tap filtering
	float rpp = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(-3,0)).r;
	float bnn = textureOffset(u_freeTypeTextureUnit, texcoord, ivec2(3,0)).r;
	
	// first order filtering
	vec4 alpha4;
	alpha4.r = dot(vec3(alpha.r, rp, alpha.g), filterWeights[0].xyy) + dot(vec2(rpp,alpha.b),filterWeights[0].zz);
	alpha4.g = dot(vec3(alpha.g, alpha.r, alpha.b), filterWeights[1].xyy) + dot(vec2(rp,bn),filterWeights[1].zz);
	alpha4.b = dot(vec3(alpha.b, alpha.g, bn), filterWeights[2].xyy) + dot(vec2(alpha.r,bnn),filterWeights[2].zz);
	
	// an average alpha value for the cases when we need to preserve dst alpha
	// e.g. when being rendered onto a texture for blending
	// which means that there won't be per channel alpha blending
	alpha4.a = (alpha.r + alpha.g + alpha.b) / 3.0;
		
	return alpha4;
}
