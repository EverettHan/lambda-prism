/* -*-C++-*- */

#ifndef CATCellManifoldNotchNavigator_H
#define CATCellManifoldNotchNavigator_H

// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// PRL: Feature recognition -- Notch Navigator 
//      Simple repompage de CATCellManifoldPadPocketNavigator + qqs modifs
// ----------------------------------------------------------------------------------------------//

#include "CATPersistentCell.h"

#include "CATCellManifoldNotchNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATExtrusionType.h"
#include "CATPadPocketManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATNotchManifoldAttribute.h"

class CATCellManifoldExtrusionNavigatorData;

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;


class ExportedByPersistentCell CATCellManifoldNotchNavigator : public CATCellManifoldNotchNavigatorInterface
{
public:
    // Constructor
    CATCellManifoldNotchNavigator(); 
    CATCellManifoldNotchNavigator(CATLiveBody          * iLiveBody, 
        CATCellManifoldGroup * iNetworkGroup); 
    CATCellManifoldNotchNavigator(CATDRepNavigator     * iDrepNavigator, 
        CATCellManifoldGroup * iNetworkGroup); 

    //-------------------------------------------------------------------------------------------------------
    // Surcharge du new/delete
    //-------------------------------------------------------------------------------------------------------
    CATCGMDeclareManifoldNavigator(CATCellManifoldNotchNavigator, CATCellManifoldNotchNavigatorInterface);
    //CATCGMNewClassArrayDeclare;      // Pool allocation

    // Destructor
    virtual ~CATCellManifoldNotchNavigator();

    CATCellManifoldNotchNavigator * GetAsNotchNavigator();

    //Interface methods

    // Implement pure virtual methods from CATCellManifoldExtrusionNavigatorInterface
    virtual HRESULT GetNetworkGroup (CATCellManifoldGroup *& oNetworkGroup) const;

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

    virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const;

    virtual CATLiveBody& GetLiveBody() const;

    virtual HRESULT IsBlind(CATBoolean &oIsBlind) const;
    virtual HRESULT GetEndWallType(EndWallType & oType) const;
    virtual HRESULT GetDepth(double & oDepth) const;
    virtual HRESULT GetLength(double & oLength) const;
    virtual HRESULT GetWidth(double & oWidth) const;

protected:

    void Dump(CATCGMOutput& Output);
    void Init();

private:
    CATCellManifoldExtrusionNavigatorData *_pExtrusionNavigatorData;
    CATNotchManifoldAttribute * _NotchAttr;
};

// ---------------------------------------
// CATCreateCellManifoldNotchNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldNotchNavigator * CATCreateCellManifoldNotchNavigator(CATLiveBody          * iLiveBody,
                                                                                             CATCellManifoldGroup * iNetworkGroup); 


#endif
