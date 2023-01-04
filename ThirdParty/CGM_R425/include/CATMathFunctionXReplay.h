#ifndef CATMathFunctionXReplay_H
#define CATMathFunctionXReplay_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
//
// Chargement des CGMReplays associes a CATMathFunctionX
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// 23/07/09 NLD Creation
//              CATMathLoadFunctionXSolve,
//              CATMathLoadFunctionXSolveNewton,
//              CATMathLoadFunctionXMinimize
// 30/07/09 NLD Ajout
//              CATMathLoadFunctionXSolveDebug,
//              CATMathLoadFunctionXSolveNewtonDebug,
//              CATMathLoadFunctionXMinimizeDebug
// 06/08/09 NLD Ajout
//              CATMathLoadFunctionXOperator,
//              CATMathLoadFunctionXOperatorDebug
//=============================================================================

#include <YN000FUN.h>
#include <CATMathStream.h>
class CATCGMOperator;

/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXSolve(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream) ;
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXSolveDebug(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream) ;

/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXSolveNewton(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXSolveNewtonDebug(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);

/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXMinimize(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXMinimizeDebug(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);

/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXOperator(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN CATCGMOperator * CATMathLoadFunctionXOperatorDebug(CATMathStream &Str,const short LevelOfRuntime, const short VersionOfStream);

#endif
