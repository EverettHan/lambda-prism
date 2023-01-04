#ifndef CATechRefObserver_h
#define CATechRefObserver_h

// Mathematics
#include "CATIRefObserver.h"
#include "ExportedByCATTechTools.h"

/*
* @COPYRIGHT DASSAULT SYSTEMES 2012
* -------------------------------------------------------------------------------------------------
* CATechRefObserver : Base class for the observers that the extension has to implement 
*                     for getting notifications for wrong entries during the reference check
*                     mechanism at the time of phoenix replay
* NOTE : All the methods have empty implementation and thus the derived observers have to
*        implement each according to their requirement. Done like this so that observers have
*        to implement the methods relevant to them only and not worry about others
* -------------------------------------------------------------------------------------------------
*/

class ExportedByCATTechTools CATechRefObserver : public CATIRefObserver
{
public:
  virtual void ResultOfComparison(const CATechMeta      & iRole, 
                                  const unsigned char   & iValBefore, 
                                  const unsigned char   & iValAfter, 
                                  const HRESULT         & iResultOfComparison,
                                  unsigned int            iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const short       & iValBefore, 
                                  const short       & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const int         & iValBefore, 
                                  const int         & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch);

  virtual void ResultOfComparison(CATechMeta      & iRole, 
                                  CATLONG64       & iValBefore, 
                                  CATLONG64       & iValAfter, 
                                  const HRESULT   & iResultOfComparison,
                                  unsigned int      iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const float       & iValBefore, 
                                  const float       & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta  & iRole, 
                                  const double      & iValBefore, 
                                  const double      & iValAfter, 
                                  const HRESULT     & iResultOfComparison,
                                  unsigned int        iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta        & iRole, 
                                  const CATUnicodeString  & iValBefore, 
                                  const CATUnicodeString  & iValAfter, 
                                  const HRESULT           & iResultOfComparison,
                                  unsigned int              iLineNoForMismatch); 

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathPoint  & iValBefore, 
                                  const CATMathPoint  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathVector & iValBefore, 
                                  const CATMathVector & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATMathBox2D  & iValBefore, 
                                  const CATMathBox2D  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta            & iRole, 
                                  const CATMathTransformation & iValBefore, 
                                  const CATMathTransformation & iValAfter, 
                                  const HRESULT               & iResultOfComparison,
                                  unsigned int                  iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta    & iRole, 
                                  const CATListOfInt  & iValBefore, 
                                  const CATListOfInt  & iValAfter, 
                                  const HRESULT       & iResultOfComparison,
                                  unsigned int          iLineNoForMismatch);

  virtual void ResultOfComparison(const CATechMeta      & iRole, 
                                  const CATListOfDouble & iValBefore, 
                                  const CATListOfDouble & iValAfter, 
                                  const HRESULT         & iResultOfComparison,
                                  unsigned int            iLineNoForMismatch);
};

#endif
