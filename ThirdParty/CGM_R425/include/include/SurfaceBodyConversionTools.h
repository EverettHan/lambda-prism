#ifndef SurfaceBodyConversionTools_h
//=============================================================================
// 24/02/2017  G5S  Creation from functions that were in CATSplitTools.cpp.  
//                  Code from there refactored into new method CreateBodyByUnlimitingPlanesForSplit(...).
//=============================================================================
#define SurfaceBodyConversionTools_h

#include "CATBoolean.h" //System
#include "CATTopDefine.h" //GMModelInterfaces
#include "ExportedByCATTopologicalObjects.h" //NewTopologicalObjects

class CATBody;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATSurface;
class CATFace;

// Check whether a surface is a plane.
CATBoolean SurfaceIsPlane(CATSurface * iSurface);

CATBoolean BodyOn1NonInfiniteFaceOnAPlane(CATBody * iBody);

// Create  a body from the max limits of a surface.  If the surface came from a body, 
// you can specify a face from that body.
CATBody * CreateFromPositioningSurface(CATGeoFactory * iFactory,
                                       CATSoftwareConfiguration * iConfig,
                                       CATSurface * iSurface,
                                       CATCGMJournalList * ioJournal,
                                       CATFace * iOriginalFaceForJournal);

// If the body consists of a single plane, simply unlimit the plane and create a new body containing the 
// infinite plane.  Check the orientation of the new body's shell to decide whether we should invert
// the selection side if we're doing a split. 
// If the body doesn't consist of a single plane, return NULL and set oMustInvertSelectionSide = FALSE.
ExportedByCATTopologicalObjects CATBody * CreateBodyByUnlimitingPlanesForSplit(CATGeoFactory            * iFactory, 
                                                                               CATSoftwareConfiguration * iConfig, 
                                                                               CATBody                  * iSkinBody, 
                                                                               CATCGMJournalList        * ioJournal, 
                                                                               CATBoolean               & oMustInvertSelectionSide);

#endif
