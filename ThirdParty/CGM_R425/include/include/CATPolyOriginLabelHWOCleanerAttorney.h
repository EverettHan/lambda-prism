// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelHWOCleanerAttorney.h
//
//===================================================================
// August 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelHWOCleanerAttorney_H
#define CATPolyOriginLabelHWOCleanerAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelHWOCleanerAttorney
{
private:
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelHWOCleanerAttorney(){}
  ~CATPolyOriginLabelHWOCleanerAttorney(){}
};



#endif
