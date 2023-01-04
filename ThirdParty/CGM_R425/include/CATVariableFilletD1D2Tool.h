//=============================================================================
// Copyright Dassault Systemes Provence 2000-2003, all rights reserved
//=============================================================================
//
// CATVariableFilletD1D2Tool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// 23/10/2014 : Q48 : Implement X-scale in CGM-replay
// 28/08/2003 : HLN : Add GetDistanceFunction*
// 19/06/2003 : HLN : Creation
// 22/04/2021 : SME31 : Implement GetCutterDimension()
//=============================================================================
#ifndef CATVariableFilletD1D2Tool_h
#define CATVariableFilletD1D2Tool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATString.h"

class CATCGMStream;
//#include "CATCGMStream.h"
class CATCurve;
class CATCompositeLaw;
class CATMathFunctionX;

class CATFilletVariousParameters;

class CATSoftwareConfiguration;

class ExportedByConnect CATVariableFilletD1D2Tool : public CATConnectTool  
   {

   public:

      //---------------------------------------------------------------
      // Constructor
      //---------------------------------------------------------------
      CATVariableFilletD1D2Tool(CATSoftwareConfiguration   * iConfig,
                                CATCurve                   * iSpine,
                                CATCompositeLaw            * iDistanceLaw1,
                                CATCompositeLaw            * iDistanceLaw2,
                                CATCompositeLaw            * iMappingLaw1,
                                CATCompositeLaw            * iMappingLaw2,
                                CATFilletVariousParameters * iVariousParameters = NULL);
      //---------------------------------------------------------------
      // Destructor
      //---------------------------------------------------------------

      ~CATVariableFilletD1D2Tool();

      //---------------------------------------------------------------
      // Public Methods
      //---------------------------------------------------------------

      CATLONG32	GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve               *GetSpine() const;
      const CATMathFunctionX *GetDistanceFunction1() const;
      const CATMathFunctionX *GetDistanceFunction2() const;
      const CATCompositeLaw  *GetDistance1() const;
      const CATCompositeLaw  *GetDistance2() const;
      const CATCompositeLaw  *GetMapping1() const;
      const CATCompositeLaw  *GetMapping2() const;
      const CATFilletVariousParameters *GetFilletVariousParameters() const;

      // Methods to stream and unstream the tool for the CGMReplay
      void WriteInput(CATCGMStream  &ioStream);
      static CATString _OperatorId;
      const	CATString *GetOperatorId();
      CATExtCGMReplay *IsRecordable(short &LevelOfRuntime, short &VersionOfStream);

   private:

      //---------------------------------------------------------------
      // Private Data : fields
      //---------------------------------------------------------------

      CATCurve                   *_Spine;
      CATCompositeLaw            *_DistanceLaw1;
      CATCompositeLaw            *_DistanceLaw2;
      CATCompositeLaw            *_MappingLaw1;
      CATCompositeLaw            *_MappingLaw2;
      CATFilletVariousParameters *_VariousParameters;

      CATMathFunctionX           *_Composition1;
      CATMathFunctionX           *_Composition2;
   };

#endif
