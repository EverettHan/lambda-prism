// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointCellIterator.h
//
//===================================================================
// 24/04/19 : F1Z : Creation
// DD/MM/YY
//===================================================================

#ifndef CATPolyCellPointIterator_H
#define CATPolyCellPointIterator_H

#include <string.h>
#include "PolyBodyTools.h"

#include <utility>
#include <memory>

class CATPolyBody;
class CATPolyCellPoint;

/**
 * Iterator through a subset of CATPolyCellPoint
 * from one or several poly bodies.
 */
class ExportedByPolyBodyTools CATPolyCellPointIterator
{
public:
  virtual ~CATPolyCellPointIterator() {};

  virtual CATPolyCellPointIterator & Begin () = 0;
  virtual bool End() = 0;
  virtual CATPolyCellPointIterator & operator++() = 0;

  virtual const int                GetTag()       const = 0; // Tag useful to identify operand
  virtual const CATPolyBody      * GetPolyBody () const = 0;
  virtual const CATPolyCellPoint * GetCellPoint() const = 0;
};

/**
 * Iterator on N cell points (N defined at compile time)
 */
template<int N>
class CATPolyNCellPointIterator : public CATPolyCellPointIterator
{
public:
  // -------------------------------------------------------------------
  // Object Management
  // -------------------------------------------------------------------
  CATPolyNCellPointIterator(const CATPolyCellPoint * iPointCell[N],
                            const CATPolyBody      * iPolyBody [N],                        
                            const int                iTag      [N]);
#ifndef _AIX
  template<typename ...Args>
  CATPolyNCellPointIterator(const CATPolyCellPoint * iPointCell,
                            const CATPolyBody      * iPolyBody ,
                            const int                iTag      ,
                                  Args&&...           iArgs    );
#endif

  virtual ~CATPolyNCellPointIterator(){};

  // -------------------------------------------------------------------
  // Iterator interface
  // -------------------------------------------------------------------
  virtual CATPolyNCellPointIterator & Begin () { _index = 0; return *this; };
  virtual bool End() { return _index>=N; };
  virtual CATPolyNCellPointIterator & operator++() { ++_index; return *this; };

  inline const CATPolyBody      * GetPolyBody () const { return _polyBody [_index]; };
  inline const CATPolyCellPoint * GetCellPoint() const { return _pointCell[_index]; };
  inline const int                GetTag      () const { return _tag      [_index]; };

protected:
  // -------------------------------------------------------------------
  // Protected methods
  // -------------------------------------------------------------------
  CATPolyNCellPointIterator();

#ifndef _AIX
  template<typename ...Args>
  void Initialize(      int                iId       ,
                  const CATPolyCellPoint * iPointCell,   
                  const CATPolyBody      * iPolyBody ,
                  const int                iTag      ,
                        Args&&...          iArgs     );

  void Initialize(int                iId,
                  const CATPolyCellPoint * iPointCell,
                  const CATPolyBody * iPolyBody,
                  const int                iTag);
#endif

  inline unsigned int GetIndex() { return _index; };

private:
  // -------------------------------------------------------------------
  // Attributs
  // -------------------------------------------------------------------
  const CATPolyBody      * _polyBody [N];
  const CATPolyCellPoint * _pointCell[N];
        int                _tag      [N];

  unsigned int _index;
};

/**
 * Get the first N cell points from iCellPoints
 * If they are not enough points, set the remaining space to 0
 */
template<int N>
void GetFirstsCellPoints(      CATPolyCellPointIterator & iCellPoints   ,
                         const CATPolyCellPoint         * oCellPoints[N],
                         const CATPolyBody              * oPolyBody  [N],
                               int                        oTag       [N])
{
  int k = 0;
  iCellPoints.Begin();
  for(; !iCellPoints.End() && k<N; ++iCellPoints)
  {
    oCellPoints[k] = iCellPoints.GetCellPoint();
    oPolyBody  [k] = iCellPoints.GetPolyBody();
    oTag       [k] = iCellPoints.GetTag();
  }
  for(; k<N; ++k)
  {
    oCellPoints[k] = 0;
    oPolyBody[k] = 0;
    oTag[k] = 0;
  }
}

template<int N>
CATPolyNCellPointIterator<N>::CATPolyNCellPointIterator()
{
  memset(_polyBody , 0, sizeof(const CATPolyBody*     )*N);
  memset(_pointCell, 0, sizeof(const CATPolyCellPoint*)*N);
  memset(_tag      , 0, sizeof(const int              )*N);
};

template<int N>
CATPolyNCellPointIterator<N>::CATPolyNCellPointIterator(const CATPolyCellPoint * iPointCell[N],
                                                        const CATPolyBody      * iPolyBody [N],
                                                        const int                iTag      [N])
{
  memcpy(_pointCell, iPointCell, sizeof(const CATPolyCellPoint*)*N);
  memcpy(_polyBody , iPolyBody , sizeof(const CATPolyBody*     )*N);
  memcpy(_tag      , iTag      , sizeof(const int              )*N);
};

#ifndef _AIX
template<int N>
template<typename ...Args>
CATPolyNCellPointIterator<N>::CATPolyNCellPointIterator(const CATPolyCellPoint * iPointCell,
                                                        const CATPolyBody      * iPolyBody ,
                                                        const int                iTag      ,
                                                              Args&&...          iArgs     )
{
  memset(_polyBody , 0, sizeof(const CATPolyBody*     )*N);
  memset(_pointCell, 0, sizeof(const CATPolyCellPoint*)*N);
  memset(_tag      , 0, sizeof(const int              )*N);

  Initialize(0, iPointCell, iPolyBody, iTag, std::forward<Args>(iArgs)...);
};

template<int N>
void CATPolyNCellPointIterator<N>::Initialize(int                iId,
                                              const CATPolyCellPoint * iPointCell,
                                              const CATPolyBody * iPolyBody,
                                              const int                iTag)
{
  _polyBody[iId] = iPolyBody;
  _pointCell[iId] = iPointCell;
  _tag[iId] = iTag;
}

template<int N>
template<typename ...Args>
void CATPolyNCellPointIterator<N>::Initialize(      int                iId       ,
                                              const CATPolyCellPoint * iPointCell,
                                              const CATPolyBody      * iPolyBody ,
                                              const int                iTag      ,
                                                    Args&&...          iArgs     )
{
  _polyBody [iId] = iPolyBody;
  _pointCell[iId] = iPointCell;
  _tag      [iId] = iTag;
  Initialize(iId++, iArgs...);
};

#endif

/**
 * We export the most used cases
 */
template class ExportedByPolyBodyTools CATPolyNCellPointIterator<1>;
template class ExportedByPolyBodyTools CATPolyNCellPointIterator<2>;


#endif
