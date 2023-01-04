#ifndef CATIPGMTopFRRFilletDetectionOpe_h_
#define CATIPGMTopFRRFilletDetectionOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "ListPOfCATBody.h"


class CATMathInterval;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopFRRFilletDetectionOpe;

/**
 * Class defining the operator that detects Fillet in a Body for Fillet Radius Reduction.
 * <br>
 * This operator follows the general scheme of the topological operators. User should:
 * <ul>
 *<li> Create the operator with the <tt>CATPGMCreateTopFRRFilletDetectionOpe</tt>
 * global function, which defines the shell to treat.
 *<li> Run the operator with the <tt>Run</tt> method. In case of any failing treatment, the <tt>Run</tt>
 * method returns an integer error status different from 0:
 *

 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRFilletDetectionOpe: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopFRRFilletDetectionOpe();

  /** 
  * Set Intervals of available radius
  *
  * <br><b>/If a Face is Recongnized as a Fillet an have a Fillet Radius R that is in the interval i
  * Than the Face will be Append in the returned Array of List of Face [i];
  * If no interval are specified than the array contains all Face Fillet and have only one element [0]</b>
  *
  * @param iNbInterval [in]
  *   The Number Of Intervals...
  * @param iArrayOfInterval [in]
  *   The Array of intervals...
  *
  */
  virtual void SetIntervals(
    int iNbInterval,
    const CATMathInterval *iArrayOfInterval) = 0;

  /** 
  * Get The found fillet as a list of face
  *
  * @param oNbInterval [out]
  *   The Dimension of the returned array...
  *
  * @return
  *   array (same dimension of the Input Intervals) of List of cell (CATFace s)that are considered as Fillets
  *
  */
  virtual CATLISTP(CATCell) *GetFilletFaces(int &oNbInterval) = 0;

  /** 
  * Get The found fillet as MULTI-DOMAIN bodies
  *
  *
  * @param iSeparation [in] [!!!Experimental!!!!]
  * If TRUE divide the resulting search fillet into two parts (fillets in curvature opposition)
  * IF FALSE (Normal Behavior) 
  * @param oNbInterval [out]
  *   The parameter role...
  *
  * @return
  *   an array  of Size oNbInterval of a List of Bodies (1 Body in List if iSeparation=FALSE)
  * !!!! Each Body can have several Domains
  * (contiguous Fillets are automatically federated in one Domain)
  *
  */
  virtual CATLISTP(CATBody) *GetBodies(
    CATBoolean iSeparation,
    int &oNbInterval) = 0;

  /**
  * Force the operator to compute a Radius (and Detection) even if the surface (Fillet,Cylinder) can give the exact radius
  */
  virtual void SetNoUseOfNativeSurfaceType() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopFRRFilletDetectionOpe(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRFilletDetectionOpe *CATPGMCreateTopFilletDetectionOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody);

#endif /* CATIPGMTopFRRFilletDetectionOpe_h_ */
