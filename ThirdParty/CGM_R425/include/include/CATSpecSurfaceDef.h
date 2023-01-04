// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Base class designed to handle the definition of a spec surface 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Aug. 00   Creation                                     fbz
//=============================================================================
#ifndef CATSpecSurfaceDef_H
#define CATSpecSurfaceDef_H

#include "YP00IMPL.h"                    
#include "CATCGMDefSurface.h"
#include "CATMathTransformation.h"

class CATSurface;
class CATCGMStream;
class CATCGMOutput;
class CATGeometry;

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATSpecSurfaceDef : public CATCGMDefSurface
{
public:
	
	//-------------------------------------------------------------------------
	// Constructors
	//-------------------------------------------------------------------------
	CATSpecSurfaceDef();
	CATSpecSurfaceDef(CATSurface * iSurface);
  CATSpecSurfaceDef(const CATSpecSurfaceDef & iFrom);

	//-------------------------------------------------------------------------
	// virtual Destructor
	//-------------------------------------------------------------------------
	virtual ~CATSpecSurfaceDef();
	
	//-------------------------------------------------------------------------
	// Gets the type of SpecSurface
	//-------------------------------------------------------------------------
	enum Type {
		CATSpecBissectorSurfaceDefType=1
	};
	virtual CATSpecSurfaceDef::Type GetType() const = 0;
	
	//-------------------------------------------------------------------------
	// Duplicate this 
	//-------------------------------------------------------------------------
	virtual CATSpecSurfaceDef * Duplicate() const = 0;
	
	//-------------------------------------------------------------------------
	// Apply isometric transformation on the data 
	//-------------------------------------------------------------------------
	virtual void ApplyTransformation(const CATMathTransformation & iTransfo);

	virtual void CreateSurface() =0;

	virtual CATSurface * GetSurface() const;
  virtual void SetSurface(CATSurface * iSurface);

  virtual void Dump(CATCGMOutput & os) = 0;

	//-------------------------------------------------------------------------
	// Pour le stream
	//-------------------------------------------------------------------------
  virtual void BeginningLinkObjects() ;
	virtual CATLONG32 NextLinkObjects() ;
	virtual CATGeometry * GetLinkObjects();
	virtual CATLONG32 GetNumberOfLinkObjects();

protected:
  void SetLinkObjects(CATGeometry ** iLinkObjects, CATLONG32 iNbLinkObjects);
  
private:
	CATSurface * _Surface;
	CATGeometry ** _LinkObjects;
	CATLONG32 _iLinkObjects, _NbLinkObjects;
};

#endif
