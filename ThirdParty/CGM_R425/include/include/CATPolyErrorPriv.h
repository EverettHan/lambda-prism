//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//==============================================================================================================
// CATPolyErrorPriv : List of prepro definitions and classes associated with CATPolyError
//                    to be used in PolyhedralObjects fw only

//==============================================================================================================
// Creation : CHU  sep 2005
//==============================================================================================================

#ifndef CATPolyErrorPriv_H
#define CATPolyErrorPriv_H
#include "CATPolyError.h"
#include "CATErrorDef.h"

// usage : RAISE(err) << " blabla"; // can be used if err is null or not, avoids the error constructor call
#define RAISE(err) CATPolyErrorPointer( & ( err ) )

// usage : RAISE_WITH(err,hr) << " blabla"; // as above, will transmit HRESULT only if not null
#define RAISE_WITH(err, hr) CATPolyErrorPointer( & ( err ) , hr )

#define TAG( obj ) obj->GetTag()

// Following class is designed to be used as left-value of operator << instead of a CATPolyError,
// enabling the use of a pointer to a CATPolyError that may not be initialized
class CATPolyErrorPointer {
public:
  inline CATPolyErrorPointer(CATPolyError ** ioErr, HRESULT iHR = E_FAIL);
  CATPolyError ** _PolyError;
  HRESULT         _InitialHR;
  //friend ExportedByPolyhedralUtilities CATPolyErrorPointer & operator << ( CATPolyErrorPointer& e, const char * iText);
  ExportedByPolyhedralUtilities CATPolyErrorPointer & operator << ( const char * iText);
  // friend ExportedByPolyhedralUtilities CATPolyErrorPointer & operator << ( CATPolyErrorPointer& e, const int iVal);
  ExportedByPolyhedralUtilities CATPolyErrorPointer & operator << ( const int iVal);
  ExportedByPolyhedralUtilities CATPolyErrorPointer & operator << ( const double iVal);
};

inline CATPolyErrorPointer::CATPolyErrorPointer(CATPolyError ** ioErr, HRESULT iHR) {
  _PolyError = ioErr; _InitialHR = (iHR) ? (iHR) : (E_FAIL); }

#endif
