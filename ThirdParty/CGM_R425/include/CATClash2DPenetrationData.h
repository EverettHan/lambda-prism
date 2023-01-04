//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATClash2DPenetrationData:
//    Header file for the implementation of the CATClash2D penetration data.
//
//=============================================================================
// Usage notes:
//=============================================================================
// 16/06/14 : XMH : Creation
// 15/07/15 : XMH : Add tolerance.
// 20/07/15 : XMH : Use resolution for comparison of penetration data.
// 23/09/15 : XMH : Method DumpOutput
// 03/10/15 : XMH : Avoid transformed pcurve for line and circle edges (requires
//                  replacement of CATCrvParam and CATCrvLimits by doubles)
//=============================================================================
#ifndef CATClash2DPenetrationData_H
#define CATClash2DPenetrationData_H


// Mathematics
#include "CATMathDirection2D.h"
#include "CATMathPoint2D.h"

// Geometry
#include "CATCrvParam.h"

// Misc.
#include "CATBoolean.h"
#include "CATDataType.h" // for CATLONG32

// Classes
class CATEdge;

class CATClash2DPenetrationData
{
public :
   // Constructors
   CATClash2DPenetrationData();

   // Destructor
   virtual ~CATClash2DPenetrationData();
   //-----------------------------------------------------------------------
   //- Results methods
   //-----------------------------------------------------------------------

   // Gets the number of penetration data items.
   virtual CATLONG32 GetNumberOfPenetrationData() const = 0;

   // Initializes the penetration data iterator.
   virtual void BeginPenetrationData() const = 0;

   // Increments the penetration data iterator to the next clash region.
   virtual CATBoolean NextPenetrationData() const =0 ;

   // Returns a penetration data of the body
   virtual CATBoolean GetPenetrationData(CATEdge            *& oPenetrationEdge,
                                         CATCrvParam         & oPenetrationParam,
                                         CATMathPoint2D      & oPenetrationPoint,
                                         CATMathDirection2D  & oPenetrationDirection,
                                         double              & oPenetrationDepth) const = 0;

};

#endif
