//__________________________________________________________________________
// P REISS   01/11
// CATLinearSolve.h
// resolution de systeme lineaire

#ifndef CATLinearSolve_H
#define CATLinearSolve_H

#include "CATMathematics.h"
#include "CATArithTypes.h"

extern "C" ExportedByCATMathematics int CATLinearSolve
  ( double *A, double *B, double Prec, int Cnt, int SecondCnt, int Lda );
extern "C" ExportedByCATMathematics int CATLinearSolveC
  ( double *A, double *B, double Prec, int Cnt, int SecondCnt, int Lda );

extern "C" ExportedByCATMathematics int  CATLinearInitForAsm  ( int IsMT );
extern "C" ExportedByCATMathematics void CATLinearCloseForAsm ();
extern "C" ExportedByCATMathematics int  CATAwakeCores        ();
extern "C" ExportedByCATMathematics void CATAsleepCores       ();
extern "C" ExportedByCATMathematics void CATAvxTransition     ();
extern "C" ExportedByCATMathematics void CATChipWarmUp        ();

extern "C" ExportedByCATMathematics void CATTransposeTriangle
  ( double *A, int Cnt, int Lda );
extern "C" ExportedByCATMathematics void CATTransposeTriangC
  ( double *A, int Cnt, int Lda );

extern "C" ExportedByCATMathematics void CATNegateMatrix
  ( double *A, int Dk, int Dm, int Lda, int TransA );
extern "C" ExportedByCATMathematics void CATNegateMatrixC
  ( double *A, int Dk, int Dm, int Lda, int TransA );

extern "C" ExportedByCATMathematics double* CATAlignMatrix
  ( double *A, double* &Alo, int &SizeAlloc, int Dm, int Dk, int Lda );
extern "C" ExportedByCATMathematics double* CATAlignSqVector
  ( double *A, double *B, double* &Alo, double* &Bli, int &SizeAlloc,
    int Cnt, int SecondCnt, int Lda );
extern "C" ExportedByCATMathematics void CATBackFromAlign
  ( double *A, double *Ali, int Dm, int Dk, int Lda );
//__________________________________________________________________________
// services non exportes

extern "C" int CATLinearCombineMTRun
  ( double *R, int Rem, int Lda, int ActualLog );

extern "C" int CATLinearSolveSSE2
  ( double *A, double *B, double Prec, int Cnt, int Lda,
    int Tdx, int MaxThreads, void* MultiThread );
extern "C" int CATLinearSolveA02
  ( double *A, double *B, double Prec, int Cnt, int Lda,
    int Tdx, int MaxThreads, double *ForAlign, void *MultiThread );

extern "C" void CATAlignMatrixInC
  ( double *A, double* Ali, int Dm, int Dk, int Lda );
extern "C" void CATAlignSquareVectorInC
  ( double *A, double *B, double* Ali, double* &Bli, int Cnt, int SecondCnt,
    int Lda );
extern "C" void CATBackFromAlignInC
  ( double *A, double *Ali, int Dm, int Dk, int Lda );

extern "C" void CATAvxSave    ( double *Area );
extern "C" void CATAvxRestore ( double *Area );
extern "C" void CATAlignMatrixAvx
  ( double *A, double* Ali, int Dm, int Dk, int Lda, double *ForAlign );
extern "C" void CATAlignSqVectorAvx
  ( double *A, double *B, double* Ali, double* &Bli,
    int Cnt, int SecondCnt, int Lda, double *ForAlign );
extern "C" void CATBackFromAlignAvx
  ( double *A, double *Ali, int Dm, int Dk, int Lda, double *ForAlign );
#endif
//__________________________________________________________________________
