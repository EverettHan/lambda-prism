#ifndef CATCGMCockpit_h
#define CATCGMCockpit_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
#include "CATSysSimpleHashTable.h"
#include "CATListOfCATCGMCockpit.h"
#include "CATUnicodeString.h"
#include "CATDataType.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "CATMathematics.h"

#include "CATCGAreport_PCS.h"
#include "CATCGAMeasureGMData.h"
 
class CATCGAMeasure;

class  ExportedByCATMathematics CATCGMCockpit
{ 
public :
  CATCGMNewClassArrayDeclare;

  CATCGMCockpit(int  iCSIDepth, const CATCGAMeasureContext &iCopy ) ;
  CATCGMCockpit(const char    * iOperation, const char    * iOperationDomain  , CATCGMItfName    *  iWorkingFeature);
  CATCGMCockpit(CATCGMCockpit * iCaller ,   CATCGMCockpit * iCallee ) ;
 
  ~CATCGMCockpit() ;

  CATBoolean operator == (const CATCGMCockpit & iOther) const ;

  CATUINTPTR HashValue()  
  { return _Key; }

  // Collecting Computer Science Indicator 
  CATCGAreport_PCS      _CSI;

  // Collecting  Working Statistics (IFWe Purge)
  CATCGAMeasureGMData   _GMData;

  CATULONG64        _NbCalls;
  CATULONG64        _NbCallers;

  CATULONG64        _CumulatedDepth;

  //  Specific Links (in Context of first caller of function stack)
  CATCGMCockpit  *  _Caller;
  CATCGMCockpit  *  _Callee;

  // IndexTable
  CATULONG32        _IndexTable;
  const CATUINTPTR  _Key;  

  int               _CSIDepth; // Filter for Local HashTable HT
  int               _CSIKEY;  

private :
  
  friend class     CATCGMCockpitTable;

  CATCGMCockpit (CATCGMCockpit &);    
  CATCGMCockpit& operator=(CATCGMCockpit&);  
};

extern ExportedByCATMathematics int SortCATCGMCockpitByDepthAndString(CATCGMCockpit *left,    CATCGMCockpit *right);
extern ExportedByCATMathematics int SortCATCGMCockpitByRatioLucid(CATCGMCockpit *left,    CATCGMCockpit *right);
extern ExportedByCATMathematics int SortCATCGMCockpitByString(CATCGMCockpit *left,    CATCGMCockpit *right);
extern ExportedByCATMathematics int SortCATCGMCockpitByMeanDepth(CATCGMCockpit *left, CATCGMCockpit *right);

 
#endif
