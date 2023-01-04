#ifndef CATCGMStreamVersionUnderEvaluation_h
#define CATCGMStreamVersionUnderEvaluation_h

// COPYRIGHT DASSAULT SYSTEMES  2008
#include "CATCGMStreamVersion.h"
#include "ExportedByCATMathStream.h"
#include "CATCGMStreamVersionLimited.h"
#include "CATBoolean.h"


//----------------------------------------------------------------------------
// For identified variation of persistency given as enumeration from  
//    Mathematics\ProtectedInterfaces\CATCGMStreamVersionUnderEvaluation.h
//----------------------------------------------------------------------------

#define CATCGMStreamVersionDECLARE(StreamTopic,TargetCATCGMStreamVersion,CurrentActivation) \
      extern ExportedByCATMathStream  const CATCGMStreamVersion & CATCGMStreamVersion__##StreamTopic ;

#define CATCGMStreamVersionIsActive(iToCheck,iReference) \
  ( ( (int)iReference >= (int)CATCGMStreamVersion__##iToCheck ) ? TRUE : FALSE )

#include "CATCGMStreamVersionDEFINE.h"


//----------------------------------------------------------------------------
// Incremental Enhancements for Persistency 
//    (Split by small requirements & specifications & certifications)
//    originated from recovery request of delivered ...
//----------------------------------------------------------------------------
 

/*
  Compact Header Variation :  if ( CATCGMStreamVersion_DifferedDeletion( GetVersionNumber() ) )
*/

#define CATCGMStreamVersion_DifferedDeletion(iReference) CATCGMStreamVersionIsActive(DifferedDeletion,iReference)

/*
  FactoryHeaderAtBegin :  if ( CATCGMStreamVersion_FactoryHeaderAtBegin( GetVersionNumber() ) )
*/

#define CATCGMStreamVersion_FactoryHeaderAtBegin(iReference) CATCGMStreamVersionIsActive(FactoryHeaderAtBegin,iReference)
 


#endif  /* CATCGMStreamVersionUnderEvaluation_h  */
