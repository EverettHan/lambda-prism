#ifndef CATWallBendDRepSeed_H
#define CATWallBendDRepSeed_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"
#include "CATDRepSeed.h"

#include "ListPOfCATFace.h"
#include "ListPOfCATCellManifold.h"

class CATWallDRepSeed;
class CATBendDRepSeed;
class ExportedByCATGMModelInterfaces CATWallBendDRepSeed: public CATDRepSeed
{
public: 
  CATWallBendDRepSeed(ListPOfCATFace &iRepFaces,
                      ListPOfCATCellManifold &iSkinARepCM,
                      ListPOfCATCellManifold &iSkinBRepCM,
                      double &iThickValue);

  virtual ~CATWallBendDRepSeed();

  virtual INLINE CATWallBendDRepSeed * GetAsWallBendDRepSeed();
  virtual INLINE CATWallDRepSeed * GetAsWallDRepSeed();
  virtual INLINE CATBendDRepSeed * GetAsBendDRepSeed();

  INLINE double GetThickValue();
  void GetSkinReps(ListPOfCATCellManifold &oSkinARepCM,ListPOfCATCellManifold &oSkinBRepCM);

protected:

private:
  ListPOfCATCellManifold _SkinARepCM,_SkinBRepCM;
  double _ThickValue;

};

INLINE CATWallBendDRepSeed * CATWallBendDRepSeed::GetAsWallBendDRepSeed()
{
  return this;
}
INLINE CATWallDRepSeed * CATWallBendDRepSeed::GetAsWallDRepSeed()
{
  return NULL;
}
INLINE CATBendDRepSeed * CATWallBendDRepSeed::GetAsBendDRepSeed()
{
  return NULL;
}
INLINE double CATWallBendDRepSeed::GetThickValue()
{
  return _ThickValue;
}

#endif

