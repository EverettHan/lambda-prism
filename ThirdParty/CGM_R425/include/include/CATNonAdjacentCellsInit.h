//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Master class for various solving locally a fillet between 2 Cells
//=============================================================================
// Responsible: ZUS
//=============================================================================
#ifndef CATNonAdjacentCellsInit_h
#define CATNonAdjacentCellsInit_h

#include "Connect.h"
#include "CATMathDiagnostic.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATCGMNewArray.h"
#include "CATListOfInt.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATPCurve;
class CATCrvParam;
class CATSurParam;

class ExportedByConnect CATNonAdjacentCellsInit
{
  public:

    CATNonAdjacentCellsInit(      CATGeoFactory           * iFactory,
                                  CATSoftwareConfiguration* iConfig,
                            const CATLONG32                 iFilletToolType,
                                  double                    iUserRadius);

    CATCGMNewClassArrayDeclare;      // Pool allocation

    virtual                   ~CATNonAdjacentCellsInit();

    virtual CATMathDiagnostic  Run() = 0;

            void               GetStatus            (const int            iSide         ,
                                                           CATBoolean   & oStatusOnSupport);

            double             GetLastRadius        ();

    virtual void               GetResultOnFace      (const int            iSide         ,
                                                           CATSurParam  & oParamSurface ) = 0;
    virtual void               GetResultOnEdge      (const int            iSide         ,
                                                           CATPCurve   *& oPCurve       ,
                                                           CATCrvParam  & oCrvParam     ) = 0;

  protected:

            CATBoolean         Intersection               (CATPCurve   *  iPCurve1      ,
                                                           CATCrvParam  & iStartPCurve1 ,
                                                           CATCrvParam  & iEndPCurve1   ,
                                                           CATPCurve   *  iPLine        ,
                                                           CATCrvParam  & oParamOnPCurve,
                                                           CATBoolean   & oConfusion    );

            CATBoolean         ResultIntersectionFacePLine(CATPCurve   *  iPCrv         ,
                                                           CATPCurve  **  iTPCurve      ,
                                                           CATLONG32    & inbPCurve     ,
                                                           CATCrvParam *  iStartCrvParam,
                                                           CATCrvParam *  iEndCrvParam  ,
                                                           CATPCurve   *& ioPCurve      ,
                                                           CATCrvParam  & oParamOnPCurve,
                                                           CATListOfInt*  oExcludedBorders = 0 );

            CATBoolean         IsPointInsideFace           (CATSurParam & iSurParam     ,
                                                            CATPCurve **& iTPCurve      ,
                                                            CATLONG32   & inbPCurve     ,
                                                            CATCrvParam*  iStartCrvParam,
                                                            CATCrvParam*  iEndCrvParam  ,
                                                            CATListOfInt* iExcludedBorders = 0 );

  private:

    //---------------------------------
    // Data
    //---------------------------------
  protected:
    double                        _UserRadius;
    double                        _RadiusSol;
    CATLONG32                     _FilletToolType;
    CATGeoFactory*                _Factory;
    CATSoftwareConfiguration*     _Config;
    CATBoolean                    _StatusOnSupport1;
    CATBoolean                    _StatusOnSupport2;
    CATListOfInt                * _ExcludedBorders1;
    CATListOfInt                * _ExcludedBorders2;
};

#endif
