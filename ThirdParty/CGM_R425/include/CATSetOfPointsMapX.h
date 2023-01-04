// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle mapping between two Curves of an EdgeCurve
// The Mapping is realised using a set of Points on each Curve.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//  Mar. 99     Creation                                                 E. Guerin
//  Mar. 04 HCN Stream/UnStreamCompact(...),
//              Stream/UnStreamCompactLossAllowed(...) 
//  Jun. 04 HCN GetStreamSortingKey(...),
//              HasCommonStreamData(...),
//              CopyCommonStreamData(...) 
// 26/05/09 NLD Ajout _SenseParams, _SenseRefParams et ComputeSenses();
//              Ajout Init()
//  Jul. 09 VUC Suppression du StreamCompact
//  Aug. 11 R1Y Added GetOriginAllocation() (for comparing geometries) and
//              changed IsReconverge() to be public and constant.
// 08/11/11 NLD Ajout GetEquivalentParamGen()
// 09/11/11 NLD Ajout CATSetOfPointsMapXNonMonotonousCount()
// 02/03/15 F1Z Remove of _IsReconverge (not used).
// 17/09/15 F1Z Clean
// 30/09/16 JSX RI 448518 ajout de GetOrientationValidated donne acces a la validte du mapping
// 08/04/19 NLD Smart indent
// DD/MM/YY
//=============================================================================
#ifndef CATSetOfPointsMapX_H
#define CATSetOfPointsMapX_H

#include "CATIdentityMapX.h"
#include "CATErrorDef.h"
class CATMathSetOfPointsND;
class CATMathVector;
class CATMathPoint;

class ExportedByYP00IMPL CATSetOfPointsMapX : public CATIdentityMapX
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;
  //-------------------------------------------------------------------------
  // Constructors/Destructors
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  // Creates a CATSetOfPointsMapX between iRefCurve and iCurve, using two
  // arrays of double which are Global Params expressed on each curve.
  // The arrays must be ordered.
  // If iDuplicate=1, the arrays are duplicated.
  //-------------------------------------------------------------------------
                     CATSetOfPointsMapX                  (const CATCurve                * iRefCurve      ,
                                                          const CATCrvLimits            & iRefLimits     ,
                                                          const CATCurve                * iCurve         ,
                                                          const CATCrvLimits            & iLimits        ,
                                                          const double                    iMaxGap        ,
                                                          const CATLONG32                 iNbPoints   = 0,
                                                          const double                  * iRefParams  = 0,
                                                          const double                  * iParams     = 0,
                                                          const short                     iDuplicate  = 1);

                     CATSetOfPointsMapX                  (const CATCurve                * iRefCurve      ,
                                                          const double                    iRefLow        ,
                                                          const double                    iRefHigh       ,
                                                          const CATCurve                 * iCurve        ,
                                                          const double                     iLow          ,
                                                          const double                     iHigh         ,
                                                          const double                     iMaxGap       ,
                                                          const CATLONG32                  iNbPoints  = 0,
                                                          const double                   * iRefParams = 0,
                                                          const double                   * iParams    = 0,
                                                          const short                      iDuplicate = 1);

  //-------------------------------------------------------------------------
  // Creates a CATSetOfPointsMapX between iRefCurve and iCurve, using
  // a CATSetOfPointsND.
  //-------------------------------------------------------------------------
                     CATSetOfPointsMapX                  (const CATCurve                * iRefCurve         ,
                                                          const CATCrvLimits            & iRefLimits        ,
                                                          const CATCurve                * iCurve            ,
                                                          const CATCrvLimits            & iLimits           ,
                                                          const double                    iMaxGap           ,
                                                          const CATMathSetOfPointsND    & iPoints           ,
                                                          const short                     iRefParamFirst = 1);

                     CATSetOfPointsMapX                  (const CATCurve                * iRefCurve         ,
                                                          const double                    iRefLow           ,
                                                          const double                    iRefHigh          ,
                                                          const CATCurve                * iCurve            ,
                                                          const double                    iLow              ,
                                                          const double                    iHigh             ,
                                                          const double                    iMaxGap           ,
                                                          const CATMathSetOfPointsND    & iPoints           ,
                                                          const short                     iRefParamFirst = 1);

                                  CATSetOfPointsMapX     (const CATSetOfPointsMapX      * iMapX              );
   virtual                       ~CATSetOfPointsMapX     ();

   //-------------------------------------------------------------------------
   // Object Management
   //-------------------------------------------------------------------------
   virtual CATMapX              * Duplicate              () const;

   /**
    * Swap the _RefCurve and _Curve.
    */
   virtual void                   Invert                 ();

   virtual void                   AdjustLimits           ();

   //-------------------------------------------------------------------------
   // Set interface
   //-------------------------------------------------------------------------
   // N.B au 080419 cette méthode
   //     - n'est pas héritée de la classe mère
   //     - n'est pas derivée
   //     le iDuplicate peut venir du constructeur
   virtual void                   Set                    (const CATLONG32                 iNbPoints          ,
                                                          const double                  * iRefParams         ,
                                                          const double                  * iParams            ,
                                                          const short                     iDuplicate         = 1);

   virtual void                   Set                    (const CATMathSetOfPointsND    & iPoints            ,
                                                          const short                     iRefParamsFirst = 1);

   virtual CATMapX *              SetCurve               (const CATCurve                * iOldCurve          ,
                                                          const CATCurve                * iNewCurve          ,
                                                          const CATMathTransformation1D * iTransfo           );

   //-------------------------------------------------------------------------
   // Get interface
   //-------------------------------------------------------------------------
           void                   GetCouple              (const CATLONG32                 iIndex             ,
                                                                double                  & oRefParam          ,
                                                                double                  & oParam             ) const;

   virtual CATMapX::Type          GetType                ()                                                    const;

           short                  GetOriginAllocation    ()                                                    const;

   virtual short                  GetOrientation         ()                                                    const;

           HRESULT                GetOrientationValidated(      CATLONG32               & oRefOrientation    ,
                                                                CATLONG32               & oOrientation       ) const;

           CATLONG32              GetNbPoints            ()                                                    const;

   virtual void                   GetMappingLimits       (const CATCurve                * iCurve             ,
                                                                double                  & oLow               ,
                                                                double                  & oHigh              ) const;

   /**
    * Creates a CATMathSetOfPointsND from the CATSetOfPointsMapX.
    * The returned object must be deleted by the caller.
    */
           CATMathSetOfPointsND * CreateMathSetOfPointsND()              const;


   //-------------------------------------------------------------------------
   // Geometric method
   //-------------------------------------------------------------------------
   /**
    * Compute the MaxGap based on the set of points given.
    * Notice it will also update the _MaxGap attributes of this class.
    */
   virtual double                 ComputeMaxGap          ();

   /**
    * If possible, creates a new MapX which is simpler than the current one
    */
   virtual CATMapX              * Simplify               () const;

   /**
    * Creates CATMathFunctionX* which transforms a parameter expressed on
    * one curve to the parameter expressed on the other.
    */
   virtual CATMathFunctionX     * CreateFunctionX        (      short                     iRefCurveFirst = 1 ,
                                                                CATBoolean                iAdjustedC2    = 0,
                                                          const double                  * iDomain        = 0) const;

   virtual CATLONG32              Unextrapolate          (const CATCrvLimits            & NewLimits      ,
                                                                double                    tol2           ,
                                                                CATLONG32                 Mode           = 0);

protected:
   //-------------------------------------------------------------------------
   // Protected methods
   //-------------------------------------------------------------------------
   virtual void                   Compose                (const CATMapX                 * iMapX              ,
                                                          const CATCurve                * iCurve             );

   // Equivalent methods
   // ---------------------------
   virtual double GetEquivalentParamOnRefCurve           (const double              iParamOnCurve          ,
                                                                short               iReconvergence         ) const;

   virtual double GetEquivalentParamOnCurve              (const double              iParamOnRefCurve       ,
                                                                short               iReconvergence         ) const;

   virtual double GetApproximateEquivalentParamOnRefCurve(const double              iParamOnCurve          ,
                                                          const CATPositiveLength & iApproximateResolution ) const;

   virtual double GetApproximateEquivalentParamOnCurve   (const double              iParamOnRefCurve       ,
                                                          const CATPositiveLength & iApproximateResolution ) const;

   virtual double GetEquivalent                          (const double            * iParams                ,
                                                          const double              iParam                 ,
                                                          const double            * iEqParams              ) const;

   // Reconverge method
   // --------------------------
   virtual void                   Reconverge             (const CATCurve          * iFirstCurve                 ,
                                                          const double              iFirstPoint                 ,
                                                          const CATCurve          * iCurve                      ,
                                                                double            & oPointToCompute             ,
                                                          const double              iLow                        ,
                                                          const double              iHigh                       ,
                                                          const CATPositiveLength   iApproximateResolution = 0.0) const;

   virtual CATBoolean             ReconvergeBetter       (const CATCurve          * iFirstCurve                 ,
                                                          const double              iFirstPoint                 ,
                                                          const CATCurve          * iCurve                      ,
                                                                double            & oPointToCompute             ,
                                                          const double              iLow                        ,
                                                          const double              iHigh                       ,
                                                          const CATPositiveLength   iApproximateResolution = 0.0,
                                                                int               * CGMLevel               = NULL) const;

   virtual CATBoolean             LocalReconverge        (const CATCurve          * iFirstCurve                  ,
                                                          const double              iFirstPoint                  ,
                                                          const CATCurve          * iCurve                       ,
                                                                double            & oPointToCompute              ,
                                                          const CATPositiveLength   iApproximateResolution = 0.0 ,
                                                                int               * CGMLevel               = NULL) const;

   virtual CATBoolean             Bracket                (const double            * iParams                     ,
                                                          const double            * iEqParams                   ,
                                                          const double              iParam                      ,
                                                                double            & oEqLow                      ,
                                                                double            & oEqHigh                     ) const;

   virtual void                   UpdateLimits           ();

   // INTERNAL ONLY 
   virtual size_t                 GetDynamicMemoryBytes() const;
   virtual size_t                 GetStaticMemoryBytes() const;

private:
   //-----------------------------------------------------------------------------
   // Private Methods
   //-----------------------------------------------------------------------------
           void                   UpdateIncreasingRefParams();
           void                   ClearParams            ();
           void                   Init                   ();
           void                   ComputeSenses          (      int                 iUnStream                 =0);
           double                 GetEquivalentParamGen  (const CATCurve          * FromCurve                   ,
                                                                double            * ParamsFrom                  ,
                                                          const double              ParamFrom                   ,
                                                          const CATCurve          * DestCurve                   ,
                                                                double            * ParamsDest                  ,
                                                          const double              iLow                        ,
                                                          const double              iHigh                       ,
                                                                short               iReconvergence              ) const;

           void                   GetOrientationWithLocalUpdate
                                                         (const CATCurve          * iFirstCurve                 ,
                                                          const CATCurve          * iCurve                      ,
                                                                CATMathVector     & ioD0                        ,
                                                          const CATMathVector     & iD1                         ,
                                                                short             & oOrientation                ) const;


   //-----------------------------------------------------------------------------
   // Attributes
   //-----------------------------------------------------------------------------
   // Inputs
   double    *  _RefParams;
   double    *  _Params;
   CATLONG32    _NbPoints;
   short        _OriginAllocation;
   int          _SenseParams;
   int          _SenseRefParams;

public:

   //-------------------------------------------------------------------------
   // Streaming & Dump
   //-------------------------------------------------------------------------
   virtual CATBoolean             IsStreamable           (const CATCGMStreamVersion iTargetVersion              ,
                                                                CATBoolean        & ioReversible                ) const;

   virtual void                   Stream                 (      CATCGMStream         & Str                      );

   virtual void                   UnStream               (      CATCGMStream         & Str                      );

   virtual int                    GetStreamSortingKey    (      CATCGMStream         & Str                      );

   virtual int                    HasCommonStreamData    (const CATMapX              * ipMapXToCompare          ,
                                                                CATCGMStream         & Str                      );

   virtual void                   CopyCommonStreamData   (const CATMapX              * ipMapXToCompare          ,
                                                                int                    iSimilarityLevel         ,
                                                                CATCGMStream         & Str                      );

   virtual void                   Dump                   (      CATCGMOutput         & os                       ) const;
};


//-------------------------------------------------------------------------
// Restricted use for test and debug purpose only. NLD091111
// gives global non monotonous mapping counter
//-------------------------------------------------------------------------
extern "C" ExportedByYP00IMPL int CATSetOfPointsMapXNonMonotonousCount();
#endif
