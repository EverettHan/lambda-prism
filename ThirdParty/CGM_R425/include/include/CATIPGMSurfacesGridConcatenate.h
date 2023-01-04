#ifndef CATIPGMSurfacesGridConcatenate_h_
#define CATIPGMSurfacesGridConcatenate_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATGeoOpTimer;
class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATString;
class CATMathTransformation2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurfacesGridConcatenate;

//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMSurfacesGridConcatenate: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurfacesGridConcatenate();

  // to specify the objective continuity
  //the default value is 2
  virtual void SetObjectiveContinuity(CATLONG32 objectiveContinuity) = 0;

  // 0, 1 or 2 (2 is default value)
  virtual void SetKindOfContinuity(CATLONG32 kindOfContinuity = 0) = 0;

  // 1 for G 
  virtual void MakeNoShapeOptimization() = 0;

  virtual CATLONG32 RunConcatenationCheck() = 0;

  // the expected deformation
  // computed only for if kindOfContinuity==0
  virtual double GetMinimumDeviationForC0Mode() = 0;

  // effectuer la concatenation en une seule surface C0. toujours calculee
  virtual double GetAngleThresholdForG1Concatenation() = 0;

  // pour effectuer la concatenation en une seule surface G1. toujours calculee
  virtual double GetMinimumDeviationForCnMode() = 0;

  // effectuer la concatenation en une seule surface C0(G1), C1 ou C2
  //
  //  2 other deviations will be taken into account and can not really be mixed with the first one :
  //  - The first one is the parametric deviation, and enable to concatenate the grid of surface into 
  //  one C0-surface. We will call it the parametric deviation
  //  - The second deviation is the deformation that is necessary to improve the level of continuity from
  //  C0 (after concatenation) to the objective continuity (C1 or C2).
  // To simplify the interface of the current class, we just let the user specify one tolerance
  // that will be used as the sum of two tolerances.
  // Hence, it has to be greater to the C0-Parametric minimal deviation. Otherwise, we can even not
  // concatenate. If the global deforation tolerance is smaller thant the C0-parametric deviation,
  // the operator will fail.
  // Secondly, the tolerance of the optimisation will be the difference of the global deformation
  // tolerance with the C0-parametric deviation.
  //
  // If the user set the globalDeformationTolerance to -1, we will force
  // the C0 concatenation as well as the optimisation into one single surface.
  virtual void SetGlobalDeformationTolerance(double globalDeformationTolerance = -1.) = 0;

  virtual void SetGTolerance(double maximumAuthorizedGTolerance) = 0;

  virtual void SetNoReparametrization() = 0;

  // sum of the C0parametric tolerance and of the optimisation tolerance
  virtual double GetGlobalDeformation() = 0;

  virtual void GetResultingSurfaces(
    CATNurbsSurface **&resultingSurfaces,
    CATLONG32 &nbSurfU,
    CATLONG32 &nbSurfV) = 0;

  // supply the user with index correspondance between of the input and output surfaces,
  // as well as with 2d-transformation between the initial surface and the resulting one.
  virtual CATLONG32 GetSurfaceMapping(
    CATLONG32 iNumSurfUInit,
    CATLONG32 iNumSurfVInit,
    CATLONG32 &iNumSurfUNew,
    CATLONG32 &iNumSurfVNew,
    CATMathTransformation2D &transfor2D) = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurfacesGridConcatenate(); // -> delete can't be called
};

// Do not use from V5R15 - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
/* NLD270120
ExportedByCATGMModelInterfaces CATIPGMSurfacesGridConcatenate *CATPGMCreateSurfacesGridConcatenate(
  CATGeoFactory *factory,
  CATNurbsSurface **initialSurfaces,
  CATLONG32 nbSurfI,
  CATLONG32 nbSurfJ,
  CATLONG32 *iExchangeIJFlags,
  CATLONG32 *iInvertIFlags,
  CATLONG32 *iInvertJFlags,
  double *internalStartIParameters,
  double *internalEndIParameters,
  double *internalStartJParameters,
  double *internalEndJParameters);
*/

// on a une grille de nbSurfI surfaces dans la direction I
// et de nbSurfJ surfaces dans la direction J (i en horizontal (pour les colonnes) et j en vertival (pour les lignes)).
// on ordonnera les surfaces dans le sens I d'abord :
// surfaces rangees suivant les u croissants d'abord.
// surf(i,j)=initialSurfaces[j*nbSurfI+i]
// les surfaces resultats seront parametrees en u suivant I et en v suivant J.
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfacesGridConcatenate *CATPGMCreateSurfacesGridConcatenate(
  CATGeoFactory *factory,
  CATSoftwareConfiguration *iConfig,
  CATNurbsSurface **initialSurfaces,
  CATLONG32 nbSurfI,
  CATLONG32 nbSurfJ,
  CATLONG32 *iExchangeIJFlags,
  CATLONG32 *iInvertIFlags,
  CATLONG32 *iInvertJFlags,
  double *internalStartIParameters,
  double *internalEndIParameters,
  double *internalStartJParameters,
  double *internalEndJParameters);

#endif /* CATIPGMSurfacesGridConcatenate_h_ */
