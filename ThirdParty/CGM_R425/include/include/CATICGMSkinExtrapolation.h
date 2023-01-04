#ifndef CATICGMSkinExtrapolation_h_
#define CATICGMSkinExtrapolation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSkinExtrapolation;

/**  
* Class defining the topological operator that extrapolates a 
* surface in tangency. 
* The parameters to be specified are:
* <ul>
* <li>an extrapolation length. 
* <li>the type of extrapolation: the faces that are created to extend the surface body
*   are added smoothly. See diagram below:
* </ul>
* <pre>
*
*                             |--------|              /--\
*                             |        |             /    \
*                             |        |            /      \
*       /--------\            /--------\           /--------\
*      /          \          /          \         /          \
*     /            \        /            \       /            \
*        . . . .               . . . .               . . . .
*
*        body to               normal mode         tangent mode
*       extrapolate
*
*</pre> 
* <ul>
* <li>A CATICGMSkinExtrapolation operator is created with the
* <tt>CATCGMCreateSkinExtrapolation</tt> global method.
* It must be directly released with the <tt>Release</tt> method after use. It is is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
* <li>The resulting body is retrieved with the <tt>GetResult</tt> method.
*</ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMSkinExtrapolation: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMSkinExtrapolation();

  /**
* Specifies the type of extrapolation.
* @param mode
*<dl>  
*<dt><tt>1</tt></dt><dd>  The extrapolation is Tangent to extremities.   
*<dt><tt>2</tt></dt><dd>  The extrapolation is Normal to extremities.
*   This mode is the default mode.
*</dl>  
*/
 virtual void                      SetBorderMode            (     int                        mode                     = 1) = 0; 

  /**
* Specifies the extrapolation length.
*/
 virtual void                      SetLength                (     double)                                                  = 0;

  /**
* Retrieves the resulting body.
*/
 virtual CATBody                 * GetResult               ()                                                              = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSkinExtrapolation(); // -> delete can't be called
};

/**
 * Creates a CATICGMSkinExtrapolation operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data of the operation.
 * @param iSkin
 * The pointer to surface to be extrapolated.
 * @param iWireOnSkin
 * The pointer to the wire from which the skin is to be extrapolated.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSkinExtrapolation * CATCGMCreateSkinExtrapolation( CATGeoFactory     * iFactory, 
                                                                                             CATTopData        * iTopData, 
                                                                                             CATBody           * iSkin, 
                                                                                             CATBody           * iWireOnSkin ); 

#endif /* CATICGMSkinExtrapolation_h_ */
