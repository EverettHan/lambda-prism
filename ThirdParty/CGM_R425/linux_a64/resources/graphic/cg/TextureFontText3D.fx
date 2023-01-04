// parameters
float4x4 modelViewProj : ModelViewProjection;
sampler2D atlasSampler = sampler_state 
{
	GenerateMipmap = false;
	MinFilter = int(Linear);
	MagFilter = int(Linear);
};

// Vertex shader
void main_vs
(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	float4 colour	: COLOR0,
	uniform float4x4	modelViewProj,
	out float4 oPosition : POSITION,
	out float2 oTexCoord : TEXCOORD0,
	out float4 oColour	  : COLOR0
)
{
	oPosition = mul(modelViewProj, position);
	oTexCoord = texcoord;
	oColour = colour;
}

// Fragment shader
void main_ps
(
	float4 colour : COLOR0,
	float2 texcoord : TEXCOORD0,
	out float4 oColor : COLOR,
	uniform sampler2D atlasSampler
)
{
	float alpha = tex2D(atlasSampler, texcoord).a;
	oColor = float4(colour.rgb, alpha*colour.a);
}

// technique
technique text3d_ARB
{
	pass p0
	{
		VertexProgram = compile arbvp1 main_vs(modelViewProj);
		FragmentProgram = compile arbfp1 main_ps(atlasSampler);
		
		ZEnable = false;
		ZWriteEnable = false;
		AlphaTestEnable = true;
		AlphaFunc = float2(Greater, 0);
		BlendEnable = true;
		BlendFunc = int2(SrcAlpha, OneMinusSrcAlpha);
		CullFaceEnable = false;
	}
}