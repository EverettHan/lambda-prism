#ifndef CATSapConstantsTypes_H
#define CATSapConstantsTypes_H 

//====================================================================
// Copyright Dassault Systemes Provence 2008, all rights reserved 
//====================================================================
//
// Une seule instance par session ! permettant de fournir des SapKnotVector qui reviennent tres souvent dans les subdivisions
// Permet d'avoir une seule instance du KV pour des milliers de surfaces
// La construction/destruction des KV est gere par cette classe "Factory"
// Idem pour les MathGridOfpoints ... on a un container qui s'occupe de gerer ces objets et donc de partager les meme CP entre deux SubdivCell !!


// 
//======================================================================
// 01/07/2008 : RNO : Creation
//======================================================================
#include "CATIACGMLevel.h"
#include "CATSapKnotVector.h"
#include "CATSapApprox.h"
class CATMathNxNBandSymMatrix;
class CATMathPolynomX;
class CATMathGridOfPoints;
//Enumrate the Different Type of Configuration For One Level
//#define SAPSTATISTICS



const int NBKUVType=14;
//Attention ne jamais changer la numerotation (Impact Stream)
typedef enum
{
  KUV_UNKNOWN_ERROR         =-1,       //Shoul never Happen
  KUV_BEZIER_CUBIQUE        = 0,
  KUV_NURBS_C2_CUBIQUE      = 1,
  KUV_NURBS_C2_DEG_6        = 2,
  KUV_NURBS_C2_DEG_6_Opti   = 3, //For Level== 2 Only
  KUV_NURBS_C2_DEG_6_TRI    = 4, //( TRIANGULAIRE )
  KUV_NURBS_C1_DEG_3_WK     = 5, //Working KV for Quad
  KUV_NURBS_C0_DEG_6_WK     = 6, //Working KV for Quad
  KUV_NURBS_C1_DEG_3_TRI_WK = 7, //Working KV for Tri-Quad
  KUV_NURBS_C0_DEG_6_TRI_WK = 8, //Working KV for Tri-Quad
  KUV_NURBS_C0_DEG_6_Opti_WK= 9, //For Level== 2 Only
  KUV_BEZIER_DEG_1          = 10, //Degree 1 for Extrapol (One arc)
  KUV_NURBS_C2_DEG_5        = 11,  //Degree 5 for Extrapol (4 arcs)
  KUV_NURBS_EXTC2_DEG_5_014 = 12,  //Degre 5 avec noeuds en 0,1,4
  KUV_NURBS_EXTC2_DEG_5_034 = 13  //Degre 5 avec noeuds en 0,3,4

} CATSAPKVType;

#ifdef SAPSTATISTICS
void IncrzStatsForType(const CATSAPKVType iType);
void DumpStatsByTypes();
void ResetStats();
#endif


const int NBChangeVectorType =8;
typedef enum
{
  CHANGE_UNKNOWN                          =-1,
  CHG_KUV_C1_DEG_3_TO_KUVBezier           =0, //KUV_NURBS_C1_DEG_3_WK ==> KUV_BEZIER_CUBIQUE
  CHG_KUV_C1_DEG_3_TO_C2_CUBIQUE          =1,  //KUV_NURBS_C1_DEG_3_WK ==> KUV_NURBS_C2_CUBIQUE
  CHG_KUV_C1_DEG_3_TO_C0_DEG_6            =2, //KUV_NURBS_C1_DEG_3_WK ==> KUV_NURBS_C0_DEG_6_WK
  CHG_KUV_C1_DEG_3_TO_C0_DEG_6_TRI        =3,//KUV_NURBS_C1_DEG_3_WK ==> KUV_NURBS_C0_DEG_6_WK (NoOPti for level2 Case)
  CHG_KUV_C0_DEG_6_TO_C2_DEG_6            =4, //KUV_NURBS_C0_DEG_6_WK ==> KUV_NURBS_C2_DEG_6
  CHG_KUV_C0_DEG_6_TO_C2_DEG_6_TRI        =5, //KUV_NURBS_C0_DEG_6_WK ==> KUV_NURBS_C2_DEG_6 For Tri-Quad (NoOPti for level2 Case)
  CHG_KUV_C1_DEG_3_TRI_TO_C0_DEG_6_TRI    =6, //KUV_NURBS_C1_DEG_3_TRI_WK ==> KUV_NURBS_C0_DEG_6_TRI_WK  
  CHG_KUV_C0_DEG_6_TRI_TO_C2_DEG_6_TRI    =7  //KUV_NURBS_C0_DEG_6_TRI_WK ==> KUV_NURBS_C2_DEG_6_TRI
  
} CATSAPChangeKVType;







//Same Class as CATSapKnotVector With AddRef/Release
//Pour des raison de Code 77 (La SapKnotVector factory est detruite apres le check de MLK)
// on doit faire un KV avec addref release + pointeur retour
class ExportedByCATSapApprox CATSapKnotVectorAuto: public CATSapKnotVector
{
public:
  CATSapKnotVectorAuto(const  CATSAPKVType _MyType,const CATLONG32 iDegree=3);
  CATSapKnotVectorAuto (const  CATSAPKVType _MyType, const CATLONG32 &iDegree,
    const CATLONG32 &iIsPeriodic,const CATLONG32 &iNbOfKnots, const double * iKnots, const CATLONG32* iMultiplicities, const CATLONG32 iIndexOffset=0 );
  ~CATSapKnotVectorAuto(); 
  CATSAPKVType GetKVType ();
  INLINE CATBoolean IsAKnotVectorAuto() const;
  // ------------------------------------------------------------------------------
  //--->  Update CATMathPolynom for one arc   
  void UpdatePolynomsForAllArcs(CATLONG32 iIsShifted) const  ;
private:
  const  CATSAPKVType _MyType;
};

INLINE CATBoolean CATSapKnotVectorAuto::IsAKnotVectorAuto() const
{
  return(TRUE);
}

class CATSAPChangeKVResult
{

public:
  CATSAPChangeKVResult();
  ~CATSAPChangeKVResult();//A voir ce qu'il faut detruire
  int        _SizeOfTransfPol;
  double  *  _TransfPol;
  int       _SizeOfoTabImp;
  int     * _TabImp;
  int     * _OldBase;
  int       _Periodic;
  CATMathNxNBandSymMatrix  * _NewMat;
  int      _WhichDer;
  int      _NewSize;
  CATMathPolynomX         ** _NewPol;
  CATMathPolynomX         ** _OldPol;
  CATMathNxNBandSymMatrix  * _TempMat; 
  CATMathNxNBandSymMatrix  * _FactoCholesky; 
  int                       _error;
};


//The CATSapGridOfPointsHolder will manage the lifecycle (Through AddRef/Release) of the CATMathGridOfPoints it holds
// When the Holder it destroys the Grid too !
//Use the Creator above

class CATSapGridOfPointsHolder
{
public :
  CATSapGridOfPointsHolder(CATMathGridOfPoints *);
  //Do not Delete the Grid Use Release()
  inline CATMathGridOfPoints * GetGrid() const {return(_Grid);};
  inline void SetGrid(CATMathGridOfPoints *iGrid);
  CATLONG32 AddRef();
  CATLONG32 Release();
private :
  ~CATSapGridOfPointsHolder();
  CATMathGridOfPoints * _Grid;
  CATULONG32 _CountRef;
};

CATSapGridOfPointsHolder * CATCreateSapHolder(CATMathGridOfPoints * iGrid);

#endif
