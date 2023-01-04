#ifndef CATIPGMLocalComparison2D_h_
#define CATIPGMLocalComparison2D_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATIPGMVirtual.h"

class CATIPGMLocalAnalysis2D;
class CATMathDirection2D;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMLocalComparison2D;

/**
* Class defining the local Comparison on a point of a two CATSurfaces.
* The two surfaces have to haeve the same parametrization/
*<br>It performs deformation in length on a point of a CATSurface. This class is not streamable.
* The point where the analysis is done can be changed by @href CATIPGMLocalComparison2D#SetParam.
*/
class ExportedByCATGMModelInterfaces CATIPGMLocalComparison2D: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMLocalComparison2D();

  /**
    * Modifies the point where <tt>this</tt> CATIPGMLocalComparison2D is performed.
    *<br>The comparison is automatically done.
    * @param iNewParamToAnalyze
    * The parameter of the new point to analyze.
    */
  virtual void SetParam(const CATSurParam &iNewParamToAnalyze) = 0;

  /**
    * @nodoc
    */
  virtual void SetReferenceSurface(CATSurface *iRefSurface) = 0;

  /**
    * @nodoc
    */
  virtual double GetDeformation() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLocalComparison2D(); // -> delete can't be called
};

#endif /* CATIPGMLocalComparison2D_h_ */
