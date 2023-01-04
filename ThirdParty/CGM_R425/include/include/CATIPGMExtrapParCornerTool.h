#ifndef CATIPGMExtrapParCornerTool_h_
#define CATIPGMExtrapParCornerTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2000
/**
 * @level Protected
 * @usage U1
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMExtrapolParallelTool2.h"

class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapParCornerTool;
/**
* Class which defines the round extrapolation in an offset operation.
* A CATIPGMExtrapParCornerTool operator is created with the 
* <tt>CATPGMCreateExtrapParCornerTool</tt> global function.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapParCornerTool: public CATIPGMExtrapolParallelTool2
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapParCornerTool();

  /** @nodoc */
  virtual int ComputeExtrapolationPar(
    CATBody * Wire[2],
    CATLaw **MapLaw1,
    CATLaw **MapLaw2,
    CATBody * Parallel[2],
    CATBody * Extrap[2],
    CATCGMJournalList *Rep,
    CATLONG32 WT[2]) = 0;
  /** @nodoc */
  virtual int GetExtrapInfo() = 0;
  /** @nodoc */
  virtual CATLONG32 GetConnexionInfo() = 0;
  /** @nodoc */
  virtual void DeleteOverlap(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iBodyPtImage,
    CATBody *&iCurvePar,
    CATVertex *iVxParallelExtremity) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapParCornerTool(); // -> delete can't be called
};
/**
* Creates a CATIPGMExtrapParCornerTool object. This object defines the
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
ExportedByCATGMOperatorsInterfaces CATIPGMExtrapParCornerTool *CATPGMCreateExtrapParCornerTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATICGMDistanceTool *iDist,
  CATBody *iShFond);

#endif /* CATIPGMExtrapParCornerTool_h_ */
