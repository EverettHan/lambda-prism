#ifndef CATDynFilletBlendVertex_h_
#define CATDynFilletBlendVertex_h_

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"

#include "ListPOfCATDynFilletBlendVertex.h"
#include "CATDynFilletBlendVertexSpec.h"
#include "CATIAV5Level.h"

class CATCell;
class CATCGMStream;
class CATDynFilletBlendVertexSpec;

/**
* @level Protected
* @usage U1
*/

#ifndef NULL
#define NULL 0
#endif

/**
* Class defining a hyper vertex to blend.<br>
* A blend vertex (also named hyper vertex or corner with setbacks)
* is a vertex where three edges blend together at a defined distance from the corner vertex. 
* Compared to the default corner which is obtained when three edges
* are simply filletted, the result is more appealing. <br>
* Here is what you have to do to create a blend vertex:
* <ol>
* <li>Create a CATIPGMDynFillet
* <li>For each edge to be filletted and leading to the corner to be rounded:
* <ol>
* <li>Create a CATDynFilletBlendVertexSpec
* <li>Create a CATDynFilletEdgeRibbon and apply the SetReconfigFillFunction method with the 
* CATDynC1SingleFaceFilling option
* </ol>
* <li>Sort the list of CATDynFilletBlendVertexSpec so that they are re-ordered clock-wise.
* To do this, use CATIPGMSortBlendVertexSpecs
* <li>Create a CATDynFilletBlendVertex
* <li>Add each CATDynFilletBlendVertex to the CATIPGMDynFillet.
* </ol>
*/
class ExportedByCATGMOperatorsInterfaces CATDynFilletBlendVertex
{
public :

	/**
	* Defines the mode of creation of the blend corner.	
	* @param PocOnly
	* The only mode implemented.
	* @param PocOrSetback
	* Do not use.
	* @param SetbackOnly
	* Do not use.
	*/
	enum SpecMode
	{
		PocOnly,  
		PocOrSetback,
		SetbackOnly
	};
	/**
	* @nodoc
	*/
	CATDynFilletBlendVertex();

	virtual ~CATDynFilletBlendVertex();

	enum CornerMode
	{
		Disabled,
		EnabledMustSucceed,
		EnabledMayFail
	};

	/**
	* Specifies Corner mode Disabled/enabled...
	*/
	virtual void SetCornerMode(CornerMode iMode);

	/**
	* Specifies Multi convexity resolution mode...
	*/
	virtual void SetMultiConvexityMode(CATBoolean iEnabled);

	/**
	* Sets tangents correction...
	*/
	virtual void SetTangentCorrectionMode(CATBoolean iEnabled);

protected:
};


/**
* Constructs a blend vertex.
* @param iSpecMode
* CATDynFilletBlendVertex::PocOnly, the only implemented option.
* @param iSpecs
* The clock-wise list of CATDynFilletBlendVertexSpec.
* @return
* The CATDynFilletBlendVertex operator.
*/
ExportedByCATGMOperatorsInterfaces CATDynFilletBlendVertex* CATCreateDynFilletBlendVertex (CATDynFilletBlendVertex::SpecMode iSpecMode,
																						   CATLISTP(CATDynFilletBlendVertexSpec) &iSpecs);

#endif
