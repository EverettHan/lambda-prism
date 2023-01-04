// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATPositionPtVol
//
// Class for operator of positionement point - volume
//
// Description of the volume is following :
//  - CATLONG32    _NbFaces             : number of faces.
//  - CATLONG32 *  _NbPCurves           : number of PCurves delimiting the faces
//  _ CATPCurve ** _PCurveAllFaces : pointer on PCurves*, all PCurves
//                                   delimiting the same face grouped and ordered.
//  - CATCrvParam * _AllStartParam : start param on PCurve (index corresponding
//                                   with the one of _PCurveAllFaces)
//  - CATCrvParam * _AllEndParam   : end param on PCurve (index corresponding
//                                   with the one of _PCurveAllFaces)
//  _ CATMathBox *  _BBoxFaces     : bounding box of the faces. (for convenience
//                                   to avoid computations allready done ) 
//
//  !!!! convention !!!! : to allow the internal use of PositionPtLoop, the list of
// the PCurves/startparam/endparam of one face have to be in order in the following
// sense : the endparam of the i(th) pcurve of the face is geometricaly corresponding 
// to the startparam of the i+1(th) pcurve.  
//
//  tolerance : distance at which the point is considered as included in the skin of 
// the volume
//  
//  !!!! caution !!!! : problem is ill-conditionned if tolerance for inclusion in the 
//  skin is smaller than gap of EdgeCurve of the volume
//
// return value : 1 if in, -1 if out, 0 if on frontier at tolerance
//===================================================================
//   /12/97     Creation                                      J.Peter
// 12/03/20 Q48 Headers etc for math versioning
//===================================================================

#ifndef CATPositionPtVol_H
#define CATPositionPtVol_H

// ExportedBy
#include "Y300IINT.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCGMVirtual.h"

class CATSurParam;
class CATPCurve;
class CATPointOnCurve;
class CATGeoFactory;
class CATCrvParam;

class CATMathInterval;
class CATMathFunctionX;
class CATMathBox;

class CATSoftwareConfiguration;

#include "CATCrvParam.h"
#include "CATMathDef.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATGeoOperator.h"
#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

class ExportedByY300IINT CATPositionPtVol  : public CATGeoOperator
{
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATPositionPtVol(CATGeoFactory * iFactory,
    CATSoftwareConfiguration *iConfig,
		    const CATLONG32 iNbFaces,
		    const CATLONG32 * iNbPCurves,
		    const CATPCurve ** iPCurvesAllFaces,
		    const CATCrvParam * iAllStartParam,
		    const CATCrvParam * iAllEndParam,
                    const CATMathBox * iBBoxFaces,
		    const CATMathPoint & iPoint,
                    const double tolerance);

  CATPositionPtVol(CATGeoFactory * iFactory,
	    const CATLONG32 iNbFaces,
		    const CATLONG32 * iNbPCurves,
		    const CATPCurve ** iPCurvesAllFaces,
		    const CATCrvParam * iAllStartParam,
		    const CATCrvParam * iAllEndParam,
                    const CATMathBox * iBBoxFaces,
		    const CATMathPoint & iPoint,
                    const double tolerance);

  ~CATPositionPtVol();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  
  int RunOperator();

  CATLONG32 GetPosition() const; // returns 1 if in, -1 if out, 0 if on frontier at iTol

  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
  // private:

    int InterRayFaces(const CATMathDirection & dir, const double dombox);

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------

private:

  CATGeoFactory  * _ImplicitFactory;
  CATMathPoint _Point;
  CATSoftwareConfiguration *_Config;

  CATLONG32  _NbFaces;
  const CATLONG32 * _NbPCurves;
  CATCrvParam * _AllStartParam, * _AllEndParam;
  const CATPCurve ** _PCurvesAllFaces;
  CATMathBox * _BBoxFaces;
  
  double _Tolerance;
  CATLONG32 _Position;


//========================================================================
// CGMReplay Implementation - SKA Creation
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  virtual const CATString * GetOperatorId();
  virtual CATGeoOpTimer * GetTimer();
  virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  virtual void WriteInput(CATCGMStream  & Str);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void WriteOutput(CATCGMStream & Str);
  virtual void DumpOutput(CATCGMOutput & os) ;
  virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
  virtual CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

};

#endif
