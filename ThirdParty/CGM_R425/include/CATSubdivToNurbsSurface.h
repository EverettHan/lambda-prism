/*-*-c++-*-*/
//===============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved 
//===============================================================================
//
// CATExtrapolSubdivSurface :
// Class for converting a SubdivSurface (CATSubdivCellSurface or CATSubdivGridSurface) into
// a NurbsSurface : since the conversion is as exact as possible there is no tolerance
// Run it by the usual Run() methods before getting result
//
//=============================================================================
// Usage notes:
//
// 
//=============================================================================
// History :
// 27/05/2009 : RNO : Creation
//
#ifndef CATSubdivToNurbsSurface_H 
#define CATSubdivToNurbsSurface_H 

#include "CATGeoOperator.h"
#include "CATCGMOperatorDebug.h"
#include "Y30C3XGG.h"


#include "CATCGMVirtual.h"

class CATSurface;
class CATKnotVector;

class CATGeoFactory;
class CATMathSetOfPoints;
class CATMathVector2D;
class CATSurParam;
class CATMathNurbsBipar;
class CATSoftwareConfiguration;
class CATNurbsSurface;



class ExportedByY30C3XGG CATSubdivToNurbsSurface   : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATSubdivToNurbsSurface);
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  //CTOR with SubdivCell or Grid
  CATSubdivToNurbsSurface (CATGeoFactory * iFactory,
                            CATSoftwareConfiguration * iConfig,
                              CATSurface * ioSur);


  virtual ~CATSubdivToNurbsSurface();

  

  //Get the Equivalent Bipar (when called delete the bipar)
  virtual CATMathNurbsBipar * GetBipar()  =0;
  //Create the Nurbs Surface
  virtual CATNurbsSurface * GetNurbsSurface()  =0;

  //Get Original equation Size
  virtual void GetEquationSize(int & oNU, int &oNV) const=0;

  //Set it To TRUE if the original parametrization is needed (ie exach patch from 0. to 4.)
  // Default is equivalent to FALSE
  virtual void SetKeepNaturalParameter(CATBoolean iKeep) =0;


};


ExportedByY30C3XGG
CATSubdivToNurbsSurface * CATCreateSubdivToNurbsSurface  (CATGeoFactory * iFactory,
                            CATSoftwareConfiguration * iConfig,
                              CATSurface * ioSur);


#endif
