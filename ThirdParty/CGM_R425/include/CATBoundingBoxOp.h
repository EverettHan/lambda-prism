/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATBoundingBoxOp : Small operator to handle bounding boxes of
//                    a geometric object and implement CGMReplay
//                    capacity
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
//   /09/01      Creation                       S. Dauby
// 12/03/20 Q48  Headers etc for math versioning 
//========================================================================== 

#ifndef CATBoundingBoxOp_H
#define CATBoundingBoxOp_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSurLimits.h"
#include "CATMathBox.h"
#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATBoundingBoxOp : public CATGeoOperator
{    
public:
  virtual ~CATBoundingBoxOp();
  CATBoundingBoxOp(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATSurface * iSurf);
  void SetLimits(CATSurLimits & iSurLim);
  void GetBox(CATMathBox & oBox);

  int RunOperator();
   
private:
  CATSurface * _Surf;
  CATSurLimits _SurLim;
  CATMathBox _Box;
  CATSoftwareConfiguration * _Config;

//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
	const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & ioStream);
  virtual void WriteOutput(CATCGMStream & ioStream);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream,CATCGMOutput &os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};
#endif
