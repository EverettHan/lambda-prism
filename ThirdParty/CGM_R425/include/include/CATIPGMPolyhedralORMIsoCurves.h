#ifndef CATIPGMPolyhedralORMIsoCurves_h_
#define CATIPGMPolyhedralORMIsoCurves_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPolyTopOperator.h"

#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATWire.h"

class CATCGMOrmModel;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyhedralORMIsoCurves;

/**
*
* Class defining an operator that generate isoCurves (and associated surfaces) from a surfacic OrmModel
* <ul>
*     <li> A <tt>CATICGMPolyhedralORMIsoCurves</tt> operator is created with the <tt>CATCGMCreatePolyhedralORMIsoCurves</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralORMIsoCurves: public CATIPGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolyhedralORMIsoCurves();

  //===========================================================================
  // NODE DENSITIES ACCESS
  //===========================================================================
  //--------------------------------------------------------------------------
  // Method: ComputeNodesDensity
  //
  // Description: Can Only be called BEFORE the Run
  //  Compute the density of the all the nodes of the model.
  //  Then use the Set / GetNodeDensity of this class to access the densities.
  //
  // CAUTION : it does not update the input ORMModel, it will instantiate 
  //   the PolyOrmMesh (internal data) with the data of the OrmModel.
  //   THUS you must have set all the options before a call to this method,
  //   including the SetOriginContext if it is needed.
  //--------------------------------------------------------------------------
  virtual HRESULT ComputeNodesDensity() = 0;

  //--------------------------------------------------------------------------
  // Method: SetNodeDensity
  //
  // Description: 
  //  Set the density of a node from its id in the OrmModel.
  //
  // CAUTION : ComputeNodesDensity MUST HAVE been called before
  //--------------------------------------------------------------------------
  virtual HRESULT SetNodeDensity(int iIdNodeInOrmModel, float iDensity) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeDensity
  //
  // Description: 
  //  Get the density of a node from its id in the OrmModel.
  //
  // CAUTION : ComputeNodesDensity MUST HAVE been called before
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeDensity(int iIdNodeInOrmModel, float &oDensity) = 0;

  //===========================================================================
  // ORIGIN CONTEXT MANAGEMENT
  //===========================================================================
  //--------------------------------------------------------------------------
  // Method: SetOriginContext
  //
  // Description: 
  //  Set the list of origin bodies used to create the OrmModel.
  //		For now, this operator is implemented only for the mono-body cases.
  //	Also set the list of frozen cells among this body.
  //
  // CAUTION : it activates the subdivision of the result accordingly to the CATFaces generating each triangles.
  //
  // Return:
  //   E_FAIL if there is more or less than one body
  //--------------------------------------------------------------------------
  virtual HRESULT SetOriginContext(
    const CATLISTP(CATBody) &iBodyList,
    const CATLISTP(CATCell) &iFrozenCells) = 0;

  //--------------------------------------------------------------------------
  // Method: AddMergedFaces
  //
  // Description: 
  //  Add a group of origin-CATFaces that are to be considered as merged.
  //
  // CAUTION : a CATFace can be in only one group.
  //--------------------------------------------------------------------------
  virtual void AddMergedFaces(const CATLISTP(CATFace) &iMergedFaces) = 0;

  //=============================================================================
  // Settings
  //=============================================================================
  // Method: SetIsoValues
  // 
  // Description:
  //   Set the list of IsoValues. Each isoValue will generate an isoCurve.
  //   In surface mode (by default) the surface will be subidived by those isoCurves
  //       in addition of the data about the Origin CATFace.
  // CAUTION : the isovalues must be ordered by increasing value and without duplicates.
  //
  // Without isoValue and without the wire mode, the result will be the surface 
  // described by the model, only subdivided accordingly to the origin CATFace.
  virtual void SetIsoValues(const CATListOfDouble &iListIsoValues) = 0;

  // Method: SetAreasToKeep
  // Description: 
  //   Set the list of Boolean to specify if each area between the isovalues must be kept 
  //      or not.
  //   The size of this list MUST BE equal to the number of isoValues + 1.
  //   Each area is defined by the isoCurves corresponding to the isoValues surrounding 
  //     it, and by the border of the model if needed.
  //   The first area correspond to the isoCurve of the first isoValue and the zone  
  //     below this isoValue.
  //   The last area correspond to the isoCurve of the last isoValue and the zone
  //     above it.
  //
  //   In WIRE MODE, those booleans specify the border of the areas to keep as wire 
  //     (including borders of the models if needed).
  //   If the two areas around an isoValue are set to FALSE, the result will contain the 
  //	  isoCurves corresponding to this isoValue, without closing it with the borders of 
  //     the model.
  //
  //   Without a call to this method, the default modes are
  // 	  In surface mode : keep all intervals, just subdividing the surface by all the   
  //         isolines.
  //     In wire mode : keep only the isolines (open if they reach the border of the 
  //         model)
  //
  //   Frozen elements behaviour :
  //      In surfacic mode, the frozen faces (gathering the frozen elements) are concidered as areas to keep.
  //      In wire mode, the frozen areas are NOT concidered as areas to keep.
  virtual void SetAreasToKeep(const CATListOfInt &iList) = 0;

  // Method: EnableWireMode
  //
  // Description: 
  //   Activate the generation of wires corresponding to the iIsoCurves and the borders 
  //   of the areas to keep.
  //   Without a call to SetAreaToKeep, generates the wires corresponding to the isoCurve only
  //     (can generates open wires)
  // 
  //   CAUTION : in WireMode, the FrozenAreas are not concidered as to keep !
  //     Their borders will not persist, except if near a not-frozen area to keep.
  // 
  // Default Mode (if this method is not called) : generate the surfaces 
  //   inside the areas to keep.
  virtual void EnableWireMode() = 0;

  // Method: EnableConvergenceToOrigin()
  // 
  // Description:
  //   Converge the points generated on the bars of the OrmModel onto
  //   the origin-elements generating those bars (CATFace or CATEdge).
  //
  //   It will converge the border of the optimised/frozen parts onto the originBody
  //     geometry.
  virtual void EnableConvergenceToOrigin() = 0;

  //=============================================================================
  // Get additional information after Run
  //=============================================================================
  // Method: GetFacesOfArea
  // 
  // Description: ONLY IN SURFACE MODE (default mode)
  //   Return all the faces of the resulting body that are in the area iAreaId.
  //       Set iAreaId at -1 to get the faces of the frozen area.
  //   Also specify the groups of faces corresponding to the different connex parts.
  //     oIndexesBegGroups[i] = id into oListFaces of the first face of the group i
  //   Two faces of a same area are connex if and only if they are separated by an edge
  //     of the origin body. Aka if those faces are generated by two different groups
  //     of origin CATFaces.
  //
  //   All the faces are oriented accordingly to the OrmModel element's orientation.
  //
  // return 	E_FAIL if this areaID does not exist or if the mode wire is activated.
  //        	S_FALSE if the result is empty.
  virtual HRESULT GetFacesOfArea(
    int iAreaId,
    CATLISTP(CATFace) &oListFaces,
    CATListOfInt &oIndexesBegGroups) = 0;

  // Method: GetEdgesOfIsoCurve
  //
  // Description: for both surface and wire modes.
  //   Return all the edges corresponding to the isoCurves of the isoValue iIsoValueID.
  //   Also specify the groups of edges corresponding to the different isoCurves.
  //     oIndexesBegGroups[i] = id into oListEdges of the first edge of the group i
  //
  //  if oEdgesOrientations is different than NULL it will store the orientations
  //     of the edges in order for them to have the area of their isoValue on their right
  //        and the area of isoValue+1 on their left.
  //
  // return 	E_FAIL if this isoValue does not exist.
  // 		      S_FALSE if the result is empty
  virtual HRESULT GetEdgesOfIsoCurve(
    int iIsoValueID,
    CATLISTP(CATEdge) &oListEdges,
    CATListOfInt &oIndexesBegGroups,
    CATListOfInt *oEdgesOrientations = NULL) = 0;

  // Method: GetWireContaingIsoCurve
  //
  // Description: ONLY IN WIRE MODE
  //   Return all the wires containing an isoCurve of the isoValue iIsoValueID.
  // If an area around this isoValue is to be kept, then the wire can also contain edges
  //   generated by another isoValue or by the border of the model.
  //
  // Wires Orientations :
  //   If the wire is near an area to keep, it will be oriented with this are on its left.
  //   If both areas are to be kept around it, the highest area ID will be on its left
  //   If no area to keep around, it will be oriented with the area of idIsovalue on its right (and idIsoValue+1 on its left)
  //
  // return 	E_FAIL if this isoValue does not exist.
  // 		      S_FALSE if the result is empty
  virtual HRESULT GetWireContaingIsoCurve(
    int iIsoValueID,
    CATLISTP(CATWire) &oListWires) = 0;

  // Method: GetWiresBoundingArea
  //
  // Description: ONLY IN WIRE MODE
  //   Return all the wires bounding the area iAreaID.
  //   Works ONLY for the area that are defined as to keep (or if all the areas are to be kept)
  //        Set iAreaID at -1 to get the wires bounding the frozen area.
  //
  // The wires will be oriented to have the area to be kept on their left.
  //   If between two areas to be kept, they will be oriented in order for them
  //   to have the area with the highest id on their left.
  //
  // return 	E_FAIL if this area does not exist or is not kept.
  // 		S_FALSE if the result is empty
  virtual HRESULT GetWiresBoundingArea(
    int iAreaID,
    CATLISTP(CATWire) &oListWires) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyhedralORMIsoCurves(); // -> delete can't be called
};

/**
 * Creates a CATIPGMPolyhedralORMIsoCurves operator
 * @param iFactory : MANDATORY
 *   The factory of the geometry.
 * @param iTopData
 *   The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt>
 *   is <tt>NULL</tt>, it is not filled.
 * @param iOrmModel : MANDATORY
 *   The pointer to the 2D OrmModel 
 * @return [out, IUnknown#Release]
 *   The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 *   Or NULL if the OrmModel or the factory are NULL.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralORMIsoCurves *CATPGMCreatePolyhedralORMIsoCurves(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATCGMOrmModel *iOrmModel);

#endif /* CATIPGMPolyhedralORMIsoCurves_h_ */
