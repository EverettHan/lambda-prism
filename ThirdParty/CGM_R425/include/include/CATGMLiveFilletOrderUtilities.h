/* -*-C++-*- */

#ifndef CATGMLiveFilletOrderUtilities_H
#define CATGMLiveFilletOrderUtilities_H

// COPYRIGHT DASSAULT SYSTEMES 2016

//=============================================================================
//=============================================================================
//
// CATGMLiveFilletOrderUtilities : Utilitaires pour l'ordonnancement des
//                                 fillets 'live'
//
//=============================================================================

//=============================================================================
// Mai 2016  Creation                                                    PRL
// Mai 2016  HaveSamePriorityForCriteriaRSCO                             PRL
// Aou 2016  HasPriorityStepFillet - proto pour test d'integration       PRL
//=============================================================================
//=============================================================================


// classe
#include "PersistentCell.h"

// Defs si necessaire!
#ifndef NULL
#define NULL 0
#endif

// Gal
#include "CATBoolean.h"
class CATGeoFactory;
class CATSoftwareConfiguration;

// DRep
class CATBoneFillet;
#include "ListPOfCATBoneFillet.h"

// Topolo
class CATBody;


class ExportedByPersistentCell CATGMLiveFilletOrderUtilities
{

public: 
//===========================================================================================================

  //------------------------------------------------------------------------------
  // Ctor & Dtor
  //------------------------------------------------------------------------------    
  CATGMLiveFilletOrderUtilities();
  virtual ~CATGMLiveFilletOrderUtilities();

  //------------------------------------------------------------------------------    
  // Rend TRUE si les 2 bones en entree:
  //  - sont bitangents de meme rayon constant (R)
  //  - partagent un support unique (au sens fillet: contexte smooth) (S1)  
  //  - ont meme convexite (C)
  //  - sont connectes via une arete vive de convexite opposee a celle des fillets (O) 
  //  - il y a au moins un support smooth adjacent a l'edge trouvee en O(S2)
  //------------------------------------------------------------------------------  
  static CATBoolean HaveSamePriorityForCriteriaRSCO(CATSoftwareConfiguration *iConfig,
                                                    CATBody                  *iBody,
                                                    CATBoneFillet            *iBone1, 
                                                    CATBoneFillet            *iBone2,                                                    
                                                    double                    iTol);

  //------------------------------------------------------------------------------    
  // Rend le bone prioritaire entre iBone1 et iBone2 (au sens qu'il
  //  est necessaire d'enlever en premier ce fillet) si on est dans une config 'Step'  
  //------------------------------------------------------------------------------  
  static CATBoneFillet* HasStepPriority            (CATSoftwareConfiguration *iConfig,
                                                    CATBody                  *iBody,
                                                    CATBoneFillet            *iBone1, 
                                                    CATBoneFillet            *iBone2,
                                                    CATBoolean               &oChoice);


private:
//===========================================================================================================
  
  //------------------------------------------------------------------------------
  // Juste pour eviter que le compilo ne definisse par lui-meme ces operateurs
  //------------------------------------------------------------------------------    
  CATGMLiveFilletOrderUtilities(CATGMLiveFilletOrderUtilities& iObj);
  CATGMLiveFilletOrderUtilities& operator=(const CATGMLiveFilletOrderUtilities & iObj);

};
#endif

// Ne rien ecrire sous cette ligne
//===========================================================================================================

