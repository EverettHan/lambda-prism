
#ifndef CATNurbsSurfaceCompactorF_H
#define CATNurbsSurfaceCompactorF_H

#include "CATDataType.h"


class CATMathStreamImpl;
#include "CATGeoFloatCompactor.h"
#include "CATFloatCompactor.h"
#include "YN000FUN.h"


class ExportedByYN000FUN CATNurbsSurfaceCompactorF: public CATGeoFloatCompactor
{
public: 
	CATNurbsSurfaceCompactorF(CATULONG32 iTag, CATMathStreamImpl * ioStream, CATLONG32 iNbCP[2],CATMathStreamBits::FlowType iFlowType, CATBoolean iAllComputation);
	~CATNurbsSurfaceCompactorF();

	void SetControlPoints(float * iControlPoints);
  void SetGrevilleParameters(float * iParam[2]);
	void Run();

	//To be called using the following line in CATNurbsSurfaceCGM::Stream : 
	//CATNurbsSurfaceCompactorF::StaticStream(ioStream, GetPersistentTag(), &_Data.KnotVectorU, &_Data.KnotVectorV, _Data.Vertices)
  // iParam : Greville parameters;
  // iNbCP : Number of control points 
  // iAllComputation : if TRUE , computer the prediction points in all cases. Otherwise, computer the prediction points in case 3.
	static void StaticStream(CATMathStreamImpl * ioStream, CATULONG32 iTag,  float * iControlPoints, float * iParam[2], CATLONG32 iNbCP[2], CATBoolean iAllComputation);
	static void StaticUnstream(CATMathStreamImpl * ioStream, CATULONG32 iTag,  float * ioControlPoints, float * iParam[2], CATLONG32 iNbCP[2], CATBoolean iAllComputation);

  
  

private:
	enum CompactionType { Incremental1, Incremental2 };


	CATLONG32 _N[2]; 
  float * _Param[2];
	float * _ControlPoints;
	CompactionType _CompactionType;
  CATBoolean _AllComputation;


	void HandleControlPoints();
	unsigned int GetType(int i, int j);
	void GetComputedCPIncremental(int i, int j, float  oVertex[3]);
	void ComputeCompactionParamIncremental();
	void GetComputedCPIncrementalCase1(int iUorV, int i, int j, float oVertex[3]);
	void GetComputedCPIncrementalCase2(int iUorV, int i, int j, float  oVertex[3]);
	void GetComputedCPIncrementalCase3(int i, int j, float oVertex[3]);
	void GetComputedCPIncrementalCase4(int iUorV, int i, int j, float  oVertex[3]);
	void GetComputedCPIncrementalCase5(int i, int j, float  oVertex[3]);

  

	CATNurbsSurfaceCompactorF(const CATNurbsSurfaceCompactorF &);
	void operator = (const CATNurbsSurfaceCompactorF &);
};

#endif
