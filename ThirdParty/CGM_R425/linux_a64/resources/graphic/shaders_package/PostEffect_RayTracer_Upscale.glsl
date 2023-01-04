void main()
{   
  vec2  deltaPixel        = vec2(0.5);
  vec2  sizeSrc           = vec2(vTextureSize(s_SourceTex, 0));
  ivec2 coordMinPixelSrc  = ivec2(vAbs(vFloor(vTexCoord.xy * sizeSrc - deltaPixel)));
  vec2  coordMin          = (vec2(coordMinPixelSrc)+deltaPixel        )/sizeSrc;
  vec2  coordMax          = (vec2(coordMinPixelSrc)+vec2(1)+deltaPixel)/sizeSrc;

  vec2 coord1 = coordMin;
  vec2 coord2 = vec2(coordMin.x, coordMax.y);
  vec2 coord3 = vec2(coordMax.x, coordMin.y);
  vec2 coord4 = coordMax;
  

  float z  = (GetZ(vTexCoord));
  float z1  = (GetZ(coord1));
  float z2  = (GetZ(coord2));
  float z3  = (GetZ(coord3));
  float z4  = (GetZ(coord4));
  float deltaZ1 = vAbs(z-z1);
  float deltaZ2 = vAbs(z-z2);
  float deltaZ3 = vAbs(z-z3);
  float deltaZ4 = vAbs(z-z4);
  
  vec2 coord = coord1;
  float deltaZ = deltaZ1;
  if (deltaZ2<deltaZ) 
  {
    deltaZ = deltaZ2;
    coord = coord2;
  }
  if (deltaZ3<deltaZ) 
  {
    deltaZ = deltaZ3;
    coord = coord3;
  }
  if (deltaZ4<deltaZ) 
  {
    deltaZ = deltaZ4;
    coord = coord4;
  }
  if (deltaZ1==deltaZ2 && deltaZ2==deltaZ3 && deltaZ3==deltaZ4)
    coord = vTexCoord;

  vec4 col = GetEffectTexture(s_SourceTex, coord);

  col.w = 1.0;
      
  FRAGCOLOR = col;
}




