/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 02:01:11
 */

/* -*-C++-*- */

#ifndef __CATTopPropagationEdge_H__
#define __CATTopPropagationEdge_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Operator for edge tangency propagation on a body as a replacement for the
// following CATBody method :
//
// virtual CATLISTP(CATCell) CATBody::CATEdgePropagate(CATLISTP(CATCell) * iInitialEdges,
//                              CATPropagationTypePr3 iPropagationType,
//	                            CATLISTP(CATEdge) * iRollingEdges = NULL) = 0;
// Cf. CATCreatePropagationEdge.h
//
// Jan. 02      Creation                                HCN
// Aout 2003    Ajout methode DumpInterne               CBK
// Sept 2003    Modif pour expo CAA compatible avec packaging  CRE
//              Remplacement par include - expo ds CATTopPropagationEdgeOpe
//===========================================================================
#include "CATTopPropagationEdgeOpe.h"

#endif
