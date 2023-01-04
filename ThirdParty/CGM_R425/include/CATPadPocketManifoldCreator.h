// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Pad-Pocket Creation/Recognition -- | Creation Level |
// --------------------------------------------------------------------------------------//

#ifndef CATPadPocketManifoldCreator_H
#define CATPadPocketManifoldCreator_H

#include "PersistentCell.h"
#include "CATMathInline.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCellManifoldGroupOperator.h"
#include "CATExtrusionManifoldCreatorBase.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATGMLiveExtrusionPrimitivesContainer.h"
#include "ListPOfCATManifoldNavigator.h"

class ExportedByPersistentCell CATPadPocketManifoldCreator : public CATExtrusionManifoldCreatorBase
{
public:
	CATCGMDeclareManifoldAgent(CATPadPocketManifoldCreator, CATDeclarativeManifoldAgent);

	// Constructors
	CATPadPocketManifoldCreator();
	CATPadPocketManifoldCreator(CATGMLiveExtrusionPrimitivesContainer * iExtrusionContainer);

	// Destructor
	virtual ~CATPadPocketManifoldCreator();

	virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) & iParentCellManifolds, 
		CATLISTP(CATCellManifold) & iChildrenManifolds, 
		int                         iInfo,
		CATBoolean iForbidZeroInfo=TRUE);

	virtual int GetPriority();
	CATPadPocketManifoldCreator * GetAsPadPocketManifoldCreator();
	virtual HRESULT CreateImageManifolds();

	//INLINE void GetCreatedNavigators(ListPOfCATManifoldNavigator & ioPadPocketNavigators);
	INLINE virtual CATDeclarativeManifoldAgent* Clone();
	INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

protected:

	virtual HRESULT BuildExtrusionPrimitiveSets(CATBody                               & iInputBody,
		ListPOfCATFace                        & ioFacesToBeRecognized,
		CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

	virtual void UpdateFacesWhenDecoHasNonPlanarSupports(CATBody         & iInputBody,
                                                          ListPOfCATFace & ioDecoFaces,
                                                          ListPOfCATFace & ioSupportFaces,
                                                          ListPOfCATFace const & iExtrudeFaces);
};

INLINE CATDeclarativeManifoldAgent* CATPadPocketManifoldCreator::Clone()
{
	return new CATPadPocketManifoldCreator();
}

INLINE CATBoolean CATPadPocketManifoldCreator::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
	return TRUE;
}

#endif
