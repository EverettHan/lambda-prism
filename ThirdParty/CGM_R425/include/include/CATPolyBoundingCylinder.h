//=============================================================================
// COPYRIGHT Dassault Systemes 2011
//=============================================================================
// CATPolyBoundingCylinder.h
//
//=============================================================================
// 2011-02-01   JXO: New
//=============================================================================
#ifndef CATPolyBoundingCylinder_H
#define CATPolyBoundingCylinder_H

#include "PolyMathBV.h"
#include "CATPolyBoundingVolume.h"
#include "CATPolyPool.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathDirection.h"
#include "CATDataType.h"

/**
 * This class represents a cylinder as a bounding volume.
 * If the iLimit is negative, then the cylinder is infinite in both directions.
 * If the iLimit is positive, then the cylinder's length is 2*iLimit (iLimit in both directions from the center). It is capped with half spheres at both ends.
 */

class ExportedByPolyMathBV CATPolyBoundingCylinder
  : public CATPolyBoundingVolume
{
  CATPolyDeclarePooledNew;

public:
 /**
  * Constructor. This class represents a cylinder as a bounding volume.
  * If the iLimit is negative, then the cylinder is infinite in both directions.
  * If the iLimit is positive, then the cylinder's length is 2*iLimit (iLimit in both directions from the center). It is capped with half spheres at both ends.
  */
  CATPolyBoundingCylinder(const CATMathPoint &iCenter, const CATMathVector &iDir, double iRadius, double iLimit = -1.0) :
   _Center(iCenter),
   _Dir(iDir),
   _Radius(iRadius),
   _Limit(iLimit)  
   {}

 /**
  * Default constructor. This class represents a cylinder as a bounding volume.
  * Limit is negative, the cylinder is infinite in both directions.
  */
  CATPolyBoundingCylinder() {_Radius = 0.; _Limit = -1.;}

  virtual ~CATPolyBoundingCylinder () {}

  TypeID GetTypeID() const; 
  
public:
  inline const CATMathPoint &GetCenter() const { return _Center; }
  inline const CATMathVector &GetDirection() const { return _Dir; }
  inline double GetHalfHeight () const {return _Limit;}
  inline double GetRadius() const { return _Radius; }
  inline double GetLimit() const { return _Limit; }
  inline CATBoolean IsInfinite() const { return (_Limit < 0.0 ? TRUE : FALSE); }

  inline void Set (const CATMathPoint & iCenter, const CATMathVector &iDir, double iRadius, double iLimit = -1.0)
  {
    _Center = iCenter;
    _Dir = iDir;
    _Radius = iRadius;
    if(iLimit >= 0.)
      _Limit = iLimit;
  }

public:

  HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const;

  virtual CATBoolean IsEmpty() const;

protected:
  CATMathPoint _Center;   // Origin of the cylinder, a point on the axis
  CATMathDirection _Dir; // direction of the axis
  double _Radius;       // radius of the cylinder
  double _Limit;       // limit of the volume of the cylinder around the origin (_Center +/- _Limit*_Dir)
                      // Negative value if no limit (infinite cylinder)
};


#endif // !CATPolyBoundingCylinder_H
