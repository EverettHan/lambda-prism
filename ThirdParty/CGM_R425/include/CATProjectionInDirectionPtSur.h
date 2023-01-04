/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// Usage notes: Operateur d'intersections multiples droites surface.
// sample of use : pojette un SetOfPoints sur une surface dans une direction donnee.
//   Cet operateur ne retourne pas les solutions de types PLines et n'est reelement
//   optimise que pour les NurbsSurfaces non rationnelle.
//=============================================================================
#ifndef CATProjectionInDirectionPtSur_H
#define CATProjectionInDirectionPtSur_H

#include "Y30E3PMG.h"
#include "CreateProjectionInDirectionPtSur.h"
#include "CATCreateProjectionInDirectionPtSur.h"
#include "CATCGMOperator.h"
#include "CATSurLimits.h"

class CATMathSetOfPoints;
class CATMathVector;
class CATGeoFactory;

class ExportedByY30E3PMG  CATProjectionInDirectionPtSur : public CATCGMOperator
   {
   CATCGMVirtualDeclareClass(CATProjectionInDirectionPtSur);

   public:

      CATProjectionInDirectionPtSur (CATGeoFactory * factory);
      virtual    ~CATProjectionInDirectionPtSur ();

      virtual    void SetDirection(const CATMathVector  *iDir) =0;

      virtual    void SetSetOfPoints(const CATMathSetOfPoints *iSet) =0;

      virtual    void SetLimits(CATSurLimits &iSurLim) =0;

      //-----------------------------------------------------------------------
      // Get the number of solutions for a given point, where iPointRank is the
      // index of the point in the input CATMathSetOfPoints. 
      //-----------------------------------------------------------------------
      virtual    CATLONG32 GetNumberOfPoints(CATLONG32 iPointRank=0) const =0;

      //-----------------------------------------------------------------------
      // Get the solutions for a given point, where iPointRank is the index
      // of the point in the input CATMathSetOfPoints, and inumber is the 
      // solutions number : 0 <= inumber < GetNumberOfPoints(iPointRank).
      // GetPointOnLocalAxis(oPoint,iPointRank,0) return the distance min
      // solution. oPoint is a double [3], where (oPoint[0],oPoint[1]) define
      // the global parameter on the surface, and oPoint[2] represent the
      // oriented distance (oriented regards to the direction of projection)
      // from the point to the surface.
      //-----------------------------------------------------------------------
      virtual    void GetPointOnLocalAxis(double *oPoint,CATLONG32 iPointRank=0,CATLONG32 inumber=0) =0;

   };
#endif
