#ifndef CATPGMLocalOrientationInvert_h_
#define CATPGMLocalOrientationInvert_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATGeometry;
class CATLoop;
class CATPCurve;
class CATICGMSmartBodyDuplicator;
class CATTopData;

class ExportedByCATGMOperatorsInterfaces CATPGMLocalOrientationInvert
{
public:
  /**
   * Constructor
   */
  CATPGMLocalOrientationInvert();

  /**
   * Destructor
   */
  virtual ~CATPGMLocalOrientationInvert();

  // Specifying cells to invert
  // short value returned by AppendCellToInvert = 0 if cell was already in the list, otherwise 1
  // short value returned by RemoveCellToInvert = 1 if cell was already in the list, otherwise 0
  virtual short AppendCellToInvert(CATCell *iCell) = 0;

  virtual void AppendListOfCellsToInvert(CATCell **iCells, CATLONG32 iNumberOfCells) = 0;

  virtual short RemoveCellToInvert(CATCell *iCell) = 0;

  virtual void RemoveListOfCellsToInvert(CATCell **iCells, CATLONG32 iNumberOfCells) = 0;

  virtual void InvertAllFaces() = 0;

  virtual void InvertAllEdges() = 0;

  virtual void InvertAllCells() = 0;

  // Make local orientations positive or negative (input +1 or -1)
  virtual void SetAllFacesTo(short iOrientation) = 0;

  virtual void SetAllEdgesTo(short iOrientation) = 0;

  // Set one cell 's orientation, or all cells if cell is ommitted
  virtual void SetOrientation(short iOrientation, CATCell *iCell = 0) = 0;

  // Execution 
  virtual void Run() = 0;

  // Getting initial and final bodies (final body = null if the operation failed)
  // and get the journal, if it had been giben as input to the constructor
  virtual CATBody *GetInitialBody() const = 0;

  virtual CATBody *GetResult() = 0;

  virtual CATCGMJournalList *GetJournal() = 0;

  // Getting internal duplicator
  /**
   * @return [out, IUnknown#Release]
   */
  virtual CATICGMSmartBodyDuplicator *GetIDuplicator() const = 0;

  // internal utility
  virtual void UpdateList(short iDim, CATCell *iBefore, CATCell *iAfter) = 0;
};

// old constructor without CATTopData
ExportedByCATGMOperatorsInterfaces CATPGMLocalOrientationInvert *CATPGMCreateLocalOrientationInvert(
  CATBody *iBody,
  CATCGMJournalList *iJournal = 0);

// constructor (does nothing but setting the initial body)
ExportedByCATGMOperatorsInterfaces CATPGMLocalOrientationInvert *CATPGMCreateLocalOrientationInvert(
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATPGMLocalOrientationInvert_h_ */
