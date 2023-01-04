//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldGenEntity
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldGenEntity_H
#define CATCldGenEntity_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATGeometry.h"

class CATMathPoint ;
#include "CATBoolean.h"
#include "CATCldDef.h"
#include "CATListOfInt.h"
#include "CATListOfFloat.h"
#include "CATListOfDouble.h"
#include "CATListOfCATICGMObjects.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldGenEntity ;
#else
extern "C" const IID IID_CATCldGenEntity ;
#endif
/**
 * General interface for the entities managing clouds of points.<br>
 * The architecture of such entities is as following :
 * <pre>
 * CATCldGenEntity
 *  |
 *  +-- CATCldBody - Set of CATCldCell
 *  |
 *  +-- CATCldCell
 *       |
 *       +-- CATCldUniCell - Unitary cell
 *       |    |
 *       |    +-- CATCldCloud   - Unordered cloud of points
 *       |    |
 *       |    +-- CATCldScan    - 1D-ordered cloud of points
 *       |    |
 *       |    +-- CATCldGrid    - 2D-ordered cloud of points
 *       |    |
 *       |    +-- CATCldPolygon - Tessellation of a cloud of points
 *       |
 *       +-- CATCldMultiCell - Multi cells of the same type
 *            |
 *            +-- CATCldSetOfScans
 *            |
 *            +-- CATCldSetOfGrids
 * </pre>
 * The reason of such architecture is to preserve the topological semantic of the digitalization files.<br>
 * The points coordinates are stored in an entity: the <tt>CATCldSetOfPoints</tt>.<br>
 * This entity is referenced by all the entities, and the access to the coordinates is done by several
 * methods encapsulated at the <tt>CATCldGenEntity</tt> level.<br>
 * The <tt>CATCldSetOfPoints</tt> is derived either in <tt>CATCldSetOfPointsF</tt> (coordinates in float)
 * or in <tt>CATCldSetOfPointsD</tt> (coordinates in double), depending of the use of the present Data
 * Structure (for a huge number of data, float is preferred). It is the reason of the duplication of the
 * access methods.<br>
 * <b>Glossary:</b>
 * <ul>
 * <li>A point in the <tt>CATCldSetOfPoints</tt> is referenced by its <b>index</b>.
 * <li>A point in a <tt>CATCldUniCell</tt> is referenced by its <b>relative indice</b> (or <b>indice</b>).
 * </ul>
 * To distinguish the methods working on/with indexes and indices, we have two families :
 * <ul>
 * <li>For the <b>indexes</b>, the methods have the prefix <tt>[GS]etIdx</tt>.
 * <li>For the <b>indices</b>, the methods have the prefix <tt>[GS]etNum</tt> (<b>Num</b> for <b>numero</b> in french).
 * </ul>
 * <br>
 * <b>CAUTION:</b><br>
 * The indexes given as parameters COULD NOT BELONG to the entity and must be in the range <tt>[1,GetNbTotalPoints()]</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATCldGenEntity : public CATGeometry
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// General methods for all the CloudEditor entities.
//==============================================================================================================

  /**
   * Declares that the entity creation is achieved.<br>
   * This method does some computations and runs some basic checks.<br>
   * This is interesting when the creation is incremental.
   */
  virtual CATBoolean EndOfCreation () = 0 ;

  /**
   * Declares that the entity modification is achieved.<br>
   * This method does some computations and runs some basic checks.
   */
  virtual CATBoolean EndOfModification () = 0 ;

  /**
   * Returns the bounding box of the active points.
   */
  virtual void GetActiveBoundingBox (CATMathBox &oBox) const = 0 ;

  /**
   * Tests if the point given by its coordinates is rejected by the entity,<br>
   * ie is outside of its bounding box inflated of the given tolerance.
   */
  virtual CATBoolean Reject (const float iCoords[3],
                             const float iTolerance = 0.) const = 0 ;

  /**
   * Tests if the point given by its coordinates is rejected by the entity,<br>
   * ie is outside of its bounding box inflated of the given tolerance.
   */
  virtual CATBoolean Reject (const double iCoords[3],
                             const double iTolerance = 0.) const = 0 ;

  /**
   * Tests if the point given by its index is rejected by the entity,<br>
   * ie is outside of its bounding box inflated of the given tolerance.
   */
  virtual CATBoolean Reject (const int    iIndex,
                             const double iTolerance = 0.) const = 0 ;

  /**
   * Tests if the given <tt>CldGenEntity</tt> is rejected by the entity,<br>
   * ie there is no intersection between the two associated bounding boxes.
   */
  virtual CATBoolean Reject (const CATCldGenEntity* iEntity) const = 0 ;

  /**
   * Tests if the point given by its index is referenced by the entity.
   */
  virtual CATBoolean Contains (const int iIndex) const = 0 ;

  /**
   * Opens an partitionning context by creating an internal spatial partition
   * of the <tt>CATCldGenEntity</tt> to optimize a point search or projection.
   * @param iOnlyActive
   * <ul>
   * <li>If <tt>TRUE</tt>, only the active points will be considered.
   * <li>If <tt>FALSE</tt>, all the points will be considered.
   * </ul>
   */
  virtual CATBoolean PartitionBegin (const CATBoolean iOnlyActive = FALSE) = 0 ;
  
  /**
   * Closes the partitionning context opened by <tt>PartitionBegin</tt>.
   */
  virtual CATBoolean PartitionEnd() = 0 ;
  
  /**
   * Returns the fact that the <tt>CATCldGenEntity</tt> is in an opened partitionning context or not.
   */
  virtual CATBoolean HasAPartition() const = 0 ;
  
  /**
   * Searches the points confused with the given point within the given tolerance.<br>
   * @param ioIndexes
   * List of the indexes of the points which are confused with the given point.<br>
   * The indexes are sorted in regards on their distance to the given point (the first is the closest).
   * @param ioDistances
   * List of the distances to the given point. It is parallel to <tt>ioIndexes</tt>.<br>
   * The distances are sorted in the increasing order.<br>
   * <b>CAUTION:</b> The lists will be cleared by the method before use.
   */
  virtual void SearchIndex (const float     iCoords[3],
                            CATListOfInt   &ioIndexes,
                            CATListOfFloat &ioDistances,
                            const float     iTolerance = 0.) const = 0 ;

  /**
   * Searches the points confused with the given point within the given tolerance.<br>
   * @param ioIndexes
   * List of the indexes of the points which are confused with the given point.<br>
   * The indexes are sorted in regards on their distance to the given point (the first is the closest).
   * @param ioDistances
   * List of the distances to the given point. It is parallel to <tt>ioIndexes</tt>.<br>
   * The distances are sorted in the increasing order.<br>
   * <b>CAUTION:</b> The lists will be cleared by the method before use.
   */
  virtual void SearchIndex (const double     iCoords[3],
                            CATListOfInt    &ioIndexes,
                            CATListOfDouble &ioDistances,
                            const double     iTolerance = 0.) const = 0 ;

  /**
   * Returns the closest points to a given point.
   * @param iCoords
   * The coordinates of the given point.
   * @param iNbPoints
   * The wanted number of closest points.
   * @param oIndexes
   * Array of the indexes of the closest points.<br>
   * The indexes are sorted in regards on their distance to the given point (the first is the closest).
   * @param oDistances
   * Array of the distances to the given point. It is parallel to <tt>ioIndexes</tt>.<br>
   * The distances are sorted in the increasing order.<br>
   * @param iOnlyActive
   * <ul>
   * <li>If <tt>TRUE</tt>, only the active points will be considered.
   * <li>If <tt>FALSE</tt>, all the points will be considered.
   * </ul>
   * <b>CAUTION 1:</b> The allocations of the two arraies <tt>oIndexes</tt> and <tt>oDistances</tt> have
   * to be done by the calling method and their size must be at least <tt>iNbPoints</tt>.<br>
   * <b>CAUTION 2:</b> The returned indexes correspond to <b>exactly non-confused</b> points.
   * Nevertheless their associated distances could be equal.<br>
   * <b>CAUTION 3:</b> Some returned indexes could be null if less than <tt>iNbPoints</tt> are found.
   */
  virtual void ClosestPoints (const float      iCoords[3],
                              const int        iNbPoints,
                              int*             oIndexes,
                              float*           oDistances,
                              const CATBoolean iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns the closest points to a given point.
   * @param iCoords
   * The coordinates of the given point.
   * @param iNbPoints
   * The wanted number of closest points.
   * @param oIndexes
   * Array of the indexes of the closest points.<br>
   * The indexes are sorted in regards on their distance to the given point (the first is the closest).
   * @param oDistances
   * Array of the distances to the given point. It is parallel to <tt>ioIndexes</tt>.<br>
   * The distances are sorted in the increasing order.<br>
   * @param iOnlyActive
   * <ul>
   * <li>If <tt>TRUE</tt>, only the active points will be considered.
   * <li>If <tt>FALSE</tt>, all the points will be considered.
   * </ul>
   * <b>CAUTION 1:</b> The allocations of the two arraies <tt>oIndexes</tt> and <tt>oDistances</tt> have
   * to be done by the calling method and their size must be at least <tt>iNbPoints</tt>.<br>
   * <b>CAUTION 2:</b> The returned indexes correspond to <b>exactly non-confused</b> points.
   * Nevertheless their associated distances could be equal.<br>
   * <b>CAUTION 3:</b> Some returned indexes could be null if less than <tt>iNbPoints</tt> are found.
   */
  virtual void ClosestPoints (const double     iCoords[3],
                              const int        iNbPoints,
                              int*             oIndexes,
                              double*          oDistances,
                              const CATBoolean iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns the projection of a given point.
   * @param iPoint
   * The point to project.
   * @param oProjection
   * The projection.
   * @param iNormal
   * <ul>
   * <li>If <tt>FALSE</tt>, the projection will be the closest point.
   * <li>If <tt>TRUE</tt>, the projection will be the projection on the triangle defined by the three
   * closest points with a "vertex-edge-triangle" priority.
   * </ul>
   * @param iOnlyActive
   * <ul>
   * <li>If <tt>TRUE</tt>, only the active points will be considered.
   * <li>If <tt>FALSE</tt>, all the points will be considered.
   * </ul>
   * @param iTolerance
   * The tolerance defining the confusion with a vertex or an edge in case of a normal projection.
   * @return
   * <tt>TRUE</tt>, if there is a projection. <tt>FALSE</tt>, otherwise.
   */
  virtual CATBoolean Projection (const CATMathPoint &iPoint,
                                 CATMathPoint       &oProjection,
                                 const CATBoolean    iNormal = FALSE,
                                 const CATBoolean    iOnlyActive = FALSE,
                                 const double        iTolerance = 0.) const = 0 ;

//==============================================================================================================
// Points.
//==============================================================================================================

  /**
   * Returns the number of points referenced by the entity.<br>
   * @param iAllPoints
   * <ul>
   * <li>If <tt>TRUE</tt>, it returns the <b>total</b> number of indexes.
   * <li>If <tt>FALSE</tt>, it returns the number of non-null indexes.
   * </ul>
   */
  virtual int GetNbPoints (const CATBoolean iAllPoints = TRUE) const = 0 ;

  /**
   * Returns the number and the non-null indexes of the points referenced by the entity.<br>
   * @param oNbIndexes
   * The number of indexes.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbIndexes</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetPoints (int  &oNbPoints,
                          int* &ioIndexes) const = 0 ;

  /**
   * Returns the number of active points of the entity.<br>
   * <b>A point is said to be active when it is selected and unfiltered.</b><br>
   * The null indexes will not be taken into account, but the non-null indexes could be duplicated.
   */
  virtual int GetNbActivePoints () const = 0 ;

  /**
   * Returns the number of active points of the entity and their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The null indexes will be suppressed, but the non-null indexes could be duplicated.<br>
   * <b>CAUTION 2:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetActivePoints (int  &oNbPoints,
                                int* &ioIndexes) const = 0 ;

  /**
   * Returns the number of selected points of the entity.<br>
   * The null indexes will not be taken into account, but the non-null indexes could be duplicated.
   */
  virtual int GetNbSelectedPoints () const = 0 ;

  /**
   * Returns the number of selected points of the entity and their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The null indexes will be suppressed, but the non-null indexes could be duplicated.<br>
   * <b>CAUTION 2:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetSelectedPoints (int  &oNbPoints,
                                  int* &ioIndexes) const = 0 ;

  /**
   * Returns the number of unselected points of the entity.<br>
   * The null indexes will not be taken into account, but the non-null indexes could be duplicated.
   */
  virtual int GetNbUnselectedPoints () const = 0 ;

  /**
   * Returns the number of unselected points of the entity and their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The null indexes will be suppressed, but the non-null indexes could be duplicated.<br>
   * <b>CAUTION 2:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetUnselectedPoints (int  &oNbPoints,
                                    int* &ioIndexes) const = 0 ;

  /**
   * Inverts the selection.<br>
   * For points inside a cell:
   * <ul>
   * <li><tt>"Selected   -> Unselected"</tt>
   * <li><tt>"Unselected -> Selected"</tt>
   * </ul>
   */
  virtual void InvertSelection () = 0 ;

  /**
   * Sets all points as selected.
   */
  virtual void SetAllPointsSelected () = 0 ;

  /**
   * Sets all points as unselected.
   */
  virtual void SetAllPointsUnselected () = 0 ;

  /**
   * Returns the number of filtered points of the entity.<br>
   * The null indexes will not be taken into account, but the non-null indexes could be duplicated.
   */
  virtual int GetNbFilteredPoints () const = 0 ;

  /**
   * Returns the number of filtered points of the entity and their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The null indexes will be suppressed, but the non-null indexes could be duplicated.<br>
   * <b>CAUTION 2:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetFilteredPoints (int  &oNbPoints,
                                  int* &ioIndexes) const = 0 ;

  /**
   * Returns the number of unfiltered points of the entity.<br>
   * The null indexes will not be taken into account, but the non-null indexes could be duplicated.
   */
  virtual int GetNbUnfilteredPoints () const = 0 ;

  /**
   * Returns the number of unfiltered points of the entity and their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioIndexes
   * The array of indexes.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The null indexes will be suppressed, but the non-null indexes could be duplicated.<br>
   * <b>CAUTION 2:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetUnfilteredPoints (int  &oNbPoints,
                                    int* &ioIndexes) const = 0 ;

  /**
   * Inverts the filtered attribute.<br>
   * For points inside a cell:
   * <ul>
   * <li><tt>"Filtered   -> Unfiltered"</tt>
   * <li><tt>"Unfiltered -> Filtered"</tt>
   * </ul>
   */
  virtual void InvertFiltering () = 0 ;

  /**
   * Sets all points as filtered.
   */
  virtual void SetAllPointsFiltered () = 0 ;

  /**
   * Sets all points as unfiltered.
   */
  virtual void SetAllPointsUnfiltered () = 0 ;

  /**
   * Compacts the <tt>CATCldGenEntity</tt>.<br>
   * <ul>
   * <li>For a <tt>CATCldBody</tt> or a <tt>CATCldMultiCell</tt>, removes
   * the reference to the null or removed cell and call the method for each
   * sub-cells.
   * <li>For a <tt>CATCldUniCell</tt>, removes the reference to the null indexes.
   * <li>For a <tt>CATCldGrid</tt>, the sub-grid (UMin,UMax,VMin,VMax) of non-null indexes is determined,
   * and the grid is restricted to this sub-grid.
   * <li>For a <tt>CATCldPolygon</tt>, the removed triangles are also deleted.
   * </ul>
   */
  virtual void Compact () = 0 ;

//==============================================================================================================
// The following methods are the public access to the SetOfPoints via the point indexes.
//==============================================================================================================

  /**
   * Returns the list of all the <tt>CATCldGenEntities</tt> sharing the same <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> The list will be cleared by the method before use.
   */
  virtual void GetSoPEntities (CATLISTP(CATICGMObject) &ioEntities) const = 0 ;

  /**
   * Returns the <b>total</b> number of points of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual int GetNbTotalPoints () const = 0 ;

  /**
   * Returns the coordinates of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean GetIdxCoords (const int iIndex,
                                   float     oCoords[3]) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean GetIdxCoords (const int iIndex,
                                   double    oCoords[3]) const = 0 ;

  /**
   * Returns the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean GetIdxInfo (const int      iIndex,
                                 CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean GetIdxPoint (const int      iIndex,
                                  float          oCoords[3],
                                  CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean GetIdxPoint (const int      iIndex,
                                  double         oCoords[3],
                                  CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>3*iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual CATBoolean GetIdxCoords (const int   iNbPoints,
                                   const int*  iIndexes,
                                   float*     &ioCoords) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>3*iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual CATBoolean GetIdxCoords (const int   iNbPoints,
                                   const int*  iIndexes,
                                   double*    &ioCoords) const = 0 ;

  /**
   * Returns the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioInfos</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual CATBoolean GetIdxInfos (const int       iNbPoints,
                                  const int*      iIndexes,
                                  CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Returns the coordinates and the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> (resp. <tt>ioInfos</tt>) is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>3*iNbPoints</tt> (resp. <tt>iNbPoints</tt>).<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual CATBoolean GetIdxPoints (const int       iNbPoints,
                                   const int*      iIndexes,
                                   float*         &ioCoords,
                                   CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Returns the coordinates and the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> (resp. <tt>ioInfos</tt>) is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>3*iNbPoints</tt> (resp. <tt>iNbPoints</tt>).<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual CATBoolean GetIdxPoints (const int       iNbPoints,
                                   const int*      iIndexes,
                                   double*        &ioCoords,
                                   CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Sets the coordinates of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxCoords (const int   iIndex,
                                   const float iCoords[3]) = 0 ;

  /**
   * Sets the coordinates of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxCoords (const int    iIndex,
                                   const double iCoords[3]) = 0 ;

  /**
   * Sets the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt> to the given information.
   */
  virtual CATBoolean SetIdxInfo (const int           iIndex,
                                 const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt> to the given information.
   */
  virtual CATBoolean SetIdxInfo (const int           iNbPoints,
                                 const int*          iIndexes,
                                 const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxPoint (const int           iIndex,
                                  const float         iCoords[3],
                                  const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the <tt>iIndex</tt>'th point of the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxPoint (const int           iIndex,
                                  const double        iCoords[3],
                                  const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxCoords (const int    iNbPoints,
                                   const int*   iIndexes,
                                   const float* iCoords) = 0 ;

  /**
   * Sets the coordinates of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxCoords (const int     iNbPoints,
                                   const int*    iIndexes,
                                   const double* iCoords) = 0 ;

  /**
   * Sets the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt> to the given informations.
   */
  virtual CATBoolean SetIdxInfos (const int            iNbPoints,
                                  const int*           iIndexes,
                                  const CATCldInfoPnt* iInfos) = 0 ;

  /**
   * Sets the coordinates and the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxPoints (const int            iNbPoints,
                                   const int*           iIndexes,
                                   const float*         iCoords,
                                   const CATCldInfoPnt* iInfos) = 0 ;

  /**
   * Sets the coordinates and the associated informations of the <tt>iNbPoints</tt> points given by their indexes in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATBoolean SetIdxPoints (const int            iNbPoints,
                                   const int*           iIndexes,
                                   const double*        iCoords,
                                   const CATCldInfoPnt* iInfos) = 0 ;

  /**
   * Sets to 0 all the associated informations.
   */
  virtual void CleanAllIdxInfos () = 0 ;

  /**
   * Compacts the <tt>CATCldSetOfPoints</tt>.<br>
   * <ul>
   * <li>Calls the <tt>Compact</tt> method on each <tt>CATCldBody</tt> sharing the <tt>CATCldSetOfPoints</tt>.
   * <li>Compacts the <tt>CATCldSetOfPoints</tt> (removes the unreferenced points).
   * <li>Does the reindexization of the unitary cells.
   * </ul>
   */
  virtual void OptimizeMemory () = 0 ;

} ;

CATDeclareHandler (CATCldGenEntity, CATGeometry) ;

#endif
