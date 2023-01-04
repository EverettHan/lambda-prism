// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATContourPCurves.h
// header for internal class of surface surface intersection
//
//=============================================================================
// Usage Notes:
// Internal class of V5 implementation of surface surface intersection
// Internal use only
//=============================================================================
// Mar. 97   Creation                                   N.Barrier
// Juin 2004 Versionning interne                        EAB
//=============================================================================

#ifndef CATCONTOURPCURVES_H
#define CATCONTOURPCURVES_H
#include "Y30UIUTI.h"
#include "CATListOfCATPCurves.h"
#include "CATArrayManagement.h"
#include "CATIntersectionOrientation.h"
#include "CATIsoParameter.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

//Big Scale Modification : BQJ
#include "CATTolerance.h"

class CATPCurve;
class CATMathSetOfPointsNDTwoTangents;
class CATSoftwareConfiguration;

const int INITIALSIZE = 8;     /* to avoid allocation for most of cases */

class ExportedByY30UIUTI CATContourPCurves : public CATCGMVirtual
{
   int _SizeOfArrayOfSetOfPoints ;/*   CATLISTP(CATPCurve) _ListOfPCurve[2];*/
   CATMathSetOfPointsNDTwoTangents **_ArrayOfSetOfPoints;
   CATMathSetOfPointsNDTwoTangents *_InitialArray[INITIALSIZE];

   CATIntersectionOrientation *_Orientation;
   CATIntersectionOrientation _TabOrient[INITIALSIZE];
   int _SizeOrient;
  
   int _NumberOfConnex;
   int _SizeConnexIndex;        /* for allocation if _NumberOfConnex > _Size */

   CATSoftwareConfiguration * _Config;

   int *_Closed;                /* (_NumberOfConnex)                         */
   int _CloseInfo[INITIALSIZE];

   int *_FirstComponent;        /* Index of the PCurve end of a connex       */
   int _EndComponentIndex[INITIALSIZE];
                                /* PCurves are ordered from _SortIndex[i]+1  */
                                /* to _SortIndex[i+1]                        */
   double NUMTOL;               /* Temporary value waiting for serious       */
                                /*  tolerance management                     */
                                /* ie precision on converged value available */
                                /* from Mathematics Framework                */

   CATArrayManagement _ArraySize;

   int DifferenceBetween( CATMathSetOfPointsNDTwoTangents *NewSet,
                           CATIntersectionOrientation NewOrientation,
	                        		 int ComponentNumber );
   int Include( CATMathSetOfPointsNDTwoTangents *NewSet,
	                        		 int ComponentNumber );
   void Append( CATMathSetOfPointsNDTwoTangents *NewSet, int Closed );

   CATContourPCurves () ;
public:
   CATContourPCurves (const CATTolerance &iTol) ;
   CATContourPCurves ( CATSoftwareConfiguration * iConfig, double iTolerance) ;
   ~CATContourPCurves () ;
   void Reset();
   /* insert sorts the new PCurve inside components of the object */
   void Insert( CATMathSetOfPointsNDTwoTangents *NewSet );
   int IsClosed( int ComponentNumber ) const;                           
   void SetOpened( int ComponentNumber );
   int GetNumberOfConnexComponents();
   int GetComponentSize( int ComponentNumber ) const;
                 /* return an array of size CATMathSetOfPointsNDTwoTangents */
                 /* Orientations is an array of int containing -1 or 1 for  */
                 /* each set indicating the orientation of the equivalent   */
                 /* PCurve inside the contour                               */
                 /* first ComponentNumber is 0                              */
   CATMathSetOfPointsNDTwoTangents ** GetList( int iComponentNumber,
                                                  int &oNumberOfSet,
                    CATIntersectionOrientation **oOrientations = NULL ) const;
                 /* first ComponentNumber is 0 */
   int GetNumberOfPCurves();
                 /* PCurveNumber is between 0 and NumberOfPCurves-1 */ 
   CATMathSetOfPointsNDTwoTangents * GetPCurve( int PCurveNumber);
};

                 /* IsoPar and index are two array of two elements */
                 /* the returned value gives the number of isopar  */
                 /* found ( between 0 and 2 )                      */
ExportedByY30UIUTI
CATLONG32 IsAnIsopar( CATMathSetOfPointsNDTwoTangents *set,
         	  CATIsoParameter *IsoPar, int *index, int *increasing , const CATTolerance & iTol);

#endif
