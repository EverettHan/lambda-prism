#ifndef CATPieceToKeep_H
#define CATPieceToKeep_H

// COPYRIGHT DASSAULT SYSTEMES 2011

//===================================================================
//signature des elements des mosaiques resultantes apres le multi trim Shell by wires
//
//
//
////===================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATListOfInt.h"
#include "CATListPtrCATPieceToKeep.h"
#include "CATLISTP_Declare.h"

struct ExportedByCATGMOperatorsInterfaces CATPieceToKeep
{
  CATPieceToKeep();
  CATPieceToKeep(const CATPieceToKeep &ST);

  int _JShellBodyInitial;// PieceBodyInitial is a support of iPieceMosaicBody
  CATListOfInt  _WireIndexIntial; // InitialBodiesIndex bounded iPieceMosaicBody in _JShellBodyInitial 
                                                    // if the border of ShellBodyInitial bounds the mosaic piece then: the last element in the stack is equal -1
  CATListOfInt  _SideToKeep; //side to keep corresponding to  InitialBodies in _JShellBodyInitial (same index like ShellIndexIntersection)
                                                 // if the border of PieceBodyInitial bounds the mosaic piece its orientation  is equal 1
  CATListOfInt  _ShellIndexIntersection;// between JShellBodyInitial (_JShellBodyInitial if the bodyIntersection is in the boundary of InitalPiece)
  //=================================
  //if they are NIW intersection bodies between iPiece and jPiece  
  // Let NS = number of InitialPieces and  iw index of intersection bodis, with iw =1,...NIW
  //  _ShellIndexIntersection = NS(iw -1) + jPiece 
  CATListOfInt  _SideToKeepIntersection ;//side to keep corresponding to   IntersectionBodies  JShellBodyInitial (same index like ShellIndexIntersection)
  //(synchronise with ShellIndexIntersection)
  //==================================
  int _indexMultipleSolution;// -1 pas d'indexation necessaire sinon de 0 a .. n-1
};

//-----------------------------------------------------------
// Copy constructeur
//------------------------------------------------------------
//ExportedByCATGMOperatorsInterfaces CATPieceToKeep(const CATPieceToKeep &ST);

ExportedByCATGMOperatorsInterfaces int EsIgual(CATPieceToKeep * first, CATPieceToKeep * second);

#endif
