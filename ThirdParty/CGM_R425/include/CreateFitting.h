// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// December. 97  Creation                        cen-nld
// Remarque importante :
//   Cet operateur de Fitting ne se comporte pas comme tous les 
//   operateurs en ce qui concerne mode BASIC et mode ADVANCED 
// En fait le mode ADVANCED sert juste a passer de facon claire et 
// simple les donnees et les options
//=============================================================================



/*****************************************************************************
 
   NE PLUS UTILISER - UTILISER CATLISS - NE PLUS UTILISER - UTILISER CATLISS
 
*******************************************************************************/


#ifndef CREATEFITTING_H 
#define CREATEFITTING_H 

// 23/04/12 NLD Ajout CATCreateFitting() (2 signatures)
//              Les deux signatures de CreateFitting() restent inchangées et merdiques
//              Je conserve l'argument mode dans les CATCreateFitting() tellement
//              ca fonctionne bizarrement (voir les implémentations)

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

#ifndef NULL
#define NULL 0
#endif

class CATMathSetOfPointsNDTwoTangents;
class CATFitting;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces
CATFitting *    CreateFitting(CATMathSetOfPointsNDTwoTangents *iPoints,
                              CATLength iFittingTol,
                              CATSkillValue mode,
                              CATGeoFactory * iFactory = NULL );

ExportedByCATGMOperatorsInterfaces
CATFitting * CATCreateFitting(CATGeoFactory                   * iFactory,
                              CATSoftwareConfiguration        * iConfig,
                              CATMathSetOfPointsNDTwoTangents * iPoints,
                              CATLength                         iFittingTol,
                              CATSkillValue                     mode
                             );

/* Au premier appel Il faut faire un GetResult ,
   et si  le pointeur iPtr n'est plus nul , il ne faut pas faire 
   de GetResult                                                      */
ExportedByCATGMOperatorsInterfaces
CATFitting * CreateFitting   (CATMathSetOfPointsNDTwoTangents *iPoints,
                              CATLength                        iFittingTol,
                              CATLONG32                        iDegree ,
                              CATFrFNurbsMultiForm           * iPtr ,
                              CATSkillValue                    mode,
                              CATGeoFactory                  * iFactory = NULL );

/* Au premier appel Il faut faire un GetResult ,
   et si  le pointeur iPtr n'est plus nul , il ne faut pas faire 
   de GetResult                                                      */
ExportedByCATGMOperatorsInterfaces
CATFitting * CATCreateFitting(CATGeoFactory                   * iFactory,
                              CATSoftwareConfiguration        * iConfig,
                              CATMathSetOfPointsNDTwoTangents * iPoints,
                              CATLength                         iFittingTol,
                              CATLONG32                         iDegree ,
                              CATFrFNurbsMultiForm            * iPtr,
                              CATSkillValue                     mode
                             );

ExportedByCATGMOperatorsInterfaces
void Remove( CATFitting *&iFitting);


#endif



