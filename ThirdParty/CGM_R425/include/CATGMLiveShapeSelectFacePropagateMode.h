// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATGMLiveShapeSelectFacePropagateMode.cpp
// Header definition of CATGMLiveShapeSelectFacePropagateMode
//
//===================================================================

//===================================================================
//
//  July 2007
//===================================================================
#ifndef CATGMLiveShapeSelectFacePropagateMode_H
#define CATGMLiveShapeSelectFacePropagateMode_H

#include <functional>
#include "CATSysBoolean.h"

class CATBody;
class CATEdge;
class CATFace;
class CATShell;

// Type def 
// ------------------------------------------------------------------
#ifndef _AIX_SOURCE

// Ne compile pas sous AIX..., va savoir pourquoi.
typedef std::function<CATBoolean(CATBody *ipBody, CATEdge *iCurrEdge, CATFace * iCurrFace, CATFace *iNextFace, CATShell * iCurrShell)>  CLSSFPropagationFunction;

#else

typedef CATBoolean (*CLSSFPropagationFunction) (CATBody *ipBody, CATEdge *iCurrEdge, CATFace * iCurrFace, CATFace *iNextFace, CATShell * iCurrShell);

#endif

//==============================================================================
// Define propagation mode
//==============================================================================
// Les modes complementaire sont-ils a faire ?

// NEVER CHANGE THE ORDER OF THE ENUM: IT WILL BREAK ODT "*LiveSelect*"
enum CATGMLiveShapeSelectFacePropagateMode { CLSSF_POINT_CONTINUITY    = 0,
                                             CLSSF_TANGENCY_CONTINUITY = 1,
                                             CLSSF_DEPRESSION          = 2,
                                             CLSSF_PROTRUSION          = 3, 
                                             CLSSF_CELLMANIFOLD        = 4,
                                             // ----------------------------------------------------------------------------------------------
                                             CLSSF_NATURAL_LOCAL       = 5,    // ! Do not use. It's a prototype.
                                             CLSSF_NATURAL_EXTENDED    = 6,    // ! Do not use. It's a prototype.
                                             CLSSF_NATURAL_DEPRESSION  = 7,    // ! Do not use. It's a prototype.
                                             CLSSF_NATURAL_PROTRUSION  = 8,    // ! Do not use. It's a prototype.
                                             // ----------------------------------------------------------------------------------------------
                                             CLSSF_DECLARATIVE         =  9,   // To get all the ribbon fillets in the same DelcarativeManifold.
                                             CLSSF_NEIGHBORHOOD        = 10,   // Neighbor faces connected by edges and by vertices.
                                             CLSSF_WALL                = 11,   // The face on the other side of the wall.
                                             CLSSF_REMOVE_RIBBONS      = 12,   // The faces to be removed with the fillet selection.
                                             CLSSF_SYMMETRY            = 13,   // The closest mirrored face 
                                             CLSSF_LOCALSYMMETRY       = 14,   // The closest locally mirrored face 
                                             // ----------------------------------------------------------------------------------------------
                                             CLSSF_DEPRESSION_DETECTION     = 15,  // Prototype : Return a list of faces included in a depression among the input list.
                                             CLSSF_PROTRUSION_DETECTION     = 16,  // Prototype : Return a list of faces included in a protrusion among the input list.
                                             CLSSF_REPLICA                  = 17,  // Prototype : Return a list of faces equal to input faces through a positive isometry.
                                             CLSSF_RIBBON_IMPACT            = 18,  // Impact of modified faces after a ribbon selection. Propag to DelcarativeManifold + neighbor Joint
                                             CLSSF_RIBBON_SAME_SPEC         = 19,  // Propagate to connexe neighbor BoneManifold with Same specification. Propag through joint when Bonefillet.
                                             CLSSF_RIBBON_SAME_SPEC_NO_FORK = 20,  // Same as "CLSSF_RIBBON_SAME_SPEC", but if a bone as more than one same spec neighbor, Propagation stops.
                                             CLSSF_GLOBAL_RANGE_SPEC        = 21,  // (Prototype) example : between 2.5mm and 3.0mm.
                                             CLSSF_MULTI_WALL               = 22,  // 3D-XPhoto request : Multi-Wall propagation.                                             
                                             // Y2018 ----------------------------------------------------------------------------------------------
                                             CLSSF_DRAFT_SAME_SPEC          = 23, // Propagate to connexe neighbor DraftManifold with same specification. Propag through joint and Bone Manifold.
                                             CLSSF_DRAFT_GLOBAL_SAME_ANGLE  = 24, // Select all draft on the body that have the same angle as the given input.
                                             CLSSF_DRAFT_GLOBAL_SAME_PULDIR = 25, // Select all draft on the body that have the same puldir as the given input.
                                             CLSSF_DRAFT_GLOBAL_SAME_NEUTRAL= 26, // Select all draft on the body that have the same neutral(s) as the given input.
                                             // Y2018 ----------------------------------------------------------------------------------------------
                                             CLSSF_MINIMAL_BUMP             = 27, // Extend the selection to the minimal depression or protrusion.
                                             CLSSF_TANGENCY_NOSHARPEDGE     = 28, // DO NOT USE PROTOTYPE 2018
                                             // Y2019 ----------------------------------------------------------------------------------------------
                                             CLSSF_REMOVE_RIBBONS_DEFEATURE = 29, // The faces to be removed with the fillet selection for defeature.
                                             CLSSF_DFT_LIMITING_DETECTION   = 30, // The faces entirely "cut" by the given limiting body.
																						 // Y2020 ---------------------------------------------------------------------------------------------
																						 CLSSF_MOVE_EXTENDED_SELECTION  = 31,	// Extends the selection to prevent the move of selection from topological due to missing faces (e.g. moving a hole). 
                                             // Y2021 ---------------------------------------------------------------------------------------------
                                             CLSSF_CUSTOM_PROPAG_FUNCTION   = 32,  // Authorize external custom function of propagation via HRESULT SetCustomPropagationFunction(...) member methods. 
                                             // Y2022 ---------------------------------------------------------------------------------------------
                                             CLSSF_DETAIL1_THINPART_OR_BUMP = 33,  // DO NOT USE PROTOTYPE 2022 for fast selection in xDD
                                             CLSSF_DETAIL2_ADJACENT_DETAIL  = 34   // DO NOT USE PROTOTYPE 2022 for fast selection in xDD
                                           };

#endif

