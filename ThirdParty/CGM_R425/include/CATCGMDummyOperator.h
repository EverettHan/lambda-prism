#ifndef CATCGMDummyOperator_h
#define CATCGMDummyOperator_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
#include "CATTopOperator.h"
#include "CATUnicodeString.h"
#include "ExportedByCATTopologicalObjects.h"

class CATExtCGMReplay;

ExportedByCATTopologicalObjects CATTopOperator *CATCreateDummyOperator(CATUnicodeString &iOperatorName);


class  ExportedByCATTopologicalObjects CATCGMDummyOperator : public CATTopOperator 
{ 
  CATCGMVirtualDeclareClass(CATCGMDummyOperator);

public :
  ~CATCGMDummyOperator() ;

protected :
  CATCGMDummyOperator(CATGeoFactory*     iFactory,  CATTopData*        iTopData,  CATBodyFreezeMode  iBodyFreezeMode, CATExtCGMReplay *iCGMReplay );
  int RunOperator();  

private :

  CATExtCGMReplay  * _CGMReplay;

  friend ExportedByCATTopologicalObjects CATTopOperator *CATCreateDummyOperator(CATUnicodeString &iOperatorName);

  CATCGMDummyOperator (CATCGMDummyOperator &);    
  CATCGMDummyOperator& operator=(CATCGMDummyOperator&);  
};
 


#endif
