/* -*-C++-*- */
#ifndef CATMathJacobiPolynomialXWeights_H
#define CATMathJacobiPolynomialXWeights_H

// COPYRIGHT DASSAULT SYSTEMES 1998

//-----------------------------------------------------------------------------
//
// CATMathJacobiPolynomialXWeights
// ------------------
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------
// Apr. 2011 : FDS , dllsize , factorization of coefficient used by "GeometricOperators" and "SurfacicMathematics" ( save 130 Ko )
//----------------------------------------------------------------------------------------------------------------------------------

#include "YN000FUN.h"

class ExportedByYN000FUN CATMathJacobiPolynomialXWeights
{
public:

  static double const * GetTransMatrix(const int iNivConstr);

  static double const * GetWeightsDB (const int iNivConstr);

  static double const * GetWeightsDB0 (const int iNivConstr);

  static double const * GetMaxValuesDB (const int iNivConstr);

};

#endif
