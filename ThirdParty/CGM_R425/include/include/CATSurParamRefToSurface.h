#ifndef CATSurParamRefToSurface_H
#define CATSurParamRefToSurface_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1999
//
// CATSurParamRefToSurface : CATSurParamReference for a surface.
//
// DESCRIPTION : this class inherits from CATSurParamReference. It requires a pointer to
// a CATSurface. It will use the GetKnotVector methods of this CATSurface.
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
//       - CATSurParamRefToSurface
//
//=============================================================================
//
// History
//
// Jan. 99   Remy Rorato                  Creation            
//
//=============================================================================

#include "YP00IMPL.h"
#include "CATSurParamReference.h"

class CATSurface;
class CATParamData;

class ExportedByYP00IMPL CATSurParamRefToSurface : public CATSurParamReference
{
//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
public:
  CATSurParamRefToSurface(CATSurface* iSurface);
  virtual ~CATSurParamRefToSurface();

//=============================================================================
// METHODS OF COMPUTATION : all inherited
//=============================================================================
public:
  virtual double ComputeGlobalParamU(const CATParamData &iLocalPosition) const ;
  virtual double ComputeGlobalParamV(const CATParamData &iLocalPosition) const ;
  virtual void   ComputeGlobalParams(const CATParamData &iLocalPositionU,  double &oGlobalParamU,
	                                 const CATParamData &iLocalPositionV,  double &oGlobalParamV) const ;
  virtual void ComputeLocalPositionU(double iGlobalParam, CATParamData & oPosition) const ;
  virtual void ComputeLocalPositionV(double iGlobalParam, CATParamData & oPosition) const ;
  virtual void ComputeLocalPositions(double iGlobalParamU, CATParamData &oPositionU, 
									 double iGlobalParamV, CATParamData &oPositionV) const ;
  virtual void ComputeLocalPositionU(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
  virtual void ComputeLocalPositionV(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
//=============================================================================
// Data
//=============================================================================
private:
  CATSurface* _Surface;

};


#endif
