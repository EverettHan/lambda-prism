/* -*-c++-*- */
#ifndef CATPositionBoxFaceOperator_h
#define CATPositionBoxFaceOperator_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// CATPositionBoxFaceOperator:
// 
/**
 * This operator defines if a 2D Box is inside a Face.
 * The box is defined by a set of CATMathPoint2D. 
 */ 
//
//=============================================================================
// Usage Notes:
//
//=============================================================================
// Mar. 2000  Creation                                  lr
//=============================================================================

#include "CATTopDef.h"
#include "CATMathPoint2D.h"
#include "CATErrorDef.h"

class CATGeoFactory;
class CATFace;
class CATTopData;
class CATMathBox2D;
class CATMathOBB2D;


#include "ExportedByCATTopologicalObjects.h"

class ExportedByCATTopologicalObjects CATPositionBoxFaceOperator
{

 public :
  CATPositionBoxFaceOperator();
  virtual ~CATPositionBoxFaceOperator();

  // to prepare setting
  virtual void  Reset() = 0;
  
  // to set new box  data  
  virtual void  SetBoxPts(int  iNbPoints,  CATMathPoint2D * iPoints) = 0;
  virtual void  GetBox2DPoint(CATMathBox2D & oBox2D ) = 0;
  virtual void  SetTolerance(double) = 0;
  virtual HRESULT  GetPointOBB2D(CATMathOBB2D & oBB2DPoint)= 0;
  virtual HRESULT  SetPointOBB2D(CATMathOBB2D & iBB2DPoint)= 0;
  // to do the job and give status
  virtual CATBoolean  Run() = 0;

};

ExportedByCATTopologicalObjects
CATPositionBoxFaceOperator*  CreatePositionBoxFaceOperator(CATGeoFactory * iFactory, CATTopData *iTopData, CATFace * iFace);

#endif
