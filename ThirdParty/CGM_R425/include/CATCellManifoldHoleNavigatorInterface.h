// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2014
// ................................
//
// ----------------------------------------------------------------------------------------------//


#ifndef CATCellManifoldHoleNavigatorInterface_H
#define CATCellManifoldHoleNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldExtrusionNavigatorInterface.h"

#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"
#include "ListVOfCATFeaturePiece.h"
#include "CATIAV5Level.h"

class CATCellManifold;
class CATMathLine;

// Note: this class has to remain an interface class
// do not introduce any data members in this class

class ExportedByCATGMModelInterfaces CATCellManifoldHoleNavigatorInterface : public CATCellManifoldExtrusionNavigatorInterface
{
public:
  typedef enum 
  {
    UnknownClogType   = 0,
    Clogless          = 1,
    Flat              = 2, 
    Conical           = 3,
    Spherical         = 4
  }
  CATHoleClogType;

  typedef enum 
  {
    UnknownFit          = 0,
    FitWithinTolerance  = 1,
    LooseFit            = 2,
    NoFit               = 3
  }
  CATHolePadFitType;


  // Constructor
  CATCellManifoldHoleNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldHoleNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATCellManifoldHoleNavigatorInterface* GetAsHoleNavigatorInterface();

  // queries specific to Hole navigators
  virtual HRESULT GetClogType(CATHoleClogType &oClogType, CATAngle &oAngle) const=0;

  //NOTE: do not use GetExtrusionDirection to get the hole axis/direction. Use this method instead
	/**
	* Returns the axis of this hole feature, encapsulated as a <tt>CATMathLine</tt>  
	* object. 
	* <br><b>Role</b>: The origin of the axis is a projection from the 
	* point on the hole entrance furthest away from the end of the hole.
	* Its direction is a unit vector oriented from the support to the end
	* of the hole.
	* @param oAxis
	* The axis.
	* @param oIsAmbiguous
	* TRUE if the orientation of the hole is ambiguous; FALSE if otherwise, in which case the orienation is provided by oAxis.
	**/
	virtual HRESULT GetHoleAxis(CATMathLine &oAxis, CATBoolean & oIsAmbiguous) const=0;

  // Simple Hole
  virtual HRESULT GetSimpleHoleParameters(double & oDiameter, double & oDepth) const=0;
  virtual HRESULT GetSimpleHoleParameters(double & oDiameter) const=0;

  //Tapered Hole RL1
  virtual HRESULT GetTaperedHoleParameters(double & oDiameter,
    double & oDepth,
    CATAngle & oTaperedAngle) const=0;
  virtual HRESULT GetTaperedHoleParameters(double & oDiameter,
    double & oTaperedAngle) const=0;

  // Countersunk Hole
  virtual HRESULT GetCountersunkHoleParameters( double & oPrimaryDiameter, 
                                                double & oDepth, 
                                                double & oCountersinkDepth, 
                                                CATAngle & oCountersinkAngle) const=0;
  virtual HRESULT GetCountersunkHoleParameters( double & oPrimaryDiameter, 
                                                CATAngle & oCountersinkAngle) const=0;
  
  // Counterbored Hole
  virtual HRESULT GetCounterboredHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterboreDiameter, 
                                                double & oDepth, 
                                                double & oCounterboreDepth) const=0;
  virtual HRESULT GetCounterboredHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterboreDiameter) const=0;
  
  // Counterdrilled Hole
  virtual HRESULT GetCounterdrilledHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterdrillDiameter, 
                                                double & oDepth, 
                                                double & oCounterdrillDepth,
                                                CATAngle & oCounterdrillAngle) const=0;
  virtual HRESULT GetCounterdrilledHoleParameters(double & oPrimaryDiameter, 
                                                double & oCounterdrillDiameter, 
                                                CATAngle & oCounterdrillAngle) const=0;



  virtual HRESULT GetHoleSignature( CATLISTV(CATFeaturePiece) & oHolePieces) const=0;

  virtual HRESULT GetMinDiameter(double & oMinDiameter) const=0;
  virtual HRESULT GetMaxDiameter(double & oMaxDiameter) const=0;

  // i49 - Do not use in any new evolutions (Use GetTransitionFaces instead)
  virtual HRESULT GetHoleIntermediateFaces(ListPOfCATCellManifold & oCMFaces) const=0;

  virtual HRESULT IsCompatible(CATCellManifoldPadPocketNavigatorInterface const* ipPad, CATHolePadFitType & oFitType, double iFitTolerance) const=0;


  virtual void Dump(CATCGMOutput& Output);
protected:
};


#endif
