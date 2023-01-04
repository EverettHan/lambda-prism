/* -*-c++-*- */
#ifndef catcxbreakpoints_H_
#define catcxbreakpoints_H_
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  INTERNAL USE ONLY
// * @quickReview 666 13:04:01  2013 Week15
//  / Assembly Design Scalability / Functions =(Product Filtering-Import CCP)  / Customer = Toyota + Exchanges / Modeler CGM
//============================================================================
//     2001 TCX Creation
// 11/07/03 NLD Ajout catcgmerror() catcgmflush()
// 04/12/03 NLD Ajout catcxtagcreate() catcxtagremove()
// 04/12/03 NLD Ajout catcxtags() et modification signature catcxtag()
// 12/10/04 NLD Ajout catcgmnull()
// 17/11/05 NLD Ajout catcxlogalloc()
// 15/06/06 NLD Ajout catcxremoved()
// 28/07/06 NLD Ajout catcgmerrortarget() et catcgmerrorreached()
// 27/11/06 NLD Ajout catcxtagrefnum() et catcxtagrefnumtarget()
// 10/01/07 NLD Ajout catcxusejournaltag() et catcxusejournaltags()
// 19/06/07 NLD Ajout catcgmerrortrack() et catcgmerrortracked()
// 31/07/07 NLD Ajout de catcgmrunoperator()
// 25/10/07 NLD Ajout de catcxusetagoneshot()
// 30/10/07 NLD catcxtag() catcxtagcreate() catcxtagremove() catcxtagremoved() prennent le tag en argument
// 11/12/07 NLD Ajout de catcxnew() catcxusenew()  catcxnewtofollow()
// 09/04/08 NLD Ajout du catcgmerrordebug() (avec argument)
// 25/11/08 NLD Macro de reperage des branleurs
// 26/11/08 NLD Ajout catcgmerrordebugoneshotormore() pour plus de commodite que catcgmerrordebug()
// 10/02/09 TCX Ajout catcgmstream / IR A0651683 : Correction PCS CPU LifeCycle avec big # CATGeoFactory
// 24/02/09 NLD Ajout catcgmerrordebugoneshotormoremacro()
// 15/10/09 NLD Ajout catcxslownoslowoneshot()
// 24/11/09 NLD Ajout catcxolk() et catcxolkcorrected()
// 25/11/09 NLD Ajout catcxolkelem()
// 23/09/10 NLD Ajout catcgmcatchsecured()
// 06/10/10 NLD Ajout catcgmcatchunsecured() et catcgmcatch()
// 17/10/11 TCX Recherche de cas particuliers et pathologies
//                 catcgmmultirun() operateur a deploiement multi-Run() 
//                 catcgmoperatorid() operateur IsRecordable sans identification nomme GetOperatorId()
//                 catcgmnotyetdefined() coverage impact about lack of knowledge on operatorid 
// 20/04/16 NLD Smart indent
//              Ajout _FreeCATICGMObjectTagDecoder et _FreeCATICGMObjectTagDecoderR22
//              Ajout catcxdecodetag()
// 25/05/16 NLD Ajout catcxjournalcheckko()
// 15/02/19 NLD Ajout catcxcurtag()
// 08/03/21 NLD Ajout catcgmforcesafeIPR()
//============================================================================
#include "CATMathematics.h" 
#include "CATDataType.h" 
#include <string.h>

class CATCGMOperator;
class CATUnicodeString;

//============================================================================
// Macros
//============================================================================
#define CasseToiPovCon(TEXTE) // No Operation. NLD251108

// Appel unique de catcgmerror() a un endroit du code, sauf si au debugger
// l'utilisateur demande de s'arreter a chaque fois, par modification de l'argument
// N.B la variable statique appartiendra a l'appelant
// N.B usage unique dans une meme methode
#define catcgmerrordebugoneshotormoremacro()                              \
{static int __alwaysstop______modifiableunderdebugger=0;                  \
 catcgmerrordebugoneshotormore(__alwaysstop______modifiableunderdebugger);}

//----------------------------------------------------------
// dummy global function to ease breakpoint in DEBUG mode :
//----------------------------------------------------------

extern "C" ExportedByCATMathematics
void  catcgmnull             ();  // BreakPoint de creation d'erreur de pointeur nul dans code CGM


extern "C" ExportedByCATMathematics
void  catcgmerror            ();  // BreakPoint de creation d'exception dans code CGM


//                                // BreakPoint de creation d'exception dans code CGM
extern "C" ExportedByCATMathematics
void  catcgmerrordebug       (     int               & ioDoNotStopHereAnymore_____modifiableunderdebugger);

// l'appelant doit initialiser la valeur statique passee en argument a 0
// au debugger: on peut mettre la valeur a 1 pour continuer a s'arreter apres le 1er passage
// sinon en interne on met la valeur a -1 au 1er passage pour ne plus s'arreter
//                                // BreakPoint de creation d'une erreur
extern "C" ExportedByCATMathematics
void  catcgmerrordebugoneshotormore(int              & ioAlwaysStop_____modifiableunderdebugger);

// autre methode de track d'erreur activable par software
// pour detecter les appels a catcgmerror() 
// dans une plage entre catcgmerrortrack(1) et catcgmerrortrack(0)
// on met un point d'arret dans catcgmerrortracked()
extern "C" ExportedByCATMathematics
void  catcgmerrortrack       (      int                iactivetrack) ;

extern "C" ExportedByCATMathematics
void  catcgmerrortracked     () ;

//   catcgmerrortarget() pour modification de la cible
//   catcgmerrorreached() pour atteinte de la cible
//                                // modification de la cible au debugger
extern "C" ExportedByCATMathematics
void  catcgmerrortarget      (      int              & ioNbErrorTarget);

//                                // atteinte de la cible
extern "C" ExportedByCATMathematics
void  catcgmerrorreached     (      int              & NbError        );

extern "C" ExportedByCATMathematics
void  catcgmthrow            ();  // BreakPoint de Levee d'exception dans code CGM

extern "C" ExportedByCATMathematics
int   catcgmthrow_number     ();  // number of catcgmthrow() ... 

extern "C" ExportedByCATMathematics
void  catcgmflush            ();  // BreakPoint de destruction d'exception dans code CGM

extern "C" ExportedByCATMathematics
void  catcgmcatchunsecured   ();  // BreakPoint de catch non securise (par CATCatch ou CATCatchOthers) dans code CGM

extern "C" ExportedByCATMathematics
void  catcgmcatchsecured     ();  // BreakPoint de catch securise (par CATCatchSecured ou CATCatchOthersSecured) dans code CGM

extern "C" ExportedByCATMathematics
void  catcgmcatch            ();  // BreakPoint de catch dans code CGM

//
extern "C" ExportedByCATMathematics
short catcgmload             ();  // Breakpoint de chargement de Shared-Lib

extern "C" ExportedByCATMathematics
void  catcxdynamic           ();  // Breakpoint dynamic CGM function loading

//                                // Breakpoint premiere CATGeoFactory V5
extern "C" ExportedByCATMathematics
void  catcgmv5               ();

                                 // appel de CATCGMOperator::RunOperator
extern "C" ExportedByCATMathematics
void  catcgmrunoperator      (      int              & GlobalTraceRun ,    // 0,1,2,3 niveau de trace
                                    int              & CallCount      ,    // numero d'appel de RunOperator
                                    int              & CallCountLevel1,    // numero d'appel de RunOperator de niveau 1
                                    int                Level          ,    // niveau d'appel
                                    int                IsTopo         ) ;  // indique si operateur topologique


//                                // BreakPoint de creation d'un object en fuite CATCX_MEMORY=follow= 
extern "C" ExportedByCATMathematics
void  catcxfollow            ();

//                                // BreakPoint de creation d'un object en fuite CATCX_MEMORY=follow= 
extern "C" ExportedByCATMathematics
void  catcxfollowifequal     (      void            * iTarget         ,
                                    void            * iAddress        );

//                                // BreakPoint Fermeture de la CATCX_FACTORY=numero de CATGeoFactory 
extern "C" ExportedByCATMathematics
void  catcxfactory           ();


//----------------------------------------------------------------------------------
// Geometric element decoder for tag access.                               NLD200416
// may be used for any CATGeometry or CATICGMObject implementation
//----------------------------------------------------------------------------------
// N.B tag decoder debugger recipe for any CATICGMObject:(to be reused in debugger watch window)
//
//                         ___________________________
//                        |                           |
//          R26 64 bits   |  ((short*)   p   ) [32]   |
//                        |                           |
//                         ___________________________
//
//          R22 32 bits      ((short*)   p   ) [12] 
//
//----------------------------------------------------------------------------------
struct CATICGMObjectR26TagDecoder
  {
   short _dummy [32];
   short _tag; // R26, et adressage 64 bits
  };

// for old implementation
struct CATICGMObjectR22TagDecoder
  {
   short _dummy [12];
   short _tag; // special R22, et adressage 32 bits
  };

//                                // free address. Never used. May be set anytime for debug to any geometric element address
extern  ExportedByCATMathematics
CATICGMObjectR26TagDecoder* _FreeCATICGMObjectTagDecoder;

//                                // free address. Never used. May be set anytime for debug to any geometric element address  (R22 32 bits version)
extern ExportedByCATMathematics
CATICGMObjectR22TagDecoder* _FreeCATICGMObjectTagDecoderR22;

//                                // BreakPoint for tag decoding
extern "C" ExportedByCATMathematics
int   catcxdecodetag         (      CATICGMObjectR26TagDecoder*& iElem   , // may be modified under debugger
                                    CATICGMObjectR22TagDecoder*& iOldElem);// may be modified under debugger (same but for 32bits old version)

//                                // BreakPoint AddRef/Release de CATCGMFollowTag=...
extern "C" ExportedByCATMathematics
void  catcxtag               (      CATULONG32         tag);

//                                // BreakPoint Creation de CATCGMFollowTag=...
extern "C" ExportedByCATMathematics
void  catcxtagcreate         (      CATULONG32         tag);

//                                // BreakPoint Remove (effectif: plus de reference) de CATCGMFollowTag=...
extern "C" ExportedByCATMathematics
void  catcxtagremove         (      CATULONG32         tag);

//                                // BreakPoint pour marquage removed de CATCGMFollowTag=...
extern "C" ExportedByCATMathematics
void  catcxtagremoved        (      CATULONG32         tag);

//                                // Rend le tag en cours (dernier créé) (sous toutes reserves de validité)  NLD150219
extern "C" ExportedByCATMathematics
CATULONG32 catcxcurtag       ();

// ce point d'arret permet d'activer dynamiquement le suivi d'un seul tag
// a la difference de catcxusetag() on y passe une seule fois en debut de session
// apres modification de ioTagToFollow activer le point d'arret sur catcxtag()
// voir catcxusetags pour suivre une plage de tags
//                                // BreakPoint pour activer catcxtag
extern "C" ExportedByCATMathematics
void  catcxusetagoneshot     (      CATULONG32       & ioTagToFollow,
                              const CATULONG32         curTag       );

//                                // BreakPoint de definition du tag a suivre
extern "C" ExportedByCATMathematics
void  catcxusetag            (      CATULONG32       & ioTagToFollow,
                              const CATULONG32         curTag       );

//                                // BreakPoint de definition de plage de tag a suivre
extern "C" ExportedByCATMathematics
void  catcxusetags(                 CATULONG32       & ioTagMin     ,
                                    CATULONG32       & ioTagMax     ,
                              const CATULONG32         curTag       );

//                                // BreakPoint sur numero de reference suivi sur tag suivi par CATCGMFollowTag=!
extern "C" ExportedByCATMathematics void  catcxtagrefnum         ();

//                                // BreakPoint pour modif ref suivie sur tag suivi!
extern "C" ExportedByCATMathematics
void  catcxtagrefnumtarget   (      int              & iRefNumTarget      ,
                                    int                iCurrentRefNum     ,
                                    int              & iActiveMainTrace   ,
                                    int              & iActiveCompactTrace);


extern "C" ExportedByCATMathematics
void  catcxtaglost           ();  // BreakPoint Acces a un tag d'objet inexistant

//                                // BreakPoint pour activer catcxjournaltag
extern "C" ExportedByCATMathematics
void  catcxusejournaltag     (      CATULONG32       & ioTagToFollow,
                              const CATULONG32         curTag       ) ;

//                                // BreakPoint de definition de plage de journal tag a suivre
extern "C" ExportedByCATMathematics
void  catcxusejournaltags    (      CATULONG32       & ioTagMin     ,
                                    CATULONG32       & ioTagMax     ,
                              const CATULONG32         curTag       );

//                                // BreakPoint CATCGMJournalItem::CATCGMJournalItem(...) de CATCGMJournalFollowTag=...
extern "C" ExportedByCATMathematics
void  catcxjournaltag        ();

//                                // BreakPoint check journal
extern "C" ExportedByCATMathematics
void  catcxjournalcheckko    ();



extern "C" ExportedByCATMathematics
void  catcxko                ();  // BreakPoint des Erreurs severes du CHECKER

extern "C" ExportedByCATMathematics
void  catcxkowarn            ();  // BreakPoint des Erreurs PotDeVin du CHECKER

extern "C" ExportedByCATMathematics
void  catcxkos               ();  // BreakPoint Apres Bilan affichage et detection d'anomalie du CHECKER

extern "C" ExportedByCATMathematics
void  catcxfreeze            ();  // Levee d'exeption Anomalie de Gestion du Freeze

extern "C" ExportedByCATMathematics
void  catcxsubd              ();  // Incoherence Topologique (CX-Subd des liens Pose-Sur)


extern "C" ExportedByCATMathematics
void  catcxslow              ();  // Poor performance due to inadequate Usage (no reverse links)

// gestion du comportement de catcxslow avec systeme d'inhibition one shot
//  catcxslownoslowoneshot(1) inhibe pour l'appel suivant et rend la valeur courante
//  catcxslownoslowoneshot(0) rend la valeur courante et desactive l'inhibition
extern "C" ExportedByCATMathematics
int   catcxslownoslowoneshot (      int                isettonoslowoneshot = 0) ;

extern "C" ExportedByCATMathematics
void  catcxio                ();  // BreakPoint for input/Output on Disk

extern "C" ExportedByCATMathematics
void  catcxactivate          (      int                NbTopo);   // BreakPoint generation des liens inverses Bodys

extern "C" ExportedByCATMathematics
void  catcxinittransactionbit();  // BreakPoint InitTransactionBit

extern "C" ExportedByCATMathematics
void  catcxbadnew();              // Detection debranchement surcharge new/delete suite mauvaise impl

// catcxusenew: ce point d'arret permet de definir l'adresse de l'allocation a reperer
// catcxnew:    ce point d'arret permet de reperer l'allocation suivie grace a catcxusenew
// catcxnewtofollow() est une methode destinee au programmeur et rend l'adresse suivie
extern "C" ExportedByCATMathematics
void  catcxusenew            (      void            *& ioTarget) ;

extern "C" ExportedByCATMathematics
void* catcxnewtofollow       () ;

extern "C" ExportedByCATMathematics
void  catcxnew               (      void            *  iAddress) ;

//                                // PCS Follow-UP against SCALABILITY of Scan ListMembers to BE AVOIDED (Not structured)
//                                // PCS Container Scan
extern "C" ExportedByCATMathematics
void  catcxlistmembers       (      int                iObjectsCount);


extern "C" ExportedByCATMathematics
void  catcxdel               ();  // BreakPoint de detection d'anomalie Release() CATCX_MEMORY=usecount

extern "C" ExportedByCATMathematics
void  catcxquota             ();  // BreakPoint de depassement de Quota Memoire CATCX_MEMORY=quota=

extern "C" ExportedByCATMathematics
void  catcxcheckcleantag     ();  // BreakPoint CATCGMCleaner::ApplyRuleToOneCATGeometricTypeEntry(...) de CATCheckCleanFollowTag=...

extern "C" ExportedByCATMathematics
void  catcxsoftdel           ();

//                                // Break point de comptage/reperage des allocations
extern "C" ExportedByCATMathematics
void  catcxlogalloc          (      int              & iGlobalNbPoolAllocs);

extern "C" ExportedByCATMathematics
int   _CATMathStream;             // BreakPoint declenchement Statistics CATMathStream=59

extern "C" ExportedByCATMathematics
void  _catmathstream         (const size_t             iEndPosition,
                              const size_t             ilength     );

extern "C" ExportedByCATMathematics
void  catmathstream();  

extern "C" ExportedByCATMathematics
void  catcgmnotyetdefined    (      CATCGMOperator  *  iOp         );

extern "C" ExportedByCATMathematics
void  catcgmoperatorid       (      CATCGMOperator  *  iOp         );

extern "C" ExportedByCATMathematics
void  catcgmmultirun         (const CATUnicodeString & iNameId     ,
                                    CATCGMOperator  *  iOp         ,
                              const int                iNumberOfRun);
 

//                                // BreakPoint Statistics CATCGAMeasure=Home=E:\tmp
extern "C" ExportedByCATMathematics
void  catcgmstream           (      CATULONG32         iHistory    );

//                                // BreakPoint Statistics CATCGAMeasure=Home=E:\tmp
extern "C" ExportedByCATMathematics
void  catcgmlog              (      CATULONG32         iHistory    );

// Gestion des OLKs
extern "C" ExportedByCATMathematics
void  catcxolk               ();  // olk (model object leak) sur ce cas de test

// Gestion des Tolerance access errors
extern "C" ExportedByCATMathematics
void  catcxtol               ();  // Tolerance access error

//                                // tracking closed NULL CGM Level (non evolutive) input specification
extern "C" ExportedByCATMathematics
void  catcxclosedlevel       ();  // tracking closed NULL CGM Level 

//                                // tracking interrupt thrown
extern "C" ExportedByCATMathematics
void  catcgminterrupt        ();

//                                // tracking catcgameasure  init exit
extern "C" ExportedByCATMathematics
void  catcgameasure_init     ();

extern "C" ExportedByCATMathematics
void  catcgameasure_exit     ();
 
//                                // tracking interrupt thrown????
extern "C" ExportedByCATMathematics
void  catcgmfollowtag        ();

//                                // forced safe IPR for CallStack generation / follow up / fix
//                                // Please make a full investigation on the test case and CallStack with invalid delete leading here
//                                // returns 0 when invalid pointer detected
extern "C" ExportedByCATMathematics
int   catcgmforcesafeIPR(void *ptr             = NULL,  // always use default value NULL for IPR generation
                         int   OnlyUnderPurify = 1);
 



#endif
