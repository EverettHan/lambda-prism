/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATCrvVertexG2Modification :
// Interface class of the CATCrvVertexG2ModificationCx2.
//
//=============================================================================
// Usage notes:
// sample of use :
//
//=============================================================================
//   /01/99 NDN Creation                                                    NDN
// 11/03/15 NLD Ajout CATCreateCrvVertexG2Modification avec configuration
// 11/07/16 NLD Migration sur CATCGMOperator pour instrumentation CGMReplay
//              Run() devient typee int
// 16/01/17 NLD Correction des incompatibilites avec les macros CATCGMOperatorDebug*
//=============================================================================
#ifndef CATCrvVertexG2Modification_H 
#define CATCrvVertexG2Modification_H

#define CATCrvVertexG2Modification_AsCGMOperator

#include "CATSkillValue.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

#ifdef CATCrvVertexG2Modification_AsCGMOperator
#include "CATCGMOperator.h"
#include "CATCGMOperatorDebug.h"
#include "CATCGMVirtual.h"
#endif
class CATMathSetOfVectors;
class CATGeoFactory;
class CATNurbsCurve;
class CATPNurbs;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATCrvVertexG2Modification
#ifdef CATCrvVertexG2Modification_AsCGMOperator
  : public CATCGMOperator
#else
  : public CATCGMVirtual
#endif
{
#ifdef CATCrvVertexG2Modification_AsCGMOperator
  CATCGMVirtualDeclareClass(CATCrvVertexG2Modification);
#endif
  public :
#ifdef CATCrvVertexG2Modification_AsCGMOperator
                            CATCrvVertexG2Modification(      CATGeoFactory            * iFactory              );
//                                                           CATSoftwareConfiguration * iSoftwareConfiguration);
#endif

  virtual                  ~CATCrvVertexG2Modification();

#ifdef CATCrvVertexG2Modification_AsCGMOperator
//  CATCGMOperatorDebugDeclareRun(CATCrvVertexG2Modification,CATCGMOperator);
#else
  virtual int               Run                       ()                                                        = 0;
#endif

  virtual void              SetContinuityOnBorder     (      CATLONG32                   Start                ,
                                                             CATLONG32                   End                  ) = 0;

  virtual void              SetMovingField            (const CATMathSetOfVectors       * iMovingField         ) = 0;

};


//------------------------------------------------------------------------------------------ 
ExportedByCATGMOperatorsInterfaces
CATCrvVertexG2Modification * CATCreateCrvVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                    CATSoftwareConfiguration* iSoftwareConfiguration,
                                                                    CATNurbsCurve           * ioNurbsCurve          ,
                                                                    CATLONG32                 Start                 ,
                                                                    CATLONG32                 End                   ,
                                                              const CATMathSetOfVectors     * iMovingField          ,
                                                                    CATSkillValue             iMode                 = BASIC);
//-----------------------------------------------------------------------------
// DEPRECATED see above CATCreateCrvVertexG2Modification()
ExportedByCATGMOperatorsInterfaces
CATCrvVertexG2Modification *    CreateCrvVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                    CATNurbsCurve           * ioNurbsCurve          ,
                                                                    CATLONG32                 Start                 ,
                                                                    CATLONG32                 End                   ,
                                                              const CATMathSetOfVectors     * iMovingField          ,
                                                                    CATSkillValue             iMode                 = BASIC);


ExportedByCATGMOperatorsInterfaces
CATCrvVertexG2Modification * CATCreateCrvVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                    CATSoftwareConfiguration* iSoftwareConfiguration,
                                                                    CATPNurbs               * ioPNurbs              ,
                                                                    CATLONG32                 Start                 ,
                                                                    CATLONG32                 End                   ,
                                                              const CATMathSetOfVectors     * iMovingField          ,
                                                                    CATSkillValue             iMode                 = BASIC);

ExportedByCATGMOperatorsInterfaces
// DEPRECATED see above CATCreateCrvVertexG2Modification()
CATCrvVertexG2Modification *    CreateCrvVertexG2Modification(      CATGeoFactory           * iFactory              ,
                                                                    CATPNurbs               * ioPNurbs              ,
                                                                    CATLONG32                 Start                 ,
                                                                    CATLONG32                 End                   ,
                                                              const CATMathSetOfVectors     * iMovingField          ,
                                                                    CATSkillValue             iMode                 = BASIC);


ExportedByCATGMOperatorsInterfaces void Remove(CATCrvVertexG2Modification *&iMove);

#endif
