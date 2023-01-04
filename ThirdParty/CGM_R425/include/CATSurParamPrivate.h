#ifndef CATSurParamPrivate_h
#define CATSurParamPrivate_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATSurParamPrivate : parameter on a surface of type CATSurface
//
// DESCRIPTION : this object is used by the surfaces to build some CATSurParam
// from their position
// 
// NOTE : as the CATSurParam and the CATSurParamPrivate have the same length
// (no additional members), one can use a cast to use the following methods.
//
//=============================================================================
//
// Inheritance :
//      - CATSurParam
//        - CATSurParamPrivate
//
//=============================================================================
//
// History
//
// Jun. 97  Simon Royer (sro)     Creation 
//
// Jul. 97  Jose CHILLAN (jch)    Modification due to the change of implementation
//
//=============================================================================

#include "YP00IMPL.h"

#include "CATSurParam.h"

class CATParamData;
class CATSurface;

class ExportedByYP00IMPL CATSurParamPrivate : public CATSurParam
{
public:
// Copy constructor
  CATSurParamPrivate (const CATSurParam & iCopiedParam);

// Builds a SurParam pointing on an interface of CATSurface, with a patch number
// in an a position on the patch (see the class CATParamData) in both U and V
// coordinates.
// The object uses the KnotVector's of the CATSurface if it exists, else the surface
// is considered as monopatch.
  CATSurParamPrivate (const CATParamData & iPositionU,
		      const CATParamData & iPositionV,
		      const CATSurface   * iSurface);

// Getting and setting the surface the param belongs
  const CATSurface * GetSurface() const;
  void SetSurface(const CATSurface * surface);

};

#endif
