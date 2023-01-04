/* -*-c++-*- */
#ifndef CATMathStrFunctionType_h
#define CATMathStrFunctionType_h

// COPYRIGHT DASSAULT SYSTEMES 1999
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
// A propos du versionning (eventuel) du stream de fonctions. NLD290709
// ---------------------------------------------------------
// - Dans les fonctions ou le stream est deja implemente avant le 23/07/09, aucun entier specifique indiquant un numero
// de version n'est sauve et relu, de sorte que, intrinsequement, chaque stream de fonction ne permet pas 
// d'evolution.
// - Pour CATNormalSquareNormFunction (CATMathStrNormalSquareNormType), je prevois cela
// - Pour CATMathDerivFunctionX       (CATMathStrDerivXType)          , je ne le prevois pas, devrait etre inutile.
// - Mais, pour celle-ci et pour toutes les autres, je propose ceci, au cas ou le versioning se revelerait necessaire:
// le gestionnaire general de stream/unstream piloterait un changement de type, en changeant le code de stream,
// par exemple en passant de CATMathStrPolynomXType a CATMathStrPolynomXV2Type.
//-------------------------------------------------------------------------------------------------------------------------------
// A propos du stream de versions hors framework AdvancedMathematics. NLD310709
// -----------------------------------------------------------------
// Le stream n'est pas trop un probleme. Le probleme c'est le UnStream(), qui necessite d'appeler du code
// dans un autre framework, qu'il faut connaitre.
// - Une possibilite generale et robuste est de faire une gestion similaire a CATExtCGMReplay dont les objets
// derives implementent des methodes  GetSharedlibOfOperator()/GetAvailableOperators(). C'est la robuste solution TCX
// - Une autre possibilite est de centraliser ici, pour les fonctions externes,
// non seulement leurs codes, mais des codes de SharedLib.
// Cela permettrait deja d'avancer sans trop de lourdeur et de difficulte. C'est la tactique solution NLD.
//-------------------------------------------------------------------------------------------------------------------------------
// 23/07/09 NLD (courant R19) Ajout previsionnel CATMathStrNormalSquareNormType               (implemente le 23/07)
// 23/07/09 NLD (courant R19) Ajout previsionnel CATMathStrFractionXYType                     (implemente le 29/07)
// 23/07/09 NLD (courant R19) Ajout previsionnel CATMathStrDerivXType                         (implemente le 23/07)
// 29/07/09 NLD (courant R19) Ajout previsionnel CATMathStrSingleMemoryXYType                 (implemente le 29/07)
// 29/07/09 NLD (courant R19) Ajout previsionnel CATMathStrOppositeXType                      (implemente le 29/07)
// 31/07/09 NLD (courant R19) Ajout previsionnel CATMathStrEquationProjectionPtCrvType        (implemente le 31/07)
//                                          avec CATMathStrEquationProjectionPtCrvUnStreamSharedLib
//                                            et CATMathStrEquationProjectionPtCrvUnStreamEntryName
// 31/07/09 NLD (courant R19) Ajout previsionnel CATMathStrSweepCoherenceFormDirFunctionXType (implemente le 31/07)
//                                          avec CATMathStrSweepCoherenceFormDirFunctionXUnStreamSharedLib
//                                            et CATMathStrSweepCoherenceFormDirFunctionXUnStreamEntryName
//              Ajout type CATFunctionXUnStream pour les chargements dynamiques de fonctions X de UnStream()
// 31/07/09 NLD Introduction de CATMathStrFunctionNoType pour parametrer le -1 
// 05/08/09 NLD Ajout CATMathStrEquationDistancePtCrvType        (implemente le 05/08)
//               avec CATMathStrEquationDistancePtCrvUnStreamSharedLib
//                 et CATMathStrEquationDistancePtCrvUnStreamEntryName
//              Ajout CATMathStrOffsetSurfaceCGMFunctionXYType      (implemente le 05/08) pour CATOffsetSurfaceCGMFunctionXY
//               avec CATMathStrOffsetSurfaceCGMFunctionXYUnStreamSharedLib
//                 et CATMathStrOffsetSurfaceCGMFunctionXYUnStreamEntryName
//              Ajout type CATFunctionXYUnStream pour les chargements dynamiques de fonctions XY de UnStream()
//              Ajout CATMathStrGenericFilletEquationType      (implemente le 05/08) pour CATGenericFilletEquation
//               avec CATMathStrGenericFilletEquationSharedLib
//                 et CATMathStrGenericFilletEquationEntryName
// 21/10/09 NLD Ajout CATMathStrFunctionInitProjIsoparType      (implemente le 21/10) pour CATFunctionInitProjIsopar
//               avec CATMathStrFunctionInitProjIsoparSharedLib
//                 et CATMathStrFunctionInitProjIsoparUnStreamEntryName
//   /02/10 tcx Protocole de definition de domaines
//   /02/11 tcx Ajout CATMathStrCylinderEquationXYType
//                    CATMathStrPolarSphereEquationXYType
//                    CATMathStrTorusEquationXYType
//                    CATMathStrConeEquationXYType
// 17/11/17 NLD Ajout CATMathStrFunctionG2IntoC2Type (pour stream/unstream CGMReplay et non stream officiel)
//              Mise au propre
//              macro CATFunctionXUnStreamArguments
//              macro CATFunctionXYUnStreamArguments
// 23/11/17 NLD Indication des frameworks (<==>domaines) pour les fonctions hors AdvancedMathematics
// 21/06/18 NLD Ajout CATMathStrMvFrPseudoOrthoFunctionXType pour CATMvFrPseudoOrthoFunctionX 
//              Deflaggage
// 21/06/18 NLD Ajout CATMathStrLawEquationDistCrvType             pour CATLawEquationDistCrv             (implementation en cours)
//                    CATMathStrLawEquationDistPCrvPCrvType        pour CATLawEquationDistPCrvPCrv        (implementation en cours)
//                    CATMathStrLawEquationDistLnCrvParamOnCrvType pour CATLawEquationDistLnCrvParamOnCrv (implementation en cours)
// 29/03/21 NLD Ajout CATMathStrSinXType                           pour CATMathSinX                       (implementation en cours)
//              Ajout CATMathStrCosXType                           pour CATMathCosX                       (implementation en cours)
//-------------------------------------------------------------------------------------------------------------------------------
#include "CATIACGMLevel.h"

#include "CATMathStream.h"
#include "YN000FUN.h"

#include "CATTolerance.h"

class CATMathFunctionX;
class CATMathFunctionXY;

/**
* @nodoc
*/

// N.B proceder toujours par ajout et pas par modification: ne JAMAIS changer les codes existants
//     sinon incompatibilite (nouveau unstream / ancien stream) et donc lecture impossible de vieux fichiers. NLD231117
#define CATMathStrFunctionNoType                     -1

// CATMathFunctionX
#define CATMathStrPolynomXType                        1
#define CATMathStrTrigonometricXType                  2
#define CATMathStrFractionXType                       3
#define CATMathStrCombinationXType                    4
#define CATMathStrPiecewiseXType                      5 
#define CATMathStrQuinticXType                        6
#define CATMathStrArctanCosXType                      7
#define CATMathStrSingleMemoryXType                   8
#define CATMathStrCompositionXByXYType                9
#define CATMathStrCubicXType                         10
#define CATMathStrCompositionXByXType                11
#define CATMathStrLinearXType                        12 
#define CATMathStrDerivXType                         13 
#define CATMathStrOppositeXType                      14
#define CATMathStrEquationProjectionPtCrvType        15         // GeometricOperators
#define CATMathStrSweepCoherenceFormDirFunctionXType 16         // FreeFormOperators
#define CATMathStrEquationDistancePtCrvType          17         // GeometricOperators
#define CATMathStrFunctionInitProjIsoparType         18         // GeometricOperators
#define CATMathStrPOffsetEquationUVXType             19         // GeometricOperators
#define CATMathStrFunctionG2IntoC2Type               20         // FreeFormOperators
#define CATMathStrMvFrPseudoOrthoFunctionXType       21         // FreeFormOperators            NLD210618
#define CATMathStrLawEquationDistCrvType             22         // FreeFormOperators   EN COURS NLD061118
#define CATMathStrLawEquationDistPCrvPCrvType        23         // FreeFormOperators   EN COURS NLD210618
#define CATMathStrLawEquationDistLnCrvParamOnCrvType 24         // FreeFormOperators   EN COURS NLD210618
#define CATMathStrSinXType                           25         // AdvancedMathematics EN COURS NLD290321
#define CATMathStrCosXType                           26         // AdvancedMathematics EN COURS NLD290321


// CATMathFunctionXY
#define CATMathStrPolynomXYType                     101
#define CATMathStrPiecewiseXYType                   102
#define CATMathStrSumXYsType                        103
#define CATMathStrNormalSquareNormType              104
#define CATMathStrFractionXYType                    105
#define CATMathStrSingleMemoryXYType                106
#define CATMathStrOffsetSurfaceCGMFunctionXYType    107
#define CATMathStrGenericFilletEquationType         108         // GeometricObjectsCGM
#define CATMathStrLinearXYType                      109
#define CATMathStrCylinderEquationXYType            110         // GeometricObjectsCGM
#define CATMathStrPolarSphereEquationXYType         111         // GeometricObjectsCGM
#define CATMathStrTorusEquationXYType               112         // GeometricObjectsCGM
#define CATMathStrConeEquationXYType                113         // GeometricObjectsCGM
 
extern  ExportedByYN000FUN const char CATMathFunctionDomainType_AdvancedMathematics[3];
extern  ExportedByYN000FUN const char CATMathFunctionDomainType_GeometricObjectsCGM[3];
extern  ExportedByYN000FUN const char CATMathFunctionDomainType_FreeFormOperators  [3];
extern  ExportedByYN000FUN const char CATMathFunctionDomainType_GeometricOperators [3];

#define CATFunctionXUnStreamArguments  CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] 
#define CATFunctionXYUnStreamArguments CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] 

extern "C"
{
  /** @nodoc */
  typedef            CATMathFunctionX    * CATFunctionXUnStream                          (CATFunctionXUnStreamArguments);
  typedef            CATFunctionXUnStream* CATGetFunctionXUnStream                       (const short iType) ;
  ExportedByYN000FUN CATFunctionXUnStream* CATGetFunctionXUnStreamAdv                    (const short iType) ;

  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_LinearX                  (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_PolynomX                 (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_TrigonometricX           (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_FractionX                (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_CombinationX             (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_PiecewiseX               (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_QuinticX                 (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_ArctanCosX               (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_SingleMemoryX            (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_CompositionXByXY         (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_CubicX                   (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_CompositionXByX          (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_LinearX                  (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_DerivX                   (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_OppositeX                (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_SinX                     (CATFunctionXUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionX    * CATFunctionXUnStream_CosX                     (CATFunctionXUnStreamArguments);
  
  /** @nodoc */
  typedef            CATMathFunctionXY    * CATFunctionXYUnStream                        (CATFunctionXYUnStreamArguments);
  typedef            CATFunctionXYUnStream* CATGetFunctionXYUnStream                     (const short iType) ;
  ExportedByYN000FUN CATFunctionXYUnStream* CATGetFunctionXYUnStreamAdv                  (const short iType) ;

  // N.B ci-dessous problemes de nomenclature; ces fonctions XY devraient se prefixer CATFunctionXYUnStream   NLD171117
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_PolynomXY               (CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_PiecewiseXY             (CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_SumXYs                  (CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_NormalSquareNormFunction(CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_FractionXY              (CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_SingleMemoryXY          (CATFunctionXYUnStreamArguments);
  ExportedByYN000FUN CATMathFunctionXY    * CATFunctionXUnStream_LinearXY                (CATFunctionXYUnStreamArguments);
 
}


#endif
