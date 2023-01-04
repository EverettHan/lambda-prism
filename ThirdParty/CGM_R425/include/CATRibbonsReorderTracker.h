/* -*-c++-*- */
#ifndef CATRibbonsReorderTracker_h
#define CATRibbonsReorderTracker_h

//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010

//===================================================================
//===================================================================
//
// Class dedicated to get information on actual ribbons reordering inside a CATDynFillet 
//
//===================================================================

//===================================================================
// Usage notes:
// Assign such a CATRibbonsReorderTracker to a CATDynFillet before run
// Get information from this CATRibbonsReorderTracker after CATDynFillet run
//===================================================================

//===================================================================
// Sept. 2010  Creation      R. Rorato
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibObject.h"
#include "CATMathInline.h"
#include "ListPOfCATGMRibbonFaceSpec.h"
#include "ListPOfListPOfCATFace.h"
#include "CATFilletDefine.h"
#include "CATChamferDefine.h" 

class CATFace;
class CATGMRibbonFaceSpec;
class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATDynFilletRibbon;

#include "CATCGMNewArray.h"
#include "CATSafe.h"
CATSafeDefine(CATRibbonsReorderTracker);

class ExportedByPersistentCell CATRibbonsReorderTracker : public CATTopRibObject
{
  public :

  CATRibbonsReorderTracker(CATSoftwareConfiguration* iConfig, const CATBoolean iActivateFilletFaceSpec=FALSE); 
  
  //------------------------------------------------------------------------------
  // Return index (1, 2, 3, etc...) of ribbons set which has created this face
  // Return 0 if face is not known as created by the Fillet
  //------------------------------------------------------------------------------
  INLINE int GetIndex(CATFace* iFace); 
  void ActivateFilletFaceSpec();

  //------------------------------------------------------------------------------
  // Dump
  //------------------------------------------------------------------------------
  void Dump(CATCGMOutput& ioOS);

  //------------------------------------------------------------------------------
  // Delete
  //------------------------------------------------------------------------------
  ~CATRibbonsReorderTracker();

  //------------------------------------------------------------------------------
  // Fillet internal area. Do not use.
  //------------------------------------------------------------------------------
  void AppendNewFaceList(CATLISTP(CATFace)& iNewFaceList);
  void UpdateWithJournal(CATCGMJournalList* iJournal);
  void RemoveAll();
  //------------------------------------------------------------------------------
  void SetFilletFaceSpec(CATFace& iFace, const CATFilletType iFilletType, const double iRadius, const CATFilletRadiusType iRadiusType, const CATFilletSectionType iSectionType, const double iShapeParameter, CATGeometry* iSupport1, CATGeometry* iSupport2, CATDynFilletRibbon* iRibbon);
  void SetChamferFaceSpec(CATFace& iFace, const CATLONG32 iChamferType, const double iValue1, const double iValue2, CATGeometry* iSupport1, CATGeometry* iSupport2, CATDynFilletRibbon* iRibbon);
  HRESULT GetRadius(CATFace& iFace, double& oRadius);
  HRESULT GetRadiusType(CATFace& iFace, CATFilletRadiusType& oRadiusType);
  HRESULT GetSectionType(CATFace& iFace, CATFilletSectionType& oSectionType);
  static HRESULT GetChamferSpec(CATFace& iFace, CATLONG32& oChamferGetType, double& oValue1, double& oValue2, CATGeometry*& oSupport1, CATGeometry*& oSupport2, CATDynFilletRibbon*& oRibbon);
  static HRESULT GetFilletSpec(CATFace& iFace, CATFilletType& oFilletType, double & oRadius, CATFilletRadiusType & oRadiusType, CATFilletSectionType & oSectionType, double & oShapeParameter, CATGeometry*& oSupport1, CATGeometry*& oSupport2, CATDynFilletRibbon*& oRibbon);
  void PropagateRibbonFaceSpec(CATCGMJournalList& iJournal);
  static void CleanRibbonFaceSpec(ListPOfCATFace& iFaces);

  CATBoolean IsUpToDateWithSpec(CATFace& iFace) const;
  void SetUpToDateWithSpec(CATFace& iFace);
  void AssignSpecToRibbon(CATFace& iFace, CATDynFilletRibbon* iRibbon);
  void SetSpecsSupportFaces(CATLISTP(ListPOfCATFace) &iFaces);
  void GetSpecsSupportFaces(CATLISTP(ListPOfCATFace) &oFaces);
  void GetRRTFaces(CATLISTP(ListPOfCATFace)& oFaces);

  //--------------- ---------------------------------------------------------------
  CATCGMNewClassArrayDeclare;        // Pool allocation
  //------------------------------------------------------------------------------
  private:
  void PropagateRibbonFaceSpec(CATFace& iFace, const CATLISTP(CATGeometry)& iNewObjects);
  void Assign(CATGMRibbonFaceSpec& iFaceSpec, CATFace& iFace);
  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
  // Packages of Faces
  //------------------------------------------------------------------------------
  CATLISTP(ListPOfCATFace)   _Faces;
  //------------------------------------------------------------------------------
  // Packages of SupportFaces for each & every LiveFillet DynEdgeFilletRibbon
  // To be cleaned in R419 level by changing CAA interface like Chamfer itf
  //------------------------------------------------------------------------------
  CATLISTP(ListPOfCATFace)   _SpecsSupportFaces;
  //------------------------------------------------------------------------------
  // Fillet internal use only to track ribbons into output body
  //------------------------------------------------------------------------------
  ListPOfCATGMRibbonFaceSpec _RibbonFaceSpecs; // Can only be used by copy
  ListPOfCATFace             _RibbonFaces;     // May have been erased
  CATBoolean                 _ActivateFilletFaceSpec;

  //------------------------------------------------------------------------------
  CATSoftwareConfiguration*  _Config;
  //------------------------------------------------------------------------------
};

INLINE int CATRibbonsReorderTracker::GetIndex(CATFace* iFace)
{
  for ( int i=_Faces.Size(); i>0; i-- )
  {
    CATLISTP(CATFace)* FaceList = _Faces[i];
    if ( FaceList && FaceList->Locate(iFace) )
      return i;
  }
  return 0;
}

#endif
