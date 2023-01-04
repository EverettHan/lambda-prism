// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATFrFCompositeCurveMapping:
// Interface class of Composite Curve Mapping Object.
//
//=============================================================================
//
// Usage notes:
// This class can be used as is for simple CompositeCurveMapping or derived
// in order to implement specific algorithm or capabilities.
// You must use CreatePreciseCompositeCurveMapping to create it.
// and Remove(map) to delete it !!
// No more than one mapping is built with one ccv.
//
// A parameter of the composite curve mapping is in [0.0, 1.0]
//
//=============================================================================
//   /01/98 TPG Creation                                             Tuan Phung
//   /06/99 OSN Modification inveval
//   /09/99 OB  GetTotalLength()
//   /05/01 NDN SetNbDiscretizationPoints
// 18/06/04 NLD Suppression de SetCompositeCurve()
//              Un mapping est desormais attaché à une composite curve invariante
// 23/06/04 NLD Méthodes GetProtectedUsedStatus() et SetProtectedUsedStatusFree(),
//              SetProtectedUsedStatusUsed()
// 17/11/04 JSX Ajout de Eval 3d multi dérivée
// 02/06/15 NLD Smart indent  & documentation
// 11/01/16 NLD Suppression de la visibilite des methodes
//              GetProtectedUsedStatus(), SetProtectedUsedStatusFree(), SetProtectedUsedStatusUsed()
//              (n'ont pas lieu d'etre vues de tous)
//=============================================================================

#ifndef CATFrFCompositeCurveMapping_H
#define CATFrFCompositeCurveMapping_H

#include "CATGMOperatorsInterfaces.h"

#include "CATPGMCreateFrFCompositeCurveMapping.h"
#include "CATEvalCommand.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class CATFrFCompositeCurve;
class CATFrFCCvLimits;
class CATFrFCCvParam;
class CATCrvParam;
class CATMathPoint;
class CATMathVector;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurveMapping : public CATCGMVirtual
  {
  public :

    virtual ~CATFrFCompositeCurveMapping();
    //
    //  Get Composite Curve
    //
    virtual const CATFrFCompositeCurve * GetCompositeCurve() const = 0;

    //
    //  Set Composite Curve 
    //
    //  NLD180604 virtual void SetCompositeCurve(const CATFrFCompositeCurve *) = 0;

    // Settings on mapping behaviour
    // -----------------------------
    //  (Restricted use; may have side effects on other operators 
    //  if this object is the implicit mapping associated to the composite curve)

    //  To authorize/forbid evaluation outside limits
    //  (default arguments values correspond to default behaviour with no call to this method)
    virtual void          SetMapOnCurveLimits(     CATLONG32        iAtInner         = 1,
                                                   CATLONG32        iAtBorder        = 1 ) = 0;

    //
    //  To increase the number of discretization points per CATCurve
    //  in the CompositeCurve. Default (and minimum) is 2.
    //  Big number gives a better accuracy but worse performance.
    //
    // virtual void SetNbDiscretizationPoints(CATLONG32 iNbDiscPoints) = 0;
    //

    // Information methods
    // -------------------
    //  Get borders 
    // Returns borders count and pointer on borders, this pointer must be
    // DELETED afterwards
    //
    virtual double      * GetBorders         (      CATLONG32       &oNumberOfBorders)                  const = 0 ;
    //
    //
    //  Get Composite Curve total length
    //
    virtual double        GetTotalLength     ()                                                         const = 0 ;
    //
    // Composite Curve evaluators
    // --------------------------
    virtual CATMathPoint  EvalPoint          (      double           iS         )                       const = 0;

    virtual CATMathVector EvalFirstDeriv     (      double           iS         )                       const = 0;

    virtual CATMathVector EvalSecondDeriv    (      double           iS         )                       const = 0;

    virtual CATMathVector EvalThirdDeriv     (      double           iS         )                       const = 0;

    virtual CATBoolean    Eval               (      double           iS         ,
                                                    CATEvalCommand   iCmd       ,
                                                    CATMathPoint   * oPt        ,
                                                    CATMathVector  * oDer       ,
                                                    CATMathVector  * oDer2      ,
                                                    CATMathVector  * oDer3      )                       const = 0;
    //
    // Parametric evaluators
    // ---------------------
    virtual CATCrvParam   Eval               (const double           iS         ,
                                                    CATLONG32      & oIndexCurve)                       const = 0 ;

    virtual void          Eval               (const double           iS         ,
                                                    CATLONG32      & oIndexCurve,
                                                    double         & oW         )                       const = 0;

    virtual void          EvalFirstDeriv     (const double           iS         ,
                                                    CATLONG32      & oIndexCurve,
                                                    double         & odWdS      )                       const = 0 ;

    virtual void          EvalSecondDeriv    (const double           iS         ,
                                                    CATLONG32      & oIndexCurve,
                                                    double         & od2WdS2    )                       const = 0 ;

    virtual void          EvalThirdDeriv     (const double           iS         ,
                                                    CATLONG32      & oIndexCurve,
                                                    double         & od3WdS3    )                       const = 0 ;
    //
    // Multi-parametric evaluator
    // --------------------------
    virtual void          Eval               (const double         * iS         ,
                                              const CATLONG32        iNbrOfParam,
                                              const CATEvalCommand   iCmd       ,
                                                    CATLONG32      * oIndexCurve,
                                                    double         * oW         ,
                                                    double         * odWdS      = 0,
                                                    double         * od2WdS2    = 0,
                                                    double         * od3WdS3    = 0)                    const = 0 ;
    //
    // Special parametric evaluators
    // -----------------------------
    virtual CATCrvParam   SubEval            (const double           iS         ,
                                              const CATLONG32        iIndexCurve)                       const = 0 ;

    virtual void          SubEval            (const double           iS         ,
                                              const CATLONG32        iIndexCurve,
                                                    double         & oW         )                       const = 0 ;
    virtual void          SubEvalFirstDeriv  (const double           iS         ,
                                              const CATLONG32        iIndexCurve,
                                                    double         & odWdS      )                       const = 0 ;

    virtual void          SubEvalSecondDeriv (const double           iS         ,
                                              const CATLONG32        iIndexCurve,
                                                    double         & od2WdS2    )                       const = 0 ;

    virtual void          SubEvalThirdDeriv  (const double           iS         ,
                                              const CATLONG32        iIndexCurve,
                                                    double         & od3WdS3    )                       const = 0 ;

    virtual void          SubEval            (const double         * iS         ,
                                              const CATLONG32        iNbrOfParam,
                                              const CATEvalCommand   iCmd       ,
                                              const CATLONG32      * iIndexCurve,
                                                    double         * oW         ,
                                                    double         * odWdS      = 0,
                                                    double         * od2WdS2    = 0,
                                                    double         * od3WdS3    = 0)                    const = 0 ;
    //
    // Inverted parametric evaluators
    // ------------------------------

    // specifications:
    //   CrvParam can be outside CrvLimits[iIndexCurve]
    //   in this case, result will be outside borders corresponding to curve iIndexCurve;
    //
    //   NbSol = 1; in all other cases, error raised.
    //
    virtual double        InvEval            (const CATLONG32         iIndexCurve,
                                              const CATCrvParam    *  iParam     )                      const = 0 ;

    virtual double        InvEval            (      CATLONG32         iIndexCurve,
                                              const CATCrvParam    *  iParam     ,
                                                    CATLONG32       & oNbSol     )                      const = 0 ; 

    virtual double        InvEval            (const CATLONG32         iIndexCurve ,
                                              const double            iW         )                      const = 0 ; 

    virtual double        InvEval            (      CATLONG32         iIndexCurve,
                                                    double            iW         ,
                                                    CATLONG32       & oNbSol     )                      const = 0 ;

    virtual double        InvEval            (const CATFrFCCvParam  & iCCvParam  )                      const = 0 ;

    // Multi eval with derivatives
    virtual void          InvEval            (const CATLONG32      * iIndexCurve ,
                                              const double         * iW          ,
                                              const CATLONG32        iNbrOfParam ,
                                              const CATEvalCommand   iCmd        ,
                                                    double         * oS          ,
                                                    double         * odSdW       = 0,
                                                    double         * od2SdW2     = 0,
                                                    double         * od3SdW3     = 0)                   const = 0 ;

    // Very restricted use (only for CATFrFCompositeCurve/CATFrFCompositeCurveMapping infrastructure software)
    // -------------------
    // Méthodes de gestion de l'état du mapping: libre ou reservé
    // Suppression de la visibilite, inutile, de ces methodes, NLD110116
//  virtual int           GetProtectedUsedStatus()     = 0 ;
//  virtual void          SetProtectedUsedStatusFree() = 0 ;
//  virtual void          SetProtectedUsedStatusUsed() = 0 ;

};

#endif
