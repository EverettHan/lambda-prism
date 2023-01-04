
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class		  :		CATCX_SetOfAnomalyManager
//	Creation	:		18/08/2010
//
//
//	Synopsis	:	Header class of CATCX_SetOfAnomalyManager 
//							Manages Anomalies	of a factory : those loaded. 
//							Detectes and diffrentiates anomalies generated during a Topological 
//							Operation° from those belonging to the input data of the operator
//
//(°) Only topological operators that No Overload the Run() service
//
//	Authors		:  KY1
//-----------------------------------------------------------------------------
//18/08/2010 Class creation
//-----------------------------------------------------------------------------

#ifndef CATCX_SetOfAnomalyManager_H
#define CATCX_SetOfAnomalyManager_H


#include "ExportedByCATCGMFusion.h"
#include "CATCollec.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATErrorDef.h"


class CATUnicodeString;
class CATListCATUnicodeString;
class CATCX_Anomaly;
class CATCGMObject;
class CATLISTP(CATCGMObject);
class CATBody;
class CATLISTP(CATBody);
class CATLISTP(CATCX_Anomaly);
class CATCGMOperator;
class CATCX_SetOfAnomalyTracker;
class CATCGMHashTableOfAnomaly;
class CATCGMHT_StringWithListOfString;
class CATGeoFactory;

/**
* @nodoc
*/
/**
*
*/
class ExportedByCATCGMFusion CATCX_SetOfAnomalyManager 
{
public:

   //CATCGMNewClassArrayDeclare;

   /**
   * @nodoc
   */
   CATCX_SetOfAnomalyManager();

   /**
   * @nodoc
   */
   static void														SetPriorCheckHasBeenDone(CATBoolean iOption);

   /**
   * @nodoc
   */
   static CATBoolean												IsPriorCheckHasBeenDone();

   /**
   * @nodoc
   */
   static void														ReInitGlobalContext(CATCX_SetOfAnomalyManager *pioSetOfAnomalyManager);
   /**
   * @nodoc
   */
   static int														HasGlobalContextModified(CATGeoFactory  *piFactory);

   /**
   * @nodoc
   */
   static void														SetFactory(CATGeoFactory  *piFactory);

   /**
   * @nodoc
   */
   static CATGeoFactory*										GetFactory();

   /**
   * @nodoc
   */
   static void														SetImplementation(CATCX_SetOfAnomalyTracker *piSetOfAnomalyTracker);

   /**
   * @nodoc
   */
   static CATCX_SetOfAnomalyTracker *				      GetImplementation();
   /**
   * @nodoc
   */
   static void														SetInputBodies(CATLISTP(CATBody)& iListOfInputBodies);

   /**
   * @nodoc
   */
   static void														SetResultBody(CATBody * piResultBody);

   /**
   * @nodoc
   */
   static void														SetCGMOperator(CATCGMOperator *piCGMOperator,CATBoolean iRunOpCtxt=TRUE);

   /**
   * @nodoc
   */
   static HRESULT													CheckInput();

   /**
   * @nodoc
   */
   static int                                         IsCheckUpActivated();

   /**
   * @nodoc
   */
   static short													IsCheckInput();

   /**
   * @nodoc
   */
   static CATBoolean												IsCheckResultBody();

	/**
   * @nodoc
   */
   static void														EnableCheckBody(CATBoolean iOption);

	/**
   * @nodoc
   */
   static CATBoolean												IsCheckBodyEnabled();



   /**
   * @nodoc
   */
   static int														Run();

   /**
   * @nodoc
   */
   static int														RunSingle();

   /**
   * @nodoc
   */
   static int														CheckFactory(const char iName[]);

   /**
   * @nodoc
   */
   static void														Dump();

   /**
   * @nodoc
   * rc = 1 if Insertion succesful and the kind of the anomaly is Unstreamed 0 otherwise
   */
   static int														AddAnomaly(CATCX_Anomaly *piAnomaly, const CATUnicodeString& iOperatorID);

   /**
   * @nodoc
   */
   static int														Insert(CATCX_Anomaly *piAnomaly,CATBoolean &ioExistInGlobalHT);

   /**
   * @nodoc
   */
   static int														Remove(CATCX_Anomaly *piAnomaly);

   /**
   * @nodoc
   */
   static CATCX_Anomaly*										Locate(CATCX_Anomaly *piAnomaly);

   /**
   * @nodoc
   */
   static int														Find(CATCX_Anomaly *piAnomaly,CATBoolean& ioIsExistInHT);

   /**
   * @nodoc
   */
   static CATBoolean												IsInContextOfRunOperator();

   /**
   * @nodoc
   */
   static CATBoolean				                        IsInContextOfSpecificService();

   /**
   * @nodoc
   */
   static void				                              SetContextOfSpecificService(CATBoolean iContextOfSpecificService);

   /**
   * @nodoc
   */
   static CATCGMOperator *										GetCGMOperator();

   /**
   * @nodoc
   */
   static void														SetCurrentAnomaly(CATCX_Anomaly *piAnomaly);

   /**
   * @nodoc
   */
   static void														SetOperatorId(CATUnicodeString *piOperatorId);


   /**
   * @nodoc
   */
   static	void													ReportAnomaly(	CATCGMOperator *piCGMOperator,const CATUnicodeString& OperatorIDFromCheckUp,CATCX_Anomaly *piAnomaly);

   /**
   * Dtor
   */
   ~CATCX_SetOfAnomalyManager();

   /**
   * @nodoc
   */
   static void														Define();

   /**
   * @nodoc
   */
   INLINE static CATBoolean									IsActive();

   /**
   * @nodoc
   */
   //static CATBoolean                                  IsSpecificActivation();

   /**
   * @nodoc
   */
   static CATBoolean												IsInitSetOfAnomalyManager();

   /**
   * @nodoc
   */
   static CATBoolean												AtLeastOneRunOperator();

   /**
   * @nodoc
   */
   static void														SetInitSetOfAnomalyManager(CATBoolean iOption);

   /**
   * @nodoc
   */
   static void														InitHashTable();

   /**
   * @nodoc
   */
   static void														ReInitLocalContext(CATCGMOperator * pCGMOperatorContexte = 0);

   /**
   * @nodoc
   */
   static int														CleanAtExit();

   /**
   * @nodoc
   */
   static void														EnableCleanerCheck(CATBoolean iActivate);

   /**
   * @nodoc
   */
   static CATBoolean												IsCleanerCheckAsked();

   /**
   * @nodoc
   */
   static CATCGMHashTableOfAnomaly *				      GetHashTableOfAnomaly();

   /**
   * @nodoc
   */
   static	void													ReportAuthorizedFile(const char *rule,const char *offense);

   /**
   * @nodoc
   */
   static CATBoolean												IsClosedConfig();

   /**
   * @nodoc
   */
   static CATBoolean												IsAuthorizedAnomalyForOperator(const char *piOperatorId,const CATUnicodeString& piPotDeVinId);

   /**
   * @nodoc
   */
   static void                                        ReportAllAnomalies();

   /**
   * @nodoc
   */
   static CATBoolean                                  IsCheckInputOperatorsDone();

   /**
   * @nodoc
   */
   static void                                        SetCheckInputOperatorsDone(CATBoolean iIsDone);

	/**
   * @nodoc
   */
	static void														SetInternalOperation(CATBoolean iOption);
	/**
   * @nodoc
   */
	static CATBoolean												IsInternalOperation();

   //Data

   /**
   * @nodoc
   */
   static CATCX_SetOfAnomalyTracker *				      _pSetOfAnomalyTracker;

private:

   //Data
   static CATULONG32												_FactoryID;
   static CATGeoFactory  *										_Factory;
   static CATCGMHashTableOfAnomaly *					   _HashTableOfAnomalies;
   static CATBoolean												_PriorCheckHasBeenDone;

   static CATBoolean												_IsDefined;
   static CATBoolean												_IsActive;
   static CATBoolean												_InitSetOfAnomalyManager;
   static int														_NbFirstLevelRunOperator;
   static CATBoolean												_AtLeastOneRunOperator;
	static CATBoolean												_IsInternalOperation;
   static CATBoolean                                  _IsInContextOfSpecificService;

   static CATListOfCATString  								_ListOfExplicitTstFwksSupervision;
   static CATBoolean												_IsInitializedExplicitTstFwksSupervision;
	static CATBoolean												_ForceCheckBody;

   static CATCGMHT_StringWithListOfString*		      _HashTableOfAuthorizedPotDeVinForOperator;
   static CATBoolean												_IsInitializedAuthorizedPotDeVinForOperator;
   //static CATUnicodeString										_AuthorizedPotDeVinForOperatorFile;	

   static CATCX_Anomaly *                             _pCurrentAnomaly;
   static CATUnicodeString *                          _pOperatorId;

   //static CATBoolean                                  _IsSpecificActivation;

   /**
   * @nodoc
   */
   static	void													_InitListOfExplicitTstFwksSupervision();

   /**
   * @nodoc
   */
   static	void													_InitHashTableAuthorizedPotDeVinForOperator();

   /**
   * @nodoc
   */
   static CATUnicodeString                            _SpecificOperator_CATCloneManager;
   static CATUnicodeString                            _SpecificOperator_CATTransfoManager;
   static CATUnicodeString                            _SpecificOperator_TopSmartBodyDuplicator;
   static CATUnicodeString                            _SpecificOperator_CATTopFrFShellUnfold;
   static CATUnicodeString                            _SpecificOperator_DynSolidDraft;
   static CATUnicodeString                            _SpecificOperator_CATTopologicalFillBoundary;
   static CATUnicodeString                            _SpecificOperator_CATTopShellUnfoldTransferImpl;
   static CATUnicodeString                            _SpecificOperator_CATTopoVarOffsetInputBuildImp;
   static CATUnicodeString                            _SpecificOperator_CATPolygon;

   static CATUnicodeString                            _SpecificOperator_TEMPORARY_MODELISATION;
   static CATUnicodeString                            _SpecificOperator_MANUAL_CREATION;

   //----------------
   //Forbidden Ctors
   //----------------

   /**
   * @nodoc
   */
   CATCX_SetOfAnomalyManager(const CATCX_SetOfAnomalyManager& piAnomalyCheck);
   CATCX_SetOfAnomalyManager& operator=(const CATCX_SetOfAnomalyManager& piAnomalyCheck);

   /**
   * @nodoc
   */
};


INLINE CATBoolean CATCX_SetOfAnomalyManager::IsActive() 
{
   if ( ! _IsDefined ) Define();
   return _IsActive;
}


/**
* @nodoc
*/
/**
*
*/

class CATCGMHT_StringWithListOfString : public CATCGMHashTableWithAssoc
{
public:
   CATCGMNewClassArrayDeclare;

   CATCGMHT_StringWithListOfString(int iEstimatedSize = 0);
   ~CATCGMHT_StringWithListOfString();	

   INLINE	int														Insert(CATUnicodeString* ipString, CATListOfCATUnicodeString* ipAssoc);
   INLINE	int														LocateItem(CATUnicodeString* ipString, CATListOfCATUnicodeString** oppAssoc) const;
   INLINE	CATUnicodeString*							         GetItemAndAssoc(int iPos, CATListOfCATUnicodeString** oppAssoc) const;
   INLINE CATListOfCATUnicodeString*			            GetAssoc(int iPos);

protected:
   static int														   CompareFunction(void* ipString1, void* ipString2);
   static unsigned int										      HashKeyFunctionBis(void* ipString);
};

int CATCGMHT_StringWithListOfString::Insert(CATUnicodeString* ipString, CATListOfCATUnicodeString* ipAssoc)
{
   return CATCGMHashTableWithAssoc::Insert((void *)ipString,(void *)ipAssoc);
}

int CATCGMHT_StringWithListOfString::LocateItem(CATUnicodeString* ipString, CATListOfCATUnicodeString** ipAssoc) const
{
   return CATCGMHashTableWithAssoc::LocateItem((void *)ipString,(void **)ipAssoc);
}

CATUnicodeString* CATCGMHT_StringWithListOfString::GetItemAndAssoc(int iPos, CATListOfCATUnicodeString** oppAssoc) const
{
   return (CATUnicodeString *)CATCGMHashTableWithAssoc::GetItemAndAssoc(iPos,(void **)oppAssoc);
}

CATListOfCATUnicodeString* CATCGMHT_StringWithListOfString::GetAssoc(int iPos)
{
   return (CATListOfCATUnicodeString *)CATCGMHashTableWithAssoc::GetAssoc(iPos);
}

#endif

