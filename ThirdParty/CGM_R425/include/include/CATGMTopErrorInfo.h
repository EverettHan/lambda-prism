#ifndef CATGMTopErrorInfo_h
#define CATGMTopErrorInfo_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2016
//-----------------------------------------------------------------------------
// Class allowing -------------------------------------------------------------
// ---------------------------------------------------------------------------- 
//-----------------------------------------------------------------------------

#include "ExportedByCATTopologicalObjects.h"
#include "CATGMErrorInfo.h"
#include "CATCGMNewArray.h"
#include "CATUnicodeString.h"
#include "CATCollec.h" 
#include "CATCGMOutput.h"
#include "CATListOfCATGMErrorInfo.h"
#include "CATBody.h"
#include "ListPOfCATBody.h"

class CATError;
class CATGMErrorInfo;
class CATLISTP(CATGMErrorInfo);
class CATBody;
class CATLISTP(CATBody);

class ExportedByCATTopologicalObjects CATGMTopErrorInfo : public CATGMErrorInfo
{
public:
    
   CATCGMNewClassArrayDeclare;

  // -----------
  // Ctor & Dtor
  // -----------

   /** @nocgmitf @nodoc */
   CATGMTopErrorInfo(CATError *piError, CATBoolean iRemoveObj = FALSE);

   /** @nocgmitf @nodoc */
   CATGMTopErrorInfo();

   /** @nocgmitf @nodoc */
   virtual ~CATGMTopErrorInfo();
        
  // -----------
  // Services
  // -----------

   /** @nocgmitf @nodoc */
   virtual CATBoolean IsTopErrorInfo();

   /** @nocgmitf @nodoc */
   virtual void Write(CATCGMStream &ioStr);

   /** @nocgmitf @nodoc */
   virtual void Read(CATCGMStream &iStr/*,CATGMTopErrorInfo *pioTopErrorInfo*/);

   /** @nocgmitf @nodoc */
   virtual int MapErrorInfo(CATGMErrorInfo *piErrorInfo, CATCGMOutput& os);

   /** @nocgmitf @nodoc */
   void GetErrorObjects(CATLISTP(CATBody) &ioListOfOutputErrors);

   /** @nocgmitf @nodoc */
  virtual void Dump(CATCGMOutput& os);

  /** @nocgmitf @nodoc */
  static CATUnicodeString  _TopOpInErrorName;

  /** @nocgmitf @nodoc */
  static CATUnicodeString  _CGMDiagnosisName;

protected:
  
  // ------------------------
  // Internal Use Ctor & Dtor
  // ------------------------
  //CATGMTopErrorInfo();
  //virtual ~CATGMTopErrorInfo();

private:
  // ---------------
  // Forbidden Ctors
  // ---------------
  CATGMTopErrorInfo(const CATGMTopErrorInfo& iTopErrorInfo);
  CATGMTopErrorInfo& operator = (const CATGMTopErrorInfo& iTopErrorInfo);

  //---------------
  // Internal Services
  //---------------
  void InitErrorInfo(CATError *piError);

  //---------------
  // Data
  //---------------
  CATLISTP(CATBody) _LocationList;
  CATLISTP(CATBody) _InputList;
  CATLISTP(CATBody) _ContextList;

  CATLISTP(CATGMErrorInfo) _ListGMErrorInfo;
    
};

#endif
