#ifndef CATCallCount_h
#define CATCallCount_h
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATCallCount : Debug class to create calling stacks using call count
//
//=============================================================================
// Usage notes:
//   for debug purpose only: to debug memory leaks problems depending on call count
//
// published in (Les bonnes recettes du père Lochard: 15/02/05) Methodologie de debug pour MLKs et UMRs non triviaux
#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(_CallCount150205,"(Les bonnes recettes du père Lochard: 15/02/05) Methodologie de debug pour MLKs et UMRs non triviaux");
//=============================================================================
//
// sample of use :
// 1 - run a purify tool
// 2 - find memory leak stack trace
// 3 - replace basic allocator by allocator using CATCallCount
// 4 - run purify tool again and use call stack to find call count leading to memory leak
// 5 - run a debugger to stop at memory leak right call count
// 6 - find and correct code error
// 7 - do not leave debugging tool active in code to deliver
// 8 - run your test cases
//
// 1 - run a purify tool
// ---------------------
//   set REPLAYPURIFY=true
//   mkodt -s *Sweep42* -B MEMORYCHECK=stack_depth=20
//
// 2 - find memory leak in standard stack trace with a purify tool
// ---------------------------------------------------------------
//
// 3 - replace basic allocator by allocator using CATCallCount
// --------------------------------------------------------
//   -----------------------------------------------------------
//   here we define an allocator based on CATCallCount
//   ----------------------------------------------
//   #define DebugMLK13954
//   #ifdef DebugMLK13954
//   #include <CATCallCount.h>
//   // allocator iodata
//   struct CreateATOListOfEdges_AllocStruct
//     {
//      int n ;
//      CATEdge** ListEdges ;
//     } ;
//   // allocation method
//   void CreateATOListOfEdges_AllocCATEdge(void* iStruct)
//   {
//    CreateATOListOfEdges_AllocStruct* Struct = (CreateATOListOfEdges_AllocStruct*) iStruct ;
//    if (Struct)
//      {
//       int nb = Struct->n ;
//       if (nb>0)
//          Struct->ListEdges = new CATEdge*[nb] ;
//      }
//   }
//   #endif
//
//   here we replace a basic allocation with new by an allocator based on CATCallCount
//   ------------------------------------------------------------------------------
//   #ifdef DebugMLK13954
//   CreateATOListOfEdges_AllocStruct Struct ;
//   Struct.n = oWireSize ;
//   Struct.ListEdges = NULL ;
//   CATCallCount AllocCounter ;
//   AllocCounter.Main (&CreateATOListOfEdges_AllocCATEdge, &Struct ) ;
//   oEdgeList = Struct.ListEdges ;
//   #else
//   oEdgeList          = new CATEdge * [oWireSize];
//   #endif
//
// 4 - run purify tool again and use call stack to find call count leading to memory leak
// --------------------------------------------------------------------------------------
//    Allocation location
//        ???            [ip=0x580015be]
//        CreateATOListOfEdges_AllocCATEdge(void *) [CreateATOListOfEdges.cpp:80]
//        CATCallCount::Scan_3(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:96]
//        CATCallCount::Scan_0(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:93]
//        CATCallCount::Scan_2(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:95]
//        CATCallCount::Scan(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:92]
//        CATCallCount::Main((*)(void *),void *) [CATCallCount.cpp:37]
//        CreateATOListOfEdges(CATTopData *,CATBody const*,CATEdge * *&,short *&,long *&,long&,BYTE,long,long) [CreateATOListOfEdges.cpp:245]
//        CreateATOCompositeCurve(CATTopData *,CATBody const*,CATEdge * *&,BYTE,long,long) [CreateATOCompositeCurve.cpp:181]
//        CATFrFWireHomogenization::Init(void) [CATFrFWireHomogenization.cpp:1070]
//
//     Here call count 203 can be read  from call Stack  CATCallCount::Scan_2 CATCallCount::Scan_0 CATCallCount::Scan_3
//
// 5 - run a debugger to stop at memory leak right call count
// ----------------------------------------------------------
// a) put a break point in CATCallCount::ModifyTarget and modify ioTarget
//
//   CATCallCount::ModifyTarget(int & 1, int & 0) line 43
//   CATCallCount::Main(void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c960) line 34
//   CreateATOListOfEdges(CATTopData * 0x0012cba0, const CATBody * 0x03c42918 {TIECATBodyCATCXBody m_cRef=2},
//                        CATEdge * * & 0x00000000, short * & 0x00000000, long * & 0x00000000, long & 11, unsigned char 0, long -1, long -1) line 246
//    in this case you've got to set ioTarget to 203
// b) remove break point in ModifyTarget
// c) add a break point in CATCallCount::BreakPoint
// d) debugger will stop when call count is equal to target
//
//   CATCallCount::BreakPoint(int & 203, int & 203) line 49
//   CATCallCount::Scan_3(CATRawCollint & {...}, void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c850) line 96 + 58 bytes
//   CATCallCount::Scan_0(CATRawCollint & {...}, void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c850) line 93 + 223 bytes
//   CATCallCount::Scan_2(CATRawCollint & {...}, void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c850) line 95 + 130 bytes
//   CATCallCount::Scan(CATRawCollint & {...}, void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c850) line 92 + 192 bytes
//   CATCallCount::Main(void (void *)* 0x03f66060 CreateATOListOfEdges_AllocCATEdge(void *), void * 0x0012c850) line 38
//   CreateATOListOfEdges(CATTopData * 0x06049cd8, const CATBody * 0x05fcbe18 {TIECATBodyCATCXBody m_cRef=2},
//                        CATEdge * * & 0x00000000, short * & 0x00000000, long * & 0x00000000, long & 9, unsigned char 0, long -1, long -1) line 246
//   CreateATOCompositeCurve(CATTopData * 0x06049cd8, const CATBody * 0x05fcbe18 {TIECATBodyCATCXBody m_cRef=2},
//                           CATEdge * * & 0x00000000, unsigned char 0, long -1, long -1) line 181 + 41 bytes


// 6 - find and correct code error
//   now you are on right position in call stack to study the error and find
//   the wrong code
//
// 7 - do not leave debugging tool active in code to deliver
//
// 8 - run your test cases
//
// Notes:
// ----
//
//  Lazy way for previous case:
//  --------------------------
//   CATCallCount AllocCounter ;
//   void** VoidEdgeList = AllocCounter.NewArrayOfPointer(oWireSize) ;
//   oEdgeList          = (CATEdge**) VoidEdgeList ;
//
//  Local variables not freed:
//  -------------------------
//  method AllocInt may be used for integer array allocation, or for
//  any memory leak associated to a local variable not freed
//
//  a) integer array case
//     ------------------
//   CATCallCount AllocCounter ;
//   int* Tab = 0 ;
//   int Size = 10 ;
//   AllocCounter.AllocInt(10, &Tab) ;
//   ........
//   if (Tab) delete [] Tab
//
//  b) local variable case
//     -------------------
//  old code with a local variable
//   {
//    CATXXX LocalVariable
//    ...
//   }
//  new code with additional local variable with allocation
//   {
//    CATXXX LocalVariable
//    CATCallCount AllocCounter ;
//    AllocCounter.AllocInt(10) ;
//    ...
//   }
//  if local variables are not freed, a new memory leak will appear
//  with explicit call number in stack; example:  (9th call to MakeWire)
//    Distribution of leaked blocks
//    Allocation location
//        ???            [ip=0x580015be]
//        CATCallCount_AllocInt(void *) [CATCallCount.cpp:68]
//        CATCallCount::Scan_9(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:157]
//        CATCallCount::Scan(CATRawCollint&,(*)(void *),void *) [CATCallCount.cpp:147]
//        CATCallCount::Main((*)(void *),void *) [CATCallCount.cpp:54]
//        CATCallCount::AllocInt(int,int * *) [CATCallCount.cpp:85]
//        CATHybSegmentWire::MakeWire(void) [CATHybSegmentWire.cpp:1071]
//        CATHybSegmentWire::Run(void) [CATHybSegmentWire.cpp:829]
//
//  Special UMR case (unitialized memory read)
//  ------------------------------------------
//
//  let us assume that, in the instruction
//  A = B ; 
//  variable B is not always initialized (a purify or memory check tool has showed that)
// 
//  we simply replace this instruction by an equivalent copy under CATCallCount:
//  CATCallCount Counter ;
//  Counter.Memcpy(&A, &B, sizeof(B)) ;
//
//  then we run the purify tool again
//
//  the outputs will give the calling stack and the call number:
//   example:
//     CATCallCount_Memcpy
//     CATCallCount::Scan_9
//     CATCallCount::Scan_8
//     CATCallCount::Scan_5
//     CATCallCount::Scan_1 
//     CATCallCount::Scan_1
//     CATCallCount::Scan
//     CATCallCount::Main
//     CATCallCount::Memcpy
//     CATMathSystem::ScaleFx
//   here the call stack gives the call number: 11589
//
//   breakpoints in CATCallCount::ModifyTarget to set the target to 11589,
//   and then in CATCallCount::BreakPoint,
//   will lead to the right occurence of the call
//
//   a simple memory check, with no copy, may be done 
//   using CATCallCount::Memcheck instead of CATCallCount::Memcpy 
//=============================================================================
//
// Other debug methods,using debugger hitcount facility:
// ----------------------------------------------------
// published in
LesBonnesRecettesDuPereLochard(_HitCount150408,"(Les bonnes recettes du pere Lochard 15/04/08)debug avec hitcount: Levee d'erreur. Debug en aveugle. Analyse de performances. Recherche de la 1ere difference.");
//
// Appropriate use of breakpoints hitcounts may lead to significative time saving in various debug situations such as
// - search of the initial error leading to the final error raised
// - iterative search of the initial computation leading to the final wrong value at a given address,
// by a stack of breakpoints starting from the final variable address,
// continuing with the previous variable from which it comes,
// until the first variable in which value has been set 
// - rough performance analysis and debug performance probleme through breakpoints on CGM standard allocator catcgmnew(),
// that gives a pretty correct idea of CPU consumption throughout a scenario execution  
// - research of the very first different behavior between 2 executions of same scenario in 2 contexts
// (such as 2 different scales), using breakpoints on catcgmnew() or catcgmrunoperator()
// and many other applications
// ____________________________________________________________________________________________________________________
// 
//    Au cas ou vous n'auriez pas encore remarque et utilise pleinement cet avantage, le nouveau debugger disponible depuis quelques mois dans nos environnements,
//    permet enfin de s'arreter facilement dans un code au numero de passage qui nous interesse grace aux hitcount associes aux points d'arret.
//    Ces hitcounts permettent sur un point d'arret actif, de ne s'arreter qu'a un numero de passage donne, ou a partir d'un numero donne,
// 
//    Ceci a un nombre considerable d'applications pratiques, dont je donne ici seulement quelques exemples. A vous d'etre imaginatifs methodiques et efficaces
// 
//   Nicolas
// 
// ____________________________________________________________________________________________________________________
// 
// Recherche de la levee d'erreur fatale
// -------------------------------------
//   Lorsqu'on s'arrete, par exemple sur un appel a catcgmerror() et que l'on veut derouler a nouveau
//  la sequence d'appel se trouvant dans la callstack, mais simplement pour l'occurrence courant de l' appel,
//  la methodologie est la suivante :
// - mettre un point d'arret a l'instruction qui nous interesse dans une des methodes de la callstack
// - activer une condition sur le hitcount, par exemple " break when hit count is equal to 10000 " de maniere a ne pas s'arreter
// - relancer au debut et s'arreter au catcgmerror(), et la noter la valeur atteinte par le hit count
// -  utiliser cette valeur comme valeur hitcount cible et relancer au debut
// 
// Cas particulier de la recherche de l'erreur initiale ayant entraine l'erreur finale : on peut utiliser en outre le point d'arret catcgmerrorcreation() dont les arguments indiquent le numero de l'erreur en cours, le numero de l'erreur la plus ancienne encore vivante, et un numero cible : Ceci permet par remontees successives de trouver l'erreur initiale conduisant a une erreur finale, meme dans une jungle d'erreurs levees et rattrapees.
// 
// 
// 
//  Debug en aveugle : Application a la recherche de la valeur source aboutissant a une erreur finale
//  ------------------------------------------------------------------------------------------------- 
// 
//  Lorsque dans un calcul, par exemple au moment d'une levee d'erreur, une valeur numerique est invalide,
//  et que l'on veut savoir d'ou elle provient, au gre des recopies successives l'ayant amene
//  dans une variable donnee, on peut utiliser de maniere systematique la surveillance de donnee (breakpoint de type adresse),
//  combinee avec l'utilisation du hitcount
//  (une majorite d'adresses memoires etant situees dans la pile et ayant au cours d'un calcul des usages tres differents).
//  Il suffit, a partir du point d'arret ou l'on constate le probleme sur une variable A,
//  de mettre en place une surveillance de l'adresse &A, avec hitcount,
//  et une fois identifiee l'instruction A=B incriminee,
//  d'iterer avec une surveillance de l'adresse &B,
//  et de continuer de proche en proche. 
// 
//  N.B le nombre maximum de points d'arret de type " data " actifs en meme temps est 5
//  (limitation du debugger due probablement a des limitations hardware).
//  Dans une methodologie iterative de remontee au calcul d'une valeur source transmise de variable en variable,
//  on a besoin de plus de 5 adresses a surveiller, mais d'une seule a la fois.
//  On conservera en pile toutes les surveillances dans la fenetre de points d 'arrets,
//  notamment pour permettre de s'y retrouver si a un moment donne on commet une erreur
//  dans la mise en place de ces points d'arrets (pour revenir a l'iteration precedente),
//  mais on n'activera que le ou les points d 'arret du sommet de la pile.
// (En toute rigueur, si l'on ne commet aucune erreur de manipulation, une seule surveillance active a la fois peut suffire).
// 
// 
//  Une utilisation judicieuse et methodique de ces points d'arret avec hitcount permet
// de remonter de maniere sure et rapide a la source d'un bug ou du calcul d'une valeur numerique,
// sans aucune connaissance du code sur lequel on travaille.
// 
//  Precaution : lors d'une telle session de debug, il est preferable de ne pas, en parallele, modifier et recompiler le code,
//  afin d'eviter des changements d'adresses intempestifs d'une execution a l'autre. 
// 
//  Par ailleurs il n'est pas interdit de prendre quelques notes permettant de reprendre rapidement
// le debug en cours en cas de probleme de debugger
// (boucle CPU, abend). Par exemple on pourra noter des numeros de passages dans certaines methodes.
// 
// 
// Analyse de performances
// -----------------------
// Analyse des problemes de performance : un point d'arret dans catcgmnew() (point d'arret associe a l'allocateur standard CGM) avec hitcount
// (par exemple : arret sur les multiples de 1000) donne une idee rapide et assez representative du sequencage des appels,
// la distorsion entre temps CPU et compteur d'allocations etant en general assez faible.
// Autre avantage sur l'analyse par un outil externe dedie du type MIPMIP, elle debouche directement sur le debug dans la meme session
// de la partie de code dans laquelle on passe du temps.
// Application pratique : debug parallele d'un meme scenario s'executant en des temps tres differents a 2 echelles differentes.
// 
// 
// Recherche de la 1ere difference
// -------------------------------
// Le meme catcgmnew() permet de cibler rapidement la 1ere difference de comportement
// entre 2 executions paralleles d'un meme odt a deux echelles differentes.
// Il suffit de jouer sur le hitcount cible et de controler les piles d'appel dans les 2 sessions,
// pour trouver la 1ere difference (par exemple entre appels 5000 et 6000, en travaillant par multiples de 1000,
// puis en raffinant par multiples de 100 a partir de 5000).
// Attention, le debugger presente quelques defauts et la modification simultanee,
// de la valeur hitcount cible et du mode de calcul
// (passage du mode multiple au mode " greater than " par exemple) est buggee, et,
// si elle est bien geree par l'affichage, elle l'est mal par le fonctionnement reel.
// Pour s'en premunir, une possibilite est de travailler toujours en mode multiple,
// avec 1000 d'abord, avec 5000 avec restart pour aller plus vite une fois la plage 5000-6000 ciblee,
// puis avec 100 pour identifier la plage de taille 100, et ainsi de suite.
// 
// La meme methodologie peut etre utilisee avec le point d'arret catcgmrunoperator(), dedie aux Run() sur les operateurs CGM. 
//
//=============================================================================
// 11/02/05 NLD Creation
// 15/02/05 NLD Ajout _IntAlloc et AllocInt()
// 15/02/05 NLD Ajout Malloc()
// 16/02/05 NLD Ajout NewArrayOfPointer()
// 21/03/05 NLD Ajout _Count, GetCount()
// 26/02/08 NLD Ajout Memcpy, Memcheck
// 09/02/09 NLD Insertion de la note methodologique sur debug avec hitcount
// 26/06/09 NLD Possibilite d'utiliser un compteur utilisateur dans Main() 
// 02/12/09 NLD Ajout point d'entree LesBonnesRecettesDuPereLochard pour methodologie
//              de breakpoint conditionnel d'Antoine Cellerier
// 28/04/10 NLD Nomenclature des #define partages: ScanWithDigits est renommee CATCallCountScanWithDigits
// 22/06/12 NLD Ajout macro CATCallCountContainerDeclare() pour easy tracking
// 14/02/19 NLD Possibilité d'utiliser un tag utilisateur      dans Main()
//              - ajout _ForcedTag
//              - ajout SetForcedTag(iForcedTag)
// 18/02/19 NLD Ajout ScanTag()
//=============================================================================
#ifndef NULL 
#define NULL 0
#endif
#include <CATListOfInt.h>
#include <CATMathematics.h>
class ExportedByCATMathematics CATCallCount
{
 public:
      // Par défaut le comptage est interne et intrinsèque,
      // mais on peut le forcer, par exemple pour imposer un tag d'élément comme compteur
      // auquel cas c'est cette valeur qui sera utilisée, sans incrément
      CATCallCount() ;
     ~CATCallCount() ;

 // Definition of a tag for count instead of inside incremental count
 void SetForcedTag       (int   iForcedTag            = 0);

 // Main program
 // if non null iUserCount, *iUserCount is used instead of global static counter, and is increased
 void Main               (void(*ReCall)(void* ioData) = NULL,
                          void* ioDataForCall         = NULL,
                          int * iUserCount            = 0) ;

 // Break point for user to modify target with a debugger
 void ModifyTarget       (int & iCount, int& ioTarget) ;

 // Break point called when iCount equals ioTarget
 void BreakPoint         (int & iCount, int& ioTarget) ;

 // Allocation of an integer array; this array belongs by default to this object
 // and will be deleted by its destructor, unless a non null pointer is given
 // in oTab: the address of the array will be given to the calling program in *oTab
 // and the array will belong to the calling program
 void AllocInt           (int   Nb   ,
                          int** oTab = NULL) ;

 // Allocation of memory using malloc() and malloc standard argument
 // and will be deleted by its destructor, unless a non null pointer is given
 // in oTab: the address of the array will be given to the calling program in *oTab
 // and the array will belong to the calling program
 void* Malloc            (int   Size) ;

 // Allocation of an array of pointers; this array belongs to the calling program
 // and may be casted in an array of any pointer type
 void** NewArrayOfPointer(int Nb) ;
  
 // Get last call count
 int    GetCount         () ;

 // Recopie de memoire
 void   Memcpy           (void* iTo, void* iFrom, int iSize) ;

 // Check de memoire (accede a toute la memoire dont on donne adresse et taille) 
 // (a coupler avec usage de purify/memorycheck/...)
 void   Memcheck         (void* iFrom, int iSize) ;

 private:

 int* _IntAlloc  ;
 int  _Count     ;
 int  _ForcedTag ;
 // calcul de la liste des chiffres de iCount
 void   ComputeDigits(int iCount, CATListOfInt& Digits) ;

 // Methodes de scan avec rateau
 #define CATCallCountScanWithDigits(METHODNAME)\
 void METHODNAME(CATListOfInt& Digits,void(*ReCall)(void* ioData)=NULL,void* ioDataForCall=NULL);
 // Scan d'un numéro d'appel (en partant du chiffre le plus à gauche)
 CATCallCountScanWithDigits(Scan)
 // Scan d'un tag            (en partant du chiffre le plus à gauche)
 CATCallCountScanWithDigits(ScanTag)
 //
 CATCallCountScanWithDigits(Scan_0)
 CATCallCountScanWithDigits(Scan_1)
 CATCallCountScanWithDigits(Scan_2)
 CATCallCountScanWithDigits(Scan_3)
 CATCallCountScanWithDigits(Scan_4)
 CATCallCountScanWithDigits(Scan_5)
 CATCallCountScanWithDigits(Scan_6)
 CATCallCountScanWithDigits(Scan_7)
 CATCallCountScanWithDigits(Scan_8)
 CATCallCountScanWithDigits(Scan_9)
} ;

 // Object container declaration macro for easy object leak tracking
 // ----------------------------------------------------------------
 // This macro may be used when normal existing object deletion instruction is not
 // executed for a given but unknown number of the execution of the corresponding allocation instruction.
 //
 // It is preferable to standard tracking with an allocator based on CATCallCount,
 // if allocation method is complex, with many arguments, or one does not want to
 // write the allocation data and allocation structure required by CATCallCount Main:
 // instead one just uses an allocation macro, in which a witness data will be allocated
 // with CATCallCount, and will have the same cycle life (this same leak) as tracked data
 //
 // 1) Usage for a sample type  SampleType with single deletion instruction
 // 1.a) Existing code
 //    // Object creation, use and deletion
 //      {
 //       SampleType* SampleObject = SampleObjectCreationMethod(SampleObjectCreationArgumentList);
 //       .... following code using SampleObject
 //       delete SampleObject;
 //      }
 // 1.b) Debug code
 //    CATCallCountContainerDeclare(SampleType);
 //    // Object creation, storage in container, use and deletion
 //      {
 //       SampleType* SampleObject = SampleObjectCreationMethod(SampleObjectCreationArgumentList);
 //       CATCallCountContainerSampleType SampleObjectContainer(SampleObject);
 //       .... following code using SampleObject
 //       // (Sample Object will be deleted at SampleObjectContainer deletion
 //      }
 //
 // 2) Usage for a sample type SampleType with multiple single deletion instructions
 // 2.a) Existing code
 //    // Object creation, use and deletion
 //      {
 //       SampleType* SampleObject = SampleObjectCreationMethod(SampleObjectCreationArgumentList);
 //       .... following code using SampleObject
 //       if ()
 //         {
 //          delete SampleObject; // 1st occurence of deletion code
 //         }
 //       if ()
 //         {
 //          delete SampleObject; // 2nd occurence of deletion code
 //         }
 //      }
 // 2.b) Debug code
 //    CATCallCountContainerDeclare(SampleType);
 //    // Object creation, storage in container, use and deletion
 //      {
 //       SampleType* SampleObject = SampleObjectCreationMethod(SampleObjectCreationArgumentList);
 //       CATCallCountContainerSampleType SampleObjectContainer = new CATCallCountContainerSampleType(SampleObject);
 //       .... following code using SampleObject
 //       if ()
 //         {
 //          delete SampleObjectContainer; // 1st occurence of deletion code
 //         }
 //       if ()
 //         {
 //          delete SampleObjectContainer; // 2nd occurence of deletion code
 //         }
 //      }
//=============================================================================


 #define CATCallCountContainerDeclare(TYPE)\
 class CATCallCountContainer##TYPE                               \
   {                                                             \
    public:                                                      \
    ##TYPE* _P;                                                  \
    int*    _Witness;                                            \
    CATCallCountContainer##TYPE(##TYPE* iP)                      \
      {                                                          \
       _P = iP;                                                  \
       CATCallCount Counter;                                     \
       Counter.AllocInt(1, &_Witness);                           \
      }                                                          \
    ~CATCallCountContainer##TYPE()                               \
      {                                                          \
       if (_P) delete _P;                                        \
       if (_Witness)                                             \
          delete [] _Witness;                                    \
       _Witness = NULL;                                          \
      }                                                          \
   };

//=============================================================================
LesBonnesRecettesDuPereLochard(_BreakConditionUsingCallStack021209,"(Les bonnes recettes du père Lochard: 02/12/09) La methode a Antoine pour arret conditionne par la presence d'une methode dans la CallStack");
//=============================================================================
/*

Comment conditionner un point d'arret de manière fine (Antoine Cellerier 01/12/09)
----------------------------------------------------------------------------------
Il faut tout d'abord créer un module VB (ALT-F11) contenant le code suivant (j'ai choisi de l'appeler Debug dans MyMacros) :

Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports System.Diagnostics

Public Module Debug
    Sub ConditionnalBreakpoint()
        'Calling DTE.Debugger.Go() is forbidden in breakpoint actions. The following workaround is new in visual studio 2008
        Dim dbg As Debugger3 = DTE.Debugger
        If HasMethodInCallStack("CATMassProperties1D") Then
            dbg.ForceContinue = False
        Else
            dbg.ForceContinue = True
        End If
    End Sub

    Function HasMethodInCallStack(ByVal name As String) As Boolean
        HasMethodInCallStack = False
        'Dim commandWin As EnvDTE.CommandWindow = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindCommandWindow).Object
        Dim frame As EnvDTE.StackFrame
        For Each frame In DTE.Debugger.CurrentThread.StackFrames
            'commandWin.OutputString(frame.FunctionName + vbCrLf)
            If InStr(frame.FunctionName, name) > 0 Then
                HasMethodInCallStack = True
            End If
        Next
    End Function
End Module

Placez ensuite votre point d'arrêt (par exemple dans catcgmthrow()) et demandez d'exécuter la macro Macros.MyMacros.Debug.ConditionnalBreakpoint
quand il est atteint (When hit). Si CATMassProperties1D est dans la call stack, l'exécution sera interrompue.

Il reste encore quelques détails à peaufiner mais c'est déjà pas mal :

Au passage, si vous avez des questions au sujet des outils Microsoft, je vous conseille d'ailleurs de contacter le correspondant Microsoft Gilles Guimard.
Il est très réactif.

Enjoy,

Antoine Cellerier

*/
//=============================================================================
#endif
