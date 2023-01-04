#ifndef CATCoordinateSystem_H
#define CATCoordinateSystem_H

#include "CATGeoAxis.h"

class CATBody;
class CATFace;
class CATEdge;
class CATVertex;
class CATPlane;
class CATLine;
class CATPoint;
class CATMathAxis;

#include "CATGMOperatorsInterfaces.h"  
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMOperatorsInterfaces IID IID_CATCoordinateSystem;
#else
extern "C" const IID IID_CATCoordinateSystem;
#endif

class ExportedByCATGMOperatorsInterfaces CATCoordinateSystem : public CATGeoAxis

{
CATDeclareInterface;
 public :
/**
 * Retrieves the body corresponding to the coordinate system.
 *<br> The pointer always points to the same body. 
 * @param oBody
 * The pointer to the body defining the coordinate system. Do not Remove it from the factory.
 */
  virtual HRESULT GetBody (CATBody *& oBody) const =0;
 // reads the topologic	cells
 virtual HRESULT GetPlanes(CATFace*& oPlaneXY, CATFace*& oPlaneYZ, CATFace*& oPlaneZX) const	=0;	
 virtual HRESULT GetAxes(CATEdge*& oAxisX, CATEdge*& oAxisY, CATEdge*& oAxisZ) const	=0;	
 virtual HRESULT GetOriginPoint(CATVertex*& oOriginPoint) const =0;

// reads the geometry
 virtual HRESULT GetPlanes(CATPlane*& oPlaneXY, CATPlane*& oPlaneYZ, CATPlane*& oPlaneZX) const=0;	
 virtual HRESULT GetAxes(CATLine*& oAxisX, CATLine*& oAxisY, CATLine*& oAxisZ) const	=0;	
 virtual HRESULT GetOriginPoint(CATPoint*& oOriginPoint) const	=0;
	
};
CATDeclareHandler(CATCoordinateSystem,CATGeoAxis);
#endif
