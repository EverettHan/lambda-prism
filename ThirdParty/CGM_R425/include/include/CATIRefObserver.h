#ifndef CATIRefObserver_h
#define CATIRefObserver_h

// System
#include "CATListPV.h"
#include "CATBaseUnknown.h"

// SpecialAPI
#include "CATDataType.h"

class CATechMeta;
class CATMathPoint;
class CATMathBox2D;
class CATMathVector;
class CATUnicodeString;
class CATMathTransformation;

/*
* @COPYRIGHT DASSAULT SYSTEMES 2012
* --------------------------------------------------------------------------------------------------
*  C++ Interface(non CAA) for implementation of reference check mechanism for phoenix infrastructure
* --------------------------------------------------------------------------------------------------
*/

class CATIRefObserver
{
public:

  /*
  * ResultOfComparison : Callback method called by the reference manager when the comparison between the
  *                      before and after values in the reference files are not equal
  * @param iValBefore : value when the operator was replayed last(read from Reference.txt)
  * @param iValAfter : Value when the operator was replayed now
  * @param iResultOfComparison : S_OK if both values match, S_FALSE if the values are within tolerance and 
  *                              E_FAIL if the values don't match at all
  * @param iLineNoForMismatch : Line number corresponding to the line where the mismatch happens
  */
  virtual void ResultOfComparison(const CATechMeta      & iRole, 
                                  const unsigned char   & iValBefore, 
                                  const unsigned char   & iValAfter, 
                                  const HRESULT         & iResultOfComparison,
                                  unsigned int            iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const short       & iValBefore, 
                                  const short       & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const int         & iValBefore, 
                                  const int         & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(CATechMeta      & iRole, 
                                  CATLONG64       & iValBefore, 
                                  CATLONG64       & iValAfter, 
                                  const HRESULT   & iResultOfComparison,
                                  unsigned int      iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const float       & iValBefore, 
                                  const float       & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const double      & iValBefore, 
                                  const double      & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta        & iRole, 
                                  const CATUnicodeString  & iValBefore, 
                                  const CATUnicodeString  & iValAfter, 
                                  const HRESULT           & iResultOfComparison,
                                  unsigned int              iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathPoint  & iValBefore, 
                                  const CATMathPoint  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathVector & iValBefore, 
                                  const CATMathVector & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathBox2D  & iValBefore, 
                                  const CATMathBox2D  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta            & iRole, 
                                  const CATMathTransformation & iValBefore, 
                                  const CATMathTransformation & iValAfter, 
                                  const HRESULT               & iResultOfComparison,
                                  unsigned int                  iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATListOfInt  & iValBefore, 
                                  const CATListOfInt  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch) = 0;

  virtual void ResultOfComparison(const CATechMeta      & iRole, 
                                  const CATListOfDouble & iValBefore, 
                                  const CATListOfDouble & iValAfter, 
                                  const HRESULT         & iResultOfComparison,
                                  unsigned int            iLineNoForMismatch) = 0;
};

#endif

