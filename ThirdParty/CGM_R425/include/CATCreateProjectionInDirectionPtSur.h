/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// April 98  Creation                       NDN   
//=============================================================================
#ifndef CATCreateProjectionInDirectionPtSur_H 
//
#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATGeoFactory.h"
#include "CATSurface.h"
#include "CATMathVector.h"
#include "CATMathSetOfPoints.h"
#include "CreateProjectionInDirectionPtSur.h"

class CATProjectionInDirectionPtSur;
class CATSoftwareConfiguration;
//

ExportedByY300IINT
CATProjectionInDirectionPtSur * CATCreateProjectionInDirectionPtSur (CATGeoFactory      *iFactory,
                                                                     CATSoftwareConfiguration *Config,
                                                                     const CATMathVector      *iDir,
                                                                     const CATMathSetOfPoints *iSet,
                                                                     const CATSurface         *isurface);

#endif
