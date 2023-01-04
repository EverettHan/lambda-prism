#ifndef CATSapEvalResult_H
#define CATSapEvalResult_H

//===============================================================================
// Copyright Dassault Systemes Provence 2008-2009, All Rights Reserved 
//===============================================================================
//HISTORIQUE : Rapporchement 
// 23/02/2009 : RNO : Rapprochement de SurEvalLocal pour conversion Rapide !
// 20/02/2009 : RNO : Suppression du support Curvature (trop lourd a l'init)
// September 2008 : RNO : Creation
#include "CATIAV5Level.h"

//Pour l'export
#include "CATSapApprox.h"
#include "CATSobDiag.h"

#include "memory.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "memory.h"

#define CATSapEvalResultAsSurEvalLocal "Fast Translation"



/**
 * Class representing an object that handles the results of a multiple
 * evaluation on a point of a CATSobMesh.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATSapEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATSobMesh</tt> interface. 
 * The objects returned
 * belong to the <tt>CATSapEvalResult</tt> and must not be deleted.
 * @see CATSapEvalCommand, CATSobMesh 
 */
#include "CATMathInline.h"



//Nombre de derivees en comptant le point et la normale
// Array of results, sorted using the values of CATSurEvalCommand::Evaluations
const int __SAPNBDERIV__ = 11;

typedef enum
{
  SapEvalResPoint          = 0,
  SapEvalResFirstDerivU    = 1,
  SapEvalResFirstDerivV    = 2,
  SapEvalResNormal         = 3,
  SapEvalResSecondDerivU2  = 4,
  SapEvalResSecondDerivUV  = 5,
  SapEvalResSecondDerivV2  = 6,
  SapEvalResThirdDerivU3   = 7,
  SapEvalResThirdDerivU2V  = 8,
  SapEvalResThirdDerivUV2  = 9,
  SapEvalResThirdDerivV3   = 10
} SapEvalResEvaluations;

typedef enum
{
  SapEvalResUpToPoint=0,
  SapEvalResUpToFirstDeriv=1,
  SapEvalResUpToNormal=3,
  SapEvalResUpToSecondDeriv=6,
  SapEvalResUpToThirdDeriv=10,
} SapEvalUpToResEvaluations;

class ExportedByCATSapApprox CATSapEvalResult
{
public:

/**
 * Empty CATSapEvalResult.
 */
  INLINE CATSapEvalResult();


//------------------------------------------------------------
// Getting the result of the evaluation
//------------------------------------------------------------
/**
 * Retrieves the evaluation of a point.
 * @param ioPoint
 * The mathematical definition of the evaluated point.
 */
  INLINE void GetPoint(CATMathPoint & ioPoint)const ;

/**
 * Retrieves the evaluation of the U first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivU
 * The vector of the U first partial derivative.
 */
  INLINE void GetFirstDerivU(CATMathVector & ioDerivU)const;

/**
 * Retrieves the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivV
 * The vector of the V first partial derivative.
 */
  INLINE void GetFirstDerivV(CATMathVector & ioDerivV)const;

/**
 * Retrieves the evaluation of the normal at a point
 * of a CATSobMesh.
 * @param ioNormal
 * The normalized normal.
 */
  INLINE void GetNormal(CATMathVector & ioNormal) const ;

/**
 * Retrieves the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2
 * The vector of the UU second partial derivative.
 */
  INLINE void GetSecondDerivU2(CATMathVector & ioDerivU2)const;

/**
 * Retrieves the evaluation of the UV second partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivUV
 * The vector of the UV second partial derivative.
 */
  INLINE void GetSecondDerivUV(CATMathVector & ioDerivUV) const ;

/**
 * Retrieves the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV2
 * The vector of the V2 second partial derivative.
 */
  INLINE void GetSecondDerivV2(CATMathVector & ioDerivV2) const;

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATSobMesh.
 * @param iPoint
 * The evaluated point.
 */
  //INLINE void SetPoint ( const CATMathPoint &iPoint);

/**
 * Sets the evaluation of the U first partial derivative at a point 
 * of a CATSobMesh.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void SetFirstDerivU( const CATMathVector &iDerivU);

/**
 * Sets the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void SetFirstDerivV( const CATMathVector &iDerivV);

/**
 * Sets the evaluation of the normal at a point
 * of a CATSobMesh. 
 * @param iNormal
 * The evaluated normal.
 */
  INLINE void SetNormal( const CATMathVector &iNormal);

/**
 * Sets the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param iDerivU2
 * The evaluated second derivative.
 */
  //INLINE void SetSecondDerivU2( const CATMathVector &iDerivU2);

/**
 * Sets the evaluation of the UV second partialderivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV
 * The evaluated second derivative.
 */
  //INLINE void SetSecondDerivUV( const CATMathVector &iDerivUV);

/**
 * Sets the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV2
 * The evaluated second derivative.
 */
  //INLINE void SetSecondDerivV2( const CATMathVector & iDerivV2);



  //The 4 Third Derivatives

/**
 * Retrieves the evaluation of the UUU third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU3
 * The vector of the UUU third partial derivative.
 */
  void GetThirdDerivU3 (CATMathVector & ioDerivU3)const;

/**
 * Retrieves the evaluation of the UUV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2V
 * The vector of the U2V third partial derivative.
 */
  void GetThirdDerivU2V(CATMathVector & ioDerivU2V)const;

/**
 * Retrieves the evaluation of the UVV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivUV2
 * The vector of the UV2 third partial derivative.
 */
  void GetThirdDerivUV2(CATMathVector & ioDerivUV2) const;

/**
 * Retrieves the evaluation of the VVV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV3
 * The vector of the VVV third partial derivative.
 */
  void GetThirdDerivV3 (CATMathVector & ioDerivV3)const ;
/**
 * Sets the evaluation of the UUU third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivU3
 * The evaluated third derivative.
 */
  void SetThirdDerivU3 ( const CATMathVector & iDerivU3);

/**
 * Sets the evaluation of the UUV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivU2V
 * The evaluated third derivative.
 */
  void SetThirdDerivU2V( const CATMathVector & iDerivU2V) ;

/**
 * Sets the evaluation of the UVV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV2
 * The evaluated third derivative.
 */
  void SetThirdDerivUV2( const CATMathVector & iDerivUV2);

/**
 * Sets the evaluation of the VVV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV3
 * The evaluated third derivative.
 */
  void SetThirdDerivV3 ( const CATMathVector & iDerivV3);
  



  //Copy Ctor
  CATSapEvalResult (const CATSapEvalResult & Loc);
  INLINE CATSobDiag GetDiag();


  #ifdef CATSapEvalResultAsSurEvalLocal


  INLINE const double * GetValue(SapEvalResEvaluations Eval) const;
/**
 * 
 * @return
 * The array[] of doubles corresponding to the required evaluation, and that belongs to the
 * CATSurEvalLocal: it must not be deleted. The 
 * <tt>iEval</tt> CATSurEvalCommand::Evaluation
 * evaluation type is located at the <tt>3*iEval</tt> place. If an evaluation
 * is not asked for, the 3 doubles space is allocated, but not filled in. 
 */
  INLINE const double * GetValues() const;

  /**

 * Sets a given type evaluation at a point of a CATSurface.
 *<br>Note that this method does not performed any verifications.
 */
  INLINE void SetValue(SapEvalResEvaluations iEvaluation,
			   const double * iValue);
#endif
//=============================================================================
// INTERNAL DATAS
//=============================================================================
private:
  INLINE void SetDiag( const CATSobDiag & iDiag){_Diag=iDiag;};

  //
#ifdef CATSapEvalResultAsSurEvalLocal

  //Nombre de derivees en comptant le point et la normale
  // Array of results, sorted using the values of CATSurEvalCommand::Evaluations
  double             _Results[3*__SAPNBDERIV__];

#else
#define __NBDERIV__ 10
  CATMathPoint _Point;
  CATMathVector _Deriv[__NBDERIV__];//10
#endif
  CATSobDiag         _Diag;
  
};




#ifdef CATSapEvalResultAsSurEvalLocal
INLINE CATSapEvalResult::CATSapEvalResult()
:_Diag(CATSobDiag_OK)
{
 memset(_Results, 0, 3*__SAPNBDERIV__*sizeof(double));
}

INLINE const double * CATSapEvalResult::GetValues() const
{
  return _Results;
}

INLINE void CATSapEvalResult::SetValue(SapEvalResEvaluations Eval,
					  const double * Value)
{
  register double *WhereToCopy=_Results + 3* (int) Eval;
  WhereToCopy[0]=Value[0];
  WhereToCopy[1]=Value[1];
  WhereToCopy[2]=Value[2];
} 

INLINE const double * CATSapEvalResult::GetValue(SapEvalResEvaluations Eval) const
{
  return (_Results + 3* (int) Eval);
}

//------------------------------------------------------------
// Getting the result of the evaluation
//------------------------------------------------------------
/**
 * Retrieves the evaluation of a point.
 * @param ioPoint
 * The mathematical definition of the evaluated point.
 */
 INLINE void CATSapEvalResult::GetPoint(CATMathPoint & ioPoint)const {ioPoint.SetCoord(_Results+3*SapEvalResPoint);}

/**
 * Retrieves the evaluation of the U first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivU
 * The vector of the U first partial derivative.
 */
  INLINE void CATSapEvalResult::GetFirstDerivU(CATMathVector & ioDerivU)const {ioDerivU.SetCoord(_Results+3*SapEvalResFirstDerivU);}

/**
 * Retrieves the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivV
 * The vector of the V first partial derivative.
 */
  INLINE void CATSapEvalResult::GetFirstDerivV(CATMathVector & ioDerivV)const  {ioDerivV.SetCoord(_Results+3*SapEvalResFirstDerivV);}

/**
 * Retrieves the evaluation of the normal at a point
 * of a CATSobMesh.
 * @param ioNormal
 * The normalized normal.
 */
  INLINE void CATSapEvalResult::GetNormal(CATMathVector & ioNormal) const  {ioNormal.SetCoord(_Results+3*SapEvalResNormal);}

/**
 * Retrieves the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2
 * The vector of the UU second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivU2(CATMathVector & ioDerivU2)const  {ioDerivU2.SetCoord(_Results+3*SapEvalResSecondDerivU2);}

/**
 * Retrieves the evaluation of the UV second partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivUV
 * The vector of the UV second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivUV(CATMathVector & ioDerivUV) const  {ioDerivUV.SetCoord(_Results+3*SapEvalResSecondDerivUV);}

/**
 * Retrieves the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV2
 * The vector of the V2 second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivV2(CATMathVector & ioDerivV2) const {ioDerivV2.SetCoord(_Results+3*SapEvalResSecondDerivV2);}

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATSobMesh.
 * @param iPoint
 * The evaluated point.
 */
  //INLINE void CATSapEvalResult::SetPoint ( const CATMathPoint &iPoint)  { iPoint.GetCoord(_Results+3*SapEvalResPoint);  }
/**
 * Sets the evaluation of the U first partial derivative at a point 
 * of a CATSobMesh.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void CATSapEvalResult::SetFirstDerivU( const CATMathVector &iDerivU) {iDerivU.GetCoord(_Results+3*SapEvalResFirstDerivU);}

/**
 * Sets the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void CATSapEvalResult::SetFirstDerivV( const CATMathVector &iDerivV){iDerivV.GetCoord(_Results+3*SapEvalResFirstDerivV);}

/**
 * Sets the evaluation of the normal at a point
 * of a CATSobMesh. 
 * @param iNormal
 * The evaluated normal.
 */
  INLINE void CATSapEvalResult::SetNormal( const CATMathVector &iNormal){iNormal.GetCoord(_Results+3*SapEvalResNormal);}

/**
 * Sets the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param iDerivU2
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivU2( const CATMathVector &iDerivU2){iDerivU2.GetCoord(_Results+3*SapEvalResSecondDerivU2);}

/**
 * Sets the evaluation of the UV second partialderivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivUV( const CATMathVector &iDerivUV){iDerivUV.GetCoord(_Results+3*SapEvalResSecondDerivUV);}

/**
 * Sets the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV2
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivV2( const CATMathVector & iDerivV2){iDerivV2.GetCoord(_Results+3*SapEvalResSecondDerivV2);}



#else



//------------------------------------------------------------
// Getting the result of the evaluation
//------------------------------------------------------------
/**
 * Retrieves the evaluation of a point.
 * @param ioPoint
 * The mathematical definition of the evaluated point.
 */
 INLINE void CATSapEvalResult::GetPoint(CATMathPoint & ioPoint)const {ioPoint=_Point;} ;

/**
 * Retrieves the evaluation of the U first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivU
 * The vector of the U first partial derivative.
 */
  INLINE void CATSapEvalResult::GetFirstDerivU(CATMathVector & ioDerivU)const {ioDerivU=_Deriv[0];};

/**
 * Retrieves the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivV
 * The vector of the V first partial derivative.
 */
  INLINE void CATSapEvalResult::GetFirstDerivV(CATMathVector & ioDerivV)const {ioDerivV=_Deriv[1];};

/**
 * Retrieves the evaluation of the normal at a point
 * of a CATSobMesh.
 * @param ioNormal
 * The normalized normal.
 */
  INLINE void CATSapEvalResult::GetNormal(CATMathVector & ioNormal) const {ioNormal=_Deriv[2];};

/**
 * Retrieves the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2
 * The vector of the UU second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivU2(CATMathVector & ioDerivU2)const {ioDerivU2=_Deriv[3];};

/**
 * Retrieves the evaluation of the UV second partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivUV
 * The vector of the UV second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivUV(CATMathVector & ioDerivUV) const {ioDerivUV=_Deriv[4];};

/**
 * Retrieves the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV2
 * The vector of the V2 second partial derivative.
 */
  INLINE void CATSapEvalResult::GetSecondDerivV2(CATMathVector & ioDerivV2) const {ioDerivV2=_Deriv[5];};

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATSobMesh.
 * @param iPoint
 * The evaluated point.
 */
  //INLINE void CATSapEvalResult::SetPoint ( const CATMathPoint &iPoint) {_Point=iPoint;};

/**
 * Sets the evaluation of the U first partial derivative at a point 
 * of a CATSobMesh.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void CATSapEvalResult::SetFirstDerivU( const CATMathVector &iDerivU){_Deriv[0]=iDerivU;};

/**
 * Sets the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  //INLINE void CATSapEvalResult::SetFirstDerivV( const CATMathVector &iDerivV){_Deriv[1]=iDerivV;};

/**
 * Sets the evaluation of the normal at a point
 * of a CATSobMesh. 
 * @param iNormal
 * The evaluated normal.
 */
  INLINE void CATSapEvalResult::SetNormal( const CATMathVector &iNormal){_Deriv[2]=iNormal;};

/**
 * Sets the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param iDerivU2
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivU2( const CATMathVector &iDerivU2){_Deriv[3]=iDerivU2;};

/**
 * Sets the evaluation of the UV second partialderivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivUV( const CATMathVector &iDerivUV){_Deriv[4]=iDerivUV;};

/**
 * Sets the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV2
 * The evaluated second derivative.
 */
  //INLINE void CATSapEvalResult::SetSecondDerivV2( const CATMathVector & iDerivV2){_Deriv[5]=iDerivV2;};



 
#endif


#endif
