#ifdef _Coverage_GOO
#ifndef CATCompactFunctionImp_H
#define CATCompactFunctionImp_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//=============================================================================
// August 2003 - ALA - Creation
// 05 05 04 CCK Ajout de friend class CATCompactDump;
// Jun. 04 GetXYMinMaxQuantum(...),
//         Stream/UnStreamCompact(...),
//         Stream/UnStreamNodexxxCompact(...),
//         GetStreamValues(...)                                           HCN
// 29/09/05 CCK : Mise en Commentaire car pas de plan clairement defini pour passer sur
//                le stream compact : StreamCompact & UnStreamCompact & StreamNodeCompact
//                & StreamNodeUCompact & UnStreamNodeUCompact & StreamNodeVCompact &
//                UnStreamNodeVCompact & StreamNodeUVCompact & UnStreamNodeUVCompact
//
//=============================================================================
//
#include "CATMathDef.h" 
#include "CATMathInterval.h" 
//#include "CATCompactFunction.h"
#include "CompactFunction.h"

//#define STATISTICS_CompactFunction
#include "CATCompactFunctionImpNode.h"
#include "CATCompactFunctionImpNodeU.h"
#include "CATCompactFunctionImpNodeV.h"
#include "CATCompactFunctionImpNodeUV.h"

//
class CATCompactStreamBits;
	//
class CATCompactFunctionImpNode;
class CATCompactFunctionImpNodeU;
class CATCompactFunctionImpNodeV;
class CATCompactFunctionImpNodeUV;

class CATMathStream;

//
//		a faire : compteur de reference pour gestion memoire...
//
//
class ExportedByCompactFunction CATCompactFunctionImp 
{
public:
// Infos XMin, Xmax,etc.. a remonter dans CATCompactFunction (economie de place et d'evaluateur)
//
	// initialize a valid 0 function assuming some basic requirements such as 
	//  iQuantum >0,  iXMin < iXMax < iXMin+ 1.e20 ,etc..,
	//
	CATCompactFunctionImp() ;
	//
	CATCompactFunctionImp(	const double &iXMin,
							const double &iXMax,
							const double &iYMin,
							const double &iYMax,
							const double &iQuantum) ;
	//
	//
	~CATCompactFunctionImp();
	//
	//
	/////////////////////////
	// increment number of references
	void AddRef(); 
	//
	// decrement number of references and delete if no more referenced
	void Release();  
	/////////////////////////
	//
	//
	// evaluators
	double Eval(const double & iX, const double & iY) const;
	double EvalFirstDerivX(const double & iX, const double & iY) const;
	double EvalFirstDerivY(const double & iX, const double & iY) const;
	double EvalSecondDerivX2(const double & iX, const double & iY) const;
	double EvalSecondDerivXY(const double & iX, const double & iY) const;
	double EvalSecondDerivY2(const double & iX, const double & iY) const;
	double EvalThirdDerivX3(const double & iX, const double & iY) const;
	double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
	double EvalThirdDerivXY2(const double & iX, const double & iY) const;
	double EvalThirdDerivY3(const double & iX, const double & iY) const;
	//
	void Eval(const double u, const double v, 
		    const CATMathOption iOptions,
		    double * ioF,
		    double * ioFx =0, double * ioFy=0,
		    double * ioFx2=0, double * ioFxy=0, double *ioFy2=0) const;
	//
	// interval evaluator
	//
	void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
		    const CATMathOption iOptions,
		    CATMathInterval * f,
		    CATMathInterval * fx =0, CATMathInterval * fy=0,
		    CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
		    CATMathInterval *fy2=0) const;

	//
	//
	// return 0 if OK
	//
	/////////  Stream : return 0 if OK
	int Stream(CATCompactStreamBits &oStream);
	///////////////////////////
	/////////  UnStream : return 0 if OK
    int UnStream(CATCompactStreamBits &iStream);

  //virtual void StreamCompact(CATCompactFunctionImp* ipOtherCompactFunctionImp, CATMathStream& Str );
  //virtual void UnStreamCompact(CATCompactFunctionImp* ipOtherCompactFunctionImp, CATMathStream& Str );
  //
	//	AddRef();
	//	Release();
	//
	// virtual CATMathFunctionX * CreateIsoparX(const double & x) const;
	// virtual CATMathFunctionX * CreateIsoparY(const double & y) const;
	//
	// virtual CATMathFunctionXY * CreateDerivX() const;
	// virtual CATMathFunctionXY * CreateDerivY() const;
	//
	//
  // Pour Stream Compact
  void GetXYMinMaxQuantum(double& ioXMin, double& ioXMax, double& ioYMin, double& ioYMax, double& ioQuantum) const;
private:
	//
	friend class CATCompactApproxImp;
  friend class CATCompactDump; // CCK pour pouvoir appeler les donnees de _FunctionImp
	//
	void InitDomaine();
	void ResetAll();
	unsigned char Compress(const double &iVal, unsigned int &oInteger, unsigned char &oSign) const;
	double UnCompress(const unsigned char &iSign, const unsigned int &iInteger) const;
	//
	void InitIntervalSecondDerivative();
	void InitIntervalSecondDerivative(const double &U, const double &V);
	void InitIntervalSecondDerivativeNodeU(CATCompactFunctionImpNodeU *NU, 
															 const double &U,
															 const double &V,
															 const double &Size);
	void InitIntervalSecondDerivativeNodeV(CATCompactFunctionImpNodeV *NV, 
															 const double &U,
															 const double &V,
															 const double &Size);
	void InitIntervalSecondDerivativeNodeUV(CATCompactFunctionImpNodeUV *NUV, 
															 const double &U,
															 const double &V,
															 const double &Size);
	//
	//
	int StreamNode(CATCompactFunctionImpNode *N, CATCompactStreamBits &oStream) const;
	int UnStreamNode(CATCompactFunctionImpNode *oN , CATCompactStreamBits &iStream);
	int StreamNodeU(CATCompactFunctionImpNodeU *NU, CATCompactStreamBits &oStream) const;
	int UnStreamNodeU(CATCompactFunctionImpNodeU *oNU , CATCompactStreamBits &iStream);
	int StreamNodeV(CATCompactFunctionImpNodeV *NV, CATCompactStreamBits &oStream) const;
	int UnStreamNodeV(CATCompactFunctionImpNodeV *oNV , CATCompactStreamBits &iStream);
	int StreamNodeUV(CATCompactFunctionImpNodeUV *NUV, CATCompactStreamBits &oStream) const;
	int UnStreamNodeUV(CATCompactFunctionImpNodeUV *oNUV , CATCompactStreamBits &iStream);

  int GetStreamValues(CATCompactFunctionImpNode* N, int ioValues[2][2], int ioSigns[2][2], unsigned char& ioMask_Vals) const;

  /*int StreamNodeCompact(CATCompactFunctionImpNode* N,
                        int                        iValues[2][2],
                        int                        iSigns[2][2],
                        unsigned char*             ipMask_Vals,
                        int                        iValues_1[2][2],
                        int                        iSigns_1[2][2],
                        unsigned char              iSameVals_1[2][2],
                        int                        iValues_2[2][2],
                        int                        iSigns_2[2][2],
                        unsigned char              iSameVals_2[2][2],
                        CATMathStream&             Str) const;

	int UnStreamNodeCompact(CATCompactFunctionImpNode* oN,
                          int                        ioValues[2][2],
                          int                        ioSigns[2][2],
                          unsigned char*             ipMask_Vals,
                          int                        iValues_1[2][2],
                          int                        iSigns_1[2][2],
                          unsigned char              iSameVals_1[2][2],
                          int                        iValues_2[2][2],
                          int                        iSigns_2[2][2],
                          unsigned char              iSameVals_2[2][2],
                          CATMathStream&             Str);
*/
//	int StreamNodeUCompact(CATCompactFunctionImpNodeU *NU, CATMathStream &Str) const;
//	int UnStreamNodeUCompact(CATCompactFunctionImpNodeU *oNU , CATMathStream &Str);
//	int StreamNodeVCompact(CATCompactFunctionImpNodeV *NV, CATMathStream &Str) const;
//	int UnStreamNodeVCompact(CATCompactFunctionImpNodeV *oNV , CATMathStream &Str);
//	int StreamNodeUVCompact(CATCompactFunctionImpNodeUV *NUV, CATMathStream &Str) const;
//	int UnStreamNodeUVCompact(CATCompactFunctionImpNodeUV *oNUV , CATMathStream &Str);
	//
	//
	/////////////////////////////////////////////////////////////////////
	//
	//	fields of CATCompactFunctionImp
	//
	double _Quantum;
	//
	//
	// Infos XMin, Xmax,etc.._InvDeltaY  ->  a remonter dans CATCompactFunction
	//    et CompactSurface..         (economie de place et d'evaluateur)
	//
	//
	double _XMin;
	double _XMax;
	double _YMin;
	double _YMax;
	double _InvDeltaX; // parameter normalization
	double _InvDeltaY;
	double _LogSmall;
	//
	CATCompactFunctionImpNode *_Corner_South_West;
	CATCompactFunctionImpNode *_Corner_South_East;
	CATCompactFunctionImpNode *_Corner_North_West;
	CATCompactFunctionImpNode *_Corner_North_East;
	CATCompactFunctionImpNodeV *_West;
	CATCompactFunctionImpNodeV *_East;
	CATCompactFunctionImpNodeU *_South;
	CATCompactFunctionImpNodeU *_North;
	CATCompactFunctionImpNodeUV *_Center;
	//
	//  compteur de ref
	//
	int _RefCount;
	int _Overflow32bits;
	//
	int _IsValid;
	//
	double _fx2Min;
	double _fx2Max;
	double _fxyMin;
	double _fxyMax;
	double _fy2Min;
	double _fy2Max;
	double _fx2Abs;
	double _fxyAbs;
	double _fy2Abs;
	//
};
#endif
#endif
