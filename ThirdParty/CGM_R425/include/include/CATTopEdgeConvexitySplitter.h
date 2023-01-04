/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

/* -*-C++-*- */

#ifndef __CATTopEdgeConvexitySplitter_H__
#define __CATTopEdgeConvexitySplitter_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Operator for splitting multi-convexity edges in bodies.
//
// Use CATCreateEdgeConvexitySplitter(...) to create such an operator.
//
// The edges from the input body to be split can be specified with SetEdgesToCheck(...).
// Otherwise, the operator checks all the edges of the input body.
//
// After the run, split edges can be retrieved with GetModifiedOriginalEdges(...).
// For each split edge, the resulting edges can be retrieved with GetSplitEdgesFromOriginalEdges(...).
//
// Mai. 02      Creation                                                  HCN
// Oct. 05      Ajout de la methode SetDuplicateOnlyIfSplit               FDN
//===========================================================================


#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATEdge.h"
#include "CATTopDefine.h"

class CATBody;
class CATEdge;
class CATListValCATCrvParam;

class ExportedByCATTopologicalObjects CATTopEdgeConvexitySplitter : public CATTopOperator
{
protected:
  
  //============================
  // Constucteur et destructeurs
  //============================
  
  CATTopEdgeConvexitySplitter(CATGeoFactory*  ipFactory,
                              CATTopData*     ipTopData,
                              CATBody*        ipBody,
                              CATAngle        iMinSharpAngle = CATTopSharpAngle);
  
public:
  
  virtual ~CATTopEdgeConvexitySplitter();

  CATCGMNewClassArrayDeclare;
  
  //======================================
  // Methodes specifiques a CATTopOperator
  //======================================
  
  virtual int Run() = 0;

  //=====================================================
  // Methodes specifiques a CATTopEdgeConvexitySplitter
  //=====================================================

  virtual void SetEdgesToCheck(CATLISTP(CATEdge) &iListOfEdgesToCheck) = 0;

  virtual void GetModifiedOriginalEdges(CATLISTP(CATEdge) &ioListOfModifiedOriginalEdges) = 0;
  virtual void GetSplitEdgesFromOriginalEdges(CATEdge* ipOriginalEdge, CATLISTP(CATEdge) &ioListOfSplitEdges) = 0;
  virtual void SetNoComplete() = 0;

  //-----------------------------------------------------------------------------
  // SetDuplicateOnlyIfSplit : Duplication is done only if some edges are splitted
  // Warning : If this set is done, result body can be NULL (it means that no split has been done)
  //-----------------------------------------------------------------------------
  virtual void SetDuplicateOnlyIfSplit() = 0;

  //====================================================================
  // Methodes specifiques a CATTopEdgeConvexitySplitter : pour debug CGM
  //====================================================================
  virtual void SetCheckWithEvalGlobalSharpness(CATBoolean iCheckModeActive = TRUE) = 0;

  //-----------------------------------------------------------------------------
  // Set the operator to only analyze for presence of mixed convexity edges.
  // Do not split the edges.
  //-----------------------------------------------------------------------------
  virtual void SetCheckOnly(CATBoolean iCheckModeActive = TRUE) = 0;
  virtual void GetMixedConvexityEdges(CATLISTP(CATEdge) & oListEdge) = 0;
  virtual void GetParam(CATEdge* iEdge, CATLISTV(CATCrvParam) & oParam) = 0;

  //-----------------------------------------------------------------------------
  // Returns the resulting body. Call this method
  // after the <tt>Run</tt> method has been called.
  // Returns NULL if SetCheckOnly property has been set.
  //-----------------------------------------------------------------------------
  virtual CATBody * GetResult() = 0;
};

#endif
