#ifndef CATGeoControl_H
#define CATGeoControl_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
/*


*/
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
#include "CATCGMTransactionControl.h"
#include "CATCGMFactoryTransaction.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATError;

class ExportedByGeometricObjects CATGeoControl
{
public :

  static CATGeoControl * GetBridge();



protected :

  
  //------------------------------------------------------------
  // ExtendedTransaction
  //------------------------------------------------------------
  INLINE static  CATCGMFactoryTransaction *  CreateExtendedTransaction(CATDocument                    * Document, 
                                                                       CATGeoFactory                  * iFactory, 
                                                                       CATCGMTransactionControl       & ioManage,
                                                                       const CATLISTP(CATICGMObject)  * pInputs,
                                                                       const CATLISTP(CATICGMObject)  * pOldResults );

  virtual        CATCGMFactoryTransaction *  _CreateExtendedTransaction(CATDocument                    * Document, 
                                                                        CATGeoFactory                  * iFactory, 
                                                                        CATCGMTransactionControl       & ioManage,
                                                                        const CATLISTP(CATICGMObject)  * pInputs,
                                                                        const CATLISTP(CATICGMObject)  * pOldResults ) = 0;


  //------------------------------------------------------------
  // CATCGMTransactionControl
  //------------------------------------------------------------
  INLINE static void  InitDefaultControl();
  virtual       void _InitDefaultControl() = 0 ;

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  virtual ~CATGeoControl();
  CATGeoControl();

  static CATGeoControl * _Bridge;
  static CATBoolean    _Defined;

  friend class CATCGMTransactionControl;
  friend class CATCGMFactoryTransaction;
};


//------------------------------------------------------------
// Declenchement effective du Clean
//------------------------------------------------------------
INLINE void CATGeoControl::InitDefaultControl()
{
  CATGeoControl *bridge = _Defined ? _Bridge : GetBridge();
  if ( bridge )
    bridge->_InitDefaultControl();
}

//---------------------------------------------------------------------------
// CreateExtendedTransaction
//---------------------------------------------------------------------------
INLINE CATCGMFactoryTransaction *  CATGeoControl::CreateExtendedTransaction(CATDocument                    * Document, 
                                                                            CATGeoFactory                  * iFactory, 
                                                                            CATCGMTransactionControl       & ioManage,
                                                                            const CATLISTP(CATICGMObject)  * pInputs,
                                                                            const CATLISTP(CATICGMObject)  * pOldResults )
{
  CATGeoControl *bridge = _Defined ? _Bridge : GetBridge();
  if ( bridge )
    return bridge->_CreateExtendedTransaction(Document,iFactory,ioManage,pInputs,pOldResults);
  return NULL;
}

#endif
