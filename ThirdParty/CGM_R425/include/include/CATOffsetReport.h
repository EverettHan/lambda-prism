//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATOffsetReport
//  Base class for parameters reports management between two surfaces linked
//  by an offset relation not necesseraly isoparametric. If so, a linear
//  UV-transformation will be computed by the operator and used for reports.
//
//=============================================================================
// June 2005   Creation                                              CQI
//=============================================================================

#ifndef CATOffsetReport_H
#define CATOffsetReport_H

#include "Y30UIUTI.h"

#include "CATCGMVirtual.h"
#include "CATGeoOperator.h"
#include "CATMathDef.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATSurface;
class CATSurParam;
class CATSoftwareConfiguration;
class CATMathTransformation2D;

class ExportedByY30UIUTI CATOffsetReport  : public CATCGMVirtual
{

 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATOffsetReport(CATGeoFactory * iFactory,
                  CATSoftwareConfiguration * iConfig,
                  CATSurface * iFromSurface,
                  CATSurface * iToSurface);
  
  ~CATOffsetReport();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  CATBoolean Run();

  // Perform direct SurParam report 'iFromSurface' ---> 'iToSurface'.
  // For an inverse report, 'iToSurface' ---> 'iFromSurface' call method with iDirect = FALSE
  CATBoolean GetEquivalentParam(const CATSurParam & iParam, CATSurParam & oEquivalentParam, CATBoolean iDirect = TRUE); 

  // Fills coefficients of oTransfoUV if UV non-isoparametric offset has been detected
  // It does nothing if offsets are isoparametric.
  // For inverse transformation, ie. 'iToSurface' ---> 'iFromSurface' call method with iDirect = FALSE
  CATBoolean GetLinearTransfoUV(CATMathTransformation2D & oTransfoUV, CATBoolean iDirect = TRUE);

  // Returns TRUE if non-isoparametric UV offset has been detected,
  // FALSE otherwise
  CATBoolean IsIsoParametricUV();

 protected:
   //-----------------------------------------------------------------------
   //- Protected methods
   //-----------------------------------------------------------------------
   CATBoolean Initialize();
   // Returns FALSE if offset link is known to be isoparametric, ie. report function is identity, TRUE otherwise
   // (for example. iToSurface = ProcOffsetType with reference = iFromSurface)
   CATBoolean IsRelevant();
   // Compute offset radius length between iFromSurface and iToSurface, with iFromSurface as reference
   CATBoolean ComputeOffset();
   // Compute linear UV transformation T(u,v) which maps UV-space of iToSurface from iFromSurface
   CATBoolean ComputeUVTransfo();
   // Compute UV reports thanks to offset relation Soffset = S + Roffset * N
   CATBoolean ReportParam(const CATSurParam & iParam, CATSurParam & oReportedParam, CATBoolean iDirect = TRUE);
   
   //-----------------------------------------------------------------------
   //- Data
   //-----------------------------------------------------------------------
   
   CATGeoFactory            * _Factory;
   CATSoftwareConfiguration * _Config;
   
   // Input data
   CATSurface * _FromSurface;
   CATSurface * _ToSurface;
   CATSurface * _FromSurfaceRef;
   CATSurface * _ToSurfaceRef;

   // Offset link data
   CATLength   _Roffset;
  
   // Linear UV-transformation for non-isoparametric offset
   CATMathTransformation2D * _LinearTransfoUV;
   CATMathTransformation2D * _InverseLinearTransfoUV;

   // Run diagnostic
   CATBoolean _RunDiag;
};


#endif

