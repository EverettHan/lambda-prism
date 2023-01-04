// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyQ3Solver.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyQ3Solver_H
#define CATPolyQ3Solver_H

#include "PolyMathUtils.h"
#include "CATErrorDef.h"


/**
 * Coefficients of the quadric matrix.
 */
class ExportedByPolyMathUtils CATPolyQ3Solver 
{

public:

  CATPolyQ3Solver(unsigned int nbDataLayers);

  ~CATPolyQ3Solver();

private:

  static const unsigned int SizeQCoef = 10;
  static const unsigned int SizeQCoefNormals = 9;
  static const unsigned int SizeQCoefNormalsPos = 9;
  static const unsigned int SizeQCoefPos = 10;
  static const unsigned int SizeQCoefTextures = 5;
  static const unsigned int SizeQCoefTexturesPos = 6;

public:

  /**
   * Given a position and a normal (defining a plane), updates the coefficients of the quadric matrix.
   * @param P
   *   The input point coordinates.
   * @param N
   *   The input normal coordinates.
   * @param qcoef
   *   The coefficients of the quadric matrix.
   */
  static void UpdateCoefficients (const double P[3], const double N[3], double qcoef[SizeQCoef]);

public:

  inline void ClearCoefficients ();
  inline void AddCoefficients (const double q[SizeQCoef]);
  inline void SetCoefficients (const double q[SizeQCoef]);
  inline void SetCoefficients (const double q0[SizeQCoef], const double q1[SizeQCoef]);

  inline void SetCoefficientsSize(unsigned int dataDimension, unsigned int dataSize, unsigned int dataPosSize, unsigned int posSize, unsigned int layer, unsigned int nbCoeffs);
  inline void SetCoefficientsData(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline void SetCoefficientsDataPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline void SetCoefficientsPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index);
  inline unsigned int GetDataDimension(unsigned int layer) const;

public:

  /**
   * Solves the system and computes the target position and optionally the 
   * target layer coordinates.
   */
  HRESULT Solve(double p[3], double* d) const;

  HRESULT SolveNormal(const double cSol[3], double n[3]) const;

  /**
   * Given the coordinates of a point, evaluates the quadric.
   */
  double Multiply (const double c[3]) const;

  double MultiplyMin(const double n[3]) const;

  double Multiply (const double c[3], const double n[3]) const;

  double MultiplyMin(const double c[3], const double n[3], const unsigned int index) const;

private:

  double _Coef[SizeQCoef];

  double **_CoefD;
  double **_CoefDP;
  double **_CoefP;
  unsigned int *_DDimension;
  const int _NbDataLayers;
};


inline void CATPolyQ3Solver::ClearCoefficients ()
{
  for (unsigned int i = 0; i < SizeQCoef; ++i)
  {
    _Coef[i] = 0;
  }
}

inline void CATPolyQ3Solver::AddCoefficients (const double q[])
{
  for (unsigned int i = 0; i < SizeQCoef; ++i)
  {
    _Coef[i] += q[i];
  }
}

inline void CATPolyQ3Solver::SetCoefficients (const double q[])
{
  for (unsigned int i = 0; i < SizeQCoef; ++i)
  {
    _Coef[i] = q[i];
  }
}

inline void CATPolyQ3Solver::SetCoefficients (const double q0 [], const double q1 [])
{
  for (unsigned int i = 0; i < SizeQCoef; ++i)
  {
    _Coef[i] = q0[i] + q1[i];
  }
}

void CATPolyQ3Solver::SetCoefficientsSize(unsigned int dataDimension, unsigned int dataSize, unsigned int dataPosSize, unsigned int posSize, unsigned int layer, unsigned int nbCoeffs)
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

inline void CATPolyQ3Solver::SetCoefficientsData (const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefD[layer][i] = q0[i] + q1[i];
  }
}

inline void CATPolyQ3Solver::SetCoefficientsDataPos (const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefDP[layer][i] = q0[i] + q1[i];
  }
}

inline void CATPolyQ3Solver::SetCoefficientsPos(const double q0[], const double q1[], unsigned int size, unsigned int layer, unsigned int index)
{
  for (unsigned int i = index * size; i < (index + 1) * size; ++i)
  {
    _CoefP[layer][i] = q0[i] + q1[i];
  }
}

inline unsigned int CATPolyQ3Solver::GetDataDimension(unsigned int layer) const
{
  return _DDimension[layer];
}

#endif
