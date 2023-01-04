
layout (local_size_x = 1, local_size_y = 1) in;


void main() 
{
  uint index = gl_LocalInvocationIndex ;

 float mm = cb_PSTime.Tick*1000;
 mm += bCounter.spawnTime;

 float r = GetRand();

 float curSpawnNumber =  1000.0 / (mix(cb_cbPSEmit.Spawn.x, cb_cbPSEmit.Spawn.y, r));

 float partPerMm =  mm / curSpawnNumber;
 int nbParticle = int(floor(partPerMm));
 float remender = mm - nbParticle*curSpawnNumber   ;

 bCounter.spawnTime = remender;
 bCounter.numberOfParticle = nbParticle;
 bCounter.count = 0;
 bCounter.microDT = curSpawnNumber/1000;
  
}
