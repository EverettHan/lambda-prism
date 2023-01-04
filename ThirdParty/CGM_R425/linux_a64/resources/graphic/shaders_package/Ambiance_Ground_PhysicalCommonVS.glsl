//-------------------------------------------------------------------------------------------
// Mirroring

#ifdef GROUND_MIRRORING
#ifndef GLES2Platform
out vec2 vMirrorTexCoord;
#else
varying vec2 vMirrorTexCoord;
#endif
#endif


//-------------------------------------------------------------------------------------------
// Methode non surchargee

void ProcessBRDFParameters(inout BRDFParameters oParameters)
{ 
}

void TransformFinalPosition(inout vec4 position)
{   
}

void ProcessTangentSpaceCustom(inout TangentSpace worldTS)
{
}

//-------------------------------------------------------------------------------------------
// Code commun

vec4  g_LocalPos = vec4(0);

vec3 GetLocalPosition()
{ 
  return g_LocalPos.xyz;
}
