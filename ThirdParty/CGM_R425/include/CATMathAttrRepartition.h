// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathAttrRepartition
// Class used to define the mode of repartition of a sampled curve.
//
//=============================================================================
//
// Usage notes:
// The curve may be parametric (t->M(t)) or implicit (F(X)=0).
// The important value of this class is the Sag value. The Sag is the maximum
// distance between two consecutives points of the curve and the curve itsef.
// Small Sag will give a great number of points.
// It is possible to impose a minimum and maximum distance between points.
//
//=============================================================================


#ifndef CATMathAttrRepartition_H
#define CATMathAttrRepartition_H

#include "YN000FUN.h"
#include "CATMathAttribute.h"

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathAttrRepartition : public CATMathAttribute
{
  public:
//--------------
//  Constructors
//--------------
    CATMathAttrRepartition (); 
    CATMathAttrRepartition (const double iSag);
  // MinStep = Minimal distance minimale between the points
  // MaxStep = Maximal distance minimale between the points
    CATMathAttrRepartition (const double iSag, 
                            const double iMinStep, const double iMaxStep);
  // Orientation (For explicit discretization x = f(t)) = direction of the discretization
  // If Orientation = 1 => increasing direction
    CATMathAttrRepartition (const double iSag, 
                            const double iMinStep, const double iMaxStep, const CATLONG32 iOrientation);
  // MinStepPoint (For explicit discretization x = f(t))= Minimal distance minimale between 2
  //points 3D
    CATMathAttrRepartition (const double iSag, 
                            const double iMinStep,const double iMaxStep,const double iMinStepPoint,
			    const CATLONG32 iOrientation); 
  // Angle = tunes the allowed angle variation between two consecutive tangents
    CATMathAttrRepartition (const double iSag, 
                            const double iMinStep,const double iMaxStep,const double iMinStepPoint,
			    const double Angle, const CATLONG32 iOrientation);
  // MaxStepPoint (For explicit discretization x = f(t))= Maximal distance minimale between 2
  //points 3D
    CATMathAttrRepartition (const double iSag, const double iMinStep, const double iMaxStep,
			    const double iMinStepPoint,const double iMaxStepPoint,
			    const double Angle, const CATLONG32 iOrientation);
    // Permet de passer au cheminement un MaxStep vectoriel, ie pour chauqe coordonnees.
    CATMathAttrRepartition (const double iSag, const double iMinStep,const double * MaxStep, CATLONG32 Dim);
    // Detructor
     virtual ~CATMathAttrRepartition ();

    CATMathAttrId GetType() const;
    CATBoolean IsExclusive() const;

//  Get the Sag value (or default if no one was specified with constructor)
//  Boolean is false if default value is given
    CATBoolean GetSag (double &oSag) const;
    CATBoolean GetAngle (double &oAngle) const; 
    CATBoolean GetOrientation (CATLONG32 &oOrientation) const;
    CATBoolean GetMinMaxStep (double &oMinStep, double &oMaxStep) const;
    CATBoolean GetMinStepPoint (double &oMinStepPoint) const;
    CATBoolean GetMaxStepPoint (double &oMaxStepPoint) const;
    CATBoolean GetMinMaxStepVect (double &oMinStep,double * oMaxStepVect, CATLONG32 Dim) const ;

//  Met a jour les attributs les plus courants
    void Set (const double iSag, const double iMinStep, const double iMaxStep);

  
  private:
    CATLONG32 _Value;
    CATLONG32 _Orientation;
    double _Sag, _Angle;
    double _MinStep, _MaxStep, _MinStepPoint, _MaxStepPoint;
    double *_MaxStepVect;
};

#endif
