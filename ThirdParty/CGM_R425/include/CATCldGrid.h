//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldGrid
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldGrid_H
#define CATCldGrid_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldUniCell.h"

#include "CATMathAxis.h"

class CATCldScan ;
class CATCldSetOfScans ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldGrid ;
#else
extern "C" const IID IID_CATCldGrid ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldGrid</tt>.<br>
 * The <tt>CATCldGrid</tt> corresponds to 2D <i>ordered</i> set of points.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell
 */
class ExportedByCATGMGeometricInterfaces CATCldGrid : public CATCldUniCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldGrid characteristics.
//==============================================================================================================

  /**
   * Tests if the <tt>CATCldGrid</tt> has a probe axis.
   */
  virtual CATBoolean HasAProbeAxis () const = 0 ;

  /**
   * Returns the probe axis of the <tt>CATCldGrid</tt>.<br>
   * Throws an exception if the <tt>CATCldGrid</tt> has not a probe axis.
   */
  virtual const CATMathAxis& GetProbeAxis () const = 0 ;

  /**
   * Sets the probe axis of the <tt>CATCldGrid</tt>.
   */
  virtual void SetProbeAxis (const CATMathAxis* iAxis) = 0 ;

  /**
   * Converts the grid in a set of scans with deletion of the null indexes.<br>
   * The set of scans references the same <tt>CATCldSetOfPoints</tt> than the grid.
   */
  virtual CATCldSetOfScans* ConvertInScans () const = 0 ;

  /**
   * Converts a 1D-indice to the 2D-indices relative to the <tt>CATCldGrid</tt>.
   */
  virtual void Num1DTo2D (const int  iNoPoint,
                          int       &oNoPointU,
                          int       &oNoPointV) const = 0 ;

  /**
   * Converts 2D-indices to the 1D-indice relative to the <tt>CATCldGrid</tt>.
   */
  virtual void Num2DTo1D (const int  iNoPointU,
                          const int  iNoPointV,
                          int       &oNoPoint) const = 0 ;

//==============================================================================================================
// Added methods for the public access to the SetOfPoints specific to the CATCldGrid.
//==============================================================================================================

  /**
   * Returns the two dimensions of the grid.
   */
  virtual void GetNbPointsUV (int &oNbPointsU,
                              int &oNbPointsV) const = 0 ;

  /**
   * Returns the indexes 2D-array.<br>
   * <b>CAUTION:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done
   * by the method.<br>
   * Otherwise it has to be done by the calling method, its sizes must be greater
   * than the expected <tt>oNbPointsU</tt> and <tt>oNbPointsV</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.
   */
  virtual void GetPointsUV (int   &oNbPointsU,
                            int   &oNbPointsV,
                            int** &ioIndexes) const = 0 ;

  /**
   * Returns the indexes array for a row.<br>
   * <b>CAUTION:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be greater
   * than the expected <<t>>oNbPointsV</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.
   */
  virtual void GetPointsV (const int  iNoRowU,
                           int       &oNbPointsV,
                           int*      &ioIndexes) const = 0 ;

  /**
   * Returns the indexes array for a column.<br>
   * <b>CAUTION:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be greater
   * than the expected <<t>>oNbPointsU</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.
   */
  virtual void GetPointsU (const int  iNoColV,
                           int       &oNbPointsU,
                           int*      &ioIndexes) const = 0 ;

//==============================================================================================================
// Specific points management for the CATCldGrid.
//==============================================================================================================

  /**
   * Adds points given by their coordinates.<br>
   * <b>CAUTION:</b> An exception is raised if <tt>iNbPoints</tt> is different
   * from the first call of the <tt>AddLine</tt> or <tt>AddScan(s)</tt> methods.
   */
  virtual void AddLine (const int    iNbPoints,
                        const float* iCoords) = 0 ;

  /**
   * Adds points given by their coordinates.<br>
   * <b>CAUTION:</b> An exception is raised if <tt>iNbPoints</tt> is different
   * from the first call of the <tt>AddLine</tt> or <tt>AddScan(s)</tt> methods.
   */
  virtual void AddLine (const int     iNbPoints,
                        const double* iCoords) = 0 ;

  /**
   * Adds points given by their coordinates and returns
   * their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> An exception is raised if <tt>iNbPoints</tt>
   * is different from the first call of the <tt>AddLine</tt> or
   * <tt>AddScan(s)</tt> methods.
   */
  virtual void AddLine (const int     iNbPoints,
                        const float*  iCoords,
                        int*         &ioIndexes) = 0 ;

  /**
   * Adds points given by their coordinates and returns
   * their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION 1:</b> If <tt>ioIndexes</tt> is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method,
   * its size must be greater than <tt>iNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no points.<br>
   * <b>CAUTION 2:</b> An exception is raised if <tt>iNbPoints</tt>
   * is different from the first call of the <tt>AddLine</tt> or
   * <tt>AddScan(s)</tt> methods.
   */
  virtual void AddLine (const int      iNbPoints,
                        const double*  iCoords,
                        int*          &ioIndexes) = 0 ;

  /**
   * Adds points given by their indexes in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> An exception is raised if <tt>iNbPoints</tt>
   * is different from the first call of the <tt>AddLine</tt> or
   * <tt>AddScan(s)</tt> methods.
   */
  virtual void AddLine (const int  iNbPoints,
                        const int* iIndexes) = 0 ;

  /**
   * Adds a <tt>CATCldScan</tt>.<br>
   * <b>CAUTION:</b> An exception is raised if the number of points
   * of the given scan is different from the first call of the
   * <tt>AddLine</tt> or <tt>AddScan(s)</tt> methods.
   */
  virtual void AddScan  (const CATCldScan* iScan) = 0 ;

  /**
   * Adds several <tt>CATCldScan</tt>.<br>
   * <b>CAUTION:</b> An exception is raised if the number of points
   * of each given scan is different from the first call of the
   * <tt>AddLine</tt> or <tt>AddScan(s)</tt> methods.
   */
  virtual void AddScans (const int    iNbScans,
                         CATCldScan** iScans) = 0 ;

  /**
   * Adds a <tt>CATCldSetOfScans</tt>.<br>
   * <b>CAUTION:</b> An exception is raised if the number of points
   * of each scan in the set of scans is different from the first
   * call of the <tt>AddLine</tt> or <tt>AddScan(s)</tt> methods.
   */
  virtual void AddScan (const CATCldSetOfScans* iScans) = 0 ;

  /**
   * Removes one point given by its relative indices in the <tt>CATCldGrid</tt>.<br>
   * A point is removed by setting its index to 0.
   */
  virtual void RemovePointUV (const int iNoPointU,
                              const int iNoPointV) = 0 ;

//==============================================================================================================
// Management of the point flag.
//==============================================================================================================

  /**
   * Tests if the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> is active.
   */
  virtual CATBoolean IsActiveUV (const int iNoPointU,
                                 const int iNoPointV) const = 0 ;

  /**
   * Tests if the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> is selected.
   */
  virtual CATBoolean IsSelectedUV (const int iNoPointU,
                                   const int iNoPointV) const = 0 ;

  /**
   * Sets the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> as selected.
   */
  virtual void SetSelectedUV (const int iNoPointU,
                              const int iNoPointV) = 0 ;

  /**
   * Sets the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> as unselected.
   */
  virtual void SetUnselectedUV (const int iNoPointU,
                                const int iNoPointV) = 0 ;

  /**
   * Tests if the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> is filtered.
   */
  virtual CATBoolean IsFilteredUV (const int iNoPointU,
                                   const int iNoPointV) const = 0 ;

  /**
   * Sets the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> as filtered.<br>
   * <b>CAUTION:</b> The point becomes inactive and invisible.
   */
  virtual void SetFilteredUV (const int iNoPointU,
                              const int iNoPointV) = 0 ;

  /**
   * Sets the <tt>(iNoPointU,iNoPointV)</tt>'th point in the
   * <tt>CATCldGrid</tt> as unfiltered.
   */
  virtual void SetUnfilteredUV (const int iNoPointU,
                                const int iNoPointV) = 0 ;

//==============================================================================================================
// Indexes management in a CATCldUniCell.
//==============================================================================================================

  /**
   * Returns the index in the <tt>CATCldSetOfPoints</tt> of the <tt>(iNoPointU,iNoPointV)</tt>'th
   * point in the <tt>CATCldGrid</tt>.
   */
  virtual int GetIndexUV (const int iNoPointU,
                          const int iNoPointV) const = 0 ;

  /**
   * Sets the index in the <tt>CATCldSetOfPoints</tt> of the <tt>(iNoPointU,iNoPointV)</tt>'th point
   * in the <tt>CATCldGrid</tt>.
   */
  virtual void SetIndexUV (const int iNoPointU,
                           const int iNoPointV,
                           const int iIndex) = 0 ;

  /**
   * Swaps the indexes in the <tt>CATCldSetOfPoints</tt> of the <tt>(iNoPointU1,iNoPointV1)</tt>'th and the
   * <tt>(iNoPointU2,iNoPointV2)</tt>'th points in the <tt>CATCldrid</tt>.
   */
  virtual void SwapIndexesUV (const int iNoPointU1,
                              const int iNoPointV1,
                              const int iNoPointU2,
                              const int iNoPointV2) = 0 ;

  /**
   * Returns the relative indices in the <tt>CATCldGrid</tt> of a point
   * from its index in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual void GetNumPointUV (const int  iIndex,
                              int       &oNoPointU,
                              int       &oNoPointV) const = 0 ;

//==============================================================================================================
// The following methods are the public access to the SetOfPoints via the point indices relative to the
// CATCldGrid.
//==============================================================================================================

  /**
   * Returns the coordinates of the <tt>(iNoPointU,iNoPointV)</tt>'th point
   * of the <tt>CATCldGrid</tt>.
   */
  virtual void GetNumCoordsUV (const int iNoPointU,
                               const int iNoPointV,
                               float     oCoords[3]) const = 0 ;

  /**
   * Returns the coordinates of the <tt>(iNoPointU,iNoPointV)</tt>'th point
   * of the <tt>CATCldGrid</tt>.
   */
  virtual void GetNumCoordsUV (const int iNoPointU,
                               const int iNoPointV,
                               double    oCoords[3]) const = 0 ;

  /**
   * Returns the associated information of the <tt>(iNoPointU,iNoPointV)</tt>'th
   * point of the <tt>CATCldGrid</tt>.
   */
  virtual void GetNumInfoUV (const int      iNoPointU,
                             const int      iNoPointV,
                             CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the
   * <tt>(iNoPointU,iNoPointV)</tt>'th point of the <tt>CATCldGrid</tt>.
   */
  virtual void GetNumPointUV (const int      iNoPointU,
                              const int      iNoPointV,
                              float          oCoords[3],
                              CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Returns the coordinates and the associated information of the
   * <tt>(iNoPointU,iNoPointV)</tt>'th point of the <tt>CATCldGrid</tt>.
   */
  virtual void GetNumPointUV (const int      iNoPointU,
                              const int      iNoPointV,
                              double         oCoords[3],
                              CATCldInfoPnt &oInfo) const = 0 ;

  /**
   * Sets the coordinates of the <tt>(iNoPointU,iNoPointV)</tt>'th point
   * of the <tt>CATCldGrid</tt>.
   */
  virtual void SetNumCoordsUV (const int   iNoPointU,
                               const int   iNoPointV,
                               const float iCoords[3]) = 0 ;

  /**
   * Sets the coordinates of the <tt>(iNoPointU,iNoPointV)</tt>'th point
   * of the <tt>CATCldGrid</tt>.
   */
  virtual void SetNumCoordsUV (const int    iNoPointU,
                               const int    iNoPointV,
                               const double iCoords[3]) = 0 ;

  /**
   * Sets the associated information of the <tt>(iNoPointU,iNoPointV)</tt>'th
   * point of the <tt>CATCldGrid</tt>.
   */
  virtual void SetNumInfoUV (const int           iNoPointU,
                             const int           iNoPointV,
                             const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the
   * <tt>(iNoPointU,iNoPointV)</tt>'th point of the <tt>CATCldGrid</tt>.
   */
  virtual void SetNumPointUV (const int           iNoPointU,
                              const int           iNoPointV,
                              const float         iCoords[3],
                              const CATCldInfoPnt iInfo) = 0 ;

  /**
   * Sets the coordinates and the associated information of the
   * <tt>(iNoPointU,iNoPointV)</tt>'th point of the <tt>CATCldGrid</tt>.
   */
  virtual void SetNumPointUV (const int           iNoPointU,
                              const int           iNoPointV,
                              const double        iCoords[3],
                              const CATCldInfoPnt iInfo) = 0 ;

} ;

CATDeclareHandler (CATCldGrid, CATCldUniCell) ;

#endif
