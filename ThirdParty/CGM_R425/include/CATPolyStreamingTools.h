// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyStreamingTools.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// Sept 2009  Creation: ZFI
//===================================================================

#ifndef CATPolyStreamingTools_H
#define CATPolyStreamingTools_H

#include "PolyMathUtils.h"
#include "CATErrorDef.h"

class CATMathStream;

class CATMathPoint2D;
class CATMathPoint;
class CATMathVector;

class ExportedByPolyMathUtils CATPolyStreamingTools
{
public:
  CATPolyStreamingTools();
  virtual ~CATPolyStreamingTools();

  //positions quantization
  static HRESULT QuantifyPoint(const CATMathPoint& iPoint, const CATMathPoint& iRefPoint, const double iPrecision, 
                               unsigned int& oX, unsigned int& oY, unsigned int& oZ);

  static HRESULT UnQuantifyPoint(const unsigned int iX, const unsigned int iY, const unsigned int iZ, 
                                 const CATMathPoint& iRefPoint, const double iPrecision,
                                 CATMathPoint& oP);

  //uv quantization
  static HRESULT QuantifyUVCoord(const CATMathPoint2D& iPoint, const CATMathPoint2D& iRefPoint2D, const double iPrecision, 
                                 unsigned int& oX, unsigned int& oY);
  
  static HRESULT UnQuantifyUVCoord(const unsigned int iX, const unsigned int iY, 
                                   const CATMathPoint2D& iRefPoint2D, const double iPrecision,
                                   CATMathPoint2D& oP);

  //vector quantization
  static HRESULT QuantifyVector(const CATMathVector& iVector,
                                unsigned int& oX, unsigned int& oY);

  static HRESULT UnQuantifyVector(const unsigned int iX, const unsigned int iY,
                                  CATMathVector& oVector);

  
  static HRESULT QuantifyVector(const CATMathVector& iVector,unsigned int& oX);

  static HRESULT UnQuantifyVector(const unsigned int iX, CATMathVector& oVector);


  //axis transfo, angles, vectors..
  static HRESULT GetSphericalAngles(const CATMathVector& iU, double& oTheta, double& oPhi);
  static HRESULT GetVector(const double iTheta, const double iPhi, CATMathVector& oU);
  //static HRESULT GetEulerAngles(const CATMathVector& iU, const CATMathVector& iV, const CATMathVector& iW, 
  //                              double& oTheta, double& oPhi, double& oPsi);
  //static HRESULT GetAxis(const double iPhi, const double iTheta, const double iPsi,
  //                       CATMathVector& oU, CATMathVector& oV, CATMathVector& oW);

  //basic types quantization
  static HRESULT QuantifyFloat(const float iX, unsigned int& oX);
  static HRESULT UnQuantifyFloat(const unsigned int iX, float& oX);

  //bits
  static HRESULT Bits2UInt(unsigned int iNbBits, unsigned char* iBits, unsigned int& oX);

  static HRESULT UInt2Bits(const unsigned int iX, unsigned int iNbBits, unsigned char* ioBits);                       
};

#endif
