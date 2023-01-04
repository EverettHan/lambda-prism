// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  09/10/2000
//
// Operateur de check d'intersection shell/shell.
//=============================================================================

#ifndef __CATShellIntersectionChecker_h__
#define __CATShellIntersectionChecker_h__

#include "CheckOperators.h"
#include "CATIntersectionChecker.h"

class CATGeoFactory;
class CATTopData;
class CATCXShellIntersectionChecker;
class CATLISTP(CATFace);
class CATShell;
class CATVolume;


class ExportedByCheckOperators CATShellIntersectionChecker: public CATIntersectionChecker
{
  CATCGMVirtualDeclareClass(CATShellIntersectionChecker);
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATShellIntersectionChecker(CATGeoFactory                 * iFactory,
                                  CATTopData                    * iData,
                                  CATCXShellIntersectionChecker * iImplementation);
      
      virtual ~CATShellIntersectionChecker();


      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

      //====================================
      // Parametrisation de l'operateur
      //====================================

      void SetShellsToCheck(CATShell * iShell1, CATShell * iShell2 = (CATShell*)0);
      void SetVolumeToCheck(CATVolume * iVolumeToCheck);

      void SetListOfRestrictedFaces(CATLISTP(CATFace)& iSetOfRestrictedFaces);
      void SetOnlyDisjoinFaces(CATBoolean iOnlyDisjoinFaces); 
};

#endif
