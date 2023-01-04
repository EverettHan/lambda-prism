#ifndef CAT_PCRV_PATCH_ANALYSIS_H
#define CAT_PCRV_PATCH_ANALYSIS_H

#include "Y30UIUTI.h"
#include "CATGeoOperator.h"

class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvLimits;

/**
 * Find patches under a given PCurve as well as the CATCrvParams corresponding
 * to patch boundary crossings
 */
class ExportedByY30UIUTI CATPCrvPatchAnalysis : public CATGeoOperator
{
public:
  virtual ~CATPCrvPatchAnalysis();

  /**
   * If called, the analysis will only provide underlying patches but not
   * the patch boundary crossing CATCrvParams.
   */
  virtual void SetNoSegments() = 0;

  /**
   * Run the analysis
   *
   * @return 0 if successful, negative number otherwise.
   */
  // SMT1 19.06.20 Now that CATPCrvPatchAnalysis is derived from CATGeoOperator RunOperator (in CATPCrvPatchAnalysisCX2)
  // is used and Run is managed by the operator infrastructure.
  //virtual int Run() = 0;

  /**
   * @return negative number upon error, the number of patches found otherwise.
   */
  virtual int GetNbPatches() const = 0;

  /**
   * @param[in] num patch number between 0 and GetNbPatches()-1
   * @param[out] oU u patch number on underlying surface
   * @param[out] oV v patch number on underlying surface
   * @return negative number upon error, number of segments from the curve
   *         crossing the current patch otherwise
   */
  virtual int GetPatch(int num, int &oU, int &oV) const = 0;

  /**
   * @param[in] num patch number between 0 and GetNbPatches()-1
   * @param[in] i segment number between 0 and GetPatch(num, u, v)-1
   * @param[out] oLimits curve limits for the segment
   * @return 0 if successful, negative number otherwise
   */
  virtual int GetSegment(int num, int i, CATCrvLimits &oLimits) const = 0;

protected:
  CATPCrvPatchAnalysis();
  CATPCrvPatchAnalysis(CATGeoFactory            * factory);

private:
  CATPCrvPatchAnalysis(const CATPCrvPatchAnalysis &);
  void operator = (const CATPCrvPatchAnalysis &);
};

/**
 * Create a CATPCrvPatchAnalysis operator
 *
 * @param[in] iSoftwareConfiguration software configuration
 * @param[in] iCurve PCurve to analyse
 * @param[in] iLimits limits on which to run the analysis
 * @return pointer to CATPCrvPatchAnalysis operator. Needs to be deleted by the caller.
 */
ExportedByY30UIUTI CATPCrvPatchAnalysis *CATCreatePCrvPatchAnalysis(CATSoftwareConfiguration *iSoftwareConfiguration, const CATPCurve &iCurve, const CATCrvLimits &iLimits);

#endif
