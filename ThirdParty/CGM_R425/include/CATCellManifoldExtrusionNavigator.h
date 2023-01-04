// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Navigator Implementation -- | Generic navigator level |
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldExtrusionNavigator_H
#define CATCellManifoldExtrusionNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldExtrusionNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATExtrusionType.h"
#include "CATExtrusionManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"


class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;
class CATCellManifoldPadPocketNavigator;
class CATCellManifoldHoleNavigator;
class CATCellManifoldSlotNavigator;
class CATCellManifoldNotchNavigator;
class CATCellManifoldExtrusionNavigatorData;

class ExportedByPersistentCell CATCellManifoldExtrusionNavigator : public CATCellManifoldExtrusionNavigatorInterface
{
public:

    // Constructor
    CATCellManifoldExtrusionNavigator();
    CATCellManifoldExtrusionNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
    CATCellManifoldExtrusionNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
    CATCellManifoldExtrusionNavigator(CATCellManifoldExtrusionNavigator *iExtrusionNavigator);

    //-------------------------------------------------------------------------------------------------------
    // Surcharge du new/delete
    //-------------------------------------------------------------------------------------------------------
    // Attribute Declaration
    CATCGMDeclareManifoldNavigator(CATCellManifoldExtrusionNavigator, CATCellManifoldExtrusionNavigatorInterface);
    //CATCGMNewClassArrayDeclare;      // Pool allocation

    // Destructor
    virtual ~CATCellManifoldExtrusionNavigator();

    CATCellManifoldExtrusionNavigator * GetAsExtrusionNavigator();

    //ST5: GetAs methods for classes inheriting from this: PadPocket, Hole, Slot, Notch etc.
    virtual CATCellManifoldPadPocketNavigator * GetAsPadPocketNavigator();
    // IZE the missing ones
    virtual CATCellManifoldHoleNavigator * GetAsHoleNavigator();  
    virtual CATCellManifoldSlotNavigator * GetAsSlotNavigator();  
    virtual CATCellManifoldNotchNavigator * GetAsNotchNavigator();  

    //Interface methods
    virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

    virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
    virtual HRESULT GetExtrusionType(CATExtrusionType & oType) const;
    virtual HRESULT GetExtrusionDirection(CATMathVector & oDir) const;
    virtual HRESULT GetExtrusionFaces(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionSupports(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionEnds(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetExtrusionExits(ListPOfCATCellManifold & oCMFaces) const;

    virtual HRESULT GetExtrusionSupportDeco(ListPOfCATCellManifold & oCMFaces) const; 
    virtual HRESULT GetExtrusionEndDeco(ListPOfCATCellManifold & oCMFaces) const;

    virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
    virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const;
    virtual HRESULT GetDepth(double & oDepth) const;

    virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const;

    virtual CATLiveBody& GetLiveBody() const;

    //Local methods: may be in the future
    //HRESULT GetBorderCellManifolds(ListPOfCATCellManifold & oCellManifolds);
    //HRESULT CheckExtrusionGroup(CATCellManifoldGroup * iGroup, int & oError);


    //-------------------------------------------------
    //   Stream / Unstream 
    //-------------------------------------------------

    // @nocgmitf
    //-------------------------------------------------------------------------------------------------
    void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
    void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);


protected:

    void GetExtrusionManifoldAttribute(CATExtrusionManifoldAttribute *& oExtrusionAttr);

private:
    CATCellManifoldExtrusionNavigatorData *_pExtrusionNavigatorData;
};

// ---------------------------------------
// CATCreateCellManifoldExtrusionNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldExtrusionNavigator * CATCreateCellManifoldExtrusionNavigator(CATLiveBody          * iLiveBody,
                                                                                                     CATCellManifoldGroup * iNetworkGroup); 



#endif
