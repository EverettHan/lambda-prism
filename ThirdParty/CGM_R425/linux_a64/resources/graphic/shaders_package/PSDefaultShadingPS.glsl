void ProcessBRDFParameters(inout BRDFParameters oParameters)
{      
}  

void ComputeCommonValues()
{ 
} 

vec3 ComputeAlbedo()
{
  vec3 finalColor = color.xyz;

  if(cb_cbParticleSystem.HaveTexure == 1.0)
    finalColor *= vTexture(ParticleTexture,  texCoord).xyz;

 // return vec3(isLife, isLife, isLife);
  return finalColor;
}

vec3 ComputeEmissive()
{  
  return vec3(0.0); 
}

float ComputeAlpha()
{ 
  float alpha = 1.0;

  if(cb_cbParticleSystem.HaveTexure == 1.0 )
    alpha = vTexture(ParticleTexture, texCoord).a;

//  if(isLife <= 0.5)
//    alpha = mix(0.0, alpha, isLife);

  return  alpha*color.w;
}

vec3 ComputeSpecularColor()
{
  return vec3(1.0);
}

vec3 ComputeWorldNormal()
{
  return vec3(0.0, -1.0, 0.0);
}

void ProcessFinalColor(inout vec3 finalColor)
{    

}

void PerformClipping()
{
}

