#ifndef CATMathDebugTools_h
#define CATMathDebugTools_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2008
//
// Debug tools ** for debug purposes only **
//
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : Yes
//=============================================================================
//
// History
//
// 30/09/08 NLD Creation. CATMathDebugForceKeepWritingRecord()
// 02/10/08 NLD Ajout CATAddRef() CATRelease() CATModifyRef()
// 02/12/08 NLD Ajout CATCGMSetLevel1OperatorId() CATCGMGetLevel1OperatorId()
//=============================================================================
#include <CATMathematics.h>
#include <CATBaseUnknown.h>
#include <LesBonnesRecettesDuPereLochard.h>

class CATString ;
//---------------------------------------------------------------------------------------------------
// Permet de piloter par software depuis n'importe quel framework la conservation
// du CGMReplay en cours d'enregistrement, lorsqu'on travaille en mode 4
//   set CGMReplay=home=E:\tmp,4
// Ici a cause de la necessite eventuelle de faire un chargement dynamique du framework
// de gestion des CGMReplays, je centralise un outil de declenchement dans un
// framework de bas niveau
//---------------------------------------------------------------------------------------------------
extern "C" ExportedByCATMathematics void CATMathDebugForceKeepWritingRecord() ;

//---------------------------------------------------------------------------------------------------
// Outils de gestion des AddRef/Release avec signature par objet pointant et debug possible
//---------------------------------------------------------------------------------------------------
LesBonnesRecettesDuPereLochard(Unpublished021008_CATAddRef, "Debug fin des AddRef/Release via CATAddRef()/CATRelease()");
/*
From: LOCHARD Nicolas 
Sent: Thursday, October 02, 2008 7:12 PM
To: CHAILLOUX Thierry; DESLANDES Arnaud

instrumentation: 
remplacer 
object->AddRef() et object->Release() par CATAddRef(object, referencingobject) et CATRelease(object, referencingobject)

si appels non symetriques on aura un code 77 sur un objet de type CATCGMDebugReference

activation par 
set CGMDebugRefForCATAddRef=1
ou bien par activation via point d'arret CATAddRefToFollow()
on peut suivre toutes les references (par defaut) ou une reference dont on precise le pointeur lors du 1er passage dans  CATAddRefToFollow()


Cette premiere version qui fonctionne doit permettre de travailler.
J'ameliorerai eventuellement l'utilisabilite apres avoir fait joujou un peu plus avant et en fonction des demandes

CATCGMDebugReference lui-meme, sur lequel il est base, a ses propres outils de debug et notamment son systeme de traces 
Activable par
Set CGMDebugReferenceTraces=1
Et un point d'arret utile :
  CATCGMDebugReferenceBreakPoint


From: LOCHARD Nicolas 
Sent: Friday, October 03, 2008 9:47 AM
To: LOCHARD Nicolas; CHAILLOUX Thierry; DESLANDES Arnaud
Subject: RE: Debug AddRef/Release via CATCGMDebugTools


 J'ai pense a un truc qui pourrait rendre service.
- Le mode set CGMDebugRefForCATAddRef=1 continue a faire les AddRef/Release et les complete par l'utilisation de CATCGMDebugReference
- un nouveau mode set CGMDebugRefForCATAddRef=2 utilise les CATCGMDebugReference mais ne fait plus les AddRef/Release

 Je viens de faire, tester et promouvoir ce mode ; il permet au fur et a mesure de la migration des AddRef vers CATAddRef de les supprimer a la fois des traces et des points d'arret sur catcxtag ; On peut donc ainsi travailler confortablement lors des raffinements successifs permettant de trouver le bug.

 Bien sur c'est un mode de debug, et il ne pose pas de probleme tant que le premier AddRef assure la duree de vie suffisante de l'element qui nous interesse (en general c'est celui fait par la lecture de la factory)

 Nicolas  

From: LOCHARD Nicolas 
Sent: Tuesday, October 07, 2008 4:01 PM
To: DESLANDES Arnaud
Cc: CHAILLOUX Thierry
Subject: AddRef sous CATBaseUnknown_var 

Si la piste est CATBaseUnknown_var
Il est tres possible que tu aies simplement un objet non detruit a cause d'un throw 

Soit tu instrumentes cet objet comme on a dit avec CATAddRef/CATRelease, soit tu mets en œuvre une  methodologie directe
En programmant dans le constructeur (avec les memes problemes non bloquants de carte d'identite)

CreateCGMDummyObject((void*)this)
Et dans le destructeur
DeleteCGMDummyObject((void*)this) ;


Comme je l'ai fait dans CATTopData via un declaratif de debug dont tu peux ici t'affranchir 


S'il reste un CATBaseUnknown_var  non detruit, il y aura alors un CATCGMDummyObject generant un code 77, et c'est celui la qu'il faudra chercher, via les methodologies habituelles avec les outils de Thierry

*/
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByCATMathematics  
int  CATAddRef(CATBaseUnknown*  iReferenced,  void*  iReferencing)  ;  
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByCATMathematics  
int  CATRelease(CATBaseUnknown*  iReferenced,  void*  iReferencing)  ;  
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByCATMathematics  
int  CATModifyRef(CATBaseUnknown*  iReferenced,  void*  iReferencing,  void*  iOldReferencing)  ;  


//---------------------------------------------------------------------------------------------------
// Gestion de l'operateur CGM de niveau 1 en cours
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByCATMathematics  
void CATCGMSetLevel1OperatorId( const  CATString  * iOperatorId) ; 
extern  "C"  ExportedByCATMathematics  
const  CATString  * CATCGMGetLevel1OperatorId() ; 
#endif
