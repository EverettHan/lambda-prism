//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

//--------------------------------
// Structure
//--------------------------------

struct pixelInput
{
    float4 HPosition      : POSITION;
    float3 texCoord		  : TEXCOORD0;
    float4 Color          : COLOR;
};


//--------------------------------
// Tweakables
//--------------------------------

float4 GlyphColor : AUTOMATICCOLORATTRIBUTE;
float  BorderWidth;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 SWXVertexGlyph_PS(pixelInput IN) : COLOR
{
	//Find the texture coordinate's distance from the edge
	float distFromEdge = min(
		min(IN.texCoord.x, 1.0 - IN.texCoord.x),
		min(IN.texCoord.y, 1.0 - IN.texCoord.y) );
		
	//If the coordinate is within L1 distance from
	//edge, we will darken the color to make a border.
	//float colorMultiplier = 1.0 - .5*(1.0 - smoothstep(BorderWidth-.05, BorderWidth+.05, distFromEdge));
	float colorMultiplier = 1.0 - .5*(1.0 - step(BorderWidth, distFromEdge));
	
	return float4(GlyphColor.r * colorMultiplier, GlyphColor.g * colorMultiplier, GlyphColor.b * colorMultiplier, 1.0f);
}

float4 SWXVertexGlyphPolite_PS(pixelInput IN) : COLOR
{
	return float4(GlyphColor.r, GlyphColor.g, GlyphColor.b, 0.55f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique SWXVertexGlyph_NV40
{
    pass PolitePass 
    {		
		DepthTestEnable = false;		
		CullFaceEnable = false;
		AlphaBlendEnable = true;
		BlendEnable = true;
		BlendFunc = float2(SrcAlpha,OneMinusSrcAlpha);
		
        FragmentProgram = compile fp40 SWXVertexGlyphPolite_PS();
    }
    
    pass NormalPass 
    {		
		DepthTestEnable = true;
		BlendEnable = false;	
		
        FragmentProgram = compile fp40 SWXVertexGlyph_PS();
    }
}

technique SWXVertexGlyph_GLSL
{
	pass PolitePass 
    {		
		DepthTestEnable = false;		
		CullFaceEnable = false;
		AlphaBlendEnable = true;
		BlendEnable = true;
		BlendFunc = float2(SrcAlpha,OneMinusSrcAlpha);
		
        FragmentProgram = compile glslf SWXVertexGlyphPolite_PS();
    }
    
    pass NormalPass 
    {		
		DepthTestEnable = true;
		BlendEnable = false;	
		
        FragmentProgram = compile glslf SWXVertexGlyph_PS();
    }
}

technique SWXVertexGlyph_NV30
{
	pass PolitePass 
    {		
		DepthTestEnable = false;		
		CullFaceEnable = false;
		AlphaBlendEnable = true;
		BlendEnable = true;
		BlendFunc = float2(SrcAlpha,OneMinusSrcAlpha);
		
        FragmentProgram = compile fp30 SWXVertexGlyphPolite_PS();
    }
    
    pass NormalPass 
    {		
		DepthTestEnable = true;
		BlendEnable = false;	
		
        FragmentProgram = compile fp30 SWXVertexGlyph_PS();
    }
}

technique SWXVertexGlyph_ARB
{
	pass PolitePass 
    {		
		DepthTestEnable = false;		
		CullFaceEnable = false;
		AlphaBlendEnable = true;
		BlendEnable = true;
		BlendFunc = float2(SrcAlpha,OneMinusSrcAlpha);
		
        FragmentProgram = compile arbfp1 SWXVertexGlyphPolite_PS();
    }
    
    pass NormalPass 
    {		
		DepthTestEnable = true;
		BlendEnable = false;	
		
        FragmentProgram = compile arbfp1 SWXVertexGlyph_PS();
    }
}


