// Usage notes:
//=============================================================================
// 15/01/2020 : SMT1 : Creation 
//=============================================================================


#ifndef CATOptUtils_h
#define CATOptUtils_h

#include "CATOptTypes.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATMathIntervalND.h"

class CATMathSetOfLongs;


class CATOptUtils
{
public:

    // QuickSelect finds the index ioTopOfBottom, so that iSelectSize many points of iSelectSize are <= than the point of that 
    // index with respect to the iSelectDim. ioBottom and ioTop are filled with the indices of smaller and larger points, respectively.
    // Quickselect works in linear time!

    static HRESULT QuickSelect(CATSetOfOptRealND * iInputSet,
        CATLONG32           iSelectSize,
        CATLONG32           iSelectDim,
        CATLONG32         & ioTopOfBottom,
        CATMathSetOfLongs *&ioBottom, 
        CATMathSetOfLongs *&ioTop);

    static HRESULT QuickSelect(CATSetOfOptRealND * iInputSet,
        CATMathSetOfLongs * iActiveIndices,
        CATLONG32           iSelectSize,
        CATLONG32           iSelectDim,
        CATLONG32         & ioTopOfBottom,
        CATMathSetOfLongs *&ioBottom, 
        CATMathSetOfLongs *&ioTop);


private:

    static CATLONG32 PickPivot(CATSetOfOptRealND * iInputSet, 
        CATMathSetOfLongs * iActiveIndices,
        CATLONG32   iSelectDim);

    static CATLONG32 NaiveMedian(CATSetOfOptRealND * iInputSet, CATMathSetOfLongs * iActiveIndices, CATLONG32  iSelectDim);
};

// A KDTree can be used to do 'spatial indexing' on a set of OptRealND
// It is a balanced tree, where each branching point separates the set of points into two sets of (almost) the same size along
// an affine coordinate plane of a specified index.
// The most important method is FindPointsInVolume which finds all points of iInputSet that lie within iVolume in O(k*N^(1-1/k))

class KDTree
{
public:
    KDTree(CATSetOfOptRealND * iInputSet);
    ~KDTree();
    void FindPointsInVolume(CATMathSetOfLongs & ioIndices, CATMathIntervalND *iVolume);
private:
    KDTree(CATSetOfOptRealND * iInputSet, CATMathSetOfLongs * iActiveIndices, CATLONG32 iCutDim);

    CATSetOfOptRealND * _InputSet;
    CATMathSetOfLongs * _ActiveIndices;
    KDTree ** _Children;
    CATLONG32 _CutIndex;
    CATLONG32 _CutDim;
};



#endif
