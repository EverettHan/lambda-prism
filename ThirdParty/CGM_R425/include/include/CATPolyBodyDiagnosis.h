// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyDiagnosis
//
//===================================================================
//
// September 2010  Creation: NDO
// June      2013  Modif     JXO: bounding boxes enums
// June      2014  Modif     JXO: documentation + new errors and warnings
//===================================================================
#ifndef CATPolyBodyDiagnosis_H
#define CATPolyBodyDiagnosis_H

#include "PolyMODEL.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMapOfPtrToInt.h"

class CATPolyCell;


/**
 * Class used for logging errors found with a CATPolyBody.
 */
class ExportedByPolyMODEL CATPolyBodyDiagnosis
{

public:

  /**
   * Definition of the errors.
   * Errors can be logged for the whole model (global errors) and also for specific cells.
   * Three distinctions are made according to the severity of the errors:
   * <ul>
   *   <li> Fatal errors (eFatalError)
   *   <li> Anomalies (eAnomaly)
   *   <li> Warnings (eWarning)
   * </ul>
   * Fatal errors indicate a corrupt model or memory beyond possible recovery. 
   * Anomalies indicate serious errors which invalidate the CATPolyBody model.  However, anomalies are not 
   * beyond recovery.  Warnings signal some minor defects in the model which do not invalidate it.
   *
   * The enums for the three categories of errors (eFatalError, eAnomaly and eWarning) are masks.
   * They are parsed with the bitwise & operator.
   *
   * It is also possible to distinguish between a cell error or a global error with the following masks, 
   * parsed also with the bitwise & operator:
   * <ul>
   *   <li> Vertex errors (eBadVertex)
   *   <li> Edge errors (eBadEdge)
   *   <li> Face errors (eBadFace)
   *   <li> Body errors (eBadBody)
   *   <li> Bounding box errors (eBadBoundingBox)
   * </ul>
   */
  enum Error 
  {
    /** No error */                                             eNoError                                 = 0x00000000,

    /** Fatal error (corrupt model beyond recovery.) */         eFatalError                              = 0x00000001,
    /** Anomaly or serious error invaliding the model. */       eAnomaly                                 = 0x00000002,
    /** Warning (does not invalidate the model) */              eWarning                                 = 0x00000004,
    
    /** Error on vertex cell */                                 eBadVertex                               = 0x00000010,
    /** Error on edge cell */                                   eBadEdge                                 = 0x00000020,
    /** Error on face cell */                                   eBadFace                                 = 0x00000040,
    /** Error on body */                                        eBadBody                                 = 0x00000080,
    /** Error with the bounding box */                          eBadBoundingBox                          = 0x00000100,

    /** Vertex cell in a middle on an edge (anomaly) */         eBadVertex_OnEdge                        = 0x00010012,
    /** Non manifold vertex cell (anomaly) */                   eBadVertex_OnVertex                      = 0x00020012,
    /** Vertex with adjacent edges of inconsistent orientations (anomaly) */
                                                                eBadVertex_EdgeOrientations              = 0x00040012,

    /** The surface vertex lines from an edge have non-matching vertices (anomaly) */
                                                                eBadEdge_NonMatchingSurfaceVertexLine    = 0x00010022,
    /** The surface vertex lines from an edge have inconsistent vertex positions (anomaly) */
                                                                eBadEdge_NonMatchingGeometry             = 0x00020022,
    /** Edge referring to a vertex without geometry (anomaly) */
                                                                eBadEdge_NoVertexPosition                = 0x00040022,
    /** Edge with less than two vertices (anomaly) */           eBadEdge_InvalidNbVertices               = 0x00080022,
    /** Edge referring to an unreferenced surface vertex (anomaly) */
                                                                eBadEdge_InvalidSurfaceVertex            = 0x00100022,
    /** Edge referring to a surface vertex multiple times (anomaly) */
                                                                eBadEdge_SelfIntersecting                = 0x00200022,
    /** Edge referring to an internal surface vertex shared by a cell vertex (anomaly) */
                                                                eBadEdge_OnVertex                        = 0x00400022,
    /** Edge whose geometry is outside the bounding box (anomaly) */      
                                                                eBadEdge_OutsideBoundingBox              = 0x00000122,
    /** Edge with adjacent faces of inconsistent orientations (anomaly) */
                                                                eBadEdge_FaceOrientations                = 0x00800022,

    /** Face with a non manifold surface (anomaly) */           eBadFace_NonManifoldSurface              = 0x00010042,
    /** Face with a non matching surface vertex line (anomaly) */
                                                                eBadFace_NonMatchingSurfaceVertexLine    = 0x00020042,
    /** Face with a non consistent orientation (anomaly) */     eBadFace_NonConsistentOrientation        = 0x00040042,
    /** Face whose geometry is outside the bounding box (anomaly) */
                                                                eBadFace_OutsideBoundingBox              = 0x00000142,
    /** Face whose facets are non contiguous (anomaly) */       eBadFace_NonContiguousSurface            = 0x00080042,
    /** Face with bad triangles (anomaly) */                    eBadFace_BadTriangles                    = 0x00100042,
    /** Face with unreferenced vertices (anomaly) */            eBadFace_UnreferencedVertices            = 0x00200042,
    /** Face with duplicate triangles (anomaly) */              eBadFace_DuplicateTriangles              = 0x00400042,
    /** Face without bounding edges (warning) */                eBadFace_WithoutBoundingEdges            = 0x00800044,
    
    /** A non-watertight body typed as a solid (warning) */     eBadBody_NonWatertight                   = 0x00010084,

    /** Do not use. */                                          eFatalErrorMemory                        = eFatalError,
    /** Do not use. */                                          eFatalErrorData                          = eAnomaly
  };

public:

  /**
   * Constructor.
   */
  CATPolyBodyDiagnosis ();

  ~CATPolyBodyDiagnosis ();

public:

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
   */
  int GetError (CATPolyCell* iCell) const;

public:

  /**
   * Iterator.  
   * Cycles through all the Cell errors that are logged. Use the global GetError for body errors.
   */
  class ExportedByPolyMODEL Iterator
  {
  public:
    Iterator (const CATPolyBodyDiagnosis& iDiagnosis);
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

  private:
    CATMapOfPtrToInt::Iterator* _It;
  };

  friend class Iterator;

private:
  friend class CATPolyBodyGeoServicesHelper;
  int _BodyErrors; 

  // Map associating a CATPolyCell to an error.
  CATMapOfPtrToInt* _CellToError;

};


inline int CATPolyBodyDiagnosis::GetError () const
{
  return _BodyErrors;
}


#endif // !CATPolyBodyDiagnosis_H
