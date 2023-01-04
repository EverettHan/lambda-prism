// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelLatticeAttorney.h
//
//===================================================================
// October 2020  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelLatticeAttorney_H
#define CATPolyOriginLabelLatticeAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelLatticeAttorney
{
private:
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelLatticeAttorney(){}
  ~CATPolyOriginLabelLatticeAttorney(){}
};



#endif
