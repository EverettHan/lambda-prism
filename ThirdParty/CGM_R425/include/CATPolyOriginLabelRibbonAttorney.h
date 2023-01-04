// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelRibbonAttorney.h
//
//===================================================================
// July 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelRibbonAttorney_H
#define CATPolyOriginLabelRibbonAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelRibbonAttorney
{
private:
  friend class CATGMPolyRibbonLabelizer;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelRibbonAttorney(){}
  ~CATPolyOriginLabelRibbonAttorney(){}
};



#endif
