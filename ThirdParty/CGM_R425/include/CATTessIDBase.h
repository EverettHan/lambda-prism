// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessIDBase
//
//===================================================================
//
// June 2011  Creation: MPX
//===================================================================
#ifndef CATTessIDBase_H
#define CATTessIDBase_H

#include "CATGMModelInterfaces.h"

class CATTessIDClassic;
class CATTessIDUV;

enum CATTessIDClassType
{
  CATTessIDClassicType,
  CATTessIDUVType
};

class ExportedByCATGMModelInterfaces CATTessIDBase
{
public:
  virtual ~CATTessIDBase();

  virtual int GetHashCode () const = 0;
  virtual CATTessIDClassType GetType() const = 0;
  virtual const CATTessIDBase* Clone() const = 0;

  int operator == (const CATTessIDBase& iRHS) const;
  int operator != (const CATTessIDBase& iRHS) const;
  int operator < (const CATTessIDBase& iRHS) const;

protected:
  virtual int IsEqualTo(const CATTessIDBase& iRHS) const = 0;
  virtual int IsLessThan(const CATTessIDBase& iRHS) const = 0;
};

#endif // CATTessIDBase_H


