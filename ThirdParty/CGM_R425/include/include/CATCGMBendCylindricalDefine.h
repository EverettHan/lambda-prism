#ifndef CATCGMBendCylindricalDefine_H
#define CATCGMBendCylindricalDefine_H

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATSpaceDeformationMapDefine.h"
#include "CATMathDirection.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATBody.h"
#include "CATTopOpInError.h"
class CATGeoFactory;
class CATBody;
class CATSpaceDeformationTopoMap;
class CATTopData;
class CATSurface;
class CATNurbsSurface;
class CATGlobdefCommand;
class CATMathPoint;
/**
 * Class defining the operator computing the map of a BendCylindrical deformation.
 * <br> The BendCylindrical deformation is ........................
 * <br>The resulting map is used by the @href CATTopDeformation operator to
 * compute the body resulting of the deformation.
 * <br>As any operator, CATCGMBendCylindricalDefine is used according the following steps:
 * <ul><li>Create it with the global function @href CATCGMCreateBendCylindricalDefine 
 * <li>If needed, tune some options
 * <li>Run it
 * <li>Get the created map. 
 * <li>If needed, tune some options again
 * <li>Update it
 * <li><tt>delete</tt> it from the memory.
 */
class ExportedByCATGMOperatorsInterfaces CATCGMBendCylindricalDefine : public CATSpaceDeformationMapDefine
{
  public:
	//-------------
  // Destructor
  //------------- 
  virtual ~CATCGMBendCylindricalDefine();

/*
  On the Set... methodes
	Add / Modify some option
	return code can be
	0 : Ok The mofification is done.
	1 : This method is inactive : Nothing is done
	2 : Internal error : Nothing is done
*/

/*
 * Specify a selection point.  
 * <br>If any selection points are specified, then only cells that are connected to
 * a selection point without going through the identity region are deformed.
 * @param iSelectionPoint
 * The selection point.
 */
  virtual void AddSelectionPoint(CATMathPoint const & iSelectionPoint) = 0;

  // NO SET METHODS: I'D PREFER (AT FIRST) TO NOT ALLOW CHANGES TO THE BEND DEFINITION AFTER CREATION.

  // NOT SURE IF WE WANT TO INCLUDE THE FOLLOWING METHOD, SINCE I WOULD LIKE TO NOT ALLOW A CHANGE IN THE BEND PARAMETERS AFTER CONSTRUCTION.
/*
 * Update the map corresponding to <tt>this</tt> deformation, after some Set
 * <br> the pointer on the map is unchanged.
 */
//	virtual CATLONG32 Update() = 0;

// SHOULDN'T THE GetWarning METHOD BE IN THE BASE CLASS CATSpaceDeformationMapDefine?
// virtual CATTopOpInError * GetWarning()=0;
};

/**
 *	Creates a BendCylindrical deformation.
 * @param iFactory
 * A pointer to the geometry factory.
 * @param iTopData
 * A pointer to the top data to be used.
 * @param iNeutralPoint
 * A point on the neutral plane and the start plane of the bend region.
 * @param iBendDir
 * The direction perpendicular to the neutral plane.  Material in the bend region will be moved to this side of the neutral plane.
 * @param iBendRadius
 * The radius of the bend which will be applied to the neutral plane.
 * @param iWidthDir
 * The direction perpendicular to start plane of the bend region.  The bend will be applied to this side of the start plane.
 * @param iWidth
 * The width of the region to be bent.  The bend angle in radians will be iWidth/iBendRadius.
 */
ExportedByCATGMOperatorsInterfaces CATCGMBendCylindricalDefine* CATCGMCreateBendCylindricalDefine(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATMathPoint const & iNeutralPoint, 
	CATMathDirection const & iBendDir, 
	double iBendRadius, 
	CATMathDirection const & iWidthDir, 
	double iWidth);
        
#endif

