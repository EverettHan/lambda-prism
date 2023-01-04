// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelRISCleanerAttorney.h
//
//===================================================================
// August 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelRISCleanerAttorney_H
#define CATPolyOriginLabelRISCleanerAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelRISCleanerAttorney
{
private:
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelRISCleanerAttorney(){}
  ~CATPolyOriginLabelRISCleanerAttorney(){}
};



#endif
