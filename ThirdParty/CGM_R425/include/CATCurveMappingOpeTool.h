//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATCurveMappingOpeTool:
//
//=============================================================================
// Usage notes:
//               
//=============================================================================
// Aug. 99     Creation                                       O. Bellart
// Oct. 04     Versionning Interne                            EAB
// Oct. 14     Implement X-scale in CGM-replay                Q48
// Apr. 21     Implement GetCutterDimension()                 SME31
//=============================================================================
#ifndef CATCurveMappingOpeTool_h
#define CATCurveMappingOpeTool_h

#include "Connect.h"
#include "CATConnectTool.h"

class CATSurTo2DMapping;
class CATSoftwareConfiguration;

class ExportedByConnect CATCurveMappingOpeTool : public CATConnectTool
   {
   public:

      CATCurveMappingOpeTool( CATSoftwareConfiguration * iConfig, 
                              const CATSurTo2DMapping * iMappingIn,
                              const CATSurTo2DMapping * iMappingOut);
      ~CATCurveMappingOpeTool();
      /*
      ===================================
      CATConnectTool Method :
      ===================================
      */
      CATLONG32 GetType() const; 
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;
      /*
      ===================================
      Specific methods :
      ===================================
      */
      //  retrieves   Geometrical Mapping 

      const CATSurTo2DMapping * GetMappingIn() const;
      const CATSurTo2DMapping * GetMappingOut() const;

   private:
      const CATSurTo2DMapping * _MappingIn;
      const CATSurTo2DMapping * _MappingOut; 
   };

#endif
