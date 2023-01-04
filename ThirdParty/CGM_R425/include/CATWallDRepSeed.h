#ifndef CATWallDRepSeed_H
#define CATWallDRepSeed_H

#include "CATMathInline.h"

#include "CATGMModelInterfaces.h"
#include "CATWallBendDRepSeed.h"

#include "ListPOfCATFace.h"
#include "CATBoolean.h"


class ExportedByCATGMModelInterfaces CATWallDRepSeed: public CATWallBendDRepSeed
{
public: 
  CATWallDRepSeed(ListPOfCATFace &iRepFaces,
                  ListPOfCATCellManifold &iSkinARepCM,
                  ListPOfCATCellManifold &iSkinBRepCM,
                  double &iThickValue); 
  virtual ~CATWallDRepSeed();

  virtual INLINE CATWallDRepSeed * GetAsWallDRepSeed();

protected:

private:
};

INLINE CATWallDRepSeed * CATWallDRepSeed::GetAsWallDRepSeed()
{
  return this;
}
#endif

