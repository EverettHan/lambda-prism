#ifndef CATPGMTopBodyTools_h_
#define CATPGMTopBodyTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATTopBodyToolsFreezeMode.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATTopDefine.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATSetOfCrvParams;
class CATVertex;
class CATWire;
class CATSoftwareConfiguration;
class CATPlane;
class CATMathLine;
class CATLISTP(CATBody);
class CATLISTP(CATDomain);
class CATLISTP(CATCell);

class ExportedByCATGMModelInterfaces CATPGMTopBodyTools
{
public:
  /**
  *-------------------------------------------------------------------------------------
  * ## BuildBody est interdit d'usage !! --> utiliser CATIPGMTopToolsCreateDomains
  *-------------------------------------------------------------------------------------
  
  /* =================================================
             -- REMOVED - W13 by QF2 -- 
     =================================================  
  static void BuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode = CATTopBodyToolsFreezeOn,
    int wantingHazardousVersion = 1);

  static void BuildBody(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOrientations,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode = CATTopBodyToolsFreezeOn,
    CATLISTP(CATDomain) *oCreatedDomains = NULL,
    int wantingHazardousVersion = 1);
  */

  /**
  *------------------------------------------------------------------------
  * Miscalleanous
  *-------------------------------------------------------------------------
  */
  static void GetDomainBoundingCells(
    CATBody *iBody,
    CATLISTP(CATCell) &oListOfCell,
    short iDimension,
    CATDomain *iDomain);

  static void MergeBodies(
    CATGeoFactory *iFactory,
    const CATLISTP(CATBody) &iList,
    CATBody *&oBody,
    CATTopBodyToolsFreezeMode iMode = CATTopBodyToolsFreezeOn);

  static void InvertWire(CATGeoFactory *iFactory, CATBody *iWireBody, CATBody *&oBody);

  //-------------------------------------------------------------------
  //	Check if there is at least one High level Domain (domain directly 
  // federated by the Body) is empty
  //-------------------------------------------------------------------
  static HRESULT IsDomainsBodyEmpty(CATBody *piBody, CATBoolean &ioIsEmpty);

  // ultra temporaire
  static int GetInfinite(CATBody *);

  /**
  *------------------------------------------------------------------------
  * Returns the planar surface of the unique face inside the infinite input body
  * Returns NULL if the Body isn't infinite
  * oOriPlaneVsBody is an optional argument which allows the caller to know the relative orientation of the plane in the body
  *------------------------------------------------------------------------
  */
  static CATPlane *GetInfinitePlanarBodySurface(
    CATBody *iBody,
    CATOrientation *oOriPlaneVsBody = NULL);

  /**
  *------------------------------------------------------------------------
  * Retrieves the mathematical line of the unique infinite linear edge inside the infinite input body
  * Returns TRUE only if the Body is both infinite and linear
  * oInfiniteLine is an optional argument which allows the caller to get the retrieved mathematical line
  *------------------------------------------------------------------------
  */
  static CATBoolean IsAnInfiniteLinearBody(
    CATBody *iBody,
    CATMathLine *oInfiniteLine = NULL);

  /**
  *------------------------------------------------------------------------
  * Checks if each highest cell is a linear or a polylinear edge
  * Returns TRUE only if all the highest cells of the input body are (poly)linear edges
  * TRUE implies that the local curvature is NULL everywhere on the wire body.
  * oIsAnInfiniteLinearBody is an optional argument which allows the caller to know if the body is an infinite linear body
  *------------------------------------------------------------------------
  */
  static CATBoolean IsBodyPolyLinearCompliant(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody,
    CATBoolean *oIsAnInfiniteLinearBody = NULL);

  /**
  *------------------------------------------------------------------------
  * Checks if each faces of the input volume is planar
  * Returns TRUE only if all the highest cells of the input body are planar surfaces
  *------------------------------------------------------------------------
  */
  static CATBoolean IsAStraightBody(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody);

  /**
  *------------------------------------------------------------------------
  * Retrieves the number of discrete sub-elements (triangles, bars, points)
  * from the highest cells of a polyhedral CATBody
  * oPolyGeoDimension012 is the dimension of the highest geometries found in the body
  * equals to 0 in case of set of points, 1 in case of polycurves, and 2 in case of polymesh
  * Returns the number of found sub-elements
  *------------------------------------------------------------------------
  */
  static int GetNbPolySubElementsFromBody(
    CATBody *iBody,
    int      &oPolyGeoDimension012);

  /**
  *------------------------------------------------------------------------
  *  ChainingSmart
  *-------------------------------------------------------------------------
  */
  static void ChainingSmart(CATBody *iInputBody, CATBody *iOutputBody);

  static void ChainingSmart(
    const CATLISTP(CATBody) &iInputBodies,
    CATBody *iOutputBody);

  /**
  *------------------------------------------------------------------------
  * To be avoided
  *-------------------------------------------------------------------------
  */
  // restricted area 
  static void Inactivate(CATBody *);

  static void ForceActivate(CATBody *);

  static CATBoolean IsWithInverseCacheLinks(CATBody *);

  static void IsRunningTessOperator(CATBody *);

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
  static HRESULT CreateFullSmartBody(
    CATSoftwareConfiguration *iConfiguration,
    CATBody *iBody,
    CATBody *&oBody,
    const CATBoolean iWithBoundixBox = FALSE);

};

#endif /* CATPGMTopBodyTools_h_ */
