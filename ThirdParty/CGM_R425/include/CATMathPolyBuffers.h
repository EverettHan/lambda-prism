// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMathPolyBuffers.h
// RefCounted poly buffers
//
//===================================================================
//
// Sep 2016  Creation: TPG
//
//===================================================================
#ifndef CATMathPolyBuffers_H
#define CATMathPolyBuffers_H

#include "CATMathematics.h"
#include "CATMathRefCounted.h"
#include "CATCGMNewArray.h"
#include "CATCGMemory.h"
#include "CATCGMMemoryManager.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCGMHashTableWithAssoc.h"

class CATUuid;

//===================================================================
typedef struct PolyBuffers_EdgeVertices
{
   CATLONG32  _NbEdgeVertices;
   CATLONG32* _EdgeVertexIndices;
   double*    _EdgeVertexParams;
   PolyBuffers_EdgeVertices(CATLONG32 iNbEdgeVertices): _NbEdgeVertices   (0),
                                                        _EdgeVertexIndices(0),
                                                        _EdgeVertexParams (0)
   {
      if (iNbEdgeVertices > 0)
         _NbEdgeVertices = iNbEdgeVertices;
   }
} PolyBuffers_EdgeVertices;

//===================================================================
class ExportedByCATMathematics CATMathPolyBuffers : public CATMathRefCounted 
{

public:
   /** @nodoc */
   //CATCGMNewClassArrayDeclare; //#define CATCGMNewClassArrayDeclare  void * operator new(size_t); void operator delete(void *) 
   //CATCGMMemoryManagerNewDel;

   /**
   * Precision of the vertex positions.  
   */
   enum VertexPositionPrecision
   {
      /** Vertex positions in float precision. */           eFloat,
      /** Vertex positions in double presison. */           eDouble
   };

public:
   CATMathPolyBuffers (      CATLONG32               iNbVertices            ,
                             VertexPositionPrecision iFloatOrDouble         = eDouble,
                             CATBoolean              iHasUniqueVertexVector = FALSE,
                             CATUuid               * iUuid                  = 0,
                             CATCGMMemoryManager   * iMemoryManager         = 0);

   CATMathPolyBuffers (const CATMathPolyBuffers    & iPolyBuffers           ,
                             CATCGMMemoryManager   * iMemoryManager         = 0);
protected:
   // Use Release ()
   virtual ~CATMathPolyBuffers ();

public:
   // Warning : The indices (for triangles, strips, fans, vertex lines) should be stored as vertex adress in the vertex coordinates buffer
   //           instead of vertex indices, thus can be directly pointed by visualization buffers:
   //           vertex coordinates adress = 3 x vertex index (and starting from 0 to 3x(NbVertices-1))
   HRESULT InitializeTriangles         (CATLONG32  iNbIsolatedTriangles, CATLONG32 iNbStrips,
                                        CATLONG32  iNbStripIndices, CATLONG32 iNbFans, CATLONG32 iNbFanIndices);
   HRESULT InitializeIsolatedTriangles (CATLONG32  iNbIsolatedTriangles); 
   HRESULT InitializeStrips            (CATLONG32  iNbStrips, CATLONG32 iNbStripIndices); 
   HRESULT InitializeFans              (CATLONG32  iNbFans, CATLONG32 iNbFanIndices); 
   HRESULT InitializeVertexLines       (CATLONG32  iNbVertexLines, CATLONG32 iNbVertexLineIndices); 
   HRESULT InitializeEdgeVertexLines   (CATULONG32 iEdgeTAG, CATLONG32 iNbEdgeVertices); // Edge vertex lines

   // Vertices.
   INLINE       CATLONG32 GetNbVertices () const;

   INLINE const float* GetVertexCoordinatesBuffer () const; // read only, null if Update not done
                float* GetVertexCoordinatesBuffer_ForUpdate (); // return 0 if already called
   INLINE void         ReleaseVertexCoordinatesBuffer ();

   INLINE const double* GetVertexCoordinatesBufferDouble () const; // read only, null if Update not done
                double* GetVertexCoordinatesBufferDouble_ForUpdate (); // return 0 if already called
   INLINE       void    ReleaseVertexCoordinatesBufferDouble ();

   // Vectors.
   INLINE       CATBoolean HasUniqueVertexVector () const;
   INLINE       CATLONG32 GetNbVectors () const;

   INLINE const float* GetVertexVectorBuffer () const; // read only, null if Update not done
                float* GetVertexVectorBuffer_ForUpdate (); // return 0 if already called
   INLINE       void   ReleaseVertexVectorBuffer ();

   INLINE const double* GetVertexVectorBufferDouble () const; // read only, null if Update not done
                double* GetVertexVectorBufferDouble_ForUpdate (); // return 0 if already called
   INLINE       void    ReleaseVertexVectorBufferDouble ();

   // UV (bi-parameters for surface, same number as vertices)
   INLINE const float* GetVertexUVBufferFloat () const; // read only, null if Update not done
                float* GetVertexUVBufferFloat_ForUpdate (); // return 0 if already called
   INLINE       void   ReleaseVertexUVBufferFloat ();

   INLINE const double* GetVertexUVBuffer () const; // read only, null if Update not done
                double* GetVertexUVBuffer_ForUpdate (); // return 0 if already called
   INLINE       void    ReleaseVertexUVBuffer ();

   // W (mono-parameters for curve, same number as vertices)
   INLINE const float* GetVertexWBufferFloat () const; // read only, null if Update not done
                float* GetVertexWBufferFloat_ForUpdate (); // return 0 if already called
   INLINE       void   ReleaseVertexWBufferFloat ();

   INLINE const double* GetVertexWBuffer () const; // read only, null if Update not done
                double* GetVertexWBuffer_ForUpdate (); // return 0 if already called
   INLINE       void    ReleaseVertexWBuffer ();

   // Triangles
   // Return the total number of triangles.
   INLINE       CATLONG32  GetNbTriangles () const;

   // Isolated triangles.
   INLINE       CATLONG32  GetNbIsolatedTriangles () const;
   INLINE const CATLONG32* GetIsolatedTriangleBuffer () const; // read only, null if Update not done
                CATLONG32* GetIsolatedTriangleBuffer_ForUpdate (); // return 0 if already called
   INLINE       void       ReleaseIsolatedTriangles ();

   // Strips.
   INLINE       CATLONG32  GetNbStrips () const;
   INLINE       CATLONG32  GetNbStripIndices () const;
   INLINE const CATLONG32* GetStripIndicesBuffer () const; // read only, null if Update not done
   INLINE const CATLONG32* GetNbVerticesPerStripBuffer () const; // read only, null if Update not done
                CATLONG32* GetStripIndicesBuffer_ForUpdate (); // return 0 if already called
                CATLONG32* GetNbVerticesPerStripBuffer_ForUpdate (); // return 0 if already called
                CATLONG32  ComputeNbStripTriangles () const;
   INLINE void  ReleaseStrips ();

   // Fans.
   INLINE       CATLONG32  GetNbFans () const;
   INLINE       CATLONG32  GetNbFanIndices () const;
   INLINE const CATLONG32* GetFanIndicesBuffer () const;                             // read only, null if Update not done
   INLINE const CATLONG32* GetNbVerticesPerFanBuffer () const;                       // read only, null if Update not done
                CATLONG32* GetFanIndicesBuffer_ForUpdate ();                         // return 0 if already called
                CATLONG32* GetNbVerticesPerFanBuffer_ForUpdate ();                   // return 0 if already called
                CATLONG32  ComputeNbFanTriangles () const;
   INLINE void ReleaseFans ();

   // VertexLines.
   INLINE       CATLONG32  GetNbVertexLines () const;
   INLINE       CATLONG32  GetNbVertexLineIndices () const;
   INLINE const CATLONG32* GetVertexLineIndicesBuffer () const;                      // read only, null if Update not done
   INLINE const CATLONG32* GetNbVerticesPerVertexLineBuffer () const;                // read only, null if Update not done
                CATLONG32* GetVertexLineIndicesBuffer_ForUpdate ();                  // return 0 if already called
                CATLONG32* GetNbVerticesPerVertexLineBuffer_ForUpdate ();            // return 0 if already called
   INLINE void ReleaseVertexLines ();

   // VertexLine - input iNumVertexLine (from 1 to NbVertexLines)
                                                                                     // return NbIndices - output array is const  
                CATLONG32 GetVertexLineIndices  (      CATLONG32   iNumVertexLine,
                                                 const CATLONG32*  oVertexLineIndices) const;

                                                                                     // return NbVertices - output array (3*NbVertices)
                                                                                     // to be deleted by caller (may be null if no float coordinates)
                CATLONG32 GetVertexLineVertices (      CATLONG32   iNumVertexLine,
                                                       float    *& oVertexLineVertices) const;

                                                                                     // return NbVertices - output array (3*NbVertices)
                                                                                     // to be deleted by caller (may be null if no double coordinates)
                CATLONG32 GetVertexLineVertices (      CATLONG32   iNumVertexLine,
                                                       double   *& oVertexLineVertices) const;

   // EdgeVertexLines.
   INLINE       CATLONG32 GetNbEdgeVertexLines () const;
                                                                                     // read only, null if Update not done
         const CATLONG32* GetEdgeVertexLineIndicesBuffer (CATULONG32 iEdgeTag, CATLONG32& oNbEdgeVertices) const;

                                                                                     // read only, null if Update not done
         const CATLONG32* GetEdgeVertexLineIndicesBuffer (CATLONG32  iNumEdge,
                                                          CATULONG32& oEdgeTag,
                                                          CATLONG32& oNbEdgeVertices) const;

                                                                                     // read only, null if Update not done
         const double*    GetEdgeVertexLineParamsBuffer  (CATULONG32 iEdgeTag, CATLONG32& oNbEdgeVertices) const;

                                                                                     // read only, null if Update not done
         const double*    GetEdgeVertexLineParamsBuffer  (CATLONG32  iNumEdge,
                                                          CATULONG32& oEdgeTag,
                                                          CATLONG32& oNbEdgeVertices) const;
               CATLONG32* GetEdgeVertexLineIndicesBuffer_ForUpdate (CATULONG32 iEdgeTag, CATLONG32& oNbEdgeVertices); // return 0 if already called
               double*    GetEdgeVertexLineParamsBuffer_ForUpdate (CATULONG32 iEdgeTag, CATLONG32& oNbEdgeVertices); // return 0 if already called
   INLINE      void       ReleaseEdgeVertexLines ();

   // 
   INLINE      void       SetSide (short iSide);
   INLINE      short      GetSide () const;

   /**
   * Definition of various bit flags.
   */
   enum Masks
   {
      /** Bit 0: Bounding box ok. */                      MaskBoundingBoxOK      = 0x0001,
      /** Bit 1: Vertex position layer in float. */       MaskVertexFloat        = 0x0002,
      /** Bit 2: Vertex position layer in double. */      MaskVertexDouble       = 0x0004,
      /** Bit 3: Unique vertex Vector. */                 MaskUniqueVertexVector = 0x0008
   };

   INLINE unsigned char GetFlags() const;

   // CATUuid
   HRESULT GetUuid(CATUuid*& oId) const; // oId to be deleted by caller

   void EmptyEdgeTagAssocEdgeVertices();

public:

   void Dump() const;

private:

   INLINE void* MemBook (size_t iSizeInBytes);
   INLINE void  MemClear(void* &iAllocated);
          void  Init    (CATLONG32               iNbVertices   ,
                         CATCGMMemoryManager   * iMemoryManager);


private:

   CATCGMMemoryManager* _MemoryManager;

   // Note to future developer(s): If data members in this class are changed/added/removed, in future,
   // then do not forget to update the Stream/UnStream code appropriately  (refer to Mathematics\ProtectedInterfaces\CATMathPolyBuffersStreamer.h)
   //
   // Stream/UnStream data 
   unsigned char _Flags;  // Bit flags.

   // Vertices
   CATLONG32 _NbVertices;
   float*    _VertexPositionF;
   double*   _VertexPositionD;
   float*    _VertexVectorF;
   double*   _VertexVectorD;
   float*    _VertexUVF;
   double*   _VertexUVD;
   float*    _VertexWF;
   double*   _VertexWD;

   // Triangles
   CATLONG32  _NbIsolatedTriangles;
   CATLONG32* _IsolatedTriangles;

   CATLONG32  _NbStrips;
   CATLONG32  _NbStripIndices;
   CATLONG32* _StripIndices;
   CATLONG32* _NbVerticesPerStrip;

   CATLONG32  _NbFans;
   CATLONG32  _NbFanIndices;
   CATLONG32* _FanIndices;
   CATLONG32* _NbVerticesPerFan;

   short      _Side;

   // Vertex Lines
   CATLONG32  _NbVertexLines;
   CATLONG32  _NbVertexLineIndices;
   CATLONG32* _VertexLineIndices;
   CATLONG32* _NbVerticesPerVertexLine;

   // Edge vertices
   CATCGMHashTableWithAssoc _EdgeTagAssocEdgeVertices;

   // CATUuid
   CATUuid * _Uuid;

   // others data not to be Streamed/UnStreamed
};

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbVertices () const
{
   return _NbVertices;
}

//---------------------------------------------------------------------
INLINE const float* CATMathPolyBuffers::GetVertexCoordinatesBuffer () const
{
   return _VertexPositionF;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexCoordinatesBuffer ()
{
   if (_VertexPositionF)
      MemClear((void*&)_VertexPositionF);
   //delete [] _VertexPositionF;
   _VertexPositionF = 0;
}

//---------------------------------------------------------------------
INLINE const double* CATMathPolyBuffers::GetVertexCoordinatesBufferDouble () const
{
   return _VertexPositionD;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexCoordinatesBufferDouble ()
{
   if (_VertexPositionD)
      MemClear((void*&)_VertexPositionD);
   //delete [] _VertexPositionD;
   _VertexPositionD = 0;
}

//---------------------------------------------------------------------
INLINE CATBoolean CATMathPolyBuffers::HasUniqueVertexVector () const
{
   if (_Flags & MaskUniqueVertexVector)
      return TRUE;
   return FALSE;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbVectors () const
{
   if (_Flags & MaskUniqueVertexVector)
      return 1;
   return _NbVertices;
}

//---------------------------------------------------------------------
INLINE const float* CATMathPolyBuffers::GetVertexVectorBuffer () const
{
   return _VertexVectorF;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexVectorBuffer ()
{
   if (_VertexVectorF)
      MemClear((void*&)_VertexVectorF);
   //delete [] _VertexVectorF;
   _VertexVectorF = 0;
}

//---------------------------------------------------------------------
INLINE const double* CATMathPolyBuffers::GetVertexVectorBufferDouble () const
{
   return _VertexVectorD;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexVectorBufferDouble ()
{
   if (_VertexVectorD)
      MemClear((void*&)_VertexVectorD);
   //delete [] _VertexVectorD;
   _VertexVectorD = 0;
}

//---------------------------------------------------------------------
INLINE const float* CATMathPolyBuffers::GetVertexUVBufferFloat () const
{
   return _VertexUVF;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexUVBufferFloat ()
{
   if (_VertexUVF)
      MemClear((void*&)_VertexUVF);
   //delete [] _VertexUVF;
   _VertexUVF = 0;
}

//---------------------------------------------------------------------
INLINE const double* CATMathPolyBuffers::GetVertexUVBuffer () const
{
   return _VertexUVD;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexUVBuffer ()
{
   if (_VertexUVD)
      MemClear((void*&)_VertexUVD);
   //delete [] _VertexUVD;
   _VertexUVD = 0;
}

//---------------------------------------------------------------------
INLINE const float* CATMathPolyBuffers::GetVertexWBufferFloat () const
{
   return _VertexWF;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexWBufferFloat ()
{
   if (_VertexWF)
      MemClear((void*&)_VertexWF);
   //delete [] _VertexWF;
   _VertexWF = 0;
}

//---------------------------------------------------------------------
INLINE const double* CATMathPolyBuffers::GetVertexWBuffer () const
{
   return _VertexWD;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexWBuffer ()
{
   if (_VertexWD)
      MemClear((void*&)_VertexWD);
   //delete [] _VertexWD;
   _VertexWD = 0;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbIsolatedTriangles () const
{
   return _NbIsolatedTriangles;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetIsolatedTriangleBuffer () const
{
   return _IsolatedTriangles;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseIsolatedTriangles ()
{
   if (_IsolatedTriangles)
      MemClear((void*&)_IsolatedTriangles);
   //delete [] _IsolatedTriangles;
   _IsolatedTriangles = 0;

   _NbIsolatedTriangles = 0;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbStrips () const
{
   return _NbStrips;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbStripIndices () const
{
   return _NbStripIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetStripIndicesBuffer () const
{
   return _StripIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetNbVerticesPerStripBuffer () const
{
   return _NbVerticesPerStrip;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseStrips ()
{
   if (_NbVerticesPerStrip)
      MemClear((void*&)_NbVerticesPerStrip);
   //delete [] _NbVerticesPerStrip;
   _NbVerticesPerStrip = 0;
   if (_StripIndices)
      MemClear((void*&)_StripIndices);
   //delete [] _StripIndices;
   _StripIndices = 0;

   _NbStrips = 0;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbFans () const
{
   return _NbFans;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbFanIndices () const
{
   return _NbFanIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetFanIndicesBuffer () const
{
   return _FanIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetNbVerticesPerFanBuffer () const
{
   return _NbVerticesPerFan;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseFans ()
{
   if (_NbVerticesPerFan)
      MemClear((void*&)_NbVerticesPerFan);
   //delete [] _NbVerticesPerFan;
   _NbVerticesPerFan = 0;
   if (_FanIndices)
      MemClear((void*&)_FanIndices);
   //delete [] _FanIndices;
   _FanIndices = 0;

   _NbFans = 0;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbVertexLines () const
{
   return _NbVertexLines;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbVertexLineIndices () const
{
   return _NbVertexLineIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetVertexLineIndicesBuffer () const
{
   return _VertexLineIndices;
}

//---------------------------------------------------------------------
INLINE const CATLONG32* CATMathPolyBuffers::GetNbVerticesPerVertexLineBuffer () const
{
   return _NbVerticesPerVertexLine;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseVertexLines ()
{
   if (_NbVerticesPerVertexLine)
      MemClear((void*&)_NbVerticesPerVertexLine);
   //delete [] _NbVerticesPerVertexLine;
   _NbVerticesPerVertexLine = 0;
   if (_VertexLineIndices)
      MemClear((void*&)_VertexLineIndices);
   //delete [] _VertexLineIndices;
   _VertexLineIndices = 0;

   _NbVertexLines = 0;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbTriangles () const
{
   return GetNbIsolatedTriangles () + ComputeNbStripTriangles () + ComputeNbFanTriangles ();
}

//---------------------------------------------------------------------
INLINE short CATMathPolyBuffers::GetSide () const
{
   return _Side;
}

//---------------------------------------------------------------------
INLINE unsigned char CATMathPolyBuffers::GetFlags() const
{
   return _Flags;
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::SetSide (short iSide)
{
   _Side = iSide;
}

//---------------------------------------------------------------------
INLINE CATLONG32 CATMathPolyBuffers::GetNbEdgeVertexLines () const
{
   return _EdgeTagAssocEdgeVertices.Size();
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::ReleaseEdgeVertexLines ()
{
   EmptyEdgeTagAssocEdgeVertices();
   _EdgeTagAssocEdgeVertices.RemoveAll();
}

//---------------------------------------------------------------------
INLINE void* CATMathPolyBuffers::MemBook(size_t iSizeInBytes)
{
   return _MemoryManager?_MemoryManager->AllocateWithSizeInBytes(iSizeInBytes):CATCGMemBook(iSizeInBytes);
}

//---------------------------------------------------------------------
INLINE void CATMathPolyBuffers::MemClear(void* &iAllocated)
{
   if (!_MemoryManager && iAllocated)
      CATCGMemClear(iAllocated);
   iAllocated = 0;
}

#endif // !CATMathPolyBuffers_H


