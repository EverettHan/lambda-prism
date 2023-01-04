
#define MIN_TOLERANCE 0.0001

void main()
{
	float distance = ConvertZBufferToZView(GetZ(vTexCoord));
	float radius = GetBlurRadius(distance);

	vec4 inFocus = GetEffectTexture(s_ColorTex, vTexCoord);
	
	vec4 frontDOF = GetEffectTexture(s_ForegroundTex, vTexCoord);
	frontDOF.xyz /= max(MIN_TOLERANCE, frontDOF.a);
	
	vec4 backDOF = GetEffectTexture(s_BackgroundTex, vTexCoord);
	backDOF *= radius;
	backDOF.xyz /= vMax(MIN_TOLERANCE, backDOF.a);

	frontDOF.a = vClamp(frontDOF.a, 0.0, 1.0);
	backDOF.a = vClamp(backDOF.a, 0.0, 1.0);

  vec3 finalcol = inFocus.xyz;
	finalcol = finalcol * (1.0 - backDOF.a) + backDOF.xyz * backDOF.a;
	finalcol = finalcol * (1.0 - frontDOF.a) + frontDOF.xyz * frontDOF.a;

  FRAGCOLOR = vec4(finalcol, 1.0);
}
