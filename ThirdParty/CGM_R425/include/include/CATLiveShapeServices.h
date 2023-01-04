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

#ifndef CATLiveShapeServices_H
#define CATLiveShapeServices_H

#include "CATPersistentCell.h"

class CATGeoFactory;
class CATFace;

class ExportedByPersistentCell CATLiveShapeServices
{
public :

  static CATBoolean AreVisuallyIdenticalFaces(CATFace       & iPreviousFace,
                                              CATFace       & iResultFace,
                                              CATGeoFactory & iFactory,
                                              CATSoftwareConfiguration * ipConfig);


};

#endif
