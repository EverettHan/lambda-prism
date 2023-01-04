#ifndef CATDynMassProperties1D_H
#define CATDynMassProperties1D_H

// COPYRIGHT DASSAULT SYSTEMES  1999 
//
//---------------------------------------------------------------------------------------------------
// 19/01/09 NLD Ajout IdenticalParams()
// 21/01/09 NLD Avis de restriction sur la fiabilite du GetRoughLengthFromParams()
// 26/01/09 NLD Ajout de ComputeDistortionData()
//              Ajout de SOSIntegrate
// 18/04/11 NLD Utilisation de CATCGMOperatorDebug pour mesures fines de performances
// 10/11/11 NLD Documentons le fait que les longueurs rendues sont eventuellement negatives,
//              ca ne sera pas du luxe
// 28/10/15 F1Z Code clean.
//---------------------------------------------------------------------------------------------------
// Geometric Operators
#include "Y30UIUTI.h"
#include "CATDynMassProperties1D.h"
#include "CATCGMOperator.h"
#include "CATCGMOperatorDebug.h"

// Geometric Objects
#include "CATCurve.h"
#include "CATCrvParam.h"

//----------------------------------------

// Mathematics
class CATSoftwareConfiguration;

// Advanced Mathematics
class CATMathFunctionX;
class CATMathInterval;

// Geometric Object
class CATPCrvPatchAnalysis;

// Geometric Operator
class CATMassProperties1DIntegrator;

// ==================================================================================================
/**
* Class allowing to perform a global analysis on a CATCurve.
*<br>This class is not streamable. It performs conversions from curve parameter
* to length and the converse. The conversion can be time consuming, and the precision is
* the factory resolution.
*/
class ExportedByY30UIUTI CATMassProperties1D : public CATDynMassProperties1D
{
  CATCGMVirtualDeclareClass(CATMassProperties1D);
public :
   /**
   * Creates a global analyzer on a CATCurve.
   * @param iCurveToAnalyse
   * The pointer to the curve to analyze.
   */
   CATMassProperties1D(      CATSoftwareConfiguration * iSoftwareConfiguration,
                       const CATCurve                 * iCurveToAnalyse       );

   CATMassProperties1D(const CATMassProperties1D      & iOperatorToCopy       );
   CATMassProperties1D & operator=(const CATMassProperties1D& iOperatorToAffect ) ;
   
   /**
   * Destructor.
   */
   virtual ~CATMassProperties1D() ;

   //-----------------------------------------------------------------------------
   // Options (Set)
   //-----------------------------------------------------------------------------
   /**
   * Set the operator in a mode where, in the GetParamFromLength method,
   * it estimates the solution before starting the computation.
   * Better and quicker results, but the modification of comportment may
   * affect sensitive algorithms.
   */
   virtual void SetEstimateInit(const CATBoolean &iEstimate=TRUE);

   /**
   * Set the absolute length and cog error the computation can make.
   * @param iPrecision
   * The absolute error.
   */
    virtual void SetPrecision(double iPrecision);

    /**
    * Set the relative inertia error the computation can make.
    * <br> The inertia can no be computed with an absolute error for performance purpose.
    * @param iPrecision
    * The relative error.
    */
    virtual void SetRelativePrecision(double iPrecision);

   /**
   * Set the new origin for the computation.
   * @param iOrigin
   * The origin. For instance, the COG computed will be relatively to this point.
   */
   void SetOrigin(const CATMathPoint & iOrigin);

   //-----------------------------------------------------------------------------
   // Options (Get)
   //-----------------------------------------------------------------------------
   /**
   * Returns the parameter of the point at a given length (on the curve)
   * to another point.
   * @param iParam
   * The parameter of the point from which the distance is computed.
   * @param iLength
   * The length on the curve.
   * @return
   * The parameter of the point at <tt>iLength</tt> from <tt>iParam</tt>.
   */
   virtual CATCrvParam GetParamFromLength(const CATCrvParam &iParam,
                                          const CATLength   &iLength) const;
   
   /**
   * Returns the length between two points of a curve.
   * @param iParam1
   * The parameter of the first point on the curve.
   * @param iParam2
   * The parameter of the second point on the curve.
   * @return
   * The length on the curve between the two points. (algebraic length: may be negative)
   */
   virtual CATLength GetLengthFromParams(const CATCrvParam &iParam1,
                                         const CATCrvParam &iParam2) const;
   
   /**
   * Returns the length between two points of a curve with a relative precision 
   * of 1%. (NOT GUARANTEED AT ALL) (NLD210109. Garanti comme du Gourdon: parfois c'est bon)
   * @param iParam1
   * The parameter of the first point on the curve.
   * @param iParam2
   * The parameter of the second point on the curve.
   * @return
   * The length on the curve between the two points. (algebraic length: may be negative)
   */
   virtual CATLength GetRoughLengthFromParams(const CATCrvParam &iParam1,
                                              const CATCrvParam &iParam2) const;
   
   /**
   * Returns the total length of the curve.
   * @return
   * The length.
   */
   virtual CATPositiveLength GetLength() const;

   /**
   * Returns the center of gravity of the curve limited to the given parameters.
   * @return
   * The center of gravity (relatively to the origin setted).
   */
   virtual CATMathPoint GetCenterOfGravity(const CATCrvParam & iParam1,
                                           const CATCrvParam & iParam2) const;

   /**
   * Returns the inertia matrix of the curve limited to the given parameters.
   * @return
   * The inertia matrix (relatively to the origin setted).
   */
   virtual CATMath3x3Matrix GetInertiaMatrix(const CATCrvParam & iParam1,
                                             const CATCrvParam & iParam2) const;

   /**
   * Compute the mass properties informations of the curve limited to the given parameters.
   * <br> The mass properties are computed from the origin point setted to this operator.
   * @param oLength
   * The length.
   * @param oCOG
   * The center of gravity (relatively to the origin setted).
   * @param oInertia
   * The inertia matrix (relatively to the origin setted).
   * @return
   * TRUE if no issue with the computation, FALSE otherwise.
   */
   virtual CATBoolean GetMassProperties(const CATCrvParam      & iParam1 ,
                                        const CATCrvParam      & iParam2 ,
                                              double           * oLength = NULL,
                                              CATMathPoint     * oCOG    = NULL,
                                              CATMath3x3Matrix * Inertia = NULL) const;

   /**
   * Compute the mass properties informations of the curve limited to the given parameters.
   * <br> The mass properties are computed from the origin point setted to this operator.
   * <br> The retrived mass properties are not normalized.
   * @param oLength
   * The length.
   * @param oCOG
    * The true center of gravity = (oCOG[0],oCOG[1],oCOG[2])/oCOG[3], oCOG[3] is the length computed with the COG, so oCOG[3] might != oLength=GetLength();
   * @param oInertia
   * Ixx=oInertia[0], Iyy=oInertia[1], Izz=oInertia[2], Iyz=oInertia[3] , Izx=oInertia[4], Ixy=oInertia[5]
   * @return
   * TRUE if no issue with the computation, FALSE otherwise.
   */
   virtual CATBoolean GetMassPropertiesNotNormalized(const CATCrvParam & iParam1       ,
                                                     const CATCrvParam & iParam2       ,
                                                           double      * oLength = NULL,
                                                           double      * oCOG    = NULL,
                                                           double      * oInertia= NULL) const;

   //DEPRECATED -- DO NOT USE -- WILL DISAPPEAR SOON
   CATMassProperties1D(const CATCurve * iCurveToAnalyse);
   
   /**
   * @nodoc
   * NLD190109 returns 1 if identical parameters, considering null length tolerance given.
   * Computation is fast when tolerance si reasonable (not too high, not too small, for example
   * near factory resolution, and rough length computation precise enough). Otherwise
   * exact length computation is done.
   */
   int IdenticalParams(const CATCrvParam &iParam1,
                       const CATCrvParam &iParam2,
                       double iTolForNullLength) const  ;

   //-----------------------------------------------------------------------------
   // Run
   //-----------------------------------------------------------------------------
   /** @nodoc
    *  @nocgminf
    */
#ifdef CATIACGMV5R21
protected:
   CATCGMOperatorDebugDeclareRun(CATMassProperties1D,CATDynMassProperties1D);
   int RunOperator();
public:
#endif
   
#ifdef CATIACGMV5R21
   // Internal use only (CGMReplay infrastructure)
   enum Queries { UNINITIALIZED = 0, GET_PARAM_FROM_LENGTH, GET_LENGTH_FROM_PARAMS, GET_LENGTH, GET_MP};
   void SetQuery(Queries iQuery, CATCrvParam *iParam, CATCrvParam *iParam2, double *iLength, CATLONG32 * iMpQuery=NULL);
#endif

protected :
   //-----------------------------------------------------------------------------
   // Protected methods
   //-----------------------------------------------------------------------------
   virtual CATBoolean GetLengthFromParamsCanonical(const CATCrvParam & iParam1     ,
                                                   const CATCrvParam & iParam2     ,
                                                         double      & oLength     ) const;
   
   virtual void       GetParamFromLength2         (const CATCrvParam & iParam      ,
                                                   const CATLength   & iLength     ,
                                                         CATCrvParam & oReturnParam);

   //-----------------------------------------------------------------------------
   // Protected attributes
   //-----------------------------------------------------------------------------
   // Input
   // -------------------------------
   CATCurve                              * _Crv ;

   // Options
   // -------------------------------
   CATMathPoint                            _Origin;
   CATBoolean                              _EstimateInit;

   // Tolerances
   // -------------------------------
   double                                  _Resolution;
   double                                  _LocalEpsilon;
   double                                  _ToleranceRel;
   double                                  _LocalEpsilonRel;

   // Algorithm
   // -------------------------------
   CATLONG32                               _IntegrationMinDepth;
   CATSoftwareConfiguration              * _SoftwareConfiguration;
   CATBoolean                              _UseCATMathIntegration;
   CATBoolean                              _C1;
   CATPCrvPatchAnalysis                  * _Patch;
   CATMathFunctionX                      * _NormDeriv;
   mutable CATMassProperties1DIntegrator * _Integrator;

private :
   //-----------------------------------------------------------------------------
   // Private methods
   //-----------------------------------------------------------------------------
   // Class Management
   // -------------------------------
   void Init();

   // Geometry
   // -------------------------------
           void              CreateNormDeriv()                                                        const;
           void              CreateIntegrator()                                                       const;
           void              UpdateIntegrator()                                                       const;

           CATBoolean        GetParamFromLength2Split(const CATCrvParam     & iParam                ,
                                                      const CATLength       & iLength               ,
                                                            CATCrvParam     & oResult               );

   virtual void              GetParamFromLengthInner (const CATCrvParam     & iParam                ,
                                                      const CATLength       & iLength               ,
                                                            CATCrvParam     & oReturnParam          );

   virtual CATLength         GetLengthFromParamsInner(const CATCrvParam     & iParam1               ,
                                                      const CATCrvParam     & iParam2               ) const;

   virtual CATPositiveLength GetLengthInner()                                                         const;

   virtual CATBoolean        ComputeLength           (const CATMathInterval & iInterval             ,
                                                      const double            iTol                  ,
                                                            double          & oLength               ) const;

   virtual CATBoolean        ComputeCenterOfGravity  (const CATCrvParam     & iParam1               ,
                                                      const CATCrvParam     & iParam2               ,
                                                            double            oCOG               [4]) const;

   virtual CATBoolean        ComputeInertia          (const CATCrvParam     & iParam1               ,
                                                      const CATCrvParam     & iParam2               ,
                                                            double            oInertia           [6]) const;

   virtual CATBoolean        ComputeMassProperties   (const CATCrvParam     & iParam1               ,
                                                      const CATCrvParam     & iParam2               ,
                                                            double          * oLength         = NULL,
                                                            double            oCOG        [4] = NULL,
                                                            double            oInertia    [6] = NULL) const;


   //-----------------------------------------------------------------------------
   // Private attributs
   //-----------------------------------------------------------------------------
#ifdef CATIACGMV5R21
   // Buffers used for CGMReplay
   // operator infrastructure
   // -------------------------------
   Queries     _Query  ;
   mutable CATLONG32   _MPQuery;
   CATCrvParam _iParam ;
   CATCrvParam _iParam2;
   double      _iLength;
   CATCrvParam _oParam ;
   double      _oLength;
   double      _oCOG[4];
   double      _oInertia[6];

  // CATCGMOperator infrastructure
  public:
    const CATString * GetOperatorId();
    CATSoftwareConfiguration* GetSoftwareConfiguration() const;
    void Dump(CATCGMOutput& os);
    CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);
    void WriteInput(CATCGMStream  & ioStream);
    void DumpOutput(CATCGMOutput &os);
    //CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
    void WriteOutput(CATCGMStream & ioStream);
    void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os, int VersionNumber);
    CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os, int VersionNumber);
    CATBoolean ValidateLength(double iLength, CATCGMOutput& os);

  protected:
    CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
#endif
};

#endif 
