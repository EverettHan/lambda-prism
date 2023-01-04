// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// Macro pour les evaluateurs des objets CGM
//
//=============================================================================
// Usage notes:
//
// strictement reserve a GeometricObjectsCGM
//
//=============================================================================
// May 97   Creation                                     R. Rorato
//=============================================================================
#ifndef CATMacEvalCommand_H
#define CATMacEvalCommand_H


#define CATMacEvalCommand( iCmd, oEval0, oEval1, oEval2, oEval3 )       \
{        				                                \
  oEval0 = iCmd & CATDeriv0 ;                                           \
  oEval1 = (iCmd & CATDeriv1) >> 1 ;                                    \
  oEval2 = (iCmd & CATDeriv2) >> 2 ;                                    \
  oEval3 = (iCmd & CATDeriv3) >> 3 ;                                    \
}    
#endif
//automate:07/09/99:suppression include de CATCrvEvalCommand.h
