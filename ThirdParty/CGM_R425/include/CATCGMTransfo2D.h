/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATCGMTransfo2D :
//=============================================================================
//=============================================================================
// Nov 03  Creation                          OAU
//=============================================================================

#ifndef CATCGMTransfo2D_H
#define CATCGMTransfo2D_H

class CATCGMTransfo2D;
class CATMathPlane;
class CATBody;
class CATMathSolveNewtonXY;

#include "YN000FUN.h"
#include "CATMathDef.h" // CATMathOption
#include "CATMathInterval2D.h"
#include "CATTolerance.h"

class CATSoftwareConfiguration;

class ExportedByYN000FUN CATCGMTransfo2D
{
public:

	virtual ~CATCGMTransfo2D();
	// Virtual Pure
	virtual int Eval( double iU,double iV,CATMathOption iEvalOption,double iDU,double iDV,double &oFu,double &oFV,double &oDU,double &oDV ) = 0;
		
	virtual int SetPlane(CATMathPlane *iMathPlane) = 0;
	virtual int GetPlane(CATMathPlane *&oMathPlane) = 0;

	virtual int SetSupportSkin(CATBody *iSupportSkin) = 0;
	virtual int GetSupportSkin(CATBody *&oSupportSkin) = 0;
	// Virtual
	virtual int ReverseEval( double iU,double iV,CATMathOption iEvalOption,double iDU,double iDV,double &oFu,double &oFV,double &oDU,double &oDV);
	virtual int ReverseEvalPoint(double iU,double iV,double &oFU,double &oFV);
	virtual int ReverseEvalFirstDeriv(double iU,double iV,double iDU,double iDV,double &oDU,double &oDV);

protected:
//	CATCGMTransfo2D(const CATTolerance &iTol = CATGetDefaultTolerance());
  CATCGMTransfo2D(CATSoftwareConfiguration * iConfig, const CATTolerance &iTol = CATGetDefaultTolerance());

private:
	CATCGMTransfo2D(const CATCGMTransfo2D &);
	void operator = (const CATCGMTransfo2D &);

protected:
  CATSoftwareConfiguration* _Config;  // KJD 13OCT2009 softwareconfig pour "versioning"
  CATMathSolveNewtonXY * _SolveNewtonXY;
  CATMathInterval2D  _iD;	
};

#endif
