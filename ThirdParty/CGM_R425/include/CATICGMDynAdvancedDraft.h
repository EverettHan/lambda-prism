#ifndef CATICGMDynAdvancedDraft_h_
#define CATICGMDynAdvancedDraft_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynDraft.h"

class CATAutomaticDraftContext;
class CATBody;
class CATDynSolidDraftCGM;
class CATGeoFactory;
class CATPlane;
class CATPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynAdvancedDraft;

/**
* Class defining an operator to draft faces of a 3D body.
* This operator offers more capabilities than <tt>CATICGMDynDraft</tt> and 
* might be able generate a result in cases where <tt>CATICGMDynDraft</tt> could fail.
* <br>
* <br>
* The <tt>CATICGMDynAdvancedDraft</tt> operator follows the global frame of the topological
* operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A <tt>CATICGMDynAdvancedDraft</tt> operator is created with the <tt>CATCGMCreateDynAdvancedDraft</tt> global method:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>Options can be precised (such as the untwist mode) with the appropriate methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedDraft: public CATICGMDynDraft
{
public:
  /**
   * Constructor
   */
  CATICGMDynAdvancedDraft();

  /**
   * Defines how twisted topology is handled.
   * <br>By default, the automatic untwisting of topology is turned off.  When activated, the twisting is repaired.
   * @param iAutoUntwistMode
   * If <tt>iAutoUntwistMode</tt> is TRUE, untwisting is activated.
   */
  virtual void SetAutomaticUntwistMode(CATBoolean iAutoUntwistMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynAdvancedDraft(); // -> delete can't be called
};

/**
 * Creates a <tt>CATICGMDynDraft</tt> operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iPart
 * The pointer to the body to draft.
 * @param iType
 * The type of the draft operation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedDraft *CATCGMCreateDynAdvancedDraft(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart,
  const CATDynDraftType iType);

#endif /* CATICGMDynAdvancedDraft_h_ */
