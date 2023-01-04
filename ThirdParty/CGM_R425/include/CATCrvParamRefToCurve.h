#ifndef CATCrvParamRefToCurve_H
#define CATCrvParamRefToCurve_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1999
//
// CATCrvParamRefToCurve : object made to handle the parameters on any kind
// of curves
//
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// Inheritance :
//     - CATCrvParamReference
//       - CATCrvParamRefToCurve
//
//=============================================================================
//
// History
//
// Apr.99   Remy Rorato                    Creation            
//
//=============================================================================

#include "YP00IMPL.h"
#include "CATCrvParamReference.h"

class CATParamData;
class CATCurve;

class ExportedByYP00IMPL CATCrvParamRefToCurve : public CATCrvParamReference
{

  public:

  CATCrvParamRefToCurve(CATCurve* iCurve);
  virtual ~CATCrvParamRefToCurve();

  virtual double ComputeGlobalParam(const CATParamData &iLocalPosition) const ;
  virtual void ComputeLocalPosition(double iGlobalParam, CATParamData & oPosition) const ;
// mimize Patchnumber distance between  the output "CATParamData"
  virtual void ComputeLocalPositions(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition) const ;
  private:

  CATCurve* _Curve;

};

#endif
