//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// utilitaire de debug de CATMathFunctionX et CATMathFunctionXY:
//
// verification des derivees par differences finies
//=============================================================================
//
// Usage notes:
//
// Activer #define CATMathFunctionXDebug_CheckDerivative
// pour que le code soit declaré et utilisé
//=============================================================================
// 21/10/05 NLD Creation
// 26/03/09 NLD On distingue #define CATMathFunctionXDebug_CheckDerivative
//              et #define CATMathFunctionXDebug_Infra
//              qui est actif et rend l'infrastructure disponible
//              La fonction est desormais exportee, pour etre couverte par les tests
//              Ajout de CATMathFunctionXDebug_ControlDeriv() pour un appel facile
//              depuis une derivee exacte, sans souci de recursivite eventuelle
// 30/03/09 NLD Argument optionnel iDomain pour eviter des evaluations hors domaine
//=============================================================================

#ifndef CATMathFunctionXDebug_H
#define CATMathFunctionXDebug_H
#include  "YN000FUN.h" 

#include <CATMathFunctionX.h>
#include <CATMathFunctionXY.h>
class CATMathInterval ;

// #define CATMathFunctionXDebug_CheckDerivative "A Livrer inactif, a activer pour debug"
   #define CATMathFunctionXDebug_Infra           "disponibilite de cette infrastructure"

#ifdef CATMathFunctionXDebug_Infra
typedef enum {
              FX_Eval              = 0,
              FX_EvalFirstDeriv    ,
              FX_EvalSecondDeriv   ,
              FXY_Eval             ,
              FXY_EvalFirstDerivX  ,
              FXY_EvalFirstDerivY  ,
              FXY_EvalSecondDerivX2,
              FXY_EvalSecondDerivXY,
              FXY_EvalSecondDerivY2
             }
              CATMathFunctionXDebug_F_EvalType ; 
typedef enum {
              NumVar_X             = 1,
              NumVar_Y
             }
              CATMathFunctionXDebug_NumVarType ;

// fonction de calcul de derivee par differences finies avec controle
// ------------------------------------------------------------------
// 1) fonction realisant le calcul par differences finies
//    et eventuellement le calcul exact, selon le type de fonction
//
// iEvalType est le type d'evaluation dont on calcule la derivee
//  par exemple,
//  si on veut controler les differences finies donnant la derivee
//  premiere, on utilise FX_Eval
//  si on veut controler les differences finies donnant une derivee seconde,
//  on utilise FX_EvalFirstDeriv ou FXY_EvalFirstDerivX ou FXY_EvalFirstDerivY
// iNumVarDelta est le numero de la variable a laquelle on applique le
//  delta (x ou y)
//  on passe une CATMathFunctionX* ou une CATMathFunctionXY suivant le cas
//   NLD211005
/**
  * @nodoc   internal use. 
  * @nocgmitf   t'as vu si je pense a toi mon gars? 
  */

extern "C" ExportedByYN000FUN 
double CATMathFunctionXDebug_EvalAndControlDeriv(const CATMathFunctionX                *  FX          ,
                                                 const CATMathFunctionXY               *  FXY         ,
                                                       CATMathFunctionXDebug_F_EvalType   iEvalType   ,
                                                 const double                           & x           , 
                                                 const double                           & y           ,
                                                 const double                           & delta       , 
                                                       CATMathFunctionXDebug_NumVarType   iNumVarDelta,
                                                       CATMathInterval                 *  iDomain     = NULL) ;
/**
  * @nodoc   internal use. 
  * @nocgmitf   t'as vu si je pense a toi mon gars? 
  */
// 2) methode realisant le calcul par differences finies
//    et comparant au resultat exact recu en entree
//    (A utiliser dans le code d'evaluation exacte pour le controler)

extern "C" ExportedByYN000FUN 
void   CATMathFunctionXDebug_ControlDeriv       (      double                             iExactDeriv ,
                                                 const CATMathFunctionX                *  FX          ,
                                                 const CATMathFunctionXY               *  FXY         ,
                                                       CATMathFunctionXDebug_F_EvalType   iEvalType   ,
                                                 const double                           & x           ,
                                                 const double                           & y           ,
                                                 const double                           & delta       ,
                                                       CATMathFunctionXDebug_NumVarType   iNumVarDelta,
                                                       CATMathInterval                 *  iDomain     =NULL) ;


#endif

#endif
