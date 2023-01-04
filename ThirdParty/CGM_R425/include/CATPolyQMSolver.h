// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyQMSolver.h
//
//===================================================================
// January 2019  Creation JBS2
//===================================================================
#ifndef CATPolyQMSolver_H
#define CATPolyQMSolver_H

#include "PolyMathUtils.h"
#include "CATErrorDef.h"


/**
* Solver minimizing the n-dimensional quadric.
* The solver tries to find the point v minimizing the quadratic expression Q(v).
*/

class ExportedByPolyMathUtils CATPolyQMSolver
{
public:

  static CATPolyQMSolver*New(unsigned int dimension, unsigned int nbDataLayers);
  ~CATPolyQMSolver();

public:

  virtual void SetCoefficients(const double *q0, const double *q1) = 0;
  inline void SetCoefficientsSize(unsigned int dataDimension, unsigned int dataSize, unsigned int dataPosSize, unsigned int posSize, unsigned int layer, unsigned int nbCoeffs); //TODO JBS2 JUST KEEP DATA DIM IN SIGNATURE
  inline void SetCoefficientsData(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline void SetCoefficientsDataPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline void SetCoefficientsPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline unsigned int GetDataDimension(unsigned int layer) const;

  /**
  * Finds the nD-point minimizing the quadric.
  */
  virtual HRESULT Solve(double *x, double *d) const = 0;

  /**
  * Computes the quadratic expression for the input nD-point.
  */
  virtual double Multiply(const double *x) const = 0;

  virtual double MultiplyMin(const double n[3]) const = 0;//TODO JBS2 COMMENT

  virtual double Multiply(const double *x, const double n[3]) const = 0;//TODO JBS2 COMMENT

  virtual double MultiplyMin(const double *x, const double n[3], const unsigned int index) const = 0;//TODO JBS2 COMMENT

  /**
  * Compute relative residual error of Ax-b = 0 values.
  */
  virtual  double RelativeResidualError(double *x) const = 0;

protected:
  static unsigned int getSymMatrixId(unsigned int i, unsigned int j);

protected:
  CATPolyQMSolver(int nbDataLayers);

protected:
  double** _CoefD;
  double** _CoefDP;
  double** _CoefP;
  unsigned int* _DDimension;
  const int _NbDataLayers;
};

void CATPolyQMSolver::SetCoefficientsSize(unsigned int dataDimension, unsigned int dataSize, unsigned int dataPosSize, unsigned int posSize, unsigned int layer, unsigned int nbCoeffs)
{
  if (nbCoeffs > 0)
  {
    if (_CoefD && !_CoefD[layer])
    {
      _CoefD[layer] = dataSize > 0 ? new double[nbCoeffs * dataSize] : 0;
    }
    if (_CoefDP && !_CoefDP[layer])
    {
      _CoefDP[layer] = dataPosSize > 0 ? new double[nbCoeffs * dataPosSize] : 0;
    }
    if (_CoefP && !_CoefP[layer])
    {
      _CoefP[layer] = posSize > 0 ? new double[nbCoeffs * posSize] : 0;
    }
    if (_DDimension)
    {
      _DDimension[layer] = dataDimension;
    }
  }
}

void CATPolyQMSolver::SetCoefficientsData(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefD[layer][i] = q0[i] + q1[i];
  }
}

void CATPolyQMSolver::SetCoefficientsDataPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefDP[layer][i] = q0[i] + q1[i];
  }
}

void CATPolyQMSolver::SetCoefficientsPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefP[layer][i] = q0[i] + q1[i];
  }
}

unsigned int CATPolyQMSolver::GetDataDimension(unsigned int layer) const
{
  return _DDimension[layer];
}
#endif
