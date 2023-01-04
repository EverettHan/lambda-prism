#ifndef CATBendDRepSeed_H
#define CATBendDRepSeed_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"
#include "CATWallBendDRepSeed.h"

#include "ListPOfCATFace.h"
#include "CATBoolean.h"


class ExportedByCATGMModelInterfaces CATBendDRepSeed: public CATWallBendDRepSeed
{
public: 
  CATBendDRepSeed(ListPOfCATFace &iRepFaces,
                  ListPOfCATCellManifold &iSkinARepCM,
                  ListPOfCATCellManifold &iSkinBRepCM,
                  ListPOfCATCellManifold &iSkinAContext0CM,
                  ListPOfCATCellManifold &iSkinAContext1CM,
                  ListPOfCATCellManifold &iSkinBContext0CM,
                  ListPOfCATCellManifold &iSkinBContext1CM,
                  double &iThickValue);
  virtual ~CATBendDRepSeed();

  virtual INLINE CATBendDRepSeed * GetAsBendDRepSeed();

  void GetContextReps(ListPOfCATCellManifold &oSkinAContext0CM,ListPOfCATCellManifold &oSkinAContext1CM,ListPOfCATCellManifold &oSkinBContext0CM,ListPOfCATCellManifold &oSkinBContext1CM);

protected:

private:
  ListPOfCATCellManifold _SkinAContext0CM, _SkinAContext1CM, _SkinBContext0CM, _SkinBContext1CM;
};

INLINE CATBendDRepSeed * CATBendDRepSeed::GetAsBendDRepSeed()
{
  return this;
}
#endif

