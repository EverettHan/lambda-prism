#ifndef CATIPGMFrFMovingFrame_h_
#define CATIPGMFrFMovingFrame_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMFrFObject.h"
#include "CATMovingFrameType.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATCurve;
class CATFrFCCvParam;
class CATFrFCompositeCurve;
class CATFrFCompositeCurveMapping;
class CATFrFTopologyCallBacks;
class CATGeoFactory;
class CATMathAxis;
class CATMathDirection;
class CATMathInterval;
class CATMathPlane;
class CATMathPoint;
class CATMathTransformation;
class CATMovingFrameStruct;
class CATSoftwareConfiguration;
class CATFrFCoupling; // Not interfaced for the moment

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFMovingFrame;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMFrFMovingFrame: public CATIPGMFrFObjectVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFMovingFrame();

  // Type
  virtual       CATBoolean             IsATypeOf                (      CATMovingFrameType     iType             ) const = 0;
  virtual       int                    GetMovingFrameType       ()                                                      = 0;

  // Factory (?)
  virtual       void                   SetFactory               (      CATGeoFactory       *  iFactory          )       = 0;

  // Spine
  virtual       void                   SetCcvMasterGuide        (      CATFrFCompositeCurve*  iSpine            )       = 0;
  virtual       CATFrFCompositeCurve * GetCcvMasterGuide        (                                               ) const = 0;

  virtual       void                   SetNumDominantGuide      (      CATLONG32              iNumDominantGuide )       = 0;
  
  // ViewingDirection
  virtual       void                   SetViewingDirection      (const CATMathDirection     & iViewingDirection )       = 0;
  virtual const CATMathDirection     * GetViewingDirection      (                                               )       = 0;
  // (Restricted use)
  virtual       void                   GetLocalViewingDirection (      int                    iNumImposedDomain ,
                                                                       CATMathDirection     & oViewingDirection )       = 0;
  
  // Data
  virtual       CATMovingFrameStruct   GetMFStruct              (                                               ) const = 0;


  // Smooth
  //----------------
  // Option 0 : inactive, 1: standard, 2: fixed tangents
  virtual       void                   SetSmoothOption          (      CATLONG32              iOption           )       = 0;

  virtual       void                   SetSmoothAngleThreshold  (      double                 iAngle            )       = 0;

  virtual       CATLONG32              GetSmoothOption          (                                               ) const = 0;

  virtual       double                 GetSmoothAngleThreshold  (                                               ) const = 0;

  // Domain (s)
  //-----------
  // Gestion de plusieurs domaines:
  // Cela permet de gerer une spine C1(voir C0)
  // en n evaluant que sur des elements C2

  virtual       void                  SetMovingDomain           (      CATMathInterval     *  iDomain           )       = 0;
  virtual const CATMathInterval     * GetMovingDomain           (                                               ) const = 0;
  virtual       CATMathInterval     * GetOneDomain              (      CATLONG32              iIndex            ) const = 0;

  virtual       double                GetTotalLength            (                                               )       = 0;

  virtual       CATLONG32             GetNumberOfDomains        (                                               ) const = 0;
 
  virtual       void                  SetDomains                (      CATMathInterval     *  iDomains          ,
                                                                       CATLONG32              iNbDomains        ,
                                                                       CATLONG32           *  iCrvIndexLow      ,
                                                                       CATLONG32           *  iCrvIndexHigh     )       = 0;
  virtual       void                  SetWorkingDomain          (      CATLONG32              iIndex            )       = 0;
  virtual       CATLONG32             GetWorkingDomain          (                                               ) const = 0;

  // Compute the domain by calculation of min distance
  // between 2 points and the MasterGuide
  virtual       void                  ComputeMovingDomain       (      CATGeoFactory       *  iFactory          ,
                                                                       CATMathPoint         & iStartPt          ,
                                                                       CATMathPoint         & iEndPt            )       = 0;

  // Parametrisation from the MovingFrame to thespine is defined 
  // by a Coupling; otherwise by a Mapping.
  virtual       void                  SetCoupling               (      CATFrFCoupling      *  iCoupling         )       = 0;
  
  // Parametric Coupling
  virtual       void                  IsParametric              (                                               )       = 0;

  // Get spine plane if all spine curves are pcurves on same plane
  virtual       CATBoolean            GetSpinePlane             (      CATMathPlane         & oPlan             )       = 0;

  // Traitement C0
  virtual       void                  SetExtrapolatedConnexions (      CATListOfInt        *  iExtrapolatedConnexions)  = 0;

  // Traitement C1
  virtual       void                  GetMvFC1Param             (      CATListOfInt         & C2Dom             ,
                                                                       CATListOfDouble      & C2Param           ) const = 0;

  // Mapping 
  // Do not use
  virtual CATFrFCompositeCurveMapping *GetMapping() = 0;

  //------------------
  //  Pseudo Operators
  //------------------
  // iParam[0 1] in MovingDomain

  // From iParam to spine parametrisation (and invert)
  virtual       void                  EvalOnSpine               (      double                 iParam            ,
                                                                       CATFrFCCvParam       & oParam            )       = 0;
  virtual       void                  InvEvalOnSpine            (const CATFrFCCvParam       & iParam            ,
                                                                       double               & oParam            )       = 0;


  // Get Axis System of the Moving Frame

  virtual       void                  GetAxisSystem             (      double                 iParam            ,
                                                                       CATMathAxis          & oAxis             )       = 0;
  virtual       void                  GetAxisSystem             (const CATFrFCCvParam       & iParam            ,
                                                                       CATMathAxis          & oAxis             )       = 0;

  // iAxis[12], idAxis[12], id2Axis[12]
  virtual       CATBoolean            EvalAxis                  (      double                 iParam            ,
                                                                       double              *  iAxis             ,
                                                                       double              *  idAxis            = NULL,
                                                                       double              *  id2Axis           = NULL) = 0;
  // Do Not use
  virtual       void                  GetAxisSystem             (      double                 iParam            ,
                                                                       CATMathPoint         & oOrigin           ,
                                                                       CATMathDirection     & oXAxis            ,
                                                                       CATMathDirection     & oYAxis            ,
                                                                       CATMathDirection     & oZAxis            )       = 0;


  // Transformation Matrix from Global to Local Axis System
  virtual      CATMathTransformation* TransformGlobalToLocal    (const double                 iParam            )       = 0;
  virtual      CATMathTransformation* TransformLocalToGlobal    (const double                 iParam            )       = 0;

  // Get Section Plane
  virtual       CATMathPlane        * GetSectionPlane           (      double                 iParam            )       = 0;

  // Get Origin
  virtual       CATMathPoint          EvalOrigin                (      double                 iT                )       = 0;

  // Eval Origin and Plane Normal
  // iP[3] & iN[3] mustn't be NULL
  virtual       CATBoolean            EvalNormal                (      double                 iParam            ,
                                                                       double              *  iP                ,
                                                                       double              *  iN                ,
                                                                       double              *  idP               = NULL,
                                                                       double              *  idN               = NULL,
                                                                       double              *  id2P              = NULL,
                                                                       double              *  id2N              = NULL) = 0;


  // Project Point on Spine
  // ----------------------
  // Return the global parameter on the spine which defines
  // a plane including PointOnGuide.
  
  // Return only one solution
  // oParam
  virtual       double                Project                   (      CATGeoFactory       *  iFactory          ,
                                                                 const CATMathPoint         & iPointOnGuide     ,
                                                                       CATLONG32            & oNbSol            )       = 0;
  // Return only one solution 
  // oAxis (is the MovingFrame)
  virtual       void                  Project                   (      CATGeoFactory       *  iFactory          ,
                                                                 const CATMathPoint         & iPointOnGuide     ,
                                                                       CATMathAxis          & oAxis             ,
                                                                       CATLONG32            & oNbSol            )       = 0;

  // Return all solutions
  // odouble
  virtual       void                  Project                   (      CATGeoFactory       *  iFactory          ,
                                                                 const CATMathPoint         & iPointOnGuide     ,
                                                                       CATLONG32            & oNbSol            ,
                                                                       double              *& oSolutionParams   )       = 0;
  // Return all solutions
  // oCCVParam
  virtual       void                  Project                   (      CATGeoFactory       *  iFactory          ,
                                                                 const CATMathPoint         & iPointOnGuide     ,
                                                                       CATLONG32            & oNbSol            ,
                                                                       CATFrFCCvParam      *& oSolutionParams   )       = 0;


  // Return all solutions on one specified curve of the spine
  // projection on one spine's crv
  // we specify merge tolerance with extremities for the project operator
  // to avoid snapping
  virtual       void                  Project                   (      CATGeoFactory       *  iFactory         ,
                                                                 const CATMathPoint         & iPointOnGuide    ,
                                                                       CATLONG32            & oNbSol           ,
                                                                       double              *& oSolutionParams  ,
                                                                       CATLONG32              iGuideIndex      ,
                                                                       double                 iTolerance       )        = 0;


  virtual       void                  SetFrFTopologyCallBacks   (      CATFrFTopologyCallBacks*  iFrFTopologyCallBacks) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFMovingFrame(); // -> delete can't be called
};

#endif /* CATIPGMFrFMovingFrame_h_ */
