//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldUniCell
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
//==============================================================================================================

#ifndef CATCldUniCell_H
#define CATCldUniCell_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldCell.h"

#include "CATBoolean.h"
#include "CATCldDef.h"

class CATCldAttribute ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldUniCell ;
#else
extern "C" const IID IID_CATCldUniCell ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldUniCell</tt>.<br>
 * <b>CAUTION:</b><br>
 * <ul>
 * <li>Some of the methods will raise an exception when used for a <tt>CATCldGrid</tt>.
 * <li>The methods having a relative indice to the <tt>CATCldUniCell</tt>
 * as argument could be used for a <tt>CATCldGrid</tt> by considering
 * it as a monodimensionnal array and not a bidimensionnal one.
 * </ul>
 * @see CATCldGenEntity, CATCldCell
 */
class ExportedByCATGMGeometricInterfaces CATCldUniCell : public CATCldCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// Points management in a CATCldUniCell.
//==============================================================================================================

  /**
   * Adds a point given by its coordinates.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoint (const float iCoords[3]) = 0 ;

  /**
   * Adds a point given by its coordinates.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoint (const double iCoords[3]) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoint (const float  iCoords[3],
                         int         &oIndex) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoint (const double  iCoords[3],
                         int          &oIndex) = 0 ;

  /**
   * Adds a point given by its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoint (const int iIndex) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointNum (const float  iCoords[3],
                            int         &oNoPoint) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointNum (const double  iCoords[3],
                            int          &oNoPoint) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its index in the <tt>CATCldSetOfPoints</tt>
   * and its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointNum (const float  iCoords[3],
                            int         &oIndex,
                            int         &oNoPoint) = 0 ;

  /**
   * Adds a point given by its coordinates and
   * returns its index in the <tt>CATCldSetOfPoints</tt>
   * and its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointNum (const double  iCoords[3],
                            int          &oIndex,
                            int          &oNoPoint) = 0 ;

  /**
   * Adds a point given by its index in the <tt>CATCldSetOfPoints</tt> and
   * returns its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> By default, the point is active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointNum (const int  iIndex,
                            int       &oNoPoint) = 0 ;

  /**
   * Adds several points given by their coordinates.<br>
   * <b>CAUTION 1:</b> By default, the points are active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoints (const int    iNbPoints,
                          const float* iCoords) = 0 ;

  /**
   * Adds several points given by their coordinates.<br>
   * <b>CAUTION 1:</b> By default, the points are active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoints (const int     iNbPoints,
                          const double* iCoords) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoints (const int     iNbPoints,
                          const float*  iCoords,
                          int*         &ioIndexes) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoints (const int      iNbPoints,
                          const double*  iCoords,
                          int*          &ioIndexes) = 0 ;

  /**
   * Adds several points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> By default, the points are active.<br>
   * <b>CAUTION 2:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPoints (const int  iNbPoints,
                          const int* iIndexes) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointsNum (const int     iNbPoints,
                             const float*  iCoords,
                             int*         &ioNoPoints) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointsNum (const int      iNbPoints,
                             const double*  iCoords,
                             int*          &ioNoPoints) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their indexes in the <tt>CATCldSetOfPoints</tt> and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> (resp. <tt>ioNoPoints</tt>)
   * is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointsNum (const int     iNbPoints,
                             const float*  iCoords,
                             int*         &ioIndexes,
                             int*         &ioNoPoints) = 0 ;

  /**
   * Adds several points given by their coordinates and
   * returns their indexes in the <tt>CATCldSetOfPoints</tt> and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> (resp. <tt>ioNoPoints</tt>)
   * is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointsNum (const int      iNbPoints,
                             const double*  iCoords,
                             int*          &ioIndexes,
                             int*          &ioNoPoints) = 0 ;

  /**
   * Adds several points given by their indexes in the <tt>CATCldSetOfPoints</tt> and
   * returns their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> By default, the points are active.<br>
   * <b>CAUTION 3:</b> This method raises an exception when used for a <tt>CATCldGrid</tt>.
   */
  virtual void AddPointsNum (const int   iNbPoints,
                             const int*  iIndexes,
                             int*       &ioNoPoints) = 0 ;

  /**
   * Removes one point given by its relative indice in the <tt>CATCldUniCell</tt>.<br>
   * A point is removed by setting its index to 0.
   */
  virtual void RemovePoint (const int iNoPoint) = 0 ;

  /**
   * Removes several points given by their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * A point is removed by setting its index to 0.
   */
  virtual void RemovePoints (const int  iNbPoints,
                             const int* iNoPoints) = 0 ;

  /**
   * Removes all the occurences of a point given by its index.<br>
   */
  virtual void RemoveIndex (const int iIndex) = 0 ;

  /**
   * Removes all the occurences of several points given by their indexes.<br>
   */
  virtual void RemoveIndexes (const int  iNbPoints,
                              const int* iIndexes) = 0 ;

  /**
   * Prepares the <tt>CATCldUniCell</tt> to optimize some treatments.<br>
   * Specially for methods :
   * <ul>
   * <li>having indexes as input arguments like :
   * <ul>
   * <li><tt>RemoveIndex(es)</tt>
   * <li><tt>GetNumPoint(s)</tt>
   * <li><tt>...</tt>
   * </ul>
   * <li>or working with the vertices/triangles on a <tt>CATCldPolygon</tt>.
   * </ul>
   * <br>
   * Example of programming :
   * <pre>
   * ...
   * Cell->OptimizeBegin() ;
   * for (IPnt = 0 ; IPnt < NbPnt ; IPnt++) {
   *   ...
   *   Cell->RemoveIndex (Indexes[IPnt]) ;
   *   ...
   * }
   * Cell->OptimizeEnd() ;
   * ...
   * </pre>
   * <b>ADVICE:</b> It is interesting to use also this optimization for the <tt>RemovePoint(s)</tt>
   * on a <tt>CATCldPolygon</tt>.
   */
  virtual CATBoolean OptimizeBegin () = 0 ;

  /**
   * Ends the optimization done by calling <tt>OptimizeBegin</tt>.
   */
  virtual CATBoolean OptimizeEnd () = 0 ;

  /**
   * Returns the fact that the <tt>CATCldUniCell</tt> is in an opened optimization context or not.
   */
  virtual CATBoolean IsOptimized() const = 0 ;

//==============================================================================================================
// Methods equivalent to those of CATCldGenEntity but returning the relative indices.
//==============================================================================================================

  /**
   * Returns the number of active points of the entity and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoPoints
   * The array of relative indices.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The relative indices corresponding to null indexes will be suppressed.<br>
   * <b>CAUTION 2:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumActivePoints (int  &oNbPoints,
                                   int* &ioNoPoints) const = 0 ;

  /**
   * Returns the number of selected points of the entity and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoPoints
   * The array of relative indices.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The relative indices corresponding to null indexes will be suppressed.<br>
   * <b>CAUTION 2:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumSelectedPoints (int  &oNbPoints,
                                     int* &ioNoPoints) const = 0 ;

  /**
   * Returns the number of unselected points of the entity and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoPoints
   * The array of relative indices.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The relative indices corresponding to null indexes will be suppressed.<br>
   * <b>CAUTION 2:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumUnselectedPoints (int  &oNbPoints,
                                       int* &ioNoPoints) const = 0 ;

  /**
   * Returns the number of filtered points of the entity and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoPoints
   * The array of relative indices.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The relative indices corresponding to null indexes will be suppressed.<br>
   * <b>CAUTION 2:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumFilteredPoints (int  &oNbPoints,
                                     int* &ioNoPoints) const = 0 ;

  /**
   * Returns the number of unfiltered points of the entity and
   * their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoPoints
   * The array of relative indices.<br>
   * <b>CAUTION 1:</b> This array is a "photo" of the informations contained in the entity.<br>
   * The relative indices corresponding to null indexes will be suppressed.<br>
   * <b>CAUTION 2:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumUnfilteredPoints (int  &oNbPoints,
                                       int* &ioNoPoints) const = 0 ;

//==============================================================================================================
// Points flags management.
//==============================================================================================================

  /**
   * Tests if the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> is active
   * ie is selected and unfiltered.
   */
  virtual CATBoolean IsActive (const int iNoPoint) const = 0 ;

  /**
   * Tests if the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> is selected.
   */
  virtual CATBoolean IsSelected (const int iNoPoint) const = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as selected.
   */
  virtual void SetSelected (const int iNoPoint) = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as unselected.
   */
  virtual void SetUnselected (const int iNoPoint) = 0 ;

  /**
   * Tests if the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> is filtered.
   */
  virtual CATBoolean IsFiltered (const int iNoPoint) const = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as filtered.<br>
   * <b>CAUTION:</b> The point becomes inactive and invisible.
   */
  virtual void SetFiltered (const int iNoPoint) = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as unfiltered.
   */
  virtual void SetUnfiltered (const int iNoPoint) = 0 ;


  /**
   * Tests if the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> is locked.
   */
  virtual CATBoolean IsLocked (const int iNoPoint) const = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as locked.
   */
  virtual void SetLocked (const int iNoPoint) = 0 ;

  /**
   * Sets the <tt>iNoPoint</tt>'th point in the <tt>CATCldUniCell</tt> as locked.
   */
  virtual void SetUnlocked (const int iNoPoint) = 0 ;


//==============================================================================================================
// Points attributes management in a CATCldUniCell.
//==============================================================================================================

  /**
   * Returns the attribute associated to the <tt>iNoPoint</tt>'th point.<br>
   * <tt>CAUTION:</tt> Returns a <tt>NULL</tt> pointer if the attributes is not set.
   */
  virtual CATCldAttribute* GetPointAttribute (const int iNoPoint) const = 0 ;

  /**
   * Associates the given attribute to the <tt>iNoPoint</tt>'th point.
   */
  virtual void SetPointAttribute (const int              iNoPoint,
                                  const CATCldAttribute* iAttribute) = 0 ;


  /**
   * Returns the annotation associated to the <tt>iNoPoint</tt>'th point.<br>
   * <tt>CAUTION:</tt> Returns a <tt>NULL</tt> pointer if the attributes is not set.
   */
  virtual CATUnicodeString * GetPointAnnotation (const int iNoPoint) = 0 ;

  /**
   * Associates the given annotation to the <tt>iNoPoint</tt>'th point.
   */
  virtual void SetPointAnnotation (const int               iNoPoint,
                                   const CATUnicodeString &iAnnotation) = 0 ;

//==============================================================================================================
// Points color and symbol management in a CATCldUniCell.
//==============================================================================================================


  /**
   * Tests if the <tt>iNoPoint</tt>'th point is colored.
   */
  virtual CATBoolean IsColored (const int iNoPoint) const = 0 ;

  /**
   * Returns the attribute associated to the <tt>iNoPoint</tt>'th point.<br>
   * Returns <tt>TRUE</tt> if the point is colored.
   */
  virtual CATBoolean GetPointColor (const int iNoPoint,
                                    unsigned char &oRed,
                                    unsigned char &oGreen,
                                    unsigned char &oBlue,
                                    unsigned char &oAlpha) const = 0 ;

  /**
   * Associates the given colors to the <tt>iNoPoint</tt>'th point.
   */
  virtual void SetPointColor (const int iNoPoint,
                              const unsigned char iRed,
                              const unsigned char iGreen,
                              const unsigned char iBlue,
                              const unsigned char iAlpha = 255) = 0 ;

  /**
   * Deletes the potential color associated to the <tt>iNoPoint</tt>'th point.
   */
  virtual void DeletePointColor (const int iNoPoint) = 0 ;
  
  /**
   * Returns the number of colored points of the entity.
   */
  virtual int GetNbColoredPoints() const = 0 ;


  /**
   * Tests if the <tt>iNoPoint</tt>'th point has a symbol.
   */
  virtual CATBoolean HasASymbol (const int iNoPoint) const = 0 ;

  /**
   * Returns the symbol associated to the <tt>iNoPoint</tt>'th point.<br>
   * Returns <tt>TRUE</tt> if the point has a symbol.<br>
   * The symbol is given by an integer. Hereafter the correspondance array.
   * <pre>
   *  1 = CROSS      : Use this enum to have a cross marker.
   *  2 = PLUS       : Use this enum to have a plus marker.
   *  3 = CONCENTRIC : Use this enum to have a circle marker.
   *  4 = COINCIDENT : Use this enum to have a two concentric circle marker.
   *  5 = FULLCIRCLE : Use this enum to have a full circle marker.
   *  6 = FULLSQUARE : Use this enum to have a full square marker.
   *  7 = STAR       : Use this enum to have a star marker.
   *  8 = DOT        : Use this enum to have a dot (3x3 pixels) marker.
   *  9 = SMALLDOT   : Use this enum to have a small dot (1 pixel) marker.
   * </pre>
   * @see CATSymbolType
   */
  virtual CATBoolean GetPointSymbol (const int      iNoPoint,
                                     unsigned char &oSymbol) const = 0 ;

  /**
   * Associates the given symbol to the <tt>iNoPoint</tt>'th point.<br>
   * @param iSymbol
   * The symbol is given by an integer. Hereafter the correspondance array.
   * <pre>
   *  1 = CROSS      : Use this enum to have a cross marker.
   *  2 = PLUS       : Use this enum to have a plus marker.
   *  3 = CONCENTRIC : Use this enum to have a circle marker.
   *  4 = COINCIDENT : Use this enum to have a two concentric circle marker.
   *  5 = FULLCIRCLE : Use this enum to have a full circle marker.
   *  6 = FULLSQUARE : Use this enum to have a full square marker.
   *  7 = STAR       : Use this enum to have a star marker.
   *  8 = DOT        : Use this enum to have a dot (3x3 pixels) marker.
   *  9 = SMALLDOT   : Use this enum to have a small dot (1 pixel) marker.
   * </pre>
   * @see CATSymbolType
   */
  virtual void SetPointSymbol (const int           iNoPoint,
                               const unsigned char iSymbol) = 0 ;

  /**
   * Deletes the potential symbol associated to the <tt>iNoPoint</tt>'th point.
   */
  virtual void DeletePointSymbol (const int iNoPoint) = 0 ;

  /**
   * Returns the number of points with a symbol of the entity.
   */
  virtual int GetNbPointsWithSymbol() const = 0 ;


//==============================================================================================================
// Indexes management in a CATCldUniCell.
//==============================================================================================================

  /**
   * Returns the index in the <tt>CATCldSetOfPoints</tt> of the <tt>iNoPoint</tt>'th
   * point in the <tt>CATCldUniCell</tt>.
   */
  virtual int GetIndex (const int iNoPoint) const = 0 ;

  /**
   * Returns the indexes in the <tt>CATCldSetOfPoints</tt> of the several points given by their
   * relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetIndexes (const int   iNbPoints,
                           const int*  iNoPoints,
                           int*       &ioIndexes) const = 0 ;

  /**
   * Sets the index in the <tt>CATCldSetOfPoints</tt> of the <tt>iNoPoint</tt>'th
   * point in the <tt>CATCldUniCell</tt>.<br>
   * If <tt>iIndex</tt> is less or equal than 0, 0 is set.
   */
  virtual void SetIndex (const int iNoPoint,
                         const int iIndex) = 0 ;

  /**
   * Swaps the indexes in the <tt>CATCldSetOfPoints</tt> of the <tt>iNoPoint1</tt>'th and
   * the <tt>iNoPoint2</tt>'th points in the <tt>CATCldUniCell</tt>..
   */
  virtual void SwapIndexes (const int iNoPoint1,
                            const int iNoPoint2) = 0 ;

  /**
   * Returns the <b>first</b> relative indice in the <tt>CATCldUniCell</tt> of a point
   * given by its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * Returns 0 if the given index does not belong to <tt>CATCldUniCell</tt>.
   */
  virtual int GetNumPoint (const int iIndex) const = 0 ;

  /**
   * Returns the relative indices in the <tt>CATCldUniCell</tt> of points
   * from their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> If an index does not belong to the <tt>CATCldUniCell</tt>,
   * its corresponding relative indice is set to 0.<br>
   * <b>CAUTION 2:</b> If an index is duplicated in the <tt>CATCldUniCell</tt>,
   * its first relative indice is returned.<br>
   * <b>CAUTION 3:</b> If <tt>ioNoPoints</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumPoints (const int   iNbPoints,
                             const int*  iIndexes,
                             int*       &ioNoPoints) const = 0 ;

//==============================================================================================================
// The following methods are the public access to the SetOfPoints via the point indices relative to the
// CATCldUniCell.
//==============================================================================================================

  /**
   * Returns the coordinates of the <tt>iNoPoint</tt>'th point
   * of the <tt>CATCldUniCell</tt>.
   */
  virtual void GetNumCoords (const int iNoPoint,
                             float     oCoords[3]) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iNoPoint</tt>'th point
   * of the <tt>CATCldUniCell</tt>.
   */
  virtual void GetNumCoords (const int iNoPoint,
                             double    oCoords[3]) const = 0 ;

  /**
   * Returns the associated information of the <tt>iNoPoint</tt>'th
   * point of the <tt>CATCldUniCell</tt>.
   */
  virtual void GetNumInfo (const int      iNoPoint,
                           CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the
   * <tt>iNoPoint</tt>'th point of the <tt>CATCldUniCell</tt>.
   */
  virtual void GetNumPoint (const int      iNoPoint,
                            float          oCoords[3],
                            CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the
   * <tt>iNoPoint</tt>'th point of the <tt>CATCldUniCell</tt>.
   */
  virtual void GetNumPoint (const int      iNoPoint,
                            double         oCoords[3],
                            CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iNbPoints</tt> points
   * given by their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>3*iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumCoords (const int   iNbPoints,
                             const int*  iNoPoints,
                             float*     &ioCoords) const = 0 ;

  /**
   * Returns the coordinates of the <tt>iNbPoints</tt> points
   * given by their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>3*iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumCoords (const int   iNbPoints,
                             const int*  iNoPoints,
                             double*    &ioCoords) const = 0 ;

  /**
   * Returns the associated informations of the <tt>iNbPoints</tt> points
   * given by their relative indices in the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioInfos</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>iNbPoints</tt>.<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumInfos (const int       iNbPoints,
                            const int*      iNoPoints,
                            CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Returns the coordinates and the associated informations of the
   * <tt>iNbPoints</tt> points given by their relative indices in
   * the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> (resp. <tt>ioInfos</tt>)
   * is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>3*iNbPoints</tt>
   * (resp. <tt>iNbPoints</tt>).<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumPoints (const int       iNbPoints,
                             const int*      iNoPoints,
                             float*         &ioCoords,
                             CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Returns the coordinates and the associated informations of the
   * <tt>iNbPoints</tt> points given by their relative indices in
   * the <tt>CATCldUniCell</tt>.<br>
   * <b>CAUTION:</b> If <tt>ioCoords</tt> (resp. <tt>ioInfos</tt>)
   * is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be at least <tt>3*iNbPoints</tt>
   * (resp. <tt>iNbPoints</tt>).<br>
   * In both cases its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   */
  virtual void GetNumPoints (const int       iNbPoints,
                             const int*      iNoPoints,
                             double*        &ioCoords,
                             CATCldInfoPnt* &ioInfos) const = 0 ;

  /**
   * Sets the coordinates of the <tt>iNoPoint</tt>'th point
   * of the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumCoords (const int   iNoPoint,
                             const float iCoords[3]) = 0 ;

  /**
   * Sets the coordinates of the <tt>iNoPoint</tt>'th point
   * of the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumCoords (const int    iNoPoint,
                             const double iCoords[3]) = 0 ;

  /**
   * Sets the associated information of the <tt>iNoPoint</tt>'th
   * point of the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumInfo (const int           iNoPoint,
                           const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the
   * <tt>iNoPoint</tt>'th point of the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumPoint (const int           iNoPoint,
                            const float         iCoords[3],
                            const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the
   * <tt>iNoPoint</tt>'th point of the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumPoint (const int           iNoPoint,
                            const double        iCoords[3],
                            const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates of the <tt>iNbPoints</tt> points given
   * by their relative indices in the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumCoords (const int    iNbPoints,
                             const int*   iNoPoints,
                             const float* iCoords) = 0 ;

  /**
   * Sets the coordinates of the <tt>iNbPoints</tt> points given
   * by their relative indices in the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumCoords (const int     iNbPoints,
                             const int*    iNoPoints,
                             const double* iCoords) = 0 ;

  /**
   * Sets the associated informations of the <tt>iNbPoints</tt> points
   * given by their relative indices in the <tt>CATCldUniCell</tt> to the given information.
   */
  virtual void SetNumInfo (const int           iNbPoints,
                           const int*          iNoPoints,
                           const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the associated informations of the <tt>iNbPoints</tt> points
   * given by their relative indices in the <tt>CATCldUniCell</tt> to the given informations.
   */
  virtual void SetNumInfos (const int            iNbPoints,
                            const int*           iNoPoints,
                            const CATCldInfoPnt* iInfos) = 0 ;

  /**
   * Sets the coordinates and the associated informations of the
   * <tt>iNbPoints</tt> points given by their relative indices in the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumPoints (const int            iNbPoints,
                             const int*           iNoPoints,
                             const float*         iCoords,
                             const CATCldInfoPnt* iInfos) = 0 ;

  /**
   * Sets the coordinates and the associated informations of the
   * <tt>iNbPoints</tt> points given by their relative indices in the <tt>CATCldUniCell</tt>.
   */
  virtual void SetNumPoints (const int            iNbPoints,
                             const int*           iNoPoints,
                             const double*        iCoords,
                             const CATCldInfoPnt* iInfos) = 0 ;

} ;

CATDeclareHandler (CATCldUniCell, CATCldCell) ;

#endif
