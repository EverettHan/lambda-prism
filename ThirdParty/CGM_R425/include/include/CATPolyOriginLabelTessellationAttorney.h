// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyOriginLabelTessellationAttorney.h
//
//===================================================================
// October 2020  Creation: JXO
//===================================================================
#ifndef CATPolyOriginLabelTessellationAttorney_H
#define CATPolyOriginLabelTessellationAttorney_H

#include "PolyBodyTools.h"

// Math
#include "CATCGMScaleCategoryDef.h"

#include "CATErrorDef.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyOriginLabelTessellationAttorney
{
private:
  friend class CATGMPolyTessellationLabelizer;
  static HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATCGMScaleCategory iScaleCategory);
  static HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface);

private:
  // For coverage 
  friend class CATPolyBodyGeoCheckerODT;
  CATPolyOriginLabelTessellationAttorney(){}
  ~CATPolyOriginLabelTessellationAttorney(){}
};



#endif
