// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- PadPocket Attribute -- | Feature level attribute |
// --------------------------------------------------------------------------------------//


#ifndef CATPadPocketManifoldAttribute_H
#define CATPadPocketManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATExtrusionManifoldAttribute.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"
#include "CATCellManifoldPadPocketNavigatorInterface.h"

class CATCylindricalExtrusionUtilities;
class CATMathVector;
class CATExtrusionUtilities;

class ExportedByPersistentCell CATPadPocketManifoldAttribute : public CATExtrusionManifoldAttribute
{
public:
    CATCGMDeclareAttribute (CATPadPocketManifoldAttribute, CATExtrusionManifoldAttribute);

    CATPadPocketManifoldAttribute(); 

    // OLD CONSTRUCTORS - DO NOT USE IN NEW EVOLUTIONS
    CATPadPocketManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATFace const & iExtrudeFaces, ListPOfCATFace const & iSupportFaces, ListPOfCATFace const & iEndFaces, ListPOfCATFace const & iExitFaces);
    CATPadPocketManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATCellManifold const & iExtrudeCMs, ListPOfCATCellManifold const & iSupportCMs, ListPOfCATCellManifold const & iEndCMs, ListPOfCATCellManifold const & iExitCMs);

    // NEW CONSTRUCTOR
    CATPadPocketManifoldAttribute(CATSoftwareConfiguration* ipConfig, 
        CATCellManifoldPadPocketNavigatorInterface::CATPadPocketType iPadPocketType, 
        CATMathVector const & iExtrudeDir, 
        ListPOfCATPrototypeExtrusion const & iPrototypeList,
        ListPOfCATCellManifold const & iSupportCMs, 
        ListPOfCATCellManifold const & iSupportDecoCMs, 
        ListPOfCATCellManifold const & iEndCMs, 
        ListPOfCATCellManifold const & iEndDecoCMs, 
        ListPOfCATCellManifold const & iExitCMs);

    virtual ~CATPadPocketManifoldAttribute();

    CATPadPocketManifoldAttribute(CATPadPocketManifoldAttribute& iToCopy); // Forbidden
    CATPadPocketManifoldAttribute& operator= (const CATPadPocketManifoldAttribute& iToCopy); // Forbidden
    virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
    virtual void Move3D(CATTransfoManager& iTransfoManager);

    CATCGMNewClassArrayDeclare;      // Pool allocation

    virtual void Stream(CATCGMStream & ioStream) const;
    virtual void UnStream(CATCGMStream& ioStream);  
    virtual void Dump(CATCGMOutput& iWhereToWrite) const;

    virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

    //Set methods
    virtual void SetType(int & iType);
    virtual void SetConstantDrafted(CATBoolean iValue);  
    virtual void SetDraftAngle(CATAngle iAngle);
    virtual void SetAngleForLocalExtrusion(CATAngle iAngle);  

    //Get methods
    virtual int  GetType() const;
    virtual CATCellManifoldPadPocketNavigatorInterface::CATPadPocketType GetPadPocketType() const;
    virtual CATBoolean  IsBlind() const;
    virtual CATBoolean  HasOpenWall() const;
    double  GetDepth() const;
    virtual CATBoolean IsConstantDrafted() const;  
    virtual CATAngle   GetDraftAngle() const;  
    virtual CATBoolean IsLocalExtrusion() const;  
    virtual CATAngle   GetAngleForLocalExtrusion() const;  
    virtual CATBoolean HasInnerFillets() const;  

    // for cylindrical pads
    // IsCylindricalPad() will return FALSE if the live model uses the legacy data structure (facelists instead of cellmanifoldlists)
    CATBoolean IsCylindricalPad() const;
    double GetCylindricalPadMinDiameter() const;
    double GetCylindricalPadMaxDiameter() const;
    double GetCylindricalPadDepth() const;
    void GetCylindricalPadAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const;


    INLINE virtual CATPadPocketManifoldAttribute *GetAsPadPocketManifoldAttribute();

    virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                     const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager &iCellManifoldsManager) const;

private:
    //ST5: Add attributes specific to pad and pocket

    // OLD LEGACY DATA (DO NOT USE ANYMORE)
    int _Type; //0=Unknown; 1=Pad; 2=Blind Pocket; 3=Through Pocket; 4=Blind Open Pocket; 5=Through Open Pocket; 

    // NEW DATA MEMBERS
    CATCellManifoldPadPocketNavigatorInterface::CATPadPocketType _PadPocketType; //0=Unknown; 1=Pad; 2=Pocket; 8=Local Pad; 9=Local Pocket; 10=PadWithInnerFillets; 11=PocketWithInnerFillets
    CATCylindricalExtrusionUtilities* cylindricalPadHelper;
    CATExtrusionUtilities* helper;
    CATBoolean _IsConstantDrafted;
    CATAngle   _DraftAngle; // -999. if not Drafted - Champ utilise aussi pour l'angle des extrusions locales
};

INLINE CATPadPocketManifoldAttribute *CATPadPocketManifoldAttribute::GetAsPadPocketManifoldAttribute()
{
    return (CATPadPocketManifoldAttribute *) this;
}
#endif

