//=======================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=======================================================================
//
// CATConvertToContinuousNurbsBipar
// Many global geometrical algorithms use CATFrFNurbsBipar s, that are
// just C0 biparammetrical elements.
// We may need more continuous sub-elements of these CATFrFNurbsBipar s.
// For instance, to represent such geometry in the model, we need 
// C2 surfaces.
// We may need C1 surfaces for some marching algorithms.
// This class is designed to break a CATFrFNurbsBipar a higher level 
// of continuity.
//
//=======================================================================
//
// Usage notes:
//=======================================================================
// Nov 98    Creation                   PRG
//=======================================================================
#ifndef CATConvertToContinuousNurbsBipar_H
#define CATConvertToContinuousNurbsBipar_H

class CATFrFNurbsBipar;
class CATKnotVector;

#include "CATSkillValue.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

//-----------------------------------------------------------------------
#include "YP00IMPL.h"
class ExportedByYP00IMPL CATConvertToContinuousNurbsBipar : public CATCGMVirtual
{
  public :
    CATConvertToContinuousNurbsBipar(CATLONG32 expecteduContinuity,
				                             CATLONG32 expectedvContinuity,
				                             CATFrFNurbsBipar* bipar,
                                     CATSkillValue     iMode = BASIC);
  virtual ~CATConvertToContinuousNurbsBipar();

  CATLONG32 GetNbOfNurbsBiparAlongU(){return _nbOfContinuousBiparAlongU;};
  CATLONG32 GetNbOfNurbsBiparAlongV(){return _nbOfContinuousBiparAlongV;};

  CATFrFNurbsBipar* GetResultingContinuousNurbsBipar(CATLONG32 iU, CATLONG32 iV)
    {return _resultingBipar[iU][iV];};

  // 
  void GetResultingBipares(CATFrFNurbsBipar***& bipares,
                           CATLONG32& nbBiparesAlongU,
                           CATLONG32& nbBiparesAlongV)
    {
      bipares = _resultingBipar;
      nbBiparesAlongU = _nbOfContinuousBiparAlongU;
      nbBiparesAlongV = _nbOfContinuousBiparAlongV;
    };
  void Run();
 private:
  CATFrFNurbsBipar*   _bipar;
  CATFrFNurbsBipar*** _resultingBipar;

  CATLONG32 _expectedContinuityAlongU;
  CATLONG32 _expectedContinuityAlongV;

  CATLONG32 _nbOfContinuousBiparAlongU;
  CATLONG32 _nbOfContinuousBiparAlongV;

};
#endif
