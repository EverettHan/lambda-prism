#ifndef CATWrapCurveDefine_H
#define CATWrapCurveDefine_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATSpaceDeformationMapDefine.h"
#include "CATMathDirection.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;
class CATBody;
class CATSpaceDeformationTopoMap;
class CATTopData;
class CATNurbsSurface;
/**
 * Class defining the operator computing the map of a WrapCurve deformation.
 * <br> The WrapCurve deformation is ........................
 * <br>The resulting map is used by the @href CATTopDeformation operator to
 * compute the body resulting of the deformation.
 * <br>As any operator, CATWrapCurveDefine is used according the following steps:
 * <ul><li>Create it with the global function @href CATCreateWrapCurveDefine 
 * <li>If needed, tune some options
 * <li>Run it
 * <li>Get the created map. 
 * <li>If needed, tune some options again
 * <li>Update it
 * <li><tt>delete</tt> it from the memory.
 */
class ExportedByCATGMOperatorsInterfaces CATWrapCurveDefine : public CATSpaceDeformationMapDefine
{
  public:
	//-------------
  // Destructor
  //------------- 
  virtual ~CATWrapCurveDefine();

/*
  On the Set... methodes
	Add / Modify some option
	return code can be
	0 : Ok The mofification is done.
	1 : This method is inactive : Nothing is done
	2 : Internal error : Nothing is done
*/
	



/**
 * Defines the continuity order beetween the modified area and the non modified area.
 * @param iOrder =0 or 2  
 * The continuity order value. The default is 2 (G2 continuous).
 */
	virtual CATLONG32 SetContinuityAtFirstCurve(const CATLONG32 iOrder) = 0;
    virtual CATLONG32 SetContinuityAtLastCurve(const CATLONG32 iOrder) = 0;

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
 * Set Spine and direction curve (Target No distinction between Start and Target  .
 * 
 */
	virtual void SetSpine(CATBody * iSpineCurve) = 0;
    virtual void SetDirectionCurve( CATBody * iDirCurve)=0;
    virtual void ComputeDirectionCurve( CATBody * iDirCurve)=0;

    

/**
 * Get Spine .
 * 
 */
	virtual  CATBody * GetStartSpine() = 0;
    virtual  CATBody * GetStartDirectionCurve() =0;

    virtual  CATBody * GetTargetSpine() =0;
    virtual  CATBody * GetTargetDirectionCurve() =0;
   
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
 * Option to use for variable offset.
 *1  if the deformation is along the normal and in the positive direction with respect to the skin
 *-1 if the deformation is along the normal and in the negative direction with respect to the skin
 */
virtual void SetDeformationAlongNormal(int iOrientation)=0;
};
/**
 *	Creates a WrapCurve deformation.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iSkinToDeform
 * 
 * 
 */
ExportedByCATGMOperatorsInterfaces CATWrapCurveDefine* 

CATCreateWrapCurveDefine(CATGeoFactory                 * iFactory,
                         CATTopData                    * iTopData,
                         CATBody                 * iStartSpineWire,
                         CATBody                 * iStartDirectionWire,
                         CATLISTP(CATBody )            * iListOfStartWires,
                         
                         CATBody                 * iTargetSpineWire,
                         CATBody                 * iTargetDirectionWire,
                         CATLISTP(CATBody )            * iListOfTargetWires);
/**
 *	Creates a WrapCurve deformation.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iSkinToDeform
 * The Start spine is taken as the first start curve 
 * 
 */
ExportedByCATGMOperatorsInterfaces CATWrapCurveDefine* 

CATCreateWrapCurveDefine(CATGeoFactory                 * iFactory,
                         CATTopData                    * iTopData,
                         CATLISTP(CATBody )            * iListOfStartWires,
                                                                
                         CATLISTP(CATBody )            * iListOfTargetWires);
#endif

