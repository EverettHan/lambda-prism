#ifndef CATCGMComputeAngle_H
#define CATCGMComputeAngle_H

// COPYRIGHT DASSAULT SYSTEMES 1998

#include "ExportedByCATCGMGeoMath.h"
class CATTolerance;
// 18/01/08 NLD Methode CATCGMComputeAngleWithScale avec iScalePower en argument
//              Ajout macro ComputeAngleScaleSafe()
//---------------------------------------------------------------------------
// ComputeAngle (pour les objets periodiques):
//    returns Param  between Start and Start + Period
//---------------------------------------------------------------------------
void ExportedByCATCGMGeoMath CATCGMComputeAngleScaleSafe (const CATTolerance &TolObject,
              double iParam, double iStart, double iPeriod,double &oNewParam);

void ExportedByCATCGMGeoMath CATCGMComputeAngleScaleOff  (const CATTolerance &TolObject,
              double iParam, double iStart, double iPeriod,double &oNewParam);
//---------------------------------------------------------------------------
// Deprecated: migration to do on one of the previous definition
//---------------------------------------------------------------------------
void ExportedByCATCGMGeoMath CATCGMComputeAngleDeprecated (
              double iParam, double iStart, double iPeriod,double &oNewParam);
              
//---------------------------------------------------------------------------
// ComputeMaxAngles (for periodic objects)
//    returns MaxLimits that include current limits
//---------------------------------------------------------------------------
void ExportedByCATCGMGeoMath CATCGMComputeMaxAnglesScaleSafe(const CATTolerance &iTolObject, 
                               double iStart, double iEnd, double iPeriod, 
                               double &oNewStart, double &oNewEnd) ;

void ExportedByCATCGMGeoMath CATCGMComputeMaxAnglesScaleOff (const CATTolerance &iTolObject, 
                               double iStart, double iEnd, double iPeriod, 
                               double &oNewStart, double &oNewEnd);
//---------------------------------------------------------------------------
// Deprecated: migration to do on one of the previous definition
//---------------------------------------------------------------------------
void ExportedByCATCGMGeoMath CATCGMComputeMaxAnglesDeprecated (const CATTolerance &iTolObject, 
                               double iStart, double iEnd, double iPeriod, 
                               double &oNewStart, double &oNewEnd) ;

#endif
