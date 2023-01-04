#ifndef CATMathEulerTransformation_H
#define CATMathEulerTransformation_H

// COPYRIGHT DASSAULT SYSTEMES  2010

// Get Set Euler angle on a transformation

#include "CATMathematics.h"

#include "CATMathTransformation.h"

class ExportedByCATMathematics CATMathEulerTransformation : CATMathTransformation
{
	
	
public:
	//============================================================================
	//- Constructors
	//============================================================================
	/**
	* Constructs an Identity transformation.
	* <br> <tt>Matrix= Identity</tt>, <tt>Vector = (0,0,0) </tt>
	*/ 
	CATMathEulerTransformation();
	
	/**
	* Constructs a CATMathEulerTransformation from a CATMathTransformation
	*/
	CATMathEulerTransformation(const CATMathTransformation & Transformation);
	
  // Extrinsic ZXY Euler Rotation
  // iAngle1 roatate about Z (xyz) => (x'y',z)
  // iAngle2 roatate about X (x'y',z) => (x',y",z')
  // iAngle3 roatate about Y (x',y",z') => (x",y",z")
  void GetRotation(double &iAngle1, double &iAngle2, double &iAngle3);
  
  void SetRotation(double iAngle1, double iAngle2, double iAngle3);

private:

  void ComputeAngles();

  //============================================================================
  // DATA

private:
  // Euler Angle
  double _TolAngle;
  double _AngleOX;
  double _AngleOY;
  double _AngleOZ;

};

#endif
