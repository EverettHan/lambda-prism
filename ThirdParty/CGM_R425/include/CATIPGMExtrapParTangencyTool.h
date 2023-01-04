#ifndef CATIPGMExtrapParTangencyTool_h_
#define CATIPGMExtrapParTangencyTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMExtrapolParallelTool2.h"
/**
 * @level Protected
 * @usage U1
 */
class CATBody;
class CATDomain;
class CATMathPoint;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapParTangencyTool;

/**
* Class which defines the tangency extrapolation in an offset operation.
* A CATIPGMExtrapParTangencyTool operator is created with the 
* <tt>CATPGMCreateExtrapParTangencyTool</tt> global function.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapParTangencyTool: public CATIPGMExtrapolParallelTool2
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapParTangencyTool();

  /** @nodoc */
  virtual int ComputeExtrapolationPar(
    CATBody * Wire[2],
    CATLaw **MapLaw1,
    CATLaw **MapLaw2,
    CATBody * Parallel[2],
    CATBody * Extrap[2],
    CATCGMJournalList *Report,
    CATLONG32 WT[2]) = 0;
  /** @nodoc */
  virtual int GetExtrapInfo() = 0;
  /** @nodoc */
  virtual CATLONG32 GetConnexionInfo() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapParTangencyTool(); // -> delete can't be called
};

/**
* Creates a CATIPGMExtrapParTangencyTool object. This object defines the
* parameters of an offset operator with sharp relimitation. 
* @param iGeoFactory
* The pointer to the factory of the resulting body.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iDist
* The definition of the distance parameters for the operation.
* @param iShFond
* The surface on which the wire is extrapolated.
* @return [out, IUnknown#Release]
* The pointer to the created object. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMExtrapParTangencyTool *CATPGMCreateExtrapParTangencyTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATICGMDistanceTool *iDist,
  CATBody *iShFond);

#endif /* CATIPGMExtrapParTangencyTool_h_ */
