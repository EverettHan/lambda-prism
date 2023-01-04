//======================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//======================================================================
//
// CATStoFadingEdgeState.h
//
//======================================================================
//
// Usage notes: Diags pour les fading edges.
//
//======================================================================
// March,    2010 : RAQ : Création
//======================================================================
#ifndef CATStoFadingEdgeState_H
#define CATStoFadingEdgeState_H

//Pour l'export
#include "YP0LOGRP.h"

//Divers
#include "CATBoolean.h"

/**
 * Structure of CATStoFadingEdgeState :
 * The states are coded on 32 bits which are organized as follows :
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *  +---+-+-------------------------+-------------------------------+
 *  |Val|T|   Not actually  used    |         State (2 bytes)       |
 *  +---+-+-------------------------+-------------------------------+
 *
 *  Val : quick validity 00 : OK
 *                       01 : Warning (not actually used)
 *                       10 : Error
 *                       11 : Error (not actually used)
 *
 *  T : Topological validity 0 : OK, the fading edge is topologically valid, ie. vertices and edges exist and are chained.
 *                               The fading edge can have a 3D visualization.
 *                           1 : KO, at least one vertex doesn't exist or there is no edge linking two consecutive vertices.
 *
 *  States : They describe the current fading edge state.
 *           See "CATSubdivisionTopOperators\Data.d\States_Character_Lines_and_Fading_Edges.xls"
 *
 **/


enum CATStoFadingEdgeState
{
  //--------------------FOR COMPATIBILITY ONLY, DON'T USE ANYMORE, SEE ABOVE INSTEAD ---------//
  //Valid = 0,                          //Seul diag de validité

  //Invalid,                            //Invalidité, générique
  //Invalid_BadParameters,
  //Invalid_ParametersOutOfRange,
  //Invalid_NotAllSharpEdges,
  //Invalid_NotExistingEdge,
  //Invalid_TooManyFadingEdgesOnEdge,   //Une CATSobEdge sert de support à plusieurs fading edges.
  //Invalid_FreeEdge,
  //Invalid_FreeVertex,
  //Invalid_NotRegularZone,
  //Invalid_BadTransitionZone,
  //Invalid_NeighbourIncompatibility,
  //Invalid_InternalNullPointer,
  //Invalid_InternalError,
  //------------------------------------------------------ END FOR COMPATIBILITY -------------//



  CATStoFE_Valid                                          = 0x00000000,                //Seul diag de validité

  CATStoFE_Invalid                                        = 0xA0000001,                //Invalidité, générique

  //------------- Fading edge errors : bits 0 --> 7 included (1st byte)
  //Invalidités topologiques
  CATStoFE_Invalid_NotExistingVertex                      = 0xA0000002,
  CATStoFE_Invalid_NotExistingEdge                        = 0xA0000003,
  CATStoFE_Invalid_BadVertexPath                          = 0xA0000004,

  //Invalidités autres
  CATStoFE_Invalid_SharpnessOnIncidentEdge                = 0x80000005,
  CATStoFE_Invalid_TooManyFadingEdgesOnEdge               = 0x80000006,                //Une CATSobEdge sert de support à plusieurs fading edges.
  CATStoFE_Invalid_TwoEdgesBelongToTheSameFace            = 0x80000007, 
  CATStoFE_Invalid_FreeVertex                             = 0x80000008,
  CATStoFE_Invalid_FreeEdge                               = 0x80000009,
  CATStoFE_Invalid_NotRegularZone                         = 0x8000000A,
  CATStoFE_Invalid_NoDisconnectedSupports                 = 0x8000000B,
  CATStoFE_Invalid_NotAllSharpEdges                       = 0x8000000C,

  CATStoFE_Invalid_BadParameters                          = 0x8000000D,
  CATStoFE_Invalid_ParametersOutOfRange                   = 0x8000000E,

  CATStoFE_Invalid_Unprocessed                            = 0x8000000F,


  //------------------ Diags à supprimer....
  Valid                               = 0x00000000,
  Invalid                             = 0xA0010001,
  Invalid_BadParameters               = 0xA0010002,
  Invalid_ParametersOutOfRange        = 0x8000000E,
  Invalid_NotAllSharpEdges            = 0x8000000C,
  Invalid_NotExistingEdge             = 0xA0000003,
  Invalid_TooManyFadingEdgesOnEdge    = 0x80000006,
  Invalid_FreeEdge                    = 0x80000009,
  Invalid_FreeVertex                  = 0x80000008,
  Invalid_NotRegularZone              = 0x8000000A,
  Invalid_BadTransitionZone           = 0xA001000A,
  Invalid_NeighbourIncompatibility    = 0xA001000B,
  Invalid_InternalNullPointer         = 0xA0010003,
  Invalid_InternalError               = 0xA0000001

};


/**
 * Checks a state.
 *
 * @param iState
 *
 * @return
 * TRUE if iState is Valid, FALSE otherwise.
 **/
ExportedByYP0LOGRP
inline CATBoolean IsValid(const CATStoFadingEdgeState iState) { return (iState & 0x80000000) ? FALSE : TRUE; }

/**
 * Checks if the fading edge is topologically valid.
 *
 * @param iState
 *
 * @return
 * TRUE if iState refers to a valid topology, FALSE otherwise.
 **/
ExportedByYP0LOGRP
inline CATBoolean IsTopologicallyValid(const CATStoFadingEdgeState iState) { return (iState & 0x20000000) ? FALSE : TRUE; }

/**
 * Gets the string corresponding to a state.
 *
 * @param iState
 * The state.
 *
 * @return
 * The string corresponding to the given state.
 **/
ExportedByYP0LOGRP
const char* ToString(const CATStoFadingEdgeState iState);

#endif

