#ifndef CATCGMAttrTopData_H_
#define CATCGMAttrTopData_H_
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  For c:topcgm Command to compare Feature with Body Result
//============================================================================
#include <stdlib.h>
#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMAttribute.h"
#include "CATTopData.h"
#include "CATMathInline.h"


class ExportedByCATTopologicalObjects CATCGMAttrTopData : public CATCGMAttribute
{
public :
  CATCGMDeclareAttribute(CATCGMAttrTopData,CATCGMAttribute);

  CATCGMAttrTopData() {}; 
  CATCGMAttrTopData(const CATCGMAttrTopData& iToCopy) {}; 
  CATCGMAttrTopData& operator = (const CATCGMAttrTopData& iToAssign) { return *this; }; 
  ~CATCGMAttrTopData() {}; 
  
  INLINE void                      GetTopData(CATTopData& oTopData) const;
  INLINE CATSoftwareConfiguration* GetSoftwareConfiguration() const;
  INLINE char* const               GetIdentifier() const;  
};


INLINE void CATCGMAttrTopData::GetTopData(CATTopData& oTopData) const
{
}

INLINE char* const CATCGMAttrTopData::GetIdentifier() const
{
  return NULL;
}

INLINE CATSoftwareConfiguration* CATCGMAttrTopData::GetSoftwareConfiguration() const
{
  return NULL;
}


#endif
