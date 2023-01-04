#ifndef CATMathBoxQuery_h
#define CATMathBoxQuery_h

// COPYRIGHT : DASSAULT SYSTEMES 1997

#include "YN000MAT.h"

#include "CATMathBox.h"
#include "CATMathPoint.h"


class CATMathSetOfLongs;
/**
 * Class representing a set of CATMathBoxs pre-processed for efficace
 * intersection queries.
 *<br>The preprocessing applies a grid of <tt>iRange * iRange</tt> cells
 * on the CATMathBox2Ds and determines all the boxes interacting with
 * a given cell.
 * <br>CAUTION: The input CATMathBox input array is not duplicated.
 */
class ExportedByYN000MAT CATMathBoxQuery
{
 public:

 CATMathBoxQuery();

 /**
 *deprecated V5R20  Set
 * Do not use it anymore. Use rather the set method 
  * Constructs a pre-processed set of CATMathBoxs.
  */
  CATMathBoxQuery(CATMathBox iBoxToUse[] , int iNbBoxToUse);

  /**
  * Constructs a pre-processed set of CATMathBoxs.
  * return <tt>E_FAIL</tt> if one of the boxof the set is empty,
  * <tt>S_OK</tt> otherwise.
  */
  HRESULT Set(CATMathBox iBoxToUse[] , int iNbBoxToUse);

/**
  * Destructor.
  */
   ~CATMathBoxQuery();
   
 /**
   *deprecated V5R20 NbBoxIntersected
  * Returns the number of CATMathBoxs of a CATMathBoxQuery
  * intersecting a given CATMathBox.
  */
   int NbBoxIntersected(const CATMathBox& iBoxToIntersect);

/**
  * Retrieves the number of CATMathBoxs of a CATMathBoxQuery
  * intersecting a given CATMathBox.
  * Returns <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
  */
     HRESULT NbBoxIntersected(const CATMathBox& iBoxToIntersect, int & ioNbBoxIntersected);
 
 /**
  *deprecated V5R20 BoxesIntersected
  * Retrieves the CATMathBoxs of a CATMathBoxQuery
  * intersecting a given CATMathBox.
  * @param iBoxToIntersect
  * The CATMathBox to intersect with all boxes of the
  * CATMathBoxQuery.
  * @param iNbIndex
  * The maximal number of <tt>int</tt> in <tt>iIndex[]</tt>.
  * @param oIndex[]
  * The array of the index numbers in the CATMathBoxQuery of the
  * CATMathBox intersecting <tt>iBoxToIntersect</tt> limited to
  * <tt>iNbIndex</tt> values.
  * @return
  * The real number of CATMathBoxs of the CATMathBoxQuery 
  * intersecting <tt>iBoxToIntersect</tt>.
  */
   int BoxesIntersected(const CATMathBox& iBoxToIntersect,
	   int iNbIndex, int oIndex[]);

    /**
  * Retrieves the CATMathBoxs of a CATMathBoxQuery
  * intersecting a given CATMathBox.
  * @param iBoxToIntersect
  * The CATMathBox to intersect with all boxes of the
  * CATMathBoxQuery.
  * @param iNbIndex
  * The maximal number of <tt>int</tt> in <tt>iIndex[]</tt>.
  * @param oIndex[]
  * The array of the index numbers in the CATMathBoxQuery of the
  * CATMathBox intersecting <tt>iBoxToIntersect</tt> limited to
  * <tt>iNbIndex</tt> values.
  *@param ioBoxNb
  * The real number of CATMathBoxs of the CATMathBoxQuery 
  * intersecting <tt>iBoxToIntersect</tt>.
  * @return
   * Returns <tt>E_FAIL</tt> if the box is empty, <tt>S_OK</tt> otherwise.
  
  */    
   HRESULT BoxesIntersected(const CATMathBox& iBoxToIntersect,
	   int iNbIndex, int oIndex[], int & ioBoxNb);
 
 protected:

/**
* deprecated V5R20 InitializeRange
* Do not use anymore. Prefer InitializeRange which returns an HRESULT.
 * Modifies the number of cells used to cover the boxes of a
 * CATMathBoxQuery.
 */
   void SetRange(int iiRange);

/**
 * Modifies the number of cells used to cover the boxes of a
 * CATMathBoxQuery.
 * return <tt>E_FAIL</tt> if one of the box of the set is empty,
 * <tt>S_OK</tt> otherwise.
 */
   HRESULT InitializeRange(int iiRange);

/**
 * Returns the number of cells used to cover the boxes of a
 * CATMathBoxQuery.
 */
   int GetRange() const;
   
   void Purge();
   void Localize(const CATMathPoint&, int&i, int&j, int&k) const;
   int InternalQuery(const CATMathBox&, int, int*); // deprecated V5R20 InternalQuery
   HRESULT InternalQuery(const CATMathBox&, int, int*,int &);
   
   CATMathBox    *_boxes;
   CATMathPoint   _min;
   CATMathPoint   _max;
   CATMathSetOfLongs **** _cells;
   int   _nboxes;
   int   _range;
   int * _tempArray;
};

#endif


