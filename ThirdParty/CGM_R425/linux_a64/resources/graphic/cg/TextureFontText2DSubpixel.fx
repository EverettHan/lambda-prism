float4 gammaCorrect(float4 color, float gamma)
{
	return pow(color, 1.0f/gamma);
}

float4 subpixelFilter
(
	float2 texcoord,
	sampler2D atlasSampler,
	float2 texelSize,
	float3x3 filterWeights
)
{
	// subpixel sampling from a 3x resolution alpha texture w optional filtering
	// sample 3 subpixel values
	float4 alpha;
	float2 dg = float2(0,0);
	float2 dt = float2(1,0);
	alpha.r = tex2D(atlasSampler, texcoord + texelSize*(dg-dt)).w;
	alpha.g = tex2D(atlasSampler, texcoord + texelSize*(dg)).w;
	alpha.b = tex2D(atlasSampler, texcoord + texelSize*(dg+dt)).w;
	
	//sample adjacent texels for inter pixel filtering
	float rp = tex2D(atlasSampler, texcoord + texelSize*(dg-dt-dt)).w;
	float bn = tex2D(atlasSampler, texcoord + texelSize*(dg+dt+dt)).w;
	
	// sample further subpixels for 5-tap filtering
	float rpp = tex2D(atlasSampler, texcoord + texelSize*(dg-dt-dt-dt)).w;
	float bnn = tex2D(atlasSampler, texcoord + texelSize*(dg+dt+dt+dt)).w;
	
	// first order filtering
	float4 alpha4;
	alpha4.r = dot(float3(alpha.r, rp, alpha.g), filterWeights[0].xyy) + dot(float2(rpp,alpha.b),filterWeights[0].zz);
	alpha4.g = dot(float3(alpha.g, alpha.r, alpha.b), filterWeights[1].xyy) + dot(float2(rp,bn),filterWeights[1].zz);
	alpha4.b = dot(float3(alpha.b, alpha.g, bn), filterWeights[2].xyy) + dot(float2(alpha.r,bnn),filterWeights[2].zz);
	
	// an average alpha value for the cases when we need to preserve dst alpha
	// e.g. when being rendered onto a texture for blending
	// which means that there won't be per channel alpha blending
	alpha4.a = (alpha.r + alpha.g + alpha.b) / 3.f;
		
	return alpha4;
}


// parameters
float4x4 modelViewProj : ModelViewProjection;
sampler2D atlasSampler = sampler_state {
	ColorOp = int(Modulate);	
	WrapS = int(Wrap);
	WrapT = int(Wrap);	
	GenerateMipmap = false;
	MinFilter = int(Nearest);
	MagFilter = int(Nearest);
};
float2 texelSize = float2(1.0f/512.f);
float3x3 filter = { 1.0f/3.0f,  1.0f/3.0f, 0.0f,
					1.0f/3.0f,  1.0f/3.0f, 0.0f,
					1.0f/3.0f,  1.0f/3.0f, 0.0f
					};
			
float gamma = 1.0f;

// Vertex shader
void main_vs
(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	float4 colour	: COLOR0,
	uniform float4x4	modelViewProj,
	out float4 oPosition : POSITION,
	out float2 oTexCoord : TEXCOORD0,
	out float4 oColour	 : COLOR0
)
{
	oPosition = mul(modelViewProj, position);
	oTexCoord = texcoord;
	oColour = colour;
}


// Fragment shaders
void main_ps0
(
	float4 textColor: COLOR0,
	float2 texcoord : TEXCOORD0,
	uniform sampler2D atlasSampler,
	uniform float	gamma,
	uniform float2	texelSize,
	uniform float3x3 filter,	
	out float4 oColor : COLOR
)
{
	// obtain filtered alpha values from the texture
	float4 alpha4 = subpixelFilter(texcoord, atlasSampler, texelSize, filter);
	alpha4.rgb *= textColor.a;
	
	// output alpha as color so the blend op modulates dst
	oColor = gammaCorrect(float4(1.0f) - alpha4, gamma);
}


void main_ps1
(
	float4 textColor: COLOR0,
	float2 texcoord : TEXCOORD0,
	uniform sampler2D atlasSampler,
	uniform float	gamma,
	uniform float2	texelSize,
	uniform float3x3 filter,	
	out float4 oColor : COLOR
)
{
	// obtain filtered alpha values from the texture
	float4 alpha4 = subpixelFilter(texcoord, atlasSampler, texelSize, filter);
	
	// output premultiplied colour so the blend op completes the per channel alpha blend
	textColor.rgb *= textColor.a;
	oColor = gammaCorrect(alpha4*textColor, gamma);
}

// technique
technique text2dsubpixel_ARB
{
	pass p0
	{
		VertexProgram = compile arbvp1 main_vs(modelViewProj);
		FragmentProgram = compile arbfp1 main_ps0(atlasSampler, gamma, texelSize, filter);
		
		ZEnable = false;
		ZWriteEnable = false;
		BlendEnable = true;
		BlendFunc = int2(Zero, SrcColor);
		CullFaceEnable = false;
	}
	
	pass p1
	{
		VertexProgram = compile arbvp1 main_vs(modelViewProj);
		FragmentProgram = compile arbfp1 main_ps1(atlasSampler, gamma, texelSize, filter);
		
		ZEnable = false;
		ZWriteEnable = false;
		BlendEnable = true;
		BlendFunc = int2(One, One);
		CullFaceEnable = false;	
	}
}