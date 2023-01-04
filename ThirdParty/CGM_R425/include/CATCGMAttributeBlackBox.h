/* -*-c++-*- */
#ifndef CATCGMAttributeBlackBox_H
#define CATCGMAttributeBlackBox_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATCGMAttributeBlackBox:
// Class representing a group of read objects not usable in current version.
//
//=============================================================================
// Dec. 98   Creation                                         JM Houdouin (JHN)
//=============================================================================

#include "YP0LOGRP.h"               
#include "CATCGMStreamAttribute.h" 
#include "CATCGMAttributeGreyBox.h"
#include "CATCGMStreamImpl.h"
#include "CATCGMNewArray.h"


///============================================================================
/**
* Group of read objects unable to be used by current version.
* <p>
* Such object is built when unstreaming a container that has been streamed with
* another version than the current one. Inside such object, those kinds of
* objects will be put :
* <ul>
* <li>objects that cannot be understood by the current version
* <br>(because their type has evolved so that objects are no longer readable,
* <br>or because their type has appear after the current version)
* <li>objects that request one of the not-understood objects
* <br>(i.e. a surface lying on a not-understood curve)
* <li>objects requested by one of the not-understood objects
* <br>(i.e. a curve belonging to the definition of a not-understood surface)
* </ul>
* <p>
* It will be possible to know what are the objects required by a given object as
* far as the way to stream an object respect the rule of putting the list of
* linked objects as a prefix just after the object header.
* <br>(see CATCGMComposedStream class about it)
*/
class ExportedByYP0LOGRP CATCGMAttributeBlackBox : public CATCGMStreamAttribute
{
  CATCGMDeclareAttribute(CATCGMAttributeBlackBox , CATCGMStreamAttribute);
public:
  CATCGMAttributeBlackBox();
  ~CATCGMAttributeBlackBox();
  CATCGMNewClassArrayDeclare;

  static void SearchAttributeDef(const char * Appli, 
    const char * localname,
    CATLONG32 versioning,
    const  CATCGMAttributeDef * &);

	CATCGMAttributeGreyBox* & GetGreyBox();
	void SetGreyBox(CATCGMAttributeGreyBox* & iGreyBox);

  void Stream(CATCGMStream &) const;
  void UnStream(CATCGMStream &);
  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  void SetDef(CATULONG32  );
  void UnstreamBox(CATCGMStream & Str,CATULONG32  lgdata);
  void FindDef(CATCGMAttributeDef * & curdef);
  static void FindDefFromID(const CATCGMAttributeDef * curdef,
    CATULONG32  & numdef);
protected :
  virtual CATLONG32 Compare(const CATCGMAttribute & newattr);
private :
	CATCGMAttributeGreyBox*  _GreyBox; // Control information for streaming attribute
  CATCGMStream * _StreamData;  // streamed data which can not be read
  // number of referenced attribute definition in the array ReferencedDefs
  CATULONG32  numdef;
  // list of attributes referenced but not found during the session
  static CATCGMAttributeDef ** ReferencedDefs;
  // numbor of attribute definitions referenced but not found
  static CATULONG32  nbdef;
  // number of possible element in the array Referenced Defs
  static CATULONG32  maxdef;
};


CATCGMAttributeBlackBox * CreateBlackBox(const CATCGMAttributeDef *, CATCGMAttributeGreyBox* & GreyBox);
//extern ExportedByYP0LOGRP CATCGMAttrId UAIDName (CATCGMAttributeBlackBox);
extern void CastTo(CATCGMAttribute *, CATCGMAttributeBlackBox *&);


#endif
