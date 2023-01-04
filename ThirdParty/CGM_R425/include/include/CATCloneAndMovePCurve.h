/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATCloneAndMovePCurve :
// Create a new PCurve on a given surface from an existing PCurve lying on a different
// surface.
// If the limits of the new surface are big enough, a clone operation is performed;
// otherwise a conversion, exact or approximate, is performed to obtain a valid
// PCurve. 
//=============================================================================
//=============================================================================
// May 03  Creation                          AAD
//=============================================================================
#ifndef CATCloneAndMovePCurve_H 
#define CATCloneAndMovePCurve_H 

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATCreateCloneAndMovePCurve.h"  //EAB - 27/11/03

class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvLimits;
class CATSurLimits;
class CATSurface;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATGeoFactory;
class CATMathSystemXY;

class ExportedByCATGMModelInterfaces CATCloneAndMovePCurve
{
public :
virtual ~CATCloneAndMovePCurve();

/**
 *@nodoc
 *iTransfo2D defines the correspondance between the UV space of the two surfaces:
 *for all parameters t, NewPCurve(t) = iTransfo2D(OldPCurve(t))
 */
virtual void SetTransformation(const CATMathTransformation2D & iTransfo2D) = 0;

/**
 *@nodoc
 *iNonLinearTransfo2D defines the correspondance between the UV space of the two surfaces:
 *for all parameters t, NewPCurve(t) = iNonLinearTransfo2D(OldPCurve(t))
 */
virtual void SetTransformation(const CATMathSystemXY * iNonLinearTransfo2D) = 0;

/**
 *@nodoc
 *By default the tolerance given in the constructor is specified in 2D.
 *If this method is called, it is specified in 3D.
 */
virtual void SetDeviationComputationIn3D() = 0;

/**
 *@nodoc
 *By default the operator always create a new PCurve: by cloning if possible, or else by approximation.
 *If this method is called, and cloning is possible, no result is created.
 */
virtual void SetNoActionIfClone() = 0;

/**
 *@nodoc
 *By default the input PCurve is assumed to lie within the max limits of its support (ie it is assumed to be valid). 
 *If this assumption is wrong, it can lead to inconsistencies.
 *
 *If this method is called, the input PCurve is not assumed to lie within the max limits of its support.
 */
virtual void SetAllowInputPCurveTooLarge() = 0;

/**
 *@nodoc
 *By default the new PCurve will have the same parameterisation as the old one.
 *If this method is called, the parameterisation can be different.
 *The mapping between the parameterisation can be retrieved with GetTransfo1D
 */
virtual void SetAllowDifferentParameterisation() = 0;

/**
 *@nodoc
 *@param iMaxUVBox
 *If this option is called, the limits taken into account on iNewSupport will not be its MaxLimits, but
 *will be iMaxUVBox.
 */
virtual void SetMaxUVBox(const CATSurLimits & iMaxUVBox) = 0;

/**
 *@nodoc
 */
virtual int Run() = 0;

/**
 *@nodoc
 *Return 0 if the new PCurve has been created by approximation.
 *Return 1 if:
 *--either the new PCurve has been created by cloning;
 *--or cloning was possible, but no PCurve was created because the method SetNoActionIfClone was called.
 */
virtual CATBoolean IsCloned() = 0;

/**
 *@nodoc
 */
virtual CATPCurve * GetResult() = 0;

/**
 *@nodoc
 *Return the mapping between the parameterisation of the new and old PCurve:
 *for all parameters t, NewPCurve(oTransfo1D(t)) = OldPCurve(t)
 *Remark: if SetAllowDifferentParameterisation was not called, oTransfo1D is always the identity.
 */
virtual CATBoolean GetTransfo1D(CATMathTransformation1D & oTransfo1D) = 0;

protected:
CATCloneAndMovePCurve();

private:
CATCloneAndMovePCurve(const CATCloneAndMovePCurve &);
void operator = (const CATCloneAndMovePCurve &);

};

#endif


