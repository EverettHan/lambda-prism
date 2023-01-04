/* -*-c++-*- */
#ifndef CATCGMExtGeometry_H
#define CATCGMExtGeometry_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2001
// DESCRIPTION : Default extension for CATTopology Class 
//               BUT Methods are not implemented
//
//=============================================================================
#include "CATGeometry.h"
#include "CATICGMObjectInterface.h"
#include "YP00IMPL.h"

class CATSurLimits;
class CATCrvLimits;

class ExportedByYP00IMPL CATCGMExtGeometry: public CATBaseUnknown
{
public:
    // -- adhesion a l'interface CATICGMObject ------------------------------
    CATICGMObjectInterface;
	
    // -- adhesion a l'interface CATGeometry ------------------------------
	virtual void         GetBoundingBox(CATMathBox & ioBox) const;
	virtual CATMathBox   GetBoundingBox() const;
	virtual void         Move3D(CATTransfoManager& iTransfo);
	virtual CATGeometry *CloneAndMove3D(CATTransfoManager& iTransfo);
	virtual CATBoolean   IsDeepConfused(CATTransfoManager & iTransfo,const CATGeometry* iTGeometry) const;
	virtual void         ApplyTransformation (const CATMathTransformation &iTranfoToApply);
	
    // -- Constructor - Destructor ------------------------------
    CATCGMExtGeometry();
    virtual ~CATCGMExtGeometry();

  virtual void NoDefaultImplemention(const char MethodName[]="") const;

};

#endif
