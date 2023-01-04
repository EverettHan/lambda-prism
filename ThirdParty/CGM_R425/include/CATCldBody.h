//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldBody
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldBody_H
#define CATCldBody_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldGenEntity.h"

#include "CATListOfCATCldCells.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldBody ;
#else
extern "C" const IID IID_CATCldBody ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldBody</tt>.<br>
 * @see CATCldGenEntity
 */
class ExportedByCATGMGeometricInterfaces CATCldBody : public CATCldGenEntity
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldBody characteristics.
//==============================================================================================================

  /**
   * Gets the <i>CharacteristicDistance</i> which is an estimation of the max
   * of the min distances between points.<br>
   * It defines the neighbourhood : for each point of the <tt>CATCldBody</tt>, there is
   * at least one point lying at a distance less than the <i>CharacteristicDistance</i>.
   */
  virtual double GetCharacteristicDistance () const = 0 ;

  /**
   * Sets the <i>CharacteristicDistance</i> which is an estimation of the max
   * of the min distances between points.<br>
   * It defines the neighbourhood : for each point of the <tt>CATCldBody</tt>, there is
   * at least one point lying at a distance less than the <i>CharacteristicDistance</i>.
   */
  virtual void SetCharacteristicDistance (const double iDistance) = 0 ;

//==============================================================================================================
// Points.
//==============================================================================================================

  /**
   * Adds a point into the <tt>CATCldSetOfPoints</tt>.<br>
   * @param iCoords
   * The coordinates of the point to add.
   * @param oIndex
   * The index of the added point in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual void AddPoint (const float iCoords[3],
                         int &oIndex) = 0 ;

  /**
   * Adds a point into the <tt>CATCldSetOfPoints</tt>.<br>
   * @param iCoords
   * The coordinates of the point to add.
   * @param oIndex
   * The index of the added point in the <tt>CATCldSetOfPoints</tt>.
   */
  virtual void AddPoint (const double iCoords[3],
                         int &oIndex) = 0 ;

  /**
   * Adds <tt>iNbPoints</tt> points into the <tt>CATCldSetOfPoints</tt>.<br>
   * @param iCoords
   * The coordinates of the points to add.
   * @param ioIndexes
   * The indexes of the added points in the <tt>CATCldSetOfPoints</tt>.
   * <b>CAUTION:</b><br>
   * If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.
   */
  virtual void AddPoints (const int     iNbPoints,
                          const float*  iCoords,
                          int*         &ioIndexes) = 0 ;

  /**
   * Adds <tt>iNbPoints</tt> points into the <tt>CATCldSetOfPoints</tt>.<br>
   * @param iCoords
   * The coordinates of the points to add.
   * @param ioIndexes
   * The indexes of the added points in the <tt>CATCldSetOfPoints</tt>.
   * <b>CAUTION:</b><br>
   * If <tt>ioIndexes</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no points.
   */
  virtual void AddPoints (const int      iNbPoints,
                          const double*  iCoords,
                          int*          &ioIndexes) = 0 ;

//==============================================================================================================
// Sub-elements management
//==============================================================================================================

  /**
   * Inserts a <tt>CATCldBody</tt>.<br>
   * If the given <tt>CATCldBody</tt> references the same <tt>CATCldSetOfPoints</tt> than the considered
   * <tt>CATCldBody</tt>, there is a simple insertion, otherwise the given <tt>CATCldBody</tt> is copied and
   * the methods returns the copy.
   */
  virtual CATCldBody* AddBody (const CATCldBody* iBody) = 0 ;

  /**
   * Inserts a <tt>CATCldCell</tt>.<br>
   * If the given <tt>CATCldCell</tt> references the same <tt>CATCldSetOfPoints</tt> than the considered
   * <tt>CATCldBody</tt>, there is a simple insertion, otherwise the given <tt>CATCldCell</tt> is copied and
   * the methods returns the copy.
   */
  virtual CATCldCell* AddCell (const CATCldCell* iCell) = 0 ;

  /**
   * Removes a <tt>CATCldCell</tt> from the considered <tt>CATCldBody</tt>.
   */
  virtual void RemoveCell (const CATCldCell* iCell) = 0 ;

  /**
   * Returns the list of the cells of a given type in the <tt>CATCldBody</tt>.<br>
   * Each cell will occur only once in the result list.<br>
   * <b>CAUTION:</b> The list will be cleared by the method before use.<br>
   * Let be a <tt>CATCldBody B</tt> composed of a <tt>CATCldCloud C</tt>, a <tt>CATCldScan S1</tt>
   * and a <tt>CATCldSetOfScans SoS</tt> which references <tt>S1</tt> and an other
   * <tt>CATCldScan S2</tt>.<pre>
   *             +-----+
   *             |  B  |
   *             +--+--+
   *                |
   *    +-------+---+-----------+
   *    |       |               |
   * +--+--+ +--+--+         +--+--+
   * |  C  | | S1  |         | SoS |
   * +-----+ +-----+         +--+--+
   *                            |
   *                    +-------+-------+
   *                    |               |
   *                 +--+--+         +--+--+
   *                 | S1  |         | S2  |
   *                 +-----+         +--+--+
   * </pre>
   * We will have the following results :<br><pre>
   *                  | CATCldCellType | CATCldUniCellType | CATCldMultiCellType
   * -----------------+----------------+-------------------+--------------------
   * FirstLevel TRUE  | (C,S1,SoS)     | (C,S1)            | (SoS)
   * FirstLevel FALSE | (C,S1,SoS,S2)  | (C,S1,S2)         | (SoS)
   * </pre>
   */
  virtual void GetAllCells (CATLISTP(CATCldCell)   &ioCells,
                            const CATGeometricType  iType = CATCldCellType,
                            const CATBoolean        iFirstLevel = TRUE) const = 0 ;

  /**
   * Initializes an iterator on the cells of a given type in the <tt>CATCldBody</tt>.<br>
   * <br>
   * Hereafter an example of programming such an iterator : <pre>
   *    for (Cloud.Init(...) ; Cloud.More() ; Cloud.Next()) {
   *      CATCldCell* Cell = Cloud.GetCell() ;
   *      ...
   *    }
   * </pre>
   */
  virtual void Init (const CATGeometricType iType = CATCldCellType) const = 0 ;

  /**
   * Tests if there is still a cell pointed by the iterator.<br>
   */
  virtual CATBoolean More () const = 0 ;

  /**
   * Does the next cell verifying the iterator criteria to be pointed by the iterator.
   */
  virtual void Next () const = 0 ;

  /**
   * Gets the current cell pointed by the iterator.
   */
  virtual CATCldCell* GetCell () const = 0 ;

//==============================================================================================================
// CNext methods
//==============================================================================================================

///**
// * Freezes the contents of the body.<br> Further modifications of this
// * body will imply that all modified elements will be copied first,
// * thus keeping the current body state unmodified.
// */
//virtual void Freeze () = 0 ;

} ;

CATDeclareHandler (CATCldBody, CATCldGenEntity) ;

#endif
