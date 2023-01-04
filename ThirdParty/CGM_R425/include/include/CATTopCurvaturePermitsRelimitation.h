/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 02:01:11
 */

/* -*-C++-*- */

#ifndef __CATTopCurvaturePermitsRelimitation_H__
#define __CATTopCurvaturePermitsRelimitation_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Cf. CATCreatePropagationEdge.h
//
// Apr. 03      Creation                                JHG
//===========================================================================


#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATSoftwareConfiguration;

CATBoolean ExportedByCATTopologicalObjects CATTopCurvaturePermitsRelimitation(CATSoftwareConfiguration *iConfig,double iCurveCandidate,
                                                                              double iCurveFrom, CATGeoFactory* iFactory);

#endif
