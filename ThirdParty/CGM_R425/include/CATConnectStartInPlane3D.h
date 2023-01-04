//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//==========================================================================
//
// CATConnectStartInPlane3D:
//   Base class for the computation of the bitangency plane between two
//   support surfaces, passing through a given 3D point.
//
//==========================================================================
//
// Usage Notes: (see comments below)
//
//========================================================================== 
//   /11/05 CQI Creation
// 12/03/20 Q48 Headers etc for math versioning
//========================================================================== 

#ifndef CATConnectStartInPlane3D_H
#define CATConnectStartInPlane3D_H

// ExportedBy
#include "Connect.h"

// Base class
#include "CATConnectStartInPlaneBase.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSurLimits.h"
#include "CATCrvParam.h"
#include "CATMathPoint.h"
#include "CATGeoOperator.h"
#include "CATMathIntervalND.h"

class CATMathSystem;
class CATMathAttrList;
class CATGeoFactory;
class CATCurve;
class CATConnectTool;
class CATSurLimits;
class CATSurface;
class CATMathPlane;
class CATSoftwareConfiguration;

class ExportedByConnect CATConnectStartInPlane3D : public CATConnectStartInPlaneBase
{    
  
public:

  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------

  /**
  * Constructor.
  * iFactory             : current geometric factory
  * iConfig              : software configuration
  * iSupport1            : first support surface
  * iSupportOrientation1 : normal orientation of first support surface
  * iSupport2            : second support surface
  * iSupportOrientation2 : normal orientation of second support surface
  * iFixedPoint          : 3D coordinates of fixed point
  * iConnectTool         : current connect tool (usefull to retrieve contextual connect information)
  */

//Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATConnectStartInPlane3D(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATSurface * iSupport1,
                           const CATLONG32 iSupportOrientation1,
                           CATSurface * iSupport2,
                           const CATLONG32 iSupportOrientation2,
                           const CATMathPoint & iFixedPoint,
                           const CATConnectTool * iConnectTool);

  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATConnectStartInPlane3D(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATSurface * iSupport1,
                           const CATLONG32 iSupportOrientation1,
                           CATSurface * iSupport2,
                           const CATLONG32 iSupportOrientation2,
                           CATSurface * iSupport3,
                           const CATLONG32 iSupportOrientation3,
                           const CATMathPoint & iFixedPoint,
                           const CATConnectTool * iConnectTool);


  /**
  * Destructor.
  */
  ~CATConnectStartInPlane3D();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
		
  /**
  * Runs a CATConnectStartHomotopy operator in <tt>ADVANCED</tt> mode.
  */
  virtual int RunOperator();

  /**
  * Mandatory : this method allows to specify usefull limits for internal computations.
  */
  virtual void SetLimits(CATSurLimits * iLimitsOnSupport1, CATSurLimits * iLimitsOnSupport2);
	
  //-----------------------------------------------------------------------
  //- Get Methods
  //-----------------------------------------------------------------------

  /**
  * GetDiagnostic : returns 1 if a solution has been found, 0 otherwise.
  */
  CATLONG32 GetDiagnostic();
	
  // Following get methods must be call if GetDiagnostic returns 1

  /**
  *  GetCurve
  *  Returns the 3D solution curve: a line (chamfer) or a circle (fillet).
  *  Caller must manage deletion.
  */
  CATCurve * GetCurve();

  /**
  *  GetCurveCenter
  *  Returns the 3D center of solution curve (eg. the center of the circle).
  *  The method returns 1 if this center exists, 0 otherwise (case of a line or infinite radius circle).
  */
  int GetCurveCenter(CATMathPoint & oCurveCenter);

  /**
  *  GetFixedPoint
  *  Returns the input 3D fixed point and the maximum distance from 3D solution points on supports.
  */
  void GetFixedPoint(CATMathPoint & oFixedPoint, double & oMaxDist);

  /**
  *  GetPlane
  *  Returns the math plane solution centered on bitangent circle center,
  *  with axis U = FirstTrace ( = Trace1 - CircleCenter), and axis V orthognal.
  *  Caller must manage deletion.
  */
  CATMathPlane * GetMathPlane();

  /**
  *  GetPoints
  *  Returns the 3D points / UV-points solution.
  */
  CATBoolean GetPoints(CATMathPoint & oPtSupp1, CATMathPoint & oPtSupp2);
  CATBoolean GetPoints(CATSurParam  & oPtSupp1, CATSurParam  & oPtSupp2);

  virtual CATBoolean GetPoints(CATMathPoint & oPtSupp1, CATMathPoint & oPtSupp2, CATMathPoint & oPtSupp3);
  virtual CATBoolean GetPoints(CATSurParam  & oPtSupp1, CATSurParam  & oPtSupp2, CATSurParam  & oPtSupp3);
  /**
  *  GetRadius
  *  Returns the radius solution (usefull for variable fillet).
  */
  double GetRadius();
  
  virtual const CATConnectTool *GetTool();
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  protected :
  // ComputeCenterCoords
  // This method allows to compute the 3D coordinates of the center point
  // of solution bitangency, with radius iRadius and defined by iX:
  // First support solution point:
  // iX[0] = u
  // iX[1] = v
  // Second support solution point:
  // iX[2] = r
  // iX[3] = s
  //
  // NB.: oCenterCoords must be allocated with dimension 3.
  //      if given, oAngle is filled with associated arc angle.
   virtual void ComputeCenterCoords(double * iX, double iRadius, double * oCenterCoords, double * oAngle = NULL);


  void Init(CATGeoFactory * iFactory,
                               CATSoftwareConfiguration * iConfig,
                               const CATMathPoint & iFixedPoint,
                               const CATConnectTool * iConnectTool,
                               CATSurface * iSupport1,
                               const CATLONG32 iSupportOrientation1,
                               CATSurface * iSupport2,
                               const CATLONG32 iSupportOrientation2,
                               CATSurface * iSupport3 = NULL,
                               const CATLONG32 iSupportOrientation3 = 0
                               );

  void AllocateInit();

  virtual int GetDim(); 

  virtual CATMathIntervalND FindDomain(double *& ioDomainArray);
  virtual CATBoolean CreatePlaneSystem();
  virtual double ComputeRadius();
  void AttributeList(CATMathAttrList & ioList);
  void CleanAttributeList(CATMathAttrList & ioList);
  virtual CATBoolean SelectSolution(CATMathSetOfPointsND &iSolutionPoints);
  virtual int ComputeDefaultResult();

  // Input data
  CATSoftwareConfiguration * _Config;
  CATSurface               * _Support1, * _Support2, * _Support3;
  CATLONG32                  _SupportOrientation1, _SupportOrientation2, _SupportOrientation3 ;
  const CATConnectTool     * _Tool;
  CATMathPoint               _FixedPoint;
  CATMathSystem            * _PlaneSystem;
  // Internal data
  CATSurLimits               _Limits[3];
  
  // Output data (solution point and radius)
  double       _radius;
  double     * _Init;
  CATLONG32    _Diagnostic;

 CATLONG32 _MaxDim;

  //-----------------------------------------------------------------------
  // - CGMReplay
  //-----------------------------------------------------------------------
protected:
  friend class CATGeoStreamFactory; 
  
  // private static data
  static CATString _OperatorId;
  
public:
  const CATString * GetOperatorId();
  
  virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

private:
  void DumpTool(CATCGMOutput& os);
  virtual void MyDebug();
};
#endif
