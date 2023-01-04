// COPYRIGHT DASSAULT SYSTEMES 1997

//===================================================================
//===================================================================
//
// CATPCurveIntegr
// ??? Classe permettant de verifier qu'une surface extrudee n'a pas de
// ??? normale nulle a l'interieur d'un pave 
// ???
//===================================================================


//===================================================================
// Usage notes:
//
//===================================================================

//===================================================================
// Mai. 97    Creation                         J-M.Guillard
// 23/05/08 NLD Ajout Init()
//===================================================================
//===================================================================

#ifndef CATPCurveIntegr_H
#define CATPCurveIntegr_H

#include "ExportedByCATGeometricObjectsCGM.h"   

#include "CATMathDef.h"
#include "CATMathFunctionX.h"
#include "CATMathBasisFunctionX.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"

class CATSurface;
class CATPCurve;
class CATSurParam;
class CATMathInterval2D;

class ExportedByCATGeometricObjectsCGM CATPCurveIntegr : public CATMathBasisFunctionX
{
 public:

  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------
  //  integrates from StartLimit to EndLimit
  CATPCurveIntegr (CATSurface * iSurface, 
		   const CATSurParam & iOrigine,  
		   CATPCurve  * iPCurve,
       const CATTolerance & iTolObject=CATGetDefaultTolerance());

  //  integrates from iStartParam to iEndParam
  CATPCurveIntegr (CATSurface * iSurface, 
		   const CATSurParam & iOrigine,  
		   CATPCurve  * iPCurve,
		   const CATCrvParam& iStartParam,
		   const CATCrvParam& iEndParam,
       const CATTolerance & iTolObject= CATGetDefaultTolerance());

  CATPCurveIntegr(const CATPCurveIntegr & PCurveInteg ); 
  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
  virtual CATMathFunctionX * Duplicate() const;
  CATMathClassId IsA() const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const; //IEY /Extreme Scale /13-07-07
  
  //-----------------------------------------------------------------
  // Destructor
  //-----------------------------------------------------------------
  virtual ~CATPCurveIntegr();


  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
  double Eval(const double & t) const;
  double Area() const;


 private:
 
  void Init(const CATSurParam & Origine) ;

  CATSurface *  _Surface;
  CATPCurve  *  _PCurve ;
  CATCrvParam   _StartParam;
  CATCrvParam   _EndParam;

  double    _u;
  double    _v;
  CATMathFunctionX * _Fx;
  CATMathFunctionX * _Fy;
  CATMathFunctionX * _Fxprime;
  CATMathFunctionX * _Fyprime;
};

#endif


