#ifndef CATMathSingleMemoryXY_H
#define CATMathSingleMemoryXY_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//---------------------------------------------------------------------------------------------------
// Merci pour cette belle documentation encore une fois
//
// Le but de cet objet semble etre de faire une FonctionXY avec memorisation du dernier Eval
// de maniere a optimiser les calculs lorsque 3 fonctions successives associees
// aux coordonnees X Y et Z utilisent une fonction denominateur commune necessitant
// donc d'etre evaluee 3 fois independamment au meme parametre (x,y).
// La fonction denominateur naturelle est alors enrobee par une CATMathSingleMemoryXY
//           NLD240908
//---------------------------------------------------------------------------------------------------
// ??/??/?? ??? Creation
// ??/??/?? ??? Introduction en R17 de arguments iTolObject
//              Introduction en R17 de EvalUpToThirdDeriv() et EvalAllThirdDerivs()
// 24/09/08 NLD Deflaggage R17
//              Renommage _dx, _dy en _x_dF, _y_dF
//              Gestion des derivees secondes: Ajout de _x_d2F, _y_d2F, _d2fx2, _d2fxy, _d2fy2 
// 29/07/09 NLD Gestion du stream
//              - derivation de _IsStreamable()
//              - derivation de GetStreamType()
//              - derivation de Stream()
//---------------------------------------------------------------------------------------------------
#include "CATIACGMLevel.h"
#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathInterval.h"
#include "CATMathFoundationXY.h"
#include "CATTolerance.h"

class CATMathSingleMemoryXYDel;

class ExportedByYN000FUN CATMathSingleMemoryXY : public CATMathFoundationXY
{

 private:

  const CATMathFunctionXY *_F;

  double _x, _y, _fxy,  _x_dF,  _y_dF, _dfx, _dfy;
  double _x_d2F, _y_d2F, _d2fx2, _d2fxy, _d2fy2 ;
  CATMathInterval _ix, _iy, _fixy, _dix, _diy, _dfix, _dfiy;
  friend class CATMathSingleMemoryXYDel;

  const CATTolerance & _TolObject;

  CATBoolean _InitDone;


  void Init(double x, double y);
 public:
  CATMathSingleMemoryXY(const CATMathFunctionXY *f,
                        const double x = 0.,const double y = 0.,  
                        const CATTolerance & iTolObject = CATGetDefaultTolerance(),
                        CATBoolean InitAtFirstEval = FALSE);
  CATCGMNewClassArrayDeclare;

  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
  CATMathClassId IsA() const;
	/** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathFunctionXY * Duplicate() const;
  CATMathFunctionXY * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  const CATMathFunctionXY * GetFunctionXY() const;
  const CATTolerance & GetToleranceObject() const;
  //-----------------------------------------------------------------
  // Stream management
  //-----------------------------------------------------------------
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  virtual void Stream( CATMathStream &Str, const char iLabelReserved[]) const ;

   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------   
   double Eval(const double & u, const double & v) const;
   double EvalFirstDerivX(const double & u, const double & v) const;
   double EvalFirstDerivY(const double & u, const double & v) const;
   double EvalSecondDerivX2(const double & u, const double & v) const;
   double EvalSecondDerivY2(const double & u, const double & v) const;
   double EvalSecondDerivXY(const double & u, const double & v) const;
   double EvalThirdDerivX3(const double & u, const double & v) const;
   double EvalThirdDerivX2Y(const double & u, const double & v) const;
   double EvalThirdDerivXY2(const double & u, const double & v) const;
   double EvalThirdDerivY3(const double & u, const double & v) const;

   /** 
   * Evaluates simultaneously the value, and all the first, second and third partial derivatives 
   */
  void EvalUpToThirdDeriv(const double iu, const double iv,double & oF, double & oFx,  double & oFy,
    double & oFx2, double & oFxy, double & oFy2,double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
  /** 
  * Evaluates the value of third partials derivatives 
  */
  void EvalAllThirdDerivs(const double iu, const double iv, double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;

   //
   // Evaluator of function and derivatives at the same time :
   //
   void Eval(const double u, const double v, const CATMathOption iOption,
             double * f, double * fx = 0, double * fy = 0, 
             double * fx2 = 0, double * fxy = 0, double * fy2 = 0) const;

   //
   // MultiEvaluator on a regular one dimensional grid on I.
   //
   void Eval(const CATMathIntervalND & iDomain, 
             const CATLONG32 *NbPoints, const CATMathOption iOption,
             double * f, double * fx = 0, double * fy = 0, 
             double * fx2 = 0, double * fxy = 0, double * fy2 = 0) const;

   /// 
   /// MultiEvaluator on a non regular grid
   ///
   void EvalGrid(CATLONG32 xNbPoints, const double * xPoints, 
                 CATLONG32 yNbPoints, const double * yPoints, 
                 const CATMathOption iOptions,
                 double * ioF, double * ioFx, double * ioFy) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------

  CATMathInterval Eval(const CATMathInterval & Du,
    const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  CATMathInterval EvalFirstDerivX(const CATMathInterval & x, const CATMathInterval & y) const;
  CATMathInterval EvalFirstDerivY(const CATMathInterval & x, const CATMathInterval & y) const;
  CATMathInterval EvalSecondDerivX2(const CATMathInterval & x, const CATMathInterval & y) const;
  CATMathInterval EvalSecondDerivXY(const CATMathInterval & x, const CATMathInterval & y) const;
  CATMathInterval EvalSecondDerivY2(const CATMathInterval & x, const CATMathInterval & y) const;

  void Eval(const CATMathInterval & x, const CATMathInterval & y, const CATMathOption iOptions,
            CATMathInterval * f, CATMathInterval * fx = 0, CATMathInterval * fy = 0, 
            CATMathInterval * fx2 = 0, CATMathInterval * fxy = 0, CATMathInterval * fy2 = 0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  
};
#endif
