#ifndef CATCGMODTScaleManager_H
#define CATCGMODTScaleManager_H
//===================================================================
//   
// COPYRIGHT   : DASSAULT SYSTEMES 2007
//
// DESCRIPTION : Input factory scaling management for all odt types 
//
//===================================================================
// 01/08/07 NLD Creation
//              code provenant de ODTScenario methode ReadFile (PTO/FDS/NLD)
//
// Order of operations:
// - constructor
// - SetFactory()
// - ApplyScale() (this object reads environment variable to initialize XScale factor)
// - GetScaledFactory() if necessary
// - GetMathTransformation if necessary
// - ReadImage() or FindObjectFromTag()
// - GetXScaleFactor() if necessary
//
// 13/10/12 EB  Nettoyage code inutile 
//===================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATErrorDef.h"
#include "CATListOfInt.h"
#include "CATMathTransformation.h"
#include "CATPGMODTScaleManager.h"
class CATGeoFactory ;
class CATTransfoManager;
class CATError;
class CATICGMObject;

//============================================================================
//Mode de gestion de  CATCGMODTScaleManager
//============================================================================
typedef unsigned int CATCGMODTScaleManagerMode;

#define CATCGMODTScaleManager_Undefined          0xFFF
#define CATCGMODTScaleManager_Deactivated        0x000
#define CATCGMODTScaleManager_Activated          0x001

#define CATCGMODTScaleManager_Request_Scaling    0x000
#define CATCGMODTScaleManager_Request_Rotation   0x010
#define CATCGMODTScaleManager_Request_Import     0x020

#define CATCGMODTScaleManager_BasicMode          0x000
#define CATCGMODTScaleManager_ShiftMode          0x100

//
class ExportedByCATTopologicalObjects CATCGMODTScaleManager: public CATPGMODTScaleManager
  {
   public:
   // constructor
   CATCGMODTScaleManager() ;
   // destructor
   ~CATCGMODTScaleManager() ;
   // Initialize input factory
   void SetFactory(CATGeoFactory* iFactory) ;
   // Access to transfomanager
   CATTransfoManager* GetTransfoManager() ;
   // Access to transfomanager
   HRESULT            GetMathTransformation(CATMathTransformation &oMathTransfo) ;
   
   // Apply scale to elements
   int    ApplyScale (CATError*& oError);
   
   // Read output factory
   CATGeoFactory* GetScaledFactory() ;

   // Read scale ratio
   double GetScaleRatio() ;
   
   // Access to object by its tag, taking transfomanager into account, if any
   CATICGMObject* FindObjectFromTag(int iTag) ;
   
   // Access to image object
   CATICGMObject* ReadImage(CATICGMObject* iInputObject) ;
   
   
   CATCGMODTScaleManagerMode   ReadCATCGMODTScaleManagerMode();

   //===================================================================
   private:
   CATGeoFactory            * _Factory ;
   CATGeoFactory            * _ScaledFactory ;
   CATTransfoManager        * _TransfoManager ;
   CATMathTransformation      _MathTransformation ; // prevision suppression de _TransfoManager
   double                     _ScaleRatio ;
   CATCGMODTScaleManagerMode  _ScaleManagerMode ;
} ;

/**
 * @return [out, delete]
 */
ExportedByCATTopologicalObjects CATCGMODTScaleManager *CATCreateODTScaleManager();

#endif
