// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Attribute -- | Generic level attribute |
// --------------------------------------------------------------------------------------//


#ifndef CATExtrusionManifoldAttribute_H
#define CATExtrusionManifoldAttribute_H

#include "CATPersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathVector.h"
#include "CATListOfCATPrototypeExtrusion.h"
#include "CATPrototypeExtrusion.h"
#include "CATFeaturePiece.h"
#include "ListVOfCATFeaturePiece.h"

class CATCloneManager;
class CATTransfoManager;
class CATPadPocketManifoldAttribute;
class CATHoleManifoldAttribute;
class CATSlotManifoldAttribute;
class CATNotchManifoldAttribute;
class CATSoftwareConfiguration;

class ExportedByPersistentCell CATExtrusionManifoldAttribute : public CATManifoldAttribute
{
	friend class CATExtrusionUtilities;

public:
  CATCGMDeclareAttribute (CATExtrusionManifoldAttribute, CATManifoldAttribute);

  CATExtrusionManifoldAttribute(); // required for CATCGMImplAttribute macro
  
  //Old Constructor - DO NOT use in new evolutions
  CATExtrusionManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATFace const & iExtrudeFaces, ListPOfCATFace const & iSupportFaces, ListPOfCATFace const & iEndFaces, ListPOfCATFace const & iExitFaces);
  //Old Constructor - DO NOT use in new evolutions
  CATExtrusionManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, ListPOfCATCellManifold const & iExtrudeCMs, ListPOfCATCellManifold const & iSupportCMs, ListPOfCATCellManifold const & iEndCMs, ListPOfCATCellManifold const & iExitCMs);

  //New Constructor - USE THIS IN NEW EVOLUTIONS
  CATExtrusionManifoldAttribute(CATSoftwareConfiguration* ipConfig, CATMathVector const & iExtrudeDir, 
	  ListPOfCATPrototypeExtrusion const & iPrototypeList, 
	  ListPOfCATCellManifold const & iSupportCMs, 
	  ListPOfCATCellManifold const & iSupportDecoCMs, 
	  ListPOfCATCellManifold const & iEndCMs, 
	  ListPOfCATCellManifold const & iEndDecoCMs, 
	  ListPOfCATCellManifold const & iExitCMs);

  virtual ~CATExtrusionManifoldAttribute();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
                           CATCGMLinkType           iLinkType,
                           CATRCOLL(int)*           oSharedStatus,
                           CATLISTV(CATString)*     oLinksString);

  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream); 
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  CATBoolean   DecorationStreamed() const; // vrai si les decorations sont streamees dans la fille

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;
  virtual CATBoolean CompareFaceLists(const ListPOfCATFace &iThisFaceList, const ListPOfCATFace &iOtherFaceList, CATBoolean iPrintDebugInfo=TRUE) const;
  CATBoolean ComparePrototypeList(const ListPOfCATPrototypeExtrusion &iThisFaceList, const ListPOfCATPrototypeExtrusion &iOtherFaceList) const;
  CATBoolean CompareCMList(const ListPOfCATCellManifold &iThisList, const ListPOfCATCellManifold &iOtherList) const;

  virtual void GetDirection(CATMathVector& oDirection) const;

  virtual int  GetBothSideDirectionState();
  virtual void SetBothSideDirectionState(int iState);

  virtual void GetExtrFaces(ListPOfCATFace &oFaces) const;
  virtual void GetSupports(ListPOfCATFace &oFaces) const;
  virtual void GetEnds(ListPOfCATFace &oFaces) const;
  virtual void GetExits(ListPOfCATFace &oFaces) const;
  virtual void GetSupportDressUps(ListPOfCATFace &oFaces) const;
  virtual void GetEndDressUps(ListPOfCATFace &oFaces) const;
  virtual void SetSupportDressUps(ListPOfCATFace &iFaces);
  virtual void SetEndDressUps(ListPOfCATFace &iFaces);

  virtual void GetPrototypeList(ListPOfCATPrototypeExtrusion &oList) const;
  virtual void GetExtrManifolds(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetTransitionManifolds(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetSupports(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetEnds(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetExits(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetSupportDressUps(ListPOfCATCellManifold &oManifolds) const;
  virtual void GetEndDressUps(ListPOfCATCellManifold &oManifolds) const;
  virtual void SetSupportDressUps(ListPOfCATCellManifold const &iManifolds);
  virtual void SetEndDressUps(ListPOfCATCellManifold const &iManifolds);

  //virtual int  GetType() const;
  //virtual void SetType(int & iType);

  INLINE virtual short GetStreamVersion() const;
  INLINE virtual void  SetStreamVersion(short & iVersion);

  INLINE virtual CATExtrusionManifoldAttribute *GetAsExtrusionManifoldAttribute();

  //ST5: GetAs methods for classes inheriting from this: PadPocket, Hole, Slot, Notch etc.
  INLINE virtual CATPadPocketManifoldAttribute *GetAsPadPocketManifoldAttribute();  
  INLINE virtual CATHoleManifoldAttribute      *GetAsHoleManifoldAttribute();
  INLINE virtual CATSlotManifoldAttribute      *GetAsSlotManifoldAttribute(); 
  INLINE virtual CATNotchManifoldAttribute     *GetAsNotchManifoldAttribute();

	static void UnStreamFaceList(CATCGMStream& ioStream, CATICGMContainer* ipContainer, ListPOfCATFace & oFaceList);
	static void StreamFaceList(CATCGMStream& ioStream, const ListPOfCATFace & iList);

	static void UnStreamCellManifoldList(CATCGMStream& ioStream, CATICGMContainer* ipContainer, ListPOfCATCellManifold & oCMList);
	static void StreamCellManifoldList(CATCGMStream& ioStream, const ListPOfCATCellManifold & iList);

	static void UnStreamPrototypeExtrusionList(CATCGMStream& ioStream, CATICGMContainer* ipContainer, ListPOfCATPrototypeExtrusion & oList);
	static void StreamPrototypeExtrusionList(CATCGMStream& ioStream, const ListPOfCATPrototypeExtrusion & iList);

protected:
  void CloneData(CATCloneManager& iCloneManager, CATExtrusionManifoldAttribute& oCloned) const;

  short            _StreamVersion; //Version du stream

  CATGeoFactory*    GetFactory() const;
  CATSoftwareConfiguration*    GetConfig() const;

  CATBoolean GetFeaturePiece(ListPOfCATCellManifold const & iManifolds, CATLiveBody const & iLiveBody, CATFeaturePiece & oFeaturePiece) const;
  CATLISTV(CATFeaturePiece) GetFeaturePiece(ListPOfCATPrototypeExtrusion const & iPrototypeExtrusionList, CATLiveBody const & iLiveBody) const;

private:
  CATMathVector    _ExtrudeDir;               // Extrusion direction
  int              _BothSideDirectionState;   // PRL 27/04/2016: -1/0/1 [-1 = undef, 1 = if both direction and reverse direction are convenient (e.g. simple hole a cuboid), else 0] 

  // LEGACY DATA MEMBERS (Not used anymore; We can't get rid of these data members)
  ListPOfCATFace   _ExtrudeFaces;  //face of the extrusion 
  ListPOfCATFace   _SupportFaces;  //support of the extrusion 
  ListPOfCATFace   _EndFaces;      //End of the extrusion 
  ListPOfCATFace   _ExitFaces;      //Exit faces of the extrusion 
  ListPOfCATFace   _SupportDressUpFaces; //contextual manifold faces connected to support faces
  ListPOfCATFace   _EndDressUpFaces; //contextual manifold faces connected to end faces

  // NEW DATA MEMBERS
  ListPOfCATPrototypeExtrusion _PrototypeList; // contains the extrusions
  ListPOfCATCellManifold   _SupportManifolds;  //support of the extrusion 
  ListPOfCATCellManifold   _EndManifolds;      //End of the extrusion 
  ListPOfCATCellManifold   _ExitManifolds;      //Exit manifolds of the extrusion 
  ListPOfCATCellManifold   _SupportDressUpManifolds; //contextual manifolds connected to support manifolds
  ListPOfCATCellManifold   _EndDressUpManifolds; //contextual manifolds connected to end manifolds

  // bad design choice - the _ExtrusionType data member has never been streamed or unstreamed!
  // so, why does this data member exist?!
  //int						_ExtrusionType; //0=Undefined; 1=Protrusion; 2=Depression  

  CATSoftwareConfiguration* _pConfig;

  short CompareCells(const CATCell *iRefCell, const CATCell *iResultCell) const;

  void AddMemberAsLink(ListPOfCATCellManifold const & iCMs);
  void AddMemberAsLink(ListPOfCATPrototypeExtrusion const & iPrototypeList);
  void AddMemberAsLink(CATPrototypeExtrusion const & iPrototype);

};

INLINE short CATExtrusionManifoldAttribute::GetStreamVersion() const
{
  return _StreamVersion;
}

INLINE void CATExtrusionManifoldAttribute::SetStreamVersion(short & iVersion)
{
  _StreamVersion = iVersion;
}

INLINE CATExtrusionManifoldAttribute *CATExtrusionManifoldAttribute::GetAsExtrusionManifoldAttribute() 
{
  return this;
}

INLINE CATPadPocketManifoldAttribute *CATExtrusionManifoldAttribute::GetAsPadPocketManifoldAttribute()
{
  return NULL;
}

INLINE CATHoleManifoldAttribute *CATExtrusionManifoldAttribute::GetAsHoleManifoldAttribute()
{
  return NULL;
}

INLINE CATSlotManifoldAttribute *CATExtrusionManifoldAttribute::GetAsSlotManifoldAttribute()
{
  return NULL;
}

INLINE CATNotchManifoldAttribute *CATExtrusionManifoldAttribute::GetAsNotchManifoldAttribute()
{
  return NULL;
}



#endif

