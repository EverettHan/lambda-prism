/* -*-c++-*- */
#ifndef CATCGMIncrementalLocalData_H
#define CATCGMIncrementalLocalData_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMIncrementalLocalData:
// Local Data necessary for the Incremental Stream/Unstream of One increment.
//
//=============================================================================
// Oct. 09 Creation                                                       VUC
//=============================================================================

#include "ExportedByCATCGMFusion.h"        

#include "CATListOfCATCGMStream.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATCGMObject.h"
#include "CATICGMObject.h"
#include "CATListOfCATCGMObjects.h"
#include "CATCGMTagHashTableWithIndex.h"
#include "CATCGMTagHashTable.h"


class ExportedByCATCGMFusion CATCGMIncrementalStreamLocalData
{

public :

  CATCGMIncrementalStreamLocalData();
  virtual ~CATCGMIncrementalStreamLocalData();
  
  void SetDeletedList(CATULONG32* iDeletedTags,CATULONG32 iSize);
	void SetUndoLogList(CATULONG32* iUndoLogTags,CATULONG32 iSize);

  CATBoolean CreateToUnstreamList(CATCGMIncrementalStreamLocalData * LastLocalData);
  CATBoolean IsNotIn(CATULONGPTR ielement,CATCGMTagHashTable* List);
  void GetObjectsList(CATULONG32* ioObjectsTags,CATULONG32 iSize); //affects the list input with the objectstags
  
  void SetObjectsList(CATULONG32* iObjectsTags,CATULONG32 iSize);

  void SetObjectList(CATCGMListOfCATULONGPTR& List);

  CATBoolean MustUnstreamObject(CATULONG32 iTag);

  void AppendObjectTag(CATULONG32 iTag);
  void AppendStreamedObjects(CATCGMObject * iObject);
  

  CATULONG32 TotalObjectsCount();
  
  INLINE void SetNext(CATCGMStream *next);
  INLINE void SetPrevious(CATCGMStream *previous);
  INLINE CATCGMStream* GetPrevious();
  INLINE CATCGMStream* GetNext();
  
  INLINE CATCGMListOfCATULONGPTR* GetObjectsList();
  INLINE CATLISTP(CATCGMObject)* GetStreamedObjects();
  INLINE void SetListNotToUnstream(CATCGMTagHashTable* list);

	INLINE void SetDeletedTagsSinceLastInc(CATCGMTagHashTable* iDeletedTags);
	INLINE CATCGMTagHashTable* GetDeletedTagsSinceLastInc();

  INLINE void SetGlobalMapping(CATCGMTagHashTableWithIndex* map);
	INLINE void SetChronologicalMapping(CATCGMHashTableWithAssoc* map);

  INLINE CATBoolean IsLast();//returns true if this is the last stream linked
  INLINE CATBoolean IsFirst();//returns true if this is the last stream linked
  INLINE CATBoolean GetVerbose();//returns true if this is the last stream linked
  
  INLINE void SetContainerIndex(size_t iContainerIndex);
  INLINE size_t GetContainerIndex();

  INLINE void SetLastLocalData(CATCGMIncrementalStreamLocalData* iLastLocalData);
  INLINE CATCGMIncrementalStreamLocalData * GetLastLocalData();

  //valid only after selection of every object that must be streamed, and only on a stream operation
  INLINE void GetIncrementalFederatorsList(CATLISTP(CATCGMObject) &oBodies);

  //valid only after selection of every object that must be streamed, and only on a stream operation
  INLINE void AppendIncrementalFederator(CATCGMObject *iBody);
  
  //valid only after selection of every object that must be streamed, and only on a stream operation
  INLINE void AppendIncrementalFederatorsList(CATLISTP(CATCGMObject) &oBodies);

  //remove the tag of an object in the must unstream list
  int RemoveTagFromList(CATULONG32 iTag );

  void SetIndex(int indx);
  int GetDependanceLocation(CATULONG32 iTag,CATCGMStreamCGMImpl*& oStreamImpl,CATCGMStream*& oStream,CATULONG32& oIndex);

  void SetIncrementList(CATLISTP(CATCGMStream)* List);
  CATCGMStream* GetIncrement(int index,CATCGMStreamCGMImpl*& oStreamImpl);

  void AppendToLocalMapping(CATULONG32 iTag,CATULONG32 iStreamIndex);

  CATBoolean HasFederators();

  CATBoolean IsChronologicallyAlive(CATULONG32 iTag);

	int GetPreviousStreamIndexInfo(CATULONG32 iTag, CATCGMStream *& oIncrementStream, CATULONG32 & oIncrementIndex, CATULONG32 & oStreamIndex);

private :

  int _index; //index of the increment in the list/chain (starts at 1)

  //the increments are linked together chronologically
  CATCGMStream* _next;
  CATCGMStream* _previous;

  //information contained on the stream
  CATCGMListOfCATULONGPTR* _ObjectsTags;
  CATCGMListOfCATULONGPTR* _DeletedTags;
	CATCGMListOfCATULONGPTR* _UndoLogTags;

  CATLISTP(CATCGMObject)* _StreamedObjects;


  //deducted from context with other streams
  CATCGMTagHashTable* _Tags_to_unstream;

  //context of the other streams, usually null except during the creation of the to_unstream list
  CATCGMTagHashTable* _Tags_not_to_unstream;

	CATCGMTagHashTable* _DeletedTagsSinceLastInc;

  CATBoolean _Verbose; //Is display active ?

  size_t _ContainerIndex;

  CATLISTP(CATCGMObject)* _Federators;

  CATCGMTagHashTableWithIndex* _GlobalMapping;
  CATCGMTagHashTableWithIndex* _LocalMapping;

	CATCGMHashTableWithAssoc* _ChronologicalMapping;

  CATLISTP(CATCGMStream)* _IncrementList;

  CATCGMIncrementalStreamLocalData* _LastLocalData;
};

INLINE CATBoolean CATCGMIncrementalStreamLocalData::IsLast()
{ return (_next) ? FALSE : TRUE ; }

INLINE CATBoolean CATCGMIncrementalStreamLocalData::IsFirst()
{ return (_previous) ? FALSE : TRUE ; }

INLINE CATCGMStream* CATCGMIncrementalStreamLocalData::GetPrevious()
{ return (_previous) ? _previous : NULL; }

INLINE CATCGMStream* CATCGMIncrementalStreamLocalData::GetNext()
{ return (_next) ? _next : NULL; }

INLINE void CATCGMIncrementalStreamLocalData::SetNext(CATCGMStream * next)
{ _next = next;}

INLINE void CATCGMIncrementalStreamLocalData::SetPrevious(CATCGMStream * previous)
{ _previous = previous;}

INLINE void CATCGMIncrementalStreamLocalData::SetListNotToUnstream(CATCGMTagHashTable* list_not_to_unstream)
{ _Tags_not_to_unstream = list_not_to_unstream;}

INLINE void CATCGMIncrementalStreamLocalData::SetGlobalMapping(CATCGMTagHashTableWithIndex* map)
{ _GlobalMapping = map;}

INLINE void CATCGMIncrementalStreamLocalData::SetChronologicalMapping(CATCGMHashTableWithAssoc* map)
{ _ChronologicalMapping = map;}

INLINE CATLISTP(CATCGMObject)* CATCGMIncrementalStreamLocalData::GetStreamedObjects()
{ return(_StreamedObjects) ? _StreamedObjects : NULL;}

INLINE CATCGMListOfCATULONGPTR* CATCGMIncrementalStreamLocalData::GetObjectsList()
{ return(_ObjectsTags) ? _ObjectsTags : NULL;}

INLINE CATBoolean CATCGMIncrementalStreamLocalData::GetVerbose()
{ return _Verbose; }

INLINE size_t CATCGMIncrementalStreamLocalData::GetContainerIndex()
{ return _ContainerIndex ; }

INLINE void CATCGMIncrementalStreamLocalData::SetContainerIndex(size_t iContainerIndex)
{ _ContainerIndex = iContainerIndex ; }

//valid only after selection of every object that must be streamed, and only on a stream operation
INLINE void CATCGMIncrementalStreamLocalData::GetIncrementalFederatorsList(CATLISTP(CATCGMObject) &oBodies)
{
  if(_Federators)
    oBodies.Append(*_Federators);
}

//valid only after selection of every object that must be streamed, and only on a stream operation
INLINE void CATCGMIncrementalStreamLocalData::AppendIncrementalFederator(CATCGMObject *iBody)
{
  if(!_Federators)
     _Federators = new   CATLISTP(CATCGMObject)();
  if(!_Federators) CATThrowForNullPointer();
  
  _Federators->Append(iBody);
}

//valid only after selection of every object that must be streamed, and only on a stream operation
INLINE void CATCGMIncrementalStreamLocalData::AppendIncrementalFederatorsList(CATLISTP(CATCGMObject) &iBodies)
{
  if(!_Federators)
     _Federators = new   CATLISTP(CATCGMObject)();
  if(!_Federators) CATThrowForNullPointer();
  
  _Federators->Append(iBodies);
}

//valid only after selection of every object that must be streamed, and only on a stream operation
INLINE CATBoolean CATCGMIncrementalStreamLocalData::HasFederators()
{
  return (_Federators && (_Federators->Size() > 0)) ? TRUE : FALSE;
}


INLINE CATCGMTagHashTable* CATCGMIncrementalStreamLocalData::GetDeletedTagsSinceLastInc()
{
	if(!_DeletedTagsSinceLastInc)
		_DeletedTagsSinceLastInc = new CATCGMTagHashTable(&HashKeyTag,&CompareTag,32);

	return _DeletedTagsSinceLastInc;
}

INLINE void CATCGMIncrementalStreamLocalData::SetDeletedTagsSinceLastInc(CATCGMTagHashTable* iDeletedTags)
{
	_DeletedTagsSinceLastInc = iDeletedTags;
}

INLINE void CATCGMIncrementalStreamLocalData::SetLastLocalData(CATCGMIncrementalStreamLocalData* iLastLocalData)
{
  _LastLocalData = iLastLocalData;
}

INLINE CATCGMIncrementalStreamLocalData * CATCGMIncrementalStreamLocalData::GetLastLocalData()
{
  return _LastLocalData;
}


#endif 
