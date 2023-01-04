#ifndef CATGMErrorInfo_h
#define CATGMErrorInfo_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2015
//-----------------------------------------------------------------------------
// Class allowing to build a CGM Model working form from sim data
// it is used as input of CATIPGMTopOrmBuildSkeleton Operator 
//-----------------------------------------------------------------------------

#include "ExportedByGeometricObjects.h"
//#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATUnicodeString.h"
#include "CATCGMOutput.h"
#include "CATBoolean.h"


class CATError;
class CATCGMStream;

class ExportedByGeometricObjects CATGMErrorInfo //: public CATCGMVirtual
{
public:
    
   CATCGMNewClassArrayDeclare;

  // -----------
  // Ctor & Dtor
  // -----------
      
   /** @nocgmitf @nodoc */
   CATGMErrorInfo(CATError *piError, CATBoolean iRemoveObj = FALSE);

   /** @nocgmitf @nodoc */
   CATGMErrorInfo();

   /** @nocgmitf @nodoc */
   virtual ~CATGMErrorInfo();
     
  // -----------
  // Services
  // -----------

  /** @nocgmitf @nodoc */
  virtual CATBoolean IsTopErrorInfo();

   /** @nocgmitf @nodoc */
   void SetRemoveObjects(CATBoolean iDoRemove);

  /** @nocgmitf @nodoc */
  const char *GetClassNameError();

  /** @nocgmitf @nodoc */
  const char *GetMsgCatalog();

  /** @nocgmitf @nodoc */
  const char *GetMsgId();

  /** @nocgmitf @nodoc */
  short GetId();

  /** @nocgmitf @nodoc */
  virtual void Write(CATCGMStream &ioStr);

  /** @nocgmitf @nodoc */
  virtual void Read(CATCGMStream &iStr/*,CATGMErrorInfo *&pioErrorInfo*/);
  
  /** @nocgmitf @nodoc */
   virtual int MapErrorInfo(CATGMErrorInfo *piErrorInfo, CATCGMOutput& os);

  /** @nocgmitf @nodoc */
  virtual void Dump(CATCGMOutput& os);

protected:
  
  // ------------------------
  // Internal Use Ctor & Dtor
  // ------------------------
  //CATGMErrorInfo();
  //virtual ~CATGMErrorInfo();

  // ---------------
  // Forbidden Ctors
  // ---------------
  CATGMErrorInfo(const CATGMErrorInfo& iErrorInfo);
  CATGMErrorInfo& operator = (const CATGMErrorInfo& iErrorInfo);

  //---------------
  // Data
  //---------------
  CATUnicodeString   _ClassNameError;
  CATUnicodeString   _MsgCatalog;
  CATUnicodeString   _MsgId;
  CATUnicodeString   _MsgNLS;
  short              _Id;
  CATBoolean         _RemoveObjects; 
 };

#endif
