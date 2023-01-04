// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphDataVector.h
//
//===================================================================
// January  Creation JBS2
//===================================================================
#ifndef CATPolyBodyBarGraphDataVector_H
#define CATPolyBodyBarGraphDataVector_H

#include "CATErrorDef.h"
#include "CATUnicodeString.h"


class CATPolyBodyBarGraphDataVector;

class CATPolyBodyBarGraphDataVector
{
public:
  enum DataType
  {
    Unknown = 1,
    Normal = 2,
    Texture = 4,
    All = Unknown | Normal | Texture
  };

public:
  static CATPolyBodyBarGraphDataVector *New(unsigned int iSize, unsigned int iDimension, DataType iDataType, const CLSID &iClassId, const CATUnicodeString &iIdentifier, CATBoolean iConstraint);
  virtual ~CATPolyBodyBarGraphDataVector() = 0;

public:
  virtual unsigned int Size() const = 0;
  virtual unsigned int GetDimension() const = 0;
  inline DataType GetDataType() const { return _DataType; };
  inline CLSID GetClassId() const { return _ClassId; };
  inline CATUnicodeString GetIdentifier() const { return _Identifier; };
  inline CATBoolean IsDataType(DataType type) const { return _DataType & type; };
  inline CATBoolean IsConstraint() const { return _Constraint; };

public:
  virtual const double *operator[](unsigned int index) const = 0;
  virtual double *operator[](unsigned int index) = 0;

protected:
  CATPolyBodyBarGraphDataVector(DataType iDataType, const CLSID &iClassId, const CATUnicodeString &iIdentifier, CATBoolean iConstraint);

protected:
  /**
   * Return the next unused cut id  (extends layer if needed).
   * @param oCutId
   *   The new identifier.
   */
  HRESULT GetNewCutId(unsigned int& oCutId);
  virtual HRESULT Resize(unsigned int iSize) = 0;

private:
  const DataType _DataType;
  const CLSID _ClassId;
  const CATUnicodeString _Identifier;
  const CATBoolean _Constraint;

private:
  friend class CATPolyBodyBarGraphSurfaceDataLayer;
};


#endif
