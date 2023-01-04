#ifndef CATMathBox2DQuery_h
#define CATMathBox2DQuery_h

// COPYRIGHT : DASSAULT SYSTEMES 1997

#include "YN000M2D.h"

#include "CATMathBox2D.h"
#include "CATMathPoint2D.h"

class CATMathSetOfLongs;
/**
 * Class representing a set of CATMathBox2Ds pre-processed for efficace
 * intersection queries.
 *<br>The preprocessing applies a grid of <tt>iRange * iRange</tt> cells
 * on the CATMathBox2Ds and determines all the boxes interacting with
 * a given cell. 
 * <br>CAUTION: The input CATMathBox input array is not duplicated.
 */
class ExportedByYN000M2D CATMathBox2DQuery
{
 public:
 /**
  * Constructs a pre-processed set of CATMathBox2Ds.
  */
   CATMathBox2DQuery(CATMathBox2D iBoxToUse[], int iNbBoxToUse);

/**
  * Destructor.
  */
   ~CATMathBox2DQuery();

 /**
  * Returns the number of CATMathBox2Ds of a CATMathBox2DQuery
  * intersecting a given CATMathBox2D.
  */
   int NbBoxIntersected(const CATMathBox2D& iBoxToIntersect);

 /**
  * Retrieves the CATMathBox2Ds of a CATMathBox2DQuery
  * intersecting a given CATMathBox2D.
  * @param iBoxToIntersect
  * The CATMathBox2D to intersect with all boxes of the
  * CATMathBox2DQuery.
  * @param iNbIndex
  * The maximal number of <tt>int</tt> in <tt>iIndex[]</tt>.
  * @param oIndex[]
  * The array of the index numbers in the CATMathBox2DQuery of the
  * CATMath2DBox intersecting <tt>iBoxToIntersect</tt> limited to
  * <tt>iNbIndex</tt> values.
  * @return
  * The real number of CATMathBox2Ds of the CATMathBox2DQuery 
  * intersecting <tt>iBoxToIntersect</tt>.
  */
   int BoxesIntersected(const CATMathBox2D& iBoxToIntersect,
	                    int iNbIndex, int oIndex[], double iTolerance = 0.0);
   
 
 protected:
/**
 * Modifies the number of cells used to cover the boxes of a
 * CATMathBox2DQuery.
 */
   void SetRange(int iRange);

/**
 * Returns the number of cells used to cover the boxes of a
 * CATMathBox2DQuery.
 */
   int GetRange() const;
   

   void Localize(const CATMathPoint2D&, int&i, int&j) const;
   int InternalQuery(const CATMathBox2D&, int, int*, double iTolerance = 0.0);
   void Purge();
   
   CATMathBox2D  *_boxes;
   CATMathPoint2D   _min;
   CATMathPoint2D   _max;
   // OLD CATMathIntCollection *** _cells;
   CATMathSetOfLongs *** _cells;

   int   _nboxes;
   int   _range;
   int * _tempArray;
};

#endif


