/* -*-c++-*- */
#ifndef CATCGA_SizeOfAdvMaths_H
#define CATCGA_SizeOfAdvMaths_H
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//============================================================================
#include "YN000DEV.h"                  // For Windows

class ExportedByYN000DEV CATCGA_SizeOfAdvMaths
{
public:
   CATCGA_SizeOfAdvMaths();
   virtual ~CATCGA_SizeOfAdvMaths();
   void GetSizes(); 

   virtual void GetSizeOf(const char *classname, const int bytes) =0;

};

#endif
