#ifndef CATAutoBaseColor_H
#define CATAutoBaseColor_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2005
//=============================================================================
//
// CATBaseColor.h
// 		
//=============================================================================
//  Oct 2003  Creation: JHG
//=============================================================================

class CATAutoBaseColor
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation
  CATAutoBaseColor(int iRed, int iGreen, int iBlue, int iZ = 0)
  {
    Set(iRed, iGreen, iBlue, iZ);
  }
  void Set(int iRed, int iGreen, int iBlue, int iZ = 0)
  {
    r = iRed;
    g = iGreen;
    b = iBlue;
    z = iZ;
  }
  CATAutoBaseColor(int iTag, int iZ = 0)
  {
    int n = iTag & 4095;
    int toto = n * 855;
    r = toto & 0xf;
    g = (toto >> 4) & 0xf;
    b = (toto >> 8) & 0xf;
    z = iZ;
  }
  CATAutoBaseColor(const CATAutoBaseColor& iColor)
  {
    r = iColor.r;
    g = iColor.g;
    b = iColor.b;
    z = iColor.z;
  }
  CATAutoBaseColor& operator=(const CATAutoBaseColor & iColor)
  {
    r = iColor.r;
    g = iColor.g;
    b = iColor.b;
    z = iColor.z;
    return *this;
  }
  CATBoolean HasHigherPriority(const CATAutoBaseColor & iOtherColor)
  {
    return z > iOtherColor.z;
  }

  void Darken()
  {
    r = r >> 1;
    g = g >> 1;
    b = b >> 1;
  } 

  void Randomize()
  {
    int rgb = rand() % 0xfff;
    r = (rgb >> 8) & 0xf;
    g = (rgb >> 4) & 0xf;
    b = rgb & 0xf;
    z = 0;
  }
  int r;
  int g;
  int b;
  int z;
};


#endif // !CATAutoBaseColor_H
