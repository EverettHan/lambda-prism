/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATMathSolveNewtonXY :
//=============================================================================
//=============================================================================
// Nov 03  Creation                          OAU
//=============================================================================

#ifndef CATMathSolveNewtonXY_H
#define CATMathSolveNewtonXY_H

class CATCGMTransfo2D;
class CATSoftwareConfiguration;

#include "CATMathSystemXY.h"

class  CATMathSolveNewtonXY : public CATMathSystemXY
{
public:

	// ctor/dtor
  CATMathSolveNewtonXY(CATSoftwareConfiguration * iConfig, CATCGMTransfo2D * iF, const CATTolerance &iTol = CATGetDefaultTolerance(),const CATMathAttrList * iattr=NULL);

    virtual ~CATMathSolveNewtonXY();


	// Information methods
    CATMathClassId IsA() const;
    int XYWanted(double xWanted,double yWanted);
	// Eval methods
    int Eval( const double & iX, const double & iY ) const;
    double EvalF( const double & iX, const double & iY ) const;
    double EvalG( const double & iX, const double & iY ) const;

protected:
	CATCGMTransfo2D * _F;
	double _xWanted,_yWanted;
};

#endif
