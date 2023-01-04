#ifndef CATCGMInputError_h
#define CATCGMInputError_h

/**
 * @CAA2Level L1
 * @CAA2Usage U2
 */

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "CATMathematics.h"
#include "CATInputError.h"
#include "CATCGMNewArray.h"

// ++IK8 
#if (!defined(_AIX_SOURCE) || defined(__ibmxl__)) // All platforms but non C++11 AIX
#define CATCGMInputError_override   override
#else
#define CATCGMInputError_override
#endif
// ++IK8 

class CATCGMInternalError;
/**
 * Parent class of CATCGMDiagnosis. Do not use directly.
 */
class ExportedByCATMathematics CATCGMInputError : public CATInputError
{
 public:

#if defined(CATError_OnBeforeThrow_Defined) // ++IK8: to facilitate the transition whatever the code level
   /** @nodoc */
   virtual void    OnBeforeThrow     (const char *loc, int line)                             CATCGMInputError_override;
#else
   /** @nodoc */
   virtual void    Throw             (const char *loc, int line, void *ptr_to_delete = NULL) CATCGMInputError_override;
#endif

   /** @nodoc */
   CATDeclareClass;

   /** @nodoc */
                   CATCGMInputError  (const CATCGMInputError &iError  );
   /** @nodoc */
                   CATCGMInputError  (      CATErrorId        id      );
   /** @nodoc */
                   CATCGMInputError  (      CATErrorId        id      ,
                                      const char            * msgId   ,
                                      const char            * catalog = NULL);
   /** @nodoc */
                   CATCGMInputError  (const char            * msgId   ,
                                      const char            * catalog );

   /** @nodoc  */
   virtual        ~CATCGMInputError  ();

   /** @nodoc */
   CATCGMNewClassArrayDeclare;

   /** @nodoc */
           void    DefineCGMErrParams(const CATCGMInternalError & iError);

   /** @nodoc */
           void    DefineCGMErrParams(const CATCGMInputError    & iError);
   /** @nodoc */
   friend class CATCGMInternalError;
};


#endif
