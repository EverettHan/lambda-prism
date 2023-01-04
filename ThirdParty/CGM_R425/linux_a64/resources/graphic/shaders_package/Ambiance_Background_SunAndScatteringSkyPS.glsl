//const vec3 g_ScatteringConstants  = vec3(0.005, 0.0005, -0.996);	//Rayleigh amount, Mie amount, Greenstein
// sun intensity par defaut: 200

float Scale(vec3 iSampleDir, vec3 iOutVector)
{	
  float x = vDot(iSampleDir, iOutVector);
  return vExp(2.73613 + x * (-8.719 + x * (4.43 + x * (-3.7 + x * 5.25))));
}

void main()
{	
  vec3  lightDir            = vNormalize(cb_Sun.u_SunDirection);

  vec3  rayDir              = vRay;
  rayDir.z = vClamp(rayDir.z, 0.0, rayDir.z); // hack pour garder la couleur de l'horizon en dessous de la ligne d'horizon
  rayDir = vNormalize(rayDir);

  vec3  rayOrig             = vec3(0.0, 0.0, 1);

  float b                   = 2.0 * rayDir.z;
  float t0                  = 0.5 * (-b + vSqrt(b * b + 0.2025));

  vec3  skyVector           = t0 * rayDir;
  float skyVectorLength     = vLength(skyVector);
  vec3  sampleRay           = skyVector * 0.125;
  skyVector /= skyVectorLength;

  vec3 rayleigh             = cbBackground.u_RayleighAmount * vec3(5.60204474, 9.47328443, 19.64380261);	//(0.65, 0.57, 0.475)^-4
  vec3 mie                  = cbBackground.u_MieAmount * vec3(1.43599451, 1.60348581, 1.86886257);	  //(0.65, 0.57, 0.475)^-0.84
  vec3 minusMieRayLeightPi  = -3.141592653589 * (rayleigh + mie);	
  vec3 scattered            = vec3(0.0);

  for(int i=1; i<8; i+=2)
  {
    vec3  samplePos     = rayOrig + i * sampleRay;
    float sampleHeight  = vLength(samplePos);
    samplePos /= sampleHeight;

    float sampleDepth   = vExp(160.0 * (1.0 - sampleHeight));
    scattered += sampleDepth * vExp(sampleDepth * minusMieRayLeightPi * (Scale(lightDir, samplePos) - Scale(skyVector, samplePos)));
  }

  scattered *= skyVectorLength * vExp(minusMieRayLeightPi * Scale(skyVector, rayOrig));
  float   cosTheta  = vDot(lightDir, -skyVector);
  float   g2        = cbBackground.u_Greenstein * cbBackground.u_Greenstein;
  float   miePhase  = 0.5 * (1.0 - g2) * vPow(1.0 - 2.0 * cbBackground.u_Greenstein * cosTheta + g2, -1.5);
  vec3   skyColor   = cb_Sun.u_SunIntensity * cbBackground.u_Boost * scattered * (rayleigh + mie * miePhase);

  vec4 colorCorrection = vec4(2.0, 0.16, 0.5, 1.0);	//Exposure, BalanceRB, BalanceG, Saturation
  float intensity = (skyColor.r + skyColor.g + skyColor.b) / 3.0;
  skyColor = intensity + colorCorrection.w * (skyColor - intensity) * vec3(1 + colorCorrection.y, colorCorrection.z, 1 - colorCorrection.y);

  //skyColor = 1.0 - vExp(-colorCorrection.x * skyColor);
    
  vec4 col = vec4(skyColor, 1);

#ifdef TEST
  col.x = vPow(col.x, 1.0/2.2);
  col.y = vPow(col.y, 1.0/2.2);
  col.z = vPow(col.z, 1.0/2.2);
#endif

 /* float ratio = rayDir.z;
  if (ratio<cbBackground.u_GroundRatio)
  {
    col = cbBackground.u_GroundColor;
  }
  else
  {
    col = vMix(col, cbBackground.u_GroundColor, 1.0-vSmoothstep(cbBackground.u_GroundRatio, 0.0, ratio)); 
  }*/
    
  FRAGCOLOR = col;
}

/*float GestionPhase <
  string UIWidget = \"slider\";
  string UIName = \"GestionPhase\";
  float UIMin = 0.0;
float UIMax = 24.0;
float UIStep = 0.001;
> = 0.0;

vec4 moonDirPower = float4(0.94920689, 0.29142392, -0.11865209, 0.0);

vec4 moonMat1;
vec4 moonMat2;
vec4 moonMat3;
vec4 moonMat4;

samplerCUBE StarsCubeMap
  <
  string File = \"\";
  > = sampler_state
{
  minFilter = Linear;
  magFilter = Linear;
};

sampler2D MoonMap
  <
  string File = \"\";
  > = sampler_state
{
  minFilter = LinearMipMapLinear;
  magFilter = Linear;
};

float LerpFactor(float iCosSunZenith)
{
  float resultat = 0;

  if(iCosSunZenith > -0.0)
  {
    return 1;
  }
  else if(iCosSunZenith > -0.45)
  {
    resultat = lerp(1, 0, -iCosSunZenith / 0.45);
    return resultat;
  }
  else
  {
    return 0.2;
  }
}

struct VSOut
{
  float4 pos			: POSITION;
  float3 oPosition 	: TEXCOORD1;
  float3 dirToCam		: TEXCOORD2;
  float4 oDirMoon		: TEXCOORD3;
  float3 oEye			: TEXCOORD4;
  float3 WorldNormal	: TEXCOORD5;
  float3 WorldView	: TEXCOORD6;
};

VSOut VS(float3 Pos : POSITION, float4 Normal : NORMAL)
{
  VSOut vsOut;
  float4 Po = float4(Pos, 1.0);
  vsOut.pos = mul(worldViewProj, Po);
  vsOut.dirToCam = Pos;

  vsOut.oDirMoon = float4(normalize(moonDirPower.xyz), 0.0);
  float3 Pw = mul(Po, world).xyz;
  vsOut.oPosition = Pw;
  vsOut.oEye = viewIT[3].xyz;
  float3 eye = normalize(viewIT[3].xyz - Pw);
  vsOut.WorldView = eye;

  float3 N = mul(worldIT, Normal).xyz;

  if(dot(eye, N) <= 0)
  {
    N = -N; // - N because we don't really want the \"real\" normal, which would go towards the camera : we want the sampling vector to go away from it.
  }

  vsOut.WorldNormal = N;

  return vsOut;
}*/

