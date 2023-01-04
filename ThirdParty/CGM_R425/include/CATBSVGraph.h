// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBSVGraph.h
//
//===================================================================
//
// Complete Graph representing the Shape of a Body
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATBSVGraph_h
#define CATBSVGraph_h

#include "CATVGraph.h"
#include "CATMathematics.h"
#include "ListPOfCATBSVNode.h"
#include "ListPOfCATBSVLink.h"
#include "CATCGMNewArray.h"

class ExportedByCATMathematics CATBSVGraph : public CATVGraph
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  static CATBSVGraph* Create(const CATBSVGraph& iToCopy);
  CATCGMNewClassArrayDeclare;        // Pool allocation

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  static CATBSVGraph* Create(CATSoftwareConfiguration *iConfig, unsigned char* iStream, int& ioStreamPosition);
  HRESULT Stream(unsigned char*& oStream, int& oStreamLength) const; 
  
  //-----------------------------------------------------------------------------
  // Private. Do not use. Only public for test.
  //-----------------------------------------------------------------------------
  static CATBSVGraph* Create(CATSoftwareConfiguration *iConfig, ListPOfCATBSVNode& ioNodes, ListPOfCATBSVLink& ioLinks);

private:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATBSVGraph(CATSoftwareConfiguration *iConfig, ListPOfCATVNode& ioNodes, ListPOfCATVLink& ioLinks);
  CATBSVGraph(const CATBSVGraph& iToCopy); 
  CATBSVGraph& operator=(const CATBSVGraph&);  
};

#endif
