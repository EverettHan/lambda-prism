/* -*-c++-*- */
#ifndef CATCGMFusion_H
#define CATCGMFusion_H
#include "ExportedByGeometricObjects.h"
/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//     Root of CGM implementation
//=============================================================================
#include "CATGMAdapter.h"
#include "CATICGMObject.h"
#include "CATCGMNewInterface.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATGeometryType.h"

#include "CATCGMCompactObject.h"
#include "CATCGMBOAObject.h"
#include "CGMObject.h"
#include "CATThrowForNullPointer.h"
#include "cgmier.h"
#include "CATCGMStreamVersion.h"
#include "ExportedByCATCGMFusion.h"
 
class CATCGMStream;
class CATCGMDynObject;

class CATCGMObject;
class CATCGMContainer ;
class CATRootContainerCGM;
class CATGeoFactoryCGM;
class CATCXTopology;
class CATCXBody;

class CATCGMDebugImpl;
class CATCGMTopoCXMODEL;
class CATCGMStreamCGMImpl;
class CATCGMDynObject;
class CATCGMAttribute;
class CATCGMExclusive;

//------------------------------------------------------------------------------------
// Pour l' "astuce" de la faible valeur du UseCount
//------------------------------------------------------------------------------------
#define CATCGMBigUseCountNeeded   (unsigned short) 0x03FF // (sur 10 bits)


#if defined ( CATCGMBOAObject )
class ExportedByGeometricObjects CATCGMFusion
#else
class ExportedByGeometricObjects CATCGMFusion : public CATGMAdapter
#endif
{
protected :
  /**
   * @nodoc constructor destructor.
   */
           CATCGMFusion();
  virtual ~CATCGMFusion();

  /**
   * @nodoc Root Data Members.
   */
    CATCGMContainer  * _Container;
    CATCGMDynObject  * _DynObject;

  /**
   * @nodoc Embedded native Interface.
   */
public :
#if defined ( CATCGMCompactObject )
   union CATCGMInterfaceForCompactObject _ForNativeInterface;
#endif

   /**
   * @nodoc Inline functions
   */
public :

  INLINE  size_t               GetEstimatedMemoryBytes     () const;
  INLINE  CATLONG32            IsExplicit                  () const;
  INLINE  CATCGMDynObject   *  RetrieveDynObject           () const;
  INLINE  short                IsPermanentFrozen           () const;
  INLINE  CATBoolean           IsModifiable                () const;
  INLINE  CATBoolean           HasBeenLoaded               () const;
  INLINE  void              *  IsCGMV5                     () const;
          int                  IsSameTypeAs                (CATICGMUnknown * iOtherObject) const ;
  INLINE  CATICGMUnknown    *  GetInterface                () const;
  INLINE  CATULONG32           GetPersistentTag            () const;
  INLINE  int                  IsContainer                 () const;
  INLINE  CATCGMContainer   *  GetContainerImpl            () const;
  INLINE  CATCGMObject      *  NextCGMObject               () const;
  INLINE  CATCGMObject      *  Previous                    () const;
  INLINE  CATLONG32            IsRemoved                   () const;
  INLINE  CATLONG32            IsRemovable                 () const;
  INLINE  CATLONG32            IsPersistent                () const;
  INLINE  short                HasBeenVisited              () const;
  INLINE  int                  IsExclusiveTemporary        () const;
  INLINE  CATBoolean           IsAlreadyStreamed           () const;
  INLINE  int                  IsNoShow                    () const;
  INLINE  int                  IsLinkedWithCGMEvents       () const;
  INLINE  short                GetTouched                  () const;
  INLINE  int                  IsExplicitShow              () const;
  INLINE  short                IsNCGMAlreadyFrozenSaved    () const;
  INLINE  int                  IsOfCurrentTransaction      (CATCGMStream* ipStr = 0) const;
  INLINE  int                  IsOfCurrentStreamTransaction(CATCGMStream& Str) const;
          int                 _IsOfCurrentStreamTransaction(CATCGMStream& Str) const;
  INLINE  int                  HasBeenPersistent           () const;
  INLINE  CATULONG32           GetUseCount                 (CATCGMUseCountType iUseType = CatCGMUseCountAllCATICGMObject) const;


  INLINE  int                  HasBeenCheckup              ();
  INLINE  void                 ResetExclusiveTemporary     ();
  INLINE  void                 SetExclusiveTemporary       ();
  INLINE  void                 SetIsVisited                ();
  INLINE  int                  HasBeenClosed               ();
  INLINE  void                 ResetOfCurrentTransaction   ();
  INLINE  void                 SetDynObject                (CATCGMDynObject *iDynObject); 
  
  //---------------------------------------------------------------
  // Unstreamed Management
  //  0 : object cree au cours de la session memoire
  //  1 : object en cours d'Unstream
  //  2 : object issu d'un Unstream
  //  3 : object imcompletement Unstream (CATCXEdgeDomain avec CATSubd)
  //---------------------------------------------------------------
  INLINE  short                IsUnstreamed                () const;
  INLINE  void                 SetStartUnstream            ();
  INLINE  void                 SetFinishUnstream           ();
  INLINE  short                IsStartedUnstreamed         () const;
  INLINE  short                IsFinishedUnstreamed        () const;
  INLINE  short                IsBetweenTwoLevelsOfUnstream() const;
  INLINE  void                 SetFirstOfTwoLevelOfUnstream();
  INLINE  void                 ReverseToFirstOfTwoLevelOfUnstream();
  INLINE  void                 FinishTwoLevelOfUnstream    ();

  INLINE  void                 SetTemporaryModifiable      (short          iYesOrNo );
  INLINE  void                 PermanentFrozen             ();
  
  INLINE  void                 SetRemoved                  (CATLONG32      yesorno);
  INLINE  void                 SetLinkedWithCGMEvents      (int);

  //---------------------------------------------------------------
  // CATCX_NCGM : smart Save (only once on Frozen Geometry)
  //---------------------------------------------------------------
  INLINE  void                 SetNCGMAlreadyFrozenSaved  (short);

  //------------------------------------------------------------------------
  // if Removable, Implicit object is removed automatically if UseCount comes to 0  
  //------------------------------------------------------------------------
  INLINE  void                 SetRemovable                (CATLONG32       yes_or_no);

  INLINE  void                 SetInterface                (CATICGMUnknown* iObject);

  //---------------------------------------------------------------
  // Persistent/Light/ToSave object chain 
  //---------------------------------------------------------------
  INLINE  CATCGMObject      *  NextPersistent              ()         const;
  INLINE  CATCGMObject      *  PreviousPersistent          ()         const;

   /**
   * @nodoc IsATypeOf
   */
  virtual int                  IsATypeOf                   (CATGeometricType TypeReference) const =0 ;

   /**
   * @nodoc
   */
    const CATTolerance       & GetToleranceObject          () const;

          CATCGMObject      *  Next                        ()    const;
   /**
   * @nodoc OMX MLK TRACKER
   */
          int                  MLKTracker_Init             ( CATMetaClass *iMetaObject ) const ;
   /**
   * @nodoc CATBaseUnknown overloading
   */
public :
  //-----------------------------------------------------------------------
  //  Surcharge de methodes  de CATBaseUnknown 
  //    AddRef, GetImpl : pour PERFOS
  //    Release         : pour PERFOS + pour controler les Release abusifs
  //    IsNull          : pour dire qu'un objet apres Clear est considere
  //                      comme detruit.
  //----------------------------------------------------------------------
  virtual ULONG           __stdcall AddRef                      ();
  virtual ULONG           __stdcall Release                     ();

#if defined ( CATCGMBOAObject )
          CATICGMUnknown* __stdcall GetImpl(int iFlag = 0) const;
#else
  virtual CATBaseUnknown* __stdcall GetImpl(int iFlag = 0) const;
#endif

  virtual int                       IsNull() const;

  virtual HRESULT         __stdcall QueryInterface(const IID     &iid,
                                                         void **  ppv);

  virtual CATBaseUnknown *          QueryInterface(CATClassId iInterface) const;

   /**
   * @nodoc UseCount
   */
  virtual CATULONG32          SpecificGetUseCount(CATCGMUseCountType iUseType) const = 0;
  virtual CATULONG32          GetTrueUseCount    ()                            const = 0;

   /**
   * @nodoc virtual genuine
   */
  virtual CATBoolean         _IsStreamable       ( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const = 0;
  virtual void                Stream             ( CATCGMStream& Str )   = 0 ;
  virtual void                UnStream           ( CATCGMStream& Str, CATLISTP(CATICGMObject)& ListDependencies ) = 0 ;
  virtual short               GetType            ()  = 0 ;
  virtual void                GetSessionType     (CATUnicodeString & oValue) const;
  virtual CATLONG32           GetHighestDimension() const;
  
   /**
   * @nodoc virtual genuine
   */
  virtual CATLONG32           PutAttribute       (      CATCGMAttribute           *  iNewAttr   )       = 0 ;
  virtual CATCGMAttribute   * GetAttribute       (const CATCGMAttrId              *  iAttrId    )       = 0 ;
  virtual CATLONG32           ReleaseAttribute   (      CATCGMAttribute           *  iAttr      )       = 0 ;
  virtual void                GetListAttribute   (      CATLISTP(CATCGMAttribute)  & oListOfAttr,
                                                  const CATCGMAttrId              *  iAttrId    = NULL) = 0;
  virtual void                GetNextAttribute   (      CATCGMAttribute           *  iPrevAttr  ,
                                                        CATCGMAttribute           *& ioNextAttr )       = 0;

  //----------------------------------------------------------------------------------
  // INTERNAL ONLY : GetStaticMemoryBytes()  + GetDynamicMemoryBytes()
  //---------------------------------------------------------------------------------
  virtual size_t              GetStaticMemoryBytes      () const = 0;
  virtual size_t              GetDynamicMemoryBytes     () const = 0;
  virtual CATCGMContainer   * GetImplicitOfCCGMContainer() const = 0;

   /**
   * @nodoc beurk
   */
  INLINE static CATCGMObject* GetImpl(CATICGMObject* iObject);

   /**
   * @nodoc protected functions
   */
protected :


  //----------------------------------------------------------------------------------
  // Specifique Container Interface
  //---------------------------------------------------------------------------------
  virtual CATICGMUnknown     * GetContainerInterface() const;
  virtual CATICGMUnknown     * SetContainerInterface(CATICGMUnknown* iObject);

  /**
  * GetName : give role of data.
  */
  virtual HRESULT              GetShortName(CATUnicodeString & oValue) const  ;


  //===================================================================================
  // Meta description for Recording Replaying
  //    for common Replay-PlayBack-Phoenix integration
  //       same descriptive infrastructure available
  //       with CGMReplay as Proof Of Concept (2012Spring)
  //===================================================================================

  /**
  * GetRecording (generate if necessary (and before Run())
  */
  virtual CATechAttribute * GetRecording(CATechSet **iContext = NULL) const   ;

  /**
  * SetRecording 
  */
  virtual HRESULT           SetRecording(CATechAttribute * iReplaying,
                                         CATechSet       * iContext  );

  /**
  * GetReplaying 
  */
  virtual CATechAttribute * GetReplaying(CATechSet      ** iContext  = NULL) const   ;

  /**
  * SetReplaying 
  */
  virtual HRESULT           SetReplaying(CATechAttribute * iReplaying,
                                         CATechSet       * iContext  );




private:
  /**
   * @nodoc genuine root.
   */ 
  struct CATCGA
  {    
#if defined ( CATCGMBOAObject )

    CATCGMFusion     * PreviousPersistent;
    CATICGMUnknown   * NextPersistentItf;

    CATCGMFusion     * PreviousCGM;
    CATICGMUnknown   * NextItf;       // Pointeur vers l'interface du suivant

#else

    CATCGMObject     * PreviousPersistent;
    CATCGMObject     * NextPersistent;

    CATCGMObject     * PreviousCGM;
    CATCGMObject     * NextCGM;

#endif

    CATULONG32        Tag;           // Identification persistente de l'objet

    unsigned UseCount                : 10; // Nombre de références sur l'objet => valuer CATCGMBigUseCountNeeded en consequence !!!

    // petits attributs persistents
    unsigned Explicit                : 1;  // object publics ou interne de construction
    unsigned infinite                : 1;  // topologie a l'infini
    unsigned touched                 : 1;  // duplication necessaire pour le partage ... 
    unsigned IsFrozen                : 1;  // Gel permanent 
    unsigned IsTemporaryFrozen       : 1;  // Gel Temporaire 

    unsigned _StrongTopoLink         : 1;  // les couleurs NCGM de l'object sont valides
    unsigned _WeakTopoLink           : 1;

    unsigned _is_Show                : 1;

    unsigned linkedWithCGMEvents     : 1;

    // petits attributs temporaires (non archives)
    unsigned removed                 : 1;
    unsigned removable               : 1;

    unsigned IsPersistent            : 1;  // persistent
    unsigned WasPersistent           : 1;  //   
    unsigned TransactionDone         : 1;  // bit temporaire de travail 

    unsigned IsClosed                : 1;  // dedie Container->RemoveAll()  
    unsigned IsUnstreamed            : 2;  // dedie Container->Unstreamed()  
                                           //  0 : non issu d'une Lecture
                                           //  1 : issue d'une lecture en cours de traitement
                                           //  2 : issue d'une lecture achevee
                                           //  3 : Stream partiel en Deux etapes
    unsigned IsAlreadyStreamed       : 1;  // Optimisation de la structure du container sur disque

    unsigned IsContainer             : 1;  // perfo IsContainer

    // valeur toujours nulle par defaut
    // dedie a des transactions tres temporairement
    // qui font passer cette valeur a 1...
    // MAIS QUI REMETTENT CETTE VALEUR A ZERO SUR LES ELEMENTS 
    // AVEC PROTECTION CATTry  CATCatch
    unsigned ExclusiveTemporaryBit   : 1;
    
    unsigned NCGMAlreadyFrozenSaved  : 1;
    
    unsigned HasBeenVisited          : 1;
    
  } CGA;

   /**
   * @nodoc forbidden.
   */
private:
  CATCGMFusion(const CATCGMFusion&);
  CATCGMFusion& operator = (const CATCGMFusion&);

  friend class CATCGMObject;
  friend class CATCGMContainer ;
  friend class CATRootContainerCGM;
  friend class CATGeoFactoryCGM;
  friend class CATCXTopology;
  friend class CATCXBody;

  friend class CATCGMDebugImpl;
  friend class CATCGMTopoCXMODEL;
  friend class CATCGMStreamCGMImpl;

  friend ExportedByCATCGMFusion unsigned int HashKeyCATCGMObject(CATCGMObject* inew); // Pour perfo

};




//--------------------------------------------------------------------------
// For Performance Enhancement, INLINE has been done,
// To understand implementation, you should have a look on CATCGMObjectBits
//-------------------------------------------------------------------------
INLINE int CATCGMFusion::HasBeenCheckup()
{
  if ( CGA.TransactionDone ) return 1;
  CGA.TransactionDone = 1;
  return 0;
}

//--------------------------------------------------------------------------
// IsOfCurrentTransaction
//-------------------------------------------------------------------------

INLINE int CATCGMFusion::IsOfCurrentTransaction(CATCGMStream* ipStr) const
{ return ipStr ? _IsOfCurrentStreamTransaction(*ipStr) : ( CGA.TransactionDone ? 1 : 0);  }

INLINE int CATCGMFusion::IsOfCurrentStreamTransaction(CATCGMStream& Str) const
{ return  _IsOfCurrentStreamTransaction(Str);  }

//--------------------------------------------------------------------------
// ResetOfCurrentTransaction
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::ResetOfCurrentTransaction()
{ CGA.TransactionDone = 0; }



//--------------------------------------------------------------------------
// HasBeenPersistent
//-------------------------------------------------------------------------
INLINE int CATCGMFusion::HasBeenPersistent() const
{ 
 if ( CGA.IsPersistent  ) return 1;
 if ( CGA.WasPersistent ) return 1;
 return 0;
}

//--------------------------------------------------------------------------
// HasBeenClosed
//-------------------------------------------------------------------------
INLINE int CATCGMFusion::HasBeenClosed()
{  
  int result  = CGA.IsClosed ? 1 : 0;
  if ( result == 0 ) CGA.IsClosed = 1; 
  return result;  
}

//--------------------------------------------------------------------------
// IsPersistent
//-------------------------------------------------------------------------
INLINE CATLONG32 CATCGMFusion::IsPersistent() const
{ 
  return ( CGA.IsPersistent ? 1 : 0);
}

//--------------------------------------------------------------------------
// IsModifiable
//-------------------------------------------------------------------------
INLINE CATBoolean CATCGMFusion::IsModifiable() const
{ 
  return ( (CGA.IsFrozen || CGA.IsTemporaryFrozen) ? FALSE : TRUE);
}

//--------------------------------------------------------------------------
// IsPermanentFrozen
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsPermanentFrozen()   const
{ 
  return (CGA.IsFrozen ? 1 : 0);
}


//--------------------------------------------------------------------------
// SetExclusiveTemporary
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::SetExclusiveTemporary()
{ 
  CGA.ExclusiveTemporaryBit = 1;  
}

//--------------------------------------------------------------------------
// ResetExclusiveTemporary
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::ResetExclusiveTemporary()
{ 
  CGA.ExclusiveTemporaryBit = 0;  
}

//--------------------------------------------------------------------------
// IsExclusiveTemporary
//-------------------------------------------------------------------------
INLINE int CATCGMFusion::IsExclusiveTemporary() const
{ 
  return (CGA.ExclusiveTemporaryBit ? 1 : 0 ); 
}

//--------------------------------------------------------------------------
// HasChangedSinceLastSave
//-------------------------------------------------------------------------
INLINE short  CATCGMFusion::HasBeenVisited() const
{
  return (CGA.HasBeenVisited ? 1 : 0); 
}

//--------------------------------------------------------------------------
// SetIsChanging
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::SetIsVisited() 
{
  if ( CGA.HasBeenVisited == 0 )
    CGA.HasBeenVisited = 1;
}

//--------------------------------------------------------------------------
// IsRemoved
//-------------------------------------------------------------------------
INLINE CATLONG32  CATCGMFusion::IsRemoved() const   
{
  return (CGA.removed   ? 1 : 0);
}
//--------------------------------------------------------------------------
// GetPersistentTag
//-------------------------------------------------------------------------
INLINE CATULONG32  CATCGMFusion::GetPersistentTag() const 
{
  return CGA.Tag; 
}

//--------------------------------------------------------------------------
// IsExplicit
//-------------------------------------------------------------------------
INLINE CATLONG32  CATCGMFusion::IsExplicit() const  
{ 
  return (CGA.Explicit  ? 1 : 0);
} 

//--------------------------------------------------------------------------
// IsExplicit
//-------------------------------------------------------------------------
INLINE int  CATCGMFusion::IsExplicitShow() const  
{
  return ( (CGA.Explicit  && CGA._is_Show) ? 1 : 0);
} 

//--------------------------------------------------------------------------
// IsRemovable
//-------------------------------------------------------------------------
INLINE CATLONG32  CATCGMFusion::IsRemovable() const 
{
  return (CGA.removable ? 1 : 0);
}

 
//--------------------------------------------------------------------------
// IsNoShow
//-------------------------------------------------------------------------
INLINE int   CATCGMFusion::IsNoShow() const 
{
  return (CGA._is_Show ? 0 : 1); 
} 

//--------------------------------------------------------------------------
// IsLinkedWithCGMEvents
//-------------------------------------------------------------------------
INLINE int   CATCGMFusion::IsLinkedWithCGMEvents() const 
{
  return (CGA.linkedWithCGMEvents ? 1 : 0);
} 

//--------------------------------------------------------------------------
// GetContainerImpl
//-------------------------------------------------------------------------
INLINE CATCGMContainer *CATCGMFusion::GetContainerImpl() const 
{ 
  return (CGA.IsContainer ? GetImplicitOfCCGMContainer() : _Container);
}



//--------------------------------------------------------------------------
// NextCGMObject
//-------------------------------------------------------------------------
INLINE  CATCGMObject *CATCGMFusion::NextCGMObject() const
#if defined ( CATCGMBOAObject )
{ 
  if ( CGA.NextItf == NULL ) return NULL;
  return (CATCGMObject*) CGA.NextItf->IsCGMV5();
}
#else
{ return CGA.NextCGM; }
#endif

INLINE CATCGMObject  *CATCGMFusion::Previous()  const
{ return CGA.PreviousCGM; }

//--------------------------------------------------------------------------
// GetTouched
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::GetTouched() const  
{ 
  return (CGA.touched ? 1 : 0);
}

//--------------------------------------------------------------------------
// IsUnstreamed
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsUnstreamed() const  
{
  return CGA.IsUnstreamed; 
}

//--------------------------------------------------------------------------
// SetStartUnstream
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::SetStartUnstream()
{
  if (CGA.IsUnstreamed != 0) CATThrowForNullPointer(); 
  CGA.IsUnstreamed = 1;
}

//--------------------------------------------------------------------------
// SetFinishUnstream
//-------------------------------------------------------------------------
INLINE void CATCGMFusion::SetFinishUnstream()
{
  if ((CGA.IsUnstreamed != 1) && (CGA.IsUnstreamed != 3)) CATThrowForNullPointer(); 
  CGA.IsUnstreamed = 2;
}

//--------------------------------------------------------------------------
// SetFinishUnstream
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsStartedUnstreamed() const
{
  return ((CGA.IsUnstreamed == 1) ? 1 : 0);
}

//--------------------------------------------------------------------------
// SetFinishUnstream
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsFinishedUnstreamed() const
{
  return ((CGA.IsUnstreamed == 2) ? 1 : 0);
}

//--------------------------------------------------------------------------
// IsBetweenTwoLevelsOfUnstream
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsBetweenTwoLevelsOfUnstream() const
{
  return (CGA.IsUnstreamed == 3) ? 1 : 0; 
}

//--------------------------------------------------------------------------
// SetFirstOfTwoLevelOfUnstream
//-------------------------------------------------------------------------
INLINE void  CATCGMFusion::SetFirstOfTwoLevelOfUnstream()
{
  if (CGA.IsUnstreamed != 1) CATThrowForNullPointer(); 
  CGA.IsUnstreamed = 3;
}

//--------------------------------------------------------------------------
// SetFirstOfTwoLevelOfUnstream
//-------------------------------------------------------------------------
INLINE void  CATCGMFusion::ReverseToFirstOfTwoLevelOfUnstream()
{
  if (CGA.IsUnstreamed != 2) CATThrowForNullPointer(); 
  CGA.IsUnstreamed = 3;
}

//--------------------------------------------------------------------------
// FinishTwoLevelOfUnstream
//-------------------------------------------------------------------------
INLINE void  CATCGMFusion::FinishTwoLevelOfUnstream()
{
  if (CGA.IsUnstreamed != 3) CATThrowForNullPointer(); 
  CGA.IsUnstreamed = 2;
}

//--------------------------------------------------------------------------
// HasBeenLoaded
//-------------------------------------------------------------------------
INLINE CATBoolean CATCGMFusion::HasBeenLoaded() const
{
  return (CGA.IsUnstreamed ? TRUE : FALSE); 
}

//--------------------------------------------------------------------------
// IsNCGMAlreadyFrozenSaved
//-------------------------------------------------------------------------
INLINE short CATCGMFusion::IsNCGMAlreadyFrozenSaved() const  
{
  return (CGA.NCGMAlreadyFrozenSaved ? 1 : 0); 
}

//--------------------------------------------------------------------------
// IsContainer
//-------------------------------------------------------------------------
INLINE  int  CATCGMFusion::IsContainer() const
{
  return (CGA.IsContainer ? 1 : 0);
}

//--------------------------------------------------------------------------
// IsAlreadyStreamed
//-------------------------------------------------------------------------
INLINE CATBoolean CATCGMFusion::IsAlreadyStreamed() const
{
  return (CGA.IsAlreadyStreamed ? TRUE : FALSE); 
}

//--------------------------------------------------------------------------
// RetrieveDynObject
//-------------------------------------------------------------------------
INLINE CATCGMDynObject  *CATCGMFusion::RetrieveDynObject() const
{
  return _DynObject;
}


//--------------------------------------------------------------------------
// IsCGMV5
//-------------------------------------------------------------------------
INLINE void *CATCGMFusion::IsCGMV5() const
{
  return (void *)this;
}

//--------------------------------------------------------------------------
// GetInterface
//-------------------------------------------------------------------------
INLINE CATICGMUnknown* CATCGMFusion::GetInterface() const
#if defined ( CATCGMCompactObject ) 
{
  if ( !CGA.IsContainer )
    return (_ForNativeInterface.CATCGMCompactItf.m_cRef > 0) ? (CATICGMUnknown *)(& _ForNativeInterface) : NULL; 
  else
    return GetContainerInterface();
}
#else
{
  if ( CGA.PreviousCGM == NULL ) return CGA.NextItf; 
  return CGA.PreviousCGM->CGA.NextItf; 
}
#endif

//-------------------------------------------------------------------------------
//  Gestion du couplage Interface-Implementation
//-------------------------------------------------------------------------------
void CATCGMFusion::SetInterface(CATICGMUnknown *iObject)
#if defined ( CATCGMCompactObject ) 
{
  if ( !CGA.IsContainer ) 
  {  
    CATICGMUnknown *MyNativeInterface = (CATICGMUnknown *) (& _ForNativeInterface); 
    if (MyNativeInterface != iObject) cgmier(667,this);  
  }
  else SetContainerInterface(iObject);
}
#else
{
  //--------------------------------------------------------------------------------------
  // Implementation avec deja une interface differente
  //---------------------------------------------------------------------------------------
  if ( CGA.PreviousCGM ) 
  {
    if ( iObject && (CGA.PreviousCGM->CGA.NextItf != iObject) ) 
      cgmier(667,this);
    
    CGA.PreviousCGM->CGA.NextItf = iObject ;
  }
  else
    CGA.NextItf = iObject ;
}
#endif

//-----------------------------------------------------------------------------------------
// Gestion des informations exeptionnelles sur l'Objet
//-----------------------------------------------------------------------------------------
INLINE void              CATCGMFusion::SetDynObject(CATCGMDynObject *iDynObject)
{
  if ( iDynObject  &&  _DynObject ) CATThrowForNullPointer(); 
  if ( !iDynObject && !_DynObject ) CATThrowForNullPointer(); 
  _DynObject = iDynObject;

}

//--------------------------------------------------------------------------
// Compteur de references de modelisation
//-------------------------------------------------------------------------
INLINE CATULONG32  CATCGMFusion::GetUseCount(CATCGMUseCountType iUseType) const  
{
  if ( iUseType != CatCGMUseCountAllCATICGMObject ) return SpecificGetUseCount(iUseType);
  if ( CGA.UseCount != CATCGMBigUseCountNeeded )    return CGA.UseCount;
  return  GetTrueUseCount();
}


//---------------------------------------------------------------------------
// For Management of Read/Only Objects
//----------------------------------------------------------------------------

INLINE void  CATCGMFusion::PermanentFrozen()
{ 
  CGA.IsFrozen = 1; 
}

INLINE void  CATCGMFusion::SetTemporaryModifiable( short iYesOrNo )
{ 
  CGA.IsTemporaryFrozen = ( iYesOrNo == 1 ) ? 0 : 1; 
}


//--------------------------------------------------------------------------
// Removed
//--------------------------------------------------------------------------
INLINE void  CATCGMFusion::SetRemoved(CATLONG32 yes_or_no)
{
  CGA.removed = (yes_or_no ? 1 : 0);
}

//--------------------------------------------------------------------------
// LinkedWithCGMEvents
//--------------------------------------------------------------------------
INLINE void  CATCGMFusion::SetLinkedWithCGMEvents(int yes_or_no)
{
  CGA.linkedWithCGMEvents = (yes_or_no ? 1 : 0);
}

//--------------------------------------------------------------------------
// CATCX_NCGM : smart Save (only once on Frozen Geometry)
//--------------------------------------------------------------------------
INLINE void  CATCGMFusion::SetNCGMAlreadyFrozenSaved(short  yes_or_no)
{
  CGA.NCGMAlreadyFrozenSaved = (yes_or_no ? 1 : 0);
}

//--------------------------------------------------------------------------
// Removable
//--------------------------------------------------------------------------
INLINE void CATCGMFusion::SetRemovable(CATLONG32 yes_or_no)
{
  CGA.removable = (yes_or_no ? 1 : 0);
}


//--------------------------------------------------------------------------
// GetEstimatedMemoryBytes
//-------------------------------------------------------------------------
INLINE  size_t  CATCGMFusion::GetEstimatedMemoryBytes() const
{
  size_t  size = ( GetDynamicMemoryBytes() + GetStaticMemoryBytes() );
  return size;
}


//--------------------------------------------------------------------------
// beurk GetImpl
//-------------------------------------------------------------------------
INLINE CATCGMObject* CATCGMFusion::GetImpl( CATICGMObject*  iObject ) 
{
  CATCGMObject* result =  iObject ? (CATCGMObject*) iObject->IsCGMV5() : NULL;
  return result;
}

//--------------------------------------------------------------------------
// Previous/Next persistent object
//-------------------------------------------------------------------------
INLINE  CATCGMObject *CATCGMFusion::NextPersistent() const
#if defined ( CATCGMBOAObject )
{ 
  if ( CGA.NextPersistentItf == NULL ) return NULL;
  return (CATCGMObject*) CGA.NextPersistentItf->IsCGMV5();
}
#else
{ return CGA.NextPersistent; }
#endif

INLINE CATCGMObject  *CATCGMFusion::PreviousPersistent()  const
{ return CGA.PreviousPersistent; } 


//--------------------------------------------------------------------------
// Previous/Next light object
//-------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Previous/Next ToSave object
//-------------------------------------------------------------------------
//INLINE  CATCGMObject *CATCGMFusion::NextToSave() const
//#if defined ( CATCGMBOAObject )
//{ 
//  if ( CGA.NextToSaveItf == NULL ) return NULL;
//  return (CATCGMObject*) CGA.NextToSaveItf->IsCGMV5();
//}
//#else
//{ return CGA.NextToSave; }
//#endif
//
//INLINE CATCGMObject  *CATCGMFusion::PreviousToSave()  const
//{ return CGA.PreviousToSave; } 


#endif

