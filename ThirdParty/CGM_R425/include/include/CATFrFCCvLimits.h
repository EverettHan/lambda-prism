// COPYRIGHT DASSAULT SYSTEMES 1998 
//==========================================================================
//
// CATFrFCCvLimits:
// Class representing the limitations of a CATFrFCompositeCurve. It contains 
// two CATFrFCCvParams, a singularity flag (CATLONG32), a resolution (double) and a 
// pointer on a CATFrFCompositeCurve. The order of the CATFrFCCvParams is 
// important, the StartLimit has the index 0 and the EndLimit has the index 1.
// If the StartLimit is greater than the EndLimit, the Closure of the pointed 
// CATFrFCompositeCurve has to be 1 (CCv closed) otherwise an error is 
// generated. This may happen when constructing the object or when modifying 
// it.
// If the minimum distance between the two limits, with a closed 
// CATFrFCompositeCurve, is smaller than the resolution then the singularity 
// flag has a meaning. In this configuration, two cases are available :
//   * use the entire CATFrFCompositeCurve,  
//   * consider the singular case of a point.
// This question is solved by the value of the singular flag (1 for the entire
// CATFrFCompositeCurve case  and 0 for the other).
// One can evaluate the quality of the object with the Check method.
// 
// To sum up :
// StartLimit<EndLimit is the usual case,
// StartLimit=EndLimit with an opened CCv (Closure=0) gives a singular point,
// StartLimit=EndLimit with a closed CCv is resolved with the singularity flag,
// StartLimit>EndLimit has a meaning only if the CCv is closed.
//
//==========================================================================
//
// Usage notes:
//   
//========================================================================== 
// March 98     Creation                    Paul-Alexandre Lourme  -   ALM
//========================================================================== 
//
#ifndef CATFrFCCvLimits_H
#define CATFrFCCvLimits_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATFrFCCvParam.h"
#include "CATFrFCompositeCurve.h"
#include "CATCGMVirtual.h"

class CATFrFCCvLimits;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFCCvLimits : public CATCGMVirtual
{
 public :
//=============================================================================
// Constructors and Destructors
//=============================================================================
//
// Default constructor : constructs an empty CATFrFCCvLimits
//
  CATFrFCCvLimits ();

//
// Constructs a CATFrFCCvLimits from a pointer on a CATFrFCompositeCurve.
// This method fills the StartLimit and the EndLimit respectively with
// the beginning of the first curve of the CATFrFCompositeCurve and the end
// of the last one (taking into account the orientations of those CATCurves
// into the CATFrFCompositeCurve). The singularity has the default value 0.
// The resolution has the default value 0..
//
//
  CATFrFCCvLimits ( CATFrFCompositeCurve * iCCv);

//
// Constructs a CATFrFCCvLimits from two CATFrFCCvParams and a pointer
// on a CATFrFCompositeCurve.
// This method checks the order of the two CATFrFCCvParams according to the 
// value of the closure of the CATFrFCompositeCurve. It also checks whether 
// the CATCurve pointed by the CATCrvParam of each CATFrFCCvParam is the 
// CATCurve of the given CATFrFCompositeCurve with index the CrvIndex of each 
// CATFrFCCvParam.
//
  CATFrFCCvLimits ( const CATFrFCCvParam & iStartLimit, 
		    const CATFrFCCvParam & iEndLimit,
		    CATFrFCompositeCurve * iCCv,
		    CATLONG32 iFlag = 0,
		    double iResolution = 0.);
  
//
// Copy Constructor.
//
// Before copying, this method calls the Check method on the input value
//
  CATFrFCCvLimits (const CATFrFCCvLimits &);

//
// Destructor
//
  virtual ~CATFrFCCvLimits();

//=============================================================================
// Check Method
//=============================================================================
//
// Checks the CATFrFCCvLimits. It returns :
//   -2 if a problem is detected,
//   -1 if the object is incomplete to be tested,
//    0 if the object is singular : one point,
//    1 if the object is usual : StartLimit<EndLimit,
//    2 if one has StartLimit>EndLimit, with the Closure=1,
//    3 if one has StartLimit=EndLimit, with a closed CCv and Flag = 1. 
//
  virtual CATLONG32 Check() const;
 
//=============================================================================
// Set and Get Methods
// The Get methods don t call the Check method, the user has to call it 
// if he wants a sure result. As the CATFrFCompositeCurve can be modified, 
// the user may use a wrong CATFrFCCvLimits. 
//=============================================================================
//
// Get Limit 
//
  virtual CATFrFCCvParam GetLimit(CATLONG32 iExtremity) const;
//
// Get Flag 
//
  virtual CATLONG32 GetFlag() const;
//
// Get Resolution 
//
  virtual double GetResolution() const;
//
// Get CCv 
//
  virtual CATFrFCompositeCurve * GetCCv() const;
//
// Set Limit 
//
  virtual void SetLimit(const CATFrFCCvParam & iLimit, CATLONG32 iExtremity);
//
// Set Flag 
//
  virtual void SetFlag(CATLONG32 iFlag);
//
// Set Resolution 
//
  virtual void SetResolution(double iResolution);
//
// Set CCv 
//
  virtual void SetCCv(CATFrFCompositeCurve * iCCv);

//=============================================================================
// Overloaded operators
//=============================================================================
//
// Defines the equality of two CATFrFCCvLimits.
// Before doing the equality, this method calls the Check method on the 
// input value
//
  const CATFrFCCvLimits& operator = (const CATFrFCCvLimits &);

 protected :
//=============================================================================
// Datas
//=============================================================================
 CATFrFCCvParam                _Limit[2];
 CATLONG32                          _Flag;
 double                        _Resolution;
 CATFrFCompositeCurve *        _CCv;

};
#endif




