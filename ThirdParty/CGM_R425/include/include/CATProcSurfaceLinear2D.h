// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle the procedural definition of a surface defined
// by the transformation in 2D (u,v)  of a surface
//
// iTransfo : transformation 2D donnee en entree
// iLimits  : boite d'entree en (u,v) a partir de laquelle sont definies les
//            Max Limits de la ProcSurface
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 00 Creation                                                      FBZ
// Aug. 11 Added the function GetOriginalLimits().                       R1Y
//=============================================================================
#ifndef CATProcSurfaceLinear2D_H
#define CATProcSurfaceLinear2D_H

#include "YP00IMPL.h"                    

#include "CATProcSurfaceDef.h"
#include "CATMathDef.h"
#include "CATMathTransformation2D.h"
#include "CATSurLimits.h"

class CATSurface;
class CATMathFunctionXY;
class CATSurParamReference;


//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATProcSurfaceLinear2D : public CATProcSurfaceDef
{
public:
	
	//-------------------------------------------------------------------------
	// Constructors
	//-------------------------------------------------------------------------
	CATProcSurfaceLinear2D(CATSurface* iSurface,
		const CATMathTransformation2D& iTransfo,
    const CATSurLimits& iLimits);
	
	CATProcSurfaceLinear2D(CATSurface* iSurface);
	//-------------------------------------------------------------------------
	// virtual Destructor
	//-------------------------------------------------------------------------
	~CATProcSurfaceLinear2D();
	
	//-------------------------------------------------------------------------
	// Gets the type of procsurface
	//-------------------------------------------------------------------------
	CATProcSurfaceDef::Type GetType() const;
	
  //-------------------------------------------------------------------------
  //  Check Input Limits
  //-------------------------------------------------------------------------
  int CheckInputLimits();

  //-------------------------------------------------------------------------
  // Get transfo
  //-------------------------------------------------------------------------
  void GetTransfo(CATMathTransformation2D & oTransfo);

  //-------------------------------------------------------------------------
  // Get Limits of the surface
  //-------------------------------------------------------------------------
  void GetLimits(CATSurLimits & oLimits);
  void SetLimits(const CATSurLimits & iLimits, const CATSurParamReference * iRef);
  void GetInternalLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV,
    CATSurLimits & oLimits);

  //-------------------------------------------------------------------------
  // Get Max Limits of the surface
  //-------------------------------------------------------------------------
  void GetMaxLimits(CATSurLimits & oMaxLimits);
  void GetInternalMaxLimits(const CATLONG32 iPatchU,const CATLONG32 iPatchV,
    CATSurLimits & oLimits);
  void GetOriginalLimits(CATSurLimits & oOriginalLimits);

  //-------------------------------------------------------------------------
  // Get NumberOfComponent
  //-------------------------------------------------------------------------
  void GetNumberOfComponent( CATLONG32 & oNbOfUPatches, CATLONG32 & oNbOfVPatches);
 
  //-------------------------------------------------------------------------
  // Get equations size
  //-------------------------------------------------------------------------
  void GetEquationsSize(int & oIndexOffsetU,
    int & oMaxCountU,
    int & oIndexOffsetV,
    int & oMaxCountV,
    int & oFunctionsSize) ;

	//-------------------------------------------------------------------------
	// Create the local equations on a given patch
  // (The returned pointers must be deleted by the caller)
	//-------------------------------------------------------------------------
	void CreateLocalEquation(CATLONG32 iArcIndexU, CATLONG32 iArcIndexV,
		CATMathFunctionXY * & oFx,
		CATMathFunctionXY * & oFy,
		CATMathFunctionXY * & oFz) const;
	//-------------------------------------------------------------------------
	// For Streaming
	//-------------------------------------------------------------------------
	void Stream( CATCGMStream& Str ) ;
	void UnStream( CATCGMStream& Str ) ;
  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
	
	
	//-------------------------------------------------------------------------
	// Duplicate this 
	//-------------------------------------------------------------------------
	CATProcSurfaceDef * Duplicate() const;
	
	void ApplyTransformation(const CATMathTransformation2D & iTransfo);
	
	
protected:
	CATMathTransformation2D _Transfo;
  CATSurLimits _Limits, _CurrentLimits;
  int          _ToUnlock;
};

#endif
