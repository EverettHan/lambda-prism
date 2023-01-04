#ifndef CATSmoEvalResult_H
#define CATSmoEvalResult_H

//===============================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
//===============================================================================


#include "CATIAV5Level.h"

//Pour l'export
#include "CATSmoOperators.h"
#include "CATSobDiag.h"

#include "CATSmoEvalCommand.h"
#include "CATMathDirection2D.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"



class CATMathPoint;
class CATMathVector;

/**
 * Class representing an object that handles the results of a multiple
 * evaluation on a point of a CATSobMesh.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATSmoEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATSobMesh</tt> interface. 
 * The objects returned
 * belong to the <tt>CATSmoEvalResult</tt> and must not be deleted.
 * @see CATSmoEvalCommand, CATSobMesh 
 */

class ExportedByCATSmoOperators CATSmoEvalResult
{
public:

/**
 * Empty CATSmoEvalResult.
 */
  inline CATSmoEvalResult():_Diag(CATSobDiag_OK){};


//------------------------------------------------------------
// Getting the result of the evaluation
//------------------------------------------------------------
/**
 * Retrieves the evaluation of a point.
 * @param ioPoint
 * The mathematical definition of the evaluated point.
 */
  inline void GetPoint(CATMathPoint & ioPoint)const {ioPoint=_Point;} ;

/**
 * Retrieves the evaluation of the U first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivU
 * The vector of the U first partial derivative.
 */
  inline void GetFirstDerivU(CATMathVector & ioDerivU)const {ioDerivU=_Deriv[0];};

/**
 * Retrieves the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivV
 * The vector of the V first partial derivative.
 */
  inline void GetFirstDerivV(CATMathVector & ioDerivV)const {ioDerivV=_Deriv[1];};

/**
 * Retrieves the evaluation of the normal at a point
 * of a CATSobMesh.
 * @param ioNormal
 * The normalized normal.
 */
  inline void GetNormal(CATMathVector & ioNormal) const {ioNormal=_Deriv[2];};

/**
 * Retrieves the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2
 * The vector of the UU second partial derivative.
 */
  inline void GetSecondDerivU2(CATMathVector & ioDerivU2)const {ioDerivU2=_Deriv[3];};

/**
 * Retrieves the evaluation of the UV second partial derivative at a point
 * of a CATSobMesh. 
 * @param ioDerivUV
 * The vector of the UV second partial derivative.
 */
  inline void GetSecondDerivUV(CATMathVector & ioDerivUV) const {ioDerivUV=_Deriv[4];};

/**
 * Retrieves the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV2
 * The vector of the V2 second partial derivative.
 */
  inline void GetSecondDerivV2(CATMathVector & ioDerivV2) const {ioDerivV2=_Deriv[5];};

  void GetPrincipalCurvatures(CATMathDirection2D Dir2D[2], double Curv[4]) const;

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATSobMesh.
 * @param iPoint
 * The evaluated point.
 */
  inline void SetPoint ( const CATMathPoint &iPoint){_Point=iPoint;};

/**
 * Sets the evaluation of the U first partial derivative at a point 
 * of a CATSobMesh.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  inline void SetFirstDerivU( const CATMathVector &iDerivU){_Deriv[0]=iDerivU;};

/**
 * Sets the evaluation of the V first partial derivative at a point
 * of a CATSobMesh. 
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  inline void SetFirstDerivV( const CATMathVector &iDerivV){_Deriv[1]=iDerivV;};

/**
 * Sets the evaluation of the normal at a point
 * of a CATSobMesh. 
 * @param iNormal
 * The evaluated normal.
 */
  inline void SetNormal( const CATMathVector &iNormal){_Deriv[2]=iNormal;};

/**
 * Sets the evaluation of the UU second partial derivative at a point
 * of a CATSobMesh.
 * @param iDerivU2
 * The evaluated second derivative.
 */
  inline void SetSecondDerivU2( const CATMathVector &iDerivU2){_Deriv[3]=iDerivU2;};

/**
 * Sets the evaluation of the UV second partialderivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV
 * The evaluated second derivative.
 */
  inline void SetSecondDerivUV( const CATMathVector &iDerivUV){_Deriv[4]=iDerivUV;};

/**
 * Sets the evaluation of the VV second partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV2
 * The evaluated second derivative.
 */
  inline void SetSecondDerivV2( const CATMathVector & iDerivV2){_Deriv[5]=iDerivV2;};

  void SetPrincipalCurvatures(CATMathDirection2D Dir2D[2], double Curv[4]);
  


  //The 4 Third Derivatives

/**
 * Retrieves the evaluation of the UUU third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU3
 * The vector of the UUU third partial derivative.
 */
  void GetThirdDerivU3 (CATMathVector & ioDerivU3){ioDerivU3=_Deriv[6];};

/**
 * Retrieves the evaluation of the UUV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivU2V
 * The vector of the U2V third partial derivative.
 */
  void GetThirdDerivU2V(CATMathVector & ioDerivU2V){ioDerivU2V=_Deriv[7];};

/**
 * Retrieves the evaluation of the UVV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivUV2
 * The vector of the UV2 third partial derivative.
 */
  void GetThirdDerivUV2(CATMathVector & ioDerivUV2) {ioDerivUV2=_Deriv[8];};

/**
 * Retrieves the evaluation of the VVV third partial derivative at a point
 * of a CATSobMesh.
 * @param ioDerivV3
 * The vector of the VVV third partial derivative.
 */
  void GetThirdDerivV3 (CATMathVector & ioDerivV3){ioDerivV3=_Deriv[9];} ;
/**
 * Sets the evaluation of the UUU third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivU3
 * The evaluated third derivative.
 */
  void SetThirdDerivU3 ( const CATMathVector & iDerivU3) {_Deriv[6]=iDerivU3;};

/**
 * Sets the evaluation of the UUV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivU2V
 * The evaluated third derivative.
 */
  void SetThirdDerivU2V( const CATMathVector & iDerivU2V) {_Deriv[7]=iDerivU2V;};

/**
 * Sets the evaluation of the UVV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivUV2
 * The evaluated third derivative.
 */
  void SetThirdDerivUV2( const CATMathVector & iDerivUV2){_Deriv[8]=iDerivUV2;};

/**
 * Sets the evaluation of the VVV third partial derivative at a point
 * of a CATSobMesh. 
 * @param iDerivV3
 * The evaluated third derivative.
 */
  void SetThirdDerivV3 ( const CATMathVector & iDerivV3){_Deriv[9]=iDerivV3;};
  



  //Copy Ctor
  CATSmoEvalResult (const CATSmoEvalResult & Loc);
  inline CATSobDiag GetDiag();
//=============================================================================
// INTERNAL DATAS
//=============================================================================
private:
  inline void SetDiag( const CATSobDiag & iDiag){_Diag=iDiag;};

//
  CATMathPoint _Point;
  CATMathVector _Deriv[10];//6
  CATMathDirection2D _PrincipalCurvature[2];//Min,Max
  double              _Curvature[4];//MaxPrinK, MinPrinK,Gaussian,Mean
  CATSobDiag         _Diag;
  
};




#endif
