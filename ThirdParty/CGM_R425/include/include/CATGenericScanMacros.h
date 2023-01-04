#ifndef CATGenericScanMacros_h
#define CATGenericScanMacros_h

#include "CATGenericScanMacros_Protected.h"
#include "CATDomain.h"
//#include "CATCXDomain.h"
//#include "CATCXLump.h"
//#include "CATCXCell.h"
//#include "CATCXVolume.h"
//#include "CATCXLocatedDomains.h"
#include "CATCGMJournal.h"
#include "CATCGMJournalList.h"
#include "CATCGMJournalItem.h"
#include "CATGeometry.h"
//#include "CATCXFace.h"
#include "CATListOfCATGeometries.h"
//#include "CATSubdBlockThrow.h"
//#include "CATSubdBoundingEdge.h"
//#include "CATSubdBoundingFace.h"
//#include "CATCXLoop.h"
//#include "CATCXShell.h"
//#include "CATSubdListDo.h"
//#include "CATCXLinkVertexType.h"
//#include "CATCXTopology.h"
//#include "CATCXEdge.h"
//#include "CATSubdEdge.h"
//#include "CATSubdEdgeCurve.h"
//#include "CATSubdBoundingVertex.h"
//#include "CATSubdArrayMemVertexP.h"
//#include "CATSubdFace.h"
//#include "CATSubdVolume.h"
//#include "CATSubdArrayMemEdgeP.h"
//#include "CATCXWire.h"
#include "ListPOfCATDomain.h"
//#include "CATCXOrientedFaces.h"
//#include "CATCXBody.h"
//#include "CATCXVertex.h"
//#include "CATSubdArrayFor.h"
//#include "CATCXVertexInFace.h"

//*******************************************************************************************
// Creation                                                                     LD2
//------------------------------------------------------------------------------------------
// CATCXBody * BodyToScan = ...
//
// CATForVolumeInBodyBegin(BodyToScan, CurrentCXLump, CurrentCXVolume)
// {
//    CurrentCXLump->...
//    CurrentCXVolume->...
// } CATForVolumeInBodyEnd;
//
// CATForVolumicShellInBodyBegin(BodyToScan, CurrentCXLump, CurrentCXVolume, CurrentCXShell)
// {
//    CurrentCXLump->...
//    CurrentCXVolume->...
//    CurrentCXShell->...
// } CATForVolumicShellInBodyEnd;
//
// CATForSurfacicShellInBodyBegin(BodyToScan, CurrentCXShell)
// {
//    CurrentCXShell->...
// } CATForSurfacicShellInBodyEnd;
//------------------------------------------------------------------------------------------
// CATCGMJournalList * JournalToScan = ...
//
// CATForFaceInJournalBegin(JournalToScan, CurrentInputCXFace, CurrentOutputCXFace)
// {
//    CurrentInputCXFace->...
//    CurrentOutputCXFace->...
// } CATForFaceInJournalEnd;
//------------------------------------------------------------------------------------------
// CATCXFace * FaceToScan = ...
// CATForEdgeInFaceBegin (FaceToScan, CurrentCXLoop, CurrentSubdBoundingEdge, CurrentCxEdge)
// {
//    CurrentCXLoop->...
//    CurrentSubdBoundingEdge->...
//    CurrentCxEdge->...
// } CATForEdgeInFaceEnd (CurrentSubdBoundingEdge);
//------------------------------------------------------------------------------------------
// CATForListPBegin(ListToScan, CurrentElement, Type *)
// {
//   CurrentElement->...
// } CATForListPEnd;
//------------------------------------------------------------------------------------------
// CATCXShell * CxShell = ...
// CATForFaceInShellBegin(CxShell, CurrentCxFace, CurrentCatOrientation)
// {
//   CurrentCxFace->...
// } CATForFaceInShellEnd;
//------------------------------------------------------------------------------------------
// CATCXBody * CxBody = ...
// CATForBodyWireEdgesBegin(CxBody, CurrentCxWire, CurrentSubdBoundingEdge, CurrentCxEdge)
// {
//   CurrentCxWire->...
//   CurrentSubdBoundingEdge->...
//   CurrentCxEdge->...
// } CATForBodyWireEdgesEnd(CurrentSubdBoundingEdge);
//------------------------------------------------------------------------------------------
// CATCXEdge * CxEdge = ...
// UpwardScan_EdgeToFaces_Begin(CxEdge, SubdEdgeCurve, CxLoop, SubdFace, CxFace)
// {
// 	 SubdEdgeCurve->... //Type: CATSubdEdgeCurve
// 	 CxLoop->...   //Type: CATCXLoop
//   SubdFace->...   //Type: CATSubdFace
// 	 CxFace->...   //Type: CATCXFace
// } UpwardScan_EdgeToFaces_End;
//------------------------------------------------------------------------------------------
// CATCXVertex * CxVertex = ...
// UpwardScan_VertexToEdges_Begin(CxVertex, BoundingVertex, SubdEdgeCurve, CxEdge)
// {
// 	 BoundingVertex->... //Type: CATSubdBoundingVertex
// 	 SubdEdgeCurve->...   //Type: CATSubdEdgeCurve
// 	 CxEdge->...   //Type: CATCXEdge
// } UpwardScan_VertexToEdges_End;
//------------------------------------------------------------------------------------------
// CATCXWire * CxWire = ...
// CATForWireEdgesBegin(CxWire, CurrentSubdBoundingEdge, CurrentCxEdge)
// {
//   CurrentSubdBoundingEdge->... //Type: CATSubdBoundingEdge
// 	 CurrentCxEdge->...   //Type: CATCXEdge
// } CATForWireEdgesEnd(CurrentSubdBoundingEdge)
//------------------------------------------------------------------------------------------
// CATCXVertex * CxVertex = ...
// UpwardScan_Vertex_Begin(CxVertex)
// {
//   UpwardScan_Vertex_EdgeCase(UpwardCxEdge)
//   {
//     UpwardCxEdge->... //Type: CATCXEdge
//   }
//   UpwardScan_Vertex_FaceCase(UpwardVIF, UpwardSubdFace, CxFace)
//   {
//     UpwardVIF->... //Type: CATCXVertexInFace
//     UpwardSubdFace->... //Type: CATSubdBoundingFace
//     CxFace->... //Type: CATCXFace
//   }
// } UpwardScan_Vertex_End;
//*******************************************************************************************

#define CATForVolumeInBodyBegin(BODY, LUMP, VOLUME)                                                                       \
if (BODY)                                                                                                                 \
{                                                                                                                         \
  int __##LUMP##NbrDomains = (BODY)->GetNbDomains();                                                                      \
  int __##LUMP##IdxDomains;                                                                                               \
  for (__##LUMP##IdxDomains = 1; __##LUMP##IdxDomains <= __##LUMP##NbrDomains; __##LUMP##IdxDomains++)                    \
  {                                                                                                                       \
    CATDomain * __##LUMP##IDomain = (BODY)->GetDomain(__##LUMP##IdxDomains);                                              \
    if (__##LUMP##IDomain)                                                                                                \
    {                                                                                                                     \
      CATCXDomain * __##LUMP##Domain = CATCGMTopologyImpl::GetImplementCXDomain(__##LUMP##IDomain);                       \
      if (__##LUMP##Domain)                                                                                               \
      {                                                                                                                   \
        CATCXLump * LUMP = __##LUMP##Domain->CastToLump();                                                                \
        if (LUMP)                                                                                                         \
        {                                                                                                                 \
          int __##LUMP##NbrVolumes = LUMP->GetNbVolumes();                                                                \
          int __##LUMP##IdxVolumes;                                                                                       \
          for (__##LUMP##IdxVolumes = 1; __##LUMP##IdxVolumes <= __##LUMP##NbrVolumes; __##LUMP##IdxVolumes++)            \
          {                                                                                                               \
            CATCXCell * __##LUMP##MaybeVolume = LUMP->GetCellImpl(__##LUMP##IdxVolumes);                                  \
            if (__##LUMP##MaybeVolume)                                                                                    \
            {                                                                                                             \
              CATCXVolume * VOLUME = __##LUMP##MaybeVolume->CastToVolume();                                               \
              if (VOLUME)                                                                                                 \
              {


#define CATForVolumeInBodyEnd                                                                                             \
              }                                                                                                           \
            }                                                                                                             \
          }                                                                                                               \
        }                                                                                                                 \
      }                                                                                                                   \
    }                                                                                                                     \
  }                                                                                                                       \
}


#define CATForVolumicShellInBodyBegin(BODY, LUMP, VOLUME, SHELL)                                                          \
CATForVolumeInBodyBegin(BODY, LUMP, VOLUME)                                                                               \
{                                                                                                                         \
  const CATCXLocatedDomains * __##SHELL##Shells = VOLUME->GetDomains();                                                   \
  if (__##SHELL##Shells)                                                                                                  \
  {                                                                                                                       \
    int __##SHELL##NbrShells = __##SHELL##Shells->Size();                                                                 \
    int __##SHELL##IdxShells;                                                                                             \
    for (__##SHELL##IdxShells = 0; __##SHELL##IdxShells < __##SHELL##NbrShells; __##SHELL##IdxShells++)                   \
    {                                                                                                                     \
      CATCXDomain * __##SHELL##MaybeShell = (*__##SHELL##Shells)[__##SHELL##IdxShells];                                   \
      if (__##SHELL##MaybeShell)                                                                                          \
      {                                                                                                                   \
        CATCXShell * SHELL = __##SHELL##MaybeShell->CastToShell();                                                        \
        if (SHELL)                                                                                                        \
        {


#define CATForVolumicShellInBodyEnd                                                                                       \
        }                                                                                                                 \
      }                                                                                                                   \
    }                                                                                                                     \
  }                                                                                                                       \
} CATForVolumeInBodyEnd;

//------------------------------------------------------------------------------------------

#define CATForSurfacicShellInBodyBegin(BODY, SHELL)                                                                                        \
if (BODY)                                                                                                                                  \
{                                                                                                                                          \
  int __##SHELL##NbrDomains = (BODY)->GetNbDomains();                                                                                      \
  int __##SHELL##IdxDomains;                                                                                                               \
  for (__##SHELL##IdxDomains = 1; __##SHELL##IdxDomains <= __##SHELL##NbrDomains; __##SHELL##IdxDomains++)                                 \
  {                                                                                                                                        \
    CATDomain * __##SHELL##IDomain = (BODY)->GetDomain(__##SHELL##IdxDomains);                                                             \
    if (__##SHELL##IDomain)                                                                                                                \
    {                                                                                                                                      \
      CATCXDomain * __##SHELL##Domain = (CATCXDomain *)__##SHELL##IDomain->GetImplementCGM(CATDomainType);                                 \
      if (__##SHELL##Domain)                                                                                                               \
      {                                                                                                                                    \
        CATCXShell * SHELL = __##SHELL##Domain->CastToShell();                                                                             \
        if (SHELL)                                                                                                                         \
        {


#define CATForSurfacicShellInBodyEnd                                                                                                       \
        }                                                                                                                                  \
      }                                                                                                                                    \
    }                                                                                                                                      \
  }                                                                                                                                        \
}

//------------------------------------------------------------------------------------------

#define CATForFaceInJournalBegin(LIST, FACE1, FACE2)                                                                                                                \
if (LIST)                                                                                                                                                           \
{                                                                                                                                                                   \
  (LIST)->Tass();                                                                                                                                                   \
  CATCGMJournal * __##FACE1##Current = NULL;                                                                                                                        \
  while (__##FACE1##Current = (LIST)->Next(__##FACE1##Current))                                                                                                     \
  {                                                                                                                                                                 \
    CATCGMJournalItem * __##FACE1##Item = __##FACE1##Current->CastToReportItem();                                                                                   \
    if (__##FACE1##Item && __##FACE1##Item->GetActiveMode())                                                                                                        \
    {                                                                                                                                                               \
      CATCGMJournal::Type __##FACE1##Type = __##FACE1##Item->GetType();                                                                                             \
      if (__##FACE1##Type == CATCGMJournal::Modification || __##FACE1##Type == CATCGMJournal::Subdivision || __##FACE1##Type == CATCGMJournal::Absorption ||        \
          __##FACE1##Type == CATCGMJournal::Creation)                                                                                                               \
      {                                                                                                                                                             \
        CATLISTP(CATGeometry) __##FACE1##Old;                                                                                                                       \
        CATLISTP(CATGeometry) __##FACE1##New;                                                                                                                       \
        __##FACE1##Item->GetFirstObjs(__##FACE1##Old);                                                                                                              \
        __##FACE1##Item->GetLastObjs(__##FACE1##New);                                                                                                               \
        int __##FACE1##NbOld = __##FACE1##Old.Size();                                                                                                               \
        int __##FACE1##NbNew = __##FACE1##New.Size();                                                                                                               \
        int __##FACE1##IxOld, __##FACE1##IxNew;                                                                                                                     \
        for (__##FACE1##IxOld = 1; __##FACE1##IxOld <= __##FACE1##NbOld; __##FACE1##IxOld++)                                                                        \
        {                                                                                                                                                           \
          CATGeometry * __##FACE1##GeoOld = __##FACE1##Old[__##FACE1##IxOld];                                                                                       \
          if (__##FACE1##GeoOld && __##FACE1##GeoOld->IsATypeOf(CATFaceType))                                                                                       \
          {                                                                                                                                                         \
            CATCXFace * FACE1 = (CATCXFace *)__##FACE1##GeoOld->GetImplementCGM(CATFaceType);                                                                       \
            if (FACE1)                                                                                                                                              \
            {                                                                                                                                                       \
              for (__##FACE1##IxNew = 1; __##FACE1##IxNew <= __##FACE1##NbNew; __##FACE1##IxNew++)                                                                  \
              {                                                                                                                                                     \
                CATGeometry * __##FACE1##GeoNew = __##FACE1##New[__##FACE1##IxNew];                                                                                 \
                if (__##FACE1##GeoNew && __##FACE1##GeoNew->IsATypeOf(CATFaceType))                                                                                 \
                {                                                                                                                                                   \
                  CATCXFace * FACE2 = (CATCXFace *)__##FACE1##GeoNew->GetImplementCGM(CATFaceType);                                                                 \
                  if (FACE2)                                                                                                                                        \
                  {                                                                                                                                          
                                                                                                                                                             

#define CATForFaceInJournalEnd                                                                                                                                      \
                  }                                                                                                                                                 \
                }                                                                                                                                                   \
              }                                                                                                                                                     \
            }                                                                                                                                                       \
          }                                                                                                                                                         \
        }                                                                                                                                                           \
      }                                                                                                                                                             \
    }                                                                                                                                                               \
  }                                                                                                                                                                 \
}

//------------------------------------------------------------------------------------------

#define CATForEdgeInFaceBegin(FACE, LOOP, EDGE, CXEDG)                                                                                                                     \
{                                                                                                                                               \
  if (!(FACE))                                                                                                                                                        \
    CATSubdBlockThrowInternalError();                                                                                                            \
  CATSubdBoundingFace * __##EDGE##BoundingFace = FACE->GetSubdFace();                                                                                              \
  if (!__##EDGE##BoundingFace || __##EDGE##BoundingFace->IsContainedInGlobalGarbageCollector() == CATSubdBooleanTrue ||                                               \
       __##EDGE##BoundingFace->IsFS() != CATSubdBooleanTrue)                                                                                                          \
    CATSubdBlockThrowInternalError();                                                                                                            \
  const CATCXLocatedDomains & __##EDGE##Loops = __##EDGE##BoundingFace->GetDomains();                                                                                 \
  CATCXDomainsFilterDo (__##EDGE##Loops, LOOP, Loop)                                                                                                                  \
  {                                                                                                                                                                   \
    CATSubdBoundingEdge * __##EDGE##MyFirstEdge = LOOP->GetFirstEdge();                                                                                               \
    CATSubdBoundingEdge * EDGE = __##EDGE##MyFirstEdge;                                                                                                               \
    do                                                                                                                                                                \
    {                                                                                                                                                                 \
      if (!EDGE || EDGE->IsContainedInGlobalGarbageCollector() == CATSubdBooleanTrue)                                                                                 \
        CATSubdBlockThrowInternalError();                                                                                                        \
      CATCXEdge * CXEDG = (CATCXEdge *)EDGE->GetClass();          \
      if (!CXEDG)                                                  \
        CATSubdBlockThrowInternalError();


#define CATForEdgeInFaceEnd(EDGE)                  \
      EDGE = EDGE->GetNextInEdgeDomain();            \
    }                                                \
    while (EDGE && (EDGE != __##EDGE##MyFirstEdge)); \
  } CATCXDomainsFilterEnd;                           \
}

//------------------------------------------------------------------------------------------

#define CATForFaceInShellBegin(CXSHELL, CXFACE, ORI)                                          \
if (CXSHELL)                                                                                  \
{                                                                                             \
  const CATCXOrientedFaces & OrientedFaces##CXFACE = CXSHELL->GetOrientedFaces();             \
  int Index##CXFACE, NbOrientedFaces##CXFACE(OrientedFaces##CXFACE.Size());                   \
  for (Index##CXFACE = 0; Index##CXFACE < NbOrientedFaces##CXFACE; Index##CXFACE++)           \
  {                                                                                           \
    CATCXFace * CXFACE = NULL;                                                                \
    CATOrientation ORI = CATOrientationUnknown;                                               \
    OrientedFaces##CXFACE.Access(Index##CXFACE, CXFACE, ORI);                                 \
    if (CXFACE)                                                                               \
    {


#define CATForFaceInShellEnd           \
    }                                  \
  }                                    \
}

//------------------------------------------------------------------------------------------

#define CATForWireEdgesBegin(CXWIRE, SUBDBOUNDINGEDGE, CXEDGE)                                                         \
if (CXWIRE)                                                                                                            \
{                                                                                                                      \
  CATSubdBoundingEdge * FirstEdge##SUBDBOUNDINGEDGE = CXWIRE->GetFirstEdge();                                          \
  CATSubdListDo(FirstEdge##SUBDBOUNDINGEDGE, SUBDBOUNDINGEDGE, CATSubdBoundingEdge *, GetNextInEdgeDomain)             \
  {                                                                                                                    \
    if ( SUBDBOUNDINGEDGE->IsContainedInGlobalGarbageCollector() != CATSubdBooleanFalse)                               \
      CATSubdBlockThrowInternalError();                                                           \
                                                                                                                       \
    CATCXEdge * CXEDGE = (CATCXEdge *)SUBDBOUNDINGEDGE->GetClass();                                                    \
    if (!CXEDGE)                                                                                                       \
      CATSubdBlockThrowInternalError();


#define CATForWireEdgesEnd(SUBDBOUNDINGEDGE)    \
  } CATSubdListEnd(SUBDBOUNDINGEDGE);           \
}

//------------------------------------------------------------------------------------------

#define CATForBodyWireEdgesBegin(CXBODY, CXWIRE, SUBDBOUNDINGEDGE, CXEDGE)                                                                         \
if (CXBODY)                                                                                                                                        \
{                                                                                                                                                  \
  CATLISTP(CATDomain) AllOutputWires##SUBDBOUNDINGEDGE;                                                                                            \
  CXBODY->GetAllDomains(1, 3, AllOutputWires##SUBDBOUNDINGEDGE);                                                                                   \
                                                                                                                                                   \
  int Idx##SUBDBOUNDINGEDGE, Nb##SUBDBOUNDINGEDGE(AllOutputWires##SUBDBOUNDINGEDGE.Size());                                                        \
  for (Idx##SUBDBOUNDINGEDGE = 1; Idx##SUBDBOUNDINGEDGE <= Nb##SUBDBOUNDINGEDGE; Idx##SUBDBOUNDINGEDGE++)                                          \
  {                                                                                                                                                \
    CATDomain * CurrDomain##SUBDBOUNDINGEDGE = AllOutputWires##SUBDBOUNDINGEDGE[Idx##SUBDBOUNDINGEDGE];                                            \
    CATCXWire * CXWIRE = CurrDomain##SUBDBOUNDINGEDGE ? (CATCXWire *)CurrDomain##SUBDBOUNDINGEDGE->GetImplementCGM(CATWireType) : NULL;            \
    if (!CXWIRE)                                                                                                                                   \
      CATSubdBlockThrowInternalError();                                                                                       \
                                                                                                                                                   \
    CATForWireEdgesBegin(CXWIRE, SUBDBOUNDINGEDGE, CXEDGE)                                                                                         \
    {

#define CATForBodyWireEdgesEnd(SUBDBOUNDINGEDGE)       \
    } CATForWireEdgesEnd(SUBDBOUNDINGEDGE)             \
  }                                                    \
}

//------------------------------------------------------------------------------------------

#define UpwardEdge_Begin(CXEDGE, SUBDEDGECURVE, CXEDGEDOMAIN)                                             \
if (CXEDGE)																																																\
{																																																					\
	const CATSubdArrayMemEdgeP * SubdEdges##CXFACE = CXEDGE->GetSubdEdges();																\
	if (SubdEdges##CXFACE)																																									\
	{																																																				\
		CATSubdArrayBegin (*SubdEdges##CXFACE, CurrentSubdEdge##CXFACE, CATSubdEdge *)												\
		{																																																			\
			if (   CurrentSubdEdge##CXFACE->IsContainedInGlobalGarbageCollector() == CATSubdBooleanFalse				\
				  && CurrentSubdEdge##CXFACE->IsEC() == CATSubdBooleanTrue																				\
				 )																																																\
			{																																																		\
				CATSubdEdgeCurve * SUBDEDGECURVE = (CATSubdEdgeCurve *)CurrentSubdEdge##CXFACE;                   \
        if (SUBDEDGECURVE)                                                                                \
        {                                                                                                 \
          CATCXEdgeDomain * CXEDGEDOMAIN = SUBDEDGECURVE->ReturnEdgeDomain();                             \
          if (CXEDGEDOMAIN)                                                                               \
          {

#define UpwardEdge_End    \
          }               \
        }                 \
      }                   \
    } CATSubdArrayEnd;    \
  }                       \
}

//------------------------------------------------------------------------------------------
// QCN5 2020-06-12, begin
#define UpwardFace_Begin(CXFACE, SUBDBOUNDINGFACE, CXLEFTSHELL, CXRIGHTSHELL)               \
if (CXFACE)																																				          \
{																																									          \
  CATSubdFace * SUBDFACE##CXVOL = CXFACE->GetSubdFace();																    \
  if (SUBDFACE##CXVOL)																																		  \
  {																																								          \
    if ( SUBDFACE##CXVOL->IsContainedInGlobalGarbageCollector() == CATSubdBooleanFalse)     \
    {																																							          \
      CATSubdBoundingFace * SUBDBOUNDINGFACE =  SUBDFACE##CXVOL->IsBoundingFace();          \
      if (SUBDBOUNDINGFACE)                                                                 \
      {                                                                                     \
        CATCXShell * CXLEFTSHELL = SUBDBOUNDINGFACE->GetLeftShell();                        \
        CATCXShell * CXRIGHTSHELL = SUBDBOUNDINGFACE->GetRightShell();                           


#define UpwardFace_End    \
      }                   \
    }                     \
  }                       \
} 
// QCN5 2020-06-12, end

//------------------------------------------------------------------------------------------

#define UpwardScan_EdgeToFaces_Begin(CXEDGE, SUBDEDGECURVE, CXLOOP, SUBDFACE, CXFACE)           \
UpwardEdge_Begin(CXEDGE, SUBDEDGECURVE, EdgeDomain##CXFACE)                                     \
{                                                                                               \
	CATCXLoop * CXLOOP = EdgeDomain##CXFACE->CastToLoop();													  				  	\
	if (CXLOOP)																																	                	\
	{																																															\
		CATSubdFace * SUBDFACE = CXLOOP->RetrieveFace();																		        \
		if (   SUBDFACE																																			        \
				&& SUBDFACE->IsContainedInGlobalGarbageCollector() == CATSubdBooleanFalse					      \
				)																																												\
		{																																														\
			CATCXFace * CXFACE = (CATCXFace *)SUBDFACE->GetClass();															      \
			if (CXFACE)																																								\
			{

#define UpwardScan_EdgeToFaces_End      \
			}											          	\
		}												          	\
	}													           	\
} UpwardEdge_End;

//------------------------------------------------------------------------------------------

#define UpwardScan_VertexToEdges_Begin(CXVERTEX, BOUNDINGVERTEX, EDGECURVE, CXEDGE)                                         \
if (CXVERTEX)                                                                                                               \
{                                                                                                                           \
  const CATSubdArrayMemVertexP * SubdVertices##CXEDGE = CXVERTEX->GetSubdVertices();                                        \
  if (SubdVertices##CXEDGE)                                                                                                 \
  {                                                                                                                         \
    CATSubdArrayBegin (*SubdVertices##CXEDGE, CurrentSubdVertex##CXEDGE, CATSubdVertex *)                                   \
    {                                                                                                                       \
      if (CurrentSubdVertex##CXEDGE->IsContainedInGlobalGarbageCollector() == CATSubdBooleanFalse)                          \
      {                                                                                                                     \
        CATSubdBoundingVertex * BOUNDINGVERTEX = CurrentSubdVertex##CXEDGE->CastToBoundingVertex();                         \
        if (BOUNDINGVERTEX)                                                                                                 \
        {                                                                                                                   \
          CATSubdEdge * SubdEdge##CXEDGE = BOUNDINGVERTEX->GetEdge();                                                       \
          if (SubdEdge##CXEDGE && SubdEdge##CXEDGE->IsContainedInGlobalGarbageCollector() == CATSubdBooleanFalse)           \
          {                                                                                                                 \
            CATSubdEdgeCurve * EDGECURVE = SubdEdge##CXEDGE->CastToEdgeCurve();                                             \
            if (EDGECURVE)                                                                                                  \
            {                                                                                                               \
              CATCXEdge * CXEDGE = (CATCXEdge *)EDGECURVE->GetClass();                                                      \
              if (CXEDGE)                                                                                                   \
              {


#define UpwardScan_VertexToEdges_End       \
              }                            \
            }                              \
          }                                \
        }                                  \
      }                                    \
    } CATSubdArrayEnd;                     \
  }                                        \
}

//------------------------------------------------------------------------------------------

#define UpwardVertex_Begin(CXVERTEX, UPWARD) \
if (CXVERTEX) \
{ \
  CATCXLinkVertexType * CXVERTEX##UpperAndLinkTypes = CXVERTEX->GetUpwardVertex(); \
  if (CXVERTEX##UpperAndLinkTypes) \
  { \
    int CXVERTEX##I, CXVERTEX##N(CXVERTEX->GetNumberOfUpwardLinks()); \
    for (CXVERTEX##I = 0; CXVERTEX##I < CXVERTEX##N; CXVERTEX##I++) \
    { \
      CATCXTopology * UPWARD = CXVERTEX##UpperAndLinkTypes[CXVERTEX##I].Evaluate(); \
      if (UPWARD) \
      {

#define UpwardVertex_End \
      } \
    } \
  } \
}

//------------------------------------------------------------------------------------------

#define UpwardScan_Vertex_Begin(CXVERTEX) \
UpwardVertex_Begin(CXVERTEX, __Upper) \
{

#define UpwardScan_Vertex_EdgeCase(CXEDGE) \
  if (CATCXEdge * CXEDGE = __Upper->CastToEdge()) \
  {

#define UpwardScan_Vertex_FaceCase(CXVIF, SUBDBF, CXFACE) \
  } \
  else if (CATCXVertexInFace * CXVIF = __Upper->CastToVertexInFace()) \
  { \
    CATSubdBoundingFace * SUBDBF = CXVIF->GetOwningFace(); \
    if (SUBDBF) \
    { \
      CATCXFace * CXFACE = (CATCXFace *)SUBDBF->GetClass(); \
      if (CXFACE) \
      { \

#define UpwardScan_Vertex_End \
      } \
    } \
  } \
} UpwardVertex_End;

//------------------------------------------------------------------------------------------

#define CXVertexIVBegin(CXVTX, IV, CONTAINER) \
CXVertexSubdBegin(CXVTX, __##IV##SubdVtx) \
{ \
  CATSubdIntersectionVertex * IV = __##IV##SubdVtx->CastToIntersectionVertex(); \
  if (IV) \
  { \
    CATSubdOccurence * CONTAINER = IV->GetContainer();

#define CXVertexIVEnd \
  } \
} CXVertexSubdEnd;

//------------------------------------------------------------------------------------------

#endif
