/* -*-C++-*- */
#ifndef CATTrdDic_H
#define CATTrdDic_H
// COPYRIGHT DASSAULT SYSTEMES 2015

//===================================================================
//===================================================================
//
// CATTrdDic: Dictionary for a CATTrdSSet
//
//===================================================================
//===================================================================
// May 2015    Creation                         R. Rorato
//===================================================================
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATLISTV_CATMathVector.h"
#include "CATListOfInt.h"
#include "CATListPV.h"

class CATMathPoint;
class CATMathVector;

class ExportedByCATMathematics CATTrdDic : public CATCGMVirtual
{
  public:
  CATTrdDic();
  ~CATTrdDic();
  CATCGMNewClassArrayDeclare;        // Pool allocation

  //------------------------------------------------------------------------------
  int Add(const CATMathPoint& iPoint);
  int Add(const CATMathVector& iVector);
  //------------------------------------------------------------------------------
  void Read(const int iIndex, CATMathPoint& oPoint);
  void Read(const int iIndex, CATMathVector& oVector);
  //------------------------------------------------------------------------------
  void Stream(unsigned char*& oStream, int& ioStreamPosition);
  int GetStreamSize();
  CATTrdDic(unsigned char* iStream, int& ioStreamPosition);
  //------------------------------------------------------------------------------
  void Dump(ostream& oStream) const;
  //------------------------------------------------------------------------------

private:
  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
  CATLISTV(CATMathPoint)  _Points;
  CATLISTV(CATMathVector) _Vectors;
  //------------------------------------------------------------------------------

};

#endif
