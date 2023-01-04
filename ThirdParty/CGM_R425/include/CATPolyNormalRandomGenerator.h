// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyNormalRandomGenerator.h
// Header definition of CATPolyNormalRandomGenerator
//
//===================================================================
//
// Usage notes: Base class for the normal or Laplace-Gauss law pseudo
// random generator
//
//===================================================================
//
// February 2013 Creation: XXC
// October  2013 Modif     JXO: Refactor
//===================================================================
#ifndef CATPolyNormalRandomGenerator_H
#define CATPolyNormalRandomGenerator_H

// ExportedBy
#include "PolyMathUtils.h"
#include "CATPolyUniformRandomGenerator.h"
#include "CATBoolean.h"

class ExportedByPolyMathUtils CATPolyNormalRandomGenerator
{
public:
  /** Type of normal generator */
  enum Type
  {
    BoxMuller,
    PolarBoxMuller,
    Quotients
  };
  /** Constructor */
  CATPolyNormalRandomGenerator(double mean, double variance, CATPolyUniformRandomGenerator & iUniformGenerator, CATPolyNormalRandomGenerator::Type iNormalType = BoxMuller);
  /** Destructor */
  virtual ~CATPolyNormalRandomGenerator();
  /** Resets with a new seed */
  virtual void Reset(unsigned int seed = 0);
  /** Returns next pseudo random number int the range 0 to Randmax */
  virtual double Rand();
  /** Returns type of pseudo random generator */
  virtual Type GetType();

protected:
  double _Mean;
  double _Variance;

  Type _Algorithm;

  CATPolyUniformRandomGenerator & m_Impl;

  CATBoolean _Switch;
  double _SwitchValue;
};
#endif
