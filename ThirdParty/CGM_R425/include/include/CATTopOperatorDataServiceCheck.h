#ifndef CATTopOperatorDataServiceCheck_H
#define CATTopOperatorDataServiceCheck_H



//-----------------------------------------------------------------------------
// KY1 : Creation                                                   January 11
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2011
//
// USAGE :
//-------
//
// CATTopOperatorDataServiceCheck : is a tool Class that make some 
// Check Operations on some Data Validity and Generic Services 
// Consistency that come from TopOperator...
//
//-----------------------------------------------------------------------------

#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfShort.h"


class CATBody;
class CATICGMObject;
class CATCGMOperator;



/** 
* CATTopOperatorDataServiceCheck : Services Class
* CATTopOperatorDataServiceCheck : is a tool Class that make some 
* Check Operations on some Data Validity and Generic Services 
* Consistency that come from TopOperator... 
*/

/** @nodoc  */
enum CATTopSizeInputBodies
{
   CATTopSizeInputBodiesUnknown,
   CATTopSizeInputBodiesEmpty,
   CATTopSizeInputBodiesNotEmpty,
   CATTopSizeInputBodiesVariable
};

/** @nodoc  */
enum CATProtocolID_CGMOperator
{
   CATProtocolID_None,
   CATProtocolID_ALL,
   CATProtocolID_GetInputBodies,
   CATProtocolID_GetResult_1,
   CATProtocolID_GetResult_2,
   CATProtocolID_GetJournal 
};

/** @nodoc  */
enum CATProtocol_OutputStatusCompliance
{
	CATProtocol_StatusUnknown,
	CATProtocol_StatusWarning,
	CATProtocol_StatusError
};


/** @nodoc  */
class ExportedByCATTopologicalObjects CATTopOperatorDataServiceCheck
{
public:

   /** @nodoc  */
   /**
   * Check Compliance of Generic Protocols
   * @return
   <dl>
   *	  <dt><tt>TRUE</tt>		<  dd>if ...........,
   *	  <dt><tt>FALSE</tt>    <dd> otherwise
   *	  </dl>  
   */
   static CATBoolean Check_CGMProtocols(CATCGMOperator *piCGMOperator); 

   /** @nodoc  */
   /**
   * Test if the generic service GetInputBodies of CATTopOperator behaves as expected ....
   * N.B : Currently, we test only if the size of the Input Bodies is as expected
   * @return
   <dl>
   *	  <dt><tt>TRUE</tt>		<  dd>if ...........,
   *	  <dt><tt>FALSE</tt>    <dd> otherwise
   *	  </dl>  
   */
   static CATBoolean CheckValidityOfGetInputBodiesService(CATCGMOperator *piCGMOperator); 

   /** @nodoc  */
   /**
   * Test if the generic service GetResult of CATTopOperator behaves as expected ....
   * N.B : Two successive calls of GetResult, and check that the calling results are the same
   * @return
   <dl>
   *	  <dt><tt>TRUE</tt>		<  dd>if ...........,
   *	  <dt><tt>FALSE</tt>    <dd> otherwise
   *	  </dl>  
   */
   static CATBoolean CheckValidityOfGetResultService(CATCGMOperator *piCGMOperator);

   /** @nodoc  */
   /**
   * 
   *	@param
   *    piObject the Object to be Check if it has Been Removed 
   * @return
   <dl>
   *	  <dt><tt>TRUE</tt>		<  dd>if Object is still valid which means it has not been removed,
   *	  <dt><tt>FALSE</tt>    <dd> otherwise
   *	  </dl>  
   */
   static short CheckValidityOfResultBody();

   /** @nodoc  */
   static void SetOutputStatus(CATProtocol_OutputStatusCompliance iStatusOfOutput);

  /** @nodoc  */
   static CATBoolean IsErrorStatusNotification();

   /** @nodoc  */
   static void SetBodyResult(CATBody *iResultBody);


   /** @nodoc  */
   static CATBoolean IsReportingActive(CATProtocolID_CGMOperator iProtocolID = CATProtocolID_None);
   /** @nodoc  */
   static void SetReporting(CATProtocolID_CGMOperator iProtocolID, CATBoolean iEnable);

   /** @nodoc  */
   /**
   * Test if the env. var. has been activated
   *	@return
   *	  <dl>
   *	  <dt><tt>TRUE</tt>		<dd>if the env. var. is activated
   *	  <dt><tt>FALSE</tt>  <dd> otherwise
   *	  </dl> 
   */
   inline static CATBoolean IsActive();  

private:

   // Static Data Member
   static CATListOfCATString _ListOfOperatorIDWithEmptyInputBodies;
   static CATListOfCATString _ListOfOperatorIDWithOrWithoutInputBodies;
   static CATListOfCATString _ListOfOperatorIDNotPertinentGetResult;
   //
   static CATBoolean _IsInitializedWithInputBodies;
   static CATBoolean _IsInitializedWithOrWithoutInputBodies;
   static CATBoolean _IsInitializedNotPertinentGetResult;
   static CATBoolean _InitReport;
   
   static CATBoolean _IsDefined;
   static CATBoolean _IsActive;

   static void _InitListOfOperatorIDsWithEmptyInputBodies(CATListOfCATString &ioListOfOperatorID);
   static void _InitListOfOperatorIDsWithOrWithoutInputBodies(CATListOfCATString &ioListOfOperatorID);
   static void _InitListOfOperatorIDsNotPertinentGetResult(CATListOfCATString &ioListOfOperatorID);

   static short _CATTopGenericProtocolCheckReport;
   static CATProtocol_OutputStatusCompliance _OutputStatus;

   static CATBody *_ResultBody;

   static void _InitReportFile();
   static void ReportResultOfCheck(CATCGMOperator *piCGMOperator,CATListOfShort& iListOfStatusCheck);

   /**
   * Allows to check if env. var. has been tested once time
   *	@return
   *	  <dl>
   *	  <dt><tt>TRUE</tt>		<dd>if checking has been done
   *	  <dt><tt>FALSE</tt>    <dd> otherwise
   *	  </dl> 
   */
   static void Define();   


   /*
   * Ctor
   */
   CATTopOperatorDataServiceCheck(CATCGMOperator *piCGMOperator);
   /*
   * Dtor
   */
   ~CATTopOperatorDataServiceCheck();
   /**
   * copy ctor
   */
   CATTopOperatorDataServiceCheck(const CATTopOperatorDataServiceCheck&  iCGMOperatorDataServiceCheck);
   /**
   * operator =
   */
   CATTopOperatorDataServiceCheck& operator = (const CATTopOperatorDataServiceCheck&  iCGMOperatorDataServiceCheck);   
};

inline CATBoolean CATTopOperatorDataServiceCheck::IsActive() 
{
  if ( ! _IsDefined ) Define();
  return _IsActive;
}

#endif
