// COPYRIGHT DASSAULT SYSTEMES 2006
//==========================================================================
//
// CATDebugDeriv:
// utility class for derivative debugging.
//
//==========================================================================
//
// Usage notes:
//
// Classe de debug du calcul d'une derivee,
// avec utilisation d'une valeur voisine obtenue par difference finie
// avec une valeur precedente memorisée
//
// la classe permet de controler facilement par differences finies
// la valeur d'une derivee et des derivées intermediaires de calculs
//
// Quelle que soit la complexité du calcul,
// il suffit d'utiliser cette classe pour tracer chaque variable intermediaire
// et sa derivee, pour controler la maniere dont on arrive a la derivée finale
//
// Exemple d'utilisation
//   static CATDebugDeriv DebugDeriv_N1(3, "N1") ;
//   static CATDebugDeriv DebugDeriv_N2(3, "N2") ;
//   static CATDebugDeriv DebugDeriv_V (3, "V ") ;
//   void Eval(double iLambda, CATMathVector& oV, odV) ;
//   {
//    CATMathVector N1, dN1 ;
//    CATMathVector N2, dN2 ;
//    CATMathVector V, dV ;
//   
//    EvalN1(iLambda, N1, dN1) ;
//    DebugDeriv_N1.SetDeriv(iLambda, N1, dN1) ;
//    EvalN2(iLambda, N2, dN2) ;
//    DebugDeriv_N2.SetDeriv(iLambda, N2, dN2) ;
//    V = N1^N2 ;
//    dV = dN1^dN2 ;
//    DebugDeriv_V.SetDeriv(iLambda, V, dV) ;
//    if (oV)
//       *oV = V ;
//    if (odV)
//       *odV = dV ; 
//   }
//==========================================================================
// 23/02/06 NLD Creation
// 24/02/06 NLD Ajout de point d'arret KO()
// 19/05/09 NLD Memorisation multiple:
//              Ajout FindMem(),_NumMem, _NumPrevMem, _MaxMem
// 25/05/09 NLD Ajout _Domain, _DomainLength et _UseDomain
//              Ajout argument optionnel iDomain au constructeur
// 16/07/09 NLD Deplacement dans AdvancedMathematics
// 04/08/09 NLD Ajout _TolZero, _TolDiv, _TolRatio
//              Passage de _MaxMem de 2 a 3 pour faciliter differences finies symetriques
//              SetDeriv() prend en argument optionnel la derivee par differences finies
//              afin de permettre a l'appelant de fournir une difference finie symetrique par exemple
//              Ajout SetDebugOutput(), _DebugOutput
//              Ajout SetDerivVector() pour factorisation
// 08/04/13 NLD Ajout _LastDerMem et _NumLastDerNoDiffMem
//              Ajout SetTolerance()/GetTolerance()
// 29/04/13 NLD Documentation des tolerances
// 05/10/15 NLD XScale
//              - Ajout SetScaleOption(), _Scale, _ScalePowerF, _ScalePowerX
//              - Mise a jour des XScaleRules associes a SetTolerance()
//==========================================================================

#ifndef CATDebugDeriv_H
#define CATDebugDeriv_H

class CATCGMOutput;
//#include <FrFAdvancedObjects.h>
#include <YN000FUN.h>

#include <CATMathPoint.h>
#include <CATMathVector.h>
#include <CATMathInterval.h>

//==========================================================================
// class ExportedByFrFAdvancedObjects CATDebugDeriv
class ExportedByYN000FUN CATDebugDeriv
  {
   public:

   static const int _MaxMem = 3 ;

   // Constructor
   CATDebugDeriv(int iDim, char* iName, CATMathInterval* iDomain = 0) ;

   // Destructor
   ~CATDebugDeriv() ;

   // XScale: Definition du comportement par rapport a l'echelle
   // N.B entraine la remise a l'echelle 1 des traces
   void SetScaleOption(double iScale, int iPowerScaleF, int iPowerScaleX);

   // Methode pour pose de point d'arret si comparaison KO entre derivée et différence finie
   void KO      (double iRatio) ;
   // passage d'un parametre, de la valeur, et eventuellement de la valeur de la derivee
   // si la derivee est passee, on controle et on trace par rapport a la valeur precedente recue
   void SetDeriv(double iParam,       double*        iVal, double*        iExactDeriv, double*        iApproxDeriv = 0) ;

   // Idem avec une valeur de type point (et derivée de type vecteur)
   void SetDeriv(double iParam, const CATMathPoint&  iVal, CATMathVector* iExactDeriv, CATMathVector* iApproxDeriv = 0) ;

   // Idem avec une valeur de type vecteur
   void SetDeriv(double iParam, const CATMathVector& iVal, CATMathVector* iExactDeriv, CATMathVector* iApproxDeriv = 0) ;

   // Defines output file (default: cgmout); 
   void SetDebugOutput(CATCGMOutput* iDebugOutput) ;

   // Tolerances definition and access
   // --------------------------------
   // CAUTION: if SetScaleOption() has been called, tests and traces are done with values reworked to scale 1,
   //          and, scale dependant tolerances must be defined in scale 1, thus be independant from scale. NLD051015
   // 1) _TolZero   : ToleranceZero
   //       - tolerance under which no comparison is done (non significative values)
   //         it applies to derivative values (exact or finite difference)
   //       - Scale dependant:  must be defined by calling software for non standard scales,
   //         according to function behaviour
   //        (Scale independant for a standard function with parameter and function varying like power 1 of scale)
   //       - default value 1.E-12
   // 2) _TolDiv   : ToleranceDivide
   //       - tolerance under which parametric delta is assumed to be null, and no finite difference can be computed
   //         it applies only on parametric delta
   //       - Scale dependant: must be defined by calling software for non standard scales,
   //         according to parameter behaviour
   //       - default value 1.E-14
   // 3) _TolRatio  : ToleranceRatio
   //       - tolerance for ratio between exact derivative and finite difference derivative
   //         (ratio must be between 1 - _TolRatio and 1 + _TolRatio)
   //       - Scale independant
   //       - default value 1.E-2
   typedef enum {
                 CATDebugDerivToleranceZero   = 1,
                 CATDebugDerivToleranceDivide = 2,
                 CATDebugDerivToleranceRatio  = 3
                }CATDebugDerivToleranceType;

   void   SetTolerance(CATDebugDerivToleranceType iToleranceType,
                       double                     iTolerance);

   double GetTolerance(CATDebugDerivToleranceType iToleranceType);

   private:

   int             _Dim ;
   double        * _ValMem ;
   double          _ParamMem[_MaxMem] ;
   double        * _LastDerMem;          // derniere derivee memorisee
   int             _NumLastDerNoDiffMem; // indique le numero en memoire de la derniere derivee si sans difference finie
   int             _NumMem  ;
   int             _NumPrevMem ;
   int             _NbMem ;
   char          * _Name ;
   int             _LgName ;
   int             _UseDomain ;
   double          _DomainLength;
   CATMathInterval _Domain;

   double          _TolZero ;//  Tolerance en dessous de laquelle on ne teste pas
   double          _TolDiv ; //  Tolerance en dessous de laquelle on ne divise pas
   double          _TolRatio;//  Tolerance d'egalite du ratio (entre 1-_TolRatio et 1+_TolRatio)

   double          _Scale;
   int             _ScalePowerF;
   int             _ScalePowerX;

   // Debug and traces system
   CATCGMOutput  * _DebugOutput ;

   // Recherche de position ou stocker
   void FindMem       (double iParam);

   // Definition de derivee a 3 coordonnees par vecteur
   void SetDerivVector(double iParam, double* iVal, CATMathVector* iExactDeriv, CATMathVector* iApproxDeriv);

  } ;
#endif
