#ifndef CATCreateConcatenateEdgeCurves_H
#define CATCreateConcatenateEdgeCurves_H

#include "Y300IINT.h"

class CATConcatenateEdgeCurves;
class CATSoftwareConfiguration;
class CATGeoFactory;

ExportedByY300IINT
CATConcatenateEdgeCurves * CATCreateConcatenateEdgeCurves(CATGeoFactory * iFactory,
                                                          CATSoftwareConfiguration * iConfig=0);

#endif



