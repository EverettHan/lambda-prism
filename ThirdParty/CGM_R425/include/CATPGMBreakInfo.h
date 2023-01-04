#ifndef CATPGMBreakInfo_h_
#define CATPGMBreakInfo_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATBoolean.h"

class CATCurve;
class CATFrFCompositeCurve;
class CATFrFCompositeCurveMapping;
class CATFrFNormalMultiComb;
class CATFrFSmoothedComb;
class CATMathPlane;
class CATMathPolynomX;
class CATMathVector;
class CATCrvParam;
class CATMathPoint;

#define RemoveOf_CATPGMBreakInfo_JSX_11Mars2010

#ifdef RemoveOf_CATPGMBreakInfo_JSX_11Mars2010
//
// CATPGMBreakInfo n'a pas d'utilité
// Les applis n'ont pas a utiliser CATBreakInfo
// L'unique utilisation, dans CATGSMSketchEval est fausse !
//( pas de void SetBreakInfo(CATPGMBreakInfo* iBreakInfo ) dans la clsse mere CATSectionSolverEngine )
// Je vide la classe car GSD pointe encore dessus.
class ExportedByCATGMOperatorsInterfaces CATPGMBreakInfo: public CATCGMVirtual
  {
public:
  CATPGMBreakInfo();
  virtual ~CATPGMBreakInfo();
  };
#else


class ExportedByCATGMOperatorsInterfaces CATPGMBreakInfo: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMBreakInfo();

  /**
   * Destructor
   */
  virtual ~CATPGMBreakInfo();

  // Set Global
  virtual void SetIsOnGuide(CATBoolean iIsOnGuide) = 0;

  virtual void SetGuideRank(int iGuideRank) = 0;

  virtual void SetWithReferencePlane(CATBoolean iWithReferencePlane) = 0;

  virtual void SetReferenceContinuity(CATFrFContinuity iReferenceG1G2 = 0) = 0;

  virtual void SetTangentOnGuidePoint(CATMathPlane *iGuidePointTgtPlane) = 0;

  virtual void SetMultiComb(CATFrFNormalMultiComb *iMultiComb) = 0;

  virtual void SetSmoothInfo(CATFrFCompositeCurve * iSmoothCcv[2]) = 0;

  virtual void SetSmoothInfo(
    CATFrFCompositeCurve *iSmoothCcv,
    CATFrFCompositeCurveMapping *CCVMapping,
    const CATListOfInt & iShiftMap,
    const CATListOfDouble & iShiftParam) = 0;

  virtual void SetSmoothedCurvature(
    CATFrFCompositeCurve *iSmoothedCurvature,
    double iProfilParamToCrvParam[2],
    CATLaw *i_iT_to_W) = 0;

  // Get Global
  virtual CATBoolean IsOnGuide() = 0;

  virtual int GuideRank() = 0;

  virtual CATMathPlane *TransversalTgt() = 0;

  virtual CATBoolean WithReferencePlane() = 0;

  virtual CATLONG32 Reference() = 0;

  virtual CATBoolean IsCombSmoothed() = 0;

  virtual int SmoothMode() = 0;

  // SetGet pour les evaluations
  //============================
  // Set avant chaque evaluation
  virtual void SetDeformG1Effectivity(double iDeformG1Effectivity) = 0;

  virtual void SetDeformG2Effectivity(double iDeformG2Effectivity) = 0;

  virtual void SetDeformBalance(double iDeformBalance) = 0;

  virtual void SetInfoAboutGuide(CATCurve *iGuide, CATCrvParam &iParamOnGuide) = 0;

  virtual void SetInfoAboutComb(CATLONG32 iPeigneIndex) = 0;

  virtual void SetInfoForSmooth(
    CATLONG32 iSmoothDomainIndex,
    double iParamForSmoothData,
    CATLONG32 iSmoothGuideIndex) = 0;

  // Get
  virtual double DeformG1Effectivity() = 0;

  virtual double DeformG2Effectivity() = 0;

  virtual double DeformBalance() = 0;

  virtual void EvalPointExternalConstraint(CATMathPoint *ioGuidePoint) = 0;

  // je ne mets pas a jour ceci, le code est inactif (modif d'interface ce EvalTangencyExternalConstraint dans CATBreakInfo le 010714, NLD)
  virtual void EvalTangencyExternalConstraint(CATMathPlane *&ioTangentPlane) = 0;

  virtual void EvalCurvatureExternalConstraint(
    CATMathDirection &iDirOnTgPlane,
    CATMathVector &oCurvature) = 0;

  virtual void GetUsedCurvature(double &LastEvalCurvature, CATMathVector &LastEvalCurvatureVector) = 0;

};

#endif
#endif /* CATPGMBreakInfo_h_ */
