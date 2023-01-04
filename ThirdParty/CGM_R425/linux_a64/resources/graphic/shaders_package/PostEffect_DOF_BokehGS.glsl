#ifndef SHADER_BUILDER
#version 420
#endif

layout (points) in;
layout (triangle_strip, max_vertices=20) out;

out vec2 vTexCoordGS;
out vec4 vColorGS;

#define MIN_QUAD_SIZE 0.1
#define MAX_QUAD_SIZE 15.0
#define BOOSTED_MAX_QUAD_SIZE 25.0
#define BASE_INTENSITY 0.05
#define BOOSTED_INTENSITY 0.1

#define COLOR_TO_INTENSITY vec3(0.299, 0.587, 0.114)

#define NUM_SAMPLES_X 2
#define NUM_SAMPLES_Y 2

float ComputeBoostFactor(vec3 pixelColor)
{
	// Checks the pixel luminance intensity, and asks to boosts its bokeh if above threshold
	const float INTENSITY_THRESHOLD = 0.9;
	
	float intensity = vDot(COLOR_TO_INTENSITY, pixelColor);
	return vStep(INTENSITY_THRESHOLD, intensity);
}

float ComputeDepthDiscontinuity(float distances[NUM_SAMPLES_X * NUM_SAMPLES_Y])
{
	// If the delta between the min depth and the max depth is above the given percentage of the camera near-far distance,
	// we asks for more bokeh
	const float DEPTH_THRESHOLD = 0.1;
	vec3 NearFar = vGetNearFarLogFactor();
	float maxDistance = NearFar.x;
	float minDistance = NearFar.y;
	
	for (int i = 0; i < NUM_SAMPLES_X * NUM_SAMPLES_Y; i++)
	{
		maxDistance = vMax(maxDistance, distances[i]);
		minDistance = vMin(minDistance, distances[i]);
	}
	
	return step(DEPTH_THRESHOLD * (NearFar.y - NearFar.x), maxDistance - minDistance);
}

float ComputeColorDiscontinuity(vec3 colors[NUM_SAMPLES_X * NUM_SAMPLES_Y])
{
	// If the delta between the min color and the max color is above the given threshold, for any component,
	// we asks for more bokeh
	const float COLOR_THRESHOLD = 0.1;

	vec3 maxColor = vec3(0.0);
	vec3 minColor = vec3(1.0);
	
	for (int i = 0; i < NUM_SAMPLES_X * NUM_SAMPLES_Y; i++)
	{
		maxColor = vMax(maxColor, colors[i]);
		minColor = vMin(minColor, colors[i]);
	}
	
	float criteria = vStep(COLOR_THRESHOLD, maxColor.x - minColor.x);
	criteria += vStep(COLOR_THRESHOLD, maxColor.y - minColor.y);
	criteria += vStep(COLOR_THRESHOLD, maxColor.z - minColor.z);
	
	return vStep(1.0, criteria);
}

void GenerateQuad( vec2 offset, float pixelDistance, vec3 pixelColor, float needMultiQuads, float boost, float maxIntensity)
{
  // Rasterization needs to hit the center of the fragment, hence the half pixel offset
	vec2 coord = gl_in[0].gl_Position.xy + (offset + vec2(0.5, 0.5)) / (cb_PostEffectAuto.u_ViewportSize.xy * 0.5);
	vec2 newPos = coord * 2.0 - 1.0;

	float radius = GetBlurRadius(pixelDistance);
	float boostFactor = ComputeBoostFactor(pixelColor);
	float quadSize = vMix(MAX_QUAD_SIZE, BOOSTED_MAX_QUAD_SIZE, boostFactor);
	quadSize *= vAbs(radius);

	quadSize *= needMultiQuads;
	float intensity = vMix(BASE_INTENSITY, maxIntensity, boostFactor) * boost;

  if (quadSize > MIN_QUAD_SIZE)
  {
    // ScreenSize is the size of the backBuffer RT, as we are working in half-res, we need to divide the size info by 2
    vec2 screenSize = cb_PostEffectAuto.u_ViewportSize.xy * 0.5;
    vec2 homogeneousQuadSize = vec2(quadSize / screenSize.x, quadSize / screenSize.y);

    vColorGS.xyz = pixelColor;
    vColorGS.a = intensity;

    gl_Position = vec4(newPos.x - homogeneousQuadSize.x, newPos.y - homogeneousQuadSize.y, 0.0, 1.0);
    vTexCoordGS = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = vec4(newPos.x - homogeneousQuadSize.x, newPos.y + homogeneousQuadSize.y, 0.0, 1.0);
    vTexCoordGS = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(newPos.x + homogeneousQuadSize.x, newPos.y - homogeneousQuadSize.y, 0.0, 1.0);
    vTexCoordGS = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = vec4(newPos.x + homogeneousQuadSize.x, newPos.y + homogeneousQuadSize.y, 0.0, 1.0);
    vTexCoordGS = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
  }
}

void main()
{
	// ScreenSize is the size of the "backBuffer RT", as we are working in half-res, we need to divide the size info by 2
	vec2 screenSize = cb_PostEffectAuto.u_ViewportSize.xy * 0.5;

	// Read all samples
	vec3 pixelColors[NUM_SAMPLES_X * NUM_SAMPLES_Y];
	float pixelDistances[NUM_SAMPLES_X * NUM_SAMPLES_Y];
	
	for (int i = 0; i < NUM_SAMPLES_X; i++)
	{
		for (int j = 0; j < NUM_SAMPLES_Y; j++)
		{
			int index = i*NUM_SAMPLES_Y + j;
			vec2 coord = gl_in[0].gl_Position.xy + (vec2(i, j)*2.0 - 0.0) / screenSize;
			
			pixelColors[index] = vTexture(s_ColorTex, coord).xyz;
			pixelDistances[index] = ConvertZBufferToZView(GetZ(coord));
		}
	}
	//

	float isDepthDiscontinuited = ComputeDepthDiscontinuity(pixelDistances);
	float isColorDiscontinuited = ComputeColorDiscontinuity(pixelColors);

	// Single simple bokeh quad
	vec2 geomPos = gl_in[0].gl_Position.xy * 2.0 - 1.0;

	vec3 pixelColor = vec3(0.0);
	float pixelDistance = 0.0;
	for (int i = 0; i < NUM_SAMPLES_X * NUM_SAMPLES_Y; i++)
	{
		pixelColor += pixelColors[i];
		pixelDistance += pixelDistances[i];
	}
	pixelColor /= NUM_SAMPLES_X * NUM_SAMPLES_Y;
	pixelDistance /= NUM_SAMPLES_X * NUM_SAMPLES_Y;

	float radius = GetBlurRadius(pixelDistance);
	float boostFactor = ComputeBoostFactor(pixelColor);
	float quadSize = vMix(MAX_QUAD_SIZE, BOOSTED_MAX_QUAD_SIZE, boostFactor);
	quadSize *= vAbs(radius);

	float needMultiQuads = vStep(1.0, isDepthDiscontinuited + isColorDiscontinuited + boostFactor);
	boostFactor *= vAbs(radius);
	
	// Disabling singleQuad optim for now, not clean enough (waiting for a proper downsampling stuff)
	//needMultiQuads = 1.0;
	//
	
	GenerateQuad(vec2(0.5, 0.5), pixelDistance, pixelColor, 1.0 - needMultiQuads, 4.0, BASE_INTENSITY);
	//
	
	// Multi bokeh quads
	GenerateQuad(vec2(0, 0), pixelDistances[0], pixelColors[0], needMultiQuads, 1.0, BASE_INTENSITY);
	GenerateQuad(vec2(0, 1), pixelDistances[1], pixelColors[1], needMultiQuads, 1.0, BASE_INTENSITY);
	GenerateQuad(vec2(1, 0), pixelDistances[2], pixelColors[2], needMultiQuads, 1.0, BASE_INTENSITY);
	GenerateQuad(vec2(1, 1), pixelDistances[3], pixelColors[3], needMultiQuads, 1.0, BASE_INTENSITY);
}
