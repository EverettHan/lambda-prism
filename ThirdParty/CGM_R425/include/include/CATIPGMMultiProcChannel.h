#ifndef CATIPGMMultiProcChannel_h_
#define CATIPGMMultiProcChannel_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATListPOfCATCGMDiagnoses.h"
#include "CATListOfCATICGMObjects.h"
#include "CATSysErrorDef.h"

class CATGeoFactory;
class CATICGMObject;
class CATCGMJournalList;
class CATCGMDiagnosis;
class CATMathStream;
class CATSoftwareConfiguration;

class ExportedByCATGMModelInterfaces CATIPGMMultiProcChannel : public CATCGMVirtual
{
public:  

 /**
  * ~ Class members ~
  *
  * Retrieve a pointer on the input Software Configuration */
  virtual  CATSoftwareConfiguration * GetConfig () const = 0;
  /* Retrieve a pointer on the input GeoFactory */
  virtual  CATGeoFactory            * GetFactory() const = 0;


 /**
  *----------------------------------------------------------------*
  *               ~ Asynchronuous Writing ~ 
  *----------------------------------------------------------------*
  * Methods to call in  CATIPGMMultiProcTask::Write() / OnExecute()
  * Data will be "catched" automatically afterwards by streamer engine.
  *   Will return E_FAIL if called on reading channel.
  *   Will return S_FALSE if no data have been sent, S_OK otherwise.
  */
  virtual HRESULT Send (CATICGMObject * iInputObj) = 0;   
  virtual HRESULT Send (const CATLISTP(CATICGMObject) & iObjectList) = 0;
  virtual HRESULT Send (CATCGMDiagnosis * ipDiagnosis) = 0;
  virtual HRESULT Send (const CATLISTP(CATCGMDiagnosis) & iWarningList) = 0;
  /* be aware: Only one Journal can be sent. */
  virtual HRESULT Send (CATCGMJournalList * ipJournal) = 0;
 /**
  * be aware: Only one stream can be sent.
  * Example:
  *   CATMathStream  writeStream ((size_t) 0, CatCGMStreamWriteOnly);
  *   HRESULT hr = ioInputChannel.Send(writeStream);
  */
  virtual HRESULT Send (const CATMathStream &iStream) = 0;
  

 /**
  *----------------------------------------------------------------*
  *               ~ Asynchronuous Reading ~ 
  *----------------------------------------------------------------*
  * Retrieve asynchronuous sent objects (from Send(Xxx) methods).
  * You can call them in any order, regardless of the Send order. 
  *   Will return E_FAIL if called on writting channel.
  *   Will return S_FALSE if no data have been found, S_OK otherwise.
  */
  virtual HRESULT GetObjects  (CATLISTP(CATICGMObject)   & oObjectList)  const = 0;
  virtual HRESULT GetDiagnosis(CATLISTP(CATCGMDiagnosis) & oWarningList) const = 0;
  virtual HRESULT GetJournal  (CATCGMJournalList        *& oJournal)     const = 0;

 /** 
  * Construct a CATMathStream object to retrieve your data.
  * Example:  
  *   CATMathStream  myReadStream (iInputChannel.GetStreamLength(), CatCGMStreamReadWrite);
  *   HRESULT hr = iInputChannel.Get(myReadStream);
  */
  virtual size_t  GetStreamLength() const = 0;
  virtual HRESULT GetStream(CATMathStream & oStream) const = 0;
  


  // @ depracated R424  
  [[deprecated("is deprecated [R424/R2022x] - Use GetObjects() instead.")]]
  virtual HRESULT Get(CATLISTP(CATICGMObject)   & oObjectList)  const = 0;
  // @ depracated R424  
  [[deprecated("is deprecated [R424/R2022x] - Use GetDiagnosis() instead.")]]
  virtual HRESULT Get(CATLISTP(CATCGMDiagnosis) & oWarningList) const = 0;
  // @ depracated R424  
  [[deprecated("is deprecated [R424/R2022x] - Use GetJournal() instead.")]]
  virtual HRESULT Get(CATCGMJournalList        *& oJournal)     const = 0;
  // @ depracated R424  
  [[deprecated("is deprecated [R424/R2022x] - Use GetStream() instead.")]]
  virtual HRESULT Get(CATMathStream & oStream) const = 0;

protected :
  /* protected Contructor */
  CATIPGMMultiProcChannel();

  /* protected destructor */
  virtual ~CATIPGMMultiProcChannel();

private :
  /* forbiden constructor */
  CATIPGMMultiProcChannel (const CATIPGMMultiProcChannel &);
  /* forbiden operator */
  CATIPGMMultiProcChannel & operator = (const CATIPGMMultiProcChannel &);

};

#endif

