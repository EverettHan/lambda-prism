// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
////
// DESCRIPTION  : 
//
//=============================================================================
// Creation May 2011
//=============================================================================
#ifndef CATTopAnalysisToolsImpl_H
#define CATTopAnalysisToolsImpl_H

#include "ExportedByCATTopologicalObjects.h"

#include "CATTopAnalysisTools.h"

#include "CATBoolean.h"
#include "CATTopDefine.h"
#include "CATErrorDef.h"
#include "ListPOfCATFace.h"
#include "CATListOfInt.h"
#include "CATSurParam.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATFace;
class CATBody;
class CATSurface;
class CATVertex;
class CATMaxOffset;


//----------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATTopAnalysisToolsImpl : public CATTopAnalysisTools
{
public:

  // Constructeur en mode Surface / Geometrique

  CATTopAnalysisToolsImpl (CATSoftwareConfiguration * ipConfig,
                           CATGeoFactory            * ipGeoFactory,
                           CATBody                  * ipBody);


  // Constructeur par copie
  CATTopAnalysisToolsImpl (const CATTopAnalysisToolsImpl & iTopAnalysisToolsImpl);
  
  // Destructeur
  virtual ~CATTopAnalysisToolsImpl(); 

  // Surcharge de l'operateur =
  CATTopAnalysisToolsImpl & operator=(const CATTopAnalysisToolsImpl& iTopAnalysisToolsImpl);



  // Methodes

  HRESULT IsSurfacePeaked(CATFace * ipFace, CATVertex *iVertex=NULL);

  HRESULT IsSurfacePeaked(CATLISTP(CATFace) & oListFace);

  HRESULT IsSurfaceTwisted(CATFace * ipFace, CATListOfDouble * iopUVTwistList = NULL, CATListOfInt * iopListLocationTwist = NULL);

  HRESULT IsSurfaceTwisted(CATLISTP(CATFace) & oListFace, short * iIsLocationFull = NULL);

  HRESULT IsSurfaceParallelTuTv(CATFace * ipFace);

  HRESULT IsSurfaceParallelTuTv(CATLISTP(CATFace) & oListFace);

  HRESULT IsFaceLocallyOffsetable(CATFace         *   ipFace,
                                  double              iFaceOffsetValue,
                                  CATMaxOffset    *   ipMaxOffset = NULL);

private:

  int IsPointAPole(CATGeoFactory            * ipFactory, 
                   CATSoftwareConfiguration * ipConfig,
                   CATSurface               * ipSurface, 
                   CATSurParam              & iSurParam, 
                   double                     iFactorReso,
                   const CATSurLimits       * iSurLim=NULL);

  int IsPointAParallelTuTv(CATGeoFactory            * ipFactory, 
                           CATSoftwareConfiguration * ipConfig,
                           CATSurface               * ipSurface, 
                           CATSurParam              & iSurParam);

  CATLONG32 GetOffsetablePatches(CATGeoFactory            *   ipFactory, 
                                 CATSoftwareConfiguration *   ipConfig,
                                 CATSurface               *   iSurface,
                                 CATSurLimits             &   iSurlimits,
                                 double                       iOffsetValue,
                                 CATSurLimits             *** oOffsetablesPatches,
                                 CATLONG32                    iNbUPatches = 5,
                                 CATLONG32                    iNbVPatches = 5);


  // Donnees
  CATSoftwareConfiguration * _pConfig;

  CATGeoFactory            * _pGeoFactory;

  CATBody                  * _pBody;
  

  // Donnees de sortie

};


#endif
