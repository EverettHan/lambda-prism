// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyStreamRecord.h
//
//===================================================================
// February 2010 Creation: NDO
// July     2014 Modification JXO: CATPolyStreamRecordTags
//===================================================================
#ifndef CATPolyStreamRecord_H
#define CATPolyStreamRecord_H

#include "PolyStream.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"  // HRESULT

#include "CATMapOfPtrToInt.h"
#include "CATMathInline.h"

class CATPolyBody;
class CATPolyCell;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolyLayer;

class ExportedByPolyStream CATPolyStreamRecordTags
{
public:
  static int GenerateTag(int iLastTag);
};

/**
 * This class records <code>CATIPolyPoint</code>'s, <code>CATIPolyCurve</code>'s and <code>CATIPolySurface</code>'s 
 * (entities) and associates them to distinct unsigned integer tags.  
 * An entity found in the record means that it has been streamed. 
 */
class ExportedByPolyStream CATPolyStreamRecord
{

public:

  CATPolyStreamRecord ();
  ~CATPolyStreamRecord ();

public:

/** @name Queries 
    @{ */

  /**
    * Finds a CATPolyBody in the records and returns its tag.
    * @param iPolyBody
    *   An input CATPolyBody.
    * @param oTag
    *   Its output tag.
    * @return
    * <ul>
    *   <li> <code> TRUE </code> if the entity is found and its tag is set.
    *   <li> <code> FALSE </code> otherwise.
    * </ul>
    */
  inline CATBoolean Find (const CATPolyBody* iPolyBody, unsigned int& oTag) const;

  /**
   * Finds a cell in the records and returns its tag.
   * @param iCell
   *   An input CATPolyCell.
   * @param oTag
   *   Its output tag.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the entity is found and its tag is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  inline CATBoolean Find (const CATPolyCell* iCell, unsigned int& oTag) const;

  /**
   * Finds a point entity in the records and returns its tag.
   * @param iPoint
   *   An input point.
   * @param oTag
   *   Its output tag.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the entity is found and its tag is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  inline CATBoolean Find (const CATIPolyPoint* iPoint, unsigned int& oTag) const;

  /**
   * Finds a curve entity in the records and returns its tag.
   * @param iCurve
   *   An input curve.
   * @param oTag
   *   Its output tag.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the entity is found and its tag is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  inline CATBoolean Find (const CATIPolyCurve* iCurve, unsigned int& oTag) const;

  /**
   * Finds a surface entity in the records and returns its tag.
   * @param iSurface
   *   An input surface.
   * @param oTag
   *   Its output tag.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the entity is found and its tag is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  inline CATBoolean Find (const CATIPolySurface* surface, unsigned int& tag) const;

  /**
   * Finds a layer in the records and returns its tag.
   * @param layer
   *   An input layer.
   * @param oTag
   *   Its output tag.
   * @return
   * <ul>
   *   <li> <code> TRUE </code> if the entity is found and its tag is set.
   *   <li> <code> FALSE </code> otherwise.
   * </ul>
   */
  inline CATBoolean Find (const CATIPolyLayer* layer, unsigned int& tag) const;

  /** @} */

public:

/** @name Recording Entities and Tags
    @{ */

  /**
    * @nodoc
    * Inserts a CATPolyBody as a new record with its associated tag.
    * The tags should identify unambiguously the CATPolyBody entity.
    * @param iPolyBody
    *   A CATPolyBody.
    * @param iTag
    *   Its tag.
    * @return
    * <ul>
    *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
    *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
    * </ul>
    */
  HRESULT Record (const CATPolyBody* iPolyBody, unsigned int iTag);

  /**
   * @nodoc
   * Inserts a cell as a new record with its associated tag.
   * The tags should identify unambiguously the cell entity.
   * @param iCell
   *   A CATPolyCell.
   * @param iTag
   *   Its tag.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (const CATPolyCell* iCell, unsigned int iTag);

  /**
   * @nodoc
   * Inserts a point entity as a new record with its associated tag.
   * The tags should identify unambiguously the point entity.
   * @param iPoint
   *   A point entity.
   * @param iTag
   *   Its tag.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (const CATIPolyPoint* iPoint, unsigned int iTag);

  /**
   * @nodoc
   * Inserts a curve entity as a new record with its associated tag.
   * The tags should identify unambiguously the curve entity.
   * @param iCurve
   *   A curve entity.
   * @param iTag
   *   Its tag.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (const CATIPolyCurve* iCurve, unsigned int iTag);

  /**
   * @nodoc
   * Inserts a surface entity as a new record with its associated tag.
   * The tags should identify unambiguously the surface entity.
   * @param iSurface
   *   A surface entity.
   * @param iTag
   *   Its tag.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (const CATIPolySurface* iSurface, unsigned int iTag);

  /**
   * @nodoc
   * Inserts a layer as a new record with its associated tag.
   * The tags should identify unambiguously the layer.
   * @param iLayer
   *   An input layer.
   * @param iTag
   *   Its tag.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity is successfully inserted in the list of records.
   *   <li> <code> E_FAIL </code> or any other error code if an error occurs.
   * </ul>
   */
  HRESULT Record (const CATIPolyLayer* iLayer, unsigned int iTag);

  /**
   * @nodoc
   * Records the CATIPolySurface, CATIPolyCurve and CATIPolyPoint entities from the CATPolyBody
   * in the records.
   */
  HRESULT RecordAllEntities (const CATPolyBody& iPolyBody);

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

  /**
   * @nodoc
   * Returns the current tag value that has been generated by this class.
   * @return
   *   A tag.
   */
  inline unsigned int GetCurrentTag ();

private:

  // Map of a CATIPolyPoint, CATIPolyCurve or a CATIPolySurface to an identifying tag.
  CATMapOfPtrToInt _MapEntityToTag;

  // The last tag that has been used.
  unsigned int _Tag;

};

inline CATBoolean CATPolyStreamRecord::Find (const CATPolyBody* polyBody, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (polyBody, (int&) tag);
}

inline CATBoolean CATPolyStreamRecord::Find (const CATPolyCell* cell, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (cell, (int&) tag);
}

inline CATBoolean CATPolyStreamRecord::Find (const CATIPolyPoint* point, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (point, (int&) tag);
}

inline CATBoolean CATPolyStreamRecord::Find (const CATIPolyCurve* curve, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (curve, (int&) tag);
}

inline CATBoolean CATPolyStreamRecord::Find (const CATIPolySurface* surface, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (surface, (int&) tag);
}

inline CATBoolean CATPolyStreamRecord::Find (const CATIPolyLayer* layer, unsigned int& tag) const
{
  return _MapEntityToTag.Locate (layer, (int&)tag);
}

inline int CATPolyStreamRecordTags::GenerateTag (int iLastTag)
{
  return (++iLastTag);
}

inline unsigned int CATPolyStreamRecord::GetCurrentTag ()
{
  return _Tag;
}

#endif
