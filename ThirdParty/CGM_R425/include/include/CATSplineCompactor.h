/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Jul 09   Creation                                    AAD  
//=============================================================================
#ifndef CATSplineCompactor_H
#define CATSplineCompactor_H

#include "CATDataType.h"

class CATKnotVector;
class CATMathStreamImpl;
#include "CATGeoDoubleCompactor.h"
#include "ExportedByCATGeometricObjectsCGM.h"

class ExportedByCATGeometricObjectsCGM CATSplineCompactor: public CATGeoDoubleCompactor
{
public: 
	CATSplineCompactor(CATULONG32 iTag, CATMathStreamImpl * ioStream, CATMathStreamBits::FlowType iFlowType);
	~CATSplineCompactor();
  void SetKnotVector(CATKnotVector * iKnotVector);
  void SetDimension(short iDimension);
  void SetArray(double * iPoint, double * iDerivative1, double * iDerivative2);
	void Run();

	//To be called using the following line in CATPSplineCGM::Stream : 
	//CATSplineCompactor::StaticStream(ioStream, GetPersistentTag(), &_Data.KnotVector, 2, _Data.Points, _Data.Tangents, _Data.SecondDeriv);
	static void StaticStream(CATMathStreamImpl * ioStream, CATULONG32 iTag, CATKnotVector * iKnotVector, short iDimension, double * iPoint, double * iDerivative1, double * iDerivative2);
	static void StaticUnstream(CATMathStreamImpl * ioStream, CATULONG32 iTag, CATKnotVector * iKnotVector, short iDimension, double * ioPoint, double * ioDerivative1, double * ioDerivative2);

private:

	CATKnotVector * _KnotVector;
	short _Dimension; 
  short _NbKnots;
  short _NbArrays;
  const double * _Knot;
	double * _Point;
  double * _Derivative1;
  double * _Derivative2;

	void RetrieveKnotVectorData();
	void SetControlPointsDebug();
  void GetParam(int iI, int iSize, double * ioParam);
  void GetVectorCoef(int iI, int iSize, double * ioVector, double * ioOffset);
  void GetMatrixCoef(double * iParam, int iSize, double * ioMatrix);
  void GetPolynomCoef(double iParam, int iDerivativeOrder, int iLength, double * ioMatrixLine);
  void EvaluatePolynom(double * iVector, int iSize, double Param, double * ioComputedRef);
  int GetComputedRef(int iI, int iOrder, double * ioComputedRef);
  void GetComputedRefWithSize(int iI, int iSize, double * ioComputedRef);
  void GetComputedRef1(int iI, double * ioComputedRef);
  void HandleArray(int iI, double * ioArray, double * iComputedRef, int iDebugType, int ThresholdExponent);
	void HandleArray();

	CATSplineCompactor(const CATSplineCompactor &);
	void operator = (const CATSplineCompactor &);
};

#endif
