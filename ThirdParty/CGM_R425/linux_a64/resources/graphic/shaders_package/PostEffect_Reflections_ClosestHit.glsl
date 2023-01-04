layout(location = 0) rayPayloadInEXT Payload_t g_Payload;

hitAttributeEXT vec2 g_HitAttributes;

void main()
{
  ObjFormat_t objFormat = g_ObjFormat.data[gl_InstanceCustomIndexEXT];
  ObjDesc_t obj = g_ObjDesc.data[gl_InstanceCustomIndexEXT];

   //those are defined in bytes, but we need them as # of floats
  uint vertexStride = objFormat.vertexStride / 4;
  uint posOffset = objFormat.positionOffset / 4;
  uint nrmOffset = objFormat.normalOffset / 4;

  Indices ptrIndices = Indices(obj.indexAddr);
  Vertices ptrVertices = Vertices(obj.vertexAddr);
  
  ivec3 ind = int(vertexStride) * ptrIndices.data[gl_PrimitiveID];

  Vertex_t v[3];

  for(int i=0; i<3; i++)
  {
    v[i].pos.x = ptrVertices.data[ind[i]+posOffset];
    v[i].pos.y = ptrVertices.data[ind[i]+posOffset+1];
    v[i].pos.z = ptrVertices.data[ind[i]+posOffset+2];

    v[i].nrm.x = ptrVertices.data[ind[i]+nrmOffset];
    v[i].nrm.y = ptrVertices.data[ind[i]+nrmOffset+1];
    v[i].nrm.z = ptrVertices.data[ind[i]+nrmOffset+2];
  }

  const vec3 barycentrics = vec3(1.0 - g_HitAttributes.x - g_HitAttributes.y, g_HitAttributes.x, g_HitAttributes.y);
  
  // Computing the coordinates of the hit position
  const vec3 pos = v[0].pos * barycentrics.x + v[1].pos * barycentrics.y + v[2].pos * barycentrics.z;
  const vec3 worldPos = vec3(gl_ObjectToWorldEXT * vec4(pos, 1.0));

  // Computing the normal at hit position
  const vec3 nrm = v[0].nrm * barycentrics.x + v[1].nrm * barycentrics.y + v[2].nrm * barycentrics.z;
  vec3 worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));

  const vec3 edge1 = normalize(v[1].pos - v[0].pos);
  const vec3 edge2 = normalize(v[2].pos - v[0].pos);

  //vec3 geomN = cross(edge1, edge2);
  //geomN = normalize(vec3(geomN * gl_WorldToObjectEXT));
  //
  //if(dot(geomN, nrm) < 0.0)
  //  worldNrm = -worldNrm;
  
  g_Payload.position = worldPos;
  g_Payload.normal = worldNrm;
  g_Payload.isHit = true;
}
