// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// July. 97  Creation                        Catherine Eymin
//=============================================================================
#ifndef CREATESegmentation_H 
#define CREATESegmentation_H 
#include "CATGMOperatorsInterfaces.h"

#include "CATSkillValue.h"
#include "CATDataType.h"
#include "CATListOfCATCurves.h"

class CATGeoFactory;
class CATSegmentation;
class CATCurve;
class CATCrvParam;

ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
                                CATCurve       *iCurve,
								CATLONG32            NbSeg ,
								CATSkillValue mode=BASIC );
ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
								CATLISTP(CATCurve ) &iListe,
								CATLONG32            NbSeg ,
								CATSkillValue mode=BASIC );

ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
                                CATCurve       *iCurve,
								CATLONG32            NbSeg ,
								CATLONG32          &NbBreak,
								CATCrvParam      *Wpar,     
								CATSkillValue mode=BASIC );

ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
                                CATCurve       *iCurve,
								double         &Tolap ,
								CATSkillValue mode=BASIC );
ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
								CATLISTP(CATCurve ) &iListe,
								double         &Tolap ,
								CATSkillValue mode=BASIC );
ExportedByCATGMOperatorsInterfaces
CATSegmentation * CreateSegmentation( CATGeoFactory *iFactory,
                                CATCurve       *iCurve,
				double         &Tolap ,
				CATLONG32          &NbBreak,
				CATCrvParam      *Wpar,     
				CATSkillValue mode=BASIC );
ExportedByCATGMOperatorsInterfaces

void Remove( CATSegmentation *&iSegmentation);

#endif
