#ifndef CATSpaceDeformationMapDefine_H
#define CATSpaceDeformationMapDefine_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATMathDirection.h"
#include "CATGMOperatorsInterfaces.h"

class CATGeoFactory;
class CATBody;
class CATSpaceDeformationTopoMap;

/**
 * Abstract Class defining the operator computing the map of a Map deformation.
 * <br> The Map deformation is the deformation of the inner of a closed wire
 * contour on a skin body, by pushing or pulling a point in the inner in one
 * one direction.
 * <br>The resulting map is used by the @href CATTopDeformation operator to
 * compute the body resulting of the deformation.
 * <br>As any operator, CATSpaceDeformationMapDefine is used according the following steps:
 * <ul><li>Create it with a global function by example @href CATCreateBumpDefine 
 * <li>If needed, tune some options
 * <li>Run it
 * <li><tt>delete</tt> it from the memory.
 */
class ExportedByCATGMOperatorsInterfaces CATSpaceDeformationMapDefine
{
  public:
	//-------------
  // Destructor
  //------------- 
  virtual ~CATSpaceDeformationMapDefine();

/*
 * Creates the map corresponding to <tt>this</tt> deformation.
 */
	virtual CATLONG32 Run()=0;

/**
 * Returns the pointer to the map corresponding to <tt>this</tt> deformation.
 * <br>To call after the <tt>Run</tt> method.
 * <br> Warning this returned Map will be deleted in the same time than <tt>this</tt>
 */	
	virtual const CATSpaceDeformationTopoMap* GetResult() const =0;
};
#endif
