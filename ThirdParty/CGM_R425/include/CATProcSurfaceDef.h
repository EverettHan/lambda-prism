// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Base class designed to handle the procedural definition of a surface based other 
// another surface (CATProcSurface class) 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 00   Creation                                     FBZ
//=============================================================================
#ifndef CATProcSurfaceDef_H
#define CATProcSurfaceDef_H

#include "YP00IMPL.h"                    
#include "CATCGMDefSurface.h"
#include "CATSurLimits.h"
#include "CATSurParamReference.h"

class CATSurface;
class CATMathFunctionXY;
class CATCGMStream;
class CATMathTransformation2D;
//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcSurfaceDef : public CATCGMDefSurface
{
public:

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATProcSurfaceDef(CATSurface* iSurface);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATProcSurfaceDef();
  
  //-------------------------------------------------------------------------
  // Gets the type of ProcSurface
  //-------------------------------------------------------------------------
  enum Type {
    CATProcSurfaceLinear2DType=1
  };
  virtual CATProcSurfaceDef::Type GetType() const = 0;

  //-------------------------------------------------------------------------
  // Create the local equations on a given arc
  // (The returned pointers must be deleted by the caller)
  //-------------------------------------------------------------------------
  virtual void CreateLocalEquation(CATLONG32 iArcIndexU, CATLONG32 iArcIndexV,
                                   CATMathFunctionXY * & oFx,
                                   CATMathFunctionXY * & oFy,
                                   CATMathFunctionXY * & oFz) const = 0;
  //-------------------------------------------------------------------------
  // Gets a pointer toward the reference surface
  //-------------------------------------------------------------------------

  virtual CATSurface* GetSurface() const;

  //-------------------------------------------------------------------------
  // Set a pointer toward the reference surface
  //-------------------------------------------------------------------------
  virtual void SetSurface(CATSurface * iSurface);

  //-------------------------------------------------------------------------
  // Get Limits of the surface
  //-------------------------------------------------------------------------
  virtual void GetLimits(CATSurLimits & oLimits)=0;
  virtual void SetLimits(const CATSurLimits & iLimits, const CATSurParamReference * iRef)=0;
  virtual void GetInternalLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV,
    CATSurLimits & oLimits)=0;

  //-------------------------------------------------------------------------
  // Get Max Limits of the surface
  //-------------------------------------------------------------------------
  virtual void GetMaxLimits(CATSurLimits & oMaxLimits) = 0;
  virtual void GetInternalMaxLimits(const CATLONG32 iPatchU,const CATLONG32 iPatchV,
    CATSurLimits & oLimits) = 0;

  //-------------------------------------------------------------------------
  // Get NumberOfComponent
  //-------------------------------------------------------------------------
  virtual void GetNumberOfComponent( CATLONG32 & oNbOfUPatches, CATLONG32 & oNbOfVPatches) = 0;

  //-------------------------------------------------------------------------
  // Get EquationsSize
  //-------------------------------------------------------------------------
  virtual void GetEquationsSize(int & oIndexOffsetU,
    int & oMaxCountU,
    int & oIndexOffsetV,
    int & oMaxCountV,
    int & oFunctionsSize) = 0 ;

  //-------------------------------------------------------------------------
  // Duplicate this 
  //-------------------------------------------------------------------------
  virtual CATProcSurfaceDef * Duplicate() const = 0;

  //-------------------------------------------------------------------------
  // Apply isometric transformation on the data (not to the surface)
  //-------------------------------------------------------------------------
  virtual void ApplyTransformation(const CATMathTransformation2D & iTransfo);

protected:
  CATSurface*     _Surface;
};

#endif
