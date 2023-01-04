// COPYRIGHT DASSAULT SYSTEMES 2019
//=============================================================================
//
// CATGeoOpDummyOp:
//  - Dummy operator to run any function
//=============================================================================
//=============================================================================
// Usage notes:
//=============================================================================
// 17/12/19 Q48  Creation
//=============================================================================

#ifndef CATGeoOpDummyOp_H
#define CATGeoOpDummyOp_H

// ExportedBy
#include "Y3DYNOPE.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

// System
#include "CATTrace.h"
#include "CATUnicodeString.h"

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATString.h"

// Mathematics
#include "CATSoftwareConfiguration.h"

class ExportedByY3DYNOPE CATGeoOpDummyOp : public CATGeoOperator
{
public:

  CATGeoOpDummyOp();
  CATGeoOpDummyOp(CATSoftwareConfiguration * iConfig);
  virtual ~CATGeoOpDummyOp();

  int RunOperator();

  void SetPtr( int (*iPtr)() );
  void SetPtr( int (*iPtr)(void *&) );

  void* GetOutputData() const;

  // Utility
  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;

protected:

  virtual CATGeoOpTimer * GetTimer();

private:

  void Reset();

  //int (CATGeoOpDummyOp::*_FuncPtr)(); // Function pointer to a function in this class

  int (*_FuncPtr)();             // Function pointer to a global function
  int (*_FuncPtr_Void)(void *&); // Function pointer to a global function

  void* _OutputData;

  CATSoftwareConfiguration* _Config;
};
#endif // CATGeoOpDummyOp_H
