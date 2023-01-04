//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// Data of CGM implementation for the CATSubdivSurface object
// A CATSubdivSurface is a Biparametrised surface that represent a part of a whole subdivision surface
// Mainly there is two flavors of Surface : Cells and Grid 
//=============================================================================
// Usage notes:
//
// Strictement réservé aux implémentations CGM.
//=============================================================================
//=============================================================================
// HISTORIQUE :
//
// 30/07/2008 : RNO : Creation !! 
//============================================================================= 
#ifndef CATSapSubdivSurface_H
#define CATSapSubdivSurface_H
#include "CATSapApprox.h"
#include "CATSobDiag.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"


class CATMathGridOfPoints;
class CATSapKnotVector;

class CATSobMesh;
class CATSobFace;

class CATSapEvalResult;
class CATSapSurParam;
class CATSapEvalCommand;

class CATMathFunctionXY;
class CATTolerance;

class CATMathTransformation;

class ExportedByCATSapApprox CATSapSubdivSurface : public CATCGMVirtual
{
public :
  virtual ~CATSapSubdivSurface();
  
  //Access to the Const Data of this Surface
  virtual void GetMesh(const CATSobMesh *& oSubdivMesh)  const=0 ;
  //Eval Method
  virtual CATSobDiag Eval(const CATSapSurParam & iWhere, const CATSapEvalCommand & Command, CATSapEvalResult & oResult) =0;  
  //Same as above but the LocalParam is computed internally
  virtual CATSobDiag EvalFromGlobalParam(const double iU,const double iV, const CATSapEvalCommand & Command, CATSapEvalResult & oResult) =0; 
  //Give the Number of Patch of this Surface
  virtual void GetNumberOfComponent (CATLONG32 & oUCount, CATLONG32 & oVCount) const=0; 
  //Get The Global Max Limits of this SapSurface
  virtual void GetGlobalMaxLimits(double &oUmin, double &oVmin, double &oUmax, double &oVmax)=0;
  //Get The Global Max Limits of this SapSurface (in Local Param Manner)
  virtual void GetMaxLimits(CATSapSurParam & oLow, CATSapSurParam & oHigh)=0;
  //Return The Global Limits of a Patch
  virtual void GetInternalMaxLimits(CATLONG32  iUCount, CATLONG32 iVCount,double &oUmin, double &oVmin, double &oUmax, double &oVmax)=0;
  //Returbn the Local Limit of a Patch
  virtual void GetInternalMaxLimits(CATLONG32  iUCount, CATLONG32 iVCount,CATSapSurParam & oLow, CATSapSurParam & oHigh)=0;
  //Compute a conversion from Global Param to local Param
  virtual CATSobDiag GlobalToLocalParam(const double iU,const double iV,CATSapSurParam & oLocal)=0;
    virtual CATSobDiag GlobalToLocalParamU(const double iU,CATLONG32 & oPatchU, double & oLocalU)=0;
  virtual CATSobDiag GlobalToLocalParamV(const double iV,CATLONG32 & oPatchV, double & oLocalV)=0;

  virtual CATSobDiag LocalToGlobalParam(const CATSapSurParam & iLocal, double & oU, double & oV) =0;//On peut remttre cette methode ci necessaire
  virtual CATSobDiag LocalToGlobalParamU(const double iU, const CATLONG32 iPatchU, double & oU) const =0;
  virtual CATSobDiag LocalToGlobalParamV(const double iV, const CATLONG32 iPatchV, double & oV) const =0;

  //Get The Extrapol Length in Number of Patch
  // Return True if The surface contains Extrapolated Data (ie if OffsetMinU+OffsetMaxU+OffsetMinV+OffsetMaxV>0
  virtual CATBoolean GetExtrapolOffset(int & OffsetMinU, int & OffsetMaxU, int &OffsetMinV, int &OffsetMaxV) const =0;
    //Use Equation
  //-------------------------------------------------------------------------
  //Do Not Delete returned Function 
  virtual CATSobDiag CreateLocalEquation(const CATLONG32 iPatchRankU, const CATLONG32 iPatchRankV,
                  const CATMathFunctionXY * & oFx,const CATMathFunctionXY * & oFy, const CATMathFunctionXY * & oFz) =0;
  virtual CATSobDiag CreateGlobalEquation(const CATMathFunctionXY * & oFx,
                                          const CATMathFunctionXY * & oFy,
                                          const CATMathFunctionXY * & oFz)=0;

    //Delete Equation to save Memory footprint
  //Delete Local and Global equations
  // If FullDelete==0 then the HotZone in the PCCM area is kept
  virtual void DeleteEquations(int FullDelete=1) = 0;

  virtual short GetMaxDegree() const =0;
  //Get Knots in the Canonical Base (if oHasTobeScaled==1 you have to multply them by the GetUVParameterScales
  virtual const double * GetKnotsU(short & oNumberOfKnots, short & oHasTobeScaled) const = 0;
  virtual const double * GetKnotsV(short & oNumberOfKnots, short & oHasTobeScaled) const = 0;

  virtual CATBoolean GetUVParameterScales(double & oUScale, double &oVScale) const =0;
  virtual const CATTolerance &  GetToleranceObject() const = 0;


  virtual CATBoolean IsClosedU() const =0;
  virtual CATBoolean IsClosedV() const =0;

protected:
  CATSapSubdivSurface();
  
};


#endif


