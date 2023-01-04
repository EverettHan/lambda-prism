/**
 * @COPYRIGHT DASSAULT SYSTEMES 2020
 */

/* -*-c++-*- */
//===========================================================================
//
// Interface pour accès aux données Maths des CATLine 
// Permet d'eviter une dépendance buildtime sur GeometricObjects
// Cf implémentation dans GeometricObjectsCGM : CATLineCGM_CATIMathLine
// Fait au départ pour Afr3DCompassUI
//
// 01/12/2020 PKC Creation                                              
//===========================================================================

#ifndef CATIMathLine_h
#define CATIMathLine_h

#include "YN000MAT.h"
#include "CATBaseUnknown.h"

class CATMathLine;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYN000MAT const IID IID_CATIMathLine;
#else
extern "C" const IID IID_CATIMathLine;
#endif
/**
* Interface to access Math Description of a Line
*/
class ExportedByYN000MAT CATIMathLine : public CATBaseUnknown
{
   CATDeclareInterface;
public:
  /**
  * Get Math Line Object Describing the Line 
  *
  *  @param oMathLine    : Math Line
  *
  *  @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */
   virtual HRESULT  GetMathLine(CATMathLine &oMathLine) = 0;
};

CATDeclareHandler(CATIMathLine, CATBaseUnknown);

#endif
