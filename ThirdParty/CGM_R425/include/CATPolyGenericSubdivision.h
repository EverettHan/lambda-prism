// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyGenericSubdivision.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// July 2010  Creation: ZFI
//===================================================================

#ifndef CATPolyGenericSubdivision_H
#define CATPolyGenericSubdivision_H

#include "CATRefCounted.h"
#include "CATListOfDouble.h"
#include "CATPolyDoublyLinkedList_T.h"
#include "PolyMathContainers.h"

class ExportedByPolyMathContainers CATPolyGenericSubdivision
{
public :
  CATPolyGenericSubdivision();
  virtual ~CATPolyGenericSubdivision();

  CATPolyGenericSubdivision(CATPolyGenericSubdivision& iCopy);
  CATPolyGenericSubdivision& operator=(const CATPolyGenericSubdivision &iCopy);

public:
  HRESULT SplitUniform(int iNbInnerPoints);
  HRESULT Split(int iIndex, int& oNewIndex);
  HRESULT GetParams(CATListOfDouble& ioParam)const;

public:
  inline int GetStartIndex() const; 
  inline int GetEndIndex() const ;
  inline int GetNextIndex(int iIndex) const ;
  inline int GetPrevIndex(int iIndex) const ;
  inline int Size()const;
  inline double GetParam(int iIndex) const;

public:
  HRESULT GetCompactData(unsigned char*& oBytes, unsigned int& oNbBytes)const;
  HRESULT SetFromCompactData(const unsigned char* iBytes, unsigned int iNbBytes);

public:
  static HRESULT ComputeFromCompactData(const unsigned char* iBytes, unsigned int iNbBytes, CATListOfDouble& ioParams);
  static HRESULT ComputeFromCompactData(const unsigned char* iBytes, unsigned int iNbBytes, double* iAllocatedParams, unsigned int iNbAllocatedParams);

public:
  class Specialize_CATPolyDoublyLinkedList_T(DoublyLinkedList, int);

private:
  int ComputeMiddleIndex(int iIndex1, int iIndex2)const; 
  double ComputeParam(int iIndex)const; 

private:
  DoublyLinkedList _Indices;
  int _NbArcs;
};

//inline
inline int CATPolyGenericSubdivision::GetStartIndex() const
{
  return _Indices.Begin();
}

inline int CATPolyGenericSubdivision::GetEndIndex() const 
{
  return _Indices.RBegin();
}

inline int CATPolyGenericSubdivision::GetNextIndex(int iIndex) const 
{
  return _Indices.Next(iIndex);
}

inline int CATPolyGenericSubdivision::GetPrevIndex(int iIndex) const 
{
  return _Indices.Prev(iIndex);
}


inline int CATPolyGenericSubdivision::Size()const
{
  return _Indices.Size();
}

inline double CATPolyGenericSubdivision::GetParam(int iIndex) const
{
  int encodedIndex=_Indices[iIndex];
  double w = ComputeParam(encodedIndex);
  return w;
}

#endif
