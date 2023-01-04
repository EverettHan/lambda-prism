// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelFillAttorney.h
//
//===================================================================
// August 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelFillAttorney_H
#define CATPolyOriginLabelFillAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelFillAttorney
{
private:
  friend class CATGMPolyFillLabelizer;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelFillAttorney(){}
  ~CATPolyOriginLabelFillAttorney(){}
};



#endif
