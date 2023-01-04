// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyUnstreamRecord.h
//
//===================================================================
// February 2010 Creation: NDO
// July     2014 Modification JXO: current max tag
//===================================================================
#ifndef CATPolyUnstreamRecord_H
#define CATPolyUnstreamRecord_H

#include "PolyStream.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"  // HRESULT
#include "CATMapOfIntToPtr.h"

class CATPolyBody;
class CATPolyCell;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolyLayer;
class CATMapOfIDToPolyRefCounted;


/**
 * This class records distinct unsigned integer tags and associates them to 
 * CATIPolyPoint's, CATIPolyCurve's and CATIPolySurface's entities.
 * A tag found in the record means that its associated entity has been unstreamed.
 * The lifecycle of the recorded entities is managed with calls to <code>AddRef</code> and <code>Release</Code>.
 */
class ExportedByPolyStream CATPolyUnstreamRecord
{

public:

  CATPolyUnstreamRecord ();
  ~CATPolyUnstreamRecord ();

public:

/** @name Queries 
    @{ */

    /**
     * Finds a tag in the records and returns its associated CATPolyCell.
     * @param iTag
     *   An input tag.
     * @param oPolyBody
     *   Its output CATPolyBody.
     * @return
     * <ul>
     *   <li> <code> TRUE </code> if the tag is found and the cell is set.
     *   <li> <code> FALSE </code> otherwise.
     * </ul>
     */
  CATBoolean Find (const int iTag, CATPolyBody*& oPolyBody) const;

  /**
   * Finds a tag in the records and returns its associated CATPolyCell.
   * @param iTag
   *   An input tag.
   * @param oCell
   *   Its output CATPolyCell.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the tag is found and the cell is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  CATBoolean Find (const int iTag, CATPolyCell*& oCell) const;

  /**
   * Finds a tag in the records and returns its associated point entity.
   * @param iTag
   *   An input tag.
   * @param oPoint
   *   Its output CATIPolyPoint.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the tag is found and the point is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  CATBoolean Find (const int iTag, CATIPolyPoint*& oPoint) const;

  /**
   * Finds a tag in the records and returns its associated curve entity.
   * @param iTag
   *   An input tag.
   * @param oCurve
   *   Its output CATIPolyCurve.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the tag is found and the curve is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  CATBoolean Find (const int iTag, CATIPolyCurve*& oCurve) const;

  /**
   * Finds a tag in the records and returns its associated surface entity.
   * @param iTag
   *   An input tag.
   * @param oSurface
   *   Its output CATIPolySurface.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the tag is found and the surface is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  CATBoolean Find (const int iTag, CATIPolySurface*& oSurface) const;

  /**
   * Finds a tag in the records and returns its associated layer.
   * @param iTag
   *   An input tag.
   * @param oLayer
   *   Its output layer.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the tag is found and the layer is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  CATBoolean Find (const int iTag, CATIPolyLayer*& oLayer) const;

  /** @} */

public:

/** @name Recording Tags and Entities
    @{ */

  /**
    * @nodoc
    * Inserts a tag and a CATPolyBody as a new record.
    * @param iTag
    *   The tag.
    * @param iPolyBody
    *   A CATPolyBody.
    * @return
    * <ul>
    *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
    *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
    * </ul>
    */
  HRESULT Record (unsigned int iTag, CATPolyBody* iPolyBody);

  /**
   * @nodoc
   * Inserts a tag and a cell as a new record.
   * @param iTag
   *   The tag.
   * @param iCell
   *   A CATPolyCell.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (unsigned int iTag, CATPolyCell* iCell);

  /**
   * @nodoc
   * Inserts a tag and a point entity as a new record.
   * @param iTag
   *   The tag.
   * @param iPoint
   *   A point entity.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (unsigned int iTag, CATIPolyPoint* iPoint);

  /**
   * @nodoc
   * Inserts a tag and a curve entity as a new record.
   * @param iTag
   *   The tag.
   * @param iCurve
   *   A curve entity.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (unsigned int iTag, CATIPolyCurve* iCurve);

  /**
   * @nodoc
   * Inserts a tag and a surface entity as a new record.
   * @param iTag
   *   The tag.
   * @param iSurface
   *   A surface entity.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (unsigned int iTag, CATIPolySurface* iSurface);

  /**
   * @nodoc
   * Inserts a tag and a layer as a new record.
   * @param iTag
   *   The tag.
   * @param iLayer
   *   A layer.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the tag and entity are successfully recorded.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (unsigned int iTag, CATIPolyLayer* iLayer);

  HRESULT RecordAllEntities (unsigned int iTag, const CATPolyBody& iPolyBody);

/** @} */

public:

  /**
   * @nodoc
   * Generates a new distinct tag that can be associated to an entity to be recorded.
   * Tags generated by different means should not be mixed.
   * If this mode of generating tags is used, then it should be used to generate all tags.
   * @return
   *   A tag.
   */
  unsigned int GenerateTag ();

private:

  // Maps a tag to a CATPolyBody.
  CATMapOfIntToPtr          _MapTagToPolyBody;

  // Maps a tag to a CATPolyCell.
  CATMapOfIntToPtr          _MapTagToPolyCell;

  // Maps of tags to a points, curves, surfaces and layers.
  CATMapOfIDToPolyRefCounted* _MapTagToPolyPoint;
  CATMapOfIDToPolyRefCounted* _MapTagToPolyCurve;
  CATMapOfIDToPolyRefCounted* _MapTagToPolySurface;
  CATMapOfIDToPolyRefCounted* _MapTagToPolyLayer;

  // The last tag that has been used.
  unsigned int _Tag;

};

#endif
