// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATVGraph.h
//
//===================================================================
//
// Valued Graph 
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATVGraph_h
#define CATVGraph_h

#include "CATMathematics.h"
#include "ListPOfCATVLink.h"
#include "ListPOfCATVNode.h"
#include "ListPOfCATVGraphMap.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATErrorDef.h"
#include "CATCGMNewArray.h"
#include "CATVGraphOptions.h"

class CATSoftwareConfiguration;
class CATCGMProgressBar;

class ExportedByCATMathematics CATVGraph
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;        // Pool allocation
  virtual ~CATVGraph();

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  HRESULT IsEqual(const CATVGraph& iGraph) const;
  HRESULT SeekSubGraph(CATVGraph& iSough, ListPOfCATVGraphMap& oInstances, CATCGMProgressBar *iProgressBar = NULL); 
  virtual void DeleteNodes(ListPOfCATVNode& iToDelete);
  virtual ListPOfCATVNode GetNonReusableNodes(const ListPOfCATVNode& iUsedNodes) const;
  int SubGraphLinkCount(const ListPOfCATVNode& iSubGraph) const;
  virtual void Dump(ostream& ioOS);

  //-----------------------------------------------------------------------------
  // Data access
  //-----------------------------------------------------------------------------
  INLINE const CATVNode* Node(const int iNode) const { return _Nodes[iNode]; };
  INLINE const CATVLink* Link(const int iLink) const { return _Links[iLink]; };
  INLINE const int       NodeCount()           const { return _Nodes.Size(); }
  INLINE const int       LinkCount()           const { return _Links.Size(); }

protected:
  INLINE CATSoftwareConfiguration* GetConfig() const { return _Config; }
  INLINE const CATVGraphOptions& GetOptions() const { return _Options; }
  CATVGraph(CATSoftwareConfiguration *iConfig, CATVGraphOptions iOptions, ListPOfCATVNode& ioNodes, ListPOfCATVLink& ioLinks);
  INLINE const ListPOfCATVNode& Nodes() const { return _Nodes; };
  virtual CATVGraphMap* CreateGraphMap(CATVGraph *iSough);
  void ResetInactiveNodes();
  HRESULT ReorderNodes(ListPOfCATVNode &iReorderedNodes);

private:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATVGraph(const CATVGraph& iToCopy); 
  CATVGraph& operator=(const CATVGraph&);  
  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  CATSoftwareConfiguration *_Config;
  CATVGraphOptions _Options;
  ListPOfCATVNode _Nodes; 
  ListPOfCATVLink _Links;
  //-----------------------------------------------------------------------------
};

#endif
