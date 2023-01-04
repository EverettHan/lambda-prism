/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//=============================================================================
// Usage Notes:
//
// This is an abstract class to handle implementation by ObjectOriented way
//
//=============================================================================
// Mar. 98   Creation                                   X. Morel
// Feb. 99   Enhancement                                H. de Wailly 
//=============================================================================

#ifndef CATExtractSameTangent_H
#define CATExtractSameTangent_H

#include "CATMathDef.h"
#include "CATCGMOperator.h"
#include "Y30A3HGG.h"
#include "CATCrvParam.h"

class CATCartesianPoint;
class CATPointOnCurve;
class CATCrvParam;
class CATCrvLimits;

class ExportedByY30A3HGG CATExtractSameTangent : public CATCGMOperator
{

  CATCGMVirtualDeclareClass(CATExtractSameTangent);
public:
/**
 * father Constructor.
 */ 
    CATExtractSameTangent(CATGeoFactory * factory) ;
  
/**
 * Destructor.
 */ 
    virtual ~CATExtractSameTangent() ;
  
  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------

    virtual CATLONG32 GetNumberOfPoints() const=0;

    virtual void BeginningPoint()=0;

    virtual CATBoolean NextPoint()=0;

    virtual CATCrvParam GetCrvParam() const = 0;

    virtual CATPointOnCurve * GetPointOnCurve() const = 0;

    virtual CATCartesianPoint *GetCartesianPoint() const=0;

    virtual void SetLimits(const CATCrvLimits &iLimits)=0;

};

#endif
