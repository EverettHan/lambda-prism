#ifndef CATSurParamRefMonoPatch_H
#define CATSurParamRefMonoPatch_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATSurParamRefMonoPatch : CATSurParamReference for a monopatch surface.
//
// DESCRIPTION : this class inherits from CATSurParamReference. It includes
// the required computations, knowing the the global parameter on a mono-patch
// surface is the local parameter.
// 
// Main Methods : see CATSurParamReference
//  
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
//  Inheritance :
//     - CATSurParamReference
//       - CATSurParamRefMonoPatch
//
//=============================================================================
//
// History
//
// Aug. 97   Jose CHILLAN (jch)    Creation            
//
//=============================================================================

#include "ExportedByCATCGMGeoMath.h"
#include "CATSurParamReference.h"

class CATMathPoint2D;
#include "CATParamData.h"
#include "CATMathInline.h"

class ExportedByCATCGMGeoMath CATSurParamRefMonoPatch : public CATSurParamReference
{
public:
//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
// Destructor
  INLINE virtual ~CATSurParamRefMonoPatch();

//=============================================================================
// METHODS OF COMPUTATION : all inherited
//=============================================================================
// Method to identify surface defined with only one patch 
  virtual CATLONG32 IsMonoPatch() const ;

// Methods to convert a global parameter to a local one
  virtual double ComputeGlobalParamU(const CATParamData &iLocalPosition) const ;
  virtual double ComputeGlobalParamV(const CATParamData &iLocalPosition) const ;
  virtual void   ComputeGlobalParams(const CATParamData &iLocalPositionU,  double &oGlobalParamU,
	                                 const CATParamData &iLocalPositionV,  double &oGlobalParamV) const ;
  virtual void ComputeLocalPositionU(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
  virtual void ComputeLocalPositionV(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
// Methods to convert a local parameter to a global one
  virtual void ComputeLocalPositionU(double         iGlobalParam,
				     CATParamData & oPosition) const ;

  virtual void ComputeLocalPositionV(double         iGlobalParam,
				     CATParamData & oPosition) const ;

  virtual void ComputeLocalPositions(double iGlobalParamU, CATParamData &oPositionU, 
									 double iGlobalParamV, CATParamData &oPositionV) const ;
// Adding a global param to local positions
// The result may be the entry position ( to behave like += )
  virtual void AddGlobalToLocalU(const CATParamData     & iPositionU,
				 double                   iMove,
				 CATParamData           & oResultU) const;
  virtual void AddGlobalToLocalV(const CATParamData     & iPositionV,
				 double                   iMove,
				 CATParamData           & oResultV) const;

// Gives the difference between to local parameters : returns First - Second
  virtual double SubstractLocalParamU(const CATParamData & iFirstParam,
				      const CATParamData & iSecondParam) const ;
  virtual double SubstractLocalParamV(const CATParamData & iFirstParam,
				      const CATParamData & iSecondParam) const ;

// Conversion of an array of Global parameters to local ones : the result
// array must have been already allocated. The Global parameters are
// defined as two-dimensional points
  virtual void ConvertGlobalToLocal(const CATMathPoint2D* iGlobalParameters,
				    CATLONG32          iCountParams,
				    CATParamData *oResultsU,
				    CATParamData *oResultsV) const;

// Reverse conversion of an local parameter to global ones : the output array of
// CATMathPoint2D must have been already allocated.
  virtual void ConvertLocalToGlobal(const CATParamData * iLocalPositionU,
				    const CATParamData * iLocalPositionV,
				    CATLONG32                 iCountParams,
				    CATMathPoint2D     * oGlobalParmaeters) const;

};


//-----------------------------------------------------------------
// INLINE method
//-----------------------------------------------------------------
// Destructor
INLINE CATSurParamRefMonoPatch::~CATSurParamRefMonoPatch()
{
};

#endif
