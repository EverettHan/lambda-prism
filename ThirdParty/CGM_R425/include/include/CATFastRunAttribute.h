#ifndef CATFastRunAttribute_H
#define CATFastRunAttribute_H

#include "ExportedByCATTopologicalObjects.h"                  
#include "CATCGMStreamAttribute.h"                                 
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATStreamTool.h"
#include "CATCGMAttrId.h"

#define CATDeclareFastRunAttribute(iChild, iParent) \
  CATCGMDeclareAttribute(iChild, iParent); \
  static iChild * Cast(CATCGMAttribute * iToCast);

#define CATImplFastRunAttribute(iChild, iParent) \
  CATCGMImplAttribute(iChild,iParent,FastRun,1); \
  iChild * iChild::Cast(CATCGMAttribute * iToCast) \
  { \
    return ((iToCast && iToCast->IsATypeOf(iChild::GetId())) ? ((iChild *)iToCast) : NULL); \
  }

class CATBody;

class ExportedByCATTopologicalObjects CATFastRunAttribute : public CATCGMStreamAttribute
{
  CATDeclareFastRunAttribute(CATFastRunAttribute, CATCGMStreamAttribute);

public :
  
  CATFastRunAttribute();

  virtual ~CATFastRunAttribute();

  void CreateBuffer(size_t iEstimatedBufferSize = 512);

  void FillBuffer(StreamingFunction iWritingFunction, void * iAdditionalObject);

  void InterpretBuffer(StreamingFunction iReadingFunction, void * iAdditionalObject);

  static CATFastRunAttribute * GetFastRunAttributeOnBody(CATBody * iBody);

  static CATBoolean AttributesAreIdentical(CATFastRunAttribute & iAttribute1, CATFastRunAttribute & iAttribute2);

  static int GetNumberOfStartingEqualBytes(CATFastRunAttribute & iAttribute1, CATFastRunAttribute & iAttribute2);

protected:

  virtual void Stream(CATCGMStream&) const;

  virtual void UnStream(CATCGMStream&);

  virtual CATBoolean IsIdenticalTo(CATFastRunAttribute & iOther);

private :

  CATFastRunAttribute(const CATFastRunAttribute &);

  CATStreamTool _StreamTool;

};

#endif
