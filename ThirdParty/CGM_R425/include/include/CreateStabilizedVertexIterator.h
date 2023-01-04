#ifndef CreateStabilizedVertexIterator_h
#define CreateStabilizedVertexIterator_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"

class CATVertexIterator;
class CATBody;
class CATVertex;
class CATSoftwareConfiguration;

/**
* Creates a stabilized CATVertexIterator:
* the order of bounded cells is stable towards translations, scalings, and disconnection of edges/faces.
* In cases where no ambiguity exists, it is also stable towards rotations.
* An ambiguity exists when there are symmetries on 1st and 2nd derivative vectors of edges bounding the vertex.
*/

ExportedByCATTopologicalObjects CATVertexIterator * CreateStabilizedVertexIterator(
  CATBody * iBody,
  CATVertex * iVertex,
  CATSoftwareConfiguration * iConfig,
  CATBoolean iUseDomainOrientationForStabilization = TRUE);

#endif
