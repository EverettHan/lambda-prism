#ifndef CATMathNormal_h
#define CATMathNormal_h

// #define CATMathNormal_MandatoryConfiguration "TEST ONLY pour controle buildtime migration sur bons constructeurs"
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathNormal:
//   This class compute the normal to a surface which is defined by
//   three functions of two variables.
//
//=============================================================================
// 23/05/07 NLD Ajout _Tolerance et SetTolerance()
// 13/08/08 NLD Ajout argument optionnel iTolerance dans les constructeurs
//              pour les cas d'utilisation tres massive ou l'on veut eviter tout appel
//              intermediaire un peu couteux a la longue a la tolerance par defaut 
// 04/05/09 NLD Ajout destructeur
// 11/01/10 NLD Ajout Init()
//              Ajout _SpyNormalX, _SpyNormalY, _SpyNormalZ,
//                    _SpyNormalDUX, _SpyNormalDUY, _SpyNormalDUZ,
//                    _SpyNormalDVX, _SpyNormalDVY, _SpyNormalDVZ
//              Ajout operator= et copy constructor pour eviter implementations par defaut
// 30/04/10 NLD Ajout _NormalSpyer de type CATMathNormalSpyer en remplacement des _Spy*
// 29/06/18 NLD Revue des notations et des signatures
//              Unaading step 1/3
//              - documentation de Normalize()
//              - renommage de l'argument iNorm2 de ComputeNormalFirstDer() en iNormalInvNorm
//              - données déplacées à la fin
// 03/07/18 NLD Unaading step 2/3
//              Suppression des multiples arguments totalement inutiles et ressortant en NaN (bravo leur design initial)
//              de ComputeNormalAndDerivIfDegenerate(), ComputeNormalAndSecondDerivIfDegenerate()
// 04/07/18 NLD Appelons un chat un chat et un produit vectoriel un produit vectoriel (et non scalaire)
//              (unaading step 3/3)
//              - ComputeVectorialProduct()           remplace ComputeDotProd()
//              - ComputeVectorialProductSquareNorm() remplace ComputeDotProdSquareNorm()
//              Preparation versionning
//              - numerotation stable et definitive des constructeurs
//              - reception optionnelle de la configuration dans Constructor_2, Constructor_4, Constructor_5
//              - reception de la configuration dans Init()
//              - ajout _CGMLevel
//              - ajout _XScaleV2
//              - ajout SetSoftwareConfiguration()
// 16/07/18 NLD Mise en conformité de la signature de Normalize(): un seul role par argument
//=============================================================================

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"

class CATMathFunctionXY;
//class CATMathIntervalND;

class CATMathNormalFunctionXYSpy ;
class CATMathNormalSpyer ;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathNormal : public CATCGMVirtual
{
 public:
  //---------------------------------------------------------------------------
  // Object Management.
  //---------------------------------------------------------------------------
  //                                                                            N.B Stable constructor numerotation, not to change
  //                                                                            Constructor_1
  #ifndef CATMathNormal_MandatoryConfiguration
  CATMathNormal                           ();
  #endif

  //                                                                            Constructor_2
  CATMathNormal                           (const CATTolerance              & iTolerance    ,
  #ifdef CATMathNormal_MandatoryConfiguration
                                                 CATSoftwareConfiguration *  iConfig       );
  #else
                                                 CATSoftwareConfiguration *  iConfig       = NULL);
  #endif

  //                                                                            Constructor_3
  CATMathNormal                           (const CATMathNormal             & iNormal       );

  //                                                                            Constructor_4
  CATMathNormal                           (const CATMathFunctionXY        *  iX            ,
                                           const CATMathFunctionXY        *  iY            ,
                                           const CATMathFunctionXY        *  iZ            ,
  #ifdef CATMathNormal_MandatoryConfiguration
                                           const CATTolerance             *  iTolerance    ,
                                                 CATSoftwareConfiguration *  iConfig       );
  #else
                                           const CATTolerance             *  iTolerance    = NULL,
                                                 CATSoftwareConfiguration *  iConfig       = NULL);
  #endif

  //                                                                            Constructor_5
  CATMathNormal                           (const CATMathFunctionXY        *  iX            ,
                                           const CATMathFunctionXY        *  iY            ,
                                           const CATMathFunctionXY        *  iZ            ,
                                           const double                    & iCenterU      ,
                                           const double                    & iCenterV      ,
  #ifdef CATMathNormal_MandatoryConfiguration
                                           const CATTolerance             *  iTolerance    ,
                                                 CATSoftwareConfiguration *  iConfig       );
  #else
                                           const CATTolerance             *  iTolerance    = NULL,
                                                 CATSoftwareConfiguration *  iConfig       = NULL);
  #endif

 ~CATMathNormal                           ();

  CATMathNormal &              operator = (const CATMathNormal             & iNormalToCopy );

  //---------------------------------------------------------------------------
  // Method for modification.
  void SetEquations                       (const CATMathFunctionXY        *  iX            ,
                                           const CATMathFunctionXY        *  iY            ,
                                           const CATMathFunctionXY        *  iZ            );

  // void SetDomain(const CATMathIntervalND * iNewDomain);
  void SetDomainCenter                    (const double                    & iCenterU      ,
                                           const double                    & iCenterV      );

  //---------------------------------------------------------------------------
  // Normal evaluator.
  //   * oNormal is the normalized normal output. It is an array of 3 doubles.
  //   * iu and iv are the parameters where the normal is to be computed.
  //   * iDU, iDV and iDUV are optional pointers. The partial derivative
  //     can be given as arguments when available, for optimisation.
  //     When given, they are arrays of three doubles.
  //        iDU  is the first  derivative of the first  variable  iu.
  //        iDV  is the first  derivative of the second variable  iv.
  //        iDUV is the second derivative of both       variables iu and iv.
  //   * iDoNotNormalize is optional : if TRUE, oNormal is filled with normal direction
  //     and is NOT normalized.
  CATBoolean EvalNormal(                         double         * oNormal         ,
                                           const double           iu              ,
                                           const double           iv              ,
                                           const double         * iDU             = NULL,
                                           const double         * iDV             = NULL,
                                           const double         * iDUV            = NULL,
                                                 CATBoolean       iDoNotNormalize = FALSE) const;

  //---------------------------------------------------------------------------
  // Normal and normal derivatives evaluator.
  //   * oNormal is the normalized normal output. It is an array of 3 doubles.
  //   * oDerivU and oDerivV are the output for the first derivative of
  //     the normalized normal. They are arrays of 3 doubles.
  //   * iu and iv are the parameters where the normal is to be computed.
  //   * iDU, iDV, iDUV, iDU2 and iDV2 are optional pointers.
  //     The partial derivative can be given as arguments when available,
  //     for optimisarion.
  //     When given, they are arrays of three doubles.
  //        iDU  is the first  derivative of the first  variable  iu.
  //        iDV  is the first  derivative of the second variable  iv.
  //        iDU2 is the second derivative of the first  variable  iu.
  //        iDUV is the second derivative of both       variables iu and iv.
  //        iDV2 is the second derivative of the second variable  iv.
  CATBoolean EvalNormalAndDeriv(                 double         * oNormal         ,
                                                 double         * oDerivU         ,
                                                 double         * oDerivV         ,
                                           const double           iu              ,
                                           const double           iv              ,
                                           const double         * iDU             = NULL,
                                           const double         * iDV             = NULL,
                                           const double         * iDU2            = NULL,
                                           const double         * iDUV            = NULL,
                                           const double         * iDV2            = NULL) const;

  //---------------------------------------------------------------------------
  // Normal, normal derivatives and normal second derivatives evaluator.
  //   * oNormal is the normalized normal output. It is an array of 3 doubles.
  //   * oDerivU and oDerivV are the output for the first derivative of
  //     the normalized normal. They are arrays of 3 doubles.
  //   * oSecondDerivU, oSecondDerivV, oSecondDerivUV are the output for the second
  //     derivative of the normalized normal. They are arrays of 3 doubles.
  //   * iu and iv are the parameters where the normal is to be computed.
  //   * iDU, iDV, iDUV, iDU2, iDV2,  iDU2V, iDUV2, iDU3 and iDV3 are optional pointers.
  //     The partial derivative can be given as arguments when available,
  //     for optimisarion.
  //     When given, they are arrays of three doubles.
  //        iDU  is the first  derivative of the first  variable  iu.
  //        iDV  is the first  derivative of the second variable  iv.
  //        iDUV is the second derivative of both       variables iu and iv.
  //        iDU2 is the second derivative of the first  variable  iu.
  //        iDUV is the second derivative of both       variables iu and iv.
  //        iDV2 is the second derivative of the second variable  iv.
  //        iDU3 is the third  derivative of the first  variable  iu. 
  //        iDU2V, iDUV2 are third derivatives of both  variables iu and iv.
  //        iDV3 is the third  derivative of the second variable  iv.
 
  CATBoolean EvalNormalDerivAndSecondDeriv(      double         * oNormal         ,
                                                 double         * oDerivU         ,
                                                 double         * oDerivV         ,
                                                 double         * oSecondDerivU   ,
                                                 double         * oSecondDerivUV  ,
                                                 double         * oSecondDerivV   ,
                                           const double           iu              ,
                                           const double           iv              ,
                                           const double         * iDU             = NULL,
                                           const double         * iDV             = NULL,
                                           const double         * iDU2            = NULL,
                                           const double         * iDUV            = NULL,
                                           const double         * iDV2            = NULL,
                                           const double         * iDU3            = NULL,
                                           const double         * iDU2V           = NULL,
                                           const double         * iDUV2           = NULL,
                                           const double         * iDV3            = NULL) const;

  // Tolerances definition
  INLINE void SetTolerance(const CATTolerance & iTolObject) ;

  //---------------------------------------------------------------------------
  // That's all for public
  //---------------------------------------------------------------------------

  // protected:
  // restricted use. USE Constructor_2 for instance
  // Afin de piloter plus facilement le deploiement de la configuration,
  // je prefere inciter à migrer vers les bons constructeurs, avec un controle buildtime dans lequel
  // on enlevera la valeur par defaut de la configuration
  void SetSoftwareConfiguration           (      CATSoftwareConfiguration *  iConfig       );

 private:

   void Init                            (const CATMathFunctionXY        *  iX            = NULL,
                                         const CATMathFunctionXY        *  iY            = NULL,
                                         const CATMathFunctionXY        *  iZ            = NULL,
                                         const CATTolerance             *  iTolerance    = NULL,
                                               CATSoftwareConfiguration *  iConfig       = NULL);
   
   // At degenerated points, first and second derivatives of the normal may be asked for. In  
   // turn, derivatives of _X, _Y, and _Z of higher order than three may be needed. These can't 
   // be calculated by CATMathFunctionXY. These are roughly estimaded by the following method.
   // Precision: Suppose that CATMathFunctionXY evaluate 4n correct digits. The number of correct 
   // digits in the fourth derivatives will be around 2n and on the fifth derivatives, around n.
   void FiniteMethodHighDerivatives     (const double            * iThirdDeriv  ,
                                         const CATLONG32           iKindOfThird , // (iThirdDerivative = TD) 0: TD=DU3, 1: TD=DU2V, 2: TD=DUV2 and 3: TD=DV3.
                                         const double              iu           ,
                                         const double              iv           ,
                                               double            * oDUofTD      ,
                                               double            * oDVofTD      = NULL,
                                               double            * oDUUofTD     = NULL,
                                               double            * oDUVofTD     = NULL,
                                               double            * oDVVofTD     = NULL ) const ;


CATBoolean ComputeMissingInputsFirstDer (const double              iu           ,
                                         const double              iv           ,
                                         const double            * iDU          ,
                                         const double            * iDV          ,
                                               double            * ioAllocatedDU,
                                               double            * ioAllocatedDV,
                                               CATMathOption     * ioOption     = NULL) const;

CATBoolean ComputeMissingInputsSecondDer(const double              iu            ,
                                         const double              iv            ,
                                         const double            * iDU2          ,
                                         const double            * iDUV          ,
                                         const double            * iDV2          ,
                                               double            * ioAllocatedDU2,
                                               double            * ioAllocatedDUV,
                                               double            * ioAllocatedDV2,
                                               CATMathOption     * ioOption      ) const;

CATBoolean ComputeMissingInputsThirdDer (const double              iu        ,
                                         const double              iv        ,
                                         const double            * iDU3      ,
                                         const double            * iDU2V     ,
                                         const double            * iDUV2     ,
                                         const double            * iDV3      ,
                                               double            * ioAllocatedDU3,
                                               double            * ioAllocatedDU2V,
                                               double            * ioAllocatedDUV2,
                                               double            * ioAllocatedDV3) const; 

int        ComputeExactNormal           (      double            * iDU       ,
                                               double            * iDV       ,
                                               double            * ioNormal  ,
                                               double            & oNorm2DU  ,
                                               double            & oNorm2DV  ,
                                               double            & oNorm2    ) const;

CATBoolean ComputeNormalFirstDer        (      double            * iDU       ,
                                               double            * iDV       ,
                                               double            * iDU2      ,
                                               double            * iDUVu     ,
                                               double            * iDUVv     ,
                                               double            * iDV2      ,
                                               double            * iNormal   ,
                                               double              iNormalInvNorm, // NLD290618 et non pas iNorm2
                                               double            * ioDerivU  ,
                                               double            * ioDerivV  ,
                                               double            * ioU       ,
                                               double            * ioV       ,
                                               double            & oScalProdU,
                                               double            & oScalProdV) const;

// méthode ultra-piegeuse, qui normalise ioNormal, certes
// mais sans rien dire prend en entrée dans ioNorm2 le carré de la norme,
// et rend dans cette meme variable l'inverse de la norme
// NLD290618
// Mise en conformité: on distingue desormais deux arguments
// NLD160718
CATBoolean Normalize                    (      double              iNorm2    ,
                                               double            * ioNormal  ,
                                               double            & oInvNorm  ) const;

double     ComputeSquareNorm            (      double            * iNormal   ) const;

void       ComputeVectorialProduct      (      double            * iU        ,
                                               double            * iV        ,
                                               double            * ioNormal  ) const;

double     ComputeVectorialProductSquareNorm(  double            * iU,
                                               double            * iV        ) const;

void       SetToNull                    (      double            * ioTable   ) const;

void       CopyWithFactor               (      double            * ioTarget  ,
                                               double            * iReference,
                                               double              iFactor   ) const;

int        ComputeNormalIfDegenerate    (const double              iu        ,
                                         const double              iv        ,
                                               double            * ioDU      ,
                                               double            * ioDV      ,
                                               double            & ioNorm2DU ,
                                               double            & ioNorm2DV ,
                                               double            * ioNormal  ,
                                               double            & ioNorm2   ) const;
int        ComputeNormalAndDerivIfDegenerate
                                        (const double              iu        ,
                                         const double              iv        ,
                                               double            * ioDU      ,
                                               double            * ioDV      ,
                                               double            * ioDU2     ,
                                               double            * ioDUVp    ,
                                               double            * ioDUVq    ,
                                               double            * ioDV2     ,
                                               double            & ioNorm2DU ,
                                               double            & ioNorm2DV ,
                                               double            * ioNormal  ,
                                 // NLD030718  double            * ioDerivU  ,
                                 // NLD030718  double            * ioDerivV  ,
                                               double            & ioNorm2   ) const;

int        ComputeNormalAndSecondDerivIfDegenerate
                                        (const double              iu        ,
                                         const double              iv        ,
                                               double            * ioDU      ,
                                               double            * ioDV      ,
                                               double            * ioDU2     ,
                                               double            * ioDUVp    ,
                                               double            * ioDUVq    ,
                                               double            * ioDV2     ,
                                               double            * ioDU2Vp   ,
                                               double            * ioDUV2p   ,
                                               double            * ioDU2Vq   ,
                                               double            * ioDUV2q   ,
                                               double            * ioDU3     ,
                                               double            * ioDV3     ,
                                               double            & ioNorm2DU ,
                                               double            & ioNorm2DV ,
                                               double            * ioNormal  ,
                                 // NLD030718  double            * ioDerivU  ,
                                 // NLD030718  double            * ioDerivV  ,
                                 // NLD030718  double            * ioSecondDerivU,
                                 // NLD030718  double            * ioSecondDerivUV,
                                 // NLD030718  double            * ioSecondDerivV, 
                                               double            & ioNorm2   ) const;

void       GetDegeneratedDir                  (double              iu        ,
                                               double              iv        ,
                                               double            * iDU       ,
                                               double            * iDV       ,
                                               double            * iDUV      ,
                                               double              iNorm2    ,
                                               double              iNorm2DU  ,
                                               double              iNorm2DV  ,
                                               CATLONG32         & oBigDU    ,
                                               CATLONG32         & oBigDV    ) const;

void       Print                              (double            * iTable    ) const;

 private:
   const CATTolerance       * _TolObject ;

   const CATMathFunctionXY  * _X;
   const CATMathFunctionXY  * _Y;
   const CATMathFunctionXY  * _Z;
// const CATMathIntervalND  * _Domain; //domaine de definition des fonctions _X, _Y, _Z
   //dimension = 2
   
   // coordonnees du centre du domaine de definition de _X, _Y, _Z;
         double               _CenterU;
         double               _CenterV;

   // fonctions espionnes des valeurs en X, Y et Z de la normale
         CATMathNormalSpyer * _NormalSpyer;
   // Data management
         int                  _CGMLevel;
         int                  _XScaleV2;
};

//-----------------------------------------------------------------------------
// Tolerances definition
INLINE void CATMathNormal::SetTolerance(const CATTolerance & iTolObject)
{
 _TolObject = &iTolObject ;
}


#endif
