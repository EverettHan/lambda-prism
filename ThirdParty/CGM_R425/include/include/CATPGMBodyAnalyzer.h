#ifndef CATPGMBodyAnalyzer_h_
#define CATPGMBodyAnalyzer_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMOperator.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATErrorDef.h"
#include "ListPOfListPOfCATFace.h"

class CATBody;
class CATPGMBodyAnalyzer;
class CATGeoFactory;
class CATLISTP_CATPrRep_;
class CATMathTransformation;
class CATTrdSSet;
class CATSoftwareConfiguration;
class CATTrdReport;
class CATTrdOptions;
class CATBSVGraph;
class CATUfrReport;
class CATVGraphOptions;
class CATIsTurnedOptions;
class CATLISTV(CATMathTransformation);
class CATLISTP(CATFace);
class CATLISTV(CATMathLine);
class CATLISTV(CATMathVector);
class CATLISTP(CATBody);

#define CATBodyAnalyzerImplIsCATExtGeoOperator
#ifdef CATBodyAnalyzerImplIsCATExtGeoOperator
class ExportedByCATGMOperatorsInterfaces CATPGMBodyAnalyzer : public CATCGMOperator
#else
class ExportedByCATGMOperatorsInterfaces CATPGMBodyAnalyzer 
#endif
{
public:
  /**
   * Constructor
   */
  CATPGMBodyAnalyzer(CATGeoFactory * iFactory, CATExtGeoOperator* iExtensible = NULL);

  /**
   * Destructor
   */
  virtual ~CATPGMBodyAnalyzer();

  /**
	* Returns S_OK whenever a Similarity exists so that Body2 = oTransfoFrom1To2(iBody1).
  * <br>iBody1 && iBody2 are the indexes of the bodies to be analyzed.
  * <br>iRequiredSimilarity is the required percentage of area (approximated for cylindrical holes) of similar faces for both bodies (between 0. & 1.).
  * <br>Negative similarity may be returned only if no positive similarity is found.
  * <br>Manage various options with iOptions. Default Options are available in CATTrdDefaultOptions.
  * <br>if S_OK, oReport contains information regarding detailed mapping & Transformation from iBody1 to iBody2. oReport must be a CATPGMTrdReportBody to benefit from interruptibility.
	*/
  virtual HRESULT AreSimilar(
    const int iBody1,
    const int iBody2,
    const double iRequiredSimilarity,
    const CATTrdOptions &iOptions,
    CATTrdReport &oReport) = 0;

  /**
	* Returns S_OK whenever a Similarity exists so that Bodies2 = oTransfoFrom1To2(iBodies1).
  * <br>iBodies1 && iBodies2 are the indexes of the bodies to be analyzed.
  * <br>iRequiredSimilarity is the required percentage of area (approximated for cylindrical holes) of similar faces for both bodies (between 0. & 1.).
  * <br>Negative similarity may be returned only if no positive similarity is found.
  * <br>Manage various options with iOptions. Default Options are available in CATTrdDefaultOptions.
  * <br>if S_OK, oReport contains information regarding detailed mapping & Transformation from iBodies1 to iBodies2.
	*/
  virtual HRESULT AreSimilar(
    const CATListOfInt &iBodies1,
    const CATListOfInt &iBodies2,
    const double iRequiredSimilarity,
    const CATTrdOptions &iOptions,
    CATTrdReport &oReport) = 0;

  /**
	* Restrict search on iBody to iSubset.
  * If iSubset is empty or this method is not called then the full Body is used.
  * Search will not found similar subset whenever iSubset is made of only coaxial cylinders, cone, torii or sphere.
	*/
  virtual HRESULT SetPartialSearch(const int iBody, const CATLISTP(CATFace) &iSubset) = 0;

  /**
	* Returns S_OK whenever exists one or several plane the Body is symmetric with regards to.
  * oDirections contains symmetry planes definitions.
	*/
  virtual HRESULT IsSymmetric(const int iBody, CATLISTV(CATMathLine) &oDirections) = 0;

  /**
  * @nodoc
  * Finds out extrusion directions and their areas (with regards to whole Body Area), sorted in decreasing order.
	*/
  virtual HRESULT IsExtruded(
    const int iBody,
    CATLISTV(CATMathVector) &oDirections,
    CATListOfDouble &oAreas) = 0;

  virtual HRESULT IsExtruded(
    const int iBody,
    CATLISTV(CATMathVector) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace &oContributors) = 0;

  /**
  * @nodoc
  * Finds out extrusion directions and their areas (with regards to Bodies Area), sorted in decreasing order.
	*/
  virtual HRESULT IsExtruded(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    CATLISTV(CATMathVector) &oDirections,
    CATListOfDouble &oAreas) = 0;

  virtual HRESULT IsExtruded(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    CATLISTV(CATMathVector) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  /**
  * @nodoc
  * Finds out directions of revolution and their areas (with regards to whole Body Area), sorted in decreasing order.
	*/
  virtual HRESULT IsTurned(
    const int iBody,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas) = 0;

  virtual HRESULT IsTurned(
    const int iBody,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  virtual HRESULT IsTurned(
    const int iBody,
    const CATIsTurnedOptions& iOptions,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  /**
  * @nodoc
  * Finds out directions of revolution and their areas (with regards to Bodies Area), sorted in decreasing order.
	*/
  virtual HRESULT IsTurned(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas) = 0;

  virtual HRESULT IsTurned(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  virtual HRESULT IsTurned(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    const CATIsTurnedOptions& iOptions,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  /**
  * @nodoc
  * Finds out planar areas and their areas (with regards to whole Body Area), sorted in decreasing order. Directions are oriented toward material.
	*/
  virtual HRESULT IsPlanar(
    const int iBody,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas) = 0;

  virtual HRESULT IsPlanar(
    const int iBody,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace &oContributors) = 0;

  /**
  * @nodoc
  * Finds out planar areas and their wet areas (with regards to Bodies wet Area), sorted in decreasing order. Directions are oriented toward material.
	*/
  virtual HRESULT IsPlanar(
    const CATListOfInt &iBodies,
    const CATLISTV(CATMathTransformation) &iPositions,
    CATLISTV(CATMathLine) &oDirections,
    CATListOfDouble &oAreas,
    ListPOfListPOfCATFace& oContributors) = 0;

  /**
  * @nodoc
  * Finds out canonic areas and their areas (with regards to whole Body Area), sorted in decreasing order. Only Planes, Cylinders & Cones are currently detected. Type definition is in CATGeometryType.h.
	*/
  virtual HRESULT IsCanonic(
    const int iBody,
    CATListOfInt &oTypes,
    CATLISTV(CATMathLine) &oLocations,
    CATListOfDouble oParams[2],
    CATListOfDouble &oAreas) = 0;

  /**
  * @nodoc
  * Analyze Topology. Not compatible with PartialSearch & non-manifold bodies.
	*/
  virtual HRESULT GetGenus(
    const int iBody,
    int &oGenus,
    int *oVolumesCount,
    int *oFacesCount,
    int *oEdgesCount,
    int *oVerticesCount) = 0;

  /**
  * @nodoc
  * Locate a similar, already known in an alphabet, shape. 
	*/
  virtual HRESULT LocateShape(const int iBody, CATUnicodeString &oShapeName) = 0;

  /**
  * @nodoc
  * Read this operator default shape names.
	*/
  virtual HRESULT GetAlphabet(CATListValCATUnicodeString &oNames) = 0;

  /**
  * @nodoc
  * Creates a TrdSSet representing the input body. CATTrdSSet can be streamed & compared to another CATTrdSSet.
	*/
  virtual CATTrdSSet *CreateTrdSSet(const int iBody) = 0;

  /**
  * @nodoc
  * Creates a TrdSSet representing the input bodies. 
  * The CATTrdSSet can be streamed & compared to another CATTrdSSet. 
  * All bodies containers must have the same scale.
	*/
  virtual CATTrdSSet *CreateTrdSSet(const CATListOfInt &iBodies) = 0;

  /**
  * @nodoc
  * Creates a BSVGraph representing the input body. CATBSVGraph can be streamed & compared (IsEqual) to another CATBSVGraph.
	*/
  virtual CATBSVGraph *CreateBSVGraph(const int iBody) = 0;

  /**	@nodoc
	* Returns S_OK whenever at least one iLookedForFeatureBodies-like exists in iSearchedBody.
  * <br>iLookedForFeatureBodies are the ordered indexes of the bodies to be looked for.
  * <br>iSearchedBody is the index of the body to be searched.
  * oReport contains detailed information about found features.
	*/
  virtual HRESULT SearchFeatures(
    const CATListOfInt &iLookedForFeatureBodies,
    const int iSearchedBody,
    CATUfrReport &oReport) = 0;

  virtual HRESULT SearchFeatures(
    const CATListOfInt& iLookedForFeatureBodies,
    const int iSearchedBody,
    const CATVGraphOptions& iOptions,
    CATUfrReport& oReport) = 0;
};

//----------------------------------------------------------------------------
// Public section
//----------------------------------------------------------------------------
/** 
	* Creates a CATPGMBodyAnalyzer operator.
	* @param iFactory
  * Factory in which objects may be created.
	* @param iConfig
  * CATSoftwareConfiguration to manage upward compatibility of changes in the implementation.
	* @param iBodies
	* List of bodies to be analyzed. 
 * @return [out, delete]
 */
ExportedByCATGMOperatorsInterfaces CATPGMBodyAnalyzer *CATPGMCreateBodyAnalyzer(
  CATGeoFactory &iFactory,
  CATSoftwareConfiguration &iConfig,
  CATLISTP(CATBody) &iBodies);

#endif /* CATPGMBodyAnalyzer_h_ */
