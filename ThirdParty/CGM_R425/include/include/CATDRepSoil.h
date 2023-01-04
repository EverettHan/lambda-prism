#ifndef CATDRepSoil_H
#define CATDRepSoil_H

#include "CATErrorDefs.h"
#include "CATCGMVirtual.h"
#include "CATGMModelInterfaces.h"
#include "CATMathInline.h"

class CATWallBendDRepSoil;
//EYL Nov. 2013 Creation
//Generic Class For Input datas given by Applicative Framework needed in Seeds Creation

class ExportedByCATGMModelInterfaces CATDRepSoil : public CATCGMVirtual
{
public:	
	// Constructor
  CATDRepSoil();

  // Destructor
	virtual ~CATDRepSoil();

  //GetAs
  virtual INLINE CATWallBendDRepSoil *GetAsWallBendDRepSoil();

private:

};
INLINE CATWallBendDRepSoil* CATDRepSoil::GetAsWallBendDRepSoil()
{
  return NULL;
}
#endif
