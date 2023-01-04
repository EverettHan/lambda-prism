// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATVNode.h
//
//===================================================================
//
// Node of CATVGraph
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATVNode_h
#define CATVNode_h

#include "CATMathematics.h"
#include "ListPOfCATVNode.h"
#include "ListPOfCATVLink.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h" // build aix
#include "CATCGMNewArray.h"
#include "CATHTableVNodeAssocVLinks.h"

class CATSoftwareConfiguration;
class CATVLink;

class ExportedByCATMathematics CATVNode
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATVNode(CATSoftwareConfiguration *iConfig);
  CATCGMNewClassArrayDeclare;        // Pool allocation
  virtual ~CATVNode();
  virtual CATVNode* Clone() const;
  void AddLink(CATVLink* iLink);
  void RemoveLink(CATVLink* iLink);
  virtual void DumpValue(ostream& ioOS) const;

  //-----------------------------------------------------------------------------
  // Data access
  //-----------------------------------------------------------------------------
  INLINE int LinkCount() const { return _Links.Size(); }
  INLINE CATVLink* Link(const int iLink) { return _Links[iLink]; }
  INLINE const CATVLink* Link(const int iLink) const { return _Links[iLink]; }

  //-----------------------------------------------------------------------------
  // Customisation
  //-----------------------------------------------------------------------------
  virtual CATULONG32 GetTag() const;

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  CATBoolean IsLinkedTo(CATVNode &iNode) const;
  CATBoolean IsLinkedTo(ListPOfCATVNode& iNodes) const;
  void Dump(ostream& ioOS) const; 
  void GetLinkedNodes(ListPOfCATVNode& oLinkedNodes) const;
  void GetCommonLinkedNodes(CATVNode& iNode, ListPOfCATVNode& oCommonLinkedNodes) const;

  //-----------------------------------------------------------------------------
  // CGM internal Use. 
  //-----------------------------------------------------------------------------
  virtual HRESULT HasSameValue(const CATVNode& iNode) const;
  void SetTag(const CATULONG32 iTag);
  virtual HRESULT FindSameValueLink(CATVLink& iRefLink, CATVNode* iRefNode1, CATVNode* iRefNode2, CATVNode* iTargetNode);
  
  INLINE CATBoolean IsInactive() const { return _IsInactive; }
  INLINE void SetInactive(CATBoolean iIsInactive) { _IsInactive = iIsInactive; }

protected:
  INLINE CATSoftwareConfiguration* GetConfig() const { return _Config; }

private:
  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  CATSoftwareConfiguration *_Config;
  CATULONG32         _Tag;
  ListPOfCATVLink    _Links;
  CATHTableVNodeAssocVLinks _LinkedNodesHT;
  CATBoolean _IsInactive;
  //-----------------------------------------------------------------------------
};

#endif
