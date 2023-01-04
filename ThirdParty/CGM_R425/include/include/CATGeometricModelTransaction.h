#ifndef CATGeometricModelTransaction_h
#define CATGeometricModelTransaction_h

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//==========================================================================
//
#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"

/**
 * Type of the transactions.
 */ 
typedef unsigned int CATCGMKindOfTransaction;

/**
 * List of the transaction types.
 */ 
#define CatQuickFindObjectFromTag             0x00000001
/**
 * Class to define a geometric model transaction. This class can 
 * typically be used when scanning the model, as it improves 
 * the performances of the CATGeoFactory->FindObjectFromTag() 
 * service.
 * <br>Example
 * <pre>
 *    CATGeometricModelTransactionBegin(MyTransactionID,CatQuickFindObjectFromTag) 
 *    {
 *      // ... Numerous calls to geometrical model services 
 *    }
 *    CATGeometricModelTransactionEnd(MyTransactionID);
 * </pre>
*/
class ExportedByCATMathStream CATGeometricModelTransaction : public CATCGMVirtual 
{
public :
/**
 * Deletes a CATGeometricModelTransaction.
 *<br>Usage of the provided "end" macro is strongly recommended.
 */ 
  virtual ~CATGeometricModelTransaction();

/**
 * @nodoc
 * It is recommended to use the macro instead of the function.
 * Creates a CATGeometricModelTransaction.
 * @param purpose
 * The kind of the transaction, form the list defined in this header.
 * <br>Usage of the provided "begin" macro is strongly recommended.
 * @return
 * The CATGeometricModelTransaction.
 */ 
  static CATGeometricModelTransaction * Create(CATCGMKindOfTransaction purpose);

/**
 * @nodoc
 */ 
  CATCGMNewClassArrayDeclare; 

protected:

/**
 * @nodoc
 * Constructs a CATGeometricModelTransaction.
 *<br><tt>purpose</tt> is the kind of the transaction, form the list defined in this header.
 */ 
  CATGeometricModelTransaction();
};

/**
 * Macro to be used to create the transaction.
 * Creation and start of the transaction.
 * <br><tt>mytransaction</tt> is the name of the transaction to be created and started.
 * <br><tt>KindOfTransaction</tt> is the kind of transaction, as defined in the transaction type list.
 */
#define CATGeometricModelTransactionBegin(mytransaction,KindOfTransaction)     \
   CATGeometricModelTransaction *volatile mytransaction                        \
     = CATGeometricModelTransaction::Create(KindOfTransaction);                \
   CATTry                                                                      \
   {

/**
 * Macro to be used to end the transaction.
 * Ending and deletion of the transaction defined by a creation macro.
 * <br><tt>mytransaction</tt> is the name of the transaction to be ended.
 */
// ++IK8 20:04:21 It is invalid to define duplicate CATCatch blocks!
// (cf. CATGeometricModelTransactionCatch)
// Any duplicate definition is dead code and breaks compilation in Native Exception mode
// CATErrorMacros.h is about to be updated to catch those errors at compile-time
// even when NATIVE_EXCEPTION is not defined
// => Replaced "CATCatch(CATError, err)" by "CATCatchOthers", which is equivalent
#define CATGeometricModelTransactionEnd(mytransaction)                         \
      if ( mytransaction ) { delete mytransaction; mytransaction = NULL; }     \
   }                                                                           \
   CATCatchOthers                                                              \
   {                                                                           \
      if ( mytransaction ) { delete mytransaction; mytransaction = NULL; }     \
      CATGeometricModelTransactionEndTry(mytransaction)
// ++IK8 20:04:21 

/**
 * Catch for error management inside transaction.
 */
#define CATGeometricModelTransactionCatch(mytransaction,error)                 \
      if ( mytransaction ) { delete mytransaction; mytransaction = NULL; }     \
   }                                                                           \
   CATCatch(CATError, error)                                                   \
   {                                                                           \
      if ( mytransaction ) { delete mytransaction; mytransaction = NULL; }


/**
 * EndTry for error management inside transaction.
 */
#define CATGeometricModelTransactionEndTry(mytransaction)                      \
      CATRethrow;                                                              \
   }                                                                           \
   CATEndTry


/**
 * EndTry for error management inside transaction ( without Rethrow ).
 */
#define CATGeometricModelTransactionEndTryWithoutRethrow(mytransaction)        \
   }                                                                           \
   CATEndTry



#endif
