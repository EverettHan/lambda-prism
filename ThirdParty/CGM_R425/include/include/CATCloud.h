#ifndef CATCloud_h
#define CATCloud_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATCloud.
 */
#include "CATClay.h"
#include "CATMathBox.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCloud ;
#else
extern "C" const IID IID_CATCloud ;
#endif


class ExportedByCATGMGeometricInterfaces CATCloud : public CATClay
{
  CATDeclareInterface;

public:

// Get the index of the first point of a given characteristic box.
  virtual CATLONG32 GetIndexOfFirstPointInACharacteristicBox (CATLONG32 IndexOfBox) const = 0;

// Get the index of the characteristic box containing a point.
  virtual CATLONG32 GetIndexOfCharacteristicBox (const float * iPointInBox) const = 0;
  
// Get the characteristic box for an index.
  virtual void GetCharacteristicBox (CATLONG32 IndexOfBox,CATMathBox &ioBox) const = 0;

// Get points in a characteristic box.
  virtual const float * GetPointsInACharacteristicBox (CATLONG32 iIndexOfBox,
						       CATLONG32 & oNumberOfPoints) const = 0;
  
// Get points in an union of Characteristic Boxes.
  virtual float * GetPointsInABox (const CATMathBox &iBox,
				   CATLONG32 & oNumberOfPoints) const = 0;
  
};
CATDeclareHandler(CATCloud,CATClay);

#endif
