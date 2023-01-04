#ifndef CATSubdivGridSurface_h
#define CATSubdivGridSurface_h

//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// 28/10/2008 : RNO : Ajout GetKnots and GetMaxDegree
// 24/10/2008 : RNO : Creation 
//=============================================================================
#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"

#if defined CATIAV5R19 || defined CATIAR206

#include "CATSurface.h"
#include "CATMathDef.h"
class CATSubdivMesh;
class CATSubdivMeshGeo;
class CATSobFace;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSubdivGridSurface ;
#else
extern "C" const IID IID_CATSubdivGridSurface ;
#endif

/*
Class that Define a piece of a Subdivision Surface
No Doc
*/
class CATSapSubdivGridSurface;
class CATMathNurbsBipar;
class CATSoftwareConfiguration;
class ExportedByCATGMGeometricInterfaces CATSubdivGridSurface : public CATSurface
{
  CATDeclareInterface;

public :
  
  //-------------------------------------------------------------------------
  // Methods of the CATSubdivGridSurface Interface
  //-------------------------------------------------------------------------
  virtual void GetSubdivMeshGeo(const CATSubdivMeshGeo*& oSubdivMeshGeo) const = 0;

  //Get Grid Data Such as oTabofSobFaces[iv*NU+iu], 0<=iu<NU, 0<=iv<NV
  // The pointer should be deleted [] by the caller.. 
  virtual void GetGrid(int & oNU, int & oNV, CATSobFace ** & oTabofSobFaces) const = 0;

  //Get Grid Data Such as oTabofSobFaces[iv*NU+iu], 0<=iu<NU, 0<=iv<NV
  // Orientations from 0 to 3 count the number of rotation needed 
  // to align the local frame of the SobFace to the Global frame of the Grid
  // The pointers should be deleted [] by the caller.. 
  virtual void GetGrid(int & oNU, int & oNV, CATSobFace ** & oTabofSobFaces, char *& oOrientations) const = 0;

  //Get Knots in U : This Knots also split the Grid into the SobFaces 
  virtual const double * GetKnotsU(short & oNumberOfKnots) const = 0;
  //Get Knots in V 
  virtual const double * GetKnotsV(short & oNumberOfKnots) const = 0;
  // Get the MaxDegree contained in the equation that evaluate ths surface
  // All Equations do not have the same degree (some are of degree 3 and some of degree 6)
  virtual short GetMaxDegree() const =0 ;
 
  // Get the extrapolated offset in each direction 
  // Each value is the number of arc/span of offset
  // return True if the surface is extrapolated
  virtual CATBoolean GetExtrapolOffsets(int & OffsetUmin, int & OffsetUmax, int & OffsetVMin, int &OffsetVMax) const =0;

  //No Doc : Never Publish In PublicInterface !!!!!
   // iSides : 0 : FullGrid, 1 =Vmin, 2=Umax, 4=Vmax, 8=Umin, 15= AllSides,
  virtual void GetInternalData(CATSoftwareConfiguration * iSoftConfig,int iSides, int & oNU, int & oNV, CATMathNurbsBipar ** & oBiPar, char *& oOrientations) =0;
  //Call This when Extrapol has been (update internal data and linked elements)
  virtual void UpdateExtrapol(CATSoftwareConfiguration * iSoftConfig,int iOffsetUmin, int iOffsetUmax, int iOffsetVMin, int iOffsetVMax, CATMathNurbsBipar ** BiPar, char * Orientations)=0;
};
  CATDeclareHandler(CATSubdivGridSurface,CATSurface);

#endif  //R19 ou R206

#endif
