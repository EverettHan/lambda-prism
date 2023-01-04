// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATOrientationLoop
// Class for operator of orientation of a loop
//
//===================================================================
// Jan. 98    Creation                                      X.Gourdon
// 04/03/20 NLD Implementation de GetSoftwareConfiguration()
// 11/03/20 Q48 Some C++11 keyword for derived methods
//===================================================================

#ifndef CATOrientationLoop_H
#define CATOrientationLoop_H

// ExportedBy
#include "Y30C1XMM.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathDef.h"

class CATGeoFactory;
class CATPCurve;
class CATMathFunctionX;

#include "CATCrvParam.h"
#include "CATCreateOrientationLoop.h"

class CATSoftwareConfiguration;

class ExportedByY30C1XMM CATOrientationLoop  : public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATOrientationLoop);
public:

   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------

   CATOrientationLoop(      CATGeoFactory * iFactory,
                      const CATLONG32       iNbPCrv,
                      const CATPCurve    ** iPCrv,
                      const CATCrvParam   * iStartParam,
                      const CATCrvParam   * iEndParam);

   //do not use - EAB - 10/09/04
   CATOrientationLoop(      CATGeoFactory            * iFactory,
                            CATSoftwareConfiguration * iConfig,
                      const CATLONG32                  iNbPCrv,
                      const CATPCurve               ** iPCrv,
                      const CATCrvParam              * iStartParam,
                      const CATCrvParam              * iEndParam);
   ~CATOrientationLoop();

   //-----------------------------------------------------------------------
   //- Public methods
   //-----------------------------------------------------------------------

   CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;

   /** @nodoc @nocgmitf */
   int RunOperator();
   CATLONG32 GetOrientation() const; // returns 1 if positive, -1 if negative, 0 if problem (area null)

   double GetArea() const;

   //-----------------------------------------------------------------------
   //- Protected methods
   //-----------------------------------------------------------------------

protected:

   void FirstApproximation(const CATTolerance & iTol , CATLONG32 & oNbNonExactPCrv, double & oMaxError,
                                 double & oNonExactArea, double & oExactArea);

   double SecondApproximation(const double iErrorMax,
                              const CATLONG32 iNbNonExactPCrv,
                                    double & oError);

   double ApproximationOnPCrv(const CATPCurve * iPCrv,
                              const CATCrvParam & iStartParam,
                              const CATCrvParam & iEndParam,
                              const double iMaxError,
                                    double & oError);

   double ApproximationOnArc(const double w0, const double w1,
                             const CATMathFunctionX * fU,
                             const CATMathFunctionX * fV,
                             const double ErrorMax,
                                   double & LocalError);

   double RApproximationOnArc(const double w0, const double w1,
                              const double u0, const double v0,
                              const double u1, const double v1,
                              const CATMathFunctionX * fU,
                              const CATMathFunctionX * fV,
                              const double ErrorMax,
                                    double & LocalError,
                              const CATBoolean IsEvalInterval,
                              const CATLONG32 iDepth);

   double ComputeArea(const double x0, const double y0,
                      const double x1, const double y1);

private:
         double        _u, _v;
         double        _Tol;
         double        _Area;
   const CATCrvParam * _StartParam;
   const CATCrvParam * _EndParam;
   const CATPCurve  ** _PCrv;
   //    CATPCurve ** _PCrvInit;
         CATLONG32     _N;
         CATLONG32     _Orientation;


   // CGMReplay integration
protected:
   friend class CATGeoStreamFactory; 
   static CATString           _OperatorId;
   CATSoftwareConfiguration * _Config;

public:
   /** @nodoc @nocgmitf */
   const CATString * GetOperatorId();
   /** @nodoc @nocgmitf */
   CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   /** @nodoc @nocgmitf */
   virtual void WriteInput(CATCGMStream & os);
   /** @nodoc @nocgmitf */
   virtual void WriteOutput(CATCGMStream & os);
   /** @nodoc @nocgmitf */
   virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
   /** @nodoc @nocgmitf */
   virtual void Dump( CATCGMOutput& os ) ;
   /** @nodoc @nocgmitf */
   virtual void DumpOutput(CATCGMOutput & os);
   /** @nodoc @nocgmitf */
   virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
   /** @nodoc @nocgmitf */
   virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};


#endif
