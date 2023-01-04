/* -*-c++-*- */
#ifndef CATCGA_SizeOfGeometry_H
#define CATCGA_SizeOfGeometry_H
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//============================================================================
// July,  2004 : RAQ : Ajout GetSizesSubdivision
//============================================================================
#include "CATIACGMLevel.h"
#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATIAV5Level.h"

class ExportedByCATGeometricObjectsCGM CATCGA_SizeOfGeometry
{
public:
   CATCGA_SizeOfGeometry();
   virtual ~CATCGA_SizeOfGeometry();
   void GetSizes(); 

   virtual void GetSizeOf(const char *classname, const int bytes) =0;

private:
  void GetSizesPoint(); 
  void GetSizesCurve(); 
  void GetSizesSurface(); 
  void GetSizesLaw(); 
  void GetSizesCGMGeoTopo();
};

#endif
