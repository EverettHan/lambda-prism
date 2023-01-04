float4 gammaCorrectAlphaBlend(float4 color, float alpha, float gamma)
{
	// approximates gamma correction with alpha blending
	// c = cs*a + cd*(1-a)
	// c = pow(c, 1/gamma)
	// we do am approximate alpha blend in gamma space with
	// preserving destination alpha for the cases where the 
	// text gets drawn onto an alpha texture
	// cf ~= (cs*a)^1/g + cd*(1-a)^1/g
	// af ~= as*as + ad*(1-as)
	float4 res;
	res.rgb	= color.rgb*color.a*alpha;
	res.rgb = pow(res.rgb, 1.0f/gamma);
	
	// aproximate (1-a)^(1/g) by 1 - (1/g)a
	res.a = color.a*alpha/gamma;

	// blend with (1,1-a)
	return res;
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
	out float4 oColor 	 : COLOR0	
)
{
	oPosition = mul(modelViewProj, position);
	oTexCoord = texcoord;
	oColor = colour;
}

// Fragment shader
void main_ps
(
	float2 texcoord  : TEXCOORD0,
	float4 textColor : COLOR0,
	uniform sampler2D atlasSampler,
	uniform float gamma,
	out float4 oColor : COLOR
)
{
	float alpha = tex2D(atlasSampler, texcoord).a;
	oColor = gammaCorrectAlphaBlend(textColor, alpha, gamma);
}

// technique
technique text2d_ARB
{
	pass p0
	{
		VertexProgram = compile arbvp1 main_vs(modelViewProj);
		FragmentProgram = compile arbfp1 main_ps(atlasSampler, gamma);
		
		ZEnable = false;
		ZWriteEnable = false;
		BlendEnable = true;
		BlendFunc = int2(One, OneMinusSrcAlpha);
		CullFaceEnable = false;
	}
}