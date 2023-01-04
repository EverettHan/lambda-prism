// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyGeoServicesHelper.h
//
//===================================================================
// Dec  2014  Creation: JXO
// Nov  2018  Modification JXO: flags and certificate
// Apr  2019  Modification JXO: Certificates on CATIPolySurfaces
//===================================================================
#ifndef CATPolyBodyGeoServicesHelper_H
#define CATPolyBodyGeoServicesHelper_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"

class CATPolyBody;
class CATPolyBodyFlags;
class CATPolyBodyBaseAttributes;
class CATSoftwareConfiguration;
class CATPolySurfaceFlagLayer;
class CATIPolySurface;
class CATIPolyLayer;
#include "CATPolyOriginLabel.h"

// Math
#include "CATCGMScaleCategoryDef.h"

// System
#include "CATBoolean.h"
#include "CATUnicodeString.h"

/**
 * This helper should be used only internally
 */

class ExportedByPolyBodyTools CATPolyBodyGeoServicesHelper
{
public:
  CATPolyBodyGeoServicesHelper(){}
  ~CATPolyBodyGeoServicesHelper(){}
  // This just manages the flags, it won't actually check!!
  static HRESULT IsGeoValid (const CATPolyBody& iPolyBody, double iTol, CATBoolean & oNeedToCheck);
  // Will unset diagnosis, topo & geo closure, and geo diagnosis
  static HRESULT UnsetFlags (CATPolyBody& iPolyBody);
  /**
   * Returns the certificate associated with this CATPolyBody, if any.
   * @param oConfig [out, IUnknown#Release]
   *   A CATSoftwareConfiguration to be released by caller. 
   */
  static HRESULT GetCertificate(CATPolyBody& iPolyBody, CATSoftwareConfiguration *& oConfig, int & oOriginLabel, CATCGMScaleCategory & oScaleCategory);
  /**
   * Returns the certificate associated with this CATIPolySurface, if any.
   */
  static HRESULT GetCertificate(CATIPolySurface & iSurface, int & oCheckerVersion, int & oOriginLabel);

  /**
   * Depending on the certificate associated with this CATIPolySurface, returns whether is should be checked or not
   * @return
   *         S_OK: No need to check. 
   *         S_FALSE: Need to check!
   */
  static HRESULT IsGeoValid(CATIPolySurface & iSurface);

private:
  // This class behaves as an attorney
  friend class CATPolyBodyDefaultStreamer;
  friend class CATPolyBodyDefaultUnstreamer;
  friend class VisPolyExplorePolyBodyBehaviour;
  friend class CATPolyExploreTagsBehaviour;
  friend class CATPolyBodyToCATBodyChecker;
  friend class CATPolyBodyGeoCheckerODT;
  friend class CATPolyBodyStreamODT;
  friend class CATTessPolyBodyBuilder;
  CATPolyBodyFlags & GetFlags(CATPolyBodyBaseAttributes & iAtt);
  HRESULT UpdateOrPutCertificate(CATPolyBody& iPolyBody, CATSoftwareConfiguration * iConfig, Poly::OriginLabel iOriginLabel, CATCGMScaleCategory iScaleCategory);

  friend class CATPolyBodyGeoChecker;
  friend class CATPolyOriginLabelBooleanAttorney;
  friend class CATPolyOriginLabelUnsafeDualAttorney;
  friend class CATPolyOriginLabelDualAttorney;
  friend class CATPolyOriginLabelImportAttorney;
  friend class CATPolyOriginLabelRibbonAttorney;
  friend class CATPolyOriginLabelFillAttorney;
  friend class CATPolyOriginLabelRISCleanerAttorney;
  friend class CATPolyOriginLabelHWOCleanerAttorney;
  friend class CATPolyOriginLabelLatticeAttorney;
  friend class CATPolyOriginLabelTessellationAttorney;

  HRESULT UpdateOrPutCertificate(CATPolySurfaceFlagLayer & ioLayer, int iCheckerVersion, Poly::OriginLabel iOriginLabel);
  HRESULT UpdateOrPutCertificate(CATIPolySurface & iSurface, int iCheckerVersion, Poly::OriginLabel iOriginLabel);
  static void UnsetCertificate(CATIPolySurface & iSurface);

  // CATPolyDummyLayer, CATPolyBlackBoxLayer, CATPolySurfaceFlagLayer
  friend class VisLocalUtils;
  static CATUnicodeString GetTypeString(const CATIPolyLayer & iLayer);
};



#endif
