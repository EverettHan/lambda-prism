#ifndef CATExpFPExpansion_H
#define CATExpFPExpansion_H

#include "CATMathExactPredicates.h"

#include <memory>
#include <cstring>
#include <algorithm>

class CATExpFPExpansion final
{
public:
  CATExpFPExpansion() = default;
  ExportedByCATMathExactPredicates explicit CATExpFPExpansion(double x);

  ExportedByCATMathExactPredicates CATExpFPExpansion(CATExpFPExpansion const&) = default;
  ExportedByCATMathExactPredicates CATExpFPExpansion(CATExpFPExpansion &&) = default;
  ExportedByCATMathExactPredicates CATExpFPExpansion& operator=(CATExpFPExpansion const&) = default;
  ExportedByCATMathExactPredicates CATExpFPExpansion& operator=(CATExpFPExpansion &&) = default;

  ExportedByCATMathExactPredicates ~CATExpFPExpansion() = default;

  double const& operator[](int i) const;

  int Size() const;

  ExportedByCATMathExactPredicates static CATExpFPExpansion Sum(double x, double y);
  ExportedByCATMathExactPredicates static CATExpFPExpansion Sub(double x, double y);
  ExportedByCATMathExactPredicates static CATExpFPExpansion Mult(double x, double y);

  ExportedByCATMathExactPredicates friend CATExpFPExpansion operator+(CATExpFPExpansion const& x, CATExpFPExpansion const& y);
  ExportedByCATMathExactPredicates friend CATExpFPExpansion operator-(CATExpFPExpansion const& x, CATExpFPExpansion y);
  ExportedByCATMathExactPredicates friend CATExpFPExpansion operator*(double x, CATExpFPExpansion const& y);

private:
  explicit CATExpFPExpansion(int n);

  template<class IntegralValue>
  explicit CATExpFPExpansion(IntegralValue const&);

  static CATExpFPExpansion FastSum(double x, double y);
  
  void Renormalize();
  void VecSum();
  void VecSumErrBranch();
  void VecSumErr();

  CATExpFPExpansion ScaleExpansion(double x) const;

  class StaticVector : private std::allocator<double>
  {
  public:
    StaticVector()
      : _begin(_staticBuffer)
      , _end(_staticBuffer)
      , _last(_staticBuffer + 4)
    {}

    StaticVector(int iSize, double iValue = 0.)
      : StaticVector()
    {
      Reserve<false>(iSize);
      std::fill_n(_begin, iSize, iValue);
      _end = _begin + iSize;
    }

    template<class IntegralValue>
    StaticVector(IntegralValue const&)
      : StaticVector()
    {
      constexpr int Size = IntegralValue::value;
      if constexpr (Size > StaticSize)
      {
        Reserve<false>(Size);
      }

      std::memset(_begin, 0, Size * sizeof(double));
      _end = _begin + Size;
    }

    ~StaticVector()
    {
      if (!UseStaticBuffer())
        deallocate(_begin, _last - _begin);
    }

    StaticVector(StaticVector const& iV)
      : StaticVector()
    {
      operator=(iV);
    }

    StaticVector& operator=(StaticVector const& iV)
    {
      if (this != &iV)
      {
        auto const size = iV._end - iV._begin;
        Reserve<false>(size);
        std::memcpy(_begin, iV._begin, size * sizeof(double));
        _end = _begin + size;
      }
      return *this;
    }

    StaticVector(StaticVector &&iV)
    {
      if (iV.UseStaticBuffer())
      {
        auto const size = iV._end - iV._begin;
        _begin = _staticBuffer;
        _end = _staticBuffer + size;
        _last = _staticBuffer + 4;
        std::memcpy(_begin, iV._begin, size * sizeof(double));
      }
      else
      {
        _begin = iV._begin;
        _end = iV._end;
        _last = iV._last;

        iV._begin = iV._staticBuffer;
        iV._end = iV._staticBuffer;
        iV._last = iV._staticBuffer + 4;
      }
    }

    StaticVector& operator=(StaticVector &&iV)
    {
      if (iV.UseStaticBuffer())
      {
        auto const size = iV._end - iV._begin;
        std::memcpy(_begin, iV._begin, size * sizeof(double));
        _end = _begin + size;
      }
      else if (UseStaticBuffer())
      {
        _begin = iV._begin;
        _end = iV._end;
        _last = iV._last;

        iV._begin = iV._staticBuffer;
        iV._end = iV._staticBuffer;
        iV._last = iV._staticBuffer + 4;
      }
      else
      {
        std::swap(_begin, iV._begin);
        std::swap(_end, iV._end);
        std::swap(_last, iV._last);
      }
      return *this;
    }

    double const& operator[](int i) const
    {
      return _begin[i];
    }

    double& operator[](int i)
    {
      return _begin[i];
    }

    std::size_t size() const
    {
      return _end - _begin;
    }

    std::size_t capacity() const
    {
      return _last - _begin;
    }

    double const* begin() const
    {
      return _begin;
    }

    double const* end() const
    {
      return _end;
    }

    double* begin()
    {
      return _begin;
    }

    double* end()
    {
      return _end;
    }

    void erase(double *iStart, double *iEnd)
    {
      std::size_t nBack = _end - iEnd;
      std::memmove(iStart, iEnd, nBack);
      _end = iStart + nBack;
    }

    double const& front() const
    {
      return *_begin;
    }

    double& front()
    {
      return *_begin;
    }

    double const& back() const
    {
      return *(_end - 1);
    }

    double& back()
    {
      return *(_end - 1);
    }

  private:
    bool UseStaticBuffer() const
    {
      return _staticBuffer == _begin;
    }

    template<bool CopyData>
    void Reserve(std::size_t iSize)
    {
      std::size_t const currentCapacity = _last - _begin;
      if (iSize <= currentCapacity)
        return;

      auto const allocatedSize = std::max(iSize, (3 * currentCapacity) / 2);
      double* newBuffer = static_cast<double*>(allocate(allocatedSize));
      if constexpr (CopyData)
      {
        std::size_t const currentSize = _end - _begin;
        std::memcpy(newBuffer, _begin, currentSize);
        _end = newBuffer + currentSize;
      }
      else
      {
        _end = newBuffer;
      }

      if (!UseStaticBuffer())
        deallocate(_begin, _last - _begin);
      _begin = newBuffer;
      _last = newBuffer + allocatedSize;
    }

    static const std::size_t StaticSize = 5;

    double _staticBuffer[StaticSize];
    double* _begin;
    double* _end;
    double* _last;
  };

  StaticVector _expansion;
};

inline int CATExpFPExpansion::Size() const
{
  return static_cast<int>(_expansion.size());
}

inline CATExpFPExpansion::CATExpFPExpansion(double x)
  : _expansion(1, x)
{
}

inline CATExpFPExpansion::CATExpFPExpansion(int n)
  : _expansion(n)
{
}

template<class IntegralValue>
inline CATExpFPExpansion::CATExpFPExpansion(IntegralValue const& iIntegralValue)
  : _expansion(iIntegralValue)
{
}

inline double const& CATExpFPExpansion::operator[](int i) const
{
  return _expansion[i];
}

#endif
