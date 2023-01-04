//=========================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=========================================================================================
//
// CATGenericFilletRadius :
//   Class used to compute the minimum and maximum radius of a generic fillet surface
//   on a given UV box.
//
// Inputs :
// - A GenericFillet surface.
// - Usefull limits.
//
// Usage notes : see comments below.
//
// Exemple of use :
//
// const CATSurLimits * UVBox = MyFace->Get2DBoundingBox();
// CATSurface * MySurface     = MySurface->GetSurface();
// const CATSurface * MyRep   = MySurface->GetGeometricRep();
//
// if(MyRep->IsATypeOf(CATGenericFilletType)
// {
//   CATGenericFillet * MyFillet = (CATGenericFillet *) MyRep;
//
//   CATGenericFilletRadius GFR(MyConfig,MyFillet,*UVBox);
//
//   CATGenericFilletRadius::CATGFRDiagnosis diag;
//
//   double RadiusMax = GFR.GetRadiusMax(&diag);
//
//   if(diag==CATGenericFilletRadius::OK)
//   // ...
// }
//
//
//=========================================================================================
// October 06 Creation															                                  CQI
//=========================================================================================
#ifndef CATGenericFilletRadius_h
#define CATGenericFilletRadius_h

#include "CATGMModelInterfaces.h"

#include "CATMathFunctionX.h"
#include "CATMathDiagnostic.h"
#include "CATSoftwareConfiguration.h"
#include "CATGenericFillet.h"
#include "CATSurLimits.h"

#include "CATBoolean.h"

class ExportedByCATGMModelInterfaces CATGenericFilletRadius : public CATMathFunctionX
{
public:

  //--------------------------------------------------------------------------
	//  Constructors / Destructor
	//--------------------------------------------------------------------------
  CATGenericFilletRadius(CATSoftwareConfiguration * iConfig, CATGenericFillet * iFillet, const CATSurLimits & iLimits);
  CATGenericFilletRadius(const CATGenericFilletRadius & F);
  ~CATGenericFilletRadius();

  //--------------------------------------------------------------------------
	//  Minimum / Maximum fillet radius computation
	//--------------------------------------------------------------------------

  enum CATGFRDiagnosis {Error = -1, OK, ConstantRadius};

  // Following methods allows to obtain respectively the maximum and minimum fillet radius (ie. radius of a circular section).
  // Input  : odiag is optional, but strongly recommended. If given, odiag is filled with :
  //    - Error if an error occured (irrelevant result)
  //    - OK if the computation performed well
  //    - ConstantRadius if the radius of circular sections has been found constant
  // Output : the maximum (or minimum) radius value.
  double GetRadiusMax(CATGFRDiagnosis * odiag = NULL);
  double GetRadiusMin(CATGFRDiagnosis * odiag = NULL);

  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATMathFunctionX * Duplicate() const;

  //-----------------------------------------------------------------------------
  // Evaluators
  //-----------------------------------------------------------------------------

  // Evaluate the radius at current u global parameter.
  double Eval(const double & u) const;
 
private:

  // Internal dispatch on minimize/maximize interface.
  // type  = 0 : minimum
  // type  = 1 : maximum
  // odiag     : filled with minimizer diagnostic
  double ComputeExtremum(CATMathDiagnostic & odiag, int type);
  
  CATSoftwareConfiguration *  _Config;
  CATGenericFillet         *  _Fillet;
  CATSurLimits                _Limits;

};
#endif
