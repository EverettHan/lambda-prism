#ifndef CATCGMTransaction_h
#define CATCGMTransaction_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
/*
      CATCGMTransactionBegin(fastQuick,CatQuickFindObjectFromTag) 
      {
          // ... Nombreuses regenerations de liens symboliques
          //  par l'interface CATINamingContext (methode GetObject_B)
          //
      }
      CATCGMTransactionEnd(fastQuick);
*/
//
//==========================================================================
/**
 *        Identify a specific transaction 
 * allowing underneath (deep level) treatment to incorporate
 * specific temporary Data Structure more appropriate 
 * to a specific application
 *
 *  For Instance, a faster CATGeoFactory->FindObjectFromTag()
 * for the dynamic drafting application ...
 *  
 *        In Case of multi-threaded application,
 * Call-back for end of a particuliar transaction is done
 * at the end of the last alive transaction
 * (transmition of callback can be done ...)
 */
//=============================================================================
//   /03/03 HCN CatCGMFactoryTransaction_OpenLight et
//              CatCGMFactoryTransaction_OpenDual Pour le Light BRep Mode
//   /11/03 HCN CatCGMDatumiserCGMCleaner
//   /12/03 HCN CatCGMOperatorRunTransaction
//   /03/04 HCN CatCGMUnStreamCreateObject
//   /02/08 TCX CatCGMFilterBreakpointsByTagAndType (Tessellation Face analysis)
//              analsysis filter by specified Face
//   /05/09 TCX Caracterisation des operations de Controle Check et Replay
//              Cf CatCGMCheckingTools pour filtrage des operations nominales
// 05/10/10 NLD Ajout macro CATCGMTransactionCatchSecured utilisant CATCatchSecured
// 30/01/12 NLD Remplacement de CATCatchSecured par CATCatchAlwaysSecured()
//              (en fait il aurait fallu creer aussi
//               CATCGMTransactionBeginSecured()/CATCGMTransactionEndSecured())
// 13/02/18 FDS Perfo : Remplacement de la données membre "_Timer" par un pointeur ( utilisation rare )
// 13/01/22 NLD Smart indent
//=============================================================================
#include "CATIACGMLevel.h"

#include "ExportedByCATMathStream.h"
#include "CATGeometricModelTransaction.h"
#include "CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CATErrorMacrosCGM.h" // pour CATCatchSecured
#include "CATCGMNewArray.h"

#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "CATechTimer.h"
#include "CATCGMInterruptDef.h"

class CATExtCGMReplay;

//------------------------------------------------------------------
// Type de la fonction d'interruption
//------------------------------------------------------------------
//typedef CATBoolean (*CATCGMInterruptFunction)(int iProgressValue, int iProgressRange);

//------------------------------------------------------------------
// Liste des types de Transactions acceptees
//------------------------------------------------------------------
typedef unsigned int CATCGMKindOfTransaction;

//#define CatQuickFindObjectFromTag           0x00000001   //Is now really defined in CATGeometricModelTransaction.h
#define CatTouchedGarbageCollector            0x00000002
#define CatCGMObjectLeaks                     0x00000004
#define CatCGMReverseTopology                 0x00000008
#define CatCGMUnstreamByInjection             0x00000010
#define CatCGMUnStreamCreateObject            0x00000020
#define CatCGMDelayingEquationsLifeCycle      0x00000040
#define CatCGMFactoryTransaction              0x00000080
#define CatCGMMultiCopyPasteManagement        0x00000100
#define CatCGMFactoryTransaction_Open         0x00000200
#define CatCGMFactoryTransaction_Save         0x00000400
#define CatCGMFactoryTransaction_Close        0x00000800
#define CatCGMNoDualLoadingOnLostTag          0x00001000
#define CatCGMDatumiserCGMCleaner             0x00002000
#define CatCGMOperatorRunTransaction          0x00004000
#define CatCGMFilterBreakpointsByTagAndType   0x00008000
#define CatCGMSelectSerialize                 0x00010000
#define CatCGMCartography                     0x00020000
#define CatCGMCheckingTools                   0x00040000 // To skip Check Input/Output of CGMReplay, CheckUp of completion for AfterRun
#define CatCGMReplayRun                       0x00080000 // To Add  CGMReplay -> Run()
#define CatCGMUpwardCompatibility             0x00100000 // To Add  CGMReplay -> Run()
#define CatCGMUnstreamMutator                 0x00200000 // 
#define CatCGMZornEdgeCurveEvaluator          0x00400000
#define CatCGMCacheForTopGN                   0x00800000
 
//------------------------------------------------------------------
// INTERNAL-SERVER usage
//------------------------------------------------------------------
#define CATCGMTransactionsStaticSize       8

#define CATCGMTransactionAtEndStaticSize   2
typedef void (*CATCGMTransactionAtEnd) ()  ;

#define CATCGMMaxNumberOfTagAndType        6

//------------------------------------------------------------------
// Identification of a transaction
//------------------------------------------------------------------
class ExportedByCATMathStream CATCGMTransaction : public CATGeometricModelTransaction 
{
public :
  //------------------------------------------------------------------
  // CLIENT : life of one CATCGMTransaction Object identify a transaction
  //------------------------------------------------------------------
  static        CATCGMTransaction     * Create(CATCGMKindOfTransaction purpose, CATBoolean isExclusiveType=FALSE);

  virtual                              ~CATCGMTransaction();
  CATCGMNewClassArrayDeclare;

  //------------------------------------------------------------------
  // INTERNAL : Used to make sure that end of Transaction is done
  // in case of exeption throw with longjmp ..
  //  If reimplemented (avoiding AtEndOfTransaction),
  //  do not forget to first make explicit
  //       this->CATCGMTransaction::Clean()
  //------------------------------------------------------------------
  virtual       void                    Clean();

  //------------------------------------------------------------------
  // SERVER : Identify if a specific Transaction exists
  // if exists, you can solve ambiguite between Older (CATLONG32 time) and Newer (short time)
  //------------------------------------------------------------------
  static INLINE CATCGMTransaction     * Search                           (CATCGMKindOfTransaction purpose    ,
                                                                          CATBoolean              OlderFirst = FALSE);

  //------------------------------------------------------------------
  // SERVER : Specific Treatment can be specify at end of Transaction
  // to make sure some temporay data stucture is cleaned
  //------------------------------------------------------------------
                void                    AtEndOfTransaction               (CATCGMTransactionAtEnd  callback);

  //------------------------------------------------------------------
  // Interrupt function (CallBack)
  // Rem : The set can't be done twice,  except if previous value is NULL
  //------------------------------------------------------------------
                void                    SetInterruptFunction             (CATCGMInterruptFunction ipInterruptFunction);
                CATCGMInterruptFunction GetInterruptFunction             () const;


  //------------------------------------------------------------------
  // SERVER : SetUp    CatCGMFilterBreakpointsByTagAndType
  //   CATGeometricType  iCATGeometricType  Cf  GeometricObjects\PublicInterfaces\CATGeometryType.h
  //   CATULONG32        iTag               Cf  GeometricObjects\PublicInterfaces\CATICGMObject.h
  //------------------------------------------------------------------
  static        void                     SetFilterBreakpointsByTagAndType(int                     iNumberOfFilter    ,
                                                                          unsigned int            iCATGeometricType[],
                                                                          CATULONG32              iTag[]             );

  //------------------------------------------------------------------
  // CLIENT : Usage beakpoints  IsBreakpointFilteredByTagAndType
  //------------------------------------------------------------------
  static INLINE CATBoolean               IsBreakpointFilteredByTagAndType();

  //------------------------------------------------------------------
  // INTERNAL :  for delegation on particular transaction
  //------------------------------------------------------------------
  virtual       CATBoolean               IsTransactionFilteredByTagAndType();

  //------------------------------------------------------------------
  // INTERNAL :  for CATechCheckPoint Logging
  //------------------------------------------------------------------
                void                     _GetStatitics                   (double                & oCpu              ,
                                                                          CATULONG32            & oElapsed          ,
                                                                          double                & oWorkingSetDelta  ) const;
  INLINE        CATCGMKindOfTransaction  GetPurpose                      () const;

  //------------------------------------------------------------------
  // Analysis
  //------------------------------------------------------------------
  INLINE        void                     GetTagAndType                   (unsigned int          & oCATGeometricType ,
                                                                          CATULONG32            & oTag              ) const;


  //------------------------------------------------------------------
  // To be used with 
  //     CATCGMTransaction *CurrentTransaction = CATCGMTransaction::Search(CatCGMCheckingTools)
  //     CurrentTransaction->CATExtCGMReplay()
  //   Integration is made under CATExtCGMReplay methods
  //------------------------------------------------------------------
  INLINE        CATExtCGMReplay        * GetCATExtCGMReplay              () const;
  INLINE        void                     SetCATExtCGMReplay              (CATExtCGMReplay       * iReplay           );
 

protected:

  //------------------------------------------------------------------
  // SERVER : Identify if a specific Transaction is active,
  // if exists, always return the older transaction (first declared)
  //------------------------------------------------------------------
  static        CATCGMTransaction      * TrueSearch                      (CATCGMKindOfTransaction purpose           ,
                                                                          CATBoolean              OlderFirst        );

  //------------------------------------------------------------------
  // INTERNAL : Usage beakpoints  IsBreakpointFilteredByTagAndType
  //------------------------------------------------------------------
  static        CATBoolean               _IsBreakpointFilteredByTagAndType();

  //------------------------------------------------------------------
  // CLIENT : life of one CATCGMTransaction Object identify a transaction
  //------------------------------------------------------------------
                                         CATCGMTransaction               (CATCGMKindOfTransaction purpose           ,
                                                                          CATBoolean              isExclusiveType   = FALSE,
                                                                          unsigned int            iCATGeometricType = 0    ,
                                                                          CATULONG32              iTag              = 0);

  //------------------------------------------------------------------
  // INTERNAL management of all Transactions
  //------------------------------------------------------------------
  static        unsigned int             _AllKindOfTransactions;
  static        int                      _AllocatedTransactions;
  static        int                      _UsedTransactions;
  static        CATCGMTransaction     ** _Transactions;
  static        CATCGMTransaction      * _StaticTransactions[CATCGMTransactionsStaticSize];

  static        void                     ReAllocateTransactions          ();

 
  //------------------------------------------------------------------
  // INTERNAL management of CatCGMFilterBreakpointsByTagAndType
   //------------------------------------------------------------------
  static        CATBoolean               _TagAndType_Filter;
  static        int                      _FilterUsed;
  static        unsigned int             _FilterGeometricType[CATCGMMaxNumberOfTagAndType];
  static        CATULONG32               _FilterTag          [CATCGMMaxNumberOfTagAndType];

  //------------------------------------------------------------------
  // INTERNAL management of current Transaction
  //------------------------------------------------------------------
                int                      _AllocatedAtEnd;
                int                      _UsedAtEnd;
                CATCGMTransactionAtEnd * _AtEnd;
                CATCGMTransactionAtEnd   _StaticAtEnd        [CATCGMTransactionAtEndStaticSize];

                void                     ReAllocateAtEnd();
  
                CATLONG32                _IdTransaction; // Identificateur de Debug
  static        CATLONG32                _NbTransaction;

                CATCGMKindOfTransaction  _Purpose;
#if defined ( CATIAR201 )
                CATechTimer            * _Timer;
#endif
                short                    _IsCleaned;

                void                   * _CATExtCGMReplay;

  // For interrupt managment
                CATCGMInterruptFunction  _pInterruptFunction;

                unsigned int             _CATGeometricType;
                CATULONG32               _Tag;

};


//------------------------------------------------------------------
// CATExtCGMReplay * context of CatCGMCheckingTools transaction
//------------------------------------------------------------------
INLINE CATExtCGMReplay * CATCGMTransaction::GetCATExtCGMReplay() const 
{
   return (CATExtCGMReplay * )_CATExtCGMReplay  ;
}

//------------------------------------------------------------------
INLINE void              CATCGMTransaction::SetCATExtCGMReplay(CATExtCGMReplay * iReplay)
{
   _CATExtCGMReplay = (void *) iReplay ;
}

//------------------------------------------------------------------
// Recherche Optimise d'un Type de transaction
//------------------------------------------------------------------
INLINE CATCGMTransaction *CATCGMTransaction::Search(CATCGMKindOfTransaction purpose, CATBoolean OlderFirst)
{
   if ( !_UsedTransactions || ! (_AllKindOfTransactions & purpose) ) return NULL;
   return TrueSearch(purpose,OlderFirst);
}

//------------------------------------------------------------------
// Controle de filtrage par une objet de Type et Tag specifie 
//------------------------------------------------------------------
INLINE  CATBoolean CATCGMTransaction::IsBreakpointFilteredByTagAndType()
{
   if ( !_UsedTransactions ) return _TagAndType_Filter ? TRUE : FALSE;
   if ( ! (_AllKindOfTransactions & CatCGMFilterBreakpointsByTagAndType) ) return _TagAndType_Filter ? TRUE : FALSE;
   return _IsBreakpointFilteredByTagAndType();
}

//------------------------------------------------------------------
// Get
//------------------------------------------------------------------
INLINE  CATCGMKindOfTransaction CATCGMTransaction::GetPurpose() const
{
   return _Purpose;
}

//------------------------------------------------------------------
// Analysis
//------------------------------------------------------------------
INLINE void CATCGMTransaction::GetTagAndType(unsigned int & oCATGeometricType, CATULONG32 & oTag) const
{
   oCATGeometricType = _CATGeometricType;  oTag = _Tag;
}

//------------------------------------------------------------------
// Macros
//------------------------------------------------------------------

#define CATCGMTransactionBegin(mytransaction,KindOfTransaction)                                   \
   CATCGMTransaction *volatile mytransaction = CATCGMTransaction::Create(KindOfTransaction);      \
   CATTry                                                                                         \
   {


#define CATCGMTransactionCatch(mytransaction,error)                                               \
      if ( mytransaction ) { mytransaction->Clean(); delete mytransaction; mytransaction = NULL;} \
   }                                                                                              \
   CATCatch(CATError, error)                                                                      \
   {                                                                                              \
      if ( mytransaction ) { mytransaction->Clean(); delete mytransaction; mytransaction = NULL;}

#define CATCGMTransactionCatchSecured(mytransaction,error)                                        \
      if ( mytransaction ) { mytransaction->Clean(); delete mytransaction; mytransaction = NULL;} \
   }                                                                                              \
   CATCatchAlwaysSecured(CATError, error)                                                         \
   {                                                                                              \
      if ( mytransaction ) { mytransaction->Clean(); delete mytransaction; mytransaction = NULL;}


#define CATCGMTransactionEndTry(mytransaction)                                                    \
      CATRethrow;                                                                                 \
   }                                                                                              \
   CATEndTry


#define CATCGMTransactionEndTryWithoutRethrow(mytransaction)                                      \
   }                                                                                              \
   CATEndTry


#define CATCGMTransactionEndFlush(mytransaction,error)                                            \
      Flush(error);                                                                               \
   }                                                                                              \
   CATEndTry 


#define CATCGMTransactionEnd(mytransaction)                                                       \
  CATCGMTransactionCatch(mytransaction,DummyError##mytransaction)                                 \
  CATCGMTransactionEndTry(mytransaction)

#endif

