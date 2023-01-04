// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyGeoDiagnosis
//
//===================================================================
//
// June 2014  Creation: JXO
// July 2016  Modification JXO: Edges & Normals
//===================================================================
#ifndef CATPolyBodyGeoDiagnosis_H
#define CATPolyBodyGeoDiagnosis_H

#include "PolyMODEL.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMapOfPtrPtrToInt.h"

class CATPolyCell;


/**
 * Class used for logging geometric errors found within a CATPolyBody.
 */
class ExportedByPolyMODEL CATPolyBodyGeoDiagnosis
{

public:

  /**
   * Definition of the geometric errors.
   * Errors can be logged for the whole model (global errors) or for specific cells.
   */
  enum Error 
  {
    /** No error */                                             eNoError                                 = 0x00000000,

    /** First, there are masks. You can use them to check the error using bitwise & */
    /** Fatal error beyond any recovery (memory, data model) */ eFatalError                              = 0x00000001,
    /** Fatal geometric error. */                               eGeometricError                          = 0x00000002,
    /** Warning. */                                             eWarning                                 = 0x00000004,
    
    /** Error on vertex cell */                                 eBadVertex                               = 0x00000010,
    /** Error on edge cell */                                   eBadEdge                                 = 0x00000020,
    /** Error on edge cell */                                   eBadFace                                 = 0x00000040,
    /** Error on body */                                        eBadBody                                 = 0x00000080,
    /** Error between two cells  */                             eBadCellCell                             = 0x00000100,

    /** List of errors (some of them being only warnings) */

    /** Vertex (point) outside model size */                    eBadVertex_OutsideModelSize              = 0x00010014,

    /** Edge (wire) with degenerate bars (identical points) */  eBadEdge_DegenerateBars                  = 0x00010022,
    /** Edge (wire) with too small a bar */                     eBadEdge_TooSmallBars                    = 0x00020024,
    /** Edge (wire) that has self intersections */              eBadEdge_SelfIntersecting                = 0x00040022,
    /** Edge (wire) that has self contacts */                   eBadEdge_SelfContact                     = 0x00080024,
    /** Edge (wire) outside model size */                       eBadEdge_OutsideModelSize                = 0x00100024,

    /** Edge (wire) Edge intersection */                        eBadEdgeEdgeIntersection                 = 0x00010102,
    /** Edge (wire) Edge contact */                             eBadEdgeEdgeContact                      = 0x00020104,

    /** Face with degenerate triangles (colinear points) */     eBadFace_DegenerateTriangles             = 0x00010042,
    /** Face with needles and caps */                           eBadFace_NeedlesAndCaps                  = 0x00020044,
    /** Face that has self intersections */                     eBadFace_SelfIntersecting                = 0x00040042,
    /** Face that has self contacts */                          eBadFace_SelfContact                     = 0x00080044,
    /** Face that has non matching vertex normals */            eBadFace_NonMatchingVertexNormals        = 0x00100042,
    /** Face outside model size */                              eBadFace_OutsideModelSize                = 0x00200044,

    /** Face face intersection */                               eBadFaceFaceIntersection                 = 0x00040102,
    /** Face face contact */                                    eBadFaceFaceContact                      = 0x00080104,

    /** Edge (wire) Face intersection */                        eBadEdgeFaceIntersection                 = 0x00100102,
    /** Edge (wire) Face contact */                             eBadEdgeFaceContact                      = 0x00200104,
    /** Vertex Vertex contact */                                eBadVertexVertexContact                  = 0x00400104,
    /** Vertex Edge contact */                                  eBadVertexEdgeContact                    = 0x00800104,
    /** Vertex Face contact */                                  eBadVertexFaceContact                    = 0x01000104,

    /** Non geometrically closed body typed as volume */        eBadBody_NonGeometricallyWatertight      = 0x10000084,
    /** Badly oriented body typed as volume */                  eBadBody_WrongOrientation                = 0x20000084,
    /** Body outside model size */                              eBadBody_OutsideModelSize                = 0x40000084
  };

public:

  /**
   * Constructor.
   */
  CATPolyBodyGeoDiagnosis ();

  ~CATPolyBodyGeoDiagnosis ();

public:
  /**
   * Returns the tolerance used for errors computation
   */
  inline double GetToleranceUsed() const;

  /**
   * Returns <tt>TRUE</tt> if fatal errors have been logged.
   */
  CATBoolean HasFatalErrors () const;

  /**
   * Logs a global error for the model.
   */
  HRESULT LogError (int iError);

  /**
   * Logs an error for a cell.
   * The methods may be called several times for the same cell if different errors are encountered.
   */
  HRESULT LogError (CATPolyCell* iCell, int iError);

  /**
   * Logs an error for two cell.
   * The methods may be called several times for the same cells if different errors are encountered.
   */
  HRESULT LogError (CATPolyCell* iCell1, CATPolyCell* iCell2, int iError);

  /**
   * Sets the tolerance used for errors
   */
  void SetToleranceUsed(double iTol);
  /**
   * Clears all errors and reset tolerance
   */
  void Clear();

public:

  /**
   * Returns the global error code associated to the CATPolyBody.
   */
  inline int GetError () const;

  /**
   * Returns the number of CATPolyCell errors that have been logged.
   */
  int GetNbCellErrors () const;

  /**
   * Returns the error code associated to a given CATPolyCell of CATPolyBody.
   * @param iCell the cell for wich errors are retrieved
   * @param iCell2 optional second cell
   */
  int GetError (CATPolyCell* iCell, CATPolyCell * iCell2 = 0) const;

public:

  /**
   * Iterator.  
   * Cycles through all the Cell errors that are logged. Use the global GetError for body errors.
   */
  class ExportedByPolyMODEL Iterator
  {
  public:
    Iterator (const CATPolyBodyGeoDiagnosis& iDiagnosis);
    ~Iterator ();

    /**
     * Given an iterator, returns a CATCell.
     */
    CATPolyCell* GetCell () const;

    /**
     * Given an iterator, returns an error.
     */
    int GetError () const;

    /**
     */
    Iterator& Begin ();

    /**
     */
    CATBoolean End () const;

    /**
     */
    Iterator& operator++ ();

    /**
     * Given an iterator, returns an optional second cell
     */
    CATPolyCell* GetSecondCell () const;

  private:
    CATMapOfPtrPtrToInt::Iterator* m_It;
  };

  friend class Iterator;

private:

  int m_BodyErrors; 

  // Map associating a CATPolyCell to an error.
  CATMapOfPtrPtrToInt * m_CellsToError;

  double m_toleranceused;
};


inline int CATPolyBodyGeoDiagnosis::GetError () const
{
  return m_BodyErrors;
}

inline double CATPolyBodyGeoDiagnosis::GetToleranceUsed() const
{
  return m_toleranceused;
}


#endif // !CATPolyBodyGeoDiagnosis_H
