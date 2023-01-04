/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

/* -*-C++-*- */

#ifndef __CATTopEdgeSharpnessMarker_H__
#define __CATTopEdgeSharpnessMarker_H__

//===========================================================================
// Operator for setting sharpnesses of edges in a body.
//
// Use CATCreateEdgeSharpnessMarker(...) to create such an operator.
//
// The edges from the input body to be marked can be specified with
// SetSmoothEdgesToMark(...) and SetSharpEdgesToMark(...)
//
// After the run, original marked edges can be retrieved with GetModifiedOriginalEdges(...).
// For each original marked edge, the resulting edge can be retrieved with GetMarkedEdgeFromOriginalEdge(...).
//
// Juin 02      Creation                                HCN
//===========================================================================


#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATEdge.h"
#include "CATTopDefine.h"
#include "CATListOfCATTopSharpnesses.h"

class CATBody;
class CATEdge;


class ExportedByCATTopologicalObjects CATTopEdgeSharpnessMarker : public CATTopOperator
{
protected:
  
  //============================
  // Constucteur et destructeurs
  //============================
  
  CATTopEdgeSharpnessMarker(CATGeoFactory*  ipFactory,
                            CATTopData*     ipTopData,
                            CATBody*        ipBody,
                            CATAngle        iMinSharpAngle = CATTopSharpAngle);
  
public:
  
  virtual ~CATTopEdgeSharpnessMarker();

  CATCGMNewClassArrayDeclare;
  
  //======================================
  // Methodes specifiques a CATTopOperator
  //======================================
  
  virtual int Run() = 0;
  
  //=====================================================
  // Methodes specifiques a CATTopEdgeSharpnessMarker
  //=====================================================

  virtual void SetSmoothEdgesToMark(CATLISTP(CATEdge) &iListOfSmoothEdgesToMark) = 0;
  virtual void SetSharpEdgesToMark(CATLISTP(CATEdge) &iListOfSharpEdgesToMark, CATLISTP(CATTopSharpness) &iListOfSharpnesses) = 0;

  virtual void GetModifiedOriginalEdges(CATLISTP(CATEdge) &ioListOfModifiedOriginalEdges) = 0;
  virtual void GetMarkedEdgeFromOriginalEdge(CATEdge* ipOriginalEdge, CATEdge* &iopMarkedEdge) = 0;

  //====================================================================
  // Methodes specifiques a CATTopEdgeSharpnessMarker : pour debug CGM
  //====================================================================
  virtual void SetCheckWithEvalGlobalSharpness(CATBoolean iCheckModeActive = TRUE) = 0;
};

#endif
