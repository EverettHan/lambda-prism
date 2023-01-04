#ifndef CATThreadSpecParams_H
#define CATThreadSpecParams_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2015
//-----------------------------------------------------------------------------
// RESPONSIBLE  : LAP
//
// DESCRIPTION  : Encapsulate and carry numerical data for CATCMDRepGroupThread Object.
//                Desgined to be use with CATCellManifoldGroup architecture
//
//
// -----------------------------------------------------------------------------
// Creation QF2 October 2015
//
//=============================================================================

#include "CATCGMNewArray.h"
#include "CATGroupSpecParams.h"
#include "CATMathInline.h"
#include "CATMathAxis.h"

#include "CATString.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"

class CATCellManifoldGroup;
class CATCellManifoldsManager;

class CATThreadSpecParams : public CATGroupSpecParams
{

public:
  CATCGMDeclareAttribute (CATThreadSpecParams, CATGroupSpecParams);

  CATThreadSpecParams(); // Default constructor is mandatory
  CATThreadSpecParams(CATMathAxis &iAxis, 
                        double iDepth, double iDiameter, double iNominalDiameter, double iPitch, int iSens, double iSupportDiameter, 
                         CATString &iThreadDescription, int iThreadType, int iDisplayInDrafting, CATString &iKeyOfThread);

  virtual ~CATThreadSpecParams();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  void  GetAxis(CATMathAxis &oThreadAxis) const;

  INLINE double GetDepth() const;
  INLINE double GetDiameter() const;
  INLINE double GetNominalDiameter() const;
  INLINE double GetPitch() const;
  INLINE CATLONG32 GetSensThread() const;
  INLINE double GetSupportDiameter() const;
  
  INLINE CATString  GetThreadDescription() const;
  INLINE CATLONG32  GetThreadType() const; // 0 for Thread, 1 for a Tap
  INLINE CATLONG32  GetDisplayInDrafting() const;
  INLINE CATString  GetKeyOfThread() const;

  void   GetNumericalParam(double &oDepth, double &oDiameter, double &oNominalDiameter, double &oPitch, int &oSens, double &oSupportDiameter) const;
  void   GetDescriptionParam(CATString &oThreadDescription, int &oThreadType, int &oDisplayInDrafting, CATString &oKeyOfThread) const;

  // CATManifoldAttribute virtual methods to implement
  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  // Bodies Mapping
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

  // LiveBodyChecker : Check integrity, coherence between the Attribute and the topology.
  virtual HRESULT CheckConsistency(const CATLiveBody * iLiveBody, const CATCellManifoldGroup &iOwningGroup, CATCGMOutput *oDbgTraces=NULL) const;
  
  // ------------------------------------------------------------------------
  // Stream
  // ------------------------------------------------------------------------  
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 


protected:

  // CATManifoldAttribute virtual methods to implement
  virtual HRESULT CheckImageValidity(const CATLISTP(CATCellManifoldGroup) &iParentGroups, const CATCellManifoldGroup & iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  // CATManifoldAttribute virtual method
  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iParentGroups, 
                                                     const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager              & iCellManifoldsManager) const;

  virtual CATGroupSpecParams * ComputeImage (const CATCellManifoldsManager &iCellManifoldsManager,
                                               const CATMathTransformation    &iTransformation, 
                                               const ListPOfCATCellManifold   &iContextImageCMList, 
                                               const CATMathTransformation    *iContextualTransfo=NULL) const;


  virtual CATThreadSpecParams * GetAsThreadSpecParams() const;  
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;
  virtual void                  SetCurrentStreamVersion();	

private:

  // Copy contructor
  CATThreadSpecParams( const CATThreadSpecParams &iThreadSpecToCopy ); 

  INLINE void SetAxis(const CATMathAxis & iThreadAxis);
  void        MoveAxis (const CATMathTransformation &iTransformation, const CATMathTransformation &iContextualTransfo, CATMathAxis &oMovedAxis) const;
  HRESULT     ComputeImageOriginPoint(const CATCellManifoldsManager &iCellManifoldsManager, 
                                       const ListPOfCATCellManifold  &iContextImageCMList, 
                                       const CATMathLine &iImageAxisLine, 
                                       CATMathPoint &oImageOrigin) const;



  // Axis
  CATMathAxis   _Axis;

  // numerical data
  double  _Depth;
  double  _Diameter;
  double  _NominalDiameter;
  double  _Pitch;
  CATLONG32 _SensThread;      // 0 / 1
  double    _SupportDiameter;


  // description data
  CATString   _ThreadDescription;   // Standard name (M18, M24, ...)
  CATLONG32   _ThreadType;          // Filetage ou taraudage
  CATLONG32   _DisplayInDrafting;
  CATString   _KeyOfThread;         // ? sous standart ?...
  
};

// --------------------------------------------------------------------
INLINE void CATThreadSpecParams::GetAxis(CATMathAxis &oThreadAxis) const {
  oThreadAxis = _Axis; }

// --------------------------------------------------------------------
INLINE void CATThreadSpecParams::SetAxis(const CATMathAxis & iThreadAxis) {
	_Axis = iThreadAxis; }

// --------------------------------------------------------------------
INLINE double CATThreadSpecParams::GetDepth() const {
  return _Depth; }
// --------------------------------------------------------------------
INLINE double CATThreadSpecParams::GetDiameter() const {
  return _Diameter; }
// --------------------------------------------------------------------
INLINE double CATThreadSpecParams::GetNominalDiameter() const {
  return _NominalDiameter; }
// --------------------------------------------------------------------
INLINE double CATThreadSpecParams::GetPitch() const {
  return _Pitch; }
// --------------------------------------------------------------------
INLINE CATLONG32 CATThreadSpecParams::GetSensThread() const {
  return _SensThread; }
// --------------------------------------------------------------------
INLINE double CATThreadSpecParams::GetSupportDiameter() const {
  return _SupportDiameter; }
// --------------------------------------------------------------------
INLINE CATString CATThreadSpecParams::GetThreadDescription() const {
  return _ThreadDescription; }
// --------------------------------------------------------------------
INLINE CATLONG32 CATThreadSpecParams::GetThreadType() const {
  return _ThreadType; }
// --------------------------------------------------------------------
INLINE CATLONG32 CATThreadSpecParams::GetDisplayInDrafting() const {
  return _DisplayInDrafting; }
// --------------------------------------------------------------------

INLINE CATString CATThreadSpecParams::GetKeyOfThread() const {
  return _KeyOfThread; }
// --------------------------------------------------------------------

#endif

