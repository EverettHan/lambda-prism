void ComputeCommonValues()
{ 
} 

vec3 ComputeAlbedo()
{    
  return vec3(1.0,0.,0.);
}

vec3 ComputeEmissive()
{  
  return vec3(0.0); 
}

float ComputeAlpha()
{  
  return 1.;
}

vec3 ComputeSpecularColor()
{
  return vec3(1.0);
}

vec3 ComputeWorldNormal()
{   
  return vGetWorldN();  
}

void ProcessFinalColor(inout vec3 finalColor)
{    
}

void PerformClipping()
{
}

