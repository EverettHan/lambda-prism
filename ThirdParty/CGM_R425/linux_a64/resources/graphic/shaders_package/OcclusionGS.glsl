#ifndef SHADER_BUILDER
#version 430
#endif

layout(points, invocations = 3)in;
layout(triangle_strip, max_vertices = 4)out;

in VertexOut
{
  vec3 bboxCtr;
flat int matrixIndex;
vec3 bboxDim;
flat int objid;
// float bboxCornerRadii[8];
#ifdef DebugBoxes
vec4 color;
#endif
} IN[1];

flat out int objid;

#ifdef DebugBoxes
  out vec4 color;
#endif

#ifdef LogDepth
out vec3 viewPos;
#endif


void main()
{
  if((IN[0].objid &(1 << 31))!= 0)
  return;

#ifdef DebugBoxes
  color = IN[0].color;
#endif

  objid = IN[0].objid &(~(1 << 31));

  int matindex = IN[0].matrixIndex* 4;

  mat4 worldTM = mat4(
    texelFetch(matricesTex, matindex + 0),
    texelFetch(matricesTex, matindex + 1),
    texelFetch(matricesTex, matindex + 2),
    texelFetch(matricesTex, matindex + 3));

#if defined(StereoOcclusion)
  worldTM = cb_OcclusionCamera.PassageMatrix * worldTM; //Transform from 1 eye to the other
#endif


  vec3 faceNormal = vec3(0);
  vec3 edgeBasis0 = vec3(0);
  vec3 edgeBasis1 = vec3(0);

  int id = gl_InvocationID;

  if(id == 0)
  {
      faceNormal.x = IN[0].bboxDim.x;
      edgeBasis0.y = IN[0].bboxDim.y;
      edgeBasis1.z = IN[0].bboxDim.z;
  }
  else if(id == 1)
  {
      faceNormal.y = IN[0].bboxDim.y;
      edgeBasis1.x = IN[0].bboxDim.x;
      edgeBasis0.z = IN[0].bboxDim.z;
  }
  else if(id == 2)
  {
      faceNormal.z = IN[0].bboxDim.z;
      edgeBasis0.x = IN[0].bboxDim.x;
      edgeBasis1.y = IN[0].bboxDim.y;
  }

  vec3 worldCtr =(worldTM * vec4(IN[0].bboxCtr, 1)).xyz;
  vec3 worldNormal = mat3(worldTM) * faceNormal;


#ifdef PROJECTION_CONIC
  vec3 worldPos = worldCtr + worldNormal;
  float proj = - sign(dot(worldPos, worldNormal));
#else //Ortho
  mat4 ViewInverse = vGetViewInverseMatrix();
  vec3 viewDir = vec3(0,0,1); //ViewInverse[2].xyz;
  float proj =   sign(dot(viewDir, worldNormal));
#endif


  faceNormal = mat3(worldTM) * (faceNormal);
  edgeBasis0 = mat3(worldTM) * (edgeBasis0);
  edgeBasis1 = mat3(worldTM) * (edgeBasis1);
  faceNormal *= proj;
  edgeBasis1 *= proj;

#ifndef LogDepth
  vec3 viewPos;
#endif

  viewPos     = worldCtr + (faceNormal - edgeBasis0 - edgeBasis1);
  gl_Position = vGetProjMatrix() * ( vec4(viewPos, 1));
  EmitVertex();

  viewPos     = worldCtr + (faceNormal + edgeBasis0 - edgeBasis1);
  gl_Position = vGetProjMatrix() * ( vec4(viewPos, 1));
  EmitVertex();

  viewPos     = worldCtr + (faceNormal - edgeBasis0 + edgeBasis1);  
  gl_Position = vGetProjMatrix() * ( vec4(viewPos, 1));
  EmitVertex();

  viewPos     = worldCtr + (faceNormal + edgeBasis0 + edgeBasis1);
  gl_Position = vGetProjMatrix() * (vec4(viewPos, 1));
  EmitVertex();
}
