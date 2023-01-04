#ifndef CATCGMUnbendCylindricalDefine_H
#define CATCGMUnbendCylindricalDefine_H

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
class CATListPtrCATCell;

/**
 * Class defining the operator computing the map of an UnbendCylindrical deformation.
 * <br> The UnbendCylindrical deformation is ........................
 * <br>The resulting map is used by the @href CATTopDeformation operator to
 * compute the body resulting of the deformation.
 * <br>As any operator, CATCGMUnbendCylindricalDefine is used according the following steps:
 * <ul><li>Create it with the global function @href CATCGMCreateUnbendCylindricalDefine 
 * <li>If needed, tune some options
 * <li>Run it
 * <li>Get the created map. 
 * <li>If needed, tune some options again
 * <li>Update it
 * <li><tt>delete</tt> it from the memory.
 */
class ExportedByCATGMOperatorsInterfaces CATCGMUnbendCylindricalDefine : public CATSpaceDeformationMapDefine
{
  public:
	//-------------
  // Destructor
  //------------- 
  virtual ~CATCGMUnbendCylindricalDefine();

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

  /* Add "hint" cells, i.e. cells that the caller knows should be in the bend,
  /* identity, and/or transform regions */
  virtual void SetHintCells(const CATLISTP(CATCell) & iBendCells,
                            const CATLISTP(CATCell) & iIdentityCells,
                            const CATLISTP(CATCell) & iTransformCells) = 0;

  // NOT SURE IF WE WANT TO INCLUDE THE FOLLOWING METHOD, SINCE I WOULD LIKE TO NOT ALLOW A CHANGE IN THE UNBEND PARAMETERS AFTER CONSTRUCTION.
/*
 * Update the map corresponding to <tt>this</tt> deformation, after some Set
 * <br> the pointer on the map is unchanged.
 */
//	virtual CATLONG32 Update() = 0;

// SHOULDN'T THE GetWarning METHOD BE IN THE BASE CLASS CATSpaceDeformationMapDefine?
// virtual CATTopOpInError * GetWarning()=0;
};

/**
 * Creates an UnbendCylindrical deformation.
 * @param iFactory
 * A pointer to the geometry factory.
 * @param iTopData
 * A pointer to the top data to be used.
 * @param iNeutralPoint
 * A point on the neutral cylinder and the start half-plane of the unbend region.
 * @param iBendDir
 * The direction from the neutral point towards the bend axis.
 * @param iBendRadius
 * The radius of the neutral cylinder.
 * @param iWidthDir
 * The direction perpendicular to start half-plane of the unbend region.  The unbend will be applied to this side of the start half-plane.
 * @param iUnbentWidth
 * The width of the region that was originally bent.  Equal to the bend angle in radians times the bend radius.
 */
ExportedByCATGMOperatorsInterfaces CATCGMUnbendCylindricalDefine* CATCGMCreateUnbendCylindricalDefine(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATMathPoint const & iNeutralPoint, 
	CATMathDirection const & iBendDir, 
	double iBendRadius, 
	CATMathDirection const & iWidthDir, 
	double iUnbentWidth);
        
#endif

