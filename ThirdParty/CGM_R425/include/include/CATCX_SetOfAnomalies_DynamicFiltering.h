#ifndef CATCX_SetOfAnomalies_DynamicFiltering_H
#define	CATCX_SetOfAnomalies_DynamicFiltering_H

// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATCX_SetOfAnomalies_DynamicFiltering
//---------------------------------------------------------------------------  
//
//  
//
//
//
//
//===========================================================================   

#include "ExportedByCATCGMFusion.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATCGMHashTableWithAssoc.h"

class CATCGMOperator;
class CATCX_Anomaly;
//class CATCGMHashTableWithAssoc;
//class CATUnicodeString;
class CATCX_OpIDAndParamID;
class CATCX_OpIDAndParamID;
class CATCX_AuthorizedAnomaliesForCGMOperator;
class CATCGMHT_OpIDAndParamIDWithListOfAnomalyID;


/** @nodoc @nocgmitf */
/**
* 
*
**/
class ExportedByCATCGMFusion CATCX_SetOfAnomalies_DynamicFiltering
{
public :
	
	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   static CATCX_SetOfAnomalies_DynamicFiltering *CATCreate_SetOfAnomalies_DynamicFiltering(CATCGMOperator *piCGMOperator);

   /** @nodoc @nocgmitf */
	virtual ~CATCX_SetOfAnomalies_DynamicFiltering();
   /** @nodoc @nocgmitf */
   static void Init();

   /** @nodoc @nocgmitf */
   static void Clear();

	/** @nodoc @nocgmitf */
	CATBoolean IsDynamicFilteringAuthorized(CATCX_Anomaly *piCX_Anomaly);
	
private:	
   /** @nodoc @nocgmitf */
   CATCX_SetOfAnomalies_DynamicFiltering(CATCGMOperator *piCGMOperator);
   
   /** @nodoc @nocgmitf */
	CATCX_SetOfAnomalies_DynamicFiltering();
	/** @nodoc @nocgmitf */
	CATCX_SetOfAnomalies_DynamicFiltering(const CATCX_SetOfAnomalies_DynamicFiltering& iSetOfAnomalies_DynamicFiltering);
	/** @nodoc @nocgmitf */
	CATCX_SetOfAnomalies_DynamicFiltering& operator =(const CATCX_SetOfAnomalies_DynamicFiltering& iSetOfAnomalies_DynamicFiltering);   
   
   /** @nodoc @nocgmitf */
   static void InitHashTabOfDynAuthAnomaliesForCGMOperators();

   /** @nodoc @nocgmitf */
   static void AddGenericParametersForDynFilteringOfAnomalies(CATUnicodeString &iOperatorID,CATCX_AuthorizedAnomaliesForCGMOperator *piAuthorizedAnomaliesForCGMOperator);

	// Data
   CATCGMOperator *_pCGMOperator;
   CATCX_AuthorizedAnomaliesForCGMOperator *_pAuthorizedAnomaliesForCGMOperator;

   static CATBoolean _IsInit;
	static CATCGMHT_OpIDAndParamIDWithListOfAnomalyID *_HashTabOfDynAuthAnomaliesForCGMOperator;	
   //static CATUnicodeString _DynAuthorizedAnomalieForCGMOperatorFile;
};


class CATCX_OpIDAndParamID
{
public :
   CATCGMNewClassArrayDeclare;

   CATCX_OpIDAndParamID(CATUnicodeString &OperatorID,CATUnicodeString& ParamID);
   virtual ~CATCX_OpIDAndParamID();

   unsigned int ComputeHashKey();
   int IsEqual(CATCX_OpIDAndParamID& OpIDAndParamID);

   CATUnicodeString _OperatorID;
   CATUnicodeString _ParamID;
private:
   CATCX_OpIDAndParamID();
   CATCX_OpIDAndParamID(const CATCX_OpIDAndParamID &OpIDAndParamID);
   CATCX_OpIDAndParamID& operator = (const CATCX_OpIDAndParamID &OpIDAndParamID);
};

class CATCGMHT_OpIDAndParamIDWithListOfAnomalyID : public CATCGMHashTableWithAssoc
{
public:
   CATCGMNewClassArrayDeclare;

   CATCGMHT_OpIDAndParamIDWithListOfAnomalyID(int iEstimatedSize = 0);
   ~CATCGMHT_OpIDAndParamIDWithListOfAnomalyID();	

   INLINE	int														Insert(CATCX_OpIDAndParamID* ipOpIDAndParamID, CATListOfCATUnicodeString* ipListOfAuthAnomalies);
   INLINE	int														LocateItem(CATCX_OpIDAndParamID* ipOpIDAndParamID, CATListOfCATUnicodeString** opListOfAuthAnomalies) const;
   INLINE	CATCX_OpIDAndParamID*					         GetItemAndAssoc(int iPos, CATListOfCATUnicodeString** opListOfAuthAnomalies) const;
   INLINE   CATListOfCATUnicodeString*			            GetAssoc(int iPos);

   int     LocateOperatorID(CATUnicodeString &iOperatorID);
   void    GetListOfAuhtorizedAnomalies(CATUnicodeString &iOperatorID,CATUnicodeString &iParamID,CATListOfCATUnicodeString& ioListListOfAuthAnomaliesID);

protected:
   static int														   CompareFunction(void* ipString1, void* ipString2);
   static unsigned int										      HashKeyFunctionBis(void* ipString);
};

int CATCGMHT_OpIDAndParamIDWithListOfAnomalyID::Insert(CATCX_OpIDAndParamID* ipOpIDAndParamID, CATListOfCATUnicodeString* ipListOfAuthAnomalies)
{
   return CATCGMHashTableWithAssoc::Insert((void *)ipOpIDAndParamID,(void *)ipListOfAuthAnomalies);
}

int CATCGMHT_OpIDAndParamIDWithListOfAnomalyID::LocateItem(CATCX_OpIDAndParamID* ipOpIDAndParamID, CATListOfCATUnicodeString** opListOfAuthAnomalies) const
{
   return CATCGMHashTableWithAssoc::LocateItem((void *)ipOpIDAndParamID,(void **)opListOfAuthAnomalies);
}

CATCX_OpIDAndParamID* CATCGMHT_OpIDAndParamIDWithListOfAnomalyID::GetItemAndAssoc(int iPos, CATListOfCATUnicodeString** opListOfAuthAnomalies) const
{
   return (CATCX_OpIDAndParamID *)CATCGMHashTableWithAssoc::GetItemAndAssoc(iPos,(void **)opListOfAuthAnomalies);
}

CATListOfCATUnicodeString* CATCGMHT_OpIDAndParamIDWithListOfAnomalyID::GetAssoc(int iPos)
{
   return (CATListOfCATUnicodeString *)CATCGMHashTableWithAssoc::GetAssoc(iPos);
}

#endif
