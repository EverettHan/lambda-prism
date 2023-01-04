//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021
//=============================================================================
//
// MathStream
//
// Under Poly namespace, contains basic stream method for basic math objects
//
//=============================================================================
// 08/21 : F1Z : Creation
//=============================================================================

#pragma once

#include "CATMathStream.h"

namespace Poly
{
  template<typename T>
  HRESULT Stream(CATMathStream& ioStream, const T& iToStream)
  {
    return E_NOTIMPL;
  }

  template<typename T>
  HRESULT Unstream(CATMathStream& ioStream, T& oUnstreamed)
  {
    return E_NOTIMPL;
  }
}

template<>
inline HRESULT Poly::Stream(CATMathStream& ioStream, const int& iToStream)
{
  ioStream.WriteLong((CATLONG32)iToStream);
  return S_OK;
}

template<>
inline HRESULT Poly::Unstream(CATMathStream& ioStream, int & oUnstreamed)
{
  ioStream.ReadLong((CATLONG32&)oUnstreamed);
  return S_OK;
}

template<>
inline HRESULT Poly::Stream(CATMathStream& ioStream, const double& iToStream)
{
  ioStream.WriteDouble(iToStream);
  return S_OK;
}

template<>
inline HRESULT Poly::Unstream(CATMathStream& ioStream, double& oUnstreamed)
{
  ioStream.ReadDouble(oUnstreamed);
  return S_OK;
}




