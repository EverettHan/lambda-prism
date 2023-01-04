/* -*-c++-*- */
#ifndef CATCGA_SizeOfGeoOperators_H
#define CATCGA_SizeOfGeoOperators_H
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//============================================================================
#include "Y30UIUTI.h"                  // For Windows

class  ExportedByY30UIUTI  CATCGA_SizeOfGeoOperators
{
public:
   CATCGA_SizeOfGeoOperators();
   virtual ~CATCGA_SizeOfGeoOperators();
   void GetSizes(); 

   virtual void GetSizeOf(const char *classname, const int bytes) =0;

};

#endif
