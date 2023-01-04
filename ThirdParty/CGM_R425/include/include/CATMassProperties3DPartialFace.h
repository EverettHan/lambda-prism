//===================================================================
// COPYRIGHT Dassault Systemes 2015/01/22
//===================================================================
// CATMassProperties3DPartialFace.cpp
// Header definition of class CATMassProperties3DPartialFace
//===================================================================
//
// Usage notes: Class intended to record the CalculateOnCurrentPCurve method
// in CATMassProperties3D.
//
//===================================================================
// Historic :
//   22-jan-2015 : F1Z - Creation
//===================================================================

#ifndef CATMassProperties3DPartialFace_H
#define CATMassProperties3DPartialFace_H

// Geometric Operator (FW)
#include "Y30UIUTI.h"
#include "CATGeoOperator.h"
#include "CATUtilMassProperties3D.h"

// Systems
#include "CATBoolean.h"

// Geometric Object
#include "CATPCurve.h"
#include "CATCrvParam.h"

#include "CATCGMOperatorDebug.h"

// GMModelInterface
#include "CATTopDefine.h"

// Not an attribut
// Mathematics
class CATMathPoint;
class CATMathVector;
class CATString;
class CATCGMOutput;
// Geometric Object
class CATGeoFactory;
class CATCGMStream;
// Geometric Operator (FW)
class CATMassProperties3D;
class CATGeometryPack;


//-----------------------------------------------------------------------

class ExportedByY30UIUTI CATMassProperties3DPartialFace: public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATMassProperties3DPartialFace);
public:
   // ---------------------------------------
   //              CONSTRUCTOR               
   // ---------------------------------------
   CATMassProperties3DPartialFace(CATGeoFactory        * iFactory                       ,
                                  CATMassProperties3D  * iMassOp                        ,
                                  short                  iIsNewLoop                     ,
                                  CATSide                iSide                          ,
                                  CATPCurve            * iPCurve                        ,
                                  CATCrvParam          & iPCStart                       ,
                                  CATCrvParam          & iPCEnd                         ,
                                  CATLONG32              iEdgeTag=0                     ,
                                  CATLONG32              iFaceTag=0                     ,
                                  CATBoolean             iInternalMemoryManagement=FALSE );
   virtual ~CATMassProperties3DPartialFace ();

   // ---------------------------------------
   //                SET
   // ---------------------------------------
   void SetGlobalContext(const CATMassPropertiesGlobalContext &iGlobalContext);

   // ---------------------------------------
   //                RUN
   // ---------------------------------------
   CATCGMOperatorDebugDeclareRun(CATMassProperties3DPartialFace, CATGeoOperator);
   int RunOperator();

   // ---------------------------------------
   //                RESULT
   // ---------------------------------------
   void GetResult ( double        * oVolume,
                    double        * oWetArea,
                    CATMathPoint  * oCenterOfGravity,
                    double        * oInertia,
                    double        * oVolumeError=NULL,
                    double        * oAreaError=NULL,
                    CATMathVector * oCenterOfGravityError = NULL);
   void GetResult(CATMassProperties3DInfo &oMassProperties);

   // ---------------------------------------
   //               CGMREPLAY
   // ---------------------------------------
   const CATString* GetOperatorId();
   static const CATString* GetDefaultOperatorId();
   CATSoftwareConfiguration* GetSoftwareConfiguration() const;
   CATExtCGMReplay* IsRecordable(short & iLevelOfRuntime, short &iVersionOfStream);
   void WriteInput(CATCGMStream  &oStream);
   void WriteOutput(CATCGMStream & ioStream);
   CATCheckDiagnostic CheckInput(CATCGMOutput & os);
   CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
   void Dump(CATCGMOutput& os);
   void DumpOutput(CATCGMOutput &os);
   void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os, int VersionNumber);
   CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os, int VersionNumber);
   static CATMassProperties3D* ReadMassOperator(CATCGMStream &iStream, const short iVersionOfStream ,
                                                 CATGeometryPack* &oGeoPack );

private:
   // ---------------------------------------
   //                METHODS
   // ---------------------------------------
   void WriteGeoAndMassOperator(CATCGMStream &oStream);
   CATString BuildAndPrintIntegrationPlane();
   void DisplayMassPropertiesComputationInformation(CATCGMOutput &os);
   void DisplayPCurveLimits();

   // ---------------------------------------
   //               ATTRIBUTS
   // ---------------------------------------
   // Inputs (constant)
   // ------------------
   CATMassProperties3D          * _MassOp;
   short                          _IsNewLoop;
   CATSide                        _Side;
   CATPCurve                    * _PCurve;
   CATCrvParam                    _PCStart;
   CATCrvParam                    _PCEnd;
   CATBoolean                     _InternalMemoryManagement;
   CATLONG32                      _EdgeTag;
   CATLONG32                      _FaceTag;

   // Options
   // -----------------
   CATMassPropertiesGlobalContext _GlobalContext;

   // Output
   // ------------------
   CATMassProperties3DInfo        _MassPropertiesInfo;

};

//-----------------------------------------------------------------------

#endif
