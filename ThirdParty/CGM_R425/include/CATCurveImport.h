/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2003
//==========================================================================
//
// CATCurveImport :
//
// fev. 2003 Creation																							PRG
//
//==========================================================================
//
// This class is first designed to enable interfaces applications
// to import any kind of curve into a V5 file (or container).
//
// The user is expected to create in a separate temporary factory a curve (CATCurve) that
// represents the element to be transfered. Since it is a V5 element,
// it already corresponds to a V5 type. Hence, it means the interface application
// has already performed a certain work to identify this kind of element and creating 
// it as a V5 type of element. However, for several reasons, any kind of curve is not 
// necessarily V5-valid. Catia V5 impose certain conditions on geometry continuity 
// and parametrisation so that any NurbsSurface or any Pcurve can not be used in V5.
// If we say it otherwise, one can create some geomtry in a V5-file, but this creation
// or existence cretirium does not guarantee that this element can be used by CATIA 's
// geometrical operators.
//
// For several reasons, geometry in V5 is supposed to be C2. C1 geometry, or a part of it 
// might be accepted in the future but geometrical operators will accept geometry that is 
// as continuous as possible. Then geometrical operators expect parametrization
// to be close to the curvilinear parametrization. Moreover geometry is supposed to 
// satisfy quality criterion :
//			- avoid null tangents,
//			- avoid micro-arcs or micro-patches,
//			- no cups,
//			- no twist,
//			- consistant data (numerical stable data), ...
//
//	Due to these reasons, the geometrical import will perform some treatements :
//			- to give the geometry an acceptable parametrization,
//			- to correct it so that it respects quality contidions,
//			- to make it as continuous as possible thanks to several ways of deformation,
//      - and to cut it into continuous new elements
//
//	This process may also include other geometrical treatment :
//			- Many of the transferred curves represent edge bounding faces (lying on surfaces). 
//			This makes things more complicated. Indeed, it enables us to understand that
//			the cutting of the initial surfaces into continuous new surfaces, or its representation
//			or correction will have direct effects on the import the PCurves that are lying on.
//			It leads to a certain synchronization process between migration data.
//	    - edge of faces may be defined as 3D curves related to a surface. This kind
//	    of PCurve is not acceptable in V5. Hence the 3D curve is laid down or projected 
//			on the surface and we get a pcurve (CATPCurve), which is mathematically defined 
//			on the Surface.
//			- Hence, the user understand this geometrical transfer is not a simple transfer.
//			To make it as simple as possible, we defin a certain standard to make it that 
//			would be the default or automatical mode. But to answer special needs or requirements,
//      we offer options tools that enables the user to choose special parameters or treatment.
//			- Moreover, the transfer may fail some time because the input data does not meet
//			CATIA V5 quality requirements. Hence we supply the application an error diagnostic,
//			so that invalid geometry can be displayed or located to the user.
//			- Finally, we would like to add a way to communicate with the application/or user 
//			so that a correction might be asked and tried as a post-processing.
//			
//==========================================================================
#ifndef CATCurveImport_H
#define CATCurveImport_H

#include "Interfaces.h"

class CATGeoFactory;
class CATSurfaceImport;
class CATCurve;
class CATNurbsTransferInfo;
class CATNurbsCurveTransfer;
class CATPNurbsTransfer;

#include "CATCrvLimits.h"

#include "CATGeoOperator.h"

//-----------------------------------------------------------------------------
class ExportedByInterfaces CATCurveImport : public CATGeoOperator
{
  public :
		CATCurveImport(CATGeoFactory* factory):CATGeoOperator(factory){};
  virtual ~CATCurveImport(){};

	virtual int Run()=0;

	virtual void SetSurfaceImport(CATSurfaceImport* surfaceImport)=0;

	virtual void GetResultingCurves(CATLONG32&       nbResultingCurves,
																	CATCurve**& resultingCurves)=0;

	//---------------------------------------------------------------------------------------
	// both following methods may be usefull in the case of non canonical geometries transfer :
	// CATNurbsCurve or CATPNurbs.
	//---------------------------------------------------------------------------------------
	// This method will help to specify the NurbsTransfer specification at the beginning.
	// and enable us to get tranfer information (reason of the failure, geometrical invalidity, ...)
	virtual void SetNurbsTransferInfo(CATNurbsTransferInfo* nurbsTransferInfo) = 0;

	// This method enables us to supply other components with information
	// linked to the geometrical transfer.
	// If the Run method fails, then this method might enable us to run a correction
	// process and finally make the transfer success.
	virtual void GetNurbsTransfer(CATNurbsCurveTransfer*& nurbsCurveTransfer) = 0;
	virtual void GetNurbsTransfer(CATPNurbsTransfer*& pNurbsTransfer) = 0;
};

CATCurveImport* CATCreateCurveImport(CATSoftwareConfiguration * iConfig,
                                  CATCurve* initialCurve, // it does not necessarily belong to the targetFactory
																	CATCrvLimits& crvLimits,
																	CATGeoFactory* targetFactory);
#endif













