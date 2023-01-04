/* -*-c++-*- */
#ifndef CATCGMCheck_H_
#define CATCGMCheck_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//============================================================================
//   Classification of errors
//============================================================================
#include "ExportedByGeometricObjects.h"

class ExportedByGeometricObjects CATCGMCheck
{
public:
  enum Category 
  { 
    IncompleteDefinition = +10,          // Topology without Geometry support 
                                   // Macro Point without POEC component
                                   // Edge without Vertices and POEC
                                   // Domain withur Cell

    SevereInternalInconsistency = +20,   // Unexepected exception thrown
                                   // GeoFactory, Tag des elements
                                   // Surface, comparaison EvalNormal et dU ^ DV
                                   // POEC with CrvParam outside MaxLimits
                                   // Connexity of Edges in Loop

    InconsistentDomains = +30,     // At least two owners of a Domain in the same Body
                                   // From Body or Cell to immediate bounding Cell, more than one Domain path.

    DegeneratedGeometry = +40,     // Edge with a too small edgecurve length

    IntermediateModelisation = +50,   // Object in intermediate state
                                      //  Touched Topology

    IntermediateTouchedModelisation = +60,   //  Touched Topology and SmartDuplication

    FuzzyTopology = +70,           // many Topology for same geometry in the same Body 
                                   // Distinct Vertices at same Location inside same Body

    FuzzyGeometry = +80,           // EdgeCurve with big Gap on mapping

    TooSmallBoundingBox = +90,     // Body contains vertices outside its persistent bounding Box

    InconsistentBackwardLinks = +100, // Internal management of topological backward links

    NotClassified = +110,              // Temporary not classified in previous categories

    NotAnError = +120,                 // All information are not so bad..

    FatGeometry = +130             // Fat geometry
  };
};


#endif
