#ifndef CATSubdivCellSurface_h
#define CATSubdivCellSurface_h

//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// 24/01/2008 : RNO : Creation 
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
extern ExportedByCATGMGeometricInterfaces IID IID_CATSubdivCellSurface ;
#else
extern "C" const IID IID_CATSubdivCellSurface ;
#endif

/*
Class that Define a piece of a Subdivision Surface
No Doc
*/
class CATSapSubdivCellSurface;

class ExportedByCATGMGeometricInterfaces CATSubdivCellSurface : public CATSurface
{
  CATDeclareInterface;

public :
  
  //-------------------------------------------------------------------------
  // Methods of the CATSubdivCellSurface Interface
  //-------------------------------------------------------------------------
  virtual void GetSubdivMeshGeo(const CATSubdivMeshGeo*& oSubdivMeshGeo) const = 0;

  virtual void GetSobFace(const CATSobFace * & oSobFace, int & oDaughterFace) const = 0;

  //-------- A supprimer: rend toujours NULL
  virtual void GetMesh(const CATSubdivMesh *& oSubdivMesh) const = 0 ;

};
  CATDeclareHandler(CATSubdivCellSurface,CATSurface);

#endif  //R19 ou R206

#endif


