// CATOptParam.h
// Header definition of the CATOptParam class
//

#ifndef CATOptParam_h
#define CATOptParam_h
#include "YN000OPT.h"
#include "CATString.h"
#include "CATDataType.h"
#include "CATOptTypes.h"

//-----------------------------------------------------------------------

class ExportedByYN000OPT  CATOptParam
{
public:

  CATOptParam();
  CATOptParam(CATBoolean iValue);
  CATOptParam(CATLONG32  iValue);
  CATOptParam(CATULONG32 iValue);
  CATOptParam(CATOptReal iValue);
  CATOptParam(CATULONG32 iValueNb,CATOptReal * iValue);
  CATOptParam(CATOptSparseMode iValue);
  CATOptParam(CATOptAcceleratorMode iValue);
  CATOptParam(CATOptMethodId iValue);
  CATOptParam(CATClusteringMethodId iValue);
  ~CATOptParam();

  CATOptParam(const CATOptParam & iValue);
  CATOptParam & operator = (const CATOptParam & iValue);

  CATOptParamType GetType() const;
  HRESULT GetParam(CATBoolean & oValue) const;
  HRESULT GetParam(CATLONG32  & oValue) const;
  HRESULT GetParam(CATULONG32 & oValue) const;
  HRESULT GetParam(CATOptReal & oValue) const;
  HRESULT GetParam(CATULONG32 & oValueNb,CATOptReal *& oValue) const;
  HRESULT GetParam(CATOptSparseMode & oValue) const;
  HRESULT GetParam(CATOptAcceleratorMode & oValue) const;
  HRESULT GetParam(CATOptMethodId & oValue) const;
  HRESULT GetParam(CATClusteringMethodId & oValue) const;

  void SetParam(const CATBoolean  iValue);
  void SetParam(const CATLONG32   iValue);
  void SetParam(const CATULONG32  iValue);
  void SetParam(const CATOptReal  iValue) ;
  // The method creates the pointers on the CATOptReal which contain the values of the input array.
  // WARNING :It is left to the caller to delete them !!!!
  void SetParam(const CATULONG32  iValueNb,CATOptReal * iValue);
  void SetParam(const CATOptSparseMode  iValue);
  void SetParam(const CATOptAcceleratorMode  iValue);
  void SetParam(const CATOptMethodId  iValue);
  void SetParam(const CATClusteringMethodId  iValue);

private:
  void init();
  void reset();
   // data
private:
  CATOptParamType _type;
  CATBoolean _bParam;
  int _lParam;
  CATULONG32 _ulParam;
  CATOptReal _rParam;
  CATULONG32 _ParamNb;
  CATOptReal * _prParam;
  CATOptSparseMode _sparseParam;
  CATOptAcceleratorMode _acceleratorParam;
  CATOptMethodId _omParam;
  CATClusteringMethodId _cmParam;
};
//-----------------------------------------------------------------------

#endif
