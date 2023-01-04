#ifndef SHADER_BUILDER
#version 430
#endif

#ifdef DebugBoxes

in vec4 color;

layout(location = 0) out vec4 fragColor;

void main(void)
{
  fragColor  = color; 
}

#elif !defined(LogDepth)


layout(early_fragment_tests)in;

//layout(std430, binding = 0)buffer visibilityBuffer
//{
//  int visibles[];
//};

flat in int objid;

void main()
{
  visibles[objid]= 1;
}

#else
//We are using log depth. We need to do our depth test manualy

//layout(std430, binding = 0)buffer visibilityBuffer
//{
//  int visibles[];
//};

flat in int objid;
in vec3     viewPos;

void main()
{
  vec4 curDepth = texelFetch(depthTex, ivec2(gl_FragCoord.xy), 0);

  float fragDepth = ComputeLogDepth(-viewPos.z); //Yes this is the viewpos and not the proj pos
 
  if(fragDepth <= curDepth.x)
    visibles[objid]= 1;
}


#endif
