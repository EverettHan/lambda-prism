// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CATBoundingPCurves
// 
//
//===================================================================
// May 2000        		Creation	PKC / FDN
//===================================================================

#ifndef CATBoundingTools_H
#define CATBoundingTools_H

#include "Y30UIUTI.h"

#include "CATSurLimits.h"
#include "CATCrvLimits.h"
class CATGeoFactory;
class CATGeometry;
class CATSurface;
class CATCurve;
class CATPCurve;


//-------------------------------------------------------------------
// creation des 4 PCurves Bords correspondants a un blocUV donne
//-------------------------------------------------------------------

ExportedByY30UIUTI void CreateBoundingOnSurf(CATGeoFactory      *  iFactory,
                                             CATSurface         *  iSurface, 
                                             const CATSurLimits &  iSurLimits,
                                             CATGeometry        *& oPCurveUMin,
                                             CATGeometry        *& oPCurveUMax,
                                             CATGeometry        *& oPCurveVMin,
                                             CATGeometry        *& oPCurveVMax);

//-------------------------------------------------------------------
// creation des 2 cones Bords correspondants a un blocW donne
//-------------------------------------------------------------------

ExportedByY30UIUTI void CreateBoundingOnCurve(CATGeoFactory      *  iFactory,
                                              CATCurve           *  iCurve, 
                                              const CATCrvLimits &  iCrvLimits,
                                              CATGeometry        *& oBoundingStart,
                                              CATGeometry        *& oBoundingEnd);

//-------------------------------------------------------------------
// creation d'un cone sur une courbe
//-------------------------------------------------------------------

ExportedByY30UIUTI void CreateBoundingCone(CATGeoFactory     *  iFactory,
                                           CATCurve          *  iCurve, 
                                           const CATCrvParam &  iCrvParam,
                                           double               iConeLenght,
                                           int                  iOrientation,
                                           CATGeometry       *& oCone);


#endif
