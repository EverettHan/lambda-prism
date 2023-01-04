/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATSurVertexG2Modification :
// Interface class of the CATSurVertexG2ModificationCx2.
//
//=============================================================================
// Usage notes:
// sample of use :
//
//=============================================================================
//   /01/99 NDN Creation
//          CPT Deplacement dans GMOperatorsInterfaces
// 18/02/15 NLD Nouvelle signature de CreateSurVertexG2Modification()
//              avec iSoftwareConfiguration et sans iMode
//              Detabulation
// 02/11/16 NLD Ajout nouvelle signature CATCreateSurVertexG2Modification() avec configuration
//              et sans mode pour respect des conventions de nommage et de fonctionnement
//              (le CreateSurVertexG2Modification() equivalent devra disparaitre)
// 08/11/16 NLD Migration sur CATCGMOPerator pour instrumentation CGMReplay
//              Run() devient typee int
//              Recopie depuis l'implementation des documentations de SetContinuityOnBorder() et SetMovingField(),
//              l'operateur etant jusqu'ici assez inutilisable
// 16/01/17 NLD Correction des incompatibilites avec les macros CATCGMOperatorDebug*
//=============================================================================
#ifndef CATSurVertexG2Modification_H 
#define CATSurVertexG2Modification_H

#define CATSurVertexG2Modification_AsCGMOperator

#include "CATSkillValue.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATMathGridOfVectors;
class CATGeoFactory;
class CATNurbsSurface;
class CATSoftwareConfiguration;

#ifdef CATSurVertexG2Modification_AsCGMOperator
#include "CATCGMOperator.h" // #include "CATGeoOperator.h" NON ACCESSIBLE
#include "CATCGMOperatorDebug.h"
class CATGeoFactory;
#endif
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATSurVertexG2Modification
#ifdef CATSurVertexG2Modification_AsCGMOperator
 : public CATCGMOperator
#else
 : public CATCGMVirtual
#endif
{
#ifdef CATSurVertexG2Modification_AsCGMOperator
  CATCGMVirtualDeclareClass(CATSurVertexG2Modification);
#endif
  public :
#ifdef CATSurVertexG2Modification_AsCGMOperator
                            CATSurVertexG2Modification(CATGeoFactory* iFactory);
#endif
  
  virtual                   ~CATSurVertexG2Modification();
   
  /** @nodoc @nocgmitf */
#ifdef CATSurVertexG2Modification_AsCGMOperator
//  CATCGMOperatorDebugDeclareRun(CATSurVertexG2Modification,CATCGMOperator);
#else

  virtual int               Run                  ()                   = 0;
#endif

  //              - border = -1 if this border is free
  //                       =  0 if there is a C0 constraint
  //                       =  1 if there is a G1 constraint
  //                       =  2 if there is a G2 constraint
  //                       =  3 if there is a G3 constraint
  virtual void              SetContinuityOnBorder(CATLONG32            borderU1,
                                                  CATLONG32            borderU2,
                                                  CATLONG32            borderV1,
                                                  CATLONG32            borderV2) =0;

 // Input Data : - iMovingField : represent a vector field applied
 //                on the control point net. Its size should be equal
 //                to control point's grid.
  virtual void              SetMovingField(const CATMathGridOfVectors *iMovingField) =0;

};


//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces
CATSurVertexG2Modification * CATCreateSurVertexG2Modification(   CATGeoFactory           * iFactory              ,
                                                                 CATSoftwareConfiguration* iSoftwareConfiguration,
                                                                 CATNurbsSurface         * ioNurbsSurface        ,
                                                                 CATLONG32                 borderU1              ,
                                                                 CATLONG32                 borderU2              ,
                                                                 CATLONG32                 borderV1              ,
                                                                 CATLONG32                 borderV2              ,
                                                           const CATMathGridOfVectors    * iMovingField          );

//-----------------------------------------------------------------------------
// DEPRECATED see above. NLD021116
ExportedByCATGMOperatorsInterfaces
CATSurVertexG2Modification * CreateSurVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                 CATSoftwareConfiguration* iSoftwareConfiguration,
                                                                 CATNurbsSurface         * ioNurbsSurface        ,
                                                                 CATLONG32                 borderU1              ,
                                                                 CATLONG32                 borderU2              ,
                                                                 CATLONG32                 borderV1              ,
                                                                 CATLONG32                 borderV2              ,
                                                           const CATMathGridOfVectors    * iMovingField          );

//-----------------------------------------------------------------------------
// DEPRECATED see above. NLD180215
ExportedByCATGMOperatorsInterfaces
CATSurVertexG2Modification * CreateSurVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                 CATNurbsSurface         * ioNurbsSurface        ,
                                                                 CATLONG32                 borderU1              ,
                                                                 CATLONG32                 borderU2              ,
                                                                 CATLONG32                 borderV1              ,
                                                                 CATLONG32                 borderV2              ,
                                                           const CATMathGridOfVectors    * iMovingField          ,
                                                                 CATSkillValue             iMode                 = BASIC);


ExportedByCATGMOperatorsInterfaces
void Remove(CATSurVertexG2Modification *&iMove);

#endif
