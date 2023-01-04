/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Jul 09   Creation                                       AAD  
// Sep 10   Optimization by CATConvertFromDoubleRShiftA    PR
//          _CPFixedPoint64RShift, _CPFixedPoint64 and _ControlPoints are
//          allocated on 4 units more, enabling pipelining in asm utilities;
//          those 4 units must be zero-initialized
//=============================================================================
#ifndef CATNurbsSurfaceCompactor_H
#define CATNurbsSurfaceCompactor_H

#include "CATDataType.h"

class CATMathStreamImpl;
#include "CATGeoDoubleCompactor.h"
#include "CATFixedPoint64.h"
#include "YN000FUN.h"
#include "CATMathInline.h" 

#include "CATArithTypes.h"

#ifdef NurbsCompactOptimPR
class CATMathPoolThread;
#endif

#define TINYBUFFER 0x10000
extern "C" void CATConvertFromDoubleRShiftA
  (double* iDouble, CATFixedPoint64::NumberRShift* oA, CATLONG32 iNbCells);

class ExportedByYN000FUN CATNurbsSurfaceCompactor: public CATGeoDoubleCompactor
{
public: 
	CATNurbsSurfaceCompactor(CATULONG32 iTag, CATMathStreamImpl * ioStream, CATLONG32 iNbCP[2],CATMathStreamBits::FlowType iFlowType,  CATBoolean iAllComputation);
	~CATNurbsSurfaceCompactor();

	INLINE void SetControlPoints(double * iControlPoints);
  INLINE void SetGrevilleParameters(double * iParam[2]);
	void Run();

	//To be called using the following line in CATNurbsSurfaceCGM::Stream : 
	//CATNurbsSurfaceCompactor::StaticStream(ioStream, GetPersistentTag(), &_Data.KnotVectorU, &_Data.KnotVectorV, _Data.Vertices)
  // iParam : Greville parameters;
  // iNbCP : Number of control points 
  // iAllComputation : if TRUE , computer the prediction points in all cases. Otherwise, computer the prediction points in case 3. 
	static void StaticStream(CATMathStreamImpl * ioStream, CATULONG32 iTag,  double * iControlPoints, double * iParam[2], CATLONG32 iNbCP[2], CATBoolean iAllComputation);
	static void StaticUnstream(CATMathStreamImpl * ioStream, CATULONG32 iTag,  double * ioControlPoints, double * iParam[2], CATLONG32 iNbCP[2], CATBoolean iAllComputation);

//#ifdef NurbsCompactOptimPR
protected:
  void ThreadAddV3 ( silla Tid, silla Debut, silla Fin );
//#endif

private:
	enum CompactionType { Incremental1, Incremental2 };


	CATLONG32 _N[2]; 
  double * _Param[2];
  CATBoolean _ParamCopy;
	double * _ControlPoints;
	CompactionType _CompactionType;
  CATBoolean _AllComputation;
  CATFixedPoint64::Number * _CPFixedPoint64;
  CATFixedPoint64::NumberRShift * _CPFixedPoint64RShift;
#ifdef NurbsCompactOptimPR
  CATMathPoolThread *_Pool;  
#endif
  int                _MaxInBuffer;      // max # of useful Number's in Buffer

  void FullCompactor();
  void FastCompactor();
	void HandleControlPoints();
	unsigned int GetType(int i, int j);
	void GetComputedCPIncremental(int i, int j, CATFixedPoint64::Number  oVertex[3]);
	void ComputeCompactionParamIncremental();
	void GetComputedCPIncrementalCase1(int iUorV, int i, int j, CATFixedPoint64::Number oVertex[3]);
	void GetComputedCPIncrementalCase2(int iUorV, int i, int j, CATFixedPoint64::Number  oVertex[3]);
	void GetComputedCPIncrementalCase3(int i, int j, CATFixedPoint64::Number oVertex[3]);
  void GetComputedCPIncrementalCase3_Full(int i, int j, CATFixedPoint64::Number oVertex[3]);
	void GetComputedCPIncrementalCase4(int iUorV, int i, int j, CATFixedPoint64::Number  oVertex[3]);
	void GetComputedCPIncrementalCase5(int i, int j, CATFixedPoint64::Number  oVertex[3]);

	CATNurbsSurfaceCompactor(const CATNurbsSurfaceCompactor &);
	void operator = (const CATNurbsSurfaceCompactor &);
};




INLINE void CATNurbsSurfaceCompactor::SetControlPoints(double * iControlPoints)
{
  _ControlPoints = iControlPoints;
}

void CATNurbsSurfaceCompactor::SetGrevilleParameters(double * iParam[2] )
{
  if(iParam)
  {
    _Param[0] = iParam[0];
    _Param[1] = iParam[1];
  }
}

#endif
