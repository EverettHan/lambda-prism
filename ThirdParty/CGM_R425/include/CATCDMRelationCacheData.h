//===================================================================
// COPYRIGHT Dassault Systemes 2012
//===================================================================
// CATCDMRelationCacheData.h
//===================================================================
//
//

//===================================================================
#ifndef CATCDMRelationCacheData_H
#define CATCDMRelationCacheData_H

#include "CATCDMBaseInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATSysBoolean.h"

class ExportedByCATCDMBaseInterfaces CATCDMRelationCacheData
{
public:
  // Standard constructors and destructors
  // -------------------------------------
  CATCDMRelationCacheData ();
  virtual ~CATCDMRelationCacheData ();


  HRESULT GetDouble (double& oDouble);
  HRESULT GetBoolean (CATBoolean & oBool);
  HRESULT GetInt (int & oValue);

  HRESULT SetDouble(double iDouble);
  HRESULT SetBoolean(CATBoolean iBool);
  HRESULT SetInt(int iValue);

  //Each time something is added here, we have to stream it in the CDMRelation
  
  // Copy constructor and equal operator
  // -----------------------------------
  CATCDMRelationCacheData (const CATCDMRelationCacheData &);
  CATCDMRelationCacheData& operator=(const CATCDMRelationCacheData &);

private:

  double*					_FirstDouble;
  CATBoolean*			_FirstBool;
  int*            _FirstInt;
};

#endif
