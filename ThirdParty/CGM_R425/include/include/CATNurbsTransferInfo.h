//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// class CATNurbsTransferInfo
//==========================================================================
// May 2001   Creation                                            CCK-PRG
//==========================================================================
// This object is used in the contect of the transfer of geometry into Nurbs elements in V5.
// 
// It can be considered as an input of the transfer.
// It contains some specification information to give tothe transfer :
//      - objective continuity (C2 in V5, but we may test the import as C1),
//      - deformation tolerance allowed to reach the objective continuity,
//      - keepSegmentationMode : Do we try to surpress knots within the remaining tolerance, 
//      once we have reached the objective continuity.
//
// It can also be considered as an output of the transfer since
// it supplies the application with some information of the behaviour of the transfer.
//      - if the transfer has been processed successfully or not,
//      - if not, why an geometrical element could not be imported into V5,
//      - eventual warning that have been detected during the transfer and
//      that might be corrected.
//
// Actually this object is designed to federate the various diagnostics that 
// have been stored during the checking step.
// It enables the application to know if the element 
// can be globally repaired or not.
//
// Be carefull : 
// -------------
// The diagnostics belongs to the CATNurbsTransferInfo
// They are created by the transfer but will be deleted be the destructor of
// the CATNurbsTransferInfo object.
//-----------------------------------------------------------------------------
#ifndef CATNurbsTransferInfo_h
#define CATNurbsTransferInfo_h

#include "CATDataType.h"
#include "Interfaces.h"
#include "CATCGMVirtual.h"
class CATSoftwareConfiguration;
class CATNurbsDiagnostic;
class CATGeoFactory;

class ExportedByInterfaces CATNurbsTransferInfo : public CATCGMVirtual
{
  public :
    virtual ~CATNurbsTransferInfo(){};

    // returns 1 if we can is use to try to coorect the error or not.
    virtual CATLONG32 IsRepairable()=0; 

    virtual CATLONG32 AddDiagnostic(CATNurbsDiagnostic* diagnostic)=0;
    virtual CATLONG32 GetNumberOfDiagnostic()=0; 
    virtual CATLONG32 GetDiagnostic(CATLONG32 iNumDiag, CATNurbsDiagnostic*& diagnostic)=0;

    // Set and Get methods
    virtual void SetObjectiveContinuity(CATLONG32 objectiveContinuity=2)=0;
    virtual void SetKeepSegmentationMode(CATLONG32 keepSegmentationMode=0)=0;
    virtual void SetContinuityDeformationTolerance(double deformationTolerance)=0;

    virtual CATLONG32   GetObjectiveContinuity()=0;
    virtual CATLONG32   GetKeepSegmentationMode()=0;
    virtual double GetContinuityDeformationTolerance()=0;
};

//------------------------------------------------------------------------------
// transfer of a bipar.
//------------------------------------------------------------------------------
//Do not use - Use the CATCreate with a CATSoftwareConfiguration
ExportedByInterfaces
CATNurbsTransferInfo* CATCreateNurbsTransferInfo(CATGeoFactory* factory,
                                                 CATLONG32           objectiveContinuity,
                                                 CATLONG32           keepSegmentationMode,
                                                 double         ContinuityDeformationTolerance);

ExportedByInterfaces
CATNurbsTransferInfo* CATCreateNurbsTransferInfo(CATGeoFactory* factory,
                                                 CATSoftwareConfiguration * iConfig,
                                                 CATLONG32           objectiveContinuity,
                                                 CATLONG32           keepSegmentationMode,
                                                 double         ContinuityDeformationTolerance);
#endif


