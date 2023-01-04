// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATVGraphMap.h
//
//===================================================================
//
// Class dedicated to map 2 CATVGraph
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#include "CATErrorDef.h"
#ifndef CATVGraphMap_h
#define CATVGraphMap_h

#include "ListPOfCATVNode.h"
#include "ListPOfCATVGraphMap.h"
#include "CATListOfInt.h"
#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATHTableVNode.h"
#include "CATVGraphOptions.h"

class CATSoftwareConfiguration;
class CATVGraph;
class CATVLink;
class CATVNode;
class CATCGMProgressBar;

class ExportedByCATMathematics CATVGraphMap
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATVGraphMap(CATSoftwareConfiguration *iConfig, CATVGraphOptions iOptions, const CATVGraph* iGraph1, const CATVGraph* iGraph2);
  ~CATVGraphMap();

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  HRESULT Run(CATCGMProgressBar *iProgressBar = NULL, int *ioNumberOfNodeTreated = NULL); // S_OK => Same graphs, S_FALSE => Different graphs, E_FAIL => ...?, E_OUTOFMEMORY =>...? E_UNEXPECTED => ...?
  CATVGraphMap* ExtractMapping();
  const ListPOfCATVNode& GetMappedNodes(const int iIndex) const;
  void Insert(const int iPosition, CATVNode* iNode2);
  HRESULT Reorder(const CATListOfInt& iOrder);

  //-----------------------------------------------------------------------------
  // Debug
  //-----------------------------------------------------------------------------
  void Dump() const;

protected:
  INLINE CATSoftwareConfiguration* GetConfig() const { return _Config; }
  INLINE const CATVGraphOptions& GetOptions() const { return _Options; }
  virtual void SetProgress(CATCGMProgressBar *iProgressBar, double iValue, double iTotalValue);
  virtual CATBoolean CheckSubGraph();

private:
  void DumpDepthAsTabs();

  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATVGraphMap(const CATVGraphMap& iMap, CATVNode& iNode1, CATVNode& iNode2, const CATBoolean iResetMap = FALSE);

  //-----------------------------------------------------------------------------
  // Search internal components
  //-----------------------------------------------------------------------------
  HRESULT ValidateLastMapItem(); 
  HRESULT CreateCandidates();
  CATBoolean InactivateNodes(const ListPOfCATVNode& iNodes); // return TRUE if this candidate should be removed
  void AddMappedNodes(CATVNode &iNodeInGraph0, CATVNode &iNodeInGraph1);

  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  CATSoftwareConfiguration *_Config;
  CATVGraphOptions _Options;
  const CATVGraph*    _Graph  [2];
  ListPOfCATVNode     _Mapped [2];  // Mapped nodes, sync-ed lists
  CATHTableVNode      _MappedHTable[2]; // mapped nodes, not synced but quicker search
  ListPOfCATVGraphMap _Candidates;  // Mappings to be tested
  //CATHTableVNode      _Inactivated; // Already Mapped nodes in _Graph[1] => to be ignored
  //-----------------------------------------------------------------------------
};

#endif
