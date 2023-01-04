//====================================================================
// Copyright Dassault Systemes Provence 2008, all rights reserved 
//====================================================================
//
//======================================================================
// 11/05/2009 : RNO : Ajout ComputeGridClosure
// May 2008-> May 2009 RNO Ajout Fonctions SapGridExpander,MakePolynoms,MakePiecewise,EvalFunction
// Fev,      13 th 2008 Creation                                    ANR
//======================================================================

#ifndef CATSapUtilities_H 
#define CATSapUtilities_H 

#include "CATSapApprox.h"
#include "CATSobDiag.h"
#include "CATDataType.h"
#include "CATBoolean.h"



class CATSobFace; 
class CATSapKnotVector;
class CATMathGridOfPoints;
class CATMathPolynomXY;
class CATMathFunctionXY;
class CATMathPiecewiseXY;
class CATSapEvalCommand;
class CATSapEvalResult; 

#define USECELLRANKATTR

#ifdef USECELLRANKATTR
#ifndef SPECIALAPPEND

#define SPECIALAPPEND(LIST,ELEM)\
{ LIST.Append(ELEM); ELEM->SetCellRank(LIST.Size(),reinterpret_cast <CATLONGPTR>(&LIST));}

#define FASTLOCATE(LIST,ELEM)\
  (ELEM)->GetCellRank(reinterpret_cast <CATLONGPTR>(&LIST))

#define FREEKEYS(LIST)\
  { int FreeKeySize##LIST=LIST.Size();\
  for(int i##LIST=1;i##LIST<=FreeKeySize##LIST;i##LIST++)\
    {\
    LIST[i##LIST]->FreeRankKey(reinterpret_cast <CATLONGPTR>(&LIST));\
    }\
    }

#endif
#endif

#define USEMEMSET "memset au lieu d'une boucle"
#ifdef USEMEMSET 
#define ZEROIFY(ARRAY,NBELEM,TYPE)\
  memset(ARRAY,0,NBELEM*sizeof(TYPE));
#else
#define ZEROIFY(ARRAY,NBELEM,TYPE) \
{register TYPE * Sweep = ARRAY; register TYPE * EndArray    = ARRAY+NBELEM; while (Sweep < EndArray){ *Sweep=0; Sweep++;}}
#endif

#ifndef CATSapcxCharNew
#define CATSapcxCharNew(iNumberOfShort)    (char *)CATCGMemBook( (iNumberOfShort)*sizeof(char) ,CATCGMemoryProvider_BestSoFar)
#define CATSapcxCharFree(iAllocated)                CATCGMemClear((void *)iAllocated     ,CATCGMemoryProvider_BestSoFar)
#endif


//Expanse the Grid From One Face To a Grid:
//Inputs : the starting Face (Origin) the Edge Index in that face {1,2,3,4}, the Number of Faces in U and V
//Return : the Grid of Faces
ExportedByCATSapApprox 
CATSobDiag SapGridExpander(CATSobFace * iOrigin, short iUEdgeIndx, int NU, int NV, CATSobFace **& oGridOfFace);


//This Method "transform" the NURBS Basis into the Polynomial Basis
// IF inputs Polynoms pointer are Null than it is automatically allocated and the caller hace to delete them 
CATSobDiag  MakePolynoms( const CATLONG32 iPatchRankU,
                         const CATLONG32 iPatchRankV,
                         const CATMathGridOfPoints * Vertices,
                         const CATSapKnotVector * KU,
                         const CATSapKnotVector * KV,
                         CATMathPolynomXY *& PolynomX,
                         CATMathPolynomXY *& PolynomY,
                         CATMathPolynomXY *& PolynomZ)  ;

//This methods make a Piecewiese Funtion from an array of Polynoms iu*NbPatch+iv;

CATSobDiag MakePiecewise(const CATMathFunctionXY ** iPolynomsX,
                         int iNbPatch, int iNbPatchV,
                         const double * iKnotsU,
                         const double * iKnotsV,
                         CATMathPiecewiseXY *& oGX);


CATSobDiag EvalFunction(const CATMathFunctionXY * PolyX,const CATMathFunctionXY * PolyY,const CATMathFunctionXY * PolyZ,
                       double LocalParamU,double LocalParamV,const CATSapEvalCommand & Command, CATSapEvalResult & oResult);


int SameKV(CATSapKnotVector * KV1, CATSapKnotVector * KV2);


ExportedByCATSapApprox
void ZoneDefinition(int ZoneNum, int BaseGridNU, int BaseNV,int OffsetMinU, int OffsetMaxU, int OffsetMinV, int OffsetMaxV,
                    int & oZoneSizeU, int & oZoneSizeV, int & oDecalU,int & oDecalV);

//Swith XY in the Poly PNew(U,V)=POld(V,U);
// !!! REPLACE THE ORIGINAL POLYNOM (BECAUSE WE NEED TO MODIFY IT
//CATSobDiag  SwitchXYInPolynomXY( CATMathPolynomXY *& OldPoly);


//Recognize C2 Canonical Sap Knot Vector return a non null SapKnotVector if succeeded
ExportedByCATSapApprox
CATSapKnotVector * RecognizeSapKV(short iDegree, int NbKnots, const double * Knots );

#endif


