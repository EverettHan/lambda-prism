#ifndef CATIPGMTopDevelop_h_
#define CATIPGMTopDevelop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATICGMSurTo2DGlobalMapping;
class CATIPGMSurTo2DGlobalMapping;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopDevelop;

/**
 * Class defining the operator that maps a wire on a shell onto another shell.
 *<ul>
 *<li>The CATIPGMTopDevelop operator is created with the <tt>CATPGMCreateTopDevelop</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>Options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopDevelop: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopDevelop();

  /**
 * Proposes a face of the target body on which the computed wire might pass. 
 * @param iInitialFace
 * The pointer to the face.
 */
  virtual void SetTargetInitialFace(CATFace *iInitialFace) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopDevelop(); // -> delete can't be called
};

/** 
* Creates an operator that maps a wire on a shell onto a wire on another shell.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iWire
* The pointer to the wire body to map. 
* The body only contains one wire, that must be lying on <tt>iWireSupport</tt>..
* @param iWireSupport
* The pointer to the shell body, that only contains one shell on which <tt>iWire</tt> is lying on.
* @param iTargetSupport
* The pointer to the shell body, that only contains one shell on which <tt>iWire</tt> must be mapped.
* @param iMappingIn
* The mapping from <tt>iWireSupport</tt> onto the 2D space. To create with the <tt>CreateXxxMapping</tt>
* global functions and to be released with the <tt>Release</tt> method after use.
* @param iMappingOut
* The mapping from the 2D space onto <tt>iTargetSupport</tt>. To create with the <tt>CreateXxxMapping</tt>
* global functions and to be released with the <tt>Release</tt> method after use.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopDevelop *CATPGMCreateTopDevelop(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iWire,
  CATBody *iWireSupport,
  CATBody *iTargetSupport,
  CATICGMSurTo2DGlobalMapping *iMappingIn,
  CATICGMSurTo2DGlobalMapping *iMappingOut);

#endif /* CATIPGMTopDevelop_h_ */
