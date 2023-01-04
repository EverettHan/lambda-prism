//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// class CATPNurbsTransfer
//==========================================================================
// May 2001   Creation                                                 PRG
//==========================================================================
//
// the function of this class is to provide the different geometrical translaters
// with a common tool that create PNurbs in V5.
// This object is supposed to centralize various actions that have to be done
// on the PNurbs to be imported.
//
// The input will be a (C0 or more continuous) Nurbs object.
//
// The output will be a set of CATPNurbs created in the model.
// This object is supposed to :
//      - to correct the parametrization if necessarly to respect the V5 criteria,
//      - to deform the shape in order to reach the objective continuity
//        thus enabling us to minimize the number of cells to be created.
// 
//-----------------------------------------------------------------------------
#ifndef CATPNurbsTransfer_h
#define CATPNurbsTransfer_h

class CATNurbsTransferInfo;
class CATGeoFactory;
class CATFrFNurbsMultiForm;
class CATPNurbs;
class CATNurbsSurfaceTransfer;
class CATSurface;
class CATSoftwareConfiguration;

#include "CATDataType.h"
#include "Interfaces.h"
#include "CATCGMVirtual.h"

class ExportedByInterfaces CATPNurbsTransfer : public CATCGMVirtual
{
  public :
    virtual ~CATPNurbsTransfer() {};
    // method to get the resulting curves.
    virtual void GetResultingPNurbs(CATLONG32&        ioNbPNurbs,
                                    CATPNurbs**& oPNurbs)=0;

    // GetDiagnostic : this method method is expected to be called if the 
    // Run method returns 2 or -1 - for 2, there is only one diagnostic that is a geometrical invalidity.
    // for -1 there may be several diagnostic, that are warnings - the translation has done but it
    // might be good to do a correction or warn the application.
    // this diagnostic can be used to enable the user to take the following decision ?
    //      - if the invalidity can be repaired, do we try to make the correction or not ?
    //      - else, do we provide the user with a graphical diagnostic explaining him 
    //      why his data are considered as invalid?
    virtual CATNurbsTransferInfo* GetNurbsTransferInfo()=0;

    // GetOptimiseContinuityDeformationRatio ( between 0. and 1. ).
    virtual double GetOptimiseContinuityDeformationRatio()=0;

    // Run : perform the translation into V5-Nurbs
    // returns 0 if the method managed to translate the geomtry.
    // returns -1 if an error has occured in the process.
    // returns 1 if the transfer has failed because of the quality of the input geometry.
    virtual CATLONG32 Run()=0;

    // ApplyGeometryCorrection : this method can be called if the diagnostic is considered
    // as repairable.
    // returns 0 if the method has managed to correct the geomtry
    // in this case, the application can call the Run method again on this objet,
    // so that the translation can success.
    // returns 1 if an error occurs / or throw an error during the reparation process.
    // returns 2 if a geometrical invalidity has been found (call the GetDiagnostic method)
    virtual CATLONG32 ApplyGeometryCorrection()=0;
};

//------------------------------------------------------------------------------ 
// transfer of a 2D-multiform.
//------------------------------------------------------------------------------

ExportedByInterfaces
CATPNurbsTransfer* CATCreatePNurbsTransfer(CATGeoFactory*              factory,
                                           CATSoftwareConfiguration * iConfig,
                                           CATFrFNurbsMultiForm* initialMultiform,
                                           CATNurbsSurfaceTransfer*    surfaceTransfer,
                                           CATNurbsTransferInfo*       transferInfo,
                                           CATSurface*                 surface);
#endif
