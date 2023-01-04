layout (local_size_x = 256, local_size_y = 1) in;

vec3 GeneratePosition()
{
  float r = GetRand();
  vec3 position;
  position.x = mix(cb_cbPSEmit.PositionMin.x, cb_cbPSEmit.PositionMax.x, r);

  r = GetRand();
  position.y = mix(cb_cbPSEmit.PositionMin.y, cb_cbPSEmit.PositionMax.y,r);

  r = GetRand();
  position.z = mix(cb_cbPSEmit.PositionMin.z, cb_cbPSEmit.PositionMax.z,r);

  return position;
}

void GenerateVelocity(uint iIndex)
{
  bVelocities.velo[iIndex].xyz = vec3(0.0);
  float r = GetRand();
  vec3 newVelo;
  newVelo.x = mix(cb_cbPSEmit.VelocityMin.x, cb_cbPSEmit.VelocityMax.x,r);
  r = GetRand();
  newVelo.y = mix(cb_cbPSEmit.VelocityMin.y, cb_cbPSEmit.VelocityMax.y,r);
  r = GetRand();
  newVelo.z = mix(cb_cbPSEmit.VelocityMin.z, cb_cbPSEmit.VelocityMax.z,r);

  float len = length(newVelo);
  if(len != 0)
  {
    newVelo = normalize(newVelo)* len;
    bVelocities.velo[iIndex].xyz = newVelo;
  }


}

float GenerateSize()
{
  float r = GetRand();
  return mix(cb_cbPSEmit.ParticuleSize.x, cb_cbPSEmit.ParticuleSize.y, r);
}

float GenerateLifeTime()
{
  float r = GetRand();
  return  mix(cb_cbPSEmit.LifeTime.x, cb_cbPSEmit.LifeTime.y, r);
}

void main() 
{
  uint index = gl_GlobalInvocationID.x ;

  if(index >= cb_cbPSEmit.MaxParticle)
    return;

  // Check if the Spawn Time is achieved
  if(cb_cbPSEmit.StartTime >= cb_PSTime.ElapsedTime)
    return;

  // Compute the current duration
  float currentDuration = cb_PSTime.ElapsedTime  - (cb_cbPSEmit.StartAt + cb_cbPSEmit.StartTime);

  float test = cb_cbPSEmit.Duration;

  // We stop the emittion if the Emitter is not in Loop mode and the Spawn duration is achieved
  if(cb_cbPSEmit.IsLoop == 0 && currentDuration > cb_cbPSEmit.Duration  )
  {
    return;
  }


  ParticleData particle = ReadParticle(4*index);

  // If LifeTime is superior to zero the particle is already emit
  if( particle.LifeTime > 0.0)
    return;

  // We reserved a particle
  int spawnNumber = atomicAdd(bCounter.count, 1);

  //If the max number of reserved particles is not achieved, we emit a particle
  if( spawnNumber < bCounter.numberOfParticle)
  {

    vec3 position = GeneratePosition();
    vec4 posTransform = cb_cbPSEmit.TransformMatrix * vec4(position, 1);
    position = posTransform.xyz;
    float size =  GenerateSize();
    vec3 color  = cb_cbPSEmit.ParticuleColor.xyz;
    float transparency = cb_cbPSEmit.ParticuleColor.w;
    float lifeCycle = GenerateLifeTime();

    GenerateVelocity(index);

    // Vertex 1
    uint realIndice = 4* index;
    ParticleData newParticle;
    newParticle.Position = position;
    newParticle.Color = color;
    newParticle.Transparency = transparency;
    newParticle.LifeTime = lifeCycle;
    newParticle.AdditionnalDT = bCounter.microDT;
    newParticle.texCoord = vec2(-size/2,-size/2);
    WriteParticle(realIndice, newParticle);

    realIndice = 4* index + 1 ;
    ParticleData newParticle1;
    newParticle1.Position = position;
    newParticle1.Color = color;
    newParticle1.Transparency = transparency;
    newParticle1.LifeTime = lifeCycle;
    newParticle1.AdditionnalDT = bCounter.microDT;
    newParticle1.texCoord = vec2(-size/2,size/2);
    WriteParticle(realIndice, newParticle1);

    realIndice = 4* index + 2 ;
    ParticleData newParticle2;
    newParticle2.Position = position;
    newParticle2.Color = color;
    newParticle2.Transparency = transparency;
    newParticle2.LifeTime = lifeCycle;
    newParticle2.AdditionnalDT = bCounter.microDT;
    newParticle2.texCoord = vec2(size/2,size/2);
    WriteParticle(realIndice, newParticle2);

    realIndice = 4* index + 3;
    ParticleData newParticle3;
    newParticle3.Position = position;    
    newParticle3.Color = color;
    newParticle3.Transparency = transparency;
    newParticle3.LifeTime = lifeCycle;
    newParticle3.AdditionnalDT = bCounter.microDT;
    newParticle3.texCoord = vec2(size/2,-size/2);
    WriteParticle(realIndice, newParticle3);

  }
}
