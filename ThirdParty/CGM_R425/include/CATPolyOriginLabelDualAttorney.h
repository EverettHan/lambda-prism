// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelDualAttorney.h
//
//===================================================================
// August 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelDualAttorney_H
#define CATPolyOriginLabelDualAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelDualAttorney
{
private:
  friend class CATFuzzyDualLabelizer;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelDualAttorney(){}
  ~CATPolyOriginLabelDualAttorney(){}
};



#endif
