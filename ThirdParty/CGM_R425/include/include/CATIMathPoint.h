/**
 * @COPYRIGHT DASSAULT SYSTEMES 2020
 */

 /* -*-c++-*- */
 //===========================================================================
 //
 // Interface pour accès aux données Maths des CATPoint 
 // Permet d'eviter une dépendance buildtime sur GeometricObjects
 // Cf implémentation dans GeometricObjectsCGM : CATPointCGM_CATIMathPoint
 // Fait au départ pour Afr3DCompassUI
 //
 // 01/12/2020 PKC Creation                                              
 //===========================================================================

#ifndef CATIMathPoint_h
#define CATIMathPoint_h

#include "YN000MAT.h"
#include "CATBaseUnknown.h"

class CATMathPoint;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYN000MAT const IID IID_CATIMathPoint;
#else
extern "C" const IID IID_CATIMathPoint;
#endif
/**
* Interface to access Math Description of a CGM Point
*/
class ExportedByYN000MAT CATIMathPoint : public CATBaseUnknown
{
   CATDeclareInterface;
public:
   /**
   * Get Math Point Object Describing the CGM Point
   *
   *  @param oMathPoint    : Math Point
   *
   *  @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
   virtual HRESULT  GetMathPoint(CATMathPoint &oMathPoint) = 0;
};

CATDeclareHandler(CATIMathPoint, CATBaseUnknown);

#endif
