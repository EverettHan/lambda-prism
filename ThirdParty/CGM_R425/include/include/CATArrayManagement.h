// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATArrayManagement.h
// header for internal class of GeometricOperators framework
//
//=============================================================================
// Usage Notes:
// Only for array of integer for the moment
// For easily managed allocated array size and avoid allocation of little array
// Internal use only
//=============================================================================
// Mar. 97   Creation                                   N.Barrier
// Juin 2004 Versionning Interne EAB
//=============================================================================

#ifndef CATARRAYMANAGEMENT_H
#define CATARRAYMANAGEMENT_H
#include "Y30UIUTI.h"
#include "CATIntersectionOrientation.h"
class CATSoftwareConfiguration;

class CATCrvParam;

class CATArrayManagement
{
   int _Size;
   CATSoftwareConfiguration * _Config;

public:
   CATArrayManagement (CATSoftwareConfiguration * iConfig, int InitialSize ); 
   ~CATArrayManagement (); 
                                /* for integers array management */
   void Increase ( int *&Adress, int &Size, int copy=1 );   
                                /* for double array management */
   void Increase ( double *&Adress, int &Size, int copy=1 );   
                                /* for Intersection Orientation array */
   void Increase ( CATIntersectionOrientation *&Adress, int &Size,
                                                               int copy=1 );   
                                /* for any pointers array management */
   void Increase ( void **&Adress, int &Size, int copy=1 );
   int GetSize();
// DG Delete de pointeur void interdit sous hp1020
//   void Delete( void *Adress, int &Size);
};
#endif
