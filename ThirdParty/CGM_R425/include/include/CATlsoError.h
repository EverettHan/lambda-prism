#ifndef CATlsoError_H
#define CATlsoError_H

// --------------------------------------------------------------------------------------------------------
// #include "CATlsoError.h"
// #include "CATTopOpInError.h"
//
//
// CATlsoAssert(ptvalue);
//
// Remplace if (!tptvalue) CATThrowForNullPointer();
//
// --------------------------------------------------------------------------------------------------------

#include "CATTopOpInError.h"
#include "CATCGMOutput.h"
#include "PersistentCell.h"

class CATExtTopOperator;

ExportedByPersistentCell CATTopOpInError * CATlsoCreateInvalidInternalDataError(const char * iFileName, int iLine);

ExportedByPersistentCell CATTopOpInError * CATlsoCreateInvalidInputDataError(const char * iFileName, int iLine);

ExportedByPersistentCell CATTopOpInError * CATlsoCreateInternalOperatorError(const char * iFileName, int iLine, const CATExtTopOperator *iOpe);

// --------------------------------------------------------------------------------------------------------
// le #define suivant permet, pour l'environnement de LiveShapeOperator, de lancer une exception
// --------------------------------------------------------------------------------------------------------


// You have to write : 
//     CATlsoInputError;
// DO NO FORGET THE ; AFTER THIS MACRO
#define CATlsoInputError \
  CATThrow(CATlsoCreateInvalidInputDataError(__FILE__,__LINE__))
    //do { cgmout << __FILE__ << "(" << __LINE__ << "): LiveShapeOperator Error -- Invalid input data" << cgmendl; \
    //CATTopOpInError * Error = new CATTopOpInError( TopOpInInvalidOperator,"TopOpInInvalidOperator", TopOpInFile ); \
    // CATThrow(Error); } while(0)

// --------------------------------------------------------------------------------------------------------
// le #define suivant permet, pour l'environnement de LiveShapeOperator, de lancer une exception
// --------------------------------------------------------------------------------------------------------

// You have to write : 
//     CATlsoInternalError;
// DO NO FORGET THE ; AFTER THIS MACRO
#define CATlsoInternalError \
  CATThrow(CATlsoCreateInvalidInternalDataError(__FILE__,__LINE__))
   // do { cgmout << __FILE__ << "(" << __LINE__ << "): LiveShapeOperator Error -- Invalid internal data" << cgmendl; \
   // CATTopOpInError * Error = new CATTopOpInError("TopOpInAllTopo_ERR_7505", TopOpInFile ); \
   //  CATThrow(Error); } while(0)


// --------------------------------------------------------------------------------------------------------
// le #define suivant permet, pour l'environnement de LiveShapeOperator, de lancer une exception
// --------------------------------------------------------------------------------------------------------
// You have to write : 
//     CATlsoInternalError;
// DO NO FORGET THE ; AFTER THIS MACRO
#define CATlsoOperatorError(ptrOperator) \
  CATThrow(CATlsoCreateInternalOperatorError(__FILE__,__LINE__,ptrOperator))
   // do { cgmout << __FILE__ << "(" << __LINE__ << "): LiveShapeOperator Error -- Invalid internal data" << cgmendl; \
   // CATTopOpInError * Error = new CATTopOpInError("TopOpInAllTopo_ERR_7505", TopOpInFile ); \
   //  CATThrow(Error); } while(0)


// --------------------------------------------------------------------------------------------------------
// le #define suivant permet, pour l'environnement de LiveShapeOperator, de lancer une exception
// si un pointeur ou un entier est nul
//
//      CATlsoAssert(ptvalue);
// remplace
//      if (!tptvalue) CATThrowForNullPointer();
//
// Astuce de code
// le test de ptvalue s'ecrit if (! (ptvalue))
// Ainsi on peut accepter le test de plusieurs variables.
//  CATlsoAssert(ptvalue1 && ptvalue2 && ... && ptvalueN);
// --------------------------------------------------------------------------------------------------------

// CAThvoAssert en attendant la declaration pour la R20
#define CAThvoAssert(ptvalue) \
{ \
  if (! (ptvalue)) CATThrow(CATlsoCreateInvalidInternalDataError(__FILE__,__LINE__)); \
}
    //do { if (! (ptvalue)) { \
    //cgmout << __FILE__ << "(" << __LINE__ << "): LiveShapeOperator Error -- Invalid internal data" << cgmendl; \
    //CATTopOpInError * Error = new CATTopOpInError("TopOpInAllTopo_ERR_7505", TopOpInFile ); \
    //CATThrow(Error); } } while(0)

#define CATlsoAssert(ptvalue) \
{ \
  if (! (ptvalue)) CATThrow(CATlsoCreateInvalidInternalDataError(__FILE__,__LINE__)); \
}
    //do { if (! (ptvalue)) { \
    //cgmout << __FILE__ << "(" << __LINE__ << "): LiveShapeOperator Error -- Invalid internal data" << cgmendl; \
    //CATTopOpInError * Error = new CATTopOpInError("TopOpInAllTopo_ERR_7505", TopOpInFile ); \
    //CATThrow(Error); } } while(0)

#endif
