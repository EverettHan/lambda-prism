/* -*-c++-*- */
#ifndef CATCGMObject_H
#define CATCGMObject_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// CATCGMObject : CGM (CXR2) Mother Class of ANY Geometric&Topological Objects 
//                 in the CXRN Model
//=============================================================================
// Jan.  97 RAD Creation                                                RAD/EBN
// Oct.  97 ILY Add Clone and methods of the CATTransfoManager
// Avr.  98 TCX
// Oct.  01 HCN. Stockage de la vivicite
// Jun.  05 FDN 2 nouveaux arguments (optionnels) pour ReleaseReference
// Jul.  09 VUC Suppression du StreamCompact & OrderedStream
// Jun.  12 FDS Perfo : inline constructor
// Nov.  14 DPS Prepare the modeler extension to polyhedral objects
// July. 15 DPS Add safe cast method into new derived class CATCGMTopologyImpl
// 14/05/21 NLD Smart indent
//=============================================================================

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATCGMFusion.h"

#include "CATCGMFusion.h"
#include "CATDataType.h"

#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATNullPointerThrow.h"
#include "CATThrowForNullPointer.h"
#include "CATCGMBuildDebug.h"
#include "CATBoolean.h"
#include "CATErrorDef.h" // HRESULT
#include "CATMathConstant.h" // CATAngle

#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATCGMAttribute.h"
#include "CATICGMObject.h"
#include "CATGeometryType.h"
#include "CATGeometryCGMType.h"
#include "CATCGMCompactObject.h"
#include "CATCGMBOAObject.h"
#include "CATICGMUnknown.h"
#include "CATCGMMacs.h"
#include "CATCGMDynObject.h"
#include "CATCGMStreamVersion.h"
#include "CATCGMEventType.h"
#include "CATCGMLimitsManagement.h"
#include "CATMathInline.h"

#include "ExportedByCATCGMFusion.h"
#include "CATCGMLimitsManagement.h"

#include "CATMathAdvancedBoxType.h"
#include "CATMathAdvancedBox_IsCacheRequest.h"

#include "LimitCompactInfoForIncStr.h"

class CATCGMOutput;
class CATCGMAttribute ;
class CATCGMAttribute ;
class CATCGMAttrId;
class CATCGMContainer ;
class CATCGMStream    ;
class CATCGMVersionDefinition;
class CATGeoFactory;
class CATCloneManager ;
class CATTransfoManager ;
class CATRootContainerCGM;
class CATCX_CHECKUP;
class CATCGMStreamCGMImpl;
class CATCGMAttrReframeDesignLimits;

class CATCXTopology;
class CATCGMTopologyImpl;
class CATSubdOccurence;

class CATBody;

class CATCGMSharpnessData;
class CATICGMUnknown;
class CATCGMSession;
class CATCGMGraph;
class CATCGMQueryManager;

struct CATCGMHeaderExtraBits;

class CATKnotVector;

class CATCGMStreamImpl;
class CATCGMNickName;


#define CPOFSM_Delegation       0x01
#define CPOFSM_TakeIntoAccount  0x02


//------------------------------------------------------------------------------------
// Reserve aux inities sur les problemes de consommations memoires
//------------------------------------------------------------------------------------
#ifdef PLATEFORME_DS64
#define CATCGMViciousPerfHighPtr   ((CATULONGPTR) 0xFFFFFFFFFFFFFFF8)
#define CATCGMViciousPerfLow3Bits  ((CATULONGPTR) 0x0000000000000007)
#else
#define CATCGMViciousPerfHighPtr   ((CATULONGPTR) 0xFFFFFFF8)
#define CATCGMViciousPerfLow3Bits  ((CATULONGPTR) 0x00000007)
#endif


//------------------------------------------------------------------------------------
// Enfin, la Classe de Base d'implementation Geometrique et Topologique
//------------------------------------------------------------------------------------
class ExportedByCATCGMFusion CATCGMObject : public CATCGMFusion
{
private :

  CATCGMDeclareVirtualClass;

public:

          CATCGMObject    ();
  
          CATCGMObject               * CreateOfSameType       ( CATGeoFactory * iFactory) const;

  //------------------------------------------------------------------
  // DumpElem pour obtenir caracteristiques generales et specifiques
  //   Dump a implementer par chaque classe CGA pour les specificites
  //------------------------------------------------------------------
  virtual void                         DumpElem               ( CATCGMOutput& os );
  virtual void                         Dump                   ( CATCGMOutput& os );

  //------------------------------------------------------------------------
  // Gestion mode Explicit/Implicit, ("Visible/Cache", "Public/Fantome",...
  //   Implicit -> introuvable par parcours Public du container
  //            -> pas d'emission d'evenement sur toute manipulation
  //            -> effacement gere en interne
  //------------------------------------------------------------------------
          void                         SetMode                ( CATCGMMode Mode ) ;
          void                         SetExplicit            () ;

  //------------------------------------------------------------------------
  // Gestion des informations dynamiques rarement utilises
  // pour gain de consommation memoire ..
  //------------------------------------------------------------------------
  virtual CATCGMDynObject            * CreateDynObject        ();
  
  virtual short                        DynObjectIsUseless     (); // A implementer mais ne pas appeler
          short                        FreeIfUselessDynObject (); // A utiliser
  
  
  virtual  CATLISTP(CATCGMAttribute) * RetrieveFirstAttribute (CATBoolean iForceAllocation = FALSE) const;
  virtual  void                        FreeAllAttributes      ();

  //------------------------------------------------------------------------
  // Gestion Etat d'avancement de la Construction
  //------------------------------------------------------------------------
  virtual void                         CompletedFreeze        (      CATCGMOperator * iOperator);

  virtual void                         Completed              (      CATBoolean       IsNoMoreModifiable      = FALSE,
                                                               const char             IdentityBuildOperator[] = "",
                                                               const CATTopData     * iData                   = NULL );


  virtual CATBoolean                   HasBeenCompletedAsNoMoreModifiable() const;

          int                          Check                 ();

          void                       * GetImplementCGM       (      CATGeometricType  iTypeReference) const;
          int                          IsImplementCGMRemoved (const CATGeometricType  iTypeReference=CATGeometryType) const;

  virtual void                         UpdateUnstreamExtraBits(CATCGMHeaderExtraBits & ExtraBits);


          CATCGMObject               * GetImplCGM            (const CATICGMObject   * Object) const;

  static INLINE CATCGMObject         * GetSecureImpl         (const CATICGMObject   * Interface,
                                                                    char            * ifile    ,
                                                                    int               iline    ,
                                                                    CATGeometricType  iTypeReference = CATGeometryType);


  INLINE static CATICGMObject        * CATCGMNativeInterfaceImpl(CATICGMObject *itf);

  //------------------------------------------------------
  // Tag : Identificateur persitant relatif au container
  //------------------------------------------------------
  virtual size_t                       GetDynamicMemoryBytes () const;

  //------------------------------------------------------
  // Gestion du Container
  //------------------------------------------------------
          CATGeoFactory              * GetContainer          (      CATBoolean        iThrowOnNullFactory = TRUE,
                                                                    CATCGMMode        iMode               = CatCGMExplicit) const;

          CATPositiveLength            GetFactoryInfiniteValue() const;
  

  //------------------------------------------------------
  // DUMMY    for simple transient rare extension aggregated cache  without shareable attribute and dummy requests without HowTo process 
  //------------------------------------------------------
  /**
  * ExtensionAdd  (for simple transient rare extension aggregated cache  without shareable attribute and dummy requests without HowTo process )
  */
  virtual void                         ExtensionAdd          (      CATCGMExclusive * iExclusive);

#if defined ( CATIACGMR215CAA )
  /** @nodoc (for simple transient extension aggregated cache  without shareable attribute and dummy request without HowTo process )  */
          CATCGMExclusive            * ExtensionSearchByMeta (      void            * iMeta);
  /** @nodoc (for simple transient extension aggregated cache  without shareable attribute and dummy request without HowTo process )  */
  static  CATICGMUnknown             * ExtensionGetCATICGMObject(   CATCGMExclusive * iExclusive);
#endif


  
          void                         SelfDestruction       ();
#if defined ( CATCGMBOAObject )
  // for debug BOA
          void                         CheckAddRef           (ULONG );
          void                         CheckRelease          (ULONG );
          void                         CheckEndOfLife        (ULONG );
#endif

  //-----------------------------------------------------------------------
  //  Surcharge AddRef()/Release() for DEBUG RunTime
  //-----------------------------------------------------------------------
  virtual ULONG __stdcall              CATAddRefFrom         (void *iForDebug, CATBoolean iLockEquation = FALSE);
  virtual ULONG __stdcall              CATReleaseFrom        (void *iForDebug, CATBoolean iLockEquation = FALSE);

   /**
   * @nodoc UseCount
   */
  virtual CATULONG32                   SpecificGetUseCount   (CATCGMUseCountType iUseType) const ;
  virtual CATULONG32                   GetTrueUseCount       () const ;

  //-----------------------------------------------------------------------
  // Pour AddRef/Release propre au framework d'implementation
  //-----------------------------------------------------------------------
          ULONG                        CGMAddRef             (const CATULONG32  increment = 1);
          ULONG                        CGMRelease            (const CATULONG32  decrement = 1);

  //----------------------------------------------------------------------
  // Usage dedie a la Geometrie-Topologie CGA (coherence interne)
  //  a distinguer de la reservation externe/applicative par AddRef/Release
  //    RemoveReference dechainera l'Objet du Container en cas de derniere
  //    reference, contrairement au mode par defaut de ReleaseReference.
  //------------------------------------------------------------------------

        //------------------------------------------------------------------------
        // Gestion de la construction topologique, Vue interne CGA simplifiee
        //------------------------------------------------------------------------
          CATULONG32                   AddReference     ( CATICGMObject * From              ) ;
  virtual CATULONG32                   ReleaseReference ( CATICGMObject * From              ,
                                                          CATBoolean      iRemoveIfPossible = TRUE ,
                                                          CATBoolean    * oRemoved          = 0    ) ;
  INLINE  CATULONG32                   RemoveReference  ( CATICGMObject * From              ) ;
        //--------------------------------------------------------------------------------
        // If Persistent, In Write Persistent, only explicitly persistent Object written  
        //--------------------------------------------------------------------------------
          void                         SetPersistent    (CATLONG32 yes_or_no = 1);

        //--------------------------------------------------------------------------------
        // CXR2 Atelier Management, For implicit element  
        //--------------------------------------------------------------------------------
          void                         SetNCGMVisible   (CATLONG32 yes_or_no = 1);

  //--------------------------------------------------------------------------------
  // Detection des changements
  //--------------------------------------------------------------------------------
  INLINE  CATLONG32                    IsNCGMVisible      () const;
  INLINE  int                          HasColor           () const ; 
  INLINE  CATBoolean                   IsDifferentialSaved() const;

  //-----------------------------------------------------------------------------
  // Valeur toujours nulle par defaut
  // Sauf transaction qui fait passer temporairement passer cette valeur a 1...
  // MAIS QUI REMETS CETTE VALEUR A ZERO SUR LES ELEMENTS 
  // AVEC PROTECTION CATTry  CATCatch
  //-----------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Pour gerer des transactions avec remove automatique des objets implicites
  //------------------------------------------------------------------------
  enum   CATCGMWhenRemoved { OnlyRemovable   ,
                             ImplicitRemoved };
  static CATCGMWhenRemoved             SetReleaseReference(const CATCGMWhenRemoved newBehavior);
 
  //----------------------------------------------------------------------
  // WithPrecaution = -1 for PurgeTransaction and Undo unavailable
  //                     
  //                     Explicits Objects unreferenced by GenericNaming
  //                     are push in implicit mode and then deleted if unused
  //                     This value is used in CleanNewerUnused method    
  //----------------------------------------------------------------------
         int                           CleanNewerUnused(int WithPrecaution=0 ); 

  //----------------------------------------------------------------------
  // Logical Clearing 
  //   called on erasure to allow overloaded behaviours 
  //   such as unsubscription
  // And its UndoAction
  //   called on resurrection ...
  //----------------------------------------------------------------------
  virtual void                         Clear() ;

  //------------------------------------------------------
  // Gestion de la famille des objets associes
  //------------------------------------------------------
          void                         GetLinks(                CATLISTP(CATICGMObject) & oLinks        ,
                                                                CATCGMLinkType            iLinkType     = CatCGMDependancies,
                                                                CATRCOLL(int)          *  oSharedStatus = NULL,
                                                                CATLISTV(CATString)    *  oLinksString  = NULL);
  

          void                         GetAllLinks              (CATLISTP(CATGeometry)  & oLinks        );

          void                         FillGraphWithDependancies(CATCGMGraph            & ioGraph       );

  //
   // la vraie delegation en une seule methode virtuelle
  //
  virtual void                         GetLinksCGM              (CATLISTP(CATICGMObject) &oLinks        ,
                                                                 CATCGMLinkType           iLinkType     = CatCGMDependancies,
                                                                 CATRCOLL(int)*           oSharedStatus = NULL,
                                                                 CATLISTV(CATString)     *oLinksString  = NULL);

  //----------------------------------------------------------------------
  // Fonctions propres a la gestion des attributs (obsolete)
  //----------------------------------------------------------------------
          int                          PutAttribute      (const int   Key    ,
                                                                void* Buffer ,
                                                          const int   Length ,
                                                          const int   Control) ;
    const void                       * GetAttribute      (const int   Key    ,
                                                                int & Length) ;
          int                          DeleteAttribute   (const int Key) ;
          void                         DeleteAllAttribute() ;

  //----------------------------------------------------------------------
  // Fonctions propres a la gestion des attributs (nouvelle gestion)
  //----------------------------------------------------------------------
          CATLONG32                    PutAttribute      (      CATCGMAttribute          * NewAttr) ;
          CATCGMAttribute            * GetAttribute      (const CATCGMAttrId             *) ;
          CATLONG32                    ReleaseAttribute  (      CATCGMAttribute          * NewAttr) ;
          void                         GetListAttribute  (      CATLISTP(CATCGMAttribute)  &,
                                                          const CATCGMAttrId              *  CurUAID = NULL);
          void                         GetNextAttribute  (      CATCGMAttribute           *  PrevAttr,
                                                                CATCGMAttribute           *& NextAttr);


  //----------------------------------------------------------------------
  // Piece pour integration SmartDuplicate/CloneManager
  //     sur entites federatrices definies (Edge pour commencer)
  //     porteuses de decorations gerables en duplication/transformation
  //     en contexte de la transformation courante
  // Generalisation possible sur la nature des attributs
  //     (pre-req monocodage PublicInterfaces V5R21)
  //----------------------------------------------------------------------
  virtual CATBoolean                   HasClonableAttribute(CATLISTP(CATCGMAttribute) &ioList);

  //----------------------------------------------------------------------
  // Gestion de la Persistence (Stream/UnStream)
  //----------------------------------------------------------------------
  
  // Optimisation de la structure du container sur disque

  virtual CATULONG32                   GetStreamPreferedRank();
  virtual CATBoolean                   AllLinkedObjectsAlreadyStreamed();

  virtual void                         CreateNecessaryStreamData(  CATCGMStream& Str );
  virtual void                         DeleteNecessaryStreamData(  CATCGMStream& Str );

  virtual int                          GetStreamSortingKey  (      CATCGMStream& Str);
  virtual int                          GetStreamSortingKey2 (      CATCGMStream& Str);
  virtual int                          HasCommonStreamData  (const CATCGMObject* ipObjectToCompare,
                                                                   CATCGMStream& Str);
  virtual int                          GetMaxSimilarityLevel();

  virtual size_t                       EstimateCommonStreamDataSize
                                                              (   int           iSimilarityLevel,
                                                                  CATCGMStream& Str             );

  virtual void                         CopyCommonStreamData(const CATCGMObject* ipObjectToCompare,
                                                                  int           iSimilarityLevel ,
                                                                  CATCGMStream& Str              );


          CATCGMObject               * GetObjCommonStreamDataKnotVector (CATBoolean       iForKnotVectorV ,
                                                                         CATBoolean       iCompareWithKnotVectorV,
                                                                         int&             ioSimilarityLevel,
                                                                         CATCGMStream&    Str             );

          void                         RegisterDataStreamedKnotVector   (CATBoolean       iForKnotVectorV ,
                                                                         CATCGMStream   & Str             );

          void                         RegisterDataNOTStreamedKnotVector(CATBoolean       iForKnotVectorV );

  virtual const CATKnotVector        * GetKnotVectorU() const;
  virtual const CATKnotVector        * GetKnotVectorV() const;

  //----------------------------------------------------------------------
  // Clone && Methods of the CATTransfoManager
  //----------------------------------------------------------------------
          CATCGMAttrReframeDesignLimits * ReframeDesignRange  (const double                          & iOldInfinite,
                                                                     CATCGMAttrReframeDesignLimits * & iAnchorLink );
          CATCGMAttrReframeDesignLimits * ReframeDesignRange  (const double                          & iOldInfinite,
                                                               const CATCloneManager                 & iCM         );
  virtual CATCGMAttrReframeDesignLimits * ReframeDesignLimits( const double                          & iOldInfinite,
                                                               const CATCloneManager                 * ipCM        );
  
  virtual CATICGMObject                 * Clone         (      CATCloneManager    & iCloning) const;
  virtual void                            Move3D        (      CATTransfoManager  & iTransfo);
  virtual CATGeometry                   * CloneAndMove3D(      CATTransfoManager  & iTransfo);
  virtual CATBoolean                      IsDeepConfused(      CATTransfoManager  & iTransfo,
                                                         const CATGeometry       *  iTGeometry) const;
  

  //----------------------------------------------------------------------
  // Gestion de la couleur en  R(ed), G(reen), B(lue), (INTERNAL ONLY)
  //----------------------------------------------------------------------
          void                         GetColor  (unsigned int &R, unsigned int &G, unsigned int &B) const;

          void                         PutColor  (unsigned int R,unsigned int G,unsigned int B, int Event = 1);
          void                         ResetColor(int Event = 1);
          void                         PutRed    (unsigned int red,   int Event = 1);
          void                         PutGreen  (unsigned int green, int Event = 1);
          void                         PutBlue   (unsigned int blue,  int Event = 1);

  //----------------------------------------------------------------------
  // Incremental stream
  //----------------------------------------------------------------------
          void                         SetDifferentialSaved();

          void                         SetDiff_Modified(CATBoolean AddInModifiedList = TRUE);
          void                         ResetDiff       ();
  INLINE  int                          GetDiff_ToModify() const;


  INLINE  int                          IsUndoLogged   () const;
          void                         SetUndoLogged  (); 
          void                         ResetUndoLogged();

  //VUC: 2009-10-27 IncrementalStream
  //determine if an object was saved previously
  INLINE CATBoolean                    WasIncrementallySaved  () const;
  INLINE void                          ResetIncrementallySaved();
  
  //VUC 2010-04-14 : we must store those information at runtime

         void                          SetHasSharpnessChange  ();
         void                          SetHasLyingOnChange    ();
  
         void                          SetTopoNoFrozen        ();
         void                          SetModifiedLinkeObjects();

  // YL3 : Linked objects of modified objects should also be saved
  virtual int                          SetLinkedObjectsForIS  ();

  //VUC: 2010-01-29 IncrementalStream
          void                         SortAttributes         ();

  virtual void                         SpecificUnstreamLimitsForIncrementalStream(CATCGMStreamImpl       * pStrImpl        ,
                                                                                  CATLISTP(CATICGMObject)& ListDependencies,
                                                                                  LimitCompactInfo       & oLimits         );

  //----------------------------------------------------------------------
  // Gestion des autres attributs VISU internes (INTERNAL ONLY)
  //----------------------------------------------------------------------
          void                         Show                   () ;
          void                         NoShow                 () ;
  
  //---------------------------------------------------------------
  // Infinite Cells (Or not) 
  //---------------------------------------------------------------
          void                         SetInfinite            (CATBoolean YesOrNo);
          CATBoolean                   GetInfinite            () const;
 
  //---------------------------------------------------------------
  // Infinite Cells (Or not) 
  //---------------------------------------------------------------
          CATICGMUnknown             * isSubscribedOn         (const CATCGMEventType itp);

  //---------------------------------------------------------------
  // smartneedCopy Cells (Or not) 
  //---------------------------------------------------------------
          void                         SetTouched             (short);

  //---------------------------------------------------------------
  // ExceptionalRattrap
  //---------------------------------------------------------------
  virtual void                         ExceptionalRattrap     (CATCGMStream& Str);

  // Unstream of linked objects : number of linked objects should be always read by the owner
  virtual void                         GetNumberOfLinkedObjects (CATCGMStreamImpl* pStrImpl, CATULONG32 &oNbLinkeds) const;

  //----------------------------------------------------------------
  // recursive analysis (dump & checkup) INTERNAL ONLY
  //----------------------------------------------------------------
  virtual void                         Inventory(const int            depth = 0 ,
                                                 const char           msg[] = "");
  virtual void                         CheckUp (       CATCX_CHECKUP* report);

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to CheckUp method and CATCX_CHECKUP class
  //----------------------------------------------------------------------

  virtual void                         InitTransactionBit(const int value=0); 

  virtual void                         IsModified() ;

  virtual void                         IsModifiedWithoutIncrementalStreamFlagSet();

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to Container->Remove()
  //-----------------------------------------------------------------------
  virtual CATCXTopology              * CastToCATCXTopology() const;
  virtual int                          IsWeaklyReferenced()  const;

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to the modeler extended to polyhedral topological objects
  //-----------------------------------------------------------------------
  virtual CATCGMTopologyImpl         * CastToCGMTopologyImpl() const; 

  //========================================================================================================================
  // Distinction  
  //     CPOFSM_Delegation      : calcul de la grappe des dependances a embarquer pour une complete autonomie de la definition
  //     CPOFSM_TakeIntoAccount : debut de prise en compte d'une participation a la persistance 
  //=======================================================================================================================

          void                         ComputePersistentObjectsForStream(CATCGMStream& Str          ,
                                                                         int           iCPOFSM_Mask = CPOFSM_Delegation|CPOFSM_TakeIntoAccount );


  //-----------------------------------------------------------------------
  // INTERNAL ONLY : gestion du CATCGMQueryManager
  //-----------------------------------------------------------------------
  virtual void                         TopologicalPropagateQuery(CATICGMUnknown     * iFrom ,
                                                                 CATCGMQueryManager & iQuery);
 
  virtual void                         DoLimitsRequest          (const CATCGMLimitsRequest  iRequest,
                                                                       CATCGMQueryManager & iQuery);
  
  //-----------------------------------------------------------------------
  // INTERNAL ONLY : gestion du CATCGMQueryManager (NegativeOffsets)
  //-----------------------------------------------------------------------

  virtual void                         UpdateAfterCleanNegativeOffsets
                                                (CATICGMObject * NOVObj,short shift1, short shift2);

  virtual CATLONG32                    IsIndexOffsetSensitive(CATLISTP(CATICGMObject) & AllDepended);
  
  //-----------------------------------------------------------------------
  // Detection d'equation ouvertes empechant la redefinition d'un objet
  //-----------------------------------------------------------------------
  virtual CATBoolean                   IsLocked      (int * oLockCount = 0) ;
  // forced destruction of OptData (throws if locked)
  virtual void                         DestroyOptData();
  virtual CATBoolean                   IsOptData     () const;

  //-----------------------------------------------------------------------
  // Gestion des UseCount specific (pour les liens topologiques
  //  Premier Usage : protection des POEC references par Edge/SubdboundingVertex
  //-----------------------------------------------------------------------
  static  void                         AddStrongTopoLink       (const CATICGMObject  *iClient, CATCXTopology  *iCustomer);
  static  void                         DelStrongTopoLink       (const CATICGMObject  *iClient, CATCXTopology  *iCustomer);
  static  CATULONG32                   GetCountOfStrongTopoLink(const CATICGMObject  *iClient);
  
  static  void                         AddWeakTopoLink         (const CATICGMObject  *iClient, CATSubdOccurence  *iCustomer);
  static  void                         DelWeakTopoLink         (const CATICGMObject  *iClient, CATSubdOccurence  *iCustomer);
  static  CATULONG32                   GetCountOfWeakTopoLink  (const CATICGMObject  *iClient);
  
  static  CATULONG32                   GetCountOfAllTopoLinks  (const CATICGMObject  *iClient);

  //-------------------------------------------------------------------------
  // Gestion des donnees de vivicite
  // CATCXEdge/CATPCurveCGM/CATPCurveCGM stockees sur CATCXEdge
  // CATCXVertex/CATCXEDge/CATCXEdge stockees sur CATCXVertex
  //-------------------------------------------------------------------------
  virtual void                         LinkSharpnessDataAsMain     (CATCGMSharpnessData* ipSharpnessData);
  virtual void                         UnlinkSharpnessDataAsMain   (CATCGMSharpnessData* ipSharpnessData);

  virtual void                         LinkSharpnessDataAsBounded  (CATCGMSharpnessData* ipSharpnessData);
  virtual void                         UnlinkSharpnessDataAsBounded(CATCGMSharpnessData* ipSharpnessData); 

  //----------------------------------------------------------------------------
  // Internal USE : Reserved for initiated DO NOT STORE or STREAM this info
  //----------------------------------------------------------------------------
  virtual  CATGeometricType            GetVolatileType             () const =0 ;

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : ....
  //-----------------------------------------------------------------------
  static CATCGMSession               * CreateIfNeededSession       ();
  static void                          CleanSessionAtExit          ();

  //--------------------------------------------------------
  // Gestion   CATCGMTempoULONGPTR
  //--------------------------------------------------------
          void                         TempoULONGPTR_Set   ( CATULONGPTR   iValue ) ;
          void                         TempoULONGPTR_Unset ( )                      ;
          CATBoolean                   TempoULONGPTR_Get   ( CATULONGPTR & ioValue) ;

  //--------------------------------------------------------
  // NickName Management
  //--------------------------------------------------------
          void                         SetNickName  ( CATCGMNickName* ipNickName       ,
                                                      CATBoolean      iWithSubscribe   ) ;
          void                         UnsetNickName( CATBoolean      iWithUnsubscribe = TRUE) ;
          CATCGMNickName             * IsNickName   () ;

 
  //--------------------------------------------------------
  // Major Version and Minor Version Management 
  //    To detect contradictory 
  //--------------------------------------------------------
  virtual  CATCGMStreamVersion         GetMininalStreamVersion( const CATCGMStreamVersion iMajorOrMinorVersion) const ;
 
  //--------------------------------------------------------
  // Fusion
  virtual void                         LockEquation       (void *iForDebug);
  virtual void                         UnLockEquation     (void *iForDebug);
  virtual CATCGMLimitsManagement       GetLimitsManagement();

  virtual CATBoolean                   IsSmallerThan255BytesOnDisk();

  //--------------------------------------------------------
  // OBB 
  //--------------------------------------------------------

   virtual CATBoolean                  IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const;

 /**
  * @param iType
  *    Type of Box.
  * @param iRequest
  *    Type of Request.
  *   <dl>
  *    <dt>IsCacheAvailable</dt><dd>check if memory cache management is available</dd>
  *    <dt>IsCacheComputed</dt><dd>check if memory cache management is computed</dd>
  *   </dl>
  * @nodoc
  * @return TRUE if request of advanced bounding box cache management is available
  */
  virtual CATBoolean                   IsAdvancedBoundingBoxCache(const CATMathAdvancedBoxType            iType,
                                                                  const CATMathAdvancedBox_IsCacheRequest iRequest) const;

  virtual int                          GetDependencyDimension();

protected:

  virtual ~CATCGMObject();


  virtual void                         IsCreated() ;

  virtual CATCGMContainer            * GetImplicitOfCCGMContainer() const ;

  virtual CATCGMStreamVersion          GetLastVersion(); // Version when occurs the last modification of the stream/unstream for this object

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to Container->RemoveAll
  // INTERNAL ONLY : dedicated Stream with GenericNaming 
  //----------------------------------------------------------------------


  //-----------------------------------------------------------------------
  // INTERNAL ONLY : ....
  //-----------------------------------------------------------------------
  virtual void                         ComputePersistentLinksForStream(); // rattrap CXR3 et anterieur sur Cell et Body (chainage Domaines)
  
  //-----------------------------------------------------------------------
  // INTERNAL ONLY : ....
  //-----------------------------------------------------------------------
  virtual CATCGMObject               * NewSameType(CATCGMContainer * iContainer) const   = 0;
  
  //-----------------------------------------------------------------------
  // INTERNAL ONLY : ....
  //-----------------------------------------------------------------------
  static CATCGMSession *_Session;

private:
  
  CATCGMObject             (const CATCGMObject&);
  CATCGMObject& operator = (const CATCGMObject&);

 
          void                         ColorChangeEvent();
          void                         ShowNoShowChangeEvent();


  static CATCGMWhenRemoved _DefaultBehavior;

  //------------------------------------------------------------------
  // CATCGMObject a des amis pour ne pas deprivatisé les données membres  
  //-------------------------------------------------------------------
  friend class CATCGMContainer ;
  friend class CATRootContainerCGM;
  friend class CATGeoFactoryCGM;
  friend class CATCXTopology;
  friend class CATCXBody;
  friend class CATCGMDebugImpl;   // Pont GeometricObjects-GeometricObjectsCGM
  friend class CATCGMTopoCXMODEL; // Pont GeometricObjectsCGM-NewTopologicalObjects
  friend class CATDeclarativeManifoldCGM;

  friend class CATCGMStreamCGMImpl; // Extraction service transactionel et dedie persistence
};



//--------------------------------------------------------------------------
// IsNCGMVisible
//-------------------------------------------------------------------------
INLINE CATLONG32 CATCGMObject::IsNCGMVisible() const
{
   return ( (!_DynObject|| ! _DynObject->DynBits._Rep_NCGM)   ? 0 : 1);
}
 
//--------------------------------------------------------------------------
// HasColor
//-------------------------------------------------------------------------
INLINE int  CATCGMObject::HasColor() const
{
   return ((_DynObject && _DynObject->DynBits._withColor) ? 1 : 0 ); 
}

//-------------------------------------------------------------------------
//VUC : 2009-10-27 
INLINE CATBoolean CATCGMObject::WasIncrementallySaved() const
{
   return (_DynObject && _DynObject->DynBits._IsDifferentialSaved) ? TRUE : FALSE ; 
}

//-------------------------------------------------------------------------
INLINE void CATCGMObject::ResetIncrementallySaved()
{
   if(_DynObject && _DynObject->DynBits._IsDifferentialSaved)
      _DynObject->DynBits._IsDifferentialSaved = 0;
}

//-------------------------------------------------------------------------
INLINE CATBoolean CATCGMObject::IsDifferentialSaved() const
{
   return (  (CGA.IsUnstreamed || (_DynObject && _DynObject->DynBits._IsDifferentialSaved) ) ? TRUE : FALSE ); 
}

//-------------------------------------------------------------------------
INLINE int CATCGMObject::GetDiff_ToModify() const
{
   return ( _DynObject ? _DynObject->DynBits._IsDifferential_ToModify  : 0 ); 
}

//-------------------------------------------------------------------------
INLINE int CATCGMObject::IsUndoLogged() const
{
   return ( _DynObject ? _DynObject->DynBits._IsUndoLogged  : 0 ); 
}

//--------------------------------------------------------------------------
// GetImplementCGM
//-------------------------------------------------------------------------
INLINE void *CATCGMObject::GetImplementCGM(CATGeometricType iTypeReference) const
{
   if ( iTypeReference == CATGeometryType )  return (void *)this;
   if ( ! IsATypeOf(iTypeReference)       )  return NULL;
   return (void *)this;
}

//--------------------------------------------------------------------------
// GetSecureImpl
//-------------------------------------------------------------------------
INLINE CATCGMObject  *CATCGMObject::GetSecureImpl(const CATICGMObject   * Object        ,
                                                        char            * ifile         ,
                                                        int               iline         ,
                                                        CATGeometricType  iTypeReference)
{
   CATCGMObject* impl = Object ? (CATCGMObject*) Object->GetImplementCGM(iTypeReference) : NULL;

   if ( impl && (impl->CGA.IsContainer || impl->CGA.removed || (impl->_Container == NULL)) )
      impl = NULL;
   // #if defined ( CATCGMBOAObject )
   // #else
   if ( impl == NULL ) CATCGMThrowForNullPointer(ifile,iline); 
   // #endif
   return impl;
}



//-------------------------------------------------------------------------
INLINE CATULONG32  CATCGMObject::RemoveReference(CATICGMObject* pointingobject)
{
   int modifmod = CGA.removable ? 0 : 1;

   if (    modifmod           )   CGA.removable = 1;

   CATULONG32  res = ReleaseReference( pointingobject );

   if ( modifmod && (res !=0) )  CGA.removable = 0;

   return res;  
}
//--------------------------------------------------------------------------
// MACRO   GetSecureCGMObject
//-------------------------------------------------------------------------

#if defined ( CATCGMBuildDebug )
#define GetSecureCGMObject(pointer)           CATCGMObject::GetSecureImpl(pointer,__FILE__,__LINE__)
#define GetSecureCGMObjectType(pointer,type)  CATCGMObject::GetSecureImpl(pointer,__FILE__,__LINE__, type)
#else
#define GetSecureCGMObject(pointer)           CATCGMObject::GetSecureImpl(pointer, NULL, 0)
#define GetSecureCGMObjectType(pointer,type)  CATCGMObject::GetSecureImpl(pointer, NULL, 0, type)
#endif

//--------------------------------------------------------------------------
// beurk CATCGMNativeInterfaceImpl
//-------------------------------------------------------------------------
INLINE CATICGMObject* CATCGMObject::CATCGMNativeInterfaceImpl(CATICGMObject *itf)
{
   if ( ! itf )
      return NULL;

   CATCGMObject  *cgmobj =  (CATCGMObject *)itf->IsCGMV5();

   // Rattrape pour DataExtension
   if ( cgmobj == NULL )
   {
      CATBaseUnknown  *unknown = itf->GetImpl();
      #ifdef CATCGMBOAObject
      CATICGMObject_var TrueItf = unknown;
      if ( !! TrueItf )
         cgmobj =  (CATCGMObject *)TrueItf->IsCGMV5();
      #else
      if ( unknown )
      {
         CATMetaClass *curMeta = unknown->GetMetaObject();
         if ( curMeta && curMeta->IsAKindOf( CATCGMObject::MetaObject() ) )
            cgmobj =  (CATCGMObject *)unknown;
      }
      #endif
   }

   if ( cgmobj == NULL ) // SANS IMPLEMENTATION  V5 IL FAUT RENVOYER LA MEME INTERFACE
      return itf;

   CATICGMUnknown *newitf = NULL;

   if ( !cgmobj->CGA.IsContainer )
   {
      #if defined ( CATCGMCompactObject ) 
      newitf = (cgmobj->_ForNativeInterface.CATCGMCompactItf.m_cRef > 0) 
              ? (CATICGMUnknown *)(& cgmobj->_ForNativeInterface) 
              : NULL; 
      #else
      if ( CGA.PreviousCGM == NULL ) 
         newitf = CGA.NextItf; 
      else
         newitf = CGA.PreviousCGM->CGA.NextItf; 
      #endif
   }

   return (CATICGMObject*)newitf;
}


#endif

