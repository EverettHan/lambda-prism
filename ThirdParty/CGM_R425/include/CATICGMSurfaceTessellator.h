#ifndef CATICGMSurfaceTessellator_h_
#define CATICGMSurfaceTessellator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"

class CATSurLimits;
class CATSurface;
class CATCGMTessFanIter;
class CATCGMTessPointIter;
class CATCGMTessPolyIter;
class CATCGMTessStripeIter;
class CATCGMTessTrianIter;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMSurfaceTessellator;

/**
* Class defining a tessellation operator on surfaces.
* <br> This operator computes a discretized geometry on the surfaces as triangles.
* The corner of the triangles are called points. Three parameters tune the tessellation result:
* <dl>
* <dt> Sag </dt><dd> Defines the maximum distance between a bar and the object to tessellate
* <dt> Step </dt><dd> Defines the maximum length of a bar. If not defined, the step is infinite 
* (this parameter is unused)
* <dt> Angle </dt><dd> Defines the maximum angle between the normals at each bar end. 
* </dl>
* The tessellation operator follows the scheme of all CGM operator:
* <ul>
* <li> Create an operator instance,
* <li> Run,
* <li> Optionally, adds other curves to tessellate in the same operation,
* <li> Recover the results by the means of iterators,
* <li> Delete the operator instance. The deletion of the operator leads to the deletion
* of the iterators and the arrays of results.
* </ul>
*/
class ExportedByCATGMModelInterfaces CATICGMSurfaceTessellator: public CATICGMVirtual
{
public:
	/**
	* Constructor
	*/
	CATICGMSurfaceTessellator();

	/**
	* Adds an other surface to <tt>this</tt> CATICGMSurfaceTessellator.
	* @param iSurface
	* The other surface to tessellate in the same operation.
	* @param iSurfaceLimits
	* The part of the surface to take into account.
	*/
	virtual void AddSurface(CATSurface *iSurface, const CATSurLimits &iSurfaceLimits) = 0;

	/**
	* Defines a finite step for <tt>this</tt> CATICGMCurveTessellator.
	* @param iStep
	* The Step value.
	*/
	virtual void SetStep(double iStep) = 0;

	/**
	* Runs <tt>this</tt> CATICGMSurfaceTessellator.
	*/
	virtual void Run() = 0;

	/**
	* Retrieves the results associated with a surface.
	* <br> All the output iterators are allocated by the <tt>GetSurface</tt> method,
	* and are deleted when the operator is deleted.
	* @param iSurface
	* A surface among the input surfaces.
	* @param ioPlane
	* Retrieves <tt>1</tt> if the surface is planar, <tt>0</tt> otherwise.
	* @param oPoints
	* A pointer to a CATCGMTessPointIter, to retrieve the computed points. 
	* @param oStrips
	* A pointer to a CATCGMTessStripeIter, to retrieve the computed triangle strips. 
	* @param oStrips
	* A pointer to a CATCGMTessFanIter, to retrieve the computed triangle fans. 
	* @param oStrips
	* A pointer to a CATCGMTessPolygonIter, to retrieve the computed polygons.
	*/
	virtual void GetSurface(
		CATSurface *iSurface,
		CATBoolean &ioPlane,
		CATCGMTessPointIter **oPoints,
		CATCGMTessStripeIter **oStrips,
		CATCGMTessFanIter **oFans,
		CATCGMTessPolyIter **oPolygons,
		CATCGMTessTrianIter **oTriangles) = 0;

protected:
	/**
	* Destructor
	*/
	virtual ~CATICGMSurfaceTessellator(); // -> delete can't be called
};

/**
* Constructs a CATICGMSurfaceTessellator with an infinite step.
* @param iSag
* The Sag value.
* @param iAngle
* The Angle value.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMSurfaceTessellator *CATCGMCreateSurfaceTessellator(
	double iSag,
	double iAngle = CATPI*.25);

#endif /* CATICGMSurfaceTessellator_h_ */
