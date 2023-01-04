in vec2 vTexCoord;

layout(location = 0) out vec4 fragColor;

const int nbCharInAtlas = 16;

vec4 GetCharacter(int iPos, int iOffset)
{
  vec2 texCoordChar = vTexCoord;
  vec2 toSum = vec2(-iPos, iPos);
  texCoordChar += toSum;
  texCoordChar.x /= nbCharInAtlas;
  texCoordChar.x += iOffset/float(nbCharInAtlas);
  
  return vTexture(sourceTex, texCoordChar);
}

void main()
{
  float frameTime = cb_cbFrameTime.u_FrameTime;
   
  if(vTexCoord.x < 1.f + 1e-5)
  {
    //Millier
    int millier = int(frameTime / 1000) % 10;
    fragColor = GetCharacter(0, millier);
  }
  else if(vTexCoord.x < 2.f + 1e-5)
  {
    //Centaine
    int centaine = int(frameTime / 100) % 10;
    fragColor = GetCharacter(1, centaine);
  }
  else if(vTexCoord.x < 3.f + 1e-5)
  {
    //Dizaine
    int dizaine = int(frameTime / 10) % 10;
    fragColor = GetCharacter(2, dizaine);
  }
  else if(vTexCoord.x < 4.f + 1e-5)
  {
    //Unite
    int unite = int(frameTime) % 10;
    fragColor   = GetCharacter(3, unite);
  }
  else if(vTexCoord.x < 5.f + 1e-5)
  {
    //Dot
    fragColor   = GetCharacter(4, 10);
  }
  else if(vTexCoord.x < 6.f + 1e-5)
  {
    //Dixieme
    int dixieme = int(frameTime * 10) % 10;
    fragColor   = GetCharacter(5, dixieme);
  }
  else if(vTexCoord.x < 7.f + 1e-5)
  {
    //m
    fragColor   = GetCharacter(6, 11);
  }
  else
  {
    //s
    fragColor   = GetCharacter(7, 12);
  }


    
    

  fragColor.w = 1;
}
