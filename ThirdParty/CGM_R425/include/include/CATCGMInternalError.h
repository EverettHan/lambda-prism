#ifndef CATCGMInternalError_h
#define CATCGMInternalError_h
/** @CAA2Required */

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "CATMathematics.h"
#include "CATInternalError.h"
#include "CATCGMNewArray.h"

// ++IK8 
#if (!defined(_AIX_SOURCE) || defined(__ibmxl__)) // All platforms but non C++11 AIX
#define CATCGMInternalError_override   override
#else
#define CATCGMInternalError_override
#endif
// ++IK8 

class CATCGMInputError;

class ExportedByCATMathematics CATCGMInternalError : public CATInternalError
{
 public:
   
#if defined(CATError_OnBeforeThrow_Defined) // ++IK8: to facilitate the transition whatever the code level
   /** @nodoc */
   virtual void OnBeforeThrow         (const char *loc, int line)                             CATCGMInternalError_override;
#else
   /** @nodoc */
   virtual void Throw                 (const char *loc, int line, void *ptr_to_delete = NULL) CATCGMInternalError_override;
#endif
   
   /** @nodoc */
   CATDeclareClass;
   
   /** @nodoc */
                   CATCGMInternalError(const CATCGMInternalError & iError       );

   /** @nodoc */
                   CATCGMInternalError(      CATErrorId            id           );

                   CATCGMInternalError(      CATErrorId            id           ,
                                       const char                * msgId        ,
                                       const char                * catalog      = NULL);

                   CATCGMInternalError(const char                * msgId        ,
                                       const char                * catalog      ); 

   /** @nodoc  */
   virtual        ~CATCGMInternalError();
   
   /** @nodoc */
   CATCGMNewClassArrayDeclare;

   /** @nodoc */
           void    DefineCGMErrParams (const CATCGMInternalError &iError);

   /** @nodoc */
           void    DefineCGMErrParams (const CATCGMInputError &iError);

   friend class CATCGMInputError;
};


#endif
