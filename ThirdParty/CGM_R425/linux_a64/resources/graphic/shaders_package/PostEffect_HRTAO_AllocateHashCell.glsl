// Output cell indices, one LOD per channel
layout(location = 0) out uvec4 cellIndices;  

void main()
{
  vec4 posNormal;
  cellIndices = allocateHashCell(ivec2(gl_FragCoord.xy), posNormal); 
}
