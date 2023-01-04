// parameters
float4x4 modelViewProj : ModelViewProjection;
sampler2D atlasSampler = sampler_state 
{
	GenerateMipmap = false;
	MinFilter = int(Linear);
	MagFilter = int(Linear);
};
float4 outline_colour = float4(0.0f,0.0f,0.0f,0.0f);
float outline_threshold =  0.f;

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
	uniform sampler2D atlasSampler,
	uniform float outline_threshold,
	uniform float4 outline_colour
)
{
	float dist = tex2D(atlasSampler, texcoord).a;
	
	// antialiased edges
    float soft_t = fwidth(dist);
    float alpha = smoothstep(0.5f-soft_t, 0.5f+soft_t, dist);
	
	// outline
	float outline_min = 0.5f - outline_threshold;
	float outline_max = 0.5f + outline_threshold;
	float weight = 1.0f;
	if (dist > outline_min && dist < outline_max)
	{
		if (dist <= 0.5f)
		{
			weight = smoothstep(outline_min, 0.5f, dist);
		}
		else
		{
			weight = smoothstep(0.5f, outline_max, dist);
		}
	}
	colour = lerp(outline_colour, colour, weight);
	
    oColor = float4(colour.rgb, alpha*colour.a);
}
// Fragment shader when no screen derivs
void main_ps_ARB
(
	float4 colour : COLOR0,
	float2 texcoord : TEXCOORD0,
	out float4 oColor : COLOR,
	uniform sampler2D atlasSampler
)
{
	float dist = tex2D(atlasSampler, texcoord).a;
	// hard edges
	float alpha = (dist >= 0.5f ? 1.0f : 0.0f);
    oColor = float4(colour.rgb, alpha*colour.a);
}

// techniques
technique text3dat_GLSL
{
	pass p0
	{
		VertexProgram = compile glslv main_vs(modelViewProj);
		FragmentProgram = compile glslf main_ps(atlasSampler, outline_threshold, outline_colour);
		
		ZEnable = false;
		ZWriteEnable = false;
		BlendEnable = true;
		BlendFunc = int2(SrcAlpha, OneMinusSrcAlpha);
		CullFaceEnable = false;
	}
}

technique text3dat_ARB
{
	// there's no screen space deriv in arb profiles, so hard edges
	pass p0
	{
		VertexProgram = compile arbvp1 main_vs(modelViewProj);
		FragmentProgram = compile arbfp1 main_ps_ARB(atlasSampler);
		
		ZEnable = false;
		ZWriteEnable = false;
		BlendEnable = true;
		BlendFunc = int2(SrcAlpha, OneMinusSrcAlpha);
		CullFaceEnable = false;
	}
}