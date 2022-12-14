#ifndef CATNonLinearTransfoSurface_h
#define CATNonLinearTransfoSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Interface representing an NonLinearTransfo surface.
 *<br> The CATNonLinearTransfoSurface is created by the <tt>CreateNonLinearTransfoSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface. 
 *<br>A CATNonLinearTransfoSurface is the surface generated by applying a transformation to
 * each point of a reference surface.
 *<table>
 * <tr><td>CATSurface</td><td><tt> Reference </tt></td>
 *                <td> The surface to transform </td></tr>
 * <tr><td>CATMathNonLinearTransformation</td><td><tt> Transformation </tt></td>
 *                <td> The transformation applied </td></tr>
 *</table>
 */

#include "CATSurface.h"
#include "CATMathDef.h"
class CATMathNonLinearTransformation;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATNonLinearTransfoSurface ;
#else
extern "C" const IID IID_CATNonLinearTransfoSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATNonLinearTransfoSurface : public CATSurface
{
  CATDeclareInterface;

  public :
  
/**
 * Returns the transformation of a CATNonLinearTransfoSurface with regards to its 
 * reference surface. 
 */
  virtual void GetTransformation(CATMathNonLinearTransformation * &oTransformation)  const  = 0;

/**  
 * Returns a pointer to the reference surface of a CATNonLinearTransfoSurface.
 */
  virtual CATSurface * GetReference()  const  = 0;
  
/**
 * Modifies the characteristics of a CATNonLinearTransfoSurface.
 */
  virtual void Set (CATMathNonLinearTransformation & iTransformation, 
                    CATSurface                     * iReference     ) = 0;
/**
 * nodoc
 */
  virtual void SetMaxLimits(CATSurLimits & iLimits) = 0;

  
};
CATDeclareHandler(CATNonLinearTransfoSurface,CATSurface);

#endif





