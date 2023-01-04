// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATExtrapolSurfaces :
//  Operator to extrapol enought two surfaces in order to make them
//  intersecting. CGM USE ONLY!
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jul. 00  Creation                          R. Hamza / P. Sebah
//=============================================================================

#ifndef CATExtrapolSurfaces_H
#define CATExtrapolSurfaces_H 

#include "Y30UIUTI.h"

#include "CATCGMOperator.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATCreateExtrapol.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

class CATGeoFactory;
class CATSurface;
class CATLine;
class CATSurParam;
class CATSurLimits;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATExtrapolSurfaces : public CATCGMOperator {
  public :
  //
  //-----------------------------------------------------------------------
  //- Constructor-destructor
  //-----------------------------------------------------------------------
  //

   CATExtrapolSurfaces (CATGeoFactory * iFactory,
                        CATSoftwareConfiguration * iConfig,
                        CATSurface * iSurface0, CATSurLimits * iLimits0,
                        CATSurface * iSurface1, CATSurLimits * iLimits1);

   //Do not use
   CATExtrapolSurfaces (CATGeoFactory * iFactory,
                        CATSurface * iSurface0, CATSurLimits * iLimits0,
                        CATSurface * iSurface1, CATSurLimits * iLimits1);
                  
  ~CATExtrapolSurfaces ();
  //
  // Launches the operator 
  //
  int RunOperator ();
 //
  // Returns the new extrapolated limits
  //
  void GetLimits (CATSurLimits & oLimits0, CATSurLimits & oLimits1);
private : 
  //
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  //
  CATSurface   *_SurfRep[2]; 
  CATSurLimits *_Limits[2], *_LimitsOut[2];
  CATLine      *_Line;
  CATLONG32 _first, _second, _ExtrapolV, _IsFirstPlanar;   
  double _OPlane[3], _IPlane[3], _JPlane[3], _KPlane[3];
  double _UMin[2], _VMin[2], _UMax[2], _VMax[2];
  double _W[3];
  CATSoftwareConfiguration * _Config;
  //
  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
  //
  void RunOnPlane (); 
  void RunOnPlaneSurface (); 
  double IntersectLineSurface (double iOr[3], double iW[3]);
  double IntersectLinePlane   (double iOr[3], double iW[3]);
  void GetDirection (CATSurParam & iUV, CATLONG32 iV);

//========================================================================
// CGMReplay Implementation - VSJ Creation
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  virtual const CATString * GetOperatorId();
  virtual CATGeoOpTimer * GetTimer();
  virtual CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  virtual void WriteInput(CATCGMStream  & Str);
	virtual void Dump( CATCGMOutput& os ) ;
  virtual void WriteOutput(CATCGMStream & Str);
	virtual void DumpOutput(CATCGMOutput & os) ;
	virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
	virtual CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

};
//
// Create and remove 
//
ExportedByY30UIUTI CATExtrapolSurfaces * CreateExtrapolSurfaces (CATGeoFactory * iFactory,
                                                                 CATSurface * iSurface0, CATSurLimits * iLimits0,
                                                                 CATSurface * iSurface1, CATSurLimits * iLimits1,                                                        
                                                                 CATSkillValue iMode=BASIC);

ExportedByY30UIUTI void Remove (CATExtrapolSurfaces * iCanonicOper);
#endif







