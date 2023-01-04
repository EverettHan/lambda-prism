/* -*-c++-*- */
#ifndef CATICGMStreamFactory_h
#define CATICGMStreamFactory_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES	1999
//=============================================================================
#include "ExportedByCATMathStream.h"
#include "CATICGMStreamable.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATMathStream IID IID_CATICGMStreamFactory ;
#else
extern "C" const IID IID_CATICGMStreamFactory ;
#endif


/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATMathStream CATICGMStreamFactory : public CATICGMStreamable
{
  CATDeclareInterface;

public:



};

// --------------------------------------------------------------------------
//                             Handler
// --------------------------------------------------------------------------

CATDeclareHandler( CATICGMStreamFactory, CATICGMStreamable ) ;


#endif



