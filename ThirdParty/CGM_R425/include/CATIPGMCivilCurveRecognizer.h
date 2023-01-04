#ifndef CATIPGMCivilCurveRecognizer_h_
#define CATIPGMCivilCurveRecognizer_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCivilCurveDef.h"

class CAT2DCurveEvaluator;
class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;

#include "CATCivilCurveArchiTEMP.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCivilCurveRecognizer;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByCATGMModelInterfaces CATIPGMCivilCurveRecognizer: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCivilCurveRecognizer();

  //-----------------------------------------------------------------------------
  // Output Interface (Get)
  //-----------------------------------------------------------------------------
  /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent.
   * <br>S_OK    If the operator has not encountered any issue.
   */
  virtual HRESULT GetRunStatus() const = 0;

  /**
   * @param oType
   * The civil curve type recognized.
   * @return
   * <br> S_OK if the oType retrieved is valid, E_FAIL otherwise.
   */
  virtual HRESULT GetCurveType(CATCivilCurveType &oType) const = 0;

  /**
   * @param oCurveEvaluator
   * The 2D curve evaluator of the civil curve detected.
   * <br> Contains the civil curve properties. Use the CATExtractCivilCurve*** methods to extract the information.
   * <br> The object life of the object retrieved has to be handle by the caller.
   */
  virtual HRESULT GetEvaluator(CAT2DCurveEvaluator *&oCurveEvaluator) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCivilCurveRecognizer(); // -> delete can't be called
};

#endif /* CATIPGMCivilCurveRecognizer_h_ */
