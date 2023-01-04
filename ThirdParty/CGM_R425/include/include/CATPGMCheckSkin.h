#ifndef CATPGMCheckSkin_h_
#define CATPGMCheckSkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATTopToolsGapCheckMode.h"
#include "CATDynValidShell.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMDiagnosis;
class CATCGMJournalList;
class CATFace;
class CATGeoFactory;
class CATShell;
class CATSoftwareConfiguration;
class CATTopData;
class CATTopOpInError;
class CATCellHashTable;
class CATLISTP(CATBody);
class CATLISTP(CATCell);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

//------------------------------------------------------------------------------
// Check if a skin or a hash table of faces is twisted and return the first
// twisted face
//
// Please note:
// If a pointer on the optional output list of twisted faces is provided, the
// method will first search all faces of the shell or hash table, and not stop
// on the first detected twist. All twisted faces are then contained in the
// list and first face is returned by the method directly
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATFace *CATPGMCheckTwistedSkin(
  CATShell *iShellToCheck,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATFace) *oTwistedFaces = NULL,
  CATBoolean iCheckInsideFace = FALSE);

ExportedByCATGMOperatorsInterfaces CATFace *CATPGMCheckTwistedSkin(
  CATCellHashTable *ihtShellToCheck,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATFace) *oTwistedFaces = NULL,
  CATBoolean iCheckInsideFace = FALSE);

//------------------------------------------------------------------------------
// Generate a twist error with corresponding data
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATTopOpInError *CATPGMMakeTwistError(
  CATShell *iSkin,
  CATLISTP(CATFace) &iTwistedFaces,
  CATGeoFactory *iFactory);

//------------------------------------------------------------------------------
// Generate a collision error with corresponding data
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATTopOpInError *CATPGMMakeCollisionError(
  CATShell *iSkin,
  CATLISTP(CATBody) &iCollisionBodies,
  CATGeoFactory *iFactory,
  CATBoolean iForceBlendVertexError = FALSE);

//------------------------------------------------------------------------------
// The methode checks whether iFace is twisted (and returns TRUE if it is)
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMIsTwistedFace(
  CATFace *iFace,
  CATBoolean iDoNewTest = FALSE,
  CATSoftwareConfiguration *iConfig = NULL,
  CATBoolean iCheckInsideFace = FALSE);

//------------------------------------------------------------------------------
// The methode checks face is offsetable
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMIsFaceOffsetable(
  CATFace *iFace,
  CATSoftwareConfiguration *iConfig,
  double iOffsetValue);

//------------------------------------------------------------------------------
// Check if a skin is hermetic and return true if it is not
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMCheckUnhermeticSkin(
  CATSoftwareConfiguration *iConfig,
  CATBody *iBodyToCheck,
  CATShell *iShellToCheck,
  CATBody **oResultBody = NULL);

//------------------------------------------------------------------------------
// donne le nombre de domaine par dimension
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void CATPGMGetNbDomainsPerDimension(
  CATBody *iBody,
  int &oNbLumps,
  int &oNbShells,
  int &oNbWires,
  int &oNbVertex);

//------------------------------------------------------------------------------
// Check if a skin is topologically valid
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATDynValidShellType CATPGMCheckValidSkin(
  CATSoftwareConfiguration *iConfig,
  CATGeoFactory *iFactory,
  CATBody *iBodyToCheck,
  CATLISTP(CATBody) &oListBody);

// Added By : SUH : 2003:6:3
//--------------------------------------------------------------------------------------
// Prefer using the other overload, CATPGMMakeDiagError(const char        *iMsgId, ....
//
// Generate - if possible - a CATTopOpInError of type iNumberError with diagnosis (error
// bodies). One should make an entry for string identifier associated with iNumberError, 
// if not already there. This string identifier is the same which appears in NLS file.
//
// iListOfCellToShow : The list of cells to be sent with error as the location of error
//--------------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATTopOpInError *CATPGMMakeDiagError(
  const int iNumberError,
  CATGeoFactory *iFactory,
  const CATLISTP(CATCell) &iListOfCellToShow);

//--------------------------------------------------------------------------------------
// Generate - if possible - a CATTopOpInError with identifier iMsgId (same as appears in
// NLS file) with diagnosis (error bodies)
//
// iListOfCellToShow : The list of cells to be sent with error as the location of error
//--------------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATTopOpInError *CATPGMMakeDiagError(
  const char *iMsgId,
  CATGeoFactory *iFactory,
  const CATLISTP(CATCell) &iListOfCellToShow);

//------------------------------------------------------------------------------
// Update a list of faces with respect to given body
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void CATPGMUpdateListOfSkinFaces(
  CATLISTP(CATFace) &iFaces,
  CATListOfInt &iOrientations,
  CATBody *iBody,
  CATCGMJournalList *iJournal);

//------------------------------------------------------------------------------
// Check maximum G0 or tangency gap on a shell in a body
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMCheckMaxGapOnShell(
  CATBody *iBody,
  CATShell *iShell,
  CATCGMDiagnosis *&oMaxGapOnResultDiagnosis,
  CATTopToolsGapCheckMode iGapCheckMode = CATTopToolsG0GapCheckMode,
  CATLISTP(CATEdge) *oGapEdges = NULL);

//------------------------------------------------------------------------------
// Check maximum G0 or tangency gap on a shell in a body
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMCheckMaxGapOnShell(
  CATBody *iBody,
  CATShell *iShell,
  CATCGMDiagnosis *&oMaxGapOnResultDiagnosis,
  CATTopToolsGapCheckMode iGapCheckMode,
  CATLISTP(CATEdge) *oGapEdges,
  const CATLISTP(CATEdge) &iListPOfEdgeToCheck);

ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMCheckBodyShellConnexity(
  CATSoftwareConfiguration *iConfig,
  CATGeoFactory *iFactory,
  CATBody *iBodyToCheck);

//------------------------------------------------------------------------------
// Check face
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATBoolean CATPGMCheckFace(
  CATBody *iBody,
  CATFace *iFace,
  CATLISTP(CATEdge) *oListOfEdgeOfNullLength = NULL);

#endif /* CATPGMCheckSkin_h_ */
