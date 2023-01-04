/* -*-c++-*- */
#ifndef CATCGMExtrapolated_h
#define CATCGMExtrapolated_h
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Managing nested Extrapolated geometric objects
//============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATCGMEvents.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATICGMUnknowns.h"

class CATHashTabCATCGMEvolutions;
class CATICGMObject;
class CATCGMEvolutions;

class ExportedByGeometricObjects CATCGMExtrapolated : public CATCGMEventExtrapolation
{
public:
  CATCGMExtrapolated(CATGeoFactory *iFactory); 
  ~CATCGMExtrapolated(); 
  CATCGMNewClassArrayDeclare;

  virtual void Extrapolation(CATCurve   *iCurve,   const CATCrvLimits & iBefore, const CATCrvLimits & iAfter) ;
  virtual void Extrapolation(CATSurface *iSurface, const CATSurLimits & iBefore, const CATSurLimits & iAfter) ;

  // Do not Forget to clean with delete []  the potential allocated arrays 
  //     ioCrvBefore ioCrvAfter ioSurBefore  ioSurAfter
  void GetCompactLog(CATLISTP(CATCurve)      &ioCurves, 
                     CATCrvLimits          * &ioCrvBefore,
                     CATCrvLimits          * &ioCrvAfter,

                     CATLISTP(CATSurface)    &ioSurfs,
                     CATSurLimits          * &ioSurBefore,
                     CATSurLimits          * &ioSurAfter );


  // Obtention de la liste des Courbes/Surfaces logges en extrapolation/desextrapolation
  void GetCompactLog(CATLISTP(CATICGMUnknown)  & ioSurfacesOrCurves);

private :

  CATHashTabCATCGMEvolutions  *_Evolutions;  

  CATCGMEvolutions  * NeedLog(CATICGMObject *iObject); 
  void                CleanHashTabFromDeadObjects(); 
};


#endif
