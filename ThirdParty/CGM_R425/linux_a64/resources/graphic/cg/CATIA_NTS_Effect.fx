//--------------------------------
// Structure
//--------------------------------

struct pixelInput
{
    float4 HPosition	: POSITION;
    float3 texCoord	: TEXCOORD0;
    float4 Color			: COLOR;
};


float getDepth(samplerRECT texture,float2 position,float projectionMode,float4 nearFar)
{
	float4 zBuffer = texRECT(texture,position);
	
	float z = 0;
	
	if(projectionMode > 0.5f)
	{
		z = -nearFar.w/(zBuffer.x - nearFar.z);
		z = (z-nearFar.x)/(nearFar.y-nearFar.x);
	}
	else
	{
		//z = -nearFar.z*zBuffer.x + nearFar.w;
		z = zBuffer.x;
	}
	
	//z = (z-nearFar.x)/(nearFar.y-nearFar.x);
	
	return z;
}


float bezierBlend(float t)
{
	return clamp((3.0f*t*t*(1.0f-t) + t*t*t),0.0f,1.0f);
}

/* Color intensity */
float getColorLuminance(float4 color)
{
	float4 colorIntensity = color;
	float colorLum = 0.299f*colorIntensity.x + 0.587f*colorIntensity.y + 0.114f*colorIntensity.z;
	
	return colorLum;
}

float getColorAverage(float4 color)
{
	float4 colorIntensity = color;
	float colorLum = (colorIntensity.x + colorIntensity.y + colorIntensity.z)/3;
	
	return colorLum;
}

/* Contrast filter */
float4 filterContrast(float4 color, float near,float far,float threshold,float depth)
{
	float4 colorContrasted = (float4)0;
	
	float contrast = lerp(far,near,depth);
	
	colorContrasted.x = color.x+(-1+contrast)*(color.x-threshold);
	colorContrasted.y = color.y+(-1+contrast)*(color.y-threshold);
	colorContrasted.z = color.z+(-1+contrast)*(color.z-threshold);
	colorContrasted.a = color.a+(-1+contrast)*(color.a-threshold);
	
	return colorContrasted;
}

float4 filterContrast(float4 color,float contrast,float threshold)
{
	float4 colorContrasted = (float4)0;
	
	colorContrasted.x = color.x+(-1+contrast)*(color.x-threshold);
	colorContrasted.y = color.y+(-1+contrast)*(color.y-threshold);
	colorContrasted.z = color.z+(-1+contrast)*(color.z-threshold);
	colorContrasted.a = color.a+(-1+contrast)*(color.a-threshold);
	
	return colorContrasted;
}

/* Saturation filter */
float4 filterSaturation(float4 color, float saturation)
{
	float brightness = getColorAverage(color);
	float4 colorSaturated = (float4)0;
	
	colorSaturated.x = brightness+(saturation)*(color.x-brightness);
	colorSaturated.y = brightness+(saturation)*(color.y-brightness);
	colorSaturated.z = brightness+(saturation)*(color.z-brightness);
	colorSaturated.a = color.a;
	
	return colorSaturated;
}

/* Color saturation */
float4 saturateColor(float4 color,float near,float far,float depth)
{
	float4 colorToSaturate = float4(color.xyz,color.a);
	float brightness = getColorAverage(colorToSaturate);
	
	float saturation = lerp(far,near,depth);
	float4 saturatedColor = float4(brightness.xxx + saturation*(colorToSaturate.xyz-brightness.xxx),colorToSaturate.a);
	
	
	return saturatedColor;
}

/* Laplacian Color Edge Detection filter only on background*/
float4 filterColorEdgeDetectionBackgroundOnly(float4 currentColor,samplerRECT textureColor,float currentDepth,samplerRECT textureZ,float projectionMode,float4 nearFar,float2 position,float edgeOffset,float edgeIntensity,float edgeClamp,float edgePower)
{
	float z = 0;
	float background = 0;
	float weight = 0.0f;
	float2 coord = position;
	
	float2 offset = (1.0f).xx + (edgeOffset).xx;
	
	
	float4 cornersColor = (float4)0;
	
	coord = position+offset*float2(1,-1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	cornersColor += lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(-1,-1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	cornersColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(1,1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	cornersColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(-1,1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	cornersColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	
	float4 sidesColor = (float4)0;
	
	coord = position+offset*float2(0,-1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	sidesColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(1,0);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	sidesColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(-1,0);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	sidesColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	coord = position+offset*float2(0,1);
	z = getDepth(textureZ,coord,projectionMode,nearFar);
	background = floor(z+0.01f);
	sidesColor +=  lerp(currentColor,texRECT(textureColor,coord),background);
	
	
	float4 color = (cornersColor + 2.0f*sidesColor + 4.0f*background*currentColor)/16.0f;
	float edgeDetected = getColorAverage(cornersColor + 2.0f*sidesColor -12.0f*currentColor);
	float edge = edgeClamp*pow(max(edgeDetected,0.0f),edgePower);
	edge = edgeIntensity*clamp(edge,0.0f,1.0f);
	color.w = edge;
	
	
	return color;
}


//--------------------------------
// Automatic
//--------------------------------


// position du tile (en mode tiling) ou point de vue courant (en mode multiview)
// Auto_Position.x : x dans le point de vue courant
// Auto_Position.y : y dans le point de vue courant
// Auto_Position.z : x dans le viewer
// Auto_Position.w : y dans le viewer
float4 Auto_Position
<
>; 

// Dimensions du point de vue courant (celle de l’ecran lorsque l’on est pas en mode multiview)
// Auto_Size.x : largeur
// Auto_Size.y : hauteur
// Auto_Size.z : 1.f/largeur
// Auto_Size.w : 1.f/hauteur
float4 Auto_Size
<
>;

// Map du framebuffer de l’ecran (elle contient l’application des filtres precedents si il y en a)
samplerRECT Auto_EyeMap
<
>;

// Auto_Focus.x: distance de focus (distance de l oeil au centre de la sphere de rotatotion)
// Auto_Focus.y: valeur obscure utilisée par algo de depth of field
float4 Auto_Focus
<
>;

// Auto_NearFar.x : distance au plan near
// Auto_NearFar.y : distance au plan far
// Auto_NearFar.zw : valeurs pour accélerer les calculs du z
float4 Auto_NearFar
<
>;


// Map de profondeur (entre 0 et 1 et non lineaire, c’est ZBuffer telle quel)
// zBuf  = (farPlane+nearPlane)/(farPlane-nearPlane) + (1.f/z)*(-2.f*farPlane*nearPlane/(farPlane-nearPlane)) en conique;
// z = -paramNearFar.w/(zBuf-paramNearFar.z) en conique
// z = -paramNearFar.z*zBuf + paramNearFar.w en parallele 
samplerRECT Auto_ZMap
<
>;

// Ce parametre prend les valeurs suivantes :
//	0 : mode de projection parallele
//	1 : mode de projection perspective
float Auto_ProjectionMode
<
>;



//--------------------------------
// Tweakables
//--------------------------------

float4 Color
<
> = float4(0.902f,0.902f,0.902f,1.0f);


float DepthBlend
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 1.0f;

float DepthExponent
<
	float UIMin = 0.0f;
	float UIMax = 100.0f;
> = 10.0f;

float FocusScale
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 0.75f;

float DepthDebug
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 1.0f;


float SaturationBlend
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 1.0f;

float SaturationNear
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 1.0f;

float SaturationFar
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 0.5f;

float SaturationBackground
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 0.0f;


float ContrastBlend
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 1.0f;

float ContrastNear
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 1.0f;

float ContrastFar
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 0.1f;

float ContrastBackground
<
	float UIMin = 0.0f;
	float UIMax = 5.0f;
> = 0.0f;


float EdgeBlend
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 1.0f;

float EdgeClamp
<
	float UIMin = 0.0f;
	float UIMax = 100.0f;
> = 20.0f;

float EdgePower
<
	float UIMin = 0.0f;
	float UIMax = 100.0f;
> = 2.0f;

float4 EdgeColor
<
> = float4(0.745f,0.745f,0.745f,1.0f);

float EdgeDebug
<
	float UIMin = 0.0f;
	float UIMax = 1.0f;
> = 0.0f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
                                                  
float4 EffectNaturalSketchPS(pixelInput IN) : COLOR 
{
	/* input */
	float2 screenCoord = IN.texCoord.xy;
	float4 srcColor = texRECT(Auto_EyeMap,screenCoord.xy);
	float z = getDepth(Auto_ZMap,screenCoord.xy,Auto_ProjectionMode,Auto_NearFar);
	
	/* Depth */
	float focusDistance = (Auto_Focus.y+1.0f)*0.5f;
	float focus = (Auto_Focus.x-Auto_NearFar.x)/(Auto_NearFar.y-Auto_NearFar.x);
	float depth = pow(1.0f-bezierBlend(clamp(z-FocusScale*focus,0.0f,1.0f)),DepthExponent);
	depth = lerp(0.0f,depth,DepthBlend);
	
	float intensity = getColorAverage(Color);
	
	/* Background */
	float background = floor(z+0.01f);
	
	
	/* Gaussien Blur / Edge Detection */
	float edgeIntensity = 1.0f;
	float edgeOffset = 0.0f;
	float4 colorEdge = filterColorEdgeDetectionBackgroundOnly(srcColor,Auto_EyeMap,z,Auto_ZMap,Auto_ProjectionMode,Auto_NearFar,screenCoord,edgeOffset,edgeIntensity,EdgeClamp,EdgePower);
	float edge = colorEdge.w*background;
	float allbutedge = 1.0f - edge;
	colorEdge.w = srcColor.w;
	
	
	
	float4 result = srcColor;
	
	// Contrast
	float contrast = lerp(ContrastFar,ContrastNear,depth);
	contrast = lerp(contrast,ContrastBackground,background);
	result = filterContrast(result,contrast,intensity);
	
	// Edge Detection
	result = lerp(result,EdgeColor,edge);
	
	// Saturation
	result = saturateColor(result,SaturationNear,SaturationFar,depth);
	
	/*
	// Contrast
	float contrast = lerp(ContrastFar,ContrastNear,depth);
	contrast = lerp(contrast,ContrastBackground,background);
	float4 contrastedColor = lerp(result,filterContrast(result,contrast,intensity),ContrastBlend);
	result = contrastedColor;
	
	// Edge Detection
	result = lerp(result,EdgeColor,edge*EdgeBlend);
	
	// Saturation
	float4 saturatedColor = lerp(result,saturateColor(result,SaturationNear,SaturationFar,depth),SaturationBlend);
	result = saturatedColor;
	
	
	// Depth Debug
	result = lerp(result,depth*(float4)1,DepthDebug);
	result = lerp(result,edge,EdgeDebug);
	*/
	
	return float4(result.xyz,1.0f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique EffectNaturalSketchNV40
{
    pass p0 
    {       
        FragmentProgram = compile fp40 EffectNaturalSketchPS();
    }
}

technique EffectNaturalSketchGLSL
{
    pass p0 
    {       
        FragmentProgram = compile glslf EffectNaturalSketchPS();
    }
}

technique EffectNaturalSketchNV30
{
    pass p0 
    {       
        FragmentProgram = compile fp30 EffectNaturalSketchPS();
    }
}

technique EffectNaturalSketchARB
{
    pass p0 
    {       
        FragmentProgram = compile arbfp1 EffectNaturalSketchPS();
    }
}
