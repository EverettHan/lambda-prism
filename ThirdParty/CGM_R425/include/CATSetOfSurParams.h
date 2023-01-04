#ifndef CATSetOfSurParams_H
#define CATSetOfSurParams_H

// COPYRIGHT DASSAULT SYSTEMES  1999
/** @CAA2Required */

#include "CATIAV5Level.h"
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATParamData.h"
#include "CATMathInline.h"

class CATSurParam;
class CATSurParamReference;

#include "CATCGMNewArray.h"

/**
 * Class representing a set of parameters on a same surface.
 * <br>To enhance the performance, the indices of the parameters are not checked.
 */

//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSetOfSurParams
/*
#else
class ExportedByYP00IMPL CATSetOfSurParams
#endif  
*/
{
public:

/**
 * Constructs an empty set of CATSurParams.
 */
  CATSetOfSurParams();

/**

 * Constructs a set of a given count of CATCrvParams.

 * @param iReferenceParam
 * A curve parameter defining the curve on which all the parameters of the set will be defined. 
 * @param iNumberOfPoints
 * The count of parameters.
 */

  CATSetOfSurParams(const CATSurParam &iReference, CATLONG32 iNumberOfPoints = 0);

/**
 * @nodoc
 * Constructs a set from a surface reference.
 */
  CATSetOfSurParams(const CATSurParamReference *iReference, CATLONG32 iNumberOfPoints = 0);

/**
 * Copy constructor.
 */
  CATSetOfSurParams(const CATSetOfSurParams &iSetToCopy);

/**
 * Destructor.
 */
  ~CATSetOfSurParams();

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * @nodoc
 * Modifies the common reference of the CATSurParams.
 */
  INLINE void SetReference(const CATSurParamReference *iNewReference);

/**
 * Returns a pointer to the common reference of the CATSurParams.
 * @return
 * A pointer to the common surface reference.
 */
  INLINE const CATSurParamReference * GetReference() const;

/**
 * Modifies the size of <tt>this</tt> CATSetOfSurParams.
 * @param iSize
 * The set is re-allocated if needed.
 */
  void SetNumberOfPoints(CATLONG32 iSize);

/**
 * Returns the size of <tt>this</tt> CATSetOfSurParams.
 * @return
 * The number of points of <tt>this</tt> set.
 */ 
  INLINE CATLONG32 GetNumberOfPoints() const;

/**
 * Modifies a CATSurParam from an other CATSurParam value.
 * @param iPointIndex
 * The index point (starting at 0) of the CATSurParam to modify.
 * @param iNewPoint
 * The new parameter. This parameter is not checked: in particular, 
 * its surface reference is not checked..
 */
  void SetPoint(CATLONG32 iPointIndex, const CATSurParam &iNewPoint);

/**
 * Modifies a CATSurParam from two values.
 * @param iPointIndex
 * The index point (starting at 0) of the CATSurParam to modify.
 * @param iNewPositionU
 * The new parameter value in the first direction of the surface.
 * @param iNewPositionV
 * The new parameter value in the second direction of the surface.
 */
  void SetPoint(CATLONG32 iPointIndex,
		const CATParamData &iNewPositionU,
		const CATParamData &iNewPositionV);

/**
 * Retrieves the CATSurParam at a given index of <tt>this</tt> CATSetOfSurParams.
 * @param iPointIndex
 * The index point (starting at 0) of the CATSurParam to read.
 * @param ioPoint
 * The parameter. 
 */
  void GetPoint(CATLONG32 iPointIndex, CATSurParam &ioPoint) const;

/**
 * Retrieves <tt>this</tt> CATSetOfSurParams as an array of parameters.
 * @param ioArrayU
 * The corresponding array of parameter values in the first direction of the surface.
 *<br>The result must not be deleted as part of the internal data of the object.
 * @param ioArrayV
 * The corresponding array of parameter values in the second direction of the surface.
 *<br>The result must not be deleted as part of the internal data of the object.
 */
  void GetArrayPositions(const CATParamData * &ioArrayU,
			 const CATParamData * &ioArrayV ) const;

/**
 * Releases the unused memory.
 */
  void Compress();

/**
 * Assignment operator.
 */
  const CATSetOfSurParams & operator = (const CATSetOfSurParams &iCopied);

  /** @nodoc */
  CATCGMNewClassArrayDeclare;

/**
 * Modifies the common surface. 
 * @param iReference
 * A surface parameter defining the surface on which all the parameters of the set will be defined.
 */
  void SetReference(const CATSurParam &iReference);
//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Array of positons
  CATParamData *_UPositions;
  CATParamData *_VPositions;

// Current size of the set
  CATLONG32          _Size;

// Management datas :
  const CATSurParamReference *_Reference;

// Manages the allocation memory.

  void Allocate(CATLONG32 Size);

private:
// Size of the allocated array
  CATLONG32         _Allocated;

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATSetOfSurParams::GetNumberOfPoints() const
{
  return _Size;
}

INLINE const CATSurParamReference * CATSetOfSurParams::GetReference() const
{
  return _Reference;
}

INLINE void CATSetOfSurParams::SetReference(const CATSurParamReference * Reference)
{
  _Reference = Reference;
}

#endif
