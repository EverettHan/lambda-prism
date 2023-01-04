#ifndef CATCGMAttrIsopar_H
#define CATCGMAttrIsopar_H
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  For Performance improvement on  Intersection Face/Face with ProcOffsetSurface
//============================================================================
#include "CATCGMAttribute.h"
#include "YP0LOGRP.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATSurLimits.h"
#include "CATMathInline.h"
class  CATGeoFactory;
class  CATCurve;
class  CATSurface;


class ExportedByYP0LOGRP CATCGMAttrIsopar : public CATCGMAttribute
{
public :
  CATCGMDeclareAttribute(CATCGMAttrIsopar,CATCGMAttribute);
  CATCGMNewClassArrayDeclare;
  
  CATCGMAttrIsopar(CATCGMAttrIsopar* iNext=NULL);
  virtual ~CATCGMAttrIsopar();

  void       Initialize( CATGeoFactory * iFactory, CATSurface * _Surf);
  void       Set( CATSurLimits & iLimits,  CATCurve * iCurves[4] );
  CATCGMAttrIsopar*    Locate(CATSurface * iSurf, CATSurLimits & iLimits);
  CATBoolean Get( CATSurface * iSurf, CATSurLimits & iLimits, CATCurve * oCurves[4]);
  INLINE     CATSurface * GetSupport(){ return _Surf; };

  CATCGMAttrIsopar(const CATCGMAttrIsopar& iToCopy);
  CATCGMAttrIsopar& operator = (const CATCGMAttrIsopar& iToAssign);
  
private :
  
  CATGeoFactory * _Factory;
  CATCurve *      _Curves[4];
  CATSurLimits    _Surlim;
  CATSurface *    _Surf;
  CATCGMAttrIsopar * _next, * _previous;
};

#endif
