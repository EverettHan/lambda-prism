#ifndef CATIPGMTopSpine_h_
#define CATIPGMTopSpine_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopSpineRelimitation_Type.h"

class CATBody;
class CATGeoFactory;
class CATGeometry;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSpine;

/**
 * Class representing the topological operator that creates a spine. 
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateTopSpine</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting spine by using the GetResult method. If you do not want 
 * to keep this resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSpine: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSpine();

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

  /** 
 * @nodoc
 * Set a specific mode for extrapol operator
 */
    virtual void                  SetSpineForExtrapol      ()                                                              = 0;

  /** 
 * @nodoc
 * Set orientation of first profile.
 * This option is valid only for Planes. 
 * @param iFirstNormalOrn
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt></dt><dd> Orientation is normal to the plane. 
 * <dt><tt>-1</tt></dt><dd> Orientation is the opposite direction of the normal to the plane. 
 * <dt><tt>0</tt></dt><dd> Unset option (default value for operator).
 * </dl>
 */
    virtual void                  SetFirstPlaneNormalOrn   (const CATLONG32                     iFistNormalOrn           ) = 0;

  /** 
 * @nodoc
 * r19sp5 !
 * Set continuity type for each profile.
 * @param iContProfileTarget
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt></dt><dd> To set option. 
 * <dt><tt>0</tt></dt><dd> To unset option.
 * </dl>
 * @param IContinuity
 * The array of continuity values.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt></dt><dd> G0 continuity. 
 * <dt><tt>2</tt></dt><dd> G1 continuity.
 * </dl>
 */
  virtual void                    SetTargetContinuity      (      CATLONG32                     iContProfileTarget       ,
                                                            const CATListOfInt                & IContinuity              ) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSpine(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopSpine operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to topological data for operator configuration.
 * @param iProfiles
 * The list of pointers to profiles (CATBody) or planes (CATPlane).
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSpine *CATPGMCreateTopSpine(
                                                                  CATGeoFactory              *  iGeoFactory              ,
                                                                  CATTopData                 *  iTopData                 ,
                                                                  CATLISTP(CATGeometry)       & iProfiles                ) ;

#endif /* CATIPGMTopSpine_h_ */
