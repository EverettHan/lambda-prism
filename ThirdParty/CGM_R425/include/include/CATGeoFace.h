#ifndef CATGeoFace_H
#define CATGeoFace_H

#include "CATGeoOperator.h"
#include "CATFace.h"
#include "CATListValCATSurParam.h"
#include "CATSurParam.h"
#include "CATGeoOpDebug.h"
#include "CATSurLimits.h"
#include "CATListOfCATSurLimits.h"
#include "CATPGMGeoFace.h"


class Voxel3D;
class CATMathFunctionXY;
class CATPositionPtLoop;
class CATGeoFaceLimitTree;


class CATGeoFace : public CATPGMGeoFace
{
public:
    /** @nodoc @nocgmitf */
    CATGeoFace(CATGeoFactory * iFactory, CATSoftwareConfiguration *iConfig, CATFace* iFace, CATLISTP(CATCell) & iEdgeList, CATLONG32 nbInnerLoops, CATLISTP(CATCell) * iInnerEdges, CATOrientation iFaceInShell);

    ~CATGeoFace();

    /** @nodoc @nocgmitf */
    CATSurface* GetSurface();

    /** @nodoc @nocgmitf */
    const CATSurLimits * GetLimits();

    /** @nodoc @nocgmitf */
    const CATMathBox * GetBox();

    /** @nodoc @nocgmitf */
    CATLISTV(CATSurParam) * GetSamplePoints();

    /** @nodoc @nocgmitf */
    CATBoolean ContainsPoint(const CATSurParam & iPoint);

    /** @nodoc @nocgmitf */
    void SamplePoints(double iUVRes);

    /** @nodoc @nocgmitf */
    void GetEquation(const CATMathFunctionXY * & oFx,
                     const CATMathFunctionXY * & oFy,
                     const CATMathFunctionXY * & oFz);

    /** @nodoc @nocgmitf */
    void EvalNormal(const CATSurParam      & iParam ,
                          CATMathDirection & ioNormal);

    /** @nodoc @nocgmitf */
    CATBoolean IsIntersecting(const CATMathBox &iBox);

    /** @nodoc @nocgmitf */
    void GetIntersectingLimits(const CATMathBox &iBox, CATLISTP(CATSurLimits) & ioLimits);

    /** @nodoc @nocgmitf */
    GEOPDEBUG_CMD(void Debug_StartCountingContainsPoint());

    /** @nodoc @nocgmitf */
    GEOPDEBUG_CMD(void Debug_EndCountingContainsPoint(CATString iString));

private:

    CATBoolean ContainsPointInner(const CATSurParam & iPoint);
    CATBoolean ContainsPointOuter(const CATSurParam & iPoint);

    void ComputeInnerBox();
    GEOPDEBUG_CMD(void Debug_PrintSamplePoint(const CATSurParam& sp) const);

    CATGeoFactory * _Factory;
    CATSoftwareConfiguration *_Config;

    CATOrientation _SurfaceOrientation;
    CATSurface* _Surface;
    const CATSurLimits *_Limits;
    const CATMathBox * _Box;
    CATGeoFaceLimitTree *_LimitTree;
    CATLONG32 _NbCrvs;
    const CATPCurve ** _PCrv;
    CATCrvParam * _StartParam;
    CATCrvParam * _EndParam;

    CATLONG32  _NbInnerLoops, _NumberInnerCurves;
    CATLONG32 * _NbInnerCrvs;
    const CATPCurve *** _InnerPCrv;
    CATCrvParam ** _InnerStartParam;
    CATCrvParam ** _InnerEndParam;
    CATSurLimits *_InnerLimits;

    CATPositionPtLoop * _OuterLoop;
    CATPositionPtLoop ** _InnerLoops;

    CATLISTV(CATSurParam) _SamplePoints;

    const CATMathFunctionXY *_fxy[3];

    const CATSurLimits *_InsideLimits;

    GEOPDEBUG_INIT(CATLONG32 _DebugContainsPointCounter);

};


#include "CATLISTPP_Clean.h"
#define CATLISTPP_Append
#include "CATLISTPP_Declare.h"

CATLISTPP_DECLARE( CATGeoFace)

#endif
