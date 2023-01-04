
vec3 GetLocalPosition()
{
  return vGetPosition();
}

void TransformFinalPosition(inout vec4 position)
{
  vec4 initPosition = vec4(vGetPosition(), 1.0);
  if(cb_cbParticleSystem.isLocal == 1.0)
  {
    initPosition = cb_cbParticleSystem.TransformMatrix * initPosition ;
  }

  vec4 pos = vGetViewMatrix() * initPosition;
  position = vGetProjMatrix()*vec4(pos.x + vGetTexCoord1().y, pos.y - vGetTexCoord1().z, pos.z , 1);
}

void ComputeCommonValues()
{  
}

void ProcessVertexCustom()
{        
  color = vec4(vGetColor().xyz,vGetTexCoord0().z) ;
  isLife = vGetTexCoord0().x;
  texCoord = normalize(vGetTexCoord1().yz) + 0.5;
}

void ProcessTangentSpaceCustom(inout TangentSpace worldTS)
{
}

