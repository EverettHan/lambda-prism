#ifndef CATDynBooleanSharedFaceData_H
#define CATDynBooleanSharedFaceData_H

#include "CATMathInline.h"
#include "CATUnicodeString.h"

class CATFace;
class CATVolume;

class CATCGMOutput;
class CATCGMStream;

#include "BOOLEAN.h"

// --------------------------------------------------------------------------------------------
// Type of operation that should be applied to some volume
// (who shares at least one face with another volume of the same Operand in the same Operator)
// --------------------------------------------------------------------------------------------
enum AdjVolOperationType
{
  Inverse   = -1,
  Nothing   = 0,
  Normal    = 1
};

class ExportedByBOOLEAN CATDynBooleanSharedFaceData
{
public:
  CATDynBooleanSharedFaceData(CATFace* ipSharedFace,
    CATVolume* ipVolume1, AdjVolOperationType ipOperTypeOnVol1,
    CATVolume* ipVolume2, AdjVolOperationType ipOperTypeOnVol2);

  ~CATDynBooleanSharedFaceData();

  static CATDynBooleanSharedFaceData* ReadFromStream(CATCGMStream& ioStr);
  void WriteToStream(CATCGMStream& ioStr);

  void ResetDebugIDs();

  CATFace*    GetSharedFace()   const;
  CATVolume*  GetVolume1()      const;
  AdjVolOperationType GetOperType1()  const;
  CATVolume*  GetVolume2()      const;
  AdjVolOperationType GetOperType2()  const;
  AdjVolOperationType GetOperTypeOnVolume(CATVolume* ipVolume)  const;

  void SetSharedFace(CATFace* ipFace);
  void SetVolume1(CATVolume* ipVolume, AdjVolOperationType ipOperType);
  void SetVolume1(CATVolume* ipVolume);
  void SetOperTypeOnVol1(AdjVolOperationType ipOperType);
  void SetVolume2(CATVolume* ipVolume, AdjVolOperationType ipOperType);
  void SetVolume2(CATVolume* ipVolume);
  void SetOperTypeOnVol2(AdjVolOperationType ipOperType);

  void DumpInOneLine(CATCGMOutput& ioOutput) const;
  void Dump(CATCGMOutput& ioOutput, CATUnicodeString iLinePrefix = "") const;

private:

  static int              _DEBUG_NextDataId;
  int                     _DEBUG_Id;

  CATFace               * _pSharedFace;
  CATVolume             * _pVolume1;
  AdjVolOperationType     _pOperTypeOnVol1;
  CATVolume             * _pVolume2;
  AdjVolOperationType     _pOperTypeOnVol2;
};


INLINE void CATDynBooleanSharedFaceData::ResetDebugIDs()
{
  _DEBUG_NextDataId = 0;
}

INLINE CATFace* CATDynBooleanSharedFaceData::GetSharedFace() const
{
  return _pSharedFace;
}

INLINE CATVolume* CATDynBooleanSharedFaceData::GetVolume1() const
{
  return _pVolume1;
}

INLINE AdjVolOperationType CATDynBooleanSharedFaceData::GetOperType1() const
{
  return _pOperTypeOnVol1;
}

INLINE CATVolume* CATDynBooleanSharedFaceData::GetVolume2() const
{
  return _pVolume2;
}

INLINE AdjVolOperationType CATDynBooleanSharedFaceData::GetOperType2() const
{
  return _pOperTypeOnVol2;
}

INLINE void CATDynBooleanSharedFaceData::SetSharedFace(CATFace* ipFace)
{
  _pSharedFace = ipFace;
}

INLINE void CATDynBooleanSharedFaceData::SetVolume1(CATVolume* ipVolume, AdjVolOperationType ipOperType)
{
  _pVolume1         = ipVolume;
  _pOperTypeOnVol1  = ipOperType;
}

INLINE void CATDynBooleanSharedFaceData::SetVolume1(CATVolume* ipVolume)
{
  _pVolume1 = ipVolume;
}

INLINE void CATDynBooleanSharedFaceData::SetOperTypeOnVol1(AdjVolOperationType ipOperType)
{
  _pOperTypeOnVol1 = ipOperType;
}

INLINE void CATDynBooleanSharedFaceData::SetVolume2(CATVolume* ipVolume, AdjVolOperationType ipOperType)
{
  _pVolume2         = ipVolume;
  _pOperTypeOnVol2  = ipOperType;
}

INLINE void CATDynBooleanSharedFaceData::SetVolume2(CATVolume* ipVolume)
{
  _pVolume2 = ipVolume;
}

INLINE void CATDynBooleanSharedFaceData::SetOperTypeOnVol2(AdjVolOperationType ipOperType)
{
  _pOperTypeOnVol2 = ipOperType;
}


#endif // CATDynBooleanSharedFaceData_H
