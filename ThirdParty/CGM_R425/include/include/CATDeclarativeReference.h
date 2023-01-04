// ===========================================================================
// COPYRIGHT Dassault Systemes 2013
// ===========================================================================
//
//
// CATDeclarativeReference.h
// Resp : LAP
//
// Usage : Attribut to carry the CATGeometryReference.
//         For example, the DeformNurbs use it. The Nurbs knows its refrence Nurbs (the not exptrpolated Nurbs).
// 
// ===========================================================================

#ifndef CATDeclarativeReference_H
#define CATDeclarativeReference_H

#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCGMStreamAttribute.h"

class CATGeometry;
class CATCGMStream;
//class iAttrId;


class ExportedByPersistentCell CATDeclarativeReference : public CATCGMStreamAttribute
{
public :
  // Pool allocation
  CATCGMNewClassArrayDeclare;
  CATCGMDeclareAttribute(CATDeclarativeReference, CATCGMStreamAttribute);

  static void CreateDeclarativeReferenceWithClone(CATGeometry              * ipGeometry,
                                                  CATGeoFactory            * iFactory,
                                                  CATSoftwareConfiguration * iConfig);

  static void CreateDeclarativeReferenceWithTransfo(CATGeometry              * ipGeometry,
                                                    CATGeoFactory            * iFactory,
                                                    CATSoftwareConfiguration * iConfig,
                                                    CATMathTransformation    * ipTransfo,
                                                    CATGeometry              * ipSourceRefGeometry);

  // constructor to call
  CATDeclarativeReference(CATGeometry * ipGeometry, CATGeometry * ipRefGeometry);
  // destructor 
  virtual ~CATDeclarativeReference();

  // Set Reference
  void SetReference(CATGeometry * ipRefGeometry);
  // Get Reference
  CATGeometry * GetReference() const;

  // Dump
  virtual void Dump(CATCGMOutput& os) const;

  // -------------------
  // Stream Methods 
  // -------------------
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream( CATCGMStream& ioStr );

protected :
  // Default constructor
  CATDeclarativeReference();

private :
  // Internal data
  // The refrence geometry is pointed with AddLink(...).

};

#endif
