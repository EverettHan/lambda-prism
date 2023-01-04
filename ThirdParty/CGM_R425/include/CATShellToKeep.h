#ifndef CATShellToKeep_H
#define CATShellToKeep_H
#define CATShellToKeep CATPieceToKeep
#define CATListPtrCATShellToKeep CATListPtrCATPieceToKeep
// COPYRIGHT DASSAULT SYSTEMES 2011

//===================================================================
//signature des elements des mosaiques resultantes apres le multi trim Shell by wires
//
//
//
////===================================================================
//#include "CATGMOperatorsInterfaces.h"
//#include "CATListOfInt.h"
#include "CATPieceToKeep.h"





////struct ExportedByCATGMOperatorsInterfaces CATShellToKeep
//{
//  CATShellToKeep();
//  CATShellToKeep(const CATShellToKeep &ST);
//
//  int _JShellBodyInitial;// ShellBodyInitial is a support of iShellbody
//  CATListOfInt  _WireIndexIntial; // InitialWiresIndex bounded iShellbody in JShellBodyInitial 
//                                                    // if the border of ShellBodyInitial bounds the mosaic piece then: the last element in the stack is equal -1
//  CATListOfInt  _SideToKeep; //side to keep corresponding to  InitialWires in JShellBodyInitial (same index like ShellIndexIntersection)
//                                                 // if the border of ShellBodyInitial bounds the mosaic piece its orientation  is equal 1
//  CATListOfInt  _ShellIndexIntersection;// beetwenJShellBodyInitial (_JShellBodyInitial if the wire is in the boundary of InitalShell)
//  //=================================
//  //if they are NIW intersection wires beetwen iShell and jShell  
//  // Let NS = number of InitialShellBodies and  iw index of intersection wires, with iw =1,...NIW
//  //  _ShellIndexIntersection = NS(iw -1) + jShell 
//  CATListOfInt  _SideToKeepIntersection ;//side to keep corresponding to   IntersectionWires  JShellBodyInitial (same index like ShellIndexIntersection)
//  //(synchronise with ShellIndexIntersection)
//  //==================================
//  int _indexMultipleSolution;// -1 pas d'indexation necessaire sinon de 0 a .. n-1
//};
//
//#include "CATCGMLISTP_Declare.h"
//CATCGMLISTP_DECLARE(CATShellToKeep);
//
////-----------------------------------------------------------
//// Copy constructeur
////------------------------------------------------------------
////ExportedByCATGMOperatorsInterfaces CATShellToKeep(const CATShellToKeep &ST);
//
//ExportedByCATGMOperatorsInterfaces int EsIgual(CATShellToKeep * first, CATShellToKeep * second);

#endif
