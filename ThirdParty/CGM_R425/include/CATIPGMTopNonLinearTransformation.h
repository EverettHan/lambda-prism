#ifndef CATIPGMTopNonLinearTransformation_h_
#define CATIPGMTopNonLinearTransformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATCurve;
class CATGeoFactory;
class CATGeometry;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATSurface;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopNonLinearTransformation;

/**
* Class representing the topological operator that transforms a CATBody.
* <br>
* It follows the use frame of all operator and satisfies to the smart mechanism: the
* input body is not modified. A new resulting body is created, 
* possibly sharing data with the input one.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopNonLinearTransformation: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopNonLinearTransformation();

  /** 
   * @nodoc
   * Adds a CATGeometry to transform with <tt>this</tt> CATIPGMTopNonLinearTransformation.
   *<br>All the added objects must belong
   * to the same factory.
   * @param iObjectToTransform
   * A pointer to the CATGeometry to add to the CATIPGMTopNonLinearTransformation.
   * @param iTransformedObject
   * If not NULL, it forces the transformation of <tt>iObjectToTransform</tt> to be
   * the object <tt>iTransformedObject</tt>. This must be compatible with the
   * given transformation of the CATIPGMTopNonLinearTransformation.
   */
  virtual void Add(
    CATGeometry *iObjectToTransform,
    CATGeometry *iTransformedObject = 0) = 0;

  /** 
   * @nodoc
   */
  virtual void Add(
    CATSurface *iSurfaceToTransform,
    CATSurface *iTransformedSurface,
    CATMathTransformation2D *iTransfo2D = 0) = 0;

  /** 
   * @nodoc
   */
  virtual void Add(
    CATCurve *iCurveToTransform,
    CATCurve *iTransformedCurve,
    CATMathTransformation1D *iTransfo1D = 0) = 0;

  /**
   * @nodoc
   * Returns whether all the surfaces of the resulting body are valid
   * @return
   * The result of the test.
   */
  virtual CATBoolean CheckSurfacesOfResultBody() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopNonLinearTransformation(); // -> delete can't be called
};

#endif /* CATIPGMTopNonLinearTransformation_h_ */
