#ifndef CATSetOfCrvParams_H
#define CATSetOfCrvParams_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "ExportedByCATCGMGeoMath.h"
#include "CATParamData.h"
class CATCrvLimits;
class CATCrvParam;
class CATCrvParamReference;

#include "CATCGMNewArray.h"
#include "CATMathInline.h"

/**
 * Class representing a set of parameters on a same curve.
 * <br>To enhance the performance, the indices of the parameters are not checked.
 */
class ExportedByCATCGMGeoMath CATSetOfCrvParams
{
public:
/**
 * Constructs an empty set of CATCrvParams.
 */
  CATSetOfCrvParams();

/**
 * Constructs a set of a given count of CATCrvParams.
 * @param iNumberOfPoints
 * The count of parameters.
 * @param iReferenceParam
 * A curve parameter defining the curve on which all the parameters of the set will be defined.
 */
  CATSetOfCrvParams(CATLONG32 iNumberOfPoints, const CATCrvParam &iReferenceParam);

/**
 * @nodoc
 * Constructs a set of a given number of CATCrvParams, and a reference.
 */
  CATSetOfCrvParams(CATLONG32 iNumberOfPoints, const CATCrvParamReference * iReference);

/**
 * Constructs a set of equally spaced parameters.
 * @param iNumberOfPoints
 * The count of parameters.
 * @param iInterval
 * The box in which the parameters are equally-spaced.
 */
  CATSetOfCrvParams(CATLONG32 iNumberOfPoints, const CATCrvLimits &iInterval);

/**
 * Copy constructor.
 */
  CATSetOfCrvParams(const CATSetOfCrvParams &iSetToCopy);

/**
 * Assignment operator.
 */
  const CATSetOfCrvParams & operator =(const CATSetOfCrvParams &oSetToAffect);

/**
 * Destructor.
 */
  ~CATSetOfCrvParams();

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * @nodoc
 * Returns a pointer to the common reference of the CATCrvParams.
 * @return
 * A pointer to the common curve reference.
 */
  INLINE const CATCrvParamReference * GetReference() const;

/**
 * @nodoc
 * Modifies the common reference of the CATCrvParams.
 */
  INLINE void SetReference(const CATCrvParamReference * iNewReference);

/**
 * Modifies the size of <tt>this</tt> CATSetOfCrvParams.
 * @param iSize
 * The set is re-allocated if needed.
 */
  void SetNumberOfPoints(CATLONG32 iSize);

/**
 * Returns the size of <tt>this</tt> CATSetOfCrvParams.
 * @return
 * The number of points of <tt>this</tt> set.
 */
  INLINE CATLONG32 GetNumberOfPoints() const;

/**
 * Modifies a CATCrvParam from an other CATCrvParam value.
 * @param iPointIndex
 * The index point (starting at 0) of the CATCrvParam to modify.
 * @param iNewPoint
 * The new parameter. This parameter is not checked: in particular, 
 * its curve reference is not checked.
 */
  void SetPoint(CATLONG32 iPointIndex, const CATCrvParam &iNewPoint);

/**
 * Modifies a CATCrvParam from a CATParamData value.
 * @param iPointIndex
 * The index point (starting at 0) of the CATCrvParam to modify.
 * @param iNewPosition
 * The new parameter value.
 */
  void SetPoint(CATLONG32 iPointIndex, const CATParamData &iNewPosition);

/**
 * Retrieves the CATCrvParam at a given index of <tt>this</tt> CATSetOfCrvParams.
 * @param iPointIndex
 * The index point (starting at 0) of the CATCrvParam to read.
 * @param ioPoint
 * The parameter. 
 */
  void GetPoint(CATLONG32 iPointIndex, CATCrvParam &ioPoint) const;

/**
 * Retrieves the global value of a CATCrvParam at a given index of <tt>this</tt> CATSetOfCrvParam.
 * @param iPointIndex
 * The index point (starting at 0) of the CATCrvParam to modify.
 * @return
 * The parameter value.
 */
  double GetPoint(CATLONG32 iPointIndex) const ;

/**
 * Retrieves <tt>this</tt> CATSetOfCrvParams as an array of parameters.
 * @return
 * The corresponding array of parameters.
 *<br>The result must not be deleted as part of the internal data of the object.
 */
  const CATParamData* GetArrayPositions() const;

/**
 * Releases the unused memory.
 */
  void Compress();

/**
 * Reverses the set.
 */
  void AutoInvert();

  /** @nodoc */
  CATCGMNewClassArrayDeclare;

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Array of positons
  CATParamData * _ArrayPositions;

// Current size of the set
  CATLONG32          _Size;

// Management datas :
  const CATCrvParamReference * _Reference;


//Manages the allocation memory.
  void Allocate(CATLONG32 Size);

private:
// Size of the allocated array
  CATLONG32         _Allocated;

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATSetOfCrvParams::GetNumberOfPoints() const
{
  return _Size;
}

INLINE const CATCrvParamReference * CATSetOfCrvParams::GetReference() const
{
  return _Reference;
}

INLINE void CATSetOfCrvParams::SetReference(const CATCrvParamReference *Reference)
{
  _Reference = Reference;
}

#endif
