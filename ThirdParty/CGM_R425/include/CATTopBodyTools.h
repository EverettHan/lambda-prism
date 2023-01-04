#ifndef CATTopBodyTools_H
#define CATTopBodyTools_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//----------------------------------------------------------------------------
// 
//  ACCES ET USAGE INTERDIT
//
//  ******* SUPPRESSION EN COURS ******
//
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// **> UTILISER CATTopToolsCreateDomains a la place de CATTopBodyTools::BuildBody
//-----------------------------------------------------------------------------------

#include "ExportedByCATTopologicalObjects.h"

#include "CATListOfCATCells.h"
#include "CATListOfInt.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATDomain.h"
#include "CATTopBodyToolsFreezeMode.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATSoftwareConfiguration.h"
#include "CATTopDefine.h"

class CATSetOfCrvParams;
class CATGeoFactory;
class CATBody;
class CATPlane;
class CATDomain;
class CATWire;
class CATFace;
class CATEdge;
class CATVertex;
class CATCGMJournalList;
class CATMathLine;

class ExportedByCATTopologicalObjects CATTopBodyTools
{
public:

  enum FreezeMode { FreezeOff=CATTopBodyToolsFreezeOff, FreezeOn=CATTopBodyToolsFreezeOn };

  /**
  * ====================================================================================================
  * !!  BuildBody est >>STRICTEMENT INTERTDIT<< d'usage --> utiliser CATTopToolsCreateDomains !!
  * ====================================================================================================
  */
#ifdef _WINDOWS_SOURCE
__declspec(deprecated("is deprecated [R424/R2022x] - Use CallTopToolsCreateDomains instead."))
#endif
  static void BuildBody (CATGeoFactory* iFactory,
                         const CATLISTP(CATCell)& iCells, 
                         CATBody*& oBody,
                         FreezeMode iMode=FreezeOn,
                         int wantingHazardousVersion = 1);

#ifdef _WINDOWS_SOURCE
__declspec(deprecated("is deprecated [R424/R2022x] - Use CallTopToolsCreateDomains instead."))
#endif
  static void BuildBody (CATGeoFactory* iFactory,
                         const CATLISTP(CATCell)& iCells,
                         const CATListOfInt& iOrientations,
                         CATBody*& oBody,
                         FreezeMode iMode=FreezeOn,
			                   CATLISTP(CATDomain)* oCreatedDomains = NULL,
                         int wantingHazardousVersion = 1);
  
/* ==================================================================================================== */


  /**
  *------------------------------------------------------------------------
  * Miscalleanous
  *-------------------------------------------------------------------------
  */

  static void GetDomainBoundingCells(CATBody            *iBody,
	                             CATLISTP(CATCell)  &oListOfCell,
	                             short               iDimension,
	                             CATDomain          *iDomain);

  static void MergeBodies(CATGeoFactory    *   iFactory,
	                  const CATLISTP(CATBody)   & iList,
	                  CATBody                 * & oBody,
	                  FreezeMode                  iMode = FreezeOn);

  static void InvertWire(CATGeoFactory      *iFactory,
	                 CATBody            *iWireBody,
	                 CATBody            *&oBody);


  //-------------------------------------------------------------------
  //	Check if there is at least one High level Domain (domain directly 
  // federated by the Body) is empty
  //-------------------------------------------------------------------
  static HRESULT IsDomainsBodyEmpty(CATBody *piBody, CATBoolean& ioIsEmpty);

  // ultra temporaire
  static int GetInfinite    (CATBody *);

  /**
  *------------------------------------------------------------------------
  * Returns the planar surface of the unique face inside the infinite input body
  * Returns NULL if the Body isn't infinite
  * oOriPlaneVsBody is an optional argument which allows the caller to know the relative orientation of the plane in the body
  *------------------------------------------------------------------------
  */
  static CATPlane * GetInfinitePlanarBodySurface(CATBody * iBody, CATOrientation * oOriPlaneVsBody = NULL);


  /**
  *------------------------------------------------------------------------
  * Retrieves the mathematical line of the unique infinite linear edge inside the infinite input body
  * Returns TRUE only if the Body is both infinite and linear
  * oInfiniteLine is an optional argument which allows the caller to get the retrieved mathematical line
  *------------------------------------------------------------------------
  */
  static CATBoolean IsAnInfiniteLinearBody(CATBody * iBody, CATMathLine * oInfiniteLine=NULL);

  /**
  *------------------------------------------------------------------------
  * Checks if each highest cell is a linear or a polylinear edge
  * Returns TRUE only if all the highest cells of the input body are (poly)linear edges
  * TRUE implies that the local curvature is NULL everywhere on the wire body.
  * oIsAnInfiniteLinearBody is an optional argument which allows the caller to know if the body is an infinite linear body
  *------------------------------------------------------------------------
  */
  static CATBoolean IsBodyPolyLinearCompliant(CATSoftwareConfiguration * iConfig, CATBody * iBody, CATBoolean * oIsAnInfiniteLinearBody = NULL);

  /**
  *------------------------------------------------------------------------
  * Checks if at least one cell has a curved geometry (at least one non-linear edge or one non-planar face)
  *------------------------------------------------------------------------
  */
  static CATBoolean IsACurvedBody(CATSoftwareConfiguration * iConfig, CATBody* iBody);


    /**
  *------------------------------------------------------------------------
  * Checks if each faces of the input volume is planar
  * Returns TRUE only if all the highest cells of the input body are planar surfaces
  *------------------------------------------------------------------------
  */
  static CATBoolean IsAStraightBody(CATSoftwareConfiguration * iConfig, CATBody* iBody);

  /**
  *------------------------------------------------------------------------
  * Retrieves the number of discrete sub-elements (triangles, bars, points)
  * from the highest cells of a polyhedral CATBody
  * oPolyGeoDimension012 is the dimension of the highest geometries found in the body
  * equals to 0 in case of set of points, 1 in case of polycurves, and 2 in case of polymesh
  * Returns the number of found sub-elements
  *------------------------------------------------------------------------
  */
  static int GetNbPolySubElementsFromBody(CATBody *iBody, int &oPolyGeoDimension012);

  /**
  *------------------------------------------------------------------------
  *  ChainingSmart
  *-------------------------------------------------------------------------
  */

  static void ChainingSmart(CATBody *iInputBody, CATBody *iOutputBody);

  static void ChainingSmart(const ListPOfCATBody &iInputBodies, CATBody *iOutputBody);

  /**
  *------------------------------------------------------------------------
  * To be avoided
  *-------------------------------------------------------------------------
  */
  // restricted area 
  static void Inactivate    (CATBody *);
  static void ForceActivate (CATBody *);
  static CATBoolean IsWithInverseCacheLinks(CATBody *);

  // debug helpers (Do not exposed)
  static void       IsRunningTessOperator(CATBody *);
  static CATBoolean HasBeenTessellated(CATBody *);

  // debug helpers (Do not exposed)
  static CATBoolean HasBeenDetectedWithUntrivialConnectivity(CATBody *iBody, CATCell *iCell);
  static int        SoftLevelAtCompletion(CATBody *); // -1 if not detected
  static int        NbTopologyAtFreezeActivate(CATBody *); // 0  if not defined
 

  /**
  *------------------------------------------------------------------------
  * Miscalleanous (CreateFullSmartBody ... ) 
  *-------------------------------------------------------------------------
  */

  /**
  * Create Body by direct rerouting of domain (PCS simple optimisation).
  *   a kind of optimised single duplicate clonemanager 
  * <br>Limitation :  attribute (Body only) are only managed by HasClonableAttribute protocols
  * <br>Remarks : To Go further you must use more powrfull SmartDuplicate of CloneManager 
  */

  static HRESULT CreateFullSmartBody(CATSoftwareConfiguration  *   iConfiguration,
                                     CATBody                   *   iBody,
                                     CATBody                   * & oBody,
                                     const CATBoolean              iWithBoundixBox = FALSE );

  /* @nocgmitf @nodoc */
  static HRESULT ReorderAllShellsOfBody(CATBody * iBody, CATBoolean iUnDo = FALSE);


private :


  static HRESULT CreateFullSmartBodyProto(CATSoftwareConfiguration  *   iConfiguration,
                                     CATBody                   *   iBody,
                                     CATBody                   * & oBody);


  /**
  *------------------------------------------------------------------------
  * Other
  *-------------------------------------------------------------------------
  */


  static HRESULT CreateFullSmartBody(CATSoftwareConfiguration  *   iConfiguration,
                                     CATBody                   *   iBody,
                                     const CATLISTP(CATBody)   &   oBodies);

  static HRESULT CreateFullSmartBody(CATSoftwareConfiguration  *   iConfiguration,
                                     const CATLISTP(CATBody)   &   iBodies,
                                     CATBody                   * & oBody);

};


#endif
