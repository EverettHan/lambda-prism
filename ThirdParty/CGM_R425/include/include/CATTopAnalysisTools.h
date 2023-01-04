// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
//
// DESCRIPTION  : 
//
//=============================================================================
// Creation May 2011
//=============================================================================

#ifndef CATTopAnalysisTools_h
#define CATTopAnalysisTools_h


#include "CATGMModelInterfaces.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "IUnknown.h"

#include "ListPOfCATFace.h"
#include "CATListOfInt.h"


class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATFace;
class CATVertex;
class CATMaxOffset;


//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATTopAnalysisTools
{

public:
  /**
   * Constructor
   */
  CATTopAnalysisTools();

  /**
   * Destructor
   */
  virtual ~CATTopAnalysisTools();


  // Methods


  /** 
    * Method [IsSurfacePeaked] : for a Face
    * @param ipFace
    * The input CATFace.
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a point as pole in the surface of face.
    * S_FALSE : no point as pole.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */
  virtual HRESULT IsSurfacePeaked(CATFace * ipFace, CATVertex *iVertex=NULL) = 0;

  /** 
    * Method [IsSurfacePeaked] : for all faces of the Body (the entry body)
    * @param oListFace
    * The output list of all faces who have a point as pole.
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a point as pole.
    * S_FALSE : not point as pole.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */
  virtual HRESULT IsSurfacePeaked(CATLISTP(CATFace) & oListFace) = 0;


  /** 
    * Method [IsSurfaceParallelTuTv] : for a Face
    * @param ipFace
    * The input CATFace.
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a point with parallel Tu/Tv (isopar) in the surface of face.
    * S_FALSE : no point as pole.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */
  virtual HRESULT IsSurfaceParallelTuTv(CATFace * ipFace) = 0;

  /** 
    * Method [IsSurfaceParallelTuTv] : for all faces of the Body (the entry body)
    * @param oListFace
    * The output list of all faces who have a point with parallel Tu/Tv.
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a point with parallel Tu/Tv (isopar) in the surface of face.
    * S_FALSE : not point as pole.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */
  virtual HRESULT IsSurfaceParallelTuTv(CATLISTP(CATFace) & oListFace) = 0;

  /** 
    * Method [IsTwisted] : for a Face
    * @param ipFace
    * The input CATFace.
    * @param iopUVTwistList
    * The input CATListOfDouble.
    * @param iopListLocationTwist
    * The input CATListOfInt.
    * <br><b>Legal values</b>:
    * <dl><dt><tt>CATLocationInner</tt></dt><dd> if the twist point is inside the face
    *     <dt><tt>CATLocationFull</tt></dt><dd> if the twist point is on the boundary of the face
    * </dl>
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : surface of the face is twisted (twist is inside the face (or/and on the boundary of the face if iopListLocationTwist is valued)).
    * S_FALSE : surface of the face is not twisted.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */

  virtual HRESULT IsSurfaceTwisted(CATFace * ipFace, CATListOfDouble * iopUVTwistList = NULL, CATListOfInt * iopListLocationTwist = NULL) = 0;

  /** 
    * Method [IsTwisted] : for all faces of the Body (the entry body)
    * @param oListFace
    * The output list of all faces who are twisted.
    * @param iIsLocationFull
    * To take account twist on the boundary of the face (by default, only twist inside face are returned).
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a twisted surface of the face.
    * S_FALSE : not twisted surface of face.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */

  virtual HRESULT IsSurfaceTwisted(CATLISTP(CATFace) & oListFace, short * iIsLocationFull = NULL) = 0;
  

  /** 
    * Method [IsFaceLocallyOffsetable] : for a Face
    * @param ipFace
    * The input CATFace.
    * @param iFaceOffsetValue
    * The input offset value.
    * @param ipMaxOffset
    * The input CATMaxOffset if already exists.
    * @return [S_OK, S_FALSE, E_FAIL]
    * S_OK : we have a face locally offsetable.
    * S_FALSE : not have.
    * E_FAIL : an error occured during the operation (ex: no factory, null pointer,...).
    */

  virtual HRESULT IsFaceLocallyOffsetable(CATFace         *   ipFace,
                                          double              iFaceOffsetValue,
                                          CATMaxOffset    *   ipMaxOffset = NULL) = 0;
  




};



  /** 
    * Constructor [CATTopAnalysisTools] : 
    * @param ipConfig
    * The input CATSoftwareConfiguration.
    * @param ipFactory
    * The input CATGeoFactory.
    * @param ipBody (option in case of using method for CATBody)
    * The body
    * @return [out, delete]
    */

ExportedByCATGMModelInterfaces 
CATTopAnalysisTools * CATCreateTopAnalysisTools(CATSoftwareConfiguration * ipConfig,
                                                CATGeoFactory            * ipFactory,
                                                CATBody                  * ipBody = NULL);




	/** 
	 * @nodoc
   * do not use
	 */

ExportedByCATGMModelInterfaces 
CATTopAnalysisTools * CATCreateTopAnalysisTools(CATSoftwareConfiguration * ipConfig,
                                                CATBody                  * ipBody);

#endif /* CATTopAnalysisTools_h */


