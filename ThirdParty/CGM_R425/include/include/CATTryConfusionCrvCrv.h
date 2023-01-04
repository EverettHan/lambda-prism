#ifndef CATTryConfusionCrvCrv_H
#define CATTryConfusionCrvCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

// ExportedBy
#include "Y30A3HGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCrvParam.h"
#include "CATMathDef.h"
#include "CATMathSetOfPointsND.h"
#include "CATCGMVirtual.h"
#include "CATCreateTryConfusionCrvCrv.h"
#include "CATCGMOperatorDebug.h"
#include "CATString.h"

class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATEdgeCurve;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

 /**
 * Class defining the operator that computes the overlapping zones between two curves.
 *<br>Two curves are overlapping within a given tolerance if their
 * Haussdorf distance <tt>dH</tt> is less than this tolerance.<br>
 * <pre>
 * dH= MAX [ Max{Point1 in Curve1}Min{Point2 in Curve2} distance(Point1,Point2),
 *           Max{Point2 in Curve2}Min{Point1 in Curve1} distance(Point1,Point2) ]</pre>
 *<ul>
 *<li>The CATTryConfusionCrvCrv is not streamable. 
 *<li>After its creation, run it with the <tt>Run</tt> method. 
 * Then, you access the results by the mean of an iterator. <tt>delete</tt> it after use. 
 *</ul>
 */

class ExportedByY30A3HGG CATTryConfusionCrvCrv : public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATTryConfusionCrvCrv);
public:
   /**
   * Constructs a CATTryCOnfusionCrvCrv.
   * @param iWhere
   * The pointer to the factory of the curves.
   * @param iCrv1
   * The pointer to the first curve.
   * @param iLimits1
   * The limitations of <tt>iCrv1</tt> to take into account.
   * @param iCrv2
   * The pointer to the secong curve.
   * @param iLimits2
   * The limitations of <tt>iCrv2</tt> to take into account. 
   * @param iTol
   * The maximum Haussdorf distance for deciding the overlap.
    */
   CATTryConfusionCrvCrv(CATGeoFactory * iWhere,
                         CATSoftwareConfiguration * iConfig,
                         CATCurve * iCrv1,
                         const CATCrvLimits & iLimits1,
                         CATCurve * iCrv2,
                         const CATCrvLimits & iLimits2,
                         const double iTolerance);
 
   CATTryConfusionCrvCrv(CATGeoFactory *);
   
   ~CATTryConfusionCrvCrv();
   
   void Run2();
   
   /**
   * Runs the operator.
   */
   // non necessaire car Run() toujours declare:
   // CATCGMOperatorDebugDeclareRun(CATTryConfusionCrvCrv, CATGeoOperator);
   
   int Run();
   
   /** @nodoc @nocgmitf */
   int RunOperator();
   
   
   /**
   * Initializes the iterator of the overlapping zones.
   */
   void BeginningConfusion();
   // Return 0 if no confusion exists, 1 else
   CATBoolean GetConfusion();
   CATBoolean NextConfusion();
   
   // Return 0 if no confusion exists, return a merged curve if a confusion exists
   CATEdgeCurve * GetEdgeCurve();
   CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve* &oStart, CATPointOnEdgeCurve* &oEnd);

   // Return the params limits of the confusion on a given curve (_Crv1 or _Crv2)
   void GetConfusionLimits(CATCurve * iCrv, CATCrvParam & oStart, CATCrvParam & oEnd);
   void GetConfusionLimits(CATCurve * iCurve, CATCrvLimits &oLimits);
   void GetFirstConfusionParam(CATCrvParam &Param1, CATCrvParam &Param2);
   void GetSecondConfusionParam(CATCrvParam &Param1, CATCrvParam &Param2);

   void SetParamIncl(CATCrvParam Param1[4], CATCrvParam Param2[4][2], CATLONG32 NbInclusion[4], int NbSol);

   void SetDetectInvalidMergedCurve();
   
   // If a confusion exists, this option allows to create a merged curve whose
   // RefCurve will be stable whatever input swapping of iCrv1 and iCrv2
   void SetStableRefCurve(CATBoolean iEnable=TRUE);

   /**
    * @nodoc @nocgmitf
    * param oParamMapping
    * The mapping set of point (dimension 2) between the two curves for this merged curve.
    */
   void GetParamMapping (CATMathSetOfPointsND  & oParamMapping);

   /**
    * @nodoc @nocgmitf
    * param oParamMapping
    * The mapping set of point (dimension 2) between the two curves for this merged curve.
    * The memory has to be managed by the caller (use delete).
    */
   void GetParamMapping (CATMathSetOfPointsND *& oParamMapping);
   
   // @nodoc @nocgmitf
   CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;

private:
   
   CATCrvParam _LimParam1[2], _LimParam2[2];
   const CATCurve * _Crv1, * _Crv2;
   double _Tolerance;
   
   // Data for output
   CATLONG32 _NbConf, _IndexConf;
   CATCrvParam _ConfStart1[4], _ConfEnd1[4], _ConfStart2[4], _ConfEnd2[4];
   CATCrvParam _Param1[4], _Param2[4][2];
   int _NbSol, _SetParamIncl;
   CATLONG32 _NbInclusion[4];
   CATMathSetOfPointsND * _ParamMapping[4];
   double _MaxGap[4];
   CATEdgeCurve * _ECrv[4];
   CATBoolean _DetectInvalidMergedCurve ;
   CATBoolean _StableRefCurve;
   CATSoftwareConfiguration * _Config;
   
   void StoreConfusion(const CATCrvParam          & iStart1,
                       const CATCrvParam          & iEnd1,
                       const CATCrvParam          & iStart2,
                       const CATCrvParam          & iEnd2,
                       const double                 iMaxGap,
                             CATMathSetOfPointsND * iMapping);
   
   void RemoveConfusion(int NumConf);
   void SwapMapping(CATMathSetOfPointsND * ioParamMapping);
   //========================================================================
   // Gestion CGMReplay
   //========================================================================
protected:
   friend class CATGeoStreamFactory;
   
   // private static data
   static CATString _OperatorId;
   
public:
   
   /** @nodoc @nocgmitf*/
   const CATString * GetOperatorId();
   //-----------------------------------------------------------------------
   //- Gestion Mode Record 
   //-----------------------------------------------------------------------
   
   /** @nodoc @nocgmitf*/
   CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   /** @nodoc @nocgmitf*/
   virtual void WriteInput(CATCGMStream  & os);
   /** @nodoc @nocgmitf*/
   virtual void WriteOutput(CATCGMStream & os);
   /** @nodoc @nocgmitf*/
   virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
   /** @nodoc @nocgmitf*/
   virtual void Dump( CATCGMOutput& os );
   /** @nodoc @nocgmitf*/
   void DumpOutput(CATCGMOutput & os);
   /** @nodoc @nocgmitf*/
   virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
   /** @nodoc @nocgmitf*/
   CATCheckDiagnostic CheckOutput(CATCGMOutput &os);

private:
   /** @nodoc @nocgmitf*/
   void DumpConfusion(      CATCGMOutput & os,
                      const CATLONG32      iIndex,
                      const CATCurve     * iCrv,
                      const CATPoint     * iStart,
                      const CATPoint     * iEnd) const;

};

#endif
