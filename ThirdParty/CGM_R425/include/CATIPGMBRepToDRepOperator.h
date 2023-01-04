#ifndef CATIPGMBRepToDRepOperator_h_
#define CATIPGMBRepToDRepOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDeclarativeContext.h"

class CATBRepToDRepExtTopOperator;
class CATDeclarativeManifoldAgent;
class CATLISTP(CATAgentRelationNode);
class CATLISTP(CATFace);
class CATLISTP(CATManifoldNavigator);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBRepToDRepOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMBRepToDRepOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBRepToDRepOperator();

  virtual HRESULT AddDeclarativeManifoldAgent(CATDeclarativeManifoldAgent *&ioAgent) = 0;

  virtual HRESULT GenerateBaseAgents(
    CATDeclarativeApplication iAppli,
    CATDeclarativeContext &iContext,
    CATDeclarativeOriginModeler iModeler) = 0;

  virtual HRESULT GenerateMandatoryAgents(
    CATDeclarativeApplication iAppli,
    CATDeclarativeContext &iContext,
    CATDeclarativeOriginModeler iModeler,
    CATLISTP(CATAgentRelationNode) &iMandatoryNodes,
    CATLISTP(CATAgentRelationNode) &iForbiddenNodes) = 0;

  virtual void SetUserDefinedSelection(CATLISTP(CATFace) &iUserSelection) = 0;

  // ---------------------------
  // Industry Assistant Methods
  // ---------------------------
  // The Set has to be done before the Get Method.
  virtual void SetCandidateIndustryList(CATListOfInt &iCandidateIndustryList) = 0;

  // Return the recommended industries among the candidate industries.
  virtual void GetRecommendedIndustryList(CATListOfInt &oRecommendedIndustryList) = 0;

  // The iIndustry has to be among the candidate industries.
  virtual void GetLostFilletList(
    CATDeclarativeContextIndustry iIndustry,
    CATLISTP(CATCell) &oLostFilletList,
    double &oMinLostRadius,
    double &oMaxLostRadius) = 0;

  // The iIndustry has to be among the candidate industries.
  virtual void GetRecognizedFilletList(
    CATDeclarativeContextIndustry iIndustry,
    CATLISTP(CATCell) &oRecognizedFilletList,
    double &oMinRecogRadius,
    double &oMaxRecogRadius) = 0;

  // The iIndustry has to be among the candidate industries.
  virtual void GetLostChamferList(
    CATDeclarativeContextIndustry iIndustry,
    CATLISTP(CATCell) &oLostChamferList,
    double &oMinLostDistance,
    double &oMaxLostDistance) = 0;

  // The iIndustry has to be among the candidate industries.
  virtual void GetRecognizedChamferList(
    CATDeclarativeContextIndustry iIndustry,
    CATLISTP(CATCell) &oRecognizedChamferList,
    double &oMinRecogDist,
    double &oMaxRecogDist) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBRepToDRepOperator(); // -> delete can't be called
};

// ----------------------------
// CATPGMCreateBRepToDRepOperator creation method.
// Release iContext after use.
// ----------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBRepToDRepOperator *CATPGMCreateBRepToDRepOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATDeclarativeApplication iAppli,
  CATDeclarativeContext &iContext,
  CATDeclarativeOriginModeler iModeler);

// ----------------------------
// Old creation method for CATPGMCreateBRepToDRepOperator
// Soon Deprecated
// ----------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBRepToDRepOperator *CATPGMCreateBRepToDRepOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMBRepToDRepOperator_h_ */
