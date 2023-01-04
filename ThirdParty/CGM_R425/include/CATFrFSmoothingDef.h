#ifndef CATFrFSmoothingDef_H
#define CATFrFSmoothingDef_H

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The type of parametrization.
 * @param CATFrFSmoothingParamUniform
 * Equidistant parametrization.
 * @param CATFrFSmoothingParamChordal
 * Euclidian parametrization.
 * @param CATFrFSmoothingParamCentripetal
 * Not used.
 * @param CATFrFSmoothingParamSomOnComponent
 * Not used.
 * @param CATFrFSmoothingParamMaxOnComponent
 * Not used.
 */
typedef enum
{
  CATFrFSmoothingParamUniform        = 0
, CATFrFSmoothingParamChordal        = 1
, CATFrFSmoothingParamCentripetal    = 2
, CATFrFSmoothingParamSomOnComponent = 3
, CATFrFSmoothingParamMaxOnComponent = 4
} CATFrFSmoothingParamType;

/**
 * The cutting option.
 * @param CATFrFCuttingNo
 * No cutting.
 * @param CATFrFCuttingAutoLength
 * Cutting according to a length criteria.
 * @param CATFrFCuttingAutoAreaCurvatr
 * Cutting according to a curvature criteria.
 * @param CATFrFCuttingAutoLengthCurvatr
 * Cutting according to length and curvature criteria.
 * @param CATFrFCuttingCurvatureAnalysis
 * Cutting according to curvature criteria with inflection point analysis and high curvature analysis.
 */
typedef enum  // Options by default
{
  CATFrFCuttingNo                = 0
, CATFrFCuttingAutoLength        = 1
, CATFrFCuttingAutoAreaCurvatr   = 2
, CATFrFCuttingAutoLengthCurvatr = 3
, CATFrFCuttingCurvatureAnalysis = 4
} CATFrFCuttingOption;

/**
 * Criteria to stop the cutting.
 * @param CATFrFTestByAverageDeviation
 * When the average error is reached.
 * @param CATFrFTestByMaxDeviation
 * When the max error is reached.
 */
typedef enum
{
  CATFrFTestByAverageDeviation   = 0
, CATFrFTestByMaxDeviation       = 1
} CATFrFTestOfConvergence;

/**
 * Option to be used when CATFrFCuttingOption = CATFrFCuttingCurvatureAnalysis.
 * @param CATFrFNone
 * No treatment.
 * @param CATFrFInsertAtInflexion
 * Cutting is inserted at each inflection point.
 * @param CATFrFSurroundingInflexion
 * Cutting is inserted around each inflection point.
 */
typedef enum  // for CurvatureAnalysis Option
{
  CATFrFNone                   = 0
, CATFrFInsertAtInflexion      = 1
, CATFrFSurroundingInflexion   = 2
} CATFrFInflexionTreatment;

#endif
