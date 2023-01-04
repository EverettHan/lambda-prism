// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// Header definition of CATGMLiveShapeRevolPrismMode
// Oct 2012
//
//===================================================================

#ifndef CATGMLiveShapeRevolPrismMode_H
#define CATGMLiveShapeRevolPrismMode_H

// NEVER CHANGE THE ORDER OF THE ENUM: IT WILL BREAK ODT
enum CATGMLiveShapeRevolPrismMode { CATGMLiveShapeRevolPrism_OFF=0,
                                    CATGMLiveShapeRevolPrism_ON,
                                    CATGMLiveShapeRevolPrism_ON_WITHOUT_BOOLEAN,  // For SheetMetal Operator
                                    CATGMLiveShapeRevolPrism_ON_EXTRUDE_DRAFT,
                                    CATGMLiveShapeRevolPrism_ON_BOTH_SIDES
                                    // CATGMLiveShapeRevolPrism_ON_ONLY_SMOOTH_CONTACT // idea for futur
                                  };

#endif

