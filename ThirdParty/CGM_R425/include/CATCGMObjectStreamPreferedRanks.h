/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */
#ifndef CATCGMObjectStreamPreferedRanks_H
#define CATCGMObjectStreamPreferedRanks_H

//=============================================================================
// DESCRIPTION : CATCGMObject prefered order of appearance in
//               streamed CGM container
//=============================================================================
// Mar. 05 Creation (RI0486478)                                           HCN
//=============================================================================

#define CATCGMStreamPreferedRank_MAX               19

#define CATCGMStreamPreferedRank_Body				       19
#define CATCGMStreamPreferedRank_Lump				       18
#define CATCGMStreamPreferedRank_Volume				     17
#define CATCGMStreamPreferedRank_Shell				     16
#define CATCGMStreamPreferedRank_Face				       15
#define CATCGMStreamPreferedRank_EdgeDomain				 14
#define CATCGMStreamPreferedRank_Edge				       13
#define CATCGMStreamPreferedRank_CldGenEntity	     12
#define CATCGMStreamPreferedRank_Domain				     11
#define CATCGMStreamPreferedRank_Vertex				     10
#define CATCGMStreamPreferedRank_MacroPoint		      9
#define CATCGMStreamPreferedRank_PointOnEdgeCurve   8
#define CATCGMStreamPreferedRank_ProcCurve	        7
#define CATCGMStreamPreferedRank_EdgeCurveRef	      6
#define CATCGMStreamPreferedRank_PCurve			        5
#define CATCGMStreamPreferedRank_PPoint			        4
#define CATCGMStreamPreferedRank_Surface			      3
#define CATCGMStreamPreferedRank_Curve				      2
#define CATCGMStreamPreferedRank_Point				      1
#define CATCGMStreamPreferedRank_CGMObject			    0   // Par defaut on renvoie 0

#define CATCGM_TEST_OBJECT_ALREADY_STREAMED( pIObject )                                 \
if (pIObject)                                                                           \
{                                                                                       \
  CATCGMObject* pCGMObject = (CATCGMObject*)pIObject->GetImplementCGM(CATGeometryType); \
  if (pCGMObject)                                                                       \
  {                                                                                     \
    Result = pCGMObject->IsAlreadyStreamed();                                           \
    if (!Result)                                                                        \
      return Result;                                                                    \
  }                                                                                     \
}

#endif
