//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
// 
//
//
//=============================================================================
// 2008-04-01   BPG: New
// 2008-05-13   ZFI
//=============================================================================

#ifndef CATIPolyIntegerSetPartition_H
#define CATIPolyIntegerSetPartition_H

#include "PolyMathContainers.h"
#include "IUnknown.h"

class CATIPolyIntIterator;

class ExportedByPolyMathContainers CATIPolyIntegerSetPartition
{
public:
  CATIPolyIntegerSetPartition();
  virtual ~CATIPolyIntegerSetPartition();

public:
  virtual HRESULT MakeSubSet(int &oIdxSubSet)=0;
  virtual HRESULT KillSubSet(int iIdxSubSet)=0;

public:
  virtual HRESULT AddElementToSubSet(int iElement , int iIdxSubSet)=0;
  virtual HRESULT RemoveElementFromSubSet(int iElement, int iIdxSubSet)=0;

public:
  virtual HRESULT Empty()=0;
  virtual HRESULT EmptySubSet(int iIdxSubSet)=0;

public:
  virtual HRESULT GetContainingSubSet(int iElement,int &oIdxSubSet) const = 0; 
  virtual HRESULT GetSubSetElementsIterator(int iIdxSubSet, CATIPolyIntIterator*& oIter) const = 0;
  virtual HRESULT GetSubSetsIterator(CATIPolyIntIterator*& oIter) const = 0;
};

#endif
