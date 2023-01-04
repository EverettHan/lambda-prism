#ifndef CATCrvParamRefMonoArc_H
#define CATCrvParamRefMonoArc_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATCrvParamRefMonoArc : object made to handle the parameters on mono-arc
// curves
//
// DESCRIPTION : on a mono-arc curve, the global parameter is defined to be
// the local one and vice-versa.
// 
// Main Methods : inherited from CATCrvParamReference ( no others)
//  
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// Inheritance :
//     - CATCrvParamReference
//       - CATCrvParamRefMonoArc
//
//=============================================================================
//
// History
//
// Aug. 97   Jose CHILLAN (jch)    Creation            
//
//=============================================================================

#include "ExportedByCATCGMGeoMath.h"
#include "CATCrvParamReference.h"

class CATParamData;

class ExportedByCATCGMGeoMath CATCrvParamRefMonoArc : public CATCrvParamReference
{
public:

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
// No constructors ni destructor

//=============================================================================
// COMPUTATION METHODS (inherited)
//=============================================================================
  virtual double ComputeGlobalParam(const CATParamData &iLocalPosition) const ;
 
// Methods to convert a local parameter to a global one
  virtual void ComputeLocalPosition(double         iGlobalParam,
				    CATParamData & oPosition) const ;
// mimize Patchnumber distance between  the output "CATParamData"
  virtual void ComputeLocalPositions(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition) const ;
//------------------------------------------------------------
// Added methods to enhance speed of certain operations
//------------------------------------------------------------
// Adding a global param to local positions
// The result may be the entry position ( to behave like += )
  virtual void AddGlobalToLocal(const CATParamData     & iPosition,
				double                   iMove,
				CATParamData           & oResult) const;

// Gives the difference between to local parameters : returns First - Second
  virtual double SubstractLocalParam(const CATParamData & iFirstParam,
				     const CATParamData & iSecondParam) const ;

// Conversion of an array of Global parameters to local ones : the result
// array must have been already allocated
  virtual void ConvertGlobalToLocal(const double* iGlobalParam,
				    CATLONG32          iCountParams,
				    CATParamData *oResults) const;

// Reverse conversion of an local parameter to global ones : the output array of double
// must have been already allocated.
  virtual void ConvertLocalToGlobal(const CATParamData * iLocalPositions,
				    CATLONG32                 iCountParams,
				    double             * oGlobalParmaeters) const;


//=============================================================================
// INTERNAL DATAS
//=============================================================================

};

#endif
