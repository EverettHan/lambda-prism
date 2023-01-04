#ifndef CATTransformationHolder_H
#define CATTransformationHolder_H

#include "CATGMOperatorsInterfaces.h"  
#include "CATBaseUnknown.h"
#include "CATBoolean.h"

class CATBody;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMOperatorsInterfaces IID IID_CATTransformationHolder;
#else
extern "C" const IID IID_CATTransformationHolder;
#endif

class ExportedByCATGMOperatorsInterfaces CATTransformationHolder : public CATBaseUnknown

{
CATDeclareInterface;
 public :
/**
 * Identify an objet as holding a CATTransformation objet
 *   Dedicated to Sheet Metal architecture of V5 R8
 * for empty Body (referenced by a Feature) 
 *  holding an attribute for a Transformation
 */
  virtual CATBoolean HasTransformation() const = 0;
};

CATDeclareHandler(CATTransformationHolder,CATBaseUnknown);
#endif
