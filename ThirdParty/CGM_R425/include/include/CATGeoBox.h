// COPYRIGHT DASSAULT SYSTEMES 2020
//=============================================================================
//=============================================================================
// March. 2020   Creation                                     S.Markett
//=============================================================================

#ifndef CATGeoBox_H
#define CATGeoBox_H

class CATMathCombinationXY;
class CATMathSystemXYc;

#include "CATMathBox.h"
#include "CATGeoFace.h"
#include "CATMathDirection.h"
#include "CATPGMGeoBox.h"

class CATGeoBox : public CATPGMGeoBox
{
public:

    CATGeoBox(CATGeoFactory * iFactory, CATSoftwareConfiguration *iConfig, const CATMathBox &iBox, const CATLISTP(CATGeoFace) &iGeoFaces);
    CATGeoBox(CATGeoFactory * iFactory, CATSoftwareConfiguration *iConfig, const CATMathBox &iBox, CATPGMGeoFace **iGeoFaces, CATLONG32 iNbFaces);

    ~CATGeoBox();
 
    CATPGMGeoBox** Subdivide();

    void Intersect(CATMathSetOfPointsND **&ioIntPoints);
    void Intersect(const CATMathLine &iLine, CATMathSetOfPointsND *&ioIntPoints);

private:
    CATBoolean IsEmpty();

    CATGeoFactory * _Factory;
    CATSoftwareConfiguration *_Config;

    CATMathBox _Box;
    CATLISTP(CATGeoFace) _GeoFaces;

    CATMathCombinationXY * _fc1,* _fc2;
    CATMathSystemXYc * _sysXY;

    static CATMathDirection _LightLine[13];
};



CATGeoBox *CreateGeoBox(CATGeoFactory * Factory,      
                       CATSoftwareConfiguration * iConfig,
                       const CATMathBox &iBox, 
                       CATPGMGeoFace **iGeoFaces,
                       CATLONG32 iNbFaces);



#endif

