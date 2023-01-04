// Packed Structure for optimized acced
struct ParticlePackedData
{
  vec4 d0;
  vec4 d1;
  vec4 d2;
};

//Real structure of the vbo
struct ParticleData
{
  vec3  Position;
  vec3  Color;
  float LifeTime;
  float Size;
  float Transparency;
  float AdditionnalDT;
  vec2  texCoord;
};

//SSBO corresponding to the vbo
//layout(std140) coherent buffer particles {
//  ParticlePackedData data[];
//} bParticles;

//SSBO corresponding to the velocity
//layout(std140) buffer velocities{
//  vec4 velo[];
//} bVelocities;

//SSBO correspond to some counter
//layout(std140) coherent buffer counters{
//  int count;
//  float numberOfParticle;
//  float spawnTime;
//  float microDT;
//} bCounter;

struct Force
{
  vec4 position;
  vec4 intensity;
};

//SSBO corresponding to the forces
//layout(std140) readonly buffer forces{
//  float count;
//  float pad0;
//  float pad1;
//  float pad2;
//
//  Force data[];
//} bForces;


int countRand = 0;

int Combine(int iSeed, int iVal)
{
  iSeed ^= iVal + int(0x9e3779b9) + (iSeed << 6) + (iSeed >> 2);
  return iSeed;
}


//Function to generata a random number
float GetRand()
{
  ++countRand;

  int x = countRand;
  x = Combine(x, floatBitsToInt(fract(cb_PSTime.ElapsedTime*1023)));
  x = Combine(x, int(gl_GlobalInvocationID.x));

  int y = Combine(x, int(gl_GlobalInvocationID.x));

  countRand = Combine(countRand, y);
  vec4 color = vTexelFetch(random, ivec2(x % 1024, y % 1024), 0);
  uvec4 uvalue = uvec4(255.0 * color.x, 255.0 * color.y, 255.0 * color.z, 255.0 * color.w);
  uint combineValue = uvalue.x + (uvalue.y << 8);
  return float(combineValue) / (256.0 * 256.0 - 1);
}

//helper to convert a packed particle to a Particle
ParticleData ReadParticle(uint iIndex)
{
  ParticlePackedData particlePacked = bParticles.data[iIndex];

  ParticleData particle;
  particle.Position = particlePacked.d0.xyz;
  particle.Color = vec3(particlePacked.d0.w, particlePacked.d1.xy);
  particle.LifeTime = particlePacked.d1.z;
  particle.Size = particlePacked.d1.w;
  particle.Transparency = particlePacked.d2.x;
  particle.AdditionnalDT  = particlePacked.d2.y;
  particle.texCoord = vec2(particlePacked.d2.z, particlePacked.d2.w);
  return particle;
}

//helper to convert a Particle to a packed particle
void WriteParticle(uint iIndex, ParticleData iParticle)
{
  ParticlePackedData particlePacked;
  particlePacked.d0 = vec4(iParticle.Position, iParticle.Color.x);
  particlePacked.d1 = vec4(iParticle.Color.yz, iParticle.LifeTime, iParticle.Size);
  particlePacked.d2 = vec4(iParticle.Transparency, iParticle.AdditionnalDT, iParticle.texCoord.x, iParticle.texCoord.y);

  bParticles.data[iIndex] = particlePacked;
}

//helper to reset a particle
void ResetParticle(uint iIndex)
{
  ParticlePackedData particlePacked;
  particlePacked.d0 = vec4(0.0);
  particlePacked.d1 = vec4(0.0);
  particlePacked.d2 = vec4(0.0);

  bParticles.data[iIndex] = particlePacked;
}
