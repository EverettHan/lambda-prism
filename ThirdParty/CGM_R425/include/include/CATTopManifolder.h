/**
 * @COPYRIGHT DASSAULT SYSTEMES 2007
 */

/* -*-C++-*- */

#ifndef __CATTopManifolder_H__
#define __CATTopManifolder_H__

// COPYRIGHT DASSAULT SYSTEMES 2007

//===========================================================================
// Operator for the manifoldisation of a body.
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopMultiResultStreamed.h"

#include "CATCGMVirtualMacros.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATExtTopManifolder;

/**
 * Class representing the topological operator which clean a non-manifold body and give back N bodies 2-manifold.
 * If the InputBody is already 2-manifold, the result is the InputBody.
 * <ul>
 * <li>Create it with the CATCreateManifolder global function.
 * <li>Run it ( only one time ).
 * <li>Get the resulting bodies with the GetResult method. 
 * If you do not want to keep this resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Delete it after use  with the usual C++ delete operator. 
 * </ul>
*/
class ExportedByCATTopologicalObjects CATTopManifolder: public CATTopMultiResultStreamed
{
  CATCGMVirtualDeclareClass(CATTopManifolder);
protected:

  /**
  * @nodoc
  * Constructor. Do not use. Use <tt>CATCreateManifolder</tt> to create a <tt>CATTopManifolder</tt>.
  */
  CATTopManifolder(CATGeoFactory       * iFactory, 
									 CATTopData          * iTopData,
                   CATExtTopManifolder * iExtensible);

public:
  /**
  * Destructor.
  */
  virtual ~CATTopManifolder();

  /**
  * Return TRUE if the InputBody is already manifold
  * Return FALSE if the InputBody is non-manifold
  */
  // CATBoolean IsInputManifold();

  // Methods to override for child classes that support CGMReplays
  virtual void  SetCGMStreamVersion(short iVersion);
  virtual short GetCGMStreamVersion() const;

  virtual void SetVolumeJournalling(int iVolumeJournalling) = 0;
  virtual int GetVolumeJournalling() = 0;

};
/**
* Creates N bodies, which are manifold, resulting of the manifoldisation of a non-manifold body..
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody
* A pointer to the body.
*/
ExportedByCATTopologicalObjects CATTopManifolder *
CATCreateTopManifolder(CATGeoFactory * iFactory, 
									  CATTopData    * iTopData,
									  CATBody       * iInputBody);

#endif
