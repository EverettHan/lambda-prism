#ifndef CATIPGMSurfTopoOpeItfBldr_h
#define CATIPGMSurfTopoOpeItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "CATTopologicalFillType.h"

class CATIPGMFilling;
class CATGeoFactory;
class CATTopData;
class CATIPGMHealing;
class CATBody;
class CATIPGMTopologicalAutomaticFill;
class CATIPGMPowerFill;
class CATICGMPowerFill;
class CATIPGMTopologicalFill;
class CATIPGMTopoDeformSwitchGeometry; 
class CATCGMJournalList;
class CATCldPolygon;
class CATPowerCldPolygon;
class CATIPolyMesh;
class CATIPGMPolygon2Surface;
class CATLISTP(CATBody);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);
class CATIPGMTopXHealingOp;
class CATIPGMSurfaceSimplification;
class CATIPGMTopSurfacesDesingularizationOp;
class CATApproxStrategy;
class CATIPGMTopDeformation;
class CATSpaceDeformationMapDefine;
class CATSpaceDeformationTopoMap;
class CATCGMBendCylindricalDefine;
class CATCGMUnbendCylindricalDefine;
class CATMathPoint;
class CATMathDirection;
class CATPolyMeshMappingFunction;
class CATSoftwareConfiguration;
class CATFace;
class CATIPGMHealGaps;
class CATICGMHealGaps;
class CATICGMObject;


extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurfTopoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework SurfacicTopoOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSurfTopoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMFilling *CATPGMCreateFilling(CATGeoFactory *iFactory, CATTopData *iData) = 0;

  virtual CATIPGMHealing *CATPGMCreateHealing(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToHeal) = 0;

  virtual CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
	CATGeoFactory *iFactory,
	CATTopData *iTopData,
	const CATLISTP(CATEdge) *iListOfEdges,
	const CATLISTP(CATFace) *iListOfFaces,
	const CATBody *iBody,
	const CATTopologicalFillType iFillType) = 0;

  virtual CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATLISTP(CATBody) const &iListOfWires,
	CATLISTP(CATBody) const &iListOfSupports,
	const CATTopologicalFillType iFillType) = 0;

  virtual CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATLISTP(CATBody) const &iListOfWires,
	const CATTopologicalFillType iFillType) = 0;

  virtual CATIPGMTopologicalAutomaticFill *CATPGMCreateTopologicalAutomaticFill(
	CATGeoFactory *iFactory,
	CATTopData *iData) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateAutomaticFill(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATLISTP(CATBody) const &iListOfWires,
	CATLISTP(CATBody) const &iListOfSupports,
	const CATTopologicalFillType iFillType) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalAutomaticFill(
	CATGeoFactory *iFactory,
	CATLISTP(CATBody) const &iListOfWires,
	const CATTopologicalFillType iFillType,
	CATCGMJournalList *iJournal) = 0;

  virtual CATICGMPowerFill *CATCGMCreatePowerFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires) = 0;

  virtual CATICGMPowerFill *CATCGMCreatePowerFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports) = 0;

  virtual CATIPGMPowerFill *CATPGMCreatePowerFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires) = 0;

  virtual CATIPGMPowerFill *CATPGMCreatePowerFill(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports) = 0;

  virtual CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATCldPolygon *iCldPolygon,
	const short iLevel) = 0;

  virtual CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATPowerCldPolygon *iCldPolygon,
	const short iLevel) = 0;

   virtual CATIPGMTopoDeformSwitchGeometry *CATPGMCreateTopoDeformSwitchGeometry(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATBody *iBodyToDeform) = 0;

  virtual CATIPGMPolygon2Surface *CATPGMCreatePolygon2Surface(
	CATGeoFactory *iFactory,
	CATTopData *iData,
	CATIPolyMesh *ipPolyMesh) = 0;

	//virtual CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
	//CATGeoFactory *ipFactory,
	//CATTopData *ipTopData,
	//CATBody *ipBodyToHeal) = 0;

	//virtual CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
	//CATGeoFactory *ipFactory,
	//CATTopData *ipTopData,
	//CATBody *ipBodyToHeal,
	//const int iMode) = 0;

  virtual CATIPGMSurfaceSimplification *CATPGMCreateSurfaceSimplification(
	CATGeoFactory *iFactory,
	CATTopData *iTopData,
	CATBody *iBodyToBeSimplified) = 0;

  virtual CATIPGMTopSurfacesDesingularizationOp *CATPGMCreateTopSurfacesDesingularizationOp(
	CATGeoFactory *ipFactory,
	CATTopData *ipTopData,
	CATBody *ipBody) = 0;

   virtual CATApproxStrategy *CATCGMCreateApproxStrategy(
    const CATLONG32 iMaxDegree,
    const CATLONG32 iMaxNumberOfSpan,
    const CATBoolean iKeepDegree,
    const CATBoolean iKeepSegmentation,
    const double iTolG0,
    const double iTolG1,
    const double iTolG2,
    const CATBoolean iKeepParametrization,
    const CATBoolean iIncreaseDegreeBefSeg) = 0;

  virtual CATIPGMTopDeformation *CATPGMCreateTopDeformation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSpaceDeformationMapDefine *iMapDefine,
  CATBody *iBodyToBeDeformed) = 0;

  virtual CATIPGMTopDeformation *CATPGMCreateTopDeformation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATSpaceDeformationTopoMap *iMapDefine,
  CATBody *iBodyToBeDeformed) = 0;

  virtual CATCGMBendCylindricalDefine* CATCGMCreateBendCylindricalDefine(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATMathPoint const & iNeutralPoint, 
	CATMathDirection const & iBendDir, 
	double iBendRadius, 
	CATMathDirection const & iWidthDir, 
	double iWidth) = 0;

  virtual CATCGMUnbendCylindricalDefine* CATCGMCreateUnbendCylindricalDefine(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATMathPoint const & iNeutralPoint, 
	CATMathDirection const & iBendDir, 
	double iBendRadius, 
	CATMathDirection const & iWidthDir, 
	double iUnbentWidth) = 0;

    virtual int CATPGMPutPolyMeshMappingFunctionAttr(
    CATBody *iopBody,
    CATPolyMeshMappingFunction *ipMappingFunction,
    CATSoftwareConfiguration *ipConfig) = 0;

  virtual int CATPGMGetPolyMeshMappingFunction(
    CATBody *ipBody,
    CATSoftwareConfiguration *ipConfig,
    CATPolyMeshMappingFunction *&opMappingFunction) = 0;

  virtual int CATPGMReleasePolyMeshMappingFunctionAttr(
    CATBody *iopBody,
    CATSoftwareConfiguration *ipConfig) = 0;

   virtual int CATPGMEvalPolyMeshMappingFunction(
    CATPolyMeshMappingFunction *ipMappingFunction,
    const CATMathPoint &iPointToEval,
    CATFace *ipPointSuppport,
    double oUV[2]) = 0;

  virtual CATICGMHealGaps *CATCGMCreateHealGaps(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipInputBody) = 0;

  virtual CATIPGMHealGaps *CATPGMCreateHealGaps(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipInputBody) = 0;
// @KTU20141110
  virtual int CATPGMPutPolyMeshMappingFunctionAttr(
    CATICGMObject *iopObject,
    CATPolyMeshMappingFunction *ipMappingFunction,
    CATSoftwareConfiguration *ipConfig) = 0;

  virtual int CATPGMGetPolyMeshMappingFunction(
    CATICGMObject *ipObject,
    CATSoftwareConfiguration *ipConfig,
    CATPolyMeshMappingFunction *&opMappingFunction) = 0;

  virtual int CATPGMReleasePolyMeshMappingFunctionAttr(
    CATICGMObject *iopObject,
    CATSoftwareConfiguration *ipConfig) = 0;

};

/**
 * Returns the factory of implementations of interfaces for the framework SurfacicTopoOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMSurfTopoOpeItfBldr *CATCGMGetSurfTopoOpeItfBldr();

#endif /* CATIPGMSurfTopoOpeItfBldr_h */
