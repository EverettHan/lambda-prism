// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelBooleanAttorney.h
//
//===================================================================
// July 2019  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelBooleanAttorney_H
#define CATPolyOriginLabelBooleanAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

// System
#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelBooleanAttorney
{
private:
  friend class CATPolyOverlayBodyBuilder;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelBooleanAttorney(){}
  ~CATPolyOriginLabelBooleanAttorney(){}
};



#endif
