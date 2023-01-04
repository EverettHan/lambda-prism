// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ZUS: Feature recognition -- Hole Creation/Recognition -- | Creation Level |
// --------------------------------------------------------------------------------------//

#ifndef CATHoleManifoldCreator_H
#define CATHoleManifoldCreator_H

#include "PersistentCell.h"
#include "CATMathInline.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCellManifoldGroupOperator.h"
#include "CATExtrusionManifoldCreatorBase.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATGMLiveExtrusionPrimitivesContainer.h"
#include "CATCellManifoldHoleNavigatorInterface.h"
#include "CATCellManifoldHoleNavigator.h"

class CATCGMExtrPrimFaceListAssociation;

class ExportedByPersistentCell CATHoleManifoldCreator : public CATExtrusionManifoldCreatorBase
{
public:
    CATCGMDeclareManifoldAgent(CATHoleManifoldCreator, CATExtrusionManifoldCreatorBase);

    // Constructor
    CATHoleManifoldCreator();

    // Destructor
    virtual ~CATHoleManifoldCreator();

    

    virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) & iParentCellManifolds, 
        CATLISTP(CATCellManifold) & iChildrenManifolds, 
        int                         iInfo,
        CATBoolean iForbidZeroInfo=TRUE);

    virtual int GetPriority();
    CATHoleManifoldCreator * GetAsHoleManifoldCreator();
    INLINE virtual CATDeclarativeManifoldAgent* Clone();
    INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
    virtual HRESULT CreateImageManifolds();

protected:

    virtual HRESULT BuildExtrusionPrimitiveSets(CATBody                               & iInputBody,
        ListPOfCATFace                        & ioFacesToBeRecognized,
        CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

private:
    HRESULT CheckIfExtrusionIsCylindricalDepression(CATBody                     & iInputBody, 
        CATGMLiveExtrusionPrimitive & iExtrusionPrimitive);
    HRESULT DivideCylindricalDepression(CATBody & iInputBody, CATGMLiveExtrusionPrimitive & iExtrusionPrimitive, ListPOfCATGMLiveExtrusionPrimitive & oSeparatedCylindricalDepressions);

    ListPOfCATGMLiveExtrusionPrimitive _CreatedPrimitivesToBeCleaned;
};

INLINE CATDeclarativeManifoldAgent* CATHoleManifoldCreator::Clone()
{
    return new CATHoleManifoldCreator();
}

INLINE CATBoolean CATHoleManifoldCreator::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
    return TRUE;
}

#endif
