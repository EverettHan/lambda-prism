/* -*-c++-*- */
#ifndef CATCGA_SizeOfTopology_H
#define CATCGA_SizeOfTopology_H
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//============================================================================
#include "CXMODEL.h"                  // For Windows

class ExportedByCXMODEL CATCGA_SizeOfTopology
{
public:
   CATCGA_SizeOfTopology();
   virtual ~CATCGA_SizeOfTopology();
   void GetSizes(); 

   virtual void GetSizeOf(const char *classname, const int bytes) =0;

};

#endif
