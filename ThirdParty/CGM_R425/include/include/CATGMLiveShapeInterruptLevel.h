/* -*-C++-*- */

#ifndef CATGMLiveShapeInterruptLevel_H
#define CATGMLiveShapeInterruptLevel_H

enum CATGMLiveShapeInterruptLevel {
                      CATGMLiveShapeInterruptLevel_UNKNOWN=-1,
                      CATGMLiveShapeInterruptLevel_NO_INTERRUPTION=0,          // All is rebuild. The result is right.
                      CATGMLiveShapeInterruptLevel_NO_REDO_RIBBONS,            // The fillets on boundary of selection are not rebuild.
                      CATGMLiveShapeInterruptLevel_NOT_CHECKED_RESULT,         // The result is not checked. It may have self intersection.
                      CATGMLiveShapeInterruptLevel_ONLY_ALL_MOVING_FACES,       // Selected faces + faces from variational system.
                      CATGMLiveShapeInterruptLevel_ONLY_SELECTED_MOVING_FACES,  // Only selected faces.
                      CATGMLiveShapeInterruptLevel_STANDARD_INTERRUPTION,       // Standard interruption without result.
                      //  /\
                      //  ||   Insert the new level here
                      //  ||         
                      CATGMLiveShapeInterruptLevel_NB_LEVELS};

#endif
