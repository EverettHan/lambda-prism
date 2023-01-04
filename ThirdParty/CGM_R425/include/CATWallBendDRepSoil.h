#ifndef CATWallBendDRepSoil_H
#define CATWallBendDRepSoil_H

#include "CATErrorDefs.h"
#include "CATDRepSoil.h"
#include "CATGMModelInterfaces.h"
#include "CATMathInline.h"

class CATFace;
//EYL Nov. 2013 Creation
class ExportedByCATGMModelInterfaces CATWallBendDRepSoil : public CATDRepSoil
{
public:	
  // Constructor
  CATWallBendDRepSoil(CATFace *iRefFace);

  // Destructor
  virtual ~CATWallBendDRepSoil();

  INLINE CATWallBendDRepSoil *GetAsWallBendDRepSoil();
  INLINE CATFace *GetReferenceFace();

private:
  CATFace *_RefFace;

};
INLINE CATWallBendDRepSoil *CATWallBendDRepSoil::GetAsWallBendDRepSoil()
{
  return this;
}
INLINE CATFace *CATWallBendDRepSoil::GetReferenceFace()
{
  return _RefFace;
}
#endif
