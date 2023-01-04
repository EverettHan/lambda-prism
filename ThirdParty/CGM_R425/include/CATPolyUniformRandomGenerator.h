// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyUniformRandomGenerator.h
// Header definition of CATPolyUniformRandomGenerator
//
//===================================================================
//
// Usage notes: Base class for pseudo random generation
//
//===================================================================
//
// January 2013 Creation: JXO
// October 2013 Modif     JXO: Slight refactor
//===================================================================
#ifndef CATPolyUniformRandomGenerator_H
#define CATPolyUniformRandomGenerator_H

// ExportedBy
#include "PolyMathUtils.h"

// Math
#include "CATMathInline.h"


//#include <mutex>

class ExportedByPolyMathUtils CATPolyUniformRandomGenerator
{
public:
  /** Type of random generator */
  enum Type
  {
    undefined,
    userdefined,
    std,
    lcg,
    AdvMathematics,
    mersennetwister /** Not implemented yet */
  };
  /** Constructor */
  CATPolyUniformRandomGenerator(unsigned int seed = 0, Type iType = std);
  /** Destructor */
  virtual ~CATPolyUniformRandomGenerator();
  /** Resets with a new seed */
  virtual void Reset(unsigned int seed = 0, Type iType = undefined);
  /** Returns next pseudo random number int the range 0 to Randmax */
  virtual unsigned int Rand();
  /** Returns RAND_MAX for std, may depend on generator type */
  virtual unsigned int Randmax();
  /** Returns type of pseudo random generator */
  virtual Type GetType() const;

  /** Returns a double between 0 and 1 (both inclusive) */
  double DoubleRand();

  /**
    THIS VALUE CAN BE USED TO RENINIT THE RANDOM GENERANTOR IN SOME State
    not valid with "std"
  */
  virtual unsigned int GetCurrentStateSeed() const;

  /** For Phoenix */
  INLINE unsigned int GetSeed() const {return m_InitialSeed;}

  

protected:
  /** Returns a double between 0 and 1 (both inclusive.)
   *  Can be overloaded */
  virtual double ProtectedDoubleRand();
protected:
  CATPolyUniformRandomGenerator * m_Impl;

private:
  unsigned int m_InitialSeed;

  //mutable std::mutex mut;
};
#endif

