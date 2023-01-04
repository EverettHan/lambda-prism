//______________________________________________________________________
// P REISS   03/04
// CATMatrixMult.h
// multiplication de matrices: gestion de blocs en C
// *TransA = 0 ( 'NN' ) ou 1 ( 'TN' = A transpose * B )
// + 2 services de maintenance:
//   CATMatrixMenage libere la memoire dynamique
//   CATMatrixReactivate regenere l' allocation dynamique apres un
//     eventuel CATMatrixMenage

#ifndef CATMatrixMult_H
#define CATMatrixMult_H

#include "CATMathematics.h"
#include "CATArithTypes.h"

extern "C" ExportedByCATMathematics int          CATMatrixMult
  ( double *Ai, double *Bi, double *Ci, int *Dm, int *Dn, int *Dk,
    int *Lda, int *Ldb, int *Ldc, int *TransA, int *IsBetaUn );
extern "C" ExportedByCATMathematics unsigned int CATMatrixMenage ();
extern "C" ExportedByCATMathematics void         CATMatrixReactivate ();
extern "C" ExportedByCATMathematics void         CATMatrixFixAlgo
  ( int Algo );
extern "C" ExportedByCATMathematics void         CATMatrixFixAmd
  ( int Amd );
extern "C" ExportedByCATMathematics int          Cholesky
  ( int *Mt, int *Ni, int *Ns, double *Prec,
    double *An, int *Ipiv, double *Dpiv );

#ifdef _WIN64
extern "C" ExportedByCATMathematics double       CATScalProdMono
  ( double *Ai, double *Bi, silla KCnt, silla Delta );
extern "C" ExportedByCATMathematics void         CATScalProdBi64
#else
extern "C" ExportedByCATMathematics void         CATScalProdBiPr
#endif
  ( double *Am, double *Aj, double *Ak, double *Ac, int Dim );

#endif
