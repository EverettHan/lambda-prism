// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateFrFCompositeCurve :
// Declaration of global functions used to create and destroy
// an instance of the CompositeCurve operator
//
//=============================================================================
// Usage notes:
// 
// *** Les Create prenant en entree une CompositeCurve en recopient la
// *** SoftwareConfiguration
// *** Si on utilise les autres, il est imperatif de faire un SetSoftwareConfiguration
// *** sur la CompositeCurve obtenue avant sa premiere utilisation
//
// sample of use :
// to provide
//
//=============================================================================
// Dec r 97 CPL Creation                                               Pradalou
// Nov   98 NLD
//         /CPL Ajout CreateCompositeCurve_PackCcv
// 17/03/99 NLD Ajout CreateCompositeCurve_InvertCcv
// 04/11/03 MNA Nouvelle signature de Pack_ccv avec Liste des crv issues d'occurences multiples  
//              en argument par defaut
// 04/11/03 MNA J'elimine l'ancienne signature de Pack_ccv
// 11/01/06 NLD Suppression des signatures sans implementation
// 11/01/06 NLD Ajout CreateCompositeCurve_Streamable()
// 05/04/17 NLD Smart indent
//=============================================================================
#ifndef CreateFrFCompositeCurve_H 
#define CreateFrFCompositeCurve_H 
//
#include <CATGMOperatorsInterfaces.h>
#include <CATMathDef.h>
#include <CATSkillValue.h>
#include <CATTopDef.h>
#include <CATListOfInt.h>

//
class CATCurve;
class CATCrvLimits;
class CATFrFCompositeCurve;
class CATBody;
class CATEdge;
class CATEdgeCurve;
class CATMergedCurve;
class CATPCurve;
class CATSoftwareConfiguration;


//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (      CATLONG32            iNumberOfCurves      ,
                                                             CATCurve          ** iCurves              ,
                                                             CATCrvLimits       * iCrvLimits           ,
                                                             CATLONG32          * iCrvOrientation      ,
                                                             CATLONG32          * iSupportOrientation  );
//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (      CATLONG32             iNumberOfCurves     ,
                                                             CATCurve          **  iCurves             );
//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (      CATLONG32             iNumberOfCurves     ,
                                                             CATCrvLimits       *  iCrvLimits          ,
                                                             CATLONG32          *  iCrvOrientation     ,
                                                             CATLONG32          *  iSupportOrientation ,
                                                             CATEdgeCurve      **  iMergedCurves       ,
                                                             CATCurve          **  iCurves             ,
                                                             CATPCurve         **  iPCurves            );

ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (      CATCurve           *  iCurve              ,
                                                       const CATCrvLimits        & iCrvLimits          );

//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (      CATCurve           *  iCurve              );

//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (const CATBody            *  iWire               ,
                                                             CATLONG32             iStartIndex         = -1,
                                                             CATLONG32             iEndIndex           = -1);

// Same Create as previous except it returns a list of Edge
// corresponding to the CCV
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (const CATBody            *  iWire               ,
                                                             CATEdge           **& oEdgeList           ,
                                                             CATLONG32             iStartIndex         = -1,
                                                             CATLONG32             iEndIndex           = -1);

// La methode suivante prend en entree une liste de Edge
// avec leur orientation associee et cree une CompositeCurve.
// Si les Edge pointent sur plusieurs Curve, il n y a pas de sortie
// en erreur et la premiere est choisie
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (const CATEdge            **  iEdgeList           ,
                                                       const CATOrientation      *  iListOfOrien        ,
                                                             CATLONG32              iNbOfEdgeCur        );
//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateConnexCompositeCurve     (const CATBody             *  iWire               ,
                                                             double                 iResolution         ,
                                                             CATLONG32              iStartIndex         = -1,
                                                             CATLONG32              iEndIndex           = -1);
//
ExportedByCATGMOperatorsInterfaces
CATFrFCompositeCurve * CreateCompositeCurve           (const CATFrFCompositeCurve * iToCopy             );
//

// rend 0 si pack non necessaire
/*
ExportedByCATGMOperatorsInterfaces
void                   CreateCompositeCurve_PackCcv   (      CATFrFCompositeCurve*  iCcv                 ,
                                                             CATFrFCompositeCurve*& oCcv                 );
*/

// rend 0 si pack non necessaire
//Nouvelle signature de Pack_ccv avec Liste des crv issues d'occurences multiples

ExportedByCATGMOperatorsInterfaces
void                   CreateCompositeCurve_PackCcv   (      CATFrFCompositeCurve *  iCcv                ,
                                                             CATFrFCompositeCurve *& oCcv                ,
                                                             CATListOfInt         *  oListOfIndexPackcrv = NULL);

// rend une ccv inversee
ExportedByCATGMOperatorsInterfaces
void                   CreateCompositeCurve_InvertCcv (      CATFrFCompositeCurve *  iCcv                ,
                                                             CATFrFCompositeCurve *& oCcv                );

//
// rend une ccv streamable (sans foreign curve) (la meme eventuellement)
ExportedByCATGMOperatorsInterfaces
void                   CreateCompositeCurve_Streamable(      CATFrFCompositeCurve *  iCcv                 ,
                                                             CATFrFCompositeCurve *& oCcv                 ,
                                                             CATListOfInt         *  oListOfIndexNewCrv   = NULL);

ExportedByCATGMOperatorsInterfaces
void                   Remove                         (      CATFrFCompositeCurve *& ioCompositeCurve     );


#endif
