#ifndef CATCGMUnit_h
#define CATCGMUnit_h

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATEdge.h"
#include "CATBoolean.h"
#include  "CATICGMObject.h" 
#include "CATUnicodeString.h"
 
class CATExtCGMReplay;
class CATBody;
class CATGeoFactory;
class CATTopOperator;
class CATTopData;
class CATCGMJournalList;
class CATCGMChainLinkManager;
class CATSoftwareConfiguration;
class CATCGMStream;
class CATCGMChain;
class CATContextForFastRun;


enum  CATCGMUnitType  
{  
	CATCGMUnitDummyType,
	CATCGMUnitBooleanType,
	CATCGMUnitFilletType
};

class ExportedByCATTopologicalObjects CATCGMUnit
{
 public:

   CATCGMUnit(CATGeoFactory* f,  CATTopData * iData, CATCGMJournalList* iJournal);
   virtual ~CATCGMUnit();

   int GetId ();
   void SetId (int iIdent);

   void SetFeatureName (const char *iName);
   const char * GetFeatureName (int * pLgr);

   void               SetTopData (CATTopData * iData);
   virtual void       SetOperator (CATTopOperator * iOp);
   CATTopOperator *   GetOperator ();
   void               CloseOperator();

   CATGeoFactory  *   GetFactory ();


   virtual void Dump (CATCGMOutput & ioWhereToWrite, int Index = 0,  int iIndent = 0);
   void SetOutput ( CATBody *iBody, CATCGMJournalList* iJournal); 


   virtual HRESULT Run (CATCGMChainLinkManager *iLinks, CATBoolean WithFast=FALSE);
  // virtual HRESULT FastRun (CATCGMChainLinkManager *iLink);

   virtual CATCGMUnitType GetType();

   // Queries
   CATBody * GetOutput ();
   void GetInputBodies(CATLISTP(CATBody)& Inputs);
   CATTopOperator * GetRecordedOp ();

    /* statistics */
   int GetLastRunResult ();
   int GetLastOutputCheckResult ();
   virtual void GetLinkedGeometry (CATLISTP(CATICGMObject) & CGMLinkedObjectList);

   CATULONG32 GetCPU ();
   CATULONG32 GetElapsed ();

   void SetInactive ();
   void SetActive   ();
   CATBoolean IsActive ();
private :
    int _Active;

    
 public :

   virtual void  Stream (CATCGMStream * iStream);
   virtual void  Unstream (CATCGMStream * iStream );

   static void UnstreamHeader (CATCGMStream* iStream, CATCGMUnitType &oType,CATString &oId);

protected :
	virtual void StreamHeader (CATCGMStream* iStream );
  
 protected:
   CATGeoFactory *    _Factory;
   //CATSoftwareConfiguration * _pConfig;
   
  /* CATTopData *       _Data;
   CATCGMJournalList* _Journal;
   CATCGMJournalList* _WkJournal;*/


   /* methods to be implemented in Units if needed */
   virtual void UpdateOperatorWithNewEntry (CATBody *iOldBody, CATBody *iNewBody);
   virtual int RunOperator (CATBoolean WithFast=FALSE, CATCGMChainLinkManager *iLink=NULL);
   virtual CATBoolean ValidateOutput (CATBody *OldResult, CATBody *NewResult);
   virtual CATBoolean CheckOutput (CATExtCGMReplay * iLocalCopy=NULL);
   HRESULT InitializeFastRunContext (CATContextForFastRun*  iContextForFastRun, CATCGMChainLinkManager *iLink);

  CATBoolean GetFastRunOperator (CATTopOperator * iOp, CATCGMChainLinkManager *iLink);

   


  CATCGMJournalList  * GetJournal ();

   /* tools for units */
   CATTopOperator *DuplicateMyOperator (CATTopOperator * iOp, CATExtCGMReplay *& ioLocalExtCGMReplay);
   void    GetEdgesFromNewBody (CATBody *iOldBody, CATBody *iNewBody, 
								const CATLISTP(CATEdge)& iOldEdges, CATLISTP(CATEdge)& iNewEdges);

private :
	void AddReferenceByUnit (CATBody *iBody);
	void ReleaseReferenceByUnit (CATBody *iBody);
	void CleanLinkedGeometry ();
private :
	CATLISTP(CATICGMObject) _CGMLinkedObjectList;
protected :

	void SetLinkedGeometry (CATLISTP(CATICGMObject) &CGMLinkedObjectList);
	void AddLinkedGeometry (CATLISTP(CATICGMObject) &CGMLinkedObjectList);
	void RemoveLinkedGeometry (CATLISTP(CATICGMObject) &CGMLinkedObjectList);

private :
          void SetJournal ( CATCGMJournalList* iJournal, CATSoftwareConfiguration*  iConfig);

protected :
          CATBody *         _Result;
	CATCGMJournalList *_JResult;
          CATTopData        *_TopData;

          CATExtCGMReplay * _ExtCGMReplay; // contains a snapshot of operator


private:
	
	
	int               _Ident; //tag
	CATUnicodeString  _FeatureName;

  	CATTopOperator * _RecordedOp;

	HRESULT          _LastRun;
          HRESULT          _LastCheck;


	CATULONG32             _cpuRun;
	CATULONG32             _elapsedRun;


};

// ? utility of CATCGMJournalList* iJournal (embedded in CATTopData )
// ? utility of CATTopData (embedded by CATExtCGMReplay *)

ExportedByCATTopologicalObjects CATCGMUnit* CATCreateCGMUnit (CATGeoFactory* ifactory, CATTopOperator * iOp, CATTopData * iData, CATCGMJournalList* iJournal);

#endif
