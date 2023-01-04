#ifndef CATDirWrapSurfaceDefine_H
#define CATDirWrapSurfaceDefine_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATSpaceDeformationMapDefine.h"
#include "CATMathDirection.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;
class CATBody;
class CATSpaceDeformationTopoMap;
class CATTopData;
class CATSurface;
class CATNurbsSurface;
class CATGlobdefCommand;
/**
 * Class defining the operator computing the map of a DirWrapSurface deformation.
 * <br> The DirWrapSurface deformation is ........................
 * <br>The resulting map is used by the @href CATTopDeformation operator to
 * compute the body resulting of the deformation.
 * <br>As any operator, CATDirWrapSurfaceDefine is used according the following steps:
 * <ul><li>Create it with the global function @href CATCreateDirWrapSurfaceDefine 
 * <li>If needed, tune some options
 * <li>Run it
 * <li>Get the created map. 
 * <li>If needed, tune some options again
 * <li>Update it
 * <li><tt>delete</tt> it from the memory.
 */
class ExportedByCATGMOperatorsInterfaces CATDirWrapSurfaceDefine : public CATSpaceDeformationMapDefine
{
  public:
	//-------------
  // Destructor
  //------------- 
  virtual ~CATDirWrapSurfaceDefine();

/*
  On the Set... methodes
	Add / Modify some option
	return code can be
	0 : Ok The mofification is done.
	1 : This method is inactive : Nothing is done
	2 : Internal error : Nothing is done
*/
	



/*
 * Update the map corresponding to <tt>this</tt> deformation, after some Set
 * <br> the pointer on the map is unchanged.
 */
	virtual CATLONG32 Update() = 0;
  
/*
 * Define a Guiding Surface where deformation is kept null
 */
    virtual void SetOneGuideSurf(CATNurbsSurface *GuidingSurf) =0; 

/**
 * Set Start and Target elements  .
 * 
 */
	virtual void SetStartSurface(CATBody * iStartSurface) = 0;
    virtual void SetTargetSurface( CATBody * iTargetSurface)=0;
   

    

/**
 * Get  Start and Target elements .
 * 
 */
	virtual  CATBody * GetStartSurface() = 0;
    virtual  CATBody * GetTargetSurface() =0;

   
   
/**
 * Check if the deformation is localy applicable  
 * 
 */
virtual CATBoolean IsLocallyApplicable()=0;
/**
 * Check if a body is deformable  .
 * 
 */

virtual void SetBodyToFitDeformation(CATBody * iBodyToDeform)=0;
/**
 *	Creates a DirWrapSurface deformation.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iSkinToDeform
 * 
 * 
 */
};
ExportedByCATGMOperatorsInterfaces CATDirWrapSurfaceDefine* 

CATCreateDirWrapSurfaceDefine(CATGeoFactory                 * iFactory,
                         CATTopData                         * iTopData,
                         CATBody                            * iStartShell,
                         CATBody                            * iTargetShell,
                         CATMathDirection                   * iProjDir=NULL);
       

                         
#endif

