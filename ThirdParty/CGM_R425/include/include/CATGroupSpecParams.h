#ifndef CATGroupSpecParams_H
#define CATGroupSpecParams_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2015
//-----------------------------------------------------------------------------
// RESPONSIBLE  : LAP
//
// DESCRIPTION  : Abstract class for CATGMDRepGroup. 
//                Purpose : To be derivated for carrying numerical data
//
//
// -----------------------------------------------------------------------------
// Creation QF2 October 2015
//
//=============================================================================

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATMathInline.h"

#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"

class CATThreadSpecParams;
class CATDeclarativeManifold;
class CATCellManifoldsManager;

class ExportedByPersistentCell CATGroupSpecParams : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATGroupSpecParams, CATManifoldAttribute);

  CATGroupSpecParams(); // Default constructor is mandatory
  virtual ~CATGroupSpecParams();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Mother class virtual methods
  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const = 0;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloner) const = 0;
  virtual void Move3D(CATTransfoManager& iTransfo) = 0;
  virtual void GetColor(int &oR, int &oG, int &oB) const = 0;



  INLINE virtual CATGroupSpecParams * GetAsGroupSpecParams() const;


protected:

  // CATManifoldAttribute virtual method
  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iParentGroups, 
                                                     const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager              & iCellManifoldsManager) const;

  virtual CATGroupSpecParams * ComputeImage(const CATCellManifoldsManager &iCellManifoldsManager,
                                            const CATMathTransformation   &iTransformation, 
                                            const ListPOfCATCellManifold  &iContextImageCMList, 
                                            const CATMathTransformation   *iContextualTransfo=NULL) const = 0;

  // Utilities
  // ----------------------------------------------------------------------------------------------------------------
  CATDeclarativeManifold * GetDeclarativeManifoldFromCMGroup (const CATCellManifoldGroup & iCellManifoldGroup) const;

  // Versioning Management
  virtual void  SetCurrentStreamVersion() = 0;
  short GetStreamVersion() const;
  void  SetStreamVersion(short iStreamVersion);



private :

  short   _StreamVersion; // Version du stream

};


INLINE CATGroupSpecParams *CATGroupSpecParams::GetAsGroupSpecParams() const {
  return (CATGroupSpecParams*) this; }

#endif

