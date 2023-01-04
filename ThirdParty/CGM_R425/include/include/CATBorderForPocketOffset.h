/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATBorderForPocketOffset :
// Interface class of the CATBorderForPocketOffsetCx2.
//
//=============================================================================
// Usage notes:
// sample of use :
//
//=============================================================================
// Mar. 99  Creation                     NDN     
//=============================================================================
#ifndef CATBorderForPocketOffset_H 
#define CATBorderForPocketOffset_H

#include "CATSkillValue.h"
#include "Y30C3XGG.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

class CATPCurve;
class CATSurface;
class CATGeoFactory;
class CATCrvLimits;
class CATSurLimits;
class CATCrvParam;
class CATSurParam;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;



//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATBorderForPocketOffset  : public CATCGMVirtual
{
public :
	
	virtual                          ~CATBorderForPocketOffset() {};
	
	virtual void                     Run() =0;
	
        //you can call many times this method for a list of CATSurface.
	virtual void                     SetPreviousSurface(CATSurface * iPreviousOne) =0;
	
	//specific mode to avoid geometries that are larger than the surfaceborder itself
	//with this option, planes are NOT created.
	//by default iSurfaceMode = 0
	//in order to use this mode, iSurfaceMode = 1
	virtual void                     SetSurfaceMode (CATLONG32 iSurfaceMode) =0;

	virtual CATPCurve *              CreateRuleLine(const CATCrvParam &iParamOnInitialCrv) =0;
	
	virtual CATSurface *             GetDirectionalSurface() =0;
	
	virtual CATMathSetOfPointsND *   GetMappingForDirectionalSurface() =0;
	
	//get the corresponding SurParam on the directional surface
	//from a CrvParam on the PCurve.
	virtual void                     GetSurParamFromCrvParam(const CATCrvParam &iParam,
		CATSurParam &oParam) =0;

        //get the uv box of the projection of the pcurve on the result surface.
        virtual void                     GetUVBox(CATSurLimits &iLimits) =0;
	
	//return the sign of the determinant ( Derivative of the PCurve,
	//									 Normal to the surface,
	//									 Normal to the directional surface) at the StartParam of the PCurve.
	virtual CATLONG32                     GetOrientation() =0;
	
	//iStartLength < iEndLength
	virtual void                     ChangeLength(CATLength iStartLength, CATLength iEndLength) =0;

        //Dialog methods.
        virtual const CATPCurve * GetContactCurve(CATCrvLimits *ioLimOnContact=0) =0;
	
};


//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATBorderForPocketOffset * CreateBorderForPocketOffset(CATGeoFactory * iFactory,
													   CATPCurve     * iContact,
													   //if iLimitsOnContact==NULL, then MaxLimits is taken
													   CATCrvLimits  * iLimitsOnContact, 
													   CATAngle        iAngleWithNormal,
													   CATLength       iLength,
													   CATSkillValue iMode = BASIC);


ExportedByY30C3XGG
CATBorderForPocketOffset * CATCreateBorderForPocketOffset(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
													   CATPCurve     * iContact,
													   //if iLimitsOnContact==NULL, then MaxLimits is taken
													   CATCrvLimits  * iLimitsOnContact, 
													   CATAngle        iAngleWithNormal,
													   CATLength       iLength,
													   CATSkillValue iMode = BASIC);

ExportedByY30C3XGG
void Remove(CATBorderForPocketOffset *&iPocket);

#endif
