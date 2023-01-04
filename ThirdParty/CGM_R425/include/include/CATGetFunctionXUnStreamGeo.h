/* -*-c++-*- */
#ifndef CATGetFunctionXUnStreamGeo_h
#define CATGetFunctionXUnStreamGeo_h

// COPYRIGHT DASSAULT SYSTEMES 1999
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
//-------------------------------------------------------------------------------------------------------------------------------
#include "CATIACGMLevel.h"

#include "CATMathStrFunctionType.h"
#include "Y3DYNOPE.h"

#if defined ( CATIACGMR216CAA )
class CATTolerance;
#endif 
extern "C"
{
  ExportedByY3DYNOPE  CATFunctionXUnStream* CATGetFunctionXUnStreamGeo(const short iType) ;
 
#if defined ( CATIACGMR216CAA )
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_EquationProjectionPtCrv(CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] );
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_EquationDistancePtCrv(CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] );
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_FunctionInitProjIsopar(CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] );
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_POffsetEquationUVX(CATMathStream& Str, const CATTolerance &iTolObject, const char iLabelReserved[] );
#else
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_EquationProjectionPtCrv(CATMathStream& Str, const char iLabelReserved[]);
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_EquationDistancePtCrv(CATMathStream& Str, const char iLabelReserved[]);
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_FunctionInitProjIsopar(CATMathStream& Str, const char iLabelReserved[]);
  ExportedByY3DYNOPE CATMathFunctionX* CATFunctionXUnStream_POffsetEquationUVX(CATMathStream& Str, const char iLabelReserved[]);
#endif
};

 
#endif
