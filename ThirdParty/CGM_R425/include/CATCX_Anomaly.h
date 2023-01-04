//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class		  :		CATCX_Anomaly
//	Creation	:		18/08/2010
//
//
//	Synopsis	:	Header class of CATCX_Anomaly 
//					    Describes an Anomaly detected With CheckUp Tool
//                       - _MasterObject				:		generally it represents the Object under 
//																									which the Anomaly is observed. 
//																									Exple : a Geometry.Gap anomaly consists of a MacrtoPoint 
//																													under which the distance between 2 POECs is 
//																													greater than a given tolerance.
//																													The Master object is represented by the MacrtoPoint//													
//											 - _ListOfCATCGMObject	: list of objects involved in the Anomaly. They are generally located
//																								under the Master Object in terms of links			
//		
//                       - _AnomalyID						: the Anoamly ID
//	Authors		:  KY1
//-----------------------------------------------------------------------------
//18/08/2010 Class creation
//-----------------------------------------------------------------------------

#ifndef CATCX_AnomalyObject_H
#define CATCX_AnomalyObject_H


#include "ExportedByCATCGMFusion.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATCGMNewArray.h"
#include  "CATListOfCATCGMObjects.h"
#include  "CATCGMHashTable.h"
#include  "CATUnicodeString.h"
#include  "CATMathInline.h"
#include  "CATListOfCATUnicodeString.h"


class CATCGMObject;

/**
* @nodoc
*/
enum CATCX_Anomaly_Type 
{ 
	CATCX_Anomaly_Unknown							=		0, //Default value
	CATCX_Anomaly_Unstreamed						=		1, //Unstreamed Anomaly
	CATCX_Anomaly_TopOpID_Open						=		2, //Anomaly has been created by 1st level a Top. Op that no overload Run
   CATCX_Anomaly_TopOpID_Closed					=	   3, //Anomaly has been created by 1st level a Top. Op that no overload Run
   CATCX_Anomaly_FromInput 						=		4, //Anomaly generated during the RunOperator but has a link with an Anomaly belonging to an input data of the operator
   CATCX_Anomaly_InternOp							=		5, 
   CATCX_Anomaly_FromUnstreamed					=	   6, 
   CATCX_Anomaly_FromCloned						=     7,
   CATCX_Anomaly_TopOpID_OpenAuth				=     8,
	CATCX_Anomaly_UnDefined 						=		9,  //Not Unstreamed neither created by 1st level a Top Operator which no overloasd Run()
	CATCX_Anomaly_ManualCreation					=		10,
	CATCX_Anomaly_OLK									=		11,
	CATCX_Anomaly_TopOpID_NotPertinent			=		12
};

/**
* @nodoc
*/
enum /*ExportedByCATCGMFusion*/ CATCX_Anomaly_Feature 
{ 
	CATCX_Anomaly_Neutral_Feature						=       0x00000000, //Default value
   CATCX_Anomaly_MasterObject_Loaded				=       0x00000001, //Master Object has been loaded
	CATCX_Anomaly_AllSubObject_Loaded				=		   0x00000010, //All Sub Objects have been loaded
	CATCX_Anomaly_MasterObject_Topology				=		   0x00000100, //Master Object is a topology
   CATCX_Anomaly_AllSubObject_Topology				=		   0x00001000, //All Sub Objects are a topology   
	CATCX_Anomaly_MasterObject_NulUseCount			=		   0x00010000, //Master Object with  Nul Use Count   
};

/**
* @nodoc
*/
/**
*
*/
class ExportedByCATCGMFusion CATCX_Anomaly
{
public:

   CATCGMNewClassArrayDeclare;

   /**
   * @nodoc
   */
   static CATCX_Anomaly *CreateAnomaly(const char *iAnomalyID1,const char *iAnomalyID2,CATCGMObject *piMasterObject,CATCGMObject* const * piTabOfCGMObj, 
      int iSizeTab,CATListOfCATUnicodeString& iListOfStringValues,CATCX_Anomaly_Type iAnomalyType=CATCX_Anomaly_Unknown);
   static CATCX_Anomaly *CreateAnomaly();

   /**
   * @nodoc
   */
   void									SetAnomalyID(const char *iAnomalyID);

   /**
   * @nodoc
   */
   void									SetMasterObject(CATCGMObject* piCGMObject);

   /**
   * @nodoc
   */
   void									SetListOfObjects(CATLISTP(CATCGMObject)& iListOfObjects);

   /**
   * @nodoc
   */
   void                          SetListOfValues(CATListOfCATUnicodeString& iListOfStringValues);

	 /**
	 * @nodoc
	 */
	 void									SetAnomalyType(CATCX_Anomaly_Type iAnomalyType);

   /**
   * @nodoc
   */
   CATUnicodeString&			      GetAnomalyID();

   /**
   * @nodoc
   */
   CATCGMObject *				      GetMasterObject();

   /**
   * @nodoc
   */
   CATCX_Anomaly_Type				GetAnomalyType();


   /**
   * @nodoc
   */
   void									GetListOfObjects(CATLISTP(CATCGMObject)& ioListOfObjects);

   /**
   * @nodoc
   */
   CATListOfCATUnicodeString&    GetListOfValues();

   /**
   * @nodoc
   * Check if Master Objects removed 
   * if iOption=TRUE then Check also that all sub objects have been removed
   */
   CATBoolean IsRemoved(CATBoolean iOption = FALSE);

   /**
   * @nodoc
   */
   void									Dump();

   /**
   * @nodoc
   */
   int									IsEqual(CATCX_Anomaly& iAnomalyCheck);

   /**
   * @nodoc
   */
   int									PartiallyEqualTo(CATCX_Anomaly& iAnomaly, short iMode = 0);
   
   /**
   * @nodoc
   */
   int									WeaklyEqualTo(CATCX_Anomaly& iAnomaly);

   /**
   * @nodoc
   */
   int IsEqualWithInclusion(CATCX_Anomaly& iAnomalyCheck);

   /**
   * @nodoc
   */
   CATULONG32						   HashKey();

   /**
   * @nodoc
   */
   static CATCX_Anomaly_Feature  GetFeaturesOfAnomaly(CATCX_Anomaly *piAnomaly,CATCX_Anomaly_Feature& iRequestedAnomaly_Feature);

   /**
   * @nodoc
   */
   static short		         HasBeenLoaded(CATCX_Anomaly *piAnomaly);

	 /** LifeCycle protection  */
	 /**
	 * @nodoc
	 */
	 INLINE unsigned short        AddRef();

	 /**
	 * @nodoc
	 */
	 INLINE unsigned short        Release();



private:

   //Data
   CATCGMObject *						_MasterObject; 
   CATLISTP(CATCGMObject)		   _ListOfCATCGMObject;
   CATUnicodeString					_AnomalyID;
   CATCX_Anomaly_Type				_AnomalyType;
   CATListOfCATUnicodeString     _ListOfStringValues;
	 /** LifeCycle */
	 unsigned int                 _Counter;

   //----------------
   //Forbidden Ctors
   //----------------

    /**
   * @nodoc
   */
   /**
   * Ctor by parameters
   */
   CATCX_Anomaly(	const char *iAnomalyID1,const char *iAnomalyID2,CATCGMObject *piMasterObject,CATCGMObject* const * piTabOfCGMObj, 
									int iSizeTab,CATListOfCATUnicodeString& iListOfStringValues,CATCX_Anomaly_Type iAnomalyType=CATCX_Anomaly_Unknown);

	 /**
	 * @nodoc
	 */
	 /**
	 * Ctor by Copy
	 */
	 CATCX_Anomaly(const CATCX_Anomaly& iAnomaly);

   /**
   * Default Ctor
   */
   CATCX_Anomaly();

   /**
   * Dtor
   */
   ~CATCX_Anomaly();

   /**
   * @nodoc
   */
   //CATCX_Anomaly(const CATCX_Anomaly& iAnomaly);
   CATCX_Anomaly& operator=(const CATCX_Anomaly& piAnomaly);

   /**
   * @nodoc
   */
};

/**
* @nodoc
*/
class  ExportedByCATCGMFusion  CATCGMHashTableOfAnomaly : public CATCGMHashTable
{
public:
   CATCGMNewClassArrayDeclare;
   /**
   * @nodoc
   */
   CATCGMHashTableOfAnomaly(int iEstimatedSize = 0);
   /**
   * @nodoc
   */
   ~CATCGMHashTableOfAnomaly();
   /**
   * @nodoc
   */
   int										Insert(CATCX_Anomaly* piAnomalyCheck);
   /**
   * @nodoc
   */
   CATCX_Anomaly*					      Locate(CATCX_Anomaly* piAnomalyCheck) const;
   /**
   * @nodoc
   */
   int										LocateReturnPos(CATCX_Anomaly* piAnomalyCheck) const;
   /**
   * @nodoc
   */
   int										LocatePartial(CATCX_Anomaly* piAnomalyCheck,short iMode = 0) const;
   /**
   * @nodoc
   */
   int										LocateWeak(CATCX_Anomaly* piAnomalyCheck) const;

   /**
   * @nodoc
   */
   int										LocateWithInclusion(CATCX_Anomaly* piAnomalyCheck) const;
   /**
   * @nodoc
   */
   int										Remove(CATCX_Anomaly* piAnomalyCheck);
};


INLINE  unsigned short CATCX_Anomaly::AddRef()
{ return ++_Counter; }

INLINE  unsigned short CATCX_Anomaly::Release()
{ unsigned short rc = --_Counter; if ( 0 == rc ) delete this; return rc; }

#endif

