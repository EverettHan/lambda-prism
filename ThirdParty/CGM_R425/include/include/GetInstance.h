#ifndef GETINSTANCE_H
#define GETINSTANCE_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "YP00TMP.h"

class CATGeometry; 
class CATMathTransformation;

ExportedByYP00TMP CATGeometry * GetInstance(
					const CATGeometry *iRefGeom,
					const CATMathTransformation &iTransfo);

#endif

