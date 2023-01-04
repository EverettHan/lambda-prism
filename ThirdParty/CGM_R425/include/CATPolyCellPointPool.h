// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCellPointPool.h
//
//===================================================================
// April 2019  Creation NDO
//===================================================================
#ifndef CATPolyCellPointPool_H
#define CATPolyCellPointPool_H

#include "PolyLayers.h"
#include "CATErrorDef.h"
#include "CATPolyCellPoint.h"
#include "CATPolyBuckets.h"


/**
 * Pool of CATPolyCellPoint.
 * Deletion of the pool results in the deletion of all objects allocated by the pool.
 */
class ExportedByPolyLayers CATPolyCellPointPool 
{

public:

  /**
   * Constructor of a pool of CATPolyCellPoint.
   */
  CATPolyCellPointPool (unsigned int iNbEstimatedPoints = 0);

  ~CATPolyCellPointPool ();

public:

  /**
   * Creates a new CATPolyCellPoint from the pool.
   */
  CATPolyCellPoint* New ();

  /**
   * Deletes a CATPolyCellPoint from the pool.
   */
  inline void Delete (CATPolyCellPoint* P);

public:

  /**
   * Iterates through all the CATPolyCellPoint from the pool.
   */
  class ExportedByPolyLayers Iterator
  {
  public:

    inline Iterator (const CATPolyCellPointPool& iPool);
    ~Iterator () {}

  public:

    inline Iterator& Begin ();
    inline bool End () const {return _Index > _IndexMax;}
    inline Iterator& operator++ ();

    inline CATPolyCellPoint* operator* () const;

  private:

    unsigned int _Index;
    unsigned int _IndexMax;
    const CATPolyBuckets<CATPolyCellPoint>& _Pool;

  };

private:

  CATPolyBuckets<CATPolyCellPoint> _Pool;

  CATPolyCellPoint* _Recycled;

private:

  CATPolyCellPoint* Pop ();

  void Push (CATPolyCellPoint* P);

  inline static bool IsDefined (const CATPolyCellPoint* P);

};

inline void CATPolyCellPointPool::Delete (CATPolyCellPoint* P)
{
  Push (P);
}

inline bool CATPolyCellPointPool::IsDefined (const CATPolyCellPoint* P)
{
  return P && (P->GetBarycentricCoordinate (0) != 0 || P->GetBarycentricCoordinate (1) != 0 || P->GetBarycentricCoordinate (2) != 0);
}

inline CATPolyCellPointPool::Iterator::Iterator (const CATPolyCellPointPool& iPool) : 
  _Pool (iPool._Pool),
  _Index (1),
  _IndexMax (iPool._Pool.Size ())
{
}

inline CATPolyCellPointPool::Iterator& CATPolyCellPointPool::Iterator::Begin ()
{
  _Index = 1;
  while (_Index <= _IndexMax && !CATPolyCellPointPool::IsDefined (&_Pool[_Index]))
    ++_Index;
  return *this;
}

inline CATPolyCellPointPool::Iterator& CATPolyCellPointPool::Iterator::operator++ ()
{
  ++_Index; 
  while (_Index <= _IndexMax && !CATPolyCellPointPool::IsDefined (&_Pool[_Index]))
    ++_Index;
  return *this;
}

inline CATPolyCellPoint* CATPolyCellPointPool::Iterator::operator* () const
{
  return (CATPolyCellPoint*) &_Pool[_Index];
}

#endif
