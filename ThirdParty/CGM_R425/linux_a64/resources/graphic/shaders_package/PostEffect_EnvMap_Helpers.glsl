/*const mat3 CATIA2GLRotation = mat3
(
    0.0,  0.0, -1.0,
   -1.0,  0.0,  0.0,
    0.0, -1.0,  0.0
);
*/

vec3 ComputeDirectionFromPlane(in float iPhi, in float iTheta)
{
  vec3 r;
  r.x = vCos(iPhi)*vCos(iTheta);
  r.y = vSin(iPhi);
  r.z = vCos(iPhi)*vSin(iTheta);

  return r;
}

vec3 ComputeDirectionFromTexCoord(in vec2 iTexCoord)
{
  float phi  = -PI*(iTexCoord.y - 0.5);
  float theta = -PI*(iTexCoord.x*2.0 - 1.0);

  return ComputeDirectionFromPlane(phi, theta);
}

vec3 ComputeDirectionFromCube(in int iFace, vec2 iCoord)
{
  vec3 proj = normalize(vec3(iCoord.x*2-1, (1.0-iCoord.y)*2-1, 1.0));
  
  float s = proj.x;
  float t = proj.y;
  float r = proj.z;
  
  vec3 res;

  switch(iFace)
  {
  case 0: //+X
    res.x = r;
    res.y = t;
    res.z = -s;
    break;

  case 1: //-X
    res.x = -r;
    res.y = t;
    res.z = s;
    break;

  case 2: //+Y
    res.x = s;
    res.y = r;
    res.z = -t;
    break;

  case 3: //-Y
    res.x = s;
    res.y = -r;
    res.z = t;
    break;

  case 4: //+Z
    res.x = s;
    res.y = t;
    res.z = r;
    break;

  case 5: //-Z
    res.x = -s;
    res.y = t;
    res.z = -r;
    break;
  }

  return res;
}

vec3 ComputeDualParaboloidFromDirection(in vec3 iDir)
{
  vec2 st;
  float depth;
  const float scale = 1.2;

  if(iDir.z < 0.0)
  {
    st = iDir.xy/(scale*(1-iDir.z))*0.5+0.5;
    depth = 0.0;
  }
  else
  {
    st = -iDir.xy/(scale*(1+iDir.z))*0.5+0.5;
    depth = 1.0;
  }

  return vec3(st, depth);
}

vec3 ComputeDirectionFromDualParaboloid(in vec2 iTexCoord, in int iLayer)
{  
  vec2 st = vec2(iTexCoord.x, iTexCoord.y) * 2.0 - 1.0;
  const float scale = 1.2;

  st *= scale;

  float dotFact = vDot(st, st);
  
  vec3 dir;  //Front
  dir.xy = 2.0*st/(dotFact+1.0);
  dir.z = (dotFact-1.0)/(dotFact+1.0);
  
  if(iLayer == 1) //Back
    dir *= -1.0;

  return dir;
}

vec2 ComputeTexCoordFromPlane(in float iPhi, in float iTheta)
{
  float phi = -iPhi*INV_PI*0.5 + 0.5;
  float theta = -iTheta*INV_PI + 0.5;

  return vec2(phi, theta);
}

  //float phi  = PI*(iTexCoord.y - 0.5);
  //float theta = PI*(iTexCoord.x*2.0 - 1.0);

vec2 ComputeTexCoordFromDirection(in vec3 iDir)
{
  float phi = atan(iDir.z, iDir.x);
  float theta = asin(iDir.y);

  return ComputeTexCoordFromPlane(phi, theta);
}
