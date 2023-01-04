// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
// CATCDMBaseServicesStreamUtilities.h
//
//===================================================================
//
// Usage notes: CDM services to stream or unstream a CDMManager (and all CDM objects attached to it) and hold the model with a CATCDMBaseServices object
//
//===================================================================
//
//  Dec 2010  Creation: chu
//===================================================================
#ifndef CATCDMBaseServicesStreamUtilities_H
#define CATCDMBaseServicesStreamUtilities_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATErrorDef.h"          // HRESULT definition

class CATMathStream;
class CATCDMBaseServices;
class CATGeoFactory;

class ExportedByCATCDMBaseInterfaces CATCDMBaseServicesStreamUtilities
{
public:

  // Standard constructors and destructors
  CATCDMBaseServicesStreamUtilities ();
  virtual ~CATCDMBaseServicesStreamUtilities ();

  // Stream the CDM Model from a CATCDMBaseSerices (dedicated to CGM internal)
  // No GN graph is required here, GN pointers are converted on the fly into cgmid's
  static HRESULT StreamCDMWithoutGN(CATCDMBaseServices & iBaseServices, CATMathStream & oCDMStream);

  // Unstream the CDM Model, a CATCDMBaseServices is created that should be deleted when no more used 
  // Note that providing a CATGeoFactory is required if the CDM model includes solved labels (CDMIDs to bodies and cells) and if they are going to be investigated
  static HRESULT UnstreamCDMWithoutGN(CATMathStream & iCDMStream, CATCDMBaseServices *& oBaseServices, CATGeoFactory * iFactory = 0, double* iScaleFactor = 0);

private:
  
  // Copy constructor and equal operator are not implemented
  CATCDMBaseServicesStreamUtilities (CATCDMBaseServicesStreamUtilities &);
  CATCDMBaseServicesStreamUtilities& operator=(CATCDMBaseServicesStreamUtilities&);

  // No data

};

//-----------------------------------------------------------------------

#endif
