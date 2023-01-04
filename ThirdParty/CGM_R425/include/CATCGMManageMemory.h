/* -*-c++-*- */
#ifndef CATCGMManageMemory_H
#define CATCGMManageMemory_H
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//     Internal Use only
//============================================================================
#include "CATMathematics.h"
#include "CATBoolean.h"

class CATHashDico;

//--------------------------------------------------------------------
// Typage Evenement 
//       CATCGMManageMemory::MemoryGarbage(CatCGMoMore_CATProduct);
//--------------------------------------------------------------------
enum CATCGMEventGarbage {CatCGMNoMoreFactoryV5  = +0, 
                         CatCGMEndingExecution  = +1,
                         CatCGMoMore_CATProduct = +2,
                         CatCGMoMore_FirstFactoryV5 = +3,
                         CatCGMoMore_StartFactoryV5 = +4 };

//--------------------------------------------------------------------
// Signature CallBack de Nettoyage
//--------------------------------------------------------------------
typedef void (*CATCGMManageMemoryGarbage) (CATCGMEventGarbage iEvent);


//--------------------------------------------------------------------
// Gestionnaire de nettoyage des objets globaux
//  (Creation a posterio pour mieux gerer les recalcitrants)
//-------------------------------------------------------------------
class ExportedByCATMathematics CATCGMManageMemory
{
public:
  //----------------------------------------------------------------------------
  // Evenement approprie pour reduire la voilure des objets globaux en memoire 
  //    Debut d'evenement critique sur la consommation memoire (File/Write)
  //    Dernier close de CATGeoFactory
  //----------------------------------------------------------------------------
  static void       MemoryGarbage(CATCGMEventGarbage iEvent);

  //--------------------------------------------------------------------
  // Factorisation CATGetEnv
  //--------------------------------------------------------------------
  static CATBoolean NoReplayPurify();
  static CATBoolean WithOmxMlkTracker();
  static CATBoolean Withcatcgmmultirun();

  //--------------------------------------------------------------------
  // Typage du nettoyage (obligatoire pour Debug)
  //--------------------------------------------------------------------
  enum FwGarbage { AdvMath = +0, GeoCGM = +1, TessDisc = +2 , CGMV5 = +3 , TopoCGM = +4 , TechTools = +5 };

  static void DeclareMemoryGarbage(CATCGMManageMemory::FwGarbage fw, CATCGMManageMemoryGarbage iFunction);

  static CATCGMManageMemoryGarbage  _AdvMath;
  static CATCGMManageMemoryGarbage  _GeoCGM;
  static CATCGMManageMemoryGarbage  _TessDisc;
  static CATCGMManageMemoryGarbage  _CGMV5;
  static CATCGMManageMemoryGarbage  _TopoCGM;
  static CATCGMManageMemoryGarbage  _TechTools;

 
  static CATHashDico             *  _catcgmmultirun;
};

#endif
