// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATPairingManifoldAttribute
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================

#ifndef CATPairingManifoldAttribute_H
#define CATPairingManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATManifoldGroupAttribute.h"
#include "ListPOfCATFace.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATCell;
class CATCellManifold;

class ExportedByPersistentCell CATPairingManifoldAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATPairingManifoldAttribute, CATManifoldAttribute);

  CATCGMNewClassArrayDeclare; // Pool allocation

  CATPairingManifoldAttribute(); 
  virtual ~CATPairingManifoldAttribute();

  // Cast
  virtual CATPairingManifoldAttribute * GetAsPairingManifoldAttribute();
  
  virtual CATManifoldAttribute * CreateImageManifoldAttribute(CATLiveBody & iLiveBody, CATLISTP(CATManifoldAttribute) & iParentManifoldAttributes) const;

  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute & iOtherManifoldAttribute)const;

  virtual CATManifoldAttribute * Clone(CATCloneManager & iCloneManager) const;
  virtual void Move3D(CATTransfoManager & iTransfoManager);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream & ioStream);

  virtual void Dump(CATCGMOutput & oStr) const;
  virtual void GetColor(int & oRed, int & oGreen, int & oBlue) const;

public :

  CATLONG32 AppendPairingCellManifolds( CATCellManifold * iCM1, CATCellManifold * iCM2, double iMaxDist );

  // Returns the pairing index, starting at 0 (-1 if pairing not found)
  CATLONG32 FindPairing( CATCellManifold * iCM1, CATCellManifold * iCM2, double & oMaxDist );

  CATLONG32 GetNbPairings() const;
  HRESULT GetPairing( CATLONG32 iIndex, CATCellManifold *& oCM1, CATCellManifold *& oCM2, double & oMaxDist );

protected:

  CATPairingManifoldAttribute * Clone() const;

  virtual void Write(CATCGMStream & ioStream) const;
  virtual void Read(CATCGMStream & ioStream);

  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iListOfParentGroups, 
                                                      const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                      CATCellManifoldsManager              & iCellManifoldsManager) const;

  short _PairingStreamVersion; // Version du stream

protected:

  struct CATPairingCellManifolds
  {
    CATCellManifold * _CM1;
    CATCellManifold * _CM2;
    double            _MaxDist;

    CATPairingCellManifolds() : _CM1(NULL), _CM2(NULL), _MaxDist(0.) {}
    ~CATPairingCellManifolds() { _CM1 = NULL; _CM2 = NULL; _MaxDist = 0.; }
  };

  void ResizeTabOfPairingCM( CATLONG32 iSize );

  CATLONG32                 _SizeOfTab;
  CATLONG32                 _NbPairingCM;
  CATPairingCellManifolds * _TabOfPairingCM;
};

INLINE CATLONG32 CATPairingManifoldAttribute::GetNbPairings() const {
  return _NbPairingCM; }

#endif /* CATPairingManifoldAttribute_H */
