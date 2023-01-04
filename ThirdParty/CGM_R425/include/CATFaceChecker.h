// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  09/10/2000
//
// Operateur de check d'auto-intersection de frontieres (loops) de face
//=============================================================================

#ifndef __CATFaceChecker_h__
#define __CATFaceChecker_h__

#include "CATChecker.h"
#include "CheckOperators.h"

class CATGeoFactory;
class CATTopData;
class CATCXFaceChecker;
class CATShell;
class CATFace;


class ExportedByCheckOperators CATFaceChecker: public CATChecker
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATFaceChecker(CATGeoFactory    * iFactory,
                     CATTopData       * iData,
                     CATCXFaceChecker * iImplementation);
      
      virtual ~CATFaceChecker();


      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================


      //====================================
      // Parametrisation de l'operateur
      //====================================

      void SetFaceToCheck(CATFace * iFaceToCheck);
      void SetShellToCheck(CATShell * iShellToCheck);
};

#endif
