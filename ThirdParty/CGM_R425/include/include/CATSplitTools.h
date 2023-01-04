#ifndef CATSplitTools_h
//=============================================================================
// 19/01/2017  G5S  Get rid of all code that would deal with a list of splitting faces, since we 
//                  think we will never use it.  We must always provide a splitting body.
// 30/01/2017  G5S  Make the extrapolation tool into a class like an operator and refactor
//                  to use this new class in split and DOCO. 
// 02/02/2017  G5S  Make CATExtrapolationToolsForSplit into an operator with an extensible, so the 
//                  typedef changes slightly.
// 07/02/2017  G5S  Use enums for extrapolation mode and limit.
//=============================================================================
#define CATSplitTools_h

#include "CATBoolean.h" //System
#include "CATTopDefine.h" //GMModelInterfaces
#include "ExportedByCATTopologicalObjects.h" //NewTopologicalObjects
#include "ListPOfCATFace.h"
#include "CATDynExtrapolationToolsDef.h"

class CATBody;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATTopData;
class CATSurface;
class CATListPtrCATCell;
class CATFace;
class CATICGMObject;
class CATVoBContactCheck;
class CATShell;
class CATExtrapolationToolsForSplit;

#ifndef NULL
#define NULL 0
#endif

typedef CATExtrapolationToolsForSplit * (*CATCreateExtrapolToolsFunction)(CATGeoFactory *, CATTopData *, CATBody *, CATBody *, 
  CATDynExtrapolationMode, CATDynExtrapolationLimit);

class ExportedByCATTopologicalObjects CATSplitTools
{
public:

  /**
  * @nodoc @nocgmitf
  *
  * METHOD INPUTS:
  *
  * iSelectionMode
  *    -1 (DOUBLE TRY)
  *        If the splitting body contains 1 single non-infinite face on a plane, try split with mode 0.
  *        If no volume can be split, or if the initial condition is false, do split with mode 2.
  *     0 (KEEP)
  *        Volumes that can't be split will remain in the result.
  *     1 (REMOVE)
  *        Volumes that can't be split will not remain in the result.
  *     2 (POSITION VS PLANE)
  *        If the splitting body contains 1 single face on a plane, then use the infinite plane instead of the body.
  *        Otherwise it is equivalent to mode 0.
  * iOperation
  *     1 (POSITIVE SIDE)
  *        Keep volumes on the positive side of the splitting element.
  *    -1 (NEGATIVE SIDE)
  *        Keep volumes on the negative side of the splitting element.
  *     2 (BOTH SIDES)
  *        Keep volumes on both sides of the splitting element.
  *        Result could be non-manifold (lumps with 2 or more volumes).
  * iFactory
  *     The geometrical factory. It can't be NULL.
  * iConfig
  *     The software configuration. It can't be NULL.
  * iBodyToSplit
  *     The body to split. It can't be NULL.
  * iSplittingBody
  *     The splitting body.
  *     If NULL, then iSplittingSurface can't be NULL.
  *     If not NULL, then iSplittingSurface must be NULL.
  * iSplittingSurface
  *     The splitting surface.
  *     If NULL, then iSplittingBody can't be NULL.
  *     If not NULL, then iSplittingBody must be NULL.
  * iJournal
  *     The operation journal.
  *     If not NULL, items describing the split operation are inserted inside it.
  *     Can be NULL.
  * iVoBContactCheck
  *     The VoB tool. Can be NULL.
  * iExtrapolFunction
  *     Function to extrapolate the splitting element.
  *     Must adhere to prototype CATBody *(CATGeoFactory *, CATSoftwareConfiguration *, CATBody *, CATBody *, CATCGMJournalList *),
  *     where first CATBody is the splitting body, and second CATBody is the body to split.
  *     Can be NULL.
  *
  * METHOD OUTPUTS:
  * 
  * @return
  *     The body result of the operation.
  * oRelimitation
  *     TRUE if a part of input matter is removed.
  *     Can be leaved to NULL if you don't need this information.
  * oUnknownPositionVolumes
  *     List of CATVolumes that can't be positioned towards the splitting element.
  *     Can be leaved to NULL if you don't need this information.
  * oComplementaryBody
  *     If not NULL, a new body will be created, and it will contain the complementary parts
  *     of the input volume.
  *     WARNING: Not available with (iOperation == 2).
  */
  static CATBody * SplitEngine(short iSelectionMode,
                               short iOperation,
                               CATBoolean iNoVolumicSimplif,
                               CATBoolean iLumpPropagation,
                               CATGeoFactory * iFactory,
                               CATSoftwareConfiguration * iConfig,
                               CATBody * iBodyToSplit,
                               CATBody * iSplittingBody,
                               CATSurface * iSplittingSurface,
                               CATCGMJournalList * iJournal = NULL,
                               CATVoBContactCheck * iVoBContactCheck = NULL,
                               CATDynExtrapolationMode iExtrapolMode = DYN_NO_EXTRAPOLATION,
                               CATDynExtrapolationLimit iExtrapolLimit = DYN_THRUNEXTCONNECTED,
                               CATCreateExtrapolToolsFunction iCreateExtrapolToolsFunction = NULL,
                               CATBoolean * oRelimitation = NULL,
                               CATListPtrCATCell * oUnknownPositionVolumes = NULL,
                               CATBody ** oComplementaryBody = NULL);
};

#endif
