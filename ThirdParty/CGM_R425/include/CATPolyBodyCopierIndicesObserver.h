//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyCopierIndicesObserver.h
//
//===================================================================
// 21/02/18 F1Z : Creation
// DD/MM/YY
//===================================================================
#ifndef CATPolyBodyCopierIndicesObserver_H
#define CATPolyBodyCopierIndicesObserver_H

// Polyhedral Mathematics
#include "CATMapOfIntToPtr.h"
#include "CATMapOfPtrToPtr.h"
#include "CATPolyBuckets.h"
#include "CATPolyBucketsImpl.h"

// Polyhedral Objects
#include "CATPolyBodyUnaryObserver.h"
#include "PolyBodyTools.h"

class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;
class CATMapOfIntToInt;
class CATMapOfIntToPtr;
class CATMathTransformation;
class CATPolyCellPoint;

/**
* Observer class for the CATPolyBodyCopier
* It records the mapping between the indices of the copied poly body to the clone one.
*/
class ExportedByPolyBodyTools CATPolyBodyCopierIndicesObserver : public CATPolyBodyUnaryObserver
{
public:

   // ---------------------------------------------------------------------------
   // Object Management
   // ---------------------------------------------------------------------------
   CATPolyBodyCopierIndicesObserver();
   ~CATPolyBodyCopierIndicesObserver();
   static void DeleteMap(CATMapOfPtrToPtr * & ioMap);

   // ---------------------------------------------------------------------------
   // Get
   // ---------------------------------------------------------------------------
   // Copy the map into the provided one
   HRESULT GetCellMap               (      CATMapOfPtrToPtr   & oCellMap               ) const;
   HRESULT GetFaceVertexIndicesMap  (      CATMapOfPtrToPtr   & oFaceVertexIndicesMap  ) const;
   HRESULT GetEdgeVertexIndicesMap  (      CATMapOfPtrToPtr   & oEdgeVertexIndicesMap  ) const;
   HRESULT GetFaceTriangleIndicesMap(      CATMapOfPtrToPtr   & oFaceTriangleIndicesMap) const;

   // Directly refer to this class attributs (so does the object live...)
   HRESULT GetCellMap               (const CATMapOfPtrToPtr * & oCellMap               ) const;
   HRESULT GetFaceVertexIndicesMap  (const CATMapOfPtrToPtr * & oFaceVertexIndicesMap  ) const;
   HRESULT GetEdgeVertexIndicesMap  (const CATMapOfPtrToPtr * & oEdgeVertexIndicesMap  ) const;
   HRESULT GetFaceTriangleIndicesMap(const CATMapOfPtrToPtr * & oFaceTriangleIndicesMap) const;

   // ---------------------------------------------------------------------------
   // Geometry mode
   // ---------------------------------------------------------------------------
   bool RequestGeometryEvents () {return true;}

   // ---------------------------------------------------------------------------
   // Poly Body
   // ---------------------------------------------------------------------------
   void Begins (const CATPolyBody             & iOperand ,
                const CATMathTransformation *   iPosition,
                const int iTag) override;

   void Result (      CATPolyBody             & iPolyBody,
                const CATMathTransformation *   iPosition) override;

   void Ends (        HRESULT                    hrRun   ) override;

   // ---------------------------------------------------------------------------
   // Vertex
   // ---------------------------------------------------------------------------
   void BeginVertex (const CATPolyCellPoint * iPoint      );
   void EndVertex   (      CATPolyVertex    * iVertex     ,
                           CATPolyCell      * iCellOperand);

   // ---------------------------------------------------------------------------
   // Edge
   // ---------------------------------------------------------------------------
   void BeginEdge        ();
   void AppendCurveVertex(const int                cv          ,
                          const CATPolyCellPoint * iPoint      );
   void EndEdge          (      CATPolyEdge      * edge        ,
                                CATPolyCell      * iCellOperand);

   // ---------------------------------------------------------------------------
   // Face
   // ---------------------------------------------------------------------------
   void BeginFace       ();
   void AddSurfaceVertex(const int                iSv          ,
                         const CATPolyCellPoint * iPoint       );
   void AddTriangle     (const int                iT           ,
                               CATPolyFace      * iFace        ,
                         const int                iFaceTriangle);
   void EndFace         (      CATPolyFace      * iFace        ,
                               CATPolyFace      * iFaceOperand );

private:

   enum ObserverStatus {NotStarted, NotValid, Started, Ended};

   // ---------------------------------------------------------------------------
   // PolyVertex (private)
   // ---------------------------------------------------------------------------
   struct PolyVertex
   {
      PolyVertex() : _Cell(0), _Id(0) {};
      PolyVertex(CATPolyCell * iCell, int iId) : _Cell(iCell), _Id(iId) {};
      PolyVertex(const PolyVertex & iToCopy) : _Cell(iToCopy._Cell), _Id(iToCopy._Id) {};
      ~PolyVertex() { _Cell = 0; };

      int GetSurfaceVertexIndice(CATPolyFace * iFace) const;

      CATPolyCell * _Cell;
      int           _Id  ;
   };

   // ---------------------------------------------------------------------------
   // Methods (private)
   // ---------------------------------------------------------------------------
   static void        DeleteMapContent          (      CATMapOfPtrToPtr   & ioToClean         );
   CATMapOfIntToInt * CreateSurfaceVertexIndices(      CATPolyFace      *   iFace             ,
                                                       CATPolyFace      *   iFaceOperand      ,
                                                 const CATMapOfIntToPtr   & iNewSVToPolyVertex) const;

   // ---------------------------------------------------------------------------
   // Attributs (private)
   // ---------------------------------------------------------------------------
   // algorithm
   CATMapOfIntToInt           * m_indiceMapIntInt;
   CATMapOfIntToPtr             m_indiceMapIntPtr;
   CATPolyBuckets<PolyVertex>   m_polyVertex     ;

   // status and output
   ObserverStatus     m_status                ;
   CATMapOfPtrToPtr   m_cellMap               ;
   CATMapOfPtrToPtr   m_faceVertexIndicesMap  ;
   CATMapOfPtrToPtr   m_faceTriangleIndicesMap;
   CATMapOfPtrToPtr   m_edgeVertexIndicesMap  ;

};

#endif
