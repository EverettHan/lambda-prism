//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// Data of CGM implementation for the CATSubdivCellSurface object
//
//=============================================================================
// Usage notes:
//
// Strictement réservé aux implémentations CGM.
//=============================================================================
//=============================================================================
// HISTORIQUE :
//
// 24/01/2008 : RNO : Creation !! 
//============================================================================= 
#ifndef CATSapSubdivCellSurface_H
#define CATSapSubdivCellSurface_H
#include "CATSapApprox.h"
#include "CATSobDiag.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"
#include "CATSapSubdivSurface.h"





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

class ExportedByCATSapApprox CATSapSubdivCellSurface : public CATSapSubdivSurface
{
public :
  virtual ~CATSapSubdivCellSurface();

  virtual void GetSobFace(const CATSobFace * & oSobFace, unsigned char & oDaughterFace)const=0;
  virtual const CATSapKnotVector *GetKnotVector() const = 0 ;
  virtual const CATMathGridOfPoints * GetControlPoints() const = 0;

  //Order to apply a Scaling on the parameter /!\ The derivatives will be modified
  // By Default the Surfaces are parametrized from 0 to 1
  virtual void SetUVParameterScales(const double iUScale, const double iVScale)=0;
  //Get the UV Scale Parameter
  virtual CATBoolean GetUVParameterScales(double & oUScale, double & oVScale) const=0;
  //Compute a rough approximation of the dimension
  virtual CATSobDiag ComputePseudoCurvilinearScales(double & oUScale, double & oVScale)=0;
protected:
  CATSapSubdivCellSurface();
  
};


//Scale : <0 Auto, >0 Manual, =1 Same Has original
ExportedByCATSapApprox CATSapSubdivCellSurface * 
CATCreateSapSubdivCellSurface(const CATTolerance & TolObject,
                              CATSobMesh * SobMesh,
                              CATSobFace *	Face,
                              unsigned char	Daughter,
                              const double iScaleU, const double iScaleV);


//Scale : <0 Auto, >0 Manual, =1 Same Has original
// OPtimised Copy
ExportedByCATSapApprox CATSapSubdivCellSurface * 
CATCreateSapSubdivCellSurfaceFromAnotherOne(const CATTolerance & TolObject,
                                                        CATSobMesh * SobMesh,
                                                          CATSobFace *	Face,
                                                          unsigned char	Daughter,
                                       const double iScaleU, const double iScaleV,
                                       CATSapSubdivCellSurface * iSapSubbdivCellRef,
                                       CATMathTransformation * iOptionalMathTransfo=0);

#endif


