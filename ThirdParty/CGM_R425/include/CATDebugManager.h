// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATDebugManager: 
//  
//  Usefull services to debug a CGM operator
//  
//
//
//=============================================================================
//
//  !!!!!!!!!!!!!!!!!!!!!!!!!  WARNING  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  !PLEASE DO NOT USE FOR THE MOMENT UNDER DEVELOPPEMENT !!!!!!!!!!!!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
//
//=============================================================================
//  April 2017  Creation                                                 U29
//=============================================================================

#ifndef CATDebugManager_H
#define CATDebugManager_H

#undef CATDebugManager_ON
//#define CATDebugManager_ON

#ifdef CATDebugManager_ON

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "TopoDebugTools.h"
#include "ListPOfListPOfCATBody.h"


class CATSubdOccurence;
class CATCGMHashTableWithAssoc;
class CATCell;
class CATBody;
class CATListPtrCATBody;
class CATCGMJournalList;
class CATListPtrCATCGMJournal;
class CATUnicodeString;
class CATListPtrCATICGMObject;
class CATSubdArrayOccurenceP;
class CATCGMHashTableWithAssoc;
class CATAdaptiveHashTable;
class CATListPtrCATTopology;
class CATTopology;
class CATICGMObject;
class CellHashTableAssocList;

class ExportedByCATTopologicalObjects CATDebugManager
{
  //**********************************
  //   Internal Data
  //**********************************
private:

  static CATListPtrCATICGMObject   * _pData;
  static CATSubdArrayOccurenceP *  _pSubdData;
  static int _Counter;
  static CATCGMHashTableWithAssoc*  _pHT_DataToName; //Association ICGM ou Subd avec CATUnicodeString
  static CATAdaptiveHashTable*      _pHT_InputsToIgnore;

public:
  //**********************************
  //   Methods
  //**********************************

  static void Trace(const CATUnicodeString& iText);
  static void Trace2(const CATUnicodeString& iText, CATCGMOutput& ioStream);

  static void Clean();
  static void Reset();
  static void Save(const CATUnicodeString& iOperatorName);

  static CATBoolean IsInputToIgnore(CATBody* ipBody);
  static void       AddInputToIgnore(CATBody * ipBody);

  //Journal
  static void DumpJournal_Tass(const CATUnicodeString& iText, CATCGMJournal * ipJournal, int iIndent = 0);
  static void DumpJournal_Tass(const CATUnicodeString& iText, CATListPtrCATCGMJournal * ipJournals, int iIndent = 0);

  static void DumpJournal_NoTass(const CATUnicodeString& iText, CATCGMJournal * ipJournal, int iIndent = 0);
  static void DumpJournal_NoTass(const CATUnicodeString& iText, CATListPtrCATCGMJournal * ipJournals, int iIndent = 0);

  //HashTables
  static void DumpHT_AssocList_Topo(const CATUnicodeString& iText, HashTableAssocList* ipHT);
  static void DumpHT_Adaptive_Topo(const CATUnicodeString& iText, CATAdaptiveHashTable* ipHT);

  //TOPO
  static void Dump(const CATUnicodeString& iName, CATICGMObject* ipCGMObj);
  static void Dump(const CATUnicodeString& iName, CATCGMObject* ipCGMObj);

  static void Add(const CATUnicodeString& iName, CATSubdOccurence* ipOcc, int iIndex = -1);
  static void Add(const CATUnicodeString& iName, CATTopology* ipTopology, int iIndex = -1);
  static void Add(const CATUnicodeString& iName, CATListPtrCATBody& iBodies, int iIndex = -1);
  static void Add(const CATUnicodeString& iName, ListPOfListPOfCATBody& iListOfBodies, int iIndex = -1);
  static void Add(const CATUnicodeString& iName, CATListPtrCATTopology& iTopologies, int iIndex = -1);

};

#define  DbgManager_Trace(iText)                                  CATDebugManager::Trace(iText)
#define  DbgManager_Trace2(iText,iStream)                         CATDebugManager::Trace2(iText,iStream)
#define  DbgManager_Clean()                                       CATDebugManager::Clean()
#define  DbgManager_Reset()                                       CATDebugManager::Reset()
#define  DbgManager_IsInputToIgnore(ipBody)                       FALSE
#define  DbgManager_DumpJournal_Tass(iText,ipJournal,indent)      CATDebugManager::DumpJournal_Tass(iText,ipJournal,indent)
#define  DbgManager_DumpJournal_NoTass(iText,ipJournal,indent)    CATDebugManager::DumpJournal_NoTass(iText,ipJournal,indent)
#define  DbgManager_Add(iName,iObj,iIndex)                        CATDebugManager::Add(iName,iObj,iIndex)
#define  DbgManager_IsActive(...)                                 TRUE
#define  DbgManager_Dump(iName,iObj)                              CATDebugManager::Dump(iName,iObj)
#define  DbgManager_GetTypeAndTag(ICGMOBject)                     MacroDump(ICGMOBject)
#define  DbgManager_Save(iOperatorName)                           CATDebugManager::Save(iOperatorName)
#define  DbgManager_DumpHT_AssocList_Topo(iText,iHT)              CATDebugManager::DumpHT_AssocList_Topo(iText,iHT)
#define  DbgManager_DumpHT_Adaptive_Topo(iText,iHT)               CATDebugManager::DumpHT_Adaptive_Topo(iText,iHT)

#else

#define  DbgManager_Trace(...)
#define  DbgManager_Trace_Status(...)
#define  DbgManager_Clean(...)
#define  DbgManager_Reset(...)
#define  DbgManager_Save(...)
#define  DbgManager_IsInputToIgnore(...) FALSE
#define  DbgManager_AddInputToIgnore(...)
#define  DbgManager_DumpJournal_Tass(...)
#define  DbgManager_DumpJournal_NoTass(...)
#define  DbgManager_Add(...)
#define  DbgManager_GetTypeAndTag(...)
#define  DbgManager_IsActive(...) FALSE
#define  DbgManager_Dump(...)
#define  DbgManager_DumpHT_AssocList_Topo(...)
#define  DbgManager_DumpHT_Adaptive_Topo(...)

#endif

#endif //CATDebugManager_H
