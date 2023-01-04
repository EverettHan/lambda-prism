#ifndef CATMathBasisFunctionX_H
#define CATMathBasisFunctionX_H

// Configuration de test à ne SURTOUT pas livrer active
//#define CATMathBasisFunctionX_TestNLD161118_ConstructorOperation "NLD161118 TEST ONLY"
  #ifdef CATMathBasisFunctionX_TestNLD161118_ConstructorOperation
   #define CATMathBasisFunctionX_ReduceConstructor0
   #define CATMathBasisFunctionX_ShuntConstructor1
  #endif

#include "YN000FUN.h"
#include "CATMathFunctionX.h"
#include "CATTolerance.h"
#include "CATMathAttrScaleOption.h"
//=============================================================================
//
// XScale compliant one variable mathematical function
//
// (intermediate class having a tolerance object)
// It is mainly used in order to avoid 
// going through finite difference evaluators of CATMathFunctionX
// it computes the right step by multiplying it by the scale tolerance object.
// this is done for extreme scale project.All functions to be solved or minimized in geometric context should 
// inherit from this class and use the appropriate the tolerance object
//
//=============================================================================
// 24/11/06 obh Creation; constructeur avec iTolObject
//              (Constructor0)
// 08/01/07 obh Le constructeur reçoit p (renommé iPowerScaleX le 10/02/16)
//              (Constructor0)
// 01/02/08 NLD Ajout constructeur avec ScaleOption, _ScaleOption, _UseScaleOption
//              (Constructor1)
//              Ajout InitStep() SetScaleOption() et GetScaleOption()
// 29/09/11 R1Y Added GetFirstStep(), GetSecondStep(), and GetThirdStep() (for comparing geometries).
// 29/01/16 KJD Ajout constructeur  avec degre d'homogeneite  de la function et de la variable
//              (Constructor2)
// 10/02/16 NLD Numerotation et recommandations d'utilisation des constructeurs
// 12/02/16 NLD Ajout argument iOkReviewed a CATMathBasisFunctionX_Constructor2
// 24/03/17 F1Z Put the CATMathAttrScaleOption in cost for the constructor & setScaleOption.
// 15/11/18 NLD Suppression constructeur0 par directive de compilation (step 1: encore inactif, voir detail du processus ci-dessous)
//
// DD/MM/YY
//=============================================================================

// See below <@NLDCommentsAtTheEndForDangerousConstructorsUse>
// #define CATMathBasisFunctionX_ShuntConstructor0 "ATTENTION PIEGE essai impact; appels à ce constructeur à remplacer (utiliser Constructor2) NLD151118"
// #define CATMathBasisFunctionX_ReduceConstructor0
// #define CATMathBasisFunctionX_ShuntConstructor1 "essai impact;                                                                              NLD151118"
// #define CATMathBasisFunctionX_ShuntConstructor2 "essai impact; diverses fonctions civil + reconnaissance + migrations depuis Constructor0   NLD151118"

class ExportedByYN000FUN CATMathBasisFunctionX : public CATMathFunctionX 
{

 public:

   #ifndef CATMathBasisFunctionX_ShuntConstructor1
   //                                                                                 CATMathBasisFunctionX_Constructor1 (NLD010208)
   //                                                                                 ----------------------------------
   CATMathBasisFunctionX(const CATTolerance           & iTolObject  ,
                         const CATMathAttrScaleOption & iScaleOption);
   #endif

   #ifndef CATMathBasisFunctionX_ShuntConstructor0
   //                                                                                 CATMathBasisFunctionX_Constructor0 (OBH2006) (the oldest one)
   //                                                                                 ----------------------------------
   // - CAUTION: signature not homogeneous to CATMathAttrScaleOption constructor signature:
   //   - missing argument iPowerScaleF should appear before iPowerScaleX
   //     and will be set to 1
   //     (equivalent to CATMathAttrScaleOption(1, iPowerScaleX))
   //     with this constructor a dummy ScaleOption is defined, that will not be used
   // - for XScale certification concerns,
   //   recommended constructor is CATMathBasisFunctionX_Constructor1 with ScaleOption definition
   //   or this one                CATMathBasisFunctionX_Constructor0 followed by SetScaleOption() from child class constructor
   //   or the last one            CATMathBasisFunctionX_Constructor2 with integrated review mechanism
   // - iPowerScaleX, anyway is used for steps definition
      #ifdef CATMathBasisFunctionX_ReduceConstructor0
   CATMathBasisFunctionX(const CATTolerance          & iTolObject  );
                          //   CATLONG32               iPowerScaleX);                 // (former notation p)
      #else
   CATMathBasisFunctionX(const CATTolerance          & iTolObject  ,
                               CATLONG32               iPowerScaleX);                 // (former notation p)
      #endif
   #endif

   #ifndef CATMathBasisFunctionX_ShuntConstructor2
   //                                                                                 CATMathBasisFunctionX_Constructor2 (KJD290116)
   //                                                                                 ----------------------------------
   // - CAUTION: signature homogeneous to CATMathAttrScaleOption constructor signature but not to CATMathBasisFunctionX_Constructor0
   CATMathBasisFunctionX(const CATTolerance          & iTolObject  ,
                               CATLONG32               iPowerScaleF,                  // (former notation q)
                               CATLONG32               iPowerScaleX,                  // (former notation p)
                               CATLONG32               iOkReviewed = 0
                        );
   #endif


 ///////////////////////////////////////////////////////
 // Evaluators 
 ///////////////////////////////////////////////////////  
 virtual       double         EvalFirstDeriv    (const double                 & iT          )  const;
 virtual       double         EvalSecondDeriv   (const double                 & iT          )  const;
 virtual       double         EvalThirdDeriv    (const double                 & iT          )  const;
 virtual       CATBoolean     IsAKindOf         (const CATMathClassId           iClassId    )  const;
 virtual       CATBoolean     IsATypeOf         (const CATMathFunctionXTypeId   iClassId    )  const;
 virtual       CATMathClassId IsA               ()                                             const;
         const CATTolerance & GetToleranceObject()                                             const;

               void           SetScaleOption    (const CATMathAttrScaleOption & iScaleOption);

 // returns 0 if ScaleOption not defined
 // returns 1 if ScaleOption defined, and sets oScaleOption argument
               int            GetScaleOption    (      CATMathAttrScaleOption & oScaleOption)  const;

               double         GetFirstStep      ()                                             const;
               double         GetSecondStep     ()                                             const;
               double         GetThirdStep      ()                                             const;

protected :
               void           InitStep          (      int                      iPowerScaleX) ;

  // Tolerance management dedicated data.
  const CATTolerance         & _TolObject;
  //                                scaled finite difference steps
        double                 _h1;
        double                 _h2;
        double                 _h3;
        CATMathAttrScaleOption _ScaleOption ;
        int                    _UseScaleOption ;
};

// <@NLDCommentsAtTheEndForDangerousConstructorsUse>
// Je detaille le putain de piege que, fort heureusement j'ai intuité
// alors que je n'avais aucune erreur de compilation, et que je n'aurais eu aucune erreur runtime en echelle 1
// et probablement peu d'erreurs supplementaires à l'echelle:
// - (PIEGE1) Si je supprime le dangereux Constructor0,
//   les appelants de ce constructeur vont se retrouver non pas sur Constructor2, dont les arguments n'ont pas de valeur par defaut,
//   mais sur Constructor1, appelé alors avec un CATMathAttrScaleOption créé à la volée,
//   et donc, compte tenu que ses arguments sont (iPowerScaleF = 1, iPowerScaleX = 1) avec,
//   si PowerX (je change de notations pour que ce soit clair) est l'argument passé à Constructor0,
//   un ScaleOption de (iPowerScaleF = PowerX, iPowerScaleX = 1)
//   au lieu de anciennement, avec le ScaleOption créé en interne,
//   un ScaleOption de (iPowerScaleF = 1, iPowerScaleX = 1)
// - il faut donc trouver autre une stratégie d'elimination
// - Je propose:
//   - shunter à la fois Constructor0 et Constructor1 (qui n'a pas d'appelant à ce jour)
//   - identifier ainsi les appelants de Constructor0 et les migrer sur Constructor2
//     on remplacera                     CATMathBasisFunctionX(TolObject, PowerScaleX)
//     par l'équivalent                  CATMathBasisFunctionX(TolObject, 1, PowerScaleX)
//     en pratique on trouve beaucoup de CATMathBasisFunctionX(TolObject, 1) qui ont été faits sans reflexion
//     mais qui souvent sont justes, du point de vue de X, en etant eventuellement faux du point de vue de F
// - (PIEGE2):
//   de plus Constructor0 est en fait un constructeur tactique avec fausse definition de ScaleOption,
//   (qui met _UseScaleOption à 0) au contraire des deux autres
//   donc la migration d'un appelant sur Constructor1 ou Constructor2 change le comportement,
//   - si cela s'accompagne, bien sur de la definition d'un PowerScaleF non egal à 1,
//   - mais aussi, à iso-PowerScaleX, si celui-ci ne vaut pas 1,
//     car dans ce cas le ScaleOption, non standard deviendra effectivement utilisable (du fait de _UseScaleOption passant à 1)
//    (en troisieme rideau: si l'on regarde mon CATMathFunctionXScaleManager dans CATMathFunctionX on voit
//     que le ScaleOption est pris 1) parmi les arguments 2) parmi les attributes 3) dans la fonction elle-meme)
// - en fait il faut vraiment enlever cet argument bidon iPowerScaleX qui induit en erreur, de Constructor0,
//   mais le faire, là encore, en debranchant transitoirement Constructor1, à cause de PIEGE1
//   et voir, et statuer, s'il y a des appels avec iPowerScaleX different de 1, à cause de PIEGE3 ci-dessous
// - (PIEGE3)
//   Constructor0 appelle InitStep avec iPowerScaleX, qui a donc un vrai usage si iPowerScaleX != 1
//  NLD151118

#endif

