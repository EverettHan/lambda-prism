#ifndef CATIPGMProjectionInDirectionPtSur_h_
#define CATIPGMProjectionInDirectionPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATGeoFactory;
class CATMathSetOfPoints;
class CATMathVector;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMProjectionInDirectionPtSur;

class ExportedByCATGMModelInterfaces CATIPGMProjectionInDirectionPtSur: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMProjectionInDirectionPtSur();

  virtual void SetDirection(const CATMathVector *iDir) = 0;

  virtual void SetSetOfPoints(const CATMathSetOfPoints *iSet) = 0;

  virtual void SetLimits(CATSurLimits &iSurLim) = 0;

  //-----------------------------------------------------------------------
  // Get the number of solutions for a given point, where iPointRank is the
  // index of the point in the input CATMathSetOfPoints. 
  //-----------------------------------------------------------------------
  virtual CATLONG32 GetNumberOfPoints(CATLONG32 iPointRank = 0) const = 0;

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
  virtual void GetPointOnLocalAxis(
    double *oPoint,
    CATLONG32 iPointRank = 0,
    CATLONG32 inumber = 0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMProjectionInDirectionPtSur(); // -> delete can't be called
};

#endif /* CATIPGMProjectionInDirectionPtSur_h_ */
