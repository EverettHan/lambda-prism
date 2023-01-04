/* -*-c++-*- */
#ifndef CATCGMIncrementalGlobalData_H
#define CATCGMIncrementalGlobalData_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMIncrementalGlobalData:
// Global Data necessary for the Incremental Stream/Unstream.
//
//=============================================================================
// Oct. 09 Creation                                                       VUC
//=============================================================================

#include "IUnknown.h"
#include "ExportedByCATCGMFusion.h"        
/*#include "CATMathDef.h"             
#include "CATGeoFactory.h"
#include "CATCGMContainer.h"       
#include "CATCGMBOAObject.h"
#include "CATICGMUnknown.h"
#include "CATMathInline.h"

//checkincrementalStream

class CATGeoFactoryCGM;
class CATTolerance;
class CATech_CATGeoFactoryExt;
*/


//#define ISDebugYL3

#include "CATListOfCATCGMStream.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATCGMObject.h"
#include "CATCGMContainer.h"
#include "CATListOfCATCGMObjects.h"
#include "CATCGMObjectHashTable.h"
#include "CATHashTabCATICGMObject.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMIncrementalStreamStatisticsData.h"
#include "CATMathDebug.h"

static int LimitCompactListPerfo = CATMathDebug::integerGetEnv("LimitCompactListPerfo");
static int LimitCompactToUnstream = CATMathDebug::integerGetEnv("LimitCompactToUnstream") ? 1 : 1;

class ExportedByCATCGMFusion CATCGMIncrementalStreamGlobalData
{

public :

  CATCGMIncrementalStreamGlobalData(CATGeoFactory * iFactory);

  HRESULT GetPreviousIncrementsList(CATLISTP(CATCGMStream) & oStreamList);

	INLINE CATGeoFactory * GetIncStrFactory();

	int GetNbEstimatedObjectsToSave();

  void KeepIncrement(CATCGMStream* Str);
  void CleanIncrementList();

  int GetNumberOfDeletedObjects();
	int GetNumberOfUndoLogObjects();
  int GetDeletedTag(int i);
	int GetUndoLogTag(int i);
  void AppendDeletedTag(int i); 

	// Clean the list after each increment stream
  void ResetAfterSave();
	// When change mode from incremental to full, reset all data
	void ResetAll();

	void CleanUndoLogList();
  void CleanDeletedList();
  void CleanFederatorsList();
  int GetNumberOfIncrementalSave();
  void IncrementalSaveCounterUp();
  CATBoolean HasBeenSavedIncrementally();
	void ResetSaveNumber();//to force a next full save*/

	// Statistic 
	CATCGMIncrementalStreamStatisticsData * GetIncrementalStreamStatisticsData();
	void UpdateStatisticsData();
	void SetNbObjectsInContainer(int NbObjects);
	void SetNbSavedObjectsInIncSave(int NbObjects);

  CATBoolean IsInCheckMode();
  void SetCheckMode(CATBoolean iIsinCheckMode); 

  int GetTestMode(); 

	CATBoolean IsSingleOperatorTestMode();
	CATBoolean IsMultiOperatorsTestMode();
	CATBoolean IsFeatureTestMode();
  
  virtual ~CATCGMIncrementalStreamGlobalData();

  void AppendStreamedObjectType(CATCGMObject* Object);
  CATCGMHashTable* GetStreamedObjectType();

  void AppendFederatorTag(int  tag);
  CATCGMListOfCATULONGPTR* GetFederatorTags(); //ne modifier surtout pas cette liste après l'avoir reçu

	void AppendFederatorObject(CATCGMObject * Object);
  CATLISTP(CATCGMObject)* GetFederatorObjects(); 

	void AppendUndoLogTag(int tag);
	CATCGMListOfCATULONGPTR* GetUndoLogTags();

  void AppendNewObject(CATCGMObject* Object);
  void AppendModifiedObject(CATCGMObject* Object);
  void AppendSharpnessChange(CATCGMObject* Object);
  void AppendLyingOnChange(CATCGMObject* Object);
	void AppendModifiedLinkedObjects(CATCGMObject* Object);

  void AppendAttribute(CATCGMObject* Object);
	void RemoveAttribute(CATCGMObject* Object);
	void AppendPermanentStreamObjects(CATCGMObject* Object);
	void RemovePermanentStreamObjects(CATCGMObject* Object);
  void AppendTopoNoFrozen(CATCGMObject* Object);
	void RemoveTopoNoFrozen(CATCGMObject* Object);
	
	void AppendObjectsWithLimitCompact(CATCGMObject* object, CATCGMObject* SupportObject);
	int  AddLimitCompactObjectInAssocList(CATULONG32  ObjectTag, CATULONG32  SupportObjectTag, CATULONG32  FirstBlockBeginIndex);
	void GetLimitCompactObjectInAssocList( CATULONG32  SupportObjectTag, CATLISTP(CATCGMObject) & oAssocObjects);

	int  AddObjectInIncrementalStreamList(CATCGMObject * iObject, CATCGMHashTable *& iHashTable);
	int  RemoveObjectFromIncrementalStreamList(CATCGMObject * iObject, CATCGMHashTable *& iHashTable);

	void DeleteOrRemoveAllHT(CATCGMHashTable *& iHashTable, CATBoolean iDelete);
  void RemoveFromAll(CATCGMObject* Object);

	// In CGM ODT MultiOperatorTestMode test, as there is no persistent object flaged by Generic Naming,  we stream all objects in container for comparing with stream standard.  
	CATCGMHashTable*  _NewObjects;

	// List of modified objects during two increment stream 
  CATCGMHashTable*  _ModifiedObjects;

  //CATCGMHashTable          *  _ObjectsWithSharpness;
  //CATCGMHashTable          *  _ObjectsWithLyingOn;
  CATCGMHashTable          *  _TopoObjectsNoFrozen;
	CATCGMHashTable          *  _PermanentStreamObjects;

	// Linkd object to save. Ex : LyingOn support object and SharpnessData. The stream will check if these object is in current transaction for stream. 
	// so it should stream these objects with their LyingOn or Sharpness object (Edge or Vertex) 
	CATCGMHashTable          *  _ModifiedLinkedObjects;

		// For now, we stream all objects with attributs in order to keeping the attribute updated.
  CATCGMHashTable          *  _ObjectsWithAttribute;

	// Stock the object and its support object impacted by stream LimitCompact, ex : POEC, PLine, EdgeCurve 
	// If support object is modified, then resave the object. Because if the limit of support object has been changed, the LimitCompact info should be also updated,
	// knowing that the LimitCompact is applied when object's limit is identical than that of its support.
	CATCGMHashTableWithAssoc       * _ObjectsWithLimitCompact;

	// Mapping Tag with object pointor. When removing the object, set pointor to NULL.
	CATCGMHashTableWithAssoc       * _ObjectTagsWithPointer;


private :

  //list of the catcgmstream of the temporal increments
  //those listpointers are null until used
  //needed for complete unstream
  CATLISTP(CATCGMStream)* _IncrementList;

  //buffers where the stream are 
  CATListPV* _IncrementBufferList;
  CATListOfInt* _IncrementSizeList;

  CATCGMListOfCATULONGPTR* _DeletedTags;
	CATCGMListOfCATULONGPTR* _UndoLogTags;
    
  int _NumberOfIncrementalSave;//starts at 0, the first full save counts as 1
  //-------------------------------------------------------------------------
  // Control validite de la sauvegarde  incrementale(Debug)
  //-------------------------------------------------------------------------
  CATBoolean  _CheckMode;      

  CATCGMListOfCATULONGPTR* _FederatorsTags;
	CATLISTP(CATCGMObject)*  _FederatorObjects;
	

  CATBoolean _Verbose;

	int _TestMode; //  0 : Application mode ou Feature test
	               //  1 : test incremental stream on 1 operator
	               //  2 : test incremental stream on a serie of operators


	
	CATCGMIncrementalStreamStatisticsData * _IncStatData;
	CATCGMContainer * _IncStrContainer;

struct TagListManager 
{
	CATULONG32 * List;
	CATULONG32  AvailableIndex;
	CATULONG32 NbInUnit;
	CATULONG32 NbMax;
} _AssocTagList;
};

INLINE CATGeoFactory * CATCGMIncrementalStreamGlobalData::GetIncStrFactory()
{
	return _IncStrContainer ? (CATGeoFactory *)_IncStrContainer->GetInterface() : NULL;
}

#endif 
