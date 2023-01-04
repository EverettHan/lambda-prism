#ifndef CATICGMTopSpine_h_
#define CATICGMTopSpine_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATTopSpineRelimitation_Type.h"
#include "CATCollec.h"

class CATBody;
class CATGeoFactory;
class CATGeometry;
class CATTopData;
class CATLISTP(CATGeometry);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSpine;

/**
 * Class representing the topological operator that creates a spine. 
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateTopSpine</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting spine by using the GetResult method. If you do not want 
 * to keep this resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopSpine: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopSpine();

  /**
 * Defines the guides to refine the definition of the spine.
 * @param iGuides
 * The list of pointers to the wire bodies defining the guides.
 */
  virtual void                   SetGuides                 (       CATLISTP(CATGeometry)      & iGuides                  ) = 0 ;

  /**
 * Defines the relimitation mode for spine computation.
 * @param iMode
 * The relimitation mode.
 */
  virtual void                   SetRelimitationMode       (       CATTopSpineRelimitation_Type iMode                    ) = 0 ;

  /**
 * Sets the continuity constraints on a profile.
 * @param iRankProfile
 * The rank (beginning at 1) of the profile to constraint.
 * @param iReferenceElement
 * The pointer to the reference element (CATPlane or skin CATBody) on which the profile
 * must lay. The sweep is tangent to a skin CATBody reference element and normal to 
 * a CATPlane reference element.
 */
  virtual void                    SetProfileContinuityCondition
                                                           (       int                          iProfileRank             ,
                                                                   CATGeometry               *  iReferenceElement        ) = 0 ;

  /** 
 * Defines an imposed point of the spine.
 * <br> Only one imposed point must be defined.
 * @param iProfileRank
 * The rank (beginning at 1) of the profile to constraint.
 * @param iImposedPoint
 * The pointer to the imposed CATPoint or point body.
 */
    virtual void                  ImposePointOnProfile     (       int                          iProfileRank             ,
                                                                   CATGeometry               *  iImposedPoint            ) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSpine(); // -> delete can't be called
};

/**
 * Creates a CATICGMTopSpine operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to topological data for operator configuration.
 * @param iProfiles
 * The list of pointers to profiles (CATBody) or planes (CATPlane).
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSpine *CATCGMCreateTopSpine(
                                                                  CATGeoFactory              *  iGeoFactory              ,
                                                                  CATTopData                 *  iTopData                 ,
                                                                  CATLISTP(CATGeometry)       & iProfiles                ) ;

#endif /* CATICGMTopSpine_h_ */
