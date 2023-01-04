// COPYRIGHT DASSAULT SYSTEMES 2001

#ifndef CATDesextrapolator_H
#define CATDesextrapolator_H

#include "Y30C3XGG.h"
#include "CATSkillValue.h"
#include "CATGeoOperator.h"
#include "CATMathDef.h"

class CATGeometry;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATGeoFactory;


/**
 * Class defining a geometric operator that desextrapol a CATGeometrie.
 * A CATDesextrapolator operator is created with the <tt>@href CATCreateDesextrapolator </tt> global method
 * and must be directly <tt>delete</tt>d after use.
 * It is is not streamable.
 */

class ExportedByY30C3XGG CATDesextrapolator : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATDesextrapolator);
public :
/**
 * Destructor.
 */ 
  ~CATDesextrapolator();

/**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
  //virtual int Run() =0;

/**
 * Returns the Desextrapolated CATNurbsSurface, CATNurbsCurve or CATPNurbs.
 */
  virtual CATGeometry* GetResult() = 0;


/**
 * Allow the user to give as input topological limits instead of exact geometric
 * limits. In this case, limits will be reframed on the nearest limits corresponding
 * to an extrapolation step and containing the input limits. This implie that
 * original limits of the surface will be  kept.
 */
  virtual void SetNecessaryLimitsOption() = 0;

protected:
/**
 * Constructors.
 */
  CATDesextrapolator(CATGeoFactory* iFactory);
  CATDesextrapolator(CATDesextrapolator& );
};



//-----------------------------------------------------------------------------
// Create a Curve Desextrapolator - Do not use
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATDesextrapolator* CATCreateDesextrapolator(CATGeoFactory      *iFactory,
                                             CATCurve           *iCurve,
                                             const CATCrvLimits *iCrvLimits,
                                             CATBoolean          iDuplicate = FALSE,
                                             CATSkillValue       iMode = BASIC);

//-----------------------------------------------------------------------------
// Create a Surface Desextrapolator - Do not use
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATDesextrapolator* CATCreateDesextrapolator(CATGeoFactory      *iFactory,
                                             CATSurface         *iSurface,
                                             const CATSurLimits *iSurLimits,
                                             CATBoolean          iDuplicate = FALSE,
                                             CATSkillValue       iMode = BASIC);
//-----------------------------------------------------------------------------
// Create a Curve Desextrapolator
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATDesextrapolator* CATCreateDesextrapolator(CATGeoFactory      *iFactory,
                                             CATSoftwareConfiguration * iConfig,
                                             CATCurve           *iCurve,
                                             const CATCrvLimits *iCrvLimits,
                                             CATBoolean          iDuplicate = FALSE,
                                             CATSkillValue       iMode = BASIC);

//-----------------------------------------------------------------------------
// Create a Surface Desextrapolator
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATDesextrapolator* CATCreateDesextrapolator(CATGeoFactory      *iFactory,
                                             CATSoftwareConfiguration * iConfig,
                                             CATSurface         *iSurface,
                                             const CATSurLimits *iSurLimits,
                                             CATBoolean          iDuplicate = FALSE,
                                             CATSkillValue       iMode = BASIC);
#endif

