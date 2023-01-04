// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATVLink.h
//
//===================================================================
//
// Link of CATVGraph
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATVLink_h
#define CATVLink_h

#include "CATMathematics.h"
#include "ListPOfCATVNode.h"
#include "CATMathInline.h"
#include "CATErrorDef.h"
#include "CATCGMNewArray.h"

class CATSoftwareConfiguration;
class CATVNode;

class ExportedByCATMathematics CATVLink
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATVLink(CATSoftwareConfiguration *iConfig, CATVNode* iNode1, CATVNode* iNode2);
  CATVLink(CATSoftwareConfiguration *iConfig);
  CATCGMNewClassArrayDeclare;        // Pool allocation
  virtual ~CATVLink();
  virtual CATVLink* Clone() const;

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  void Set(CATVNode* iNode1, CATVNode* iNode2);
  void Dump(ostream& ioOS) const; 
  INLINE CATVNode* LinkedNode(const CATVNode* iNode) const { if ( iNode==_Node[0] ) return _Node[1]; else if ( iNode==_Node[1] ) return _Node[0]; return NULL; };
  INLINE CATVNode* Node(const int iSide) const { return _Node[iSide]; };

protected:
  INLINE CATSoftwareConfiguration* GetConfig() const { return _Config; }

private:
  //-----------------------------------------------------------------------------
  // Customisation
  //-----------------------------------------------------------------------------
  virtual void DumpValue(ostream& ioOS) const;
  virtual HRESULT HasSameValue(const CATVLink& iLink, const int Orn) const;

  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  CATSoftwareConfiguration *_Config;
  CATVNode* _Node[2]; // Linked Nodes

  //-----------------------------------------------------------------------------
  // Internal service
  //-----------------------------------------------------------------------------
  static HRESULT AreEqual(const CATVLink& iLink1, const CATVNode* iNode11, const CATVNode* iNode12, const CATVLink& iLink2, const CATVNode* iNode21, const CATVNode* iNode22);

  //-----------------------------------------------------------------------------
  // friend classes
  //-----------------------------------------------------------------------------
  friend class CATVGraphMap;
  friend class CATVNode;
  //-----------------------------------------------------------------------------
};

#endif
