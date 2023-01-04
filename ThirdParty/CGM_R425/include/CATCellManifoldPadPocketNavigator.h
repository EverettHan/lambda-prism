// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Pad/Pocket Navigator Implementation -- | Agent navigator |
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldPadPocketNavigator_H
#define CATCellManifoldPadPocketNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldPadPocketNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATExtrusionType.h"
#include "CATPadPocketManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATlsoBodyUtil.h"


class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;
class CATCellManifoldExtrusionNavigatorData;


class ExportedByPersistentCell CATCellManifoldPadPocketNavigator : public CATCellManifoldPadPocketNavigatorInterface
{
public:
    // Constructor
    CATCellManifoldPadPocketNavigator(); 
    CATCellManifoldPadPocketNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup); 
    CATCellManifoldPadPocketNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup); 


    //-------------------------------------------------------------------------------------------------------
    // Surcharge du new/delete
    //-------------------------------------------------------------------------------------------------------
    // Attribute Declaration
    CATCGMDeclareManifoldNavigator(CATCellManifoldPadPocketNavigator, CATCellManifoldPadPocketNavigatorInterface);
    //CATCGMNewClassArrayDeclare;      // Pool allocation


    // Destructor
    virtual ~CATCellManifoldPadPocketNavigator();

    CATCellManifoldPadPocketNavigator * GetAsPadPocketNavigator();

    //Interface methods

    // Implement pure virtual methods from CATCellManifoldExtrusionNavigatorInterface
    virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

    virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
    virtual HRESULT GetExtrusionType(CATExtrusionType & oType) const;
    virtual HRESULT GetExtrusionDirection(CATMathVector & oDir) const;
    virtual HRESULT GetExtrusionFaces(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionSupports(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionEnds(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionExits(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const;

    virtual HRESULT GetExtrusionSupportDeco(ListPOfCATCellManifold & oCMFaces) const; 
    virtual HRESULT GetExtrusionEndDeco(ListPOfCATCellManifold & oCMFaces) const;

    virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;

    virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const;

    virtual CATLiveBody& GetLiveBody() const;

    // Implement pure virtual methods from CATCellManifoldPadPocketNavigatorInterface
    virtual HRESULT IsBlind(CATBoolean &oIsBlind) const;  
    virtual HRESULT IsCylindricalPad(CATBoolean &oIsCylindricalPad) const;
    virtual HRESULT HasOpenWall(CATBoolean &oHasOpenWall) const;  
    virtual HRESULT GetDepth(double & oDepth) const;
    virtual HRESULT IsConstantDrafted(CATBoolean &oIsConstantDrafted) const;  
    virtual HRESULT GetDraftAngle(CATAngle &oConstantDraftAngle) const; 
    virtual HRESULT IsLocalExtrusion(CATBoolean &oIsLocalExtrusion) const;  
    virtual HRESULT GetAngleForLocalExtrusion(CATAngle &oAngle) const; 

    // for drafted Pad/Pocket, in order to know if the planar drafted faces are connected with cylindrical inner fillets
    virtual HRESULT HasInnerFillets(CATBoolean &oHasInnerFillets) const;      

    // for cylindrical pads
    virtual HRESULT GetCylindricalPadMinDiameter(double & oMinDiameter) const;
    virtual HRESULT GetCylindricalPadMaxDiameter(double & oMaxDiameter) const;
    virtual HRESULT GetCylindricalPadDepth(double & oDepth) const;
    virtual HRESULT GetCylindricalPadAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const;

    virtual HRESULT GetPadPocketType(CATPadPocketType & oType) const;

protected:

    void Dump(CATCGMOutput& Output);
    void Init();

private:
    CATCellManifoldExtrusionNavigatorData *_pExtrusionNavigatorData;
    CATPadPocketManifoldAttribute * _PadPocketAttr;
};

// ---------------------------------------
// CATCreateCellManifoldPadPocketNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldPadPocketNavigator * CATCreateCellManifoldPadPocketNavigator(CATLiveBody          * iLiveBody,
                                                                                                     CATCellManifoldGroup * iNetworkGroup); 


#endif
