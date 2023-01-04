// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATCouplingProjectionOnSurface :
// Class for coupling Projection between an EdgeCurve and a Surface
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Feb.  01 RHA Creation                                               R. Hamza
// 17/05/22 NLD Smart indent
//=============================================================================
#ifndef CATCouplingProjectionOnSurface_H
#define CATCouplingProjectionOnSurface_H

#include "Y30E3PMG.h"

#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATGeoDef.h"
#include "CATCGMVirtual.h"
#include "CATCreateCouplingProjectionOnSurface.h"

class CATCurve;
class CATPCurve;
class CATGeoFactory;
class CATSurface;
class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATMathPoint;
class CATMathDirection;
class CATSoftwareConfiguration;

class ExportedByY30E3PMG CATCouplingProjectionOnSurface   : public CATCGMVirtual
{
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATCouplingProjectionOnSurface(      CATGeoFactory            * iFactory,
                                       CATSoftwareConfiguration * iConfig,
                                       CATEdgeCurve             * iECrvFirst,
                                 const CATPointOnEdgeCurve      * iPOEC_ECrv_First,
                                       CATEdgeCurve             * iECrvSecond,
                                 const CATPointOnEdgeCurve      * iPOEC_ECrv_Second,
                                       CATSurface               * iSurface,
                                       CATSurParam              * iParam_First,
                                       CATSurParam              * iParam_Second,
                                       CATMathDirection         * iDirection = 0);

  //
  // Si on a qu'une seule EdgeCurve et un seul Poec en entree
  // La deuxieme EdgeCurve et son Poec seront identiques a la premiere.
  //
  CATCouplingProjectionOnSurface(      CATGeoFactory            * iFactory,
                                       CATSoftwareConfiguration * iConfig,
                                       CATEdgeCurve             * iECrvFirst,
                                 const CATPointOnEdgeCurve      * iPOEC_ECrv_First,
                                       CATEdgeCurve             * iECrvSecond,
                                 const CATPointOnEdgeCurve      * iPOEC_ECrv_Second,
                                       CATEdgeCurve             * iECrvBord,
                                       CATPointOnEdgeCurve      * iPOEC_Proj_First,
                                       CATPCurve                * iBord1,
                                       CATPointOnEdgeCurve      * iPOEC_Proj_Second,
                                       CATPCurve                * iBord2,
                                       CATGeoContinuity           iSharpness,
                                       CATMathDirection         * iDirection = 0);

  ~CATCouplingProjectionOnSurface();
  
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  void Run();
  
  //-----------------------------------------------------------------------
  //- Reading the results
  //-----------------------------------------------------------------------
  //
  // Returns TRUE if points are considered as coupled, FALSE else
  //
  CATBoolean GetCoupling();
  // If points are coupled and a Edge curve should be created between the two input
  // POECS, return this EdgeCurve together with the TwoPCurve or One PCurve on the Two surface.
  // 0 is returned if no such EdgeCurve exists.
  //
  // Si on est sur le deuxieme constructeur l'EdgeCurve cree si elle existe est la meme que iECrv_Bord
  // et les POECs sont les memes que iPOEC_Proj_First et iPOEC_Proj_Second.
  //
  CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd);
  //
  // Return a Pcurve in The Surface
  //
  CATPCurve * GetPCurve(CATSurface * iSurface);
  //
  // Setting method
  // If  the EdgeCurve is iECrvFirst = iECrvSecond iIndex !=0 (1 and 2)
  // Else iIndex = 0;
  //
  void SetLimits(CATEdgeCurve * iEdgeCurve, CATPointOnEdgeCurve * iStartPOEC, CATPointOnEdgeCurve * iEndPOEC,  CATLONG32 iIndex=0);
  //
  // Setting method
  // Si iECrvFirst != iECrvSecond return les Poecs issus du Vertex reliant les deux EdgesCurves.
  // Le iFirstPOEC est sur IECrvFirst et le iSecondPOEC est sur iECrvSecond
  //
  void SetGap1(CATPointOnEdgeCurve * iFirstPOEC, CATPointOnEdgeCurve * iSecondPOEC);
  //
  // Si le Wire est ferme on aura les Poecs issus du Vertex reliant le deuxieme trou.
  //
  void SetGap2(CATPointOnEdgeCurve * iFirstPOEC, CATPointOnEdgeCurve * iSecondPOEC);
  //
  // Returns TRUE if posage mode, FALSE else
  //
  void SetPosageMode (CATBoolean iPosageMode=0);
  
private:

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------

        CATGeoFactory            * _Factory;
        CATSoftwareConfiguration * _Config;
        CATEdgeCurve             * _ECrv[2];
  const CATPointOnEdgeCurve      * _StartPOEC,
                                 * _EndPOEC;
        CATSurface               * _Surface;

        CATPointOnEdgeCurve      * _StartPOEC_Proj,
                                 * _EndPOEC_Proj;
        CATSurParam              * _InputSurParam[2];
        CATEdgeCurve             * _ECrvBord;
        CATPCurve                * _Bord1,
                                 * _Bord2;
        CATMathDirection         * _Direction;
  
        CATBoolean                 _Coupling,
                                   _MergedCurveToCreate,
                                   _SimCurveToCreate;
        CATPCurve                * _OutputPCrv;
        CATEdgeCurve             * _OutputECrv;
        CATPointOnEdgeCurve      * _LimECrv1[2];
        CATPointOnEdgeCurve      * _LimECrv2[2];
        CATPointOnEdgeCurve      * _LimECrv_Bord[2];
        CATGeoContinuity           _Sharpness;
        double                     _TrouVertex1,
                                   _TrouVertex2;
        CATBoolean                 _PosageMode;
  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
  CATBoolean TestCouplingFromOneSurface();
  CATBoolean TestCouplingFromTwoSurfaces();
  CATBoolean TestCouplingFromTrouTrou();
};

#endif
