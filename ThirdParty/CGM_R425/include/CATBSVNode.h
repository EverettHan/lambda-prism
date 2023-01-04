// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBSVNode.h
//
//===================================================================
//
// Graph Node in CATBodyToShape
//
//===================================================================
//
// October 2015 Creation: rr
//===================================================================
#ifndef CATBSVNode_h
#define CATBSVNode_h

#include "CATVNode.h" 
#include "CATMathematics.h"
#include "ListPOfCATBSVNode.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathDef.h"
#include "CATErrorDef.h" // build aix
#include "CATCGMNewArray.h"

class CATSoftwareConfiguration;
class CATBSVLink;

class ExportedByCATMathematics CATBSVNode : public CATVNode
{
public:
  //-----------------------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------------------
  CATBSVNode(CATSoftwareConfiguration *iConfig, const CATMathPoint& iOrigin, const CATMathVector& iNormal, const CATPositiveLength iThickness);
  CATCGMNewClassArrayDeclare;        // Pool allocation
  CATBSVNode(CATSoftwareConfiguration *iConfig);
  ~CATBSVNode();

  //-----------------------------------------------------------------------------
  // Services
  //-----------------------------------------------------------------------------
  static CATBSVLink* EvalLink(CATSoftwareConfiguration *iConfig, CATBSVNode* iNode1, CATBSVNode* iNode2, const CATPositiveLength iLengthTol, const CATAngle iAngleTol);
  static HRESULT Orient(ListPOfCATBSVNode& ioNodes);
  void GetGeometry(CATMathPoint oNodeGeometry[2]) const;

private:
  HRESULT OrientVsGraph();
  short ComputeSide(const CATMathPoint& iPoint, const CATPositiveLength iLengthTol);

  //-----------------------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------------------
  CATMathPoint      _Origin;
  CATMathVector     _Normal; // Normalized by constructor
  CATPositiveLength _Thickness;
  //-----------------------------------------------------------------------------
};

#endif
