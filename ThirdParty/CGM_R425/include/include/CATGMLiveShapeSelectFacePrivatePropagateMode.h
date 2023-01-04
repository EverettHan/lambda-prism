// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATGMLiveShapeSelectFacePrivatePropagateMode.h
// Private extension of definition of CATGMLiveShapeSelectFacePropagateMode
//
//===================================================================

//===================================================================
//
//  May 2011
//===================================================================
#ifndef CATGMLiveShapeSelectFacePrivatePropagateMode_H
#define CATGMLiveShapeSelectFacePrivatePropagateMode_H

//==============================================================================
// Define propagation mode
//==============================================================================
// Les modes complementaires sont-ils a faire ?
#include "CATGMLiveShapeSelectFacePropagateMode.h"
                                             
const CATGMLiveShapeSelectFacePropagateMode CLSSF_REMOVE_REDO_RIBBONS              = (CATGMLiveShapeSelectFacePropagateMode) 101;
const CATGMLiveShapeSelectFacePropagateMode CLSSF_REMOVE_REDO_RIBBONS_AUTOLIMITING = (CATGMLiveShapeSelectFacePropagateMode) 102;

const CATGMLiveShapeSelectFacePropagateMode CLSSF_DEPRESSION_WITHOUT_SMOOTH_CONTACT = (CATGMLiveShapeSelectFacePropagateMode) 110;
const CATGMLiveShapeSelectFacePropagateMode CLSSF_PROTRUSION_WITHOUT_SMOOTH_CONTACT = (CATGMLiveShapeSelectFacePropagateMode) 111;

const CATGMLiveShapeSelectFacePropagateMode CLSSF_NEUTRAL_DRAFT                     = (CATGMLiveShapeSelectFacePropagateMode) 120;
const CATGMLiveShapeSelectFacePropagateMode CLSSF_VISU_DRAFT_FACE                   = (CATGMLiveShapeSelectFacePropagateMode) 121;

#endif /* CATGMLiveShapeSelectFacePrivatePropagateMode_H */
