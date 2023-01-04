#ifndef CATMathFunctionDebugTool_H
#define CATMathFunctionDebugTool_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2008
//=============================================================================
//
// Outil de debug (traces) des fonctions, avec macros d'espionnage des sous-fonctions
// dont elles dependent
//
// ---------------------------------------------------------------------------------
// Afin de ne pas avoir de cout CPU induit,
// les macros sont vides en implementation par defaut.
// Les macros ne travaillent que si l'on modifie ce .h et que l'on active le #define qui suit
// ---------------------------------------------------------------------------------
// *** Pour instrumenter le code, activer #define CATMathFunctionDebugToolSpyEval_Active ***
// -----------------------------------------------------------------------------------------
// Attention je rends ce #define public (utilisation dans CATMathPiecewiseXY, ...)
// #define CATMathFunctionDebugToolSpyEval_Active "*****ne pas livrer active*****"
// -----------------------------------------------------------------------------------------
//=============================================================================
// 19/12/08 NLD Creation
//              classe CATMathFunctionDebugTool
//              macros CATMathFunctionDebugToolSpyEval
//                     CATMathFunctionDebugToolSpyEvalFirstDeriv
//                     CATMathFunctionDebugToolSpyEvalSecondDeriv
// 22/12/08 NLD Ajout  CATMathFunctionDebugToolSpyEvalThirdDeriv
// 23/12/08 NLD Ajout  CATMathFunctionDebugToolSpyEvalGen
// 07/01/09 NLD Ajout de DumpAndSampleRecords() pour factorisation du code
//              Ajout de ReallocRecords()
//              - ajout Record() avec CATMathFunctionXY
//              - ajout SampleDump() avec CATMathFunctionXY
//              Ajout macro CATMathFunctionDebugToolSpyEvalXY()
//              Ajout macro CATMathFunctionDebugToolSpyEvalXYGen()
//              (faisant partiellement le travail: pas de gestion des derivees)
// 08/01/09 NLD Record() avec fonction XY prend desormais un CATMathFunctionDebugTool_OptionEvalXY
//              Finalisation de CATMathFunctionDebugToolSpyEvalXYGen()
// 21/07/09 NLD Ajout SampleDumpAndDerivControl()
//              Ajout SampleDumpWork()
// 30/07/09 NLD Parametrisation des traces pour usage dans fenetre de CGMReplay
//              Ajout SetDebugOutput(), _DebugOutput
// 21/10/09 NLD Ajout RemoveRecords()
// 08/01/10 NLD Ajout CATMathFunctionDebugTool_SpyMode
//              ActiveSpy() recoit un mode iSpyMode de maniere a permettre le re-sampling final
//              sans Dump, ou vice-versa
// 14/04/10 KJD Ajout SystemXYGraphicEditor() pour representation d'un systeme XY
// 29/04/10 NLD Pour un systeme XY, on fournit aussi un SampleDump() avec representation standard
// 24/06/10 NLD Ajout _DumpPointer et InactivePointerDump()
// 24/09/10 KJD Ajout argument optionnel ListOfRefPoint a SystemXYGraphicEditor()
// 23/02/18 KJD Ajout argument optionnel iWithTitleAndLabels a SampleDump et SampleDumpWork avec CATMathfunctionX
// 01/06/18 KJD Ajout nouvelle API SampleDump pour représenter 2 CATMathFunctionX sur meme graphique
//              Evolution SampleDumpWork pour gérer 2 fonctions
//              Nouvelles APIs (ComputePos, Eval) pour factoriser code dans SampleDumpWork
//=============================================================================

#include <CATAdvancedMathematics.h>
#include <CATMathDef.h> // pour CATMathOption
#include <CATMathSystemXY.h>
#include"CATLISTV_CATMathPoint2D.h"

// pour le moment je fais une classe
class CATMathFunctionDebugTool ;
class CATMathFunctionX ;
class CATMathFunctionXY ;
class CATMathSystemXY ;
class CATCGMOutput;


// Empilage/Depilage d'un spyer
extern "C" ExportedByCATAdvancedMathematics void StackDebugToolSpyer() ;
extern "C" ExportedByCATAdvancedMathematics void UnstackDebugToolSpyer() ;
// Acces au spyer en cours
extern "C" ExportedByCATAdvancedMathematics CATMathFunctionDebugTool* CATGetCurrentDebugToolSpyer() ;

// Description des ordres d'evaluation de fonctions XY
typedef enum
  {
    CATMathFunctionDebugTool_EvalNone,
    CATMathFunctionDebugTool_Eval,
    CATMathFunctionDebugTool_EvalFirstDerivX,
    CATMathFunctionDebugTool_EvalFirstDerivY,
    CATMathFunctionDebugTool_EvalSecondDerivX2,
    CATMathFunctionDebugTool_EvalSecondDerivXY,
    CATMathFunctionDebugTool_EvalSecondDerivY2
  } CATMathFunctionDebugTool_OptionEvalXY ;
// --------------------------------------------
// Macros d'espionnage si un spyer est en cours
// --------------------------------------------
#ifdef CATMathFunctionDebugToolSpyEval_Active
// -----------------------------------------
// Enregistrement d'un resultat d'evaluation
// -----------------------------------------
//  (CATMathFunctionX*) F: pointeur de fonction
//  double param: parametre d'evaluation
//  double value: valeur rendue par la fonction
#define CATMathFunctionDebugToolSpyEval(F, param, value)                                                                                  \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer)                                                                                                                               \
  Spyer->Record(F, param, value, OptionEval);                                                                                             \
}
// ----------------------------------------------------
// Enregistrement d'un resultat d'evaluation de derivee
// ----------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalFirstDeriv(F, param, value)                                                                        \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer)                                                                                                                               \
  Spyer->Record(F, param, value, OptionEvalFirstDeriv);                                                                                   \
}
//------------ ----------------------------------------------------
// Enregistrement d'un resultat d'evaluation de fonction et derivee
//------------ ----------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalAndFirstDeriv(F, param, f, df)                                                                     \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer)                                                                                                                               \
  {Spyer->Record(F, param, f, OptionEval);                                                                                                \
  Spyer->Record(F, param, df, OptionEvalFirstDeriv);}                                                                                     \
}
// ------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation de derivee seconde
// ------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalSecondDeriv(F, param, value)                                                                       \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer)                                                                                                                               \
  Spyer->Record(F, param, value, OptionEvalSecondDeriv);                                                                                  \
}
// --------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation de derivee troisieme
// --------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalThirdDeriv(F, param, value)                                                                        \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer)                                                                                                                               \
  Spyer->Record(F, param, value, OptionEvalThirdDeriv);                                                                                   \
}
// --------------------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation generale de fonction et derivees
// (ici on recoit les pointeurs vers les resultats)
// --------------------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalGen(F, option, param, pf, pdf, pd2f)                                                               \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
   if ((option & OptionEval)            && pf)   Spyer->Record(F, param, *pf,   OptionEval);                                              \
   if ((option & OptionEvalFirstDeriv)  && pdf)  Spyer->Record(F, param, *pdf,  OptionEvalFirstDeriv);                                    \
   if ((option & OptionEvalSecondDeriv) && pd2f) Spyer->Record(F, param, *pd2f, OptionEvalSecondDeriv);                                   \
  }}

// --------------------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation de fonction XY 
// --------------------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalXY(FXY, paramx, paramy, f)                                                                         \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, f, CATMathFunctionDebugTool_Eval);                                                                 \
  }}

// --------------------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation de derivee 1ere de fonction XY 
// --------------------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalFirstDerivX(FXY, paramx, paramy, dfx)                                                              \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, dfx, CATMathFunctionDebugTool_EvalFirstDerivX);                                                    \
  }}
#define CATMathFunctionDebugToolSpyEvalFirstDerivY(FXY, paramx, paramy, dfy)                                                              \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, dfy, CATMathFunctionDebugTool_EvalFirstDerivY);                                                    \
  }}
// --------------------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation de derivee 2nde de fonction XY 
// --------------------------------------------------------------------------
#define CATMathFunctionDebugToolSpyEvalSecondDerivX2(FXY, paramx, paramy, d2fx2)                                                          \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, d2fx2, CATMathFunctionDebugTool_EvalSecondDerivX2);                                                \
  }}
#define CATMathFunctionDebugToolSpyEvalSecondDerivXY(FXY, paramx, paramy, d2fxy)                                                          \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, d2fxy, CATMathFunctionDebugTool_EvalSecondDerivXY);                                                \
  }}
#define CATMathFunctionDebugToolSpyEvalSecondDerivY2(FXY, paramx, paramy, d2fy2)                                                          \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
    Spyer->Record(FXY, paramx, paramy, d2fy2, CATMathFunctionDebugTool_EvalSecondDerivY2);                                                \
  }}

// --------------------------------------------------------------------------
// Enregistrement d'un resultat d'evaluation generale de fonction XY et derivees
// (ici on recoit les pointeurs vers les resultats)
// --------------------------------------------------------------------------
//**** pour les derivees il faudrait definir des codes indiquant les variables 
//**** par lesquelles on derive (x, y, x2, xy, y2)
#define CATMathFunctionDebugToolSpyEvalXYGen(FXY, option, paramx, paramy, pf, pdfx, pdfy, pd2fx2, pd2fxy, pd2fy2)                         \
{CATMathFunctionDebugTool* Spyer = CATGetCurrentDebugToolSpyer();                                                                         \
 if (Spyer){                                                                                                                              \
  if ((option & OptionEval)            && pf)     Spyer->Record(FXY, paramx, paramy, *pf,     CATMathFunctionDebugTool_Eval);             \
  if ((option & OptionEvalFirstDeriv)  && pdfx)   Spyer->Record(FXY, paramx, paramy, *pdfx,   CATMathFunctionDebugTool_EvalFirstDerivX);  \
  if ((option & OptionEvalFirstDeriv)  && pdfy)   Spyer->Record(FXY, paramx, paramy, *pdfy,   CATMathFunctionDebugTool_EvalFirstDerivY);  \
  if ((option & OptionEvalSecondDeriv) && pd2fx2) Spyer->Record(FXY, paramx, paramy, *pd2fx2, CATMathFunctionDebugTool_EvalSecondDerivX2);\
  if ((option & OptionEvalSecondDeriv) && pd2fxy) Spyer->Record(FXY, paramx, paramy, *pd2fxy, CATMathFunctionDebugTool_EvalSecondDerivXY);\
  if ((option & OptionEvalSecondDeriv) && pd2fy2) Spyer->Record(FXY, paramx, paramy, *pd2fy2, CATMathFunctionDebugTool_EvalSecondDerivY2);\
  }}

#else
#define CATMathFunctionDebugToolSpyEval(F, param, value) // 
#define CATMathFunctionDebugToolSpyEvalFirstDeriv(F, param, value) // 
#define CATMathFunctionDebugToolSpyEvalAndFirstDeriv(F, param, f, df)//
#define CATMathFunctionDebugToolSpyEvalSecondDeriv(F, param, value)//
#define CATMathFunctionDebugToolSpyEvalThirdDeriv(F, param, value)//
#define CATMathFunctionDebugToolSpyEvalGen(F, option, param, pf, pdf, pd2f)//
#define CATMathFunctionDebugToolSpyEvalXY(FXY, paramx, paramy, f)//
#define CATMathFunctionDebugToolSpyEvalFirstDerivX(FXY, paramx, paramy, dfx)//
#define CATMathFunctionDebugToolSpyEvalFirstDerivY(FXY, paramx, paramy, dfy)//
#define CATMathFunctionDebugToolSpyEvalSecondDerivX2(FXY, paramx, paramy, d2fx2)//
#define CATMathFunctionDebugToolSpyEvalSecondDerivXY(FXY, paramx, paramy, d2fxy)//
#define CATMathFunctionDebugToolSpyEvalSecondDerivY2(FXY, paramx, paramy, d2fy2)//
#define CATMathFunctionDebugToolSpyEvalXYGen(FXY, option, paramx, paramy, pf, pdfx, pdfy, pd2fx2, pd2fxy, pd2fy2)//
#endif

typedef enum
  {
   CATMathFunctionDebugTool_NoDumpNoSample = 0,
   CATMathFunctionDebugTool_DumpAndSample,
   CATMathFunctionDebugTool_Sample,
   CATMathFunctionDebugTool_Dump
  }CATMathFunctionDebugTool_SpyMode;

class ExportedByCATAdvancedMathematics CATMathFunctionDebugTool
{
 public:
 CATMathFunctionDebugTool() ;

 ~CATMathFunctionDebugTool() ;

 //-----------------------------------------------------------------
 // Definition de la sortie
 //-----------------------------------------------------------------
 void SetDebugOutput(CATCGMOutput* iDebugOutput);

 // --------------------------------------------------------------------------
 // activation du mecanisme d'espionnage des sous-fonctions (si instrumentees)
 // --------------------------------------------------------------------------
 void ActiveSpy(CATMathFunctionDebugTool_SpyMode SpyMode = CATMathFunctionDebugTool_DumpAndSample);

 // --------------------------------------------------------------------------
 // desactive le dump de pointeur dans les traces (pour systemes de comparaisons de traces)
 // --------------------------------------------------------------------------
 void InactivePointerDump();

 // --------------------------------------------------------------------------
 // dump dans sortie standard de la fonction discretisee
 // --------------------------------------------------------------------------
 void SampleDump(CATMathFunctionX* iF, CATMathOption iSimpleEvalOption,
                 int iFullInterval,
                 int iSubRatio, // ratio de taille des sous-intervalles de discretisation
                 double iStart, double iEnd,
                 double iSubStart, double iSubEnd,
                 CATBoolean        iWithTitleAndLabels = TRUE) ;
 // --------------------------------------------------------------------------
 // Dump dans sortie standard de la fonction discretisee, de sa derivee
 // et utilisation du controle de derivee par les differences finies
 // --------------------------------------------------------------------------
 void SampleDumpAndDerivControl(CATMathFunctionX* iF,  CATMathOption iSimpleEvalOption,
                 int iFullInterval,
                 int iSubRatio, // ratio de taille des sous-intervalles de discretisation
                 double iStart, double iEnd,
                 double iSubStart, double iSubEnd) ;

 //----------------------------------------------------------------------------------------------------
 // Dump d'un echantillon equireparti d'une fonction XY
 //----------------------------------------------------------------------------------------------------
 void SampleDump(CATMathFunctionXY* iFXY,
                 CATMathFunctionDebugTool_OptionEvalXY iSimpleEvalOption,
                 int iSubRatioX, int iSubRatioY,// ratio de taille des sous-intervalles de discretisation
                 double iStartX, double iEndX,
                 double iStartY, double iEndY) ;

 //----------------------------------------------------------------------------------------------------
 // Dump d'un echantillon equireparti d'une fonction d'un systeme XY
 //----------------------------------------------------------------------------------------------------
 void SampleDump(CATMathSystemXY* iSystemXY,
                 int NumFunction, // numero de la fonction a utiliser (1 pour EvalF, 2 pour EvalG)
                 CATMathFunctionDebugTool_OptionEvalXY iSimpleEvalOption,
                 int iSubRatioX, int iSubRatioY,// ratio de taille des sous-intervalles de discretisation
                 double iStartX, double iEndX,
                 double iStartY, double iEndY) ;

 // --------------------------------------------------------------------------
 // enregistrement d'une valeur de fonction (ou derivee... selon iOptionEval)
 // --------------------------------------------------------------------------
 void Record(CATMathFunctionX* iF,
             double iparam,
             double ivalue,
             CATMathOption iOptionEval) ;

 void Record(CATMathFunctionXY* iFXY,
             double iparamx, double iparamy,
             double ivalue,
             CATMathFunctionDebugTool_OptionEvalXY iOptionEval // CATMathOption iOptionEval
            );
 //----------------------------------------------------------------------------------------------------
 // Suppression des enregistrements associes a une fonctionX
 //----------------------------------------------------------------------------------------------------
 void RemoveRecords(CATMathFunctionX* iFX) ;

 //----------------------------------------------------------------------------------------------------
 // Suppression des enregistrements associes a une fonctionXY
 //----------------------------------------------------------------------------------------------------
 void RemoveRecords(CATMathFunctionXY* iFXY);

 //----------------------------------------------------------------------------------------------------
 //KJD 14APR2010
 // Représentation graphique des 2 équations d'un CATMathSystemXY (F et G)  alors que les équations ne sont plus accessibles.
 // Fichiers de sorties sont générés dans repertoire standard de sortie des objets de test (et non dans E:\tmp)
 // L'option iOptions=OptionEval génère le fichier Func.txt.
 // L'option OptionEvalFirstDeriv génère en plus les fichiers FuncDF.txt et FuncDG.txt.
 //----------------------------------------------------------------------------------------------------
 static void SystemXYGraphicEditor(const CATMathSystemXY          & iSystemXY,
                                   const CATMathIntervalND        & iDomain  ,
                                   const CATLONG32                  Nu       ,
                                   const CATLONG32                  Nv       ,
                                   const CATMathOption              iOptions ,
                                   const CATLISTV(CATMathPoint2D) * ListOfRefPoint = NULL);

 // --------------------------------------------------------------------------
 // KJD 1JUNE18
 // dump dans sortie standard de 2 fonctions discretisees pour permettre
 // une comparaison graphique
 // Visu histogramme avec
 // "-" : vide
 // "*" : position du point de f
 // "+" : position du point de g
 // "#" : position du point quand f = g
 // "0" : position du 0 
 // si zoom :
 // "@" : position du point de f
 // "o" : position du point de f en cas de 2 zooms consecutifs
 // "%" : position du point de g
 // "s" : position du point de g en cas de 2 zooms consecutifs
 // "=" : position du point quand f = g
 // --------------------------------------------------------------------------
 void SampleDump(CATMathFunctionX* iF, CATMathFunctionX* iG, 
                 CATMathOption iSimpleEvalOption,
                 int iFullInterval,
                 int iSubRatio, // ratio de taille des sous-intervalles de discretisation
                 double iStart, double iEnd,
                 double iSubStart, double iSubEnd,
                 CATBoolean        iWithTitleAndLabels = TRUE) ;

 /*---------------------*/
 /*--*/ protected: /*---*/
 /*---------------------*/
 //----------------------------------------------------------------------------------------------------
 // Dump des records, et re-sampling des fonctions espionnees
 //----------------------------------------------------------------------------------------------------
 void DumpAndSampleRecords(CATMathFunctionDebugTool_SpyMode iSpyMode) ;
 //----------------------------------------------------------------------------------------------------
 // reallocation des enregistrements si necessaire
 //----------------------------------------------------------------------------------------------------
 void ReallocRecords(int NbNecessaryRecords) ;

 private:

 void SampleDumpWork(CATMathFunctionX* iF, CATMathFunctionX* iG, CATMathOption iSimpleEvalOption,
                     int iSubRatio, // ratio de taille des sous-intervalles de discretisation
                     double iStart, double iEnd,
                     CATBoolean        iWithTitleAndLabels = TRUE) ;

 void ComputePos(double* iTab, int inbcar, double  iStart, double  iEnd, 
                 int iNbPoints,  double imin, int iNoise,
                 double idelta, double iscale, int * oTabPos, int * oTabPosZoom);

 void Eval(CATMathFunctionX* iF, CATMathOption iSimpleEvalOption, double iParam, double & of, double & odf);
  
  //----------------------------------------------------------------------------------------------------
 // Suppression des enregistrements associes a une fonction 
 //----------------------------------------------------------------------------------------------------
 void RemoveRecords(CATMathFunctionX* iFX, CATMathFunctionXY* iFXY);


 int _DumpPointer;
 int _NbRecords ;
 int _NbMaxRecords ;
 CATMathFunctionDebugTool_SpyMode _ActiveSpy ;

 void* _Records;

 CATCGMOutput* _DebugOutput;
} ;
#endif
