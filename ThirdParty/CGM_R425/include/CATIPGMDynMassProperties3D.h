#ifndef CATIPGMDynMassProperties3D_h_
#define CATIPGMDynMassProperties3D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATMathDef.h"

class CATTopData;
class CATMathPoint;
class CATBody;
class CATFace;
class CATEdge;
class CATMath3x3Matrix;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynMassProperties3D;

/**
 * Class representing the operator that computes geometric characteristics of a body , a face
 * or a edge.
 * <br>To use it:
 * <ul><li>Create an operator with the <tt>CATPGMDynCreateMassProperties3D</tt> global function.
 * <li> Get the results with the appropriate methods.
 * <li><tt>delete</tt> after use.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynMassProperties3D();

  /**
 * Returns the volume of the analyzed body.
 * @return
 * The volume (in case of solid bodies). <tt>NULL</tt> for shell bodies.
 */
  virtual double GetVolume() = 0;

  /**
 * Returns the surface of the analyzed body.
 * @return
 * The surface area. In case of a 3D bodies (lump domains), 
 * the computed surface is the outside surface: cavities immersed
 * inside the 3D body are not taken into account. In case of 2D bodies (shell domains), 
 * the holes are taken into account.
 */
  virtual double GetWetArea() = 0;

  /**
 * Returns the length of the analyzed body.
 * @return
 * Useful in case of 1D bodies (wire domains).
 */
  virtual double GetLength() = 0;

  /**
 * Returns the center of gravity of the analyzed body.
 * @return
 * The center of gravity.
 * For body made of shell , the center of gravity is equivalent to a extruded volume from the shell with a unitary thickness.
 * For body made of wire  , the center of gravity is equivalent to a sweeped volume along the wire with a unitary cross section.
 */
  virtual CATMathPoint GetCenterOfGravity() = 0;

  /**
 * Returns the inertia matrix of the analyzed body.
 * @return
 * The inertia matrix.
 * The inertia matrix is relative to the center of gravity.
 * For body made of shell , the inertia matrix is equivalent to a extruded volume from the shell with a unitary thickness.
 * For body made of wire  , the inertia matrix is equivalent to a sweeped volume along the wire with a unitary cross section.
 */
  virtual CATMath3x3Matrix GetInertiaMatrix() = 0;

  /**
 * Returns an estimation of the volume relative error.
 * @param oIsRelativeErrorAvailableWithMethod
 * TRUE if the relative error is available with the method or FALSE else.
 * @return
 * The estimation of the volume relative error if applicable or 0.
 */
  virtual double GetVolumeRelativeError(
    CATBoolean &oIsRelativeErrorAvailableWithMethod) = 0;

  /**
 * Returns an estimation of the wet area relative error.
 * @param oIsRelativeErrorAvailableWithMethod
 * TRUE if the relative error is available with the method or FALSE else.
 * @return
 * The estimation of the wet area relative error if applicable or 0.
 */
  virtual double GetWetAreaRelativeError(
    CATBoolean &oIsRelativeErrorAvailableWithMethod) = 0;

  /**
 * Returns an estimation of the center of gravity relative error.
 * @param oIsRelativeErrorAvailableWithMethod
 * TRUE if the relative error is available with the method or FALSE else.
 * This method is not applicable for body made of wire.
 * @param oRelativeError
 * gives the relative center of gravity position error along axis X , Y , Z
 * @param oMaximalDimension
 * gives the maximal dimension of the part along axis X , Y , Z. 
 * This value is not the exact dimension but is extracted from the bounding box of the body.
 * <br>To have the absolute center of gravity error :
 * <ul>
 * <li>* oRelativeError[0] * ( 1 + oMaximalDimension[0] ) gives the absolute error along axis X
 * <li>* oRelativeError[1] * ( 1 + oMaximalDimension[1] ) gives the absolute error along axis X
 * <li>* oRelativeError[2] * ( 1 + oMaximalDimension[2] ) gives the absolute error along axis X
 * </ul>
 * This method is not applicable to the body made of wires.
 */
  virtual void GetCenterOfGravityRelativeError(
    CATBoolean &oIsRelativeErrorAvailableWithMethod,
    double oRelativeError[3],
    double oMaximalDimension[3]) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynMassProperties3D(); // -> delete can't be called
};

/**
 * @deprecated V5R15 Use now the signature with CATTopData.
 * Constructs an operator that computes geometric characteristics of a body.
 * @param iToAnalyze
 * The pointer to the body to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(const CATBody *iToAnalyze);

/**
 * @deprecated V5R15 Use now the signature with CATTopData.
 * Constructs an operator that computes geometric characteristics of a face.
 * @param iFaceToAnalyze
 * The pointer to the face to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
  const CATFace *iFaceToAnalyze);

/**
 * @deprecated V5R15 Use now the signature with CATTopData.
 * Constructs an operator that computes geometric characteristics of a edge.
 * @param iEdgeToAnalyze
 * The pointer to the edge to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
  const CATEdge *iEdgeToAnalyze);

/**
 * Constructs an operator that computes geometric characteristics of a body.
 * @param iToAnalyze
 * The pointer to the body to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
  class CATTopData *iTopData,
  const CATBody *iToAnalyze);

/**
 * Constructs an operator that computes geometric characteristics of a face.
 * @param iFaceToAnalyze
 * The pointer to the face to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
  class CATTopData *iTopData,
  const CATFace *iFaceToAnalyze);

/**
 * Constructs an operator that computes geometric characteristics of a edge.
 * @param iEdgeToAnalyze
 * The pointer to the edge to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynMassProperties3D *CATPGMDynCreateMassProperties3D(
  class CATTopData *iTopData,
  const CATEdge *iEdgeToAnalyze);

#endif /* CATIPGMDynMassProperties3D_h_ */
