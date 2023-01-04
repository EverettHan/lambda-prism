#ifndef CATIPGMTopBlendInt_h_
#define CATIPGMTopBlendInt_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopBlend.h"

class CATIPGMFrFTopologicalSweep;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopBlendInt;

/*  
=============================================================================

  RESPONSABLE  : J. Saloux
  
  DESCRIPTION  : Wire-Wire Blend Operator Implemetation

=============================================================================
Dec. 03 : Interface interne : Permet de tester les nouveaute sur un niveau inf
Dec  05 : AjoutSetDevelopOptions
=============================================================================
 Implementation du code dans CATTopBlendCx2 (3 lignes )
=============================================================================
*/
// Mode suplementaire de coupling
// Reste a -1 tanqu'il reste caché
// CATTopBlendCouplingMode 
class ExportedByCATGMOperatorsInterfaces CATIPGMTopBlendInt: public CATIPGMTopBlend
{
public:
  /**
   * Constructor
   */
  CATIPGMTopBlendInt();

  virtual void SetSpine(CATGeometry *iSpine) = 0;

  virtual CATBoolean SetActivateTolerantBlend(CATBoolean iActivate = TRUE) = 0;

  virtual void SetRadiusLaw(CATLaw *iRadiusLaw) = 0;

  virtual void SetDevelopOptions(
    double Develop_Clearance,
    CATLONG32 Develop_CutCone) = 0;

  virtual void GetMaxGaussianCurvature(
    double &MaxGaussianCurvature,
    CATMathPoint &MaxPosition) = 0;

  virtual void SetAligneClosure(CATLONG32 iAligneClosure) = 0;

  /**
 * Sets the plane detection mode.
 * @param iPlanesDetection
 * The plane detection mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for replacing planar surfaces by planes,
 * <tt>FALSE</tt> otherwise (default mode at the operator creation).
 */
  virtual void SetPlanesDetection(CATBoolean iPlanesDetection = CATBoolean(1)) = 0;

  /**
 * Sets the canonic surfaces detection mode (cones/cylinders/planes).
 * @param iCanonicSurfacesDetection
 * The canonic surface detection mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for replacing nurbs surfaces by canonic surfaces,
 * <tt>FALSE</tt> otherwise (default mode at the operator creation).
 */
  virtual void SetCanonicSurfacesDetection(
    CATBoolean iCanonicSurfacesDetection = CATBoolean(1)) = 0;

  // ??? interessant mais ne construit pas l'operateur Sweep (que cela permettrait de parametrer sous la ceinture)
  //     et se contente de rendre son pointeur, inutilisable donc avant le Run.
  //     but initial de cette methode jamais appelee?  NLD260416
  /**
   * @return [out, IUnknown#Release]
   */
  virtual CATIPGMFrFTopologicalSweep *GetTopologicalSweep() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopBlendInt(); // -> delete can't be called
};

#endif /* CATIPGMTopBlendInt_h_ */
