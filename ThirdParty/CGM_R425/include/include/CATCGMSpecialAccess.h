/* -*-c++-*- */
#ifndef CATCGMSpecialAccess_H_
#define CATCGMSpecialAccess_H_
// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
// CGM usage only
//=============================================================================
// Jun. 05  Creation                                                        FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATICGMObject.h"
#include "CATBoolean.h"

#include "CATDataType.h"

// MACRO d'incrementation du compteur UseCount
// Doit obligatoirement etre suivie d'une des 2 macros DEC_USECOUNT...  (sinon compilation KO)
// iObject = CATICGMObject* = adresse de l'objet
// oUsecount = CATULONG32 = valeur du UseCount apres incrementation
#ifndef INC_USECOUNT
#define INC_USECOUNT(iObject, oUseCount) { \
CATTry { \
  CATCGMSpecialAccess::IncUseCount(iObject, oUseCount); \
} 
#endif

// MACRO de decrementation du compteur UseCount sans Factory->Remove de l'objet si USeCount tombe a 0
// Doit obligatoirement etre precedee de la macro INC_USECOUNT (sinon compilation KO)
// iObject = CATICGMObject* = adresse de l'objet
// oUsecount = CATULONG32 = valeur du UseCount apres incrementation
#ifndef DEC_USECOUNT_DONT_REMOVE
#define DEC_USECOUNT_DONT_REMOVE(iObject, oUseCount) { \
CATCGMSpecialAccess::DecUseCount(iObject, oUseCount); \
} \
CATCatch(CATError, Error) { \
  CATRethrow; \
} \
CATEndTry; \
}
#endif

// MACRO de decrementation du compteur UseCount avec Factory->Remove de l'objet si UseCount tombe a 0
// Doit obligatoirement etre precedee de la macro INC_USECOUNT (sinon compilation KO)
// iObject = CATICGMObject* = adresse de l'objet
// oUsecount = CATULONG32 = valeur du UseCount apres incrementation
// oHasBeenRemoved = CATBoolean = indique si un Factory->Remove a ete effectue (optionnel, et si iRemoveIfPossible=TRUE)
#ifndef DEC_USECOUNT_AND_REMOVE_IF_POSSIBLE
#define DEC_USECOUNT_AND_REMOVE_IF_POSSIBLE(iObject, oUseCount, oHasBeenRemoved) { \
CATBoolean efface = TRUE; \
CATBoolean removed = FALSE; \
CATCGMSpecialAccess::DecUseCount(iObject, oUseCount, efface, &removed); \
oHasBeenRemoved = (removed ? TRUE : FALSE); \
} \
CATCatch(CATError, Error) { \
  CATRethrow; \
} \
CATEndTry; \
}
#endif

class ExportedByGeometricObjects CATCGMSpecialAccess
{
public:

//=================================================================
// Services permettant de modifier le CGA.UseCount d'un objet.
// Si vous pouvez, utilisez plutot les macros qui garantissent une
// utilisation "controlee".
// Si vous utilisez ces services, c'est a vous de vous assurer du
// bon fonctionnement de la duree de vie de l'objet.
//=================================================================

// Incrementation du compteur UseCount - Utilisez si possible la macro INC_USECOUNT
// oUsecount = valeur du UseCount apres incrementation
static void IncUseCount(CATICGMObject *iObject, CATULONG32 & oUseCount);

// Decrementation du compteur UseCount - Utilisez si possible une des macros DEC_USECOUNT...
// oUsecount         = valeur du UseCount apres decrementation
// iRemoveIfPossible = indique si on doit detruire l'objet si c'est possible (optionnel, par defaut = FALSE)
// oHasBeenRemoved   = indique si un Factory->Remove a ete effectue (optionnel, et n'ayant de sens que si iRemoveIfPossible=TRUE)
static void DecUseCount(CATICGMObject *iObject, CATULONG32 & oUseCount, 
                        CATBoolean iRemoveIfPossible = FALSE, CATBoolean * oHasBeenRemoved=0);

//=================================================================
// Services permettant de modifier le CGA.Removable d'un objet.
// Si vous utilisez ces services, c'est a vous de vous assurer du
// bon fonctionnement de la duree de vie de l'objet.
// Vous devez aussi controler l'existence de l'objet, en particulier dans les utilisations du type
//      SetRemovable(Objet);
//      ...Tentative de destruciton de l'objet (ReleaseReference par ex)...
//      UnsetRemovable(Objet); // risque de Core Dump si l'objet a ete detruit
//=================================================================

// Autorisation d'effacement d'un objet lorsque son UseCount tombe a 0
// oWasRemovable = optionnel = etat du flag "Removable" avant le set
static void SetRemovable(CATICGMObject *iObject, CATBoolean * oWasRemovable = 0);

// Suppression de l'autorisation d'effacement d'un objet lorsque son UseCount tombe a 0
// ATTENTION : Ceci ne protege pas l'objet d'un effacement. La methode ne fait qu'enlever l'autorisation de SetRemovable
// oWasRemovable = etat du flag "Removable" avant le unset
static void UnsetRemovable(CATICGMObject *iObject, CATBoolean * oWasRemovable = 0);

};

#endif

