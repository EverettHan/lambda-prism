#ifndef CATTopOpInError_h
#define CATTopOpInError_h
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopOpInError class declaration
//               
//=============================================================================
class CATBody;
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"

#include "CATIAV5Level.h" // to suppress

#ifndef TopOpInFile
#define TopOpInFile "CATTopologicalOperators"
#endif

#ifndef BasicTopOpInFile
#define BasicTopOpInFile "CATBasicTopologicalOpe"
#endif

#ifndef TopObInFile
#define TopObInFile "CATTopologicalObjects"
#endif

#ifndef CATSurfacicAdvancedTopoOpeFile
#define CATSurfacicAdvancedTopoOpeFile "CATSurfacicAdvancedTopoOpe"
#endif

#ifndef CATSurfacicTopoOperatorsFile
#define CATSurfacicTopoOperatorsFile "CATSurfacicTopoOperators"
#endif

#include "CATListPOfCATCGMDiagnoses.h"
/** @nodoc */
enum {
      TopOpInNull,
      TopOpInNullProfileBody,
      TopOpInInvalidProfileBody,
      TopOpInNonConnexCenterBody,
      TopOpInNullCenterBody,
      TopOpInInvalidOperator,
      TopOpInNonManifold,
      TopOpInInvalidDimension,
      TopOpInInvalidCenterDimension,
      TopOpInInvalidShellOperand,
      TopOpInInvalidGeometry,
      TopOpInDiscontinuityGeometry,
      TopOpInNonConnectedBody,
      TopOpInTooLargeGapBody,
      TopOpInNonFrozenBody,
      TopOpInOffsetValue,
      TopOpInInvalidIndice,
      TopOpInNbPoints,
      TopOpInImposition,
      TopOpInTangency,
      TopOpInAxisProfileIntersection,
      TopOpInLinearCurve,
      TopOpIn3DCurve,
      TopOpInInvalidBodySize,
      TopOpInProfilePerpendicularToAxis,
      TopOpInProfileParallelToDirection,
	  TopOpInRibbonNullRadius,
		TopOpInExtrudeTwistedProfile,
		TopOpInExtrudeOverlappingProfiles,
		TopOpInExtrudeCuspProfile,
		TopOpInExtrudeOpenProfile,
		TopOpInCloseNonPlanarOpening,
		TopOpInCloseInvalidOpening,
    TopOpInBoundaryClosedBody,
    TopOpInBoundaryImmersedCell,
		TopOpInNotLyingOn,
		TopOpInPtNotLyingOnWire,
		TopOpInPtNotLyingOnShell,
		TopOpInTooSmallLength,
		TopOpInTooCloseLimits,
		TopOpInLoftOutsideProjection,
		TopOpInLoftNonPlanarSection,
		TopOpInFillNormal,
		TopOpInCornerOutsideSupport,
		TopOpInCornerDegenerated,
		TopOpInCornerNotAvailable,
		TopOpInParallelExtrapolation,
		TopOpInParallelRelimitation,
		TopOpInParallelLoop,
    TopOpInShellEmptyResultDueToOpenings,
    TopOpInInvalidSurface,
		TopOpInRibbonMultipleSelection,
		TopOpInRibbonVariableSelection,
      TopOpInProfileOrientationChanging,
      TopOpInProfileRevoluteOrientationChanging,
	  TopOpInNoIntersection,
      TopOpInPolyhedralInputNotAllowed
  };
/**
* Class for reporting an error with the inputs of a topological operation.
*/
class  ExportedByCATGMModelInterfaces CATTopOpInError : public CATCGMInputError
{
  public:
     	/** @nodoc */
     CATCGMNewClassArrayDeclare;

    /**
     * Declares that the class CATTopOpInError is an error class which derives
     * from CATInputError.
     */
    CATDeclareError(CATTopOpInError, CATCGMInputError)

    
    virtual ~CATTopOpInError();

    /**
     * Tests whether <tt>this</tt> error references bodies.
     * @param ioYesOrNo
     * The result of the test.
     * <br><b>Legal values</b>: <tt>TRUE</tt> if empty, <tt>FALSE</tt> if there is at least one body referenced. 
     */
    void IsEmpty (CATBoolean & ioYesOrNo);

    /**
     * Retrieves the list of diagnosis pointers of <tt>this</tt> error.
     * @param ioDiagnosisList
     * The list of the pointers to diagnoses. Once read,
     * the errors of the list must be managed by the caller. 
     * In particular, they must be deleted after use by the caller.
     * However, the method <tt>GetDiagnosisList</tt> is not called, 
     * the <tt>CATTopOpInError</tt> destructor deletes them.
     * @param iReadOnly
     * Dedicated to the case where you just want to read.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the errors of the list must be deleted after use by the caller (default mode),
     * <tt>TRUE</tt> otherwise.
     */
    void GetDiagnosisList(CATLISTP(CATCGMDiagnosis) & ioDiagnosisList,
                          const CATBoolean iReadOnly = FALSE);
    
    /**
     * Sets the list of diagnosis pointers of <tt>this</tt> error.
     * @param iDiagnosisList
     * The list of the pointers to the diagnoses. To be called inside
     * an operator as an help for the caller.
     * @param iAppendOnly
     * Dedicated to the case where the previous list of diagnosis was not empty.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the previous list of diagnosis is forgotten,
     * <tt>TRUE</tt> if the previous list of diagnosis is kept.
     */
    void SetDiagnosisList (const CATLISTP(CATCGMDiagnosis) & iDiagnosisList,
                           const CATBoolean iAppendOnly = FALSE);

    /**
     * Tests whether a body is referenced inside one of the lists of the referenced diagnoses.
     * @param iBodyTest
     * The pointer to the body to test.
     * @param ioYesOrNo
     * The result of the test.
     * <br><b>Legal values</b>: <tt>TRUE</tt> if the body is referenced, <tt>FALSE</tt> otherwise. 
     */
    void Contains (CATBody* iBodyToTest, CATBoolean & ioYesOrNo);

    /**
     * @nodoc
     * return The first diagnosis if it exists.
     * No deletion can be done on this first diagnosis, as it has not been consired as read,
    */
    CATCGMDiagnosis *HasFirstDiagnosis();
    
    /** @nodoc */
    CATTopOpInError (const CATTopOpInError & iError);

    /** @nodoc */
    CATTopOpInError& operator=(const CATTopOpInError&);


  private:
    void Init();
    CATLISTP(CATCGMDiagnosis) _DiagnosisList;
    CATBoolean                _IsRead;

};
//

#endif
