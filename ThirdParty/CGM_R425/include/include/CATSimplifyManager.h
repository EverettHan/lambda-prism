/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATSimplifyManager: Simplification of body
// 
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
// Sept. 98   Creation                                 ILY (I. Levy)
//=============================================================================
#ifndef CATSimplifyManager_H
#define CATSimplifyManager_H

//Windows compatibility
#include "YP00IMPL.h"

//GeometricObjects libraries
#include "CATTransfoManager.h"

class CATGeometry;
class CATGeoFactory;
class CATCurve;
class CATSurface;
//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATSimplifyManager: public CATTransfoManager
{
public:
  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATSimplifyManager(CATSoftwareConfiguration *iConfig = NULL);

  //---------------------------------------------------------------------------
  //- WriteReport
  //---------------------------------------------------------------------------
  void WriteReport(CATCGMJournalList   * &ioJournal               , 
                   CATCGMJournal::Type    iType                   ,
                   CATBoolean             iAddInfo = CATBoolean(1)) const;

  //---------------------------------------------------------------------------
  //- WriteReport for Faces and Edges
  //---------------------------------------------------------------------------
  void WriteReportForFacesAndEdges ( CATCGMJournalList  * ioJournalForFace ,
                                     CATCGMJournalList  * ioJournalForEdge , 													  
                                     CATCGMJournal::Type  iTypeForFace     ,
                                     CATCGMJournal::Type  iTypeForEdge     ) const;

  //---------------------------------------------------------------------------
  //- WriteReport for Faces, Edges and Vertices
  //---------------------------------------------------------------------------
  void WriteReportForFacesEdgesAndVertices(CATCGMJournalList  * ioJournalForFaces,
                                           CATCGMJournalList  * ioJournalForEdges, 		
                                           CATCGMJournalList  * ioJournalForVertices,
                                           CATCGMJournal::Type  iTypeForFaces,
                                           CATCGMJournal::Type  iTypeForEdges,
                                           CATCGMJournal::Type  iTypeForVertices) const;

  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  virtual ~CATSimplifyManager();

  /** @nodoc @nocgmitf */
  void AddInternalForObjectNotInEntry ( CATICGMObject * iObjectToTransform );

protected:
  //---------------------------------------------------------------------------
  //- CreateTransformation: creates a dynamic allocation of a Transformation
  //---------------------------------------------------------------------------
  virtual void CreateTransformation();

friend class CATTransfoSimplify;

};
#endif
