#ifndef CATMathSingleMemoryX_H
#define CATMathSingleMemoryX_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//
// DESCRIPTION : Surcouche de fonction X avec memorisation de la derniere evaluation pour optimisation
//
// Merci pour cette belle documentation encore une fois
//
// Le but de cet objet semble etre de faire une FonctionX avec memorisation du dernier Eval
// de maniere a optimiser les calculs lorsque 3 fonctions successives associees
// aux coordonnees X Y et Z utilisent une fonction denominateur commune necessitant
// donc d'etre evaluee 3 fois independamment au meme parametre x.
// La fonction denominateur naturelle est alors enrobee par une CATMathSingleMemoryX
//           NLD251108

// 25/11/08 NLD Ajout d'un header
//              Renommage de _x,_dx en _x_f,_x_df
// 03/10/11 R1Y Added the function GetX() (for comparing geometries).
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathInterval.h"
#include "CATMathFoundationX.h"

class CATMathStream;
class CATMathSingleMemoryXDel;

class ExportedByYN000FUN CATMathSingleMemoryX : public CATMathFoundationX
{
 private:
  const CATMathFunctionX *_F;
  double _x_f, _fx,      // parametre et valeur de fonction memorises
         _x_df, _dfx;    // parametre et valeur de derivee memorises
  CATMathInterval _i, _fi, _di, _dfi;
  friend class CATMathSingleMemoryXDel;


 public:
  CATMathSingleMemoryX(const CATMathFunctionX *f,
             const double x = 0.);

  virtual ~CATMathSingleMemoryX();
  CATCGMNewClassArrayDeclare;

  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;
  CATMathClassId IsA() const;
   /** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  virtual size_t  GetStaticMemoryBytes() const;   
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;


  const CATMathFunctionX * GetFunctionX() const;
  double GetX() const;

   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------   
   double Eval(const double & t) const;
   double EvalFirstDeriv(const double & t) const;
   double EvalSecondDeriv(const double & t) const;
   double EvalThirdDeriv(const double & t) const;

   //
   // Evaluator of function and derivatives at the same time :
   //
   void Eval(const double t, const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

   //
   // MultiEvaluator on a regular one dimensional grid on I.
   //
   void Eval(const CATMathInterval & I, const CATLONG32 NbPoints,
             const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalThirdDeriv(const CATMathInterval & x) const;
  void Eval(const CATMathInterval & I, const CATMathOption iOptions,
       CATMathInterval * f, CATMathInterval * df = 0, 
       CATMathInterval * d2f = 0) const;

  //---------------------------------------------------------------------
  // Formal combination creation : 
  //---------------------------------------------------------------------
  virtual CATMathFunctionX * FormalCombination(const CATLONG32 iN, 
                           const CATMathFunctionX ** iFunc,
                      const double * iCoef, 
                      const double iConstant) const;

  virtual CATMathFunctionX* CreateDeriv() const;

  
};
#endif
