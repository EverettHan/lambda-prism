// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionEdgeCrvEdgeCrv:
// interface of edgecurve-edgecurve intersection
/**
* Interface representing the operator of the intersection of two CATEdgeCurves.
*<br>The operator offers the isolated solutions (points)
*<ul>
*<li>It is created with the <tt>CreateIntersection</tt> operators
*<li>In case of <tt>BASIC</tt>
* mode, the operation is automatically performed. 
*<li>In case of <tt>ADVANCED</tt>
* mode, the user may precise options with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*<li>The results are accessed thanks to iterators, that allow to handle
* multiple solutions.
*<li> The operator is removed from the memory with the <tt>Remove</tt> method.
*</ul>
*/
//
//=============================================================================
// Usage Notes:
//
// This is an abstract class to handle implementation by ObjectOriented way
//
//=============================================================================
// Jan.  99 PSH Creation                                                P. Sebah
// Nov.  99 DAD Ajout de GetBestConfusionPoint() & SetReconvergence()
// Dec.  20 R1Y Added a replay mechanism (with XScale).
// 25/01/21 NLD Shunt deprecated constructors without configuration
//              (except for one with still one external call)
//              Shunt old Create without configuration
//              Reorder: methods first, data after
//=============================================================================

#ifndef CATINTERSECTEDGECRVEDGECRV_H
#define CATINTERSECTEDGECRVEDGECRV_H

// #define CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor1
   #define CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor2 // non supprimable voir CATCmoTopoUtilities.cpp NLD250121
// #define CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor5
// #define CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedCreate

#include "CATMathDef.h"
#include "CATCGMOperator.h"
#include "CATSkillValue.h"

#include "Y30C3XGG.h"

class CATGeoFactory;
class CATCrvParam;
class CATCrvLimits;
class CATPointOnEdgeCurve;
class CATCartesianPoint;
class CATCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeoOpTimer;

//#ifdef CATIAV5R14
class CATIntersectionCrvCrv;
/*
#else
class CATIntersectionCrvCrvCx2;
#endif
*/
class ExportedByY30C3XGG CATIntersectionEdgeCrvEdgeCrv : public CATCGMOperator
{
public:
   /**
   * Constructors
   */
#ifdef CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor5
   CATIntersectionEdgeCrvEdgeCrv(CATGeoFactory            * iFactory);
#endif

#ifdef CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor1
   CATIntersectionEdgeCrvEdgeCrv(CATGeoFactory            * iFactory,
                                 CATEdgeCurve             * iEdgeCrv1,
                                 CATPointOnEdgeCurve      * iStartPOEC1,
                                 CATPointOnEdgeCurve      * iEndPOEC1,
                                 CATEdgeCurve             * iEdgeCrv2, 
                                 CATPointOnEdgeCurve      * iStartPOEC2,
                                 CATPointOnEdgeCurve      * iEndPOEC2);
#endif

#ifdef CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedConstructor2
   CATIntersectionEdgeCrvEdgeCrv(CATGeoFactory            * iFactory,
                                 CATEdgeCurve             * iEdgeCrv1,
                                 CATEdgeCurve             * iEdgeCrv2);
#endif

   CATIntersectionEdgeCrvEdgeCrv(CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCrv1,
                                 CATPointOnEdgeCurve      * iStartPOEC1,
                                 CATPointOnEdgeCurve      * iEndPOEC1,
                                 CATEdgeCurve             * iEdgeCrv2, 
                                 CATPointOnEdgeCurve      * iStartPOEC2,
                                 CATPointOnEdgeCurve      * iEndPOEC2);

   CATIntersectionEdgeCrvEdgeCrv(CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCrv1,
                                 CATEdgeCurve             * iEdgeCrv2);
   /**
   * Destructor.
   */
   ~CATIntersectionEdgeCrvEdgeCrv();

   /** Set the flag for reconvergence or not.
   */
   void                  SetReconvergence(int iNewReconvergence);

   /**
   * Runs a CATIntersectionEdgeCrvEdgeCrv operator in <tt>ADVANCED</tt> mode.
   */
   int                   RunOperator();

   /**
   * Returns the number of isolated points resulting of a CATIntersectionEdgeCrvEdgeCrv operator.
   */
   CATLONG32             GetNumberOfPoints() const;

   /**
   * Initializes the iterator of the resulting points of a 
   * CATIntersectionEdgeCrvEdgeCrv operator.
   *<br>By default, the initialization is performed once the operator has been
   * calculated, and is therefore only used to read the solutions again.
   */
   void                  BeginningPoint();

   /**
   * Points to the next solution point of a CATIntersectionEdgeCrvEdgeCrv operator.
   *<br>After <tt>Beginning</tt>, it points to the first point.
   * @return
   *<dl><dt><tt>1</tt> <dd>if there is a solution point
   *    <dt><tt>0</tt> <dd>no more solution point.</dl>
   */
   CATBoolean            NextPoint();

   /**
   * Returns the next solution point of a CATIntersectionEdgeCrvEdgeCrv operator
   * as a CATPointOnCurve pointer.
   *<br>Creates the object if necessary.
   * @param iCurve
   * The first or the second operand of the operator, on which the point has to
   * be created.
   */
   CATPointOnEdgeCurve * GetPointOnEdgeCurve (CATEdgeCurve *iEdgeCurve, const CATLONG32 iIndex=0) const ;

   /**
   * Returns the number of curves resulting of a CATIntersectionEdgeCrvEdgeCrv operator.
   */
   CATLONG32             GetNumberOfCurves() ;

   /**
   * Initializes the iterator of the resulting curves of a 
   * CATIntersectionEdgeCrvEdgeCrv operator.
   *<br>By default, the initialization is performed once the operator has been
   * calculated, and is therefore only used to read the solutions again.
   */
   void                  BeginningCurve() ;

   /**
   * Points to the next solution curve of a CATIntersectionEdgeCrvEdgeCrv operator.
   *<br>After <tt>Beginning</tt>, it points to the first curve.
   * @return
   *<dl><dt><tt>1</tt> <dd>if there is a solution curve
   *    <dt><tt>0</tt> <dd>no more solution curve.</dl>
   */
   CATBoolean            NextCurve();

   /**
   * Returns the next solution EdgeCurve of a CATIntersectionEdgeCrvEdgeCrv operator,
   * and the POEC extremities oStart and oEnd on this edgecurve.
   */
   CATEdgeCurve        * GetEdgeCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd) ;

   /**
   * Returns the first couple of POEC (POEC on edge curve 1 and POEC on edge curve 2) 
   * of the next confusion curve
   */
   void                  GetFirstConfusionPoint(CATPointOnEdgeCurve * & PointOnCurve1, CATPointOnEdgeCurve * & PointOnCurve2);

   /**
   * Returns the second couple of POEC (POEC on edge curve 1 and POEC on edge curve 2) 
   * of the next confusion curve
   */
   void                  GetSecondConfusionPoint(CATPointOnEdgeCurve * & PointOnCurve1, CATPointOnEdgeCurve * & PointOnCurve2);

   /**
   * Returns the best couple of POEC (POEC on edge curve 1 and POEC on edge curve 2) 
   * of the next confusion curve (where the curve are the closest)
   */
   void                  GetBestConfusionPoint(CATPointOnEdgeCurve * & PointOnCurve1, CATPointOnEdgeCurve * & PointOnCurve2);

   // Tangential warning diagnostic associated to a curve solution, return TRUE is the curve solution is
   // in an instable tangential configuration
   CATBoolean            GetTangentialWarningDiagnostic() const;

   void                  SetTangentialWarningAttribute();

   // Inline function to get the software configuration
   INLINE CATSoftwareConfiguration * GetSoftwareConfiguration() const;

   // CGMReplay Mechanism
   // -------------------
public:
   const CATString     * GetOperatorId();
   CATGeoOpTimer       * GetTimer();

   CATExtCGMReplay     * IsRecordable(short & oLevelOfRuntime,
                                      short & oVersionOfStream);

   void                  WriteInput (CATCGMStream & ioStream);
   void                  WriteOutput(CATCGMStream & ioStream);

   void                  Dump       (CATCGMOutput & os);
   void                  DumpOutput (CATCGMOutput & os);
   void                  DumpOutput (CATCGMStream & ioStream,
                                     CATCGMOutput & os,
                                     int            iVersionNumber = 1);

   CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);
   CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   CATBoolean            ValidateOutput(CATCGMStream & ioStream,
                                        CATCGMOutput & os,
                                        int            iVersionNumber = 1);

private:
   CATPointOnEdgeCurve     *  CompareSolToLimits        (const CATCrvParam & w, CATCurve * iCurve, double &ioTol, CATLONG32 iIndex=0) const ;
   void                       ComputeGapPointOnEdgeCurve(const CATPointOnEdgeCurve *  iPointOnEdgeCurve, double &oGap) const ; 


private:
   // Helper functions for the replay mechanism
   CATCGMOperator::CATCheckDiagnostic CheckEdgeCurve(const short          iEdgeCurveNumber,  // 1 for the first curve, 2 for the second curve
                                                           CATCGMOutput & os) const;
   void PrintPoecData(const CATPointOnEdgeCurve * const   iPoec,
                      const CATBoolean                    iIsFirstPoec,
                      const CATLONG32                     iPointNumber,
                            CATCGMOutput                & os) const;

   // CGMReplay Mechanism
   // -------------------
protected:
   static CATString                  _OperatorId;
   static CATGeoOpTimer              _Timer;

private:
          CATIntersectionCrvCrv    * _Inter;
          CATSoftwareConfiguration * _SoftwareConfiguration;
          CATPointOnEdgeCurve      * _StartPOEC1, *_EndPOEC1;
          CATPointOnEdgeCurve      * _StartPOEC2, *_EndPOEC2;
          double                     _Tol;  // cached value of the factory function GetResolution() (so is not streamed)
          CATEdgeCurve             * _EdgeCrv1;
          CATEdgeCurve             * _EdgeCrv2;
          CATBoolean                 _TangentialWarningAttribute;
          CATBoolean                 _Reconvergence;


};

/**
* Inline function to get the software configuration
*/
INLINE CATSoftwareConfiguration * CATIntersectionEdgeCrvEdgeCrv::GetSoftwareConfiguration() const
{
   return _SoftwareConfiguration;
}

/**
* Creates an operator for intersecting two CATEdgeCurves.
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
*/
#ifdef CATIntersectionEdgeCrvEdgeCrv_KeepDeprecatedCreate
ExportedByY30C3XGG
CATIntersectionEdgeCrvEdgeCrv *    CreateIntersection (CATGeoFactory *iWhere,
                                                       CATEdgeCurve *iEdgeCurve1, CATEdgeCurve *iEdgeCurve2,
                                                       CATSkillValue iMode=BASIC );
#endif

ExportedByY30C3XGG
CATIntersectionEdgeCrvEdgeCrv * CATCreateIntersection (CATGeoFactory            *iWhere,
                                                       CATSoftwareConfiguration *iConfig,
                                                       CATEdgeCurve             *iEdgeCurve1,
                                                       CATEdgeCurve             *iEdgeCurve2,
                                                       CATSkillValue             iMode = BASIC);

/**
* Removes a CATIntersectionEdgeCrvEdgeCrv operator from memory.
*/
ExportedByY30C3XGG
void Remove (CATIntersectionEdgeCrvEdgeCrv *&iOperatorToRemove);
#endif
