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
#ifndef CreateProjectionInDirectionPtSur_H 
#define CreateProjectionInDirectionPtSur_H 
//
#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATGeoFactory.h"
#include "CATSurface.h"
#include "CATMathVector.h"
#include "CATMathSetOfPoints.h"
class CATProjectionInDirectionPtSur;
//
/**
* @deprecated V5R13 CATCreateProjectionInDirectionPtSur
*/
ExportedByY300IINT
   CATProjectionInDirectionPtSur * CreateProjectionInDirectionPtSur (CATGeoFactory            *iFactory,
                                                                     const CATMathVector      *iDir,
                                                                     const CATMathSetOfPoints *iSet,
                                                                     const CATSurface         *isurface,
                                                                     CATSkillValue             iMode = BASIC);
//
ExportedByY300IINT
   void Remove(CATProjectionInDirectionPtSur *&iProjectionInDirectionPtSur);

#endif
