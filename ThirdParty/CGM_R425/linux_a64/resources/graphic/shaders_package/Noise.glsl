#ifdef Noise
#define NBOCTAVES 10
///////////////////// NOISES

//////// NOISES UTILITIES
float quinticPoly(in float iValue)
{
    float iValue3 = vPow(iValue,3);
    return iValue3 * (iValue * (iValue * 6.0 - 15.0) + 10.0);
}

vec3 quinticPoly3D(vec3 iVector)
{
    return iVector*iVector*iVector * (iVector * (iVector * 6.0 - 15.0) + 10.0);
}

int fastfloor(float iValue) 
{
	return (iValue >= 0) ? int(iValue) : int(iValue-1);
}

vec3 mod289(vec3 iVector) {
  return iVector - vFloor(iVector * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 iVector) {
  return iVector - vFloor(iVector * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 iVector) {
     return mod289(((iVector*34.0)+1.0)*iVector);
}

vec4 taylorInvSqrt(vec4 iVector) 
{
	return 1.79284291400159 - 0.85373472095314 * iVector;
}

vec3 hash3(vec3 iVector) {
    vec3 q = vec3(vDot(iVector, vec3(127.1, 311.7, 189.2)),
                  vDot(iVector, vec3(269.5, 183.3, 324.7)),
                  vDot(iVector, vec3(419.2, 371.9, 128.5)));
    return vFract(vSin(iVector) * 43758.5453);
}
//////// END NOISES UTILITIES

// Optimisation by Stefan Gustavson
float perlinNoise3D(in vec3 iVector) 
{
	vec3 vectori0 = vFloor(iVector);
	vec3 vectori1 = vectori0 + vec3(1.0);
	vectori0 = mod289(vectori0);
	vectori1 = mod289(vectori1);

	vec3 vectorf0 = vFract(iVector);
	vec3 vectorf1 = vectorf0 - vec3(1.0);

	vec4 ix = vec4(vectori0.x,vectori1.x,vectori0.x,vectori1.x);
	vec4 iy = vec4(vectori0.yy,vectori1.yy);
	vec4 iz0 = vectori0.zzzz;
	vec4 iz1 = vectori1.zzzz;

	//// permutations
	vec4 ixy = permute(permute(ix)+iy);
	vec4 ixy0 = permute(ixy + iz0);
	vec4 ixy1 = permute(ixy + iz1);

	//// gradient coordinates
	vec4 gx0 = ixy0 / 7.0;
	vec4 gy0 = vFract(vFloor(gx0) / 7.0) - 0.5;
	gx0 = vFract(gx0);
	vec4 gz0 = vec4(0.5) - vAbs(gx0) - vAbs(gy0);
	vec4 sz0 = vStep(gz0, vec4(0.0));
	gx0 -= sz0 * (vStep(0.0, gx0) - 0.5);
	gy0 -= sz0 * (vStep(0.0, gy0) - 0.5);

	//// gradient coordinates
	vec4 gx1 = ixy1 / 7.0;
	vec4 gy1 = vFract(vFloor(gx1) / 7.0) - 0.5;
	gx1 = vFract(gx1);
	vec4 gz1 = vec4(0.5) - vAbs(gx1) - vAbs(gy1);
	vec4 sz1 = vStep(gz1, vec4(0.0));
	gx1 -= sz1 * (vStep(0.0, gx1) - 0.5);
	gy1 -= sz1 * (vStep(0.0, gy1) - 0.5);

	//// gradients for each faces of the cube
	vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
	vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
	vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
	vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
	vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
	vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
	vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
	vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

	//// Normalize gradients
	vec4 norm0 = taylorInvSqrt(vec4(vDot(g000, g000), vDot(g010, g010), vDot(g100, g100), vDot(g110, g110)));
	g000 *= norm0.x;
	g010 *= norm0.y;
	g100 *= norm0.z;
	g110 *= norm0.w;
	vec4 norm1 = taylorInvSqrt(vec4(vDot(g001, g001), vDot(g011, g011), vDot(g101, g101), vDot(g111, g111)));
	g001 *= norm1.x;
	g011 *= norm1.y;
	g101 *= norm1.z;
	g111 *= norm1.w;


	//// influence of each faces of the cube
	float n000 = vDot(g000, vectorf0);
	float n100 = vDot(g100, vec3(vectorf1.x, vectorf0.yz));
	float n010 = vDot(g010, vec3(vectorf0.x, vectorf1.y, vectorf0.z));
	float n110 = vDot(g110, vec3(vectorf1.xy, vectorf0.z));
	float n001 = vDot(g001, vec3(vectorf0.xy, vectorf1.z));
	float n101 = vDot(g101, vec3(vectorf1.x, vectorf0.y, vectorf1.z));
	float n011 = vDot(g011, vec3(vectorf0.x, vectorf1.yz));
	float n111 = vDot(g111, vectorf1);

	//// linear interpolation
	vec3 fade_xyz = quinticPoly3D(vectorf0);
	vec4 n_z = vMix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
	vec2 n_yz = vMix(n_z.xy, n_z.zw, fade_xyz.y);
	float n_xyz = vMix(n_yz.x, n_yz.y, fade_xyz.x); 
	return 2.2 * n_xyz;
}

/// Optimisation by Ian McEwan
float simplexNoise3D(in vec3 iVector) 
{
	vec2 C = vec2(1.0/6.0,1.0/3.0);
	vec4 D = vec4(0.0,0.5,1.0,2.0);

	//// First corner
	vec3 i = vFloor(iVector + vDot(iVector,C.yyy));
	vec3 x0 = iVector - i + vDot(i,C.xxx);

	//// other corners
	vec3 g = vStep(x0.yzx, x0.xyz);
	vec3 l = 1.0 - g;
	vec3 i1 = vMin(g.xyz,l.zxy);
	vec3 i2 = vMax(g.xyz,l.zxy);

	//
	vec3 x1 = x0 - i1 + 1.0 * C.xxx;
	vec3 x2 = x0 - i2 + 2.0 * C.xxx;
	vec3 x3 = x0 - 1.0 + 3.0 * C.xxx;

	//// permutations
	i = mod289(i);
	vec4 p = permute(permute(
					permute(i.z + vec4(0.0,i1.z,i2.z,1.0)) 
					+ i.y + vec4(0.0,i1.y,i2.y,1.0)) 
					+ i.x + vec4(0.0,i1.x,i2.x,1.0));
	//// get gradients
	const float n = 1.0/7.0;
	vec3 ns = n * D.wyz - D.xzx;

	vec4 j = p - 49.0 * vFloor(p*ns.z*ns.z);

	vec4 x = vFloor(j * ns.z);
	vec4 y = vFloor(j - 7.0 * x);

	x = x* ns.x + ns.yyyy;
	y = y * ns.x + ns.yyyy;
	vec4 h = 1.0 - vAbs(x)-vAbs(y);

	vec4 b0 = vec4( x.xy, y.xy );
	vec4 b1 = vec4( x.zw, y.zw );

	vec4 s0 = vFloor(b0)*2.0 + 1.0;
	vec4 s1 = vFloor(b1)*2.0 + 1.0;
	vec4 sh = -vStep(h, vec4(0.0));

	vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
	vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

	vec3 p0 = vec3(a0.xy,h.x);
	vec3 p1 = vec3(a0.zw,h.y);
	vec3 p2 = vec3(a1.xy,h.z);
	vec3 p3 = vec3(a1.zw,h.w);

	//// Normalize gradients
	vec4 norm = taylorInvSqrt(vec4(vDot(p0,p0), vDot(p1,p1), vDot(p2, p2), vDot(p3,p3)));
	p0 *= norm.x;
	p1 *= norm.y;
	p2 *= norm.z;
	p3 *= norm.w;

	//// Linear interpolation
	vec4 m = vMax(0.6 - vec4(vDot(x0,x0), vDot(x1,x1), vDot(x2,x2), vDot(x3,x3)), 0.0);
	m = m * m;
	return 42.0 * vDot(m*m, vec4(vDot(p0,x0), vDot(p1,x1), 
                               vDot(p2,x2), vDot(p3,x3)));
}
///////////////////// END NOISES

///////////////////// MIXERS


float getMean(in float LODLevel) {
  float mult = 1.8;
	float LOD = 3;
  float oldLOD = 0;
  for (int i = NBOCTAVES-1; i >= 0; i--) {
    float pente = 1.0 / (LOD-oldLOD);
    float origine = i + 1 + oldLOD * pente;
    if (LODLevel <= LOD) {
      return origine - pente * LODLevel;
    }
    oldLOD = LOD;
    LOD *= mult;
	}
	return 0.0;
}

float FBM(in vec3 iVector) 
{
	vec3 vector = iVector;
	float res = 0.0;		
	float amplitude = 1.0;
	float sum = 0.0;
  for (int octave = 0; octave < NBOCTAVES  ; octave++) {
    if (amplitude < 10*kEpsilon) {
			break;
    }  
		vector = vector * 2;
		sum += amplitude;		
		res += simplexNoise3D(vector) * amplitude;			
		amplitude *= 0.5;
	}
  return vClamp(res/sum,-1.0,1.0);
}

float arrayFBMMixer(in vec3 iVector, in float LODLevel, in float frequency) 
{
	vec3 vector = iVector;
	float res = 0.0;		
	float sum = 0.0;
	float variance = 1.5;
  float mean = getMean(LODLevel);
	float amplitude;
  int minIndex = int(vMax(0.0,mean-5.0));
  int maxIndex = int(vMin(1.0*NBOCTAVES,mean+5.0));
	frequency *= vPow(1.8, minIndex); 
  for (int octave = minIndex; octave < maxIndex ; octave++) {
		vec3 vec = vector * frequency;	
		frequency *= 1.8;	
		amplitude = vGaussian(octave,mean,variance);	
		sum += amplitude;	
		res += simplexNoise3D(vec) * amplitude;	
	}
  return vClamp(res/sum,-1.0,1.0);
}
///////////////////// END MIXERS
#endif
