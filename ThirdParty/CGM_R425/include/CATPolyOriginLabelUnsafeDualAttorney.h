// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelUnsafeDualAttorney.h
//
//===================================================================
// August 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelUnsafeDualAttorney_H
#define CATPolyOriginLabelUnsafeDualAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelUnsafeDualAttorney
{
private:
  friend class CATFuzzyDualLabelizer;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelUnsafeDualAttorney(){}
  ~CATPolyOriginLabelUnsafeDualAttorney(){}
};



#endif
