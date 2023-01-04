/**
 * @COPYRIGHT DASSAULT SYSTEMES 2020
 */

 /* -*-c++-*- */
 //===========================================================================
 //
 // Interface pour accès aux données Maths des CATPlane 
 // Permet d'eviter une dépendance buildtime sur GeometricObjects
 // Cf implémentation dans GeometricObjectsCGM : CATPlaneCGM_CATIMathPlane
 // Fait au départ pour Afr3DCompassUI
 //
 // 01/12/2020 PKC Creation                                              
 //===========================================================================

#ifndef CATIMathPlane_h
#define CATIMathPlane_h

#include "YN000MAT.h"
#include "CATBaseUnknown.h"

class CATMathPlane;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYN000MAT const IID IID_CATIMathPlane;
#else
extern "C" const IID IID_CATIMathPlane;
#endif
/**
* Interface to access Math Description of a Line
*/
class ExportedByYN000MAT CATIMathPlane : public CATBaseUnknown
{
   CATDeclareInterface;
public:
   /**
   * Get Math Line Object Describing the Line
   *
   *  @param oMathPlane    : Math Line
   *
   *  @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
   virtual HRESULT  GetMathPlane(CATMathPlane &oMathPlane) = 0;
};

CATDeclareHandler(CATIMathPlane, CATBaseUnknown);

#endif
