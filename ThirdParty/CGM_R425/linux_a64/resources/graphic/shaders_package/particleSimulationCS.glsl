layout (local_size_x = 256, local_size_y = 1) in;

vec3 ComputeLocalForce(vec3 iPosition)
{
  vec3 vecForce = vec3(0.0);
  for( int i = 0 ; i < bForces.count ; i++)
  {
    Force  f = bForces.data[i];
    if(f.intensity.x == -1.0)
    {
      vecForce += f.intensity.yzw;
    }
    else
    {
      float dis = length(iPosition - f.position.xyz);
      if(dis < f.intensity.x)
      {
        vecForce += f.intensity.yzw;
      }
    }
  }
  return vecForce;
}

void UpdateParticle(uint iIndex, uint iRealIndex, vec3 iLocalForce)
{
  ParticleData particle =  ReadParticle(iRealIndex);


  if(particle.LifeTime > 0)
  {
    float dt = cb_PSTime.Tick + particle.AdditionnalDT;
    particle.AdditionnalDT = 0.0;

    particle.LifeTime -= dt;

    particle.Position += (bVelocities.velo[iIndex].xyz + 0.5*iLocalForce*dt)*dt;
    if(particle.LifeTime < 0.5*cb_cbPSEmit.LifeTime.x)
      particle.Transparency = mix(0.0, particle.Transparency, particle.LifeTime*2.0 / cb_cbPSEmit.LifeTime.x);

    if( particle.LifeTime <=0)
    {
      ResetParticle(iRealIndex);
      bVelocities.velo[iIndex] = vec4(0.0);

    }
    else
    {
      WriteParticle(iRealIndex, particle);
    }
  }

}

void main() 
{
  uint index = gl_GlobalInvocationID.x;

  if(index >= cb_cbPSEmit.MaxParticle)
    return;

  ParticleData bottom =  ReadParticle(4*index);
  vec3 center = bottom.Position;
  float dt = cb_PSTime.Tick + bottom.AdditionnalDT;

  vec3 localForce = ComputeLocalForce(center);

  UpdateParticle(index, 4*index + 0, localForce);
  UpdateParticle(index, 4*index + 1, localForce);
  UpdateParticle(index, 4*index + 2, localForce);
  UpdateParticle(index, 4*index + 3, localForce);

  bVelocities.velo[index].xyz += localForce*dt;
}
