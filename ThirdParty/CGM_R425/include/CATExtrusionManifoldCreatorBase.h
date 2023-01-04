// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Creation/Recognition -- | Data Family Level |
// --------------------------------------------------------------------------------------//

#ifndef CATExtrusionManifoldCreatorBase_H
#define CATExtrusionManifoldCreatorBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATGMLiveExtrusionPrimitivesContainer.h"

class CATLISTP(CATCellManifold);
class CATTopExtrudeRecog;
class CATCGMExtrPrimFaceListAssociation;

class ExportedByPersistentCell CATExtrusionManifoldCreatorBase : public CATDeclarativeManifoldAgent  
{

    //friend class CATExtrusionManifoldCreatorInfraContextUtilities;
    

public:
    //=====================================================================================================================
    CATCGMDeclareManifoldAgent(CATExtrusionManifoldCreatorBase, CATDeclarativeManifoldAgent);

    // Constructor
    CATExtrusionManifoldCreatorBase();
    CATExtrusionManifoldCreatorBase(CATGMLiveExtrusionPrimitivesContainer * iExtrusionContainer);

    // Destructor
    virtual ~CATExtrusionManifoldCreatorBase();

    virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) & iParentCellManifolds, 
        CATLISTP(CATCellManifold) & iChildrenManifolds, 
        int                         iInfo,
        CATBoolean iForbidZeroInfo=TRUE);

    virtual int GetPriority();
    CATExtrusionManifoldCreatorBase * GetAsExtrusionManifoldCreatorBase();
    INLINE virtual CATDeclarativeManifoldAgent * Clone();
    INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

    CATGMLiveExtrusionPrimitivesContainer * GetExtPrimContainer_WithOwnerMgmt();
    CATGMLiveExtrusionPrimitivesContainer * GetExtPrimContainer();
    void SetExtPrimContainer(CATGMLiveExtrusionPrimitivesContainer * iExtrusionContainer);

    virtual HRESULT CreateImageManifolds(); 

protected:
    //=====================================================================================================================

    virtual HRESULT BuildExtrusionPrimitiveSets(CATBody                               & iInputBody,
        ListPOfCATFace                        & ioFacesToBeRecognized,
        CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

    //HRESULT BuildExtrusionPrimitiveSets_1(CATBody                               & iInputBody,
    //                                      ListPOfCATFace                        & ioFacesToBeRecognized,
    //                                      CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

    HRESULT BuildExtrusionPrimitiveSets_2(CATBody                               & iInputBody,
        ListPOfCATFace                        & ioFacesToBeRecognized,
        CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

    virtual HRESULT GetExtrPrimitives(CATBody                               & iInputBody,
        CATGMLiveExtrusionPrimitivesContainer & ioExtrusionPrimitivesContainer);

    virtual HRESULT CreateExtrusionManifolds(CATBody                            & iInputBody, 
        ListPOfCATGMLiveExtrusionPrimitive & iExtrusionPrimitives,
        CATLISTP(CATCellManifold)          & ioCreatedExtrusionManifolds);

    // ***********************************************************************************************************************************
    // these three helper methods are for concrete creator agents to use when re-classifying deco faces. 
    // Each creator agent can decide how to implement this based on their type of feature and may chose to override this.
    virtual void UpdateFacesWhenDecoHasNonPlanarSupports(CATBody         & iInputBody,
        ListPOfCATFace & ioDecoFaces,
        ListPOfCATFace & ioSupportFaces,
        ListPOfCATFace const & iExtrudeFaces);

    virtual void UpdateClogAndExitFacesWhenDecoHasNonPlanarSupports(CATBody         & iInputBody,
        ListPOfCATFace & ioClogDecoFaces,
        ListPOfCATFace & ioExitDecoFaces,
        ListPOfCATFace & ioClogFaces,
        ListPOfCATFace & ioExitFaces,
        ListPOfCATFace const & iExtrudeFaces,
        CATMathVector const & iExtrusionDirection,
        CATBoolean iIsProtrusion);

    virtual void UpdateFacesWhenClogIsCylindrical(CATBody         & iInputBody,
        ListPOfCATFace & ioDecoFaces,
        ListPOfCATFace & ioSupportFaces,
        ListPOfCATFace const & iExtrudeFaces);

    // ***********************************************************************************************************************************
    HRESULT DetermineAdjacentFaceLists(CATBody                     & iInputBody,
        CATGMLiveExtrusionPrimitive & iExtrusionPrimitive,
        CATCGMExtrPrimFaceListAssociation & iAdjFaceLists);

private:
CATBoolean ClogIsOrientedCorrectly(CATBody & iInputBody, 
	ListPOfCATFace const & iPotentialClogFaces, 
	CATMathVector const & iExtrusionDirection);


protected:
    //=====================================================================================================================
    CATTopExtrudeRecog                    * _TopExtrudeRecog;
    CATGMLiveExtrusionPrimitivesContainer * _ExtPrimContainer;    
    CATBoolean                              _ExtPrimOwner;

};

INLINE CATDeclarativeManifoldAgent * CATExtrusionManifoldCreatorBase::Clone()
{
    return new CATExtrusionManifoldCreatorBase();
}

INLINE CATBoolean CATExtrusionManifoldCreatorBase::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
    return TRUE;
}

#endif


