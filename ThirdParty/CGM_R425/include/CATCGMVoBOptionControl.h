#ifndef CATCGMVoBOptionControl_h_
#define CATCGMVoBOptionControl_h_

//=============================================================================
// Creation YL3, March 2012
//
// Management of VoB's options
//=============================================================================


#include "CATDataType.h"
#include "CATMathInline.h"

class CATCGMVoBOptionControl
{
public:
  CATULONG32 _VoBOption;

  CATCGMVoBOptionControl();
  ~CATCGMVoBOptionControl();

  CATCGMVoBOptionControl& operator=(const CATCGMVoBOptionControl& iOther);
	CATCGMVoBOptionControl (const CATCGMVoBOptionControl & iOther);

  void Init();

  INLINE CATULONG32 GetVoBOption() const;

  // Import the specific options of operator into VoB Options
  INLINE void ImportOperatorVoBOption(CATULONG32 iVoBOption);

  //=======================================================
  // VoB Options
  //=======================================================
  INLINE int  IsPolyhedralAutoCheckUsed() const;
  INLINE void SetPolyhedralAutoCheckUsed();

  INLINE int  IsAlwaysExhaustiveCheck() const;
  INLINE void SetAlwaysExhaustiveCheck();

  INLINE int  IsIgnoreIntersectionThrow() const;
  INLINE void SetIgnoreIntersectionThrow();

  //=======================================================
  // Filters of collision results
  //=======================================================
  INLINE int  IsFilterOfAdjacentFaceByEdge() const;
  INLINE void SetFilterOfAdjacentFaceByEdge();

  INLINE int  IsFilterOfAdjacentFaceByVertex() const;
  INLINE void SetFilterOfAdjacentFaceByVertex();

  //INLINE int  IsFilterOfTinyEdgeBetweenFaces() const;
  //INLINE void SetFilterOfTinyEdgeBetweenFaces();

  INLINE int  IsFilterOfIntersectionBetweenEdge() const;
  INLINE void SetFilterOfIntersectionBetweenEdge();

  INLINE int  IsFilterOfConfusedEdge() const;
  INLINE void SetFilterOfConfusedEdge();

  INLINE int  IsFilterOfIntersectionVertex() const;
  INLINE void SetFilterOfIntersectionVertex();

  INLINE int  IsFilterOfNotCrossingIE() const;
  INLINE void SetFilterOfNotCrossingIE();

  INLINE int  IsFaceConfusionDetection() const;
  INLINE void SetFaceConfusionDetection();

  // Filter the no crossiong collision between edges in Face.
  INLINE int  IsFilterOfNotCrossingIVBetweenEdges() const;
  INLINE void SetFilterOfNotCrossingIVBetweenEdges();

  //==============================================================================
  // Specific options for certains operators (Ex: Assemble, TrimSew, Boolean)
  //==============================================================================

  // For check of Boolean contact. Active only for CATDynBoolean, CATHybTrim and CATDynSplit 
  INLINE int  IsNoIntersectionCheck() const;
  INLINE void SetNoIntersectionCheck();

  // Filter the collisions which are present between the corresponding originals cells in InputBody
  // Active only for Assemble and TrimSew because these operator do not change the geometry
  INLINE int  IsPosteriorFilterActive() const;
  INLINE void SetPosteriorFilterActive();

  // For assemble operator, the modifed faces in Journal can be considered as a non-modified face(no geometry change)
  // In this case, should not do the pre-check of the DiffMathBox with associated modified face.   
  INLINE int  IsNoChangedFaceForAssemble() const;
  INLINE void SetNoChangedFaceForAssemble();
  

};

INLINE CATULONG32 CATCGMVoBOptionControl::GetVoBOption() const
{
  return _VoBOption;
}
INLINE void CATCGMVoBOptionControl::ImportOperatorVoBOption(CATULONG32 iVoBOption)
{
  _VoBOption |= iVoBOption;
}

INLINE int CATCGMVoBOptionControl::IsPolyhedralAutoCheckUsed() const
{ return _VoBOption & 0x01UL; }
INLINE void CATCGMVoBOptionControl::SetPolyhedralAutoCheckUsed()
{ _VoBOption |= 0x01UL; }

INLINE int CATCGMVoBOptionControl::IsFilterOfAdjacentFaceByEdge() const
{ return _VoBOption & 0x02UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfAdjacentFaceByEdge()
{ _VoBOption |= 0x02UL; }


INLINE int CATCGMVoBOptionControl::IsFilterOfAdjacentFaceByVertex() const
{ return _VoBOption & 0x04UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfAdjacentFaceByVertex()
{ _VoBOption |= 0x04UL; }

//INLINE int CATCGMVoBOptionControl::IsFilterOfTinyEdgeBetweenFaces() const
//{ return _VoBOption & 0x04UL; }
//INLINE void CATCGMVoBOptionControl::SetFilterOfTinyEdgeBetweenFaces()
//{ _VoBOption |= 0x04UL; }

INLINE int CATCGMVoBOptionControl::IsFilterOfIntersectionBetweenEdge() const
{ return _VoBOption & 0x08UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfIntersectionBetweenEdge()
{ _VoBOption |= 0x08UL; }

INLINE int CATCGMVoBOptionControl::IsFilterOfConfusedEdge() const
{ return _VoBOption & 0x10UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfConfusedEdge()
{ _VoBOption |= 0x10UL; }

INLINE int CATCGMVoBOptionControl::IsFilterOfIntersectionVertex() const
{ return _VoBOption & 0x20UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfIntersectionVertex()
{ _VoBOption |= 0x20UL; }

INLINE int CATCGMVoBOptionControl::IsFilterOfNotCrossingIE() const
{ return _VoBOption & 0x40UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfNotCrossingIE()
{ _VoBOption |= 0x40UL; }

INLINE int CATCGMVoBOptionControl::IsAlwaysExhaustiveCheck() const
{ return _VoBOption & 0x80UL; }
INLINE void CATCGMVoBOptionControl::SetAlwaysExhaustiveCheck()
{ _VoBOption |= 0x80UL; }

INLINE int CATCGMVoBOptionControl::IsIgnoreIntersectionThrow() const
{ return _VoBOption & 0x100UL; }
INLINE void CATCGMVoBOptionControl::SetIgnoreIntersectionThrow()
{ _VoBOption |= 0x100UL; }

INLINE int CATCGMVoBOptionControl::IsFaceConfusionDetection() const
{ return _VoBOption & 0x200UL; }
INLINE void CATCGMVoBOptionControl::SetFaceConfusionDetection()
{ _VoBOption |= 0x200UL; }

INLINE int CATCGMVoBOptionControl::IsNoIntersectionCheck() const
{ return _VoBOption & 0x400UL; }
INLINE void CATCGMVoBOptionControl::SetNoIntersectionCheck()
{ _VoBOption |= 0x400UL; }

INLINE int CATCGMVoBOptionControl::IsPosteriorFilterActive() const
{ return _VoBOption & 0x800UL; }
INLINE void CATCGMVoBOptionControl::SetPosteriorFilterActive()
{ _VoBOption |= 0x800UL; }

INLINE int  CATCGMVoBOptionControl::IsFilterOfNotCrossingIVBetweenEdges() const
{ return _VoBOption & 0x1000UL; }
INLINE void CATCGMVoBOptionControl::SetFilterOfNotCrossingIVBetweenEdges()
{ _VoBOption |= 0x1000UL; }

INLINE int  CATCGMVoBOptionControl::IsNoChangedFaceForAssemble() const
{ return _VoBOption & 0x2000UL; }
INLINE void CATCGMVoBOptionControl::SetNoChangedFaceForAssemble()
{ _VoBOption |= 0x2000UL; }

#endif
