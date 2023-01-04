// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// Zus: Feature recognition -- Hole Attribute -- | Feature level attribute |
// --------------------------------------------------------------------------------------//


#ifndef CATHoleManifoldAttribute_H
#define CATHoleManifoldAttribute_H

#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATExtrusionManifoldAttribute.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"
#include "CATCellManifoldHoleNavigator.h"

class CATCylindricalExtrusionUtilities;
class CATMathVector;

class ExportedByPersistentCell CATHoleManifoldAttribute : public CATExtrusionManifoldAttribute
{
public:
    CATCGMDeclareAttribute (CATHoleManifoldAttribute, CATExtrusionManifoldAttribute);

    CATHoleManifoldAttribute(); 
    //Old Constructor - DO NOT use in new evolutions
    CATHoleManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATFace const & iExtrudeFaces, ListPOfCATFace const & iSupportFaces, ListPOfCATFace const & iClogFaces, ListPOfCATFace const & iExitFaces, CATCellManifoldHoleNavigator::CATHoleType iHoleType);
    //Old Constructor - DO NOT use in new evolutions
    CATHoleManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATCellManifold const & iExtrudeCMs, ListPOfCATCellManifold const & iSupportCMs, ListPOfCATCellManifold const & iClogCMs, ListPOfCATCellManifold const & iExitCMs, CATCellManifoldHoleNavigator::CATHoleType iHoleType);

    //New Constructor - USE THIS IN NEW EVOLUTIONS
    CATHoleManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, 
        ListPOfCATPrototypeExtrusion const & iPrototypeList, 
        ListPOfCATCellManifold const & iSupportCMs, 
        ListPOfCATCellManifold const & iSupportDecoCMs, 
        ListPOfCATCellManifold const & iEndCMs, 
        ListPOfCATCellManifold const & iEndDecoCMs, 
        ListPOfCATCellManifold const & iExitCMs,
        CATCellManifoldHoleNavigator::CATHoleType iHoleType);
    virtual ~CATHoleManifoldAttribute();

    CATHoleManifoldAttribute(CATHoleManifoldAttribute& iToCopy); // Forbidden
    CATHoleManifoldAttribute& operator= (const CATHoleManifoldAttribute& iToCopy); // Forbidden
    virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
    virtual void Move3D(CATTransfoManager& iTransfoManager);

    CATCGMNewClassArrayDeclare;      // Pool allocation

    //Methods
    virtual CATCellManifoldHoleNavigator::CATHoleType GetHoleType() const;

    virtual HRESULT GetSimpleHoleParameters(double & oDiameter) const;
    virtual HRESULT GetTaperedHoleParameters(double & oDiameter, CATAngle & oCountersinkAngle) const;
    virtual HRESULT GetCountersunkHoleParameters(double & oPrimaryDiameter, CATAngle & oCountersinkAngle) const;
    virtual HRESULT GetCounterboredHoleParameters( double & oPrimaryDiameter, double & oCounterboreDiameter) const;
    virtual HRESULT GetCounterdrilledHoleParameters(double & oPrimaryDiameter, double & oCounterdrillDiameter, CATAngle & oCounterdrillAngle) const;

    virtual HRESULT GetHoleSignature( CATLISTV(CATFeaturePiece) & oHolePieces, CATLiveBody const & iLiveBody) const;

    virtual void GetClogType( CATCellManifoldHoleNavigatorInterface::CATHoleClogType & oClogType, CATAngle &oAngle) const;

    virtual void SetIntermediateFaces(ListPOfCATFace &iIntermediateFaces); //DO NOT use in new evolutions
    virtual void GetIntermediateFaces(ListPOfCATFace &oIntermediateFaces) const;  //DO NOT use in new evolutions

    virtual CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody* iLiveBody, const CATTopData& iTopData, CATCellManifoldGroup* iGroup) const;

    virtual void Stream(CATCGMStream & ioStream) const;
    virtual void UnStream(CATCGMStream& ioStream);  
    virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

    virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
    INLINE virtual CATHoleManifoldAttribute *GetAsHoleManifoldAttribute();
    double GetMinDiameter() const;
    double GetMaxDiameter() const;
    double GetDepth() const;
    void GetAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const;
    void GetConeDiameter(double & oMin, double & oMax) const;
    void IsConicalFace(ListPOfCATFace &iFaces, CATBoolean & oYN) const;
    void CalculateDepthForTaperedHole(const CATMathLine & iAxis);
    void CalculateAdditionalDepthForBoredAndDrilled(const CATMathLine & iAxis);
    void CalculateAdditionalDepthForCounterSunkHole(const CATMathLine & iAxis);
    double GetAdditionalDepth() const;

protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                     const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager &iCellManifoldsManager) const;
private:
    virtual double GetRadius() const;


    // DATA MEMBERS
    CATCellManifoldHoleNavigator::CATHoleType _HoleType;
    CATCylindricalExtrusionUtilities* helper;
    //cached data (not streamed)
    double _additionalDepth;
    CATBoolean _additionalDepthHasBeenCalculated;

    // LEGACY DATA MEMBERS (Not used anymore; We can't get rid of these data members)
    ListPOfCATFace   _IntermediateFaces;
};

INLINE CATHoleManifoldAttribute *CATHoleManifoldAttribute::GetAsHoleManifoldAttribute()
{
    return (CATHoleManifoldAttribute *)this;
}
#endif


