#ifndef CATCGMAttrTangentCrvCrvWarning_H
#define CATCGMAttrTangentCrvCrvWarning_H
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  For warning diagnostic on tangent Curve/Curve intersection
//============================================================================
#include "CATCGMAttribute.h"
#include "YP0LOGRP.h"
#include "CATCGMNewArray.h"
#include "CATCrvLimits.h"
class  CATGeoFactory;
class  CATEdgeCurve;


class ExportedByYP0LOGRP CATCGMAttrTangentCrvCrvWarning : public CATCGMAttribute
{
public :
  CATCGMDeclareAttribute(CATCGMAttrTangentCrvCrvWarning,CATCGMAttribute);
  CATCGMNewClassArrayDeclare;
  
  virtual ~CATCGMAttrTangentCrvCrvWarning();

  void       Initialize( CATGeoFactory * iFactory, CATEdgeCurve * iECrv);
  void       Set( CATCrvLimits & iLimits);
  CATEdgeCurve * GetSupport(CATCrvLimits & oLimits);
  CATCGMAttrTangentCrvCrvWarning( CATGeoFactory * iFactory=NULL, CATEdgeCurve * iECrv=NULL);
  CATCGMAttrTangentCrvCrvWarning(const CATCGMAttrTangentCrvCrvWarning& iToCopy);
  CATCGMAttrTangentCrvCrvWarning& operator = (const CATCGMAttrTangentCrvCrvWarning& iToAssign);
  
private :
  
  CATGeoFactory * _Factory;
  CATEdgeCurve *  _ECrv;
  CATCrvLimits    _ECrvLim;
};

#endif
