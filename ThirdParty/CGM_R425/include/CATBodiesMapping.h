//=======================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//=======================================

#ifndef CATBodiesMapping_H
#define CATBodiesMapping_H

#include "CATGMModelInterfaces.h"
#include "CATListOfCATCells.h"
#include "ListPOfCATDomain.h"
#include "CATListOfCATGeometries.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATBoolean.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATTopData;
class CATBody;
class CATCell;
class CATDomain;
class CATCellManifold;
class CATDeclarativeManifold;
class CATCellManifoldGroup;

class ExportedByCATGMModelInterfaces CATBodiesMapping
{

  public :

                    CATBodiesMapping                  ();
  virtual          ~CATBodiesMapping                  ();

  virtual void      GetBodiesToMap                    (      CATBody                       *& oReferenceBody                                       ,
                                                             CATBody                       *& oResultBody                                          ) const = 0;

  virtual void      GetEquivalentCells                (const CATCell                       *  iCellOnFirstBody                                     ,
                                                       const CATBody                       *  iFirstBody                                           ,
                                                             ListPOfCATCell                 & oListOfMappingCellsOnSecondBody                      ) = 0;
  
  // N.B : Need specific activation through the SetLogDomainMapping service
  //       // By default, equivalent domains are not accessible. 
  virtual void      GetEquivalentDomains              (const CATDomain                     *  iDomainOnFirstBody                                   ,
                                                       const CATBody                       *  iFirstBody                                           ,
                                                             ListPOfCATDomain               & oListOfMappingDomainsOnSecondBody                    ) = 0;

  // Only for LiveInfo
  virtual void      GetEquivalentCellManifolds        (const CATCellManifold               *  iCellManifoldOnFirstBody                             ,
                                                       const CATBody                       *  iFirstBody                                           ,
                                                             ListPOfCATCellManifold         & oListOfMappingCellManifoldsOnSecondBody              ) = 0;

  // Only for LiveInfo
  virtual void      GetEquivalentDeclarativeManifolds (const CATDeclarativeManifold        *  iDeclarativeManifoldOnFirstBody                      ,
                                                       const CATBody                       *  iFirstBody                                           ,
                                                             ListPOfCATDeclarativeManifold  & oListOfMappingDeclarativeManifoldsOnSecondBody       ) = 0;
   // Only for LiveInfo
  virtual void      GetEquivalentCellManifoldGroups   (const CATCellManifoldGroup          *  iCMGroupOnFirstBody                                  ,
                                                       const CATBody                       *  iFirstBody                                           ,
                                                             ListPOfCATCellManifoldGroup   &  oListOfMappingCellManifollGroupsOnSecondBody         ) = 0;



  // oMappedWithinResolution : when diagnostic is OK
  //                           - 1 : 2 bodies are mapped within the resolution
  //                           - 0 : 2 bodies are mapped with more than the resolution
  //                                 ( but with less than the tolerance given by the 
  //                                 SetTolerance method )
  enum CATMappingDiag         {  OK                          = 0 ,
                                 KO
                              };
  //                                       // W94 ------------
  enum CATCompareDiag         { COK                          = 0 ,
                                CKO
                              };
  //-----------------
  virtual CATBodiesMapping::CATMappingDiag
                    GetDiagnostic                     (      int                           *  oMappedWithinResolution                              = NULL )
    const = 0 ;

  // Output all the mapping errors and reason
  enum CATMappingErrorsReason { NotSameTree                  =  1,
                                NoMappingFound               =  2,
                                NotSameOrientation           =  3,
                                NotSameConvexity             =  4,
                                NotSameSharpness             =  5,
                                NotSameWayOfFillingSharpness =  6,
                                NotSameLyingOnInfo           =  7,
                                NotSameJunctionStatus        =  8,
                                NotSameSurface               =  9,
                                NotHSMappingFound            = 10,
                                NotSameCellRankInDomain      = 11,
                                NotImprintMappingFound       = 12,
                                NotSameNbSurfacesOnEdge      = 13,
                                NotSameFaceSupportSharing    = 14,
                                NotSameInfinite              = 15  };
#define                         BodiesMapping_MaxErrorValue    15

  virtual void      GetMappingListOfErrors            (      CATLISTP(CATGeometry)          & oGeometriesOnError                                   ,
                                                             CATLISTP(CATGeometry)          & oNearestResultGeometries                             ,
                                                             CATListOfInt                   & oErrorReason                                         , // of type CATMappingErrorsReason
                                                             CATListOfDouble                & oErrorValue                                          ,
                                                             ListPOfCATBody                *  oBodiesOnError                                       = NULL     ) const = 0;


  // Method to follow the way filling sharpness
  // -------------------------------------------
  // - If Edges of Reference Body and mapped Edges of Result Body
  //   have the same way of filling sharpness, then the returned diagnostic
  //   will be CATBodiesMapping::OK.
  // - If any Edges of Reference Body have been set to logical sharpness AND
  //   if the corresponding mapping Edges of Result Body have been computed,
  //   then the returned diagnostic will be CATBodiesMapping::KO.
  // - In all the other cases, a warning will be sent. See Errors and Warnings
  //   returned by GetMappingListOfErrors
  // - This method gives Statistics of marked Edges on iWorkingBody
  //   (iReferenceBody or iResultBody)
  virtual void      GetWayOfFillingSharpnessStatistic (      CATBody                       *  iWorkingBody                                         ,
                                                             int                            & oNumberOfMarkedSmoothEdges                           ,
                                                             int                            & oNumberOfSmoothEdges                                 ,
                                                             int                            & oNumberOfMarkedSharpEdges                            ,
                                                             int                            & oNumberOfSharpEdges                                  ,
                                                             int                            & oNumberOfEdges                                       ) const = 0 ;


  // Method to adapt the tolerance for Bodies Mapping :
  // --------------------------------------------------
  // - It is recommanded NOT TO USE this method and to map bodies with the resolution.
  // - The tolerance is limited to the interval : [ Resolution , 100 * Resolution ]
  // - Caution : for successful mapping , the size of the smallest tolological
  //   object within each body must be greater than tolerance.
  // - See GetDiagnostic method for more information
  virtual void      SetTolerance                     (const double                          & iTolerance                                           ) = 0;

  
  // Method to allow to log domains mapping  :
  // --------------------------------------------------
  // Mandatory option if user want to retrieve the equivalent domain through 
  // the service GetEquivalentDomains. 
  // By default, equivalennt domains are not accessible. 
  virtual void      SetLogDomainMapping                     (CATBoolean iActivate) = 0;

  /**
  * @nodoc
  * Method to adapt the tolerance for Bodies Mapping :
  * - the mapping tolerance will the result of the product between iMultiplyingFactor and the factory resolution
  * - It is recommanded NOT TO USE this method and to map bodies with the resolution.
  * - iMultiplyingFactor must be limited to the interval [ 1.0 , 100.0 ], otherwise an error will be thrown
  * - Caution : for successful mapping , the size of the smallest tolological
  *   object within each body must be greater than tolerance.
  * - See GetDiagnostic method for more information
  */
  virtual void      SetToleranceMultiplyingFactor    (const double                          & iMultiplyingFactor                                   ) = 0;

  // Method to set a logical mapping between a Nurbs And a SweepSurface (Default is no ) :
  // ------------------------------------------------------------------
  virtual void      SetMapSweepWithNurbs             (      CATBoolean                        iMapSweepWithNurbs                                   ) = 0;

  // Method to map only geometric reference surface type (Default is no ) :
  // ----------------------------------------------------------------------
  virtual void      SetMapGeometricRep               (      CATBoolean                        iMapGeometricRep                                     ) = 0;

  // Method to active lying on mapping
  virtual void      AddInputBody                     (      CATBody                        *  iBodyForLyingOnInfo                                  ) = 0;

  // Method to desactivate lying on check (errors of type "NotSameLyingOnInfo")
  virtual void      SetNoLyingOnCheck                (                                                                                             ) = 0;

  // Method to desactivate live check 
  virtual void      SetLiveInfoCheck                 (      int                               iCheck                                               ) = 0;

  // Method to desactivate surface type check (Default is active) (errors of type "NotSameSurface")
  virtual void      SetSurfaceTypeCheck              (      int                               iCheck                                               ) = 0;

  // Method to desactivate way of filling sharpness check (Default is active) (errors of type "NotSameWayOfFillingSharpness")
  virtual void      SetWayOfFillingEdgeSharpnessCheck(      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same number of surfaces on an edge (Default is active) (errors of type "NotSameNbSurfacesOnEdge")
  virtual void      SetCheckSameNbSurfacesOnEdge     (      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same sharpness on an edge (Default is active) (errors of type "NotSameSharpness" and "NotSameConvexity")
  virtual void      SetCheckSameSharpness            (      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same junction status on an edge (Default is active) (errors of type "NotSameJunctionStatus")
  virtual void      SetCheckSameJunctionStatus       (      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same hidden seam properties (Default is active) (errors of type "NotHSMappingFound")
  virtual void      SetCheckSameHiddenSeam           (      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same imprint properties (Default is active) (errors of type "NotImprintMappingFound")
  virtual void      SetCheckSameImprint              (      int                               iCheck                                               ) = 0;

  // Method to deactivate the check of same infinite properties (Default is active) (errors of type "NotSameInfinite")
  virtual void      SetCheckSameInfinite             (      int                               iCheck                                               ) = 0;

  // Only for GM INTERNAL use : Method to check face/edge rank in a shell/wire (Default is no ) (errors of type "NotSameCellRankInDomain")
  virtual void      CheckCellRankOnDomain            (const CATBoolean                        iCheck                                        = FALSE) = 0;

  // Only for INTERNAL use : Method to make a deep topologic analysis (Default is no )
  virtual void      CheckDeepTopoAnalysis            (const CATBoolean                        iCheck                                        = FALSE) = 0;

  // Only for GM INTERNAL use : Method to check that if 2 faces have same/different support on one body, it is the same/different also on the other body.
  // (Default is no ) (errors of type "NotSameFaceSupportSharing")
  virtual void      SetCheckSameFaceSupportSharing   (      int                               iCheck                                               ) = 0;

  virtual void      SetMappedObjects(CATGeometry* & iObjetRef, CATGeometry * & iObjectResult) = 0;

  // General check inactivation (appends a list of checks to inactivate). NLD241114
  typedef enum     {UnactivateCellsParametricMapping  = 1
                   }UnactivateCheckList;
  virtual void      ChecksUnactivate                 (const CATListOfInt                    & iChecksToUnactivate                                  ) = 0;
  //
  virtual void      Run                              (                                                                                             ) = 0;

};

// Creation method :
// -----------------
// iTopData : TopData ( versionning )
// iReferenceBody : reference body to compare
// iResultBody    : other body to compare
// iSilentMode    : = 0 trace on difference between bodies, <> 0 no trace
//
// CATCreateBodiesMapping : versionned creation method
// CreateBodiesMapping    : not versionned creation method ( always last level , used in ODT )
//

ExportedByCATGMModelInterfaces 
CATBodiesMapping *CATCreateBodiesMapping (      CATTopData       *  iTopData       ,
                                          const CATBody          *  iReferenceBody ,
                                          const CATBody          *  iResultBody    ,
                                          const int                 iSilentMode    = 0 );


ExportedByCATGMModelInterfaces 
CATBodiesMapping *   CreateBodiesMapping (const CATBody          *  iReferenceBody ,
                                          const CATBody          *  iResultBody    ,
                                          const int                 iSilentMode    = 0 );

// Destruction method
ExportedByCATGMModelInterfaces 
void                 Remove              (      CATBodiesMapping *& BodiesMapPointer);

#endif
