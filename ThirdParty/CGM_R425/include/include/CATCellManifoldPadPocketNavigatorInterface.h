// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2015
// ................................
//
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldPadPocketNavigatorInterface_H
#define CATCellManifoldPadPocketNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldExtrusionNavigatorInterface.h"

#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"
#include "CATIAV5Level.h"
class CATMathLine;

// Note: this class has to remain an interface class
// do not introduce any data members in this class

class ExportedByCATGMModelInterfaces CATCellManifoldPadPocketNavigatorInterface : public CATCellManifoldExtrusionNavigatorInterface
{
public:
#ifndef CATIAR419
    typedef enum 
    {
        UnknownPadPocketType    = 0,
        Pad                     = 1,
        Pocket                  = 2,        
        Blind_Pocket          , // = 3, 
        Through_Pocket        , // = 4, 
        Blind_Open_Pocket     , // = 5, 
        Through_Open_Pocket   , // = 6 
        LocalPad                = 8,
        LocalPocket             = 9,
        PadWithInnerFillets     = 10,
        PocketWithInnerFillets  = 11
    }
    CATPadPocketType;
#else
    typedef enum 
    {
        UnknownPadPocketType    = 0,
        Pad                     = 1,
        Pocket                  = 2,
        LocalPad                = 8,
        LocalPocket             = 9,
        PadWithInnerFillets     = 10,
        PocketWithInnerFillets  = 11
    }
    CATPadPocketType;
#endif

    // Constructor
    CATCellManifoldPadPocketNavigatorInterface(); 

    // Destructor
    virtual ~CATCellManifoldPadPocketNavigatorInterface();

    //------------------------
    // Surcharge du new/delete
    //------------------------
    CATCGMNewClassArrayDeclare;      // Pool allocation

    virtual CATCellManifoldPadPocketNavigatorInterface* GetAsPadPocketNavigatorInterface();

    // queries specific to PadPocket navigators
    virtual HRESULT IsBlind(CATBoolean &oIsBlind) const=0;  
    virtual HRESULT IsCylindricalPad(CATBoolean &oIsCylindricalPad) const=0;  
    virtual HRESULT HasOpenWall(CATBoolean &oHasOpenWall) const=0;      
    virtual HRESULT GetPadPocketType(CATPadPocketType & oType) const=0;
    virtual HRESULT IsConstantDrafted(CATBoolean &oIsConstantDrafted) const=0;  
    virtual HRESULT GetDraftAngle(CATAngle &oConstantDraftAngle) const=0;  
    virtual HRESULT IsLocalExtrusion(CATBoolean &oIsLocalExtrusion) const=0;  
    virtual HRESULT GetAngleForLocalExtrusion(CATAngle &oAngle) const=0;  

    // for drafted Pad/Pocket, in order to know if the planar drafted faces are connected with cylindrical inner fillets
    virtual HRESULT HasInnerFillets(CATBoolean &oHasInnerFillets) const=0;      

    // for cylindrical pads
    virtual HRESULT GetCylindricalPadMinDiameter(double & oMinDiameter) const=0;
    virtual HRESULT GetCylindricalPadMaxDiameter(double & oMaxDiameter) const=0;
    virtual HRESULT GetCylindricalPadDepth(double & oDepth) const=0;
    virtual HRESULT GetCylindricalPadAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const=0;

    // TODO: When all the features support transition faces, this method can be moved 
    // to CATCellManifoldExtrusionNavigatorInterface 
    // Right now this data makes sense only for holes and pads and pockets
    virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const=0;

    virtual void Dump(CATCGMOutput& Output);
protected:
};

#endif
