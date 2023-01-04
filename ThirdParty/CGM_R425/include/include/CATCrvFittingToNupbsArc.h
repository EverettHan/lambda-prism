// COPYRIGHT DASSAULT SYSTEMES 1999 
//==========================================================================
//
// CATCrvFittingToNupbsArc:
// Interface class of the Curve Approximation in a mono arc NUPBS.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// September 99     Creation                       DHN
//========================================================================== 
//
#ifndef CATCrvFittingToNupbsArc_H
#define CATCrvFittingToNupbsArc_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateCrvFittingToNupbsArc.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATPNurbs;
class CATNurbsCurve;

//
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATCrvFittingToNupbsArc : public CATCGMVirtual
{
  public :

    virtual              ~CATCrvFittingToNupbsArc();
    virtual void         SetTolerance(const double &iToler)=0;
    virtual void         SetMaxDegree(const CATLONG32 &iMaxDegree)=0;
    virtual void         SetDimension(const CATLONG32 &iDimension)=0;  //2 for PNurbs , 3 for NurbsCurve
    virtual void         Run()=0;

    virtual CATPNurbs*       GetPArc()=0;
    virtual CATNurbsCurve*   GetArc()=0;
	virtual double           GetMaxDeviation()=0;

};
#endif
