/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 02:01:11
 */

/* -*-C++-*- */

#ifndef __CATCreatePropagationEdge_H__ 
#define __CATCreatePropagationEdge_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Methode: CATCreatePropagationEdge
//
// Auteurs: HCN
//
// Description: 
//  Creation of an operator for edge tangency propagation on a body as a replacement for the
//  following CATBody method :
//
// virtual CATLISTP(CATCell) CATBody::CATEdgePropagate(CATLISTP(CATCell) * iInitialEdges,
//                              CATPropagationTypePr3 iPropagationType,
//	                            CATLISTP(CATEdge) * iRollingEdges = NULL) = 0;
//
// WARNING : This operator operates on volumic bodies only : it does not work on wires.
//           -> no longer true
//
//
//===========================================================================
// Jan. 02 Creation                                                     HCN
// Oct. 02 Propagation on wires                                         HCN
// Sept 03 Modif pour expo CAA compatible packaging                     CRE
//===========================================================================

#include "CATCreatePropagationEdgeOpe.h"
#endif






