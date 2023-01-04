//___________________________________________________________________________
// P REISS   03/07
// CATBaseComputation.h
// objet abstrait sont derivent tous les contextes d' algos multithreades
// par STOB

#include "CATArithTypes.h"

#ifndef CATBaseComputation_h
#define CATBaseComputation_h

class CATBaseComputation
  {
  public:
     CATBaseComputation () {}
    ~CATBaseComputation () {}
  };

typedef void (CATBaseComputation::*CATThreadRun)   ( silla, silla, silla );
typedef void (CATBaseComputation::*CATThreadAstob) ( silla );
typedef void (CATBaseComputation::*CATBaseService) ( void* );
#endif                                        // CATBaseComputation_h
//*** Doc d' implementation:
// 1 _ type CATThreadRun defini ici:
//   typedef void (CATBaseComputation::*CATThreadRun) ( silla, silla, silla );
//
// 2 _ objet unique _StobAlgo cree dans CATMathPoolThread.cpp,
//     a declarer et a definir dans l' appli:
//     ( ici, InM est une methode void ( silla, silla, silla ) de la classe
//       MatrixMult, qui rassemble toutes les variables 'shared' au sens
//       OpenMP, c.a.d. toutes les infos passees aux iters multithreadees )
//   SetStobAlgo ( ..., (CATThreadRun) &MatrixMult::InM );
//
// 3 _ execution du STOB dans le main CATMathThreadStart du thread:
//     ( ici, Tid=1, Debut=20, Fin=40 )
//   (TheThreadPool->_Contexte->*((CATThreadRun)(TheThreadPool->_StobAlgo)))
//     ( 1, 20, 40 );
//___________________________________________________________________________
