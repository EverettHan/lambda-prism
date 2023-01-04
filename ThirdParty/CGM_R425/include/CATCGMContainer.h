/* -*-c++-*- */
#ifndef CATCGMContainer_H
#define CATCGMContainer_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// Jul. 02 Portage 64 bits                                                HCN
// Mar. 03 Parametre iAlreadyUnstreamed pour ObjectWithLyingOnStr(...)
// Apr. 03 Parametre iNbLyingOnDataToRead pour UnStreamLyingOnData(...)   HCN 
// Apr. 03 CheckLyingOnAfterUnStream(...),
//         StreamSharpnessData(...), UnStreamSharpnessData(...),
//         ObjectWithSharpnessData(...)                                   HCN
// Jul. 03 Table des AddRef "sauvages" CGMGlobalAddRef                    SDP
// Oct. 03 protected GetObjectNumber() devient public GetMaxTag()         HCN
// Mar. 04 Argument CATCGMHeaderObjectStream* pour CreateObjectUnStream(...) 
//         et version avec CATCGMHeaderObjectStream&,
//         Parametres ipNextObjIdx, ipObjectTag et ipObjectType
//         pour MakeUnStreamContents(...)                                 HCN
// Apr. 04 _pLType_LStrKey_LStrObjs,
//         _pLKnotVectorUStrKey_LStrObjs,
//         _pLKnotVectorVStrKey_LStrObjs,
//         _ObjectDataStreamed,
//         _ObjectDataStreamedKnotVectorU,
//         _ObjectDataStreamedKnotVectorV,
//         DeleteCompactStreamData(...)                                   HCN
// Jul. 05 Statistiques parcours UpDown :
//           GetUpDownStats()                                             HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Oct. 09 IncrementalStream : StartIncrementalStream,DiffUnordered       VUC
//=============================================================================

#include "ExportedByCATCGMFusion.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATRootSharedDataCGM.h"
#include "CATICGMObject.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATCGMFactoryStatus.h"
#include "CATCGMEvents.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATTolerance.h"
#include "CATHashDico.h"

class CATCGMStream;
class CATCGMVersionDefinition;
class CATCGMAttribute;
class CATCGMOutput;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
class CATCX_CHECKUP;
class CATCGMJournalList;
class CATGemDoc;
class CATCGMDocument;
class CATExtCGMGeom;
class CATExtCGMReplay;
class CATCGMOperator;
class CATUuid;
class CATCGMTempoULONGPTR;
class CATCGMUnstreamByInjection;
class CATCGMMapCATULONGPTR;
struct CATCGMHeaderObjectStream;
class CATCGMStreamCGMImpl;
class CATCGMGeomImpl;
class CATCGMChain;
class CATCGMFusion;
class CATCGMExtensionsForPart;
class CATCGMIncrementalStreamGlobalData;

//#include <CATLib.h>

class ExportedByCATCGMFusion CATCGMContainer : public CATCGMObject
{
protected :
  CATRootSharedDataCGM *_SHARED;

public:
  //----------------------------------------------------------------------
  // Basics
  //----------------------------------------------------------------------
  CATCGMDeclareVirtualClass;
  CATCGMContainer( const CATCGMMode          iMode          = CatCGMImplicit
                 , const short               isSessio       = 0 
                 , const CATCGMScaleCategory iScaleCategory = ScaleNotSet 
                 );               
  
  INLINE CATULONG32  ComputeTag() ; 

  void              CreateTagBlocks();
  void              CreateTagBlocks(CATULONG32 BlockLong);
  CATULONG32        GetNextTagInBlock();
  CATULONG32        GetNextTag(); // The only official way to get a new available TAG !!!!!
  int               GetOldestElem (CATGeometry * g1, CATGeometry * g2); // returns the number (1 or 2) of the oldest element, 0 if it is the same
                                                                        // AND : -1 if unknown (it is possible !!!!!!!
 
  //
  // returns the size in bytes occupied in its whole by the container.
  //CATLONG32 GetContainerSize() ;
  size_t GetContainerSize() ;
  //
  // returns the count of objects currently inside the container.
  INLINE CATULONG32   GetObjectsCount() const;
  INLINE CATULONG32   GetTopologyCount() const;
  //-------------------------------------------------------------------------
  // Obtention du Container surlequel sont geres le chainage des objects ...
  //-------------------------------------------------------------------------
  virtual CATCGMContainer * GetTrueContainer() = 0;
  virtual CATLONG32         PutAttribute(CATCGMAttribute * iNewAttr)  ;
  virtual CATCGMAttribute * GetAttribute(const CATCGMAttrId* iAttrId)  ;
  virtual CATLONG32         ReleaseAttribute(CATCGMAttribute * iAttr)  ;
  virtual void              GetListAttribute(CATLISTP(CATCGMAttribute) & oListOfAttr, const CATCGMAttrId* iAttrId=NULL) ;
  virtual void              GetNextAttribute(CATCGMAttribute * iPrevAttr, CATCGMAttribute *& ioNextAttr) ;

  //----------------------------------------------------------------------------------
  // Version du niveau de build CGAOFF    (cf CGMBuildVersion.h)
  //  une version nulle correspond a un niveau de code CGAOFF anterieur au 06/01/00
  //-----------------------------------------------------------------------------------
  INLINE CATULONG32  GetOldestData() const;
  INLINE CATULONG32  GetLastStream() const;

  //----------------------------------------------------------------------
  // Fonction de scan du container
  //----------------------------------------------------------------------
  // Permet d'obtenir le suivant (le premier si NULL) :
  virtual CATGeometry* GetNextChild(CATGeometry* Current, 
                                    CATGeometricType iType = CATGeometryType,
                                    CATBoolean WithImplicits = FALSE); 

  // Ajoute au Container 
  // L'objet ne doit appartenir a aucun Container
  virtual void Add(CATCGMObject* Object , int computetag=1);	
  
  // Enleve du Container 
  // L'objet doit appartenir au Container
  virtual void RemoveAllContents(const CATBoolean iUserClose);

  // dump du container
  virtual void DumpElem( CATCGMOutput& os );   
	
  void  SetContainerImpl(CATCGMObject * iObject); 

  //-----------------------------------------------------------------------
  //  Surcharge de methodes  de CATBaseUnknown 
  //    QueryInterface : pour gestion ambigue de l'adhesion CATIContainer
  //----------------------------------------------------------------------
  virtual HRESULT         __stdcall QueryInterface(const IID &iid,void **ppv);
  virtual CATBaseUnknown *          QueryInterface(CATClassId iInterface) const;

 
  //===================================================================================
  // DEPRECATED 
  //===================================================================================

  //------------------------------------------------------------------------------------------------
  // Gestion du modalites de traitement a la sauvegarde 
  //      - All  : ecriture de tous les objects
  //      - Pack : suppression des implicit unused
  //-------------------------------------------------------------------------------------------------
  enum CATCGMWrite { All, Pack, OnlyPersistent,  Partial};

  // VUC : 16-10-09 Incremental Stream
  //permits to perform incremental stream
  CATBoolean StartIncrementalStream();
  INLINE CATBoolean IsIncrementalStreamInitialized();
  INLINE CATCGMIncrementalStreamGlobalData* GetIncrementalGlobalData();
 
  //===================================================================================
  // DEPRECATED 
  //===================================================================================
  INLINE CATBoolean IsUnderIncrementalPersistencyManagement();
  CATBoolean StartIncrementalPersistencyManagement();

  
  //----------------------------------------------------------------------
  // should be more reliable that the date on the file (moves, copies)
  // based on the moment of an effective change of container's contents.
  //--------------------------------------------------------------------------- 
  void GetCopyOfCATUuid(CATUuid& iid) const;
  
  //----------------------------------------------------------------------
  // Fonctions de Check anti verolage
  //   Check on-the-fly avec Stream-Unstream
  //   et Comparaison par declaratif en se basant sur les valeurs de dump
  //---------------------------------------------------------------------------
  virtual void CheckStream(const CATCGMVersionDefinition *iVersion =NULL) =0;

  int Diff(CATCGMContainer *other, const CATCGMStreamVersion iVersionToCompare, const int iVerboseCGMOut = 1);

  int AsymetricDiffByTag(CATCGMContainer *other, const CATCGMStreamVersion iVersionToCompare, CATHashDico & iDico, const int iVerboseCGMOut = 1);

  //VUC : 16-10-09 Pour le CheckIncrementalStream
  //compare every object of the two containers without taking into account there order in the container
  int DiffUnordered(CATCGMContainer *NewOne, const CATCGMStreamVersion curVersion, const int iVerboseCGMOut = 1);
  HRESULT Reorder(CATListPV& ListOfListOfTags);

  //------------------------------------------------------------------------
  // INTERNAL ONLY : MLC management
  //------------------------------------------------------------------------
  CATCGMStreamVersion GetMLCLevel ();
  void SetMLCLevel (CATCGMStreamVersion iMLCLevel);

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated for CheckUp analysis
  //----------------------------------------------------------------------
  virtual void InitTransactionBit(const int value=0); 

  virtual void CheckUp(CATCX_CHECKUP* report);
  CATCGMObject *GetFirstInternal();
  static CATCGMContainer* Scan(CATCGMContainer *const previous);  
 
  //-----------------------------------------------------------------------
  // List of attribute keys that are necessary within topological operators
  //-----------------------------------------------------------------------
  void AddKernelAttributeKey( int iAttributeKey, int iAttributeType );
  void RemoveKernelAttributeKey( int iAttributeKey );
  CATLONG32 GetNbKernelAttributeKeys();
  int  GetKernelAttributeKey( CATLONG32 iIndex, int & oAttributeType );

  static int RemovingStatus();

  // internal use 
  virtual void TassTags();
  static  int  ChkCtrClosure();

  // ne pas enlever : 
  //   rien de special par rapport au CATCGMObject
  //   mais permet de mettre un point d'arret pour traquer les AddRef en trop
  virtual ULONG           __stdcall AddRef();
  virtual ULONG           __stdcall Release();  

  //----------------------------------------------------------------------
  // Identificateur de Debug
  //----------------------------------------------------------------------
  INLINE CATULONG32  GetSessionIdNumber() const ;
  
  //----------------------------------------------------------------------
  // Nettoyage des HashTables dynamiques du FindFromTag
  //----------------------------------------------------------------------
  static void DesallocateDynamicObjectHashTable();
    
  //----------------------------------------------------------------------
  //  This services allow you to explicitly identify Input Geometry
  //    which must not be taken into account in Factory Check()
  //----------------------------------------------------------------------
  void AddCorruptedUnstreamedAllowed(CATCGMObject *iObject);

  int IsCorruptedUnstreamedAllowed(CATCGMObject *iObject);

  void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
		CATCGMLinkType         iLinkType     = CatCGMDependancies,
		CATRCOLL(int)*         oSharedStatus = NULL,
		CATLISTV(CATString)*   oLinksString  = NULL);

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  Temporary Utility for LyingOn Security management
  //----------------------------------------------------------------------
  virtual  void CheckLyingOnAfterUnStream(CATCGMStream &Str) = 0;

  virtual void  ObjectWithLyingOn(CATCGMObject *cgmobject);

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  LyingOn Data for R12 stream
  //----------------------------------------------------------------------
  virtual  void StreamLyingOnData(CATCGMStream &Str) = 0; 
  virtual  void UnStreamLyingOnData(CATCGMStream     & Str,
                                   CATULONG32       iNbLyingOnDataToRead,
                                   const CATBoolean   iTryPartialLoad) = 0; 

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  Sharpness Data for R12 stream
  //----------------------------------------------------------------------
  virtual  void StreamSharpnessData(CATCGMStream &Str) = 0; 
  virtual  void UnStreamSharpnessData(CATCGMStream     & Str,
                                      CATULONG32       iNbSharpnessDataToRead,
                                      const CATBoolean   iTryPartialLoad) = 0; 

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to NCGM Document management
  //----------------------------------------------------------------------
  INLINE CATGemDoc *GetGemDoc() ; 
  void SetGemDoc(CATGemDoc *doc); 

  INLINE CATCGMDocument *GetCGMDocument() ; 
  void SetCGMDocument(CATCGMDocument *doc); 

  INLINE CATExtCGMGeom *GetExtCGMGeom();
  void SetExtCGMGeom(CATExtCGMGeom *ext);

  INLINE CATExtCGMReplay *GetExtCGMReplay();
  void SetExtCGMReplay(CATExtCGMReplay *ext);

  INLINE CATCGMChain *GetCATCGMChain();
  void SetCATCGMChain(CATCGMChain *ext);

  INLINE const CATRootSharedDataCGM  * GetDefinition() const;
  INLINE const CATTolerance          & GetToleranceObject()  const;

  virtual CATGeoFactory   *GetExplicitFactory() const = 0;

  static  CATCGMContainer *GetContainer(CATGeoFactory *iFactory, CATCGMMode iMode = CatCGMImplicit);

  INLINE CATCGMTempoULONGPTR *GetTempoULONGPTR() const;

  INLINE CATCGMUpDownStats* GetUpDownStats() const;
 
  //---------------------------------------------------------------------------
  // Internal USE
  //---------------------------------------------------------------------------
  void CheckUpStreamable( const CATCGMStreamVersion iTargetVersion, CATCGMObject* body, 
                          CATCGMObject* comp, CATCX_CHECKUP *report);

  virtual void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) ;

  //-------------------------------------------------------------------
  // should be called on :
  //    1/ every significant change to the container (without argument)
  // (i.e. when adding/removing objects, or altering objects descriptions)
  //    2/ container unstream (to restore the time read on the stream)
  //------------------------------------------------------------------------
  INLINE void SetOptimalLastModificationTime();

  INLINE int  IsTransientDirtyForMeasure() const;  
  INLINE void ResetTransientDirtyForMeasure(); 
  INLINE void SetTransientDirtyForMeasure(); 

  //---------------------------------------------------------------------------
  // Internal USE, 
  //---------------------------------------------------------------------------
  static CATBoolean CanNotBeRead(size_t DataLength, unsigned char* DataValue);
  
  void FillGraphWithAllObjects(CATCGMGraph &ioGraph); 
  
  void Clean_TempoULONGPTR() ;

  //-----------------------------------------------------------------------
  // INTERNAL ONLY  CLEANER
  //----------------------------------------------------------------------
  void SetCleanerReplaceMode(const short iReplaceMode); 

   //----------------------------------------------------------------------
   // Tools 
   //----------------------------------------------------------------------
   static void GetAllDependancies(const  CATLISTP(CATICGMObject) & iStarter, CATLISTP(CATICGMObject)   & oLinks); 


  //-------------------------------------------------------------------------
  // Pour Detection d'operation specifique sur la Factory 
  //    (Sauvegarde a partir du format V5R11)
  //-------------------------------------------------------------------------
  INLINE void        DefineIsDoing(const CATCGMFactoryStatus iSpecificOperation);
  INLINE CATBoolean  HasBeenDone(const CATCGMFactoryStatus iSpecificOperation);

   void Callback(CATICGMUnknown* Object, CATCGMEventCallback::Notification iNotif);

   //----------------------------------------------------------------------
   // Provoquer explicitement le chargement du DUAL
   //----------------------------------------------------------------------
  CATBoolean SucessullDualLoading();

   //----------------------------------------------------------------------
   // Gestion du unstream du container : iHowToLoad == 1 pour partiel, 
  //  iHowToLoad == 2 pour Full
   //----------------------------------------------------------------------
   void SetHowToLoadMode (int iHowToLoad);
   int GetHowToLoadMode ();

   //----------------------------------------------------------------------
   // Gestion table des AddRef "sauvages" CGMGlobalAddRef
   //----------------------------------------------------------------------
  void CGMGlobalAddRef(CATICGMObject * obj);
  void CGMGlobalRelease(CATICGMObject * obj);
  CATULONG32  CGMGlobalAddRef_GetUseCount(CATICGMObject * obj);
  CATBoolean HasCGMGlobalAddRef();

  INLINE CATULONG32 GetMaxTag() const;

   //----------------------------------------------------------------------
   // Do not use , stricly internal ( scale conversion )
   //----------------------------------------------------------------------
  void AdaptScale ( const CATPositiveLength & iNewModelSize );

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to NCGM Document management
  //----------------------------------------------------------------------
  virtual CATICGMUnknown     * GetContainerInterface() const;
  virtual CATICGMUnknown     * SetContainerInterface(CATICGMUnknown* Object);
 

  CATICGMObject* FindObjectFromTag(CATULONG32  tag, CATGeometricType iType = CATGeometryType);
   void FindObjectsFromTag(const CATLONG32 iNbObject, const CATULONG32  iTags[],  CATLISTP(CATICGMObject) &ioObjects );

   //---------------------------------------------------------------------------
   // Gestion du chainage des Persistent/Light/ToSave objects dans le container
   //---------------------------------------------------------------------------
   void InsertPersistentObject(CATCGMObject * Object, int Persistent_0_or_Light_1 = 0); 
   void RemovePersistentObject(CATCGMObject * Object, int Persistent_0_or_Light_1 = 0);
   void RemoveAllPersistentObjects();

protected:
  // Destructeur
  virtual ~CATCGMContainer(); 
 
  virtual CATBoolean IsStreamable( CATCGMStream        & Str,
                                   const CATCGMStreamVersion iTargetVersion, 
		                               CATBoolean & ioReversible ,
		                               CATLISTP(CATICGMUnknown) & oIncompatibles ) const;

  virtual CATCGMContainer *GetImplicitOfCCGMContainer() const;

  virtual int  RemovingObject(CATICGMObject * Object);  


  //----------------------------------------------------------------------
  // Table a acces rapide pour FindObjectFromTag
  //----------------------------------------------------------------------
   void QuickTagOpen(CATULONG32  Size =0); 
   void QuickTagInsert(CATULONG32  iTag, CATCGMObject* iObj, CATULONG32   Index);
   int  QuickTagSearch(CATULONG32  iTag, CATCGMObject* &Obj, CATULONG32  &Index); // 0 si echec
   //VUC: 2010-03-04
   int QuickTagRemove( CATCGMObject* iObj);
   void QuickTagClose(); 

   //----------------------------------------------------------------------
   // Gestion du chainage des objects dans le container
   //----------------------------------------------------------------------
   void ContainerChainInsert(CATCGMObject *newChild, int withTagComputation=1); 
   void ContainerChainRemove(CATCGMObject *newChild); 

  

   //----------------------------------------------------------------------
   // Chainage des containers
   //  IR A0651683 : Correction PCS LifeCycle avec numerous CATGeoFactory
   //     passage d'un chainage simple a chainage double 
   //----------------------------------------------------------------------
   CATCGMContainer         *_ChainNext;  
   CATCGMContainer         *_ChainPrevious;  
   static  CATCGMContainer *_ChainFirst; 


   //----------------------------------------------------------------------
   // Perfo  CATICGMEventPublisher
   //----------------------------------------------------------------------
   CATULONG32    _IsPublishing;

private:

  static int  CGMutexContainer(const CATBoolean iRemove, CATCGMContainer *container, const CATBoolean iUserClose); 

  static int  CGMRemoveContainer(CATCGMContainer *container, const CATBoolean iUserClose);  // RC=1 si deja elimine
  static void CGMInsertContainer(CATCGMContainer *container); 

 


  //----------------------------------------------------------------------
  // Gestion Echec Tag -> Objet ,  Reprise apres chargement en mode Light 
  //----------------------------------------------------------------------
  CATBoolean MustRetryLostTag(CATULONG32  tag);
 

  //VUC : 16-10-09 Pour le CheckIncrementalStream
  CATCGMObject* GetCounterPart(CATCGMContainer* NewOne,CATCGMObject* iObject);


  static  int              _RemovingStatus;

  // FirstChild identifie le chainage direct en Tag croissant des Objects
  // _NextChild est dedie a l'effacement
  CATCGMObject  *const _FirstChild;  

  CATCGMObject  *_NextChild;

  // Persistent/Light/ToSave object chain
  CATCGMObject       * _FirstPersistentObject;
  //CATCGMObject       * _FirstLightObject;
  //CATCGMObject       * _FirstToSaveObject;
 
  CATICGMUnknown     * _ContainerInterface;

  CATBoolean _ObjectDataStreamed;
  CATBoolean _ObjectDataStreamedKnotVectorU;
  CATBoolean _ObjectDataStreamedKnotVectorV;
  CATListPV* _pLType_LStrKey_LStrObjs;
  CATListPV* _pLKnotVectorUStrKey_LStrObjs;
  CATListPV* _pLKnotVectorVStrKey_LStrObjs;

  friend class CATRootContainerCGM; 
  friend class CATGeoFactoryCGM; 
  friend class CATCGMObject; 
  friend class CATCGMFusion; 

  friend class CATCGMTouchedGarbageCollector;
  friend class CATCGMTopoCXMODEL;
  friend class CATExtCGMEventPublisher;
  friend class CATCGMDebugImpl;

  friend class CATCGMGeomImpl;
  friend class CATCGMExtensionsForPart;
 
  friend class CATCGMStreamCGMImpl; // Extraction service transactionel et dedie persistence

  // Perfo PCS IR A0651683
friend ExportedByCATCGMFusion unsigned int HashKeyCATCGMContainer(CATCGMContainer* ipCGMObject);
friend ExportedByCATCGMFusion int CompareCATCGMContainer(CATCGMContainer* ipCGMObject1, CATCGMContainer* ipCGMObject2);

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMContainer(const CATCGMContainer &iCopy);
  CATCGMContainer& operator=(const CATCGMContainer &iCopy);

};

INLINE const CATRootSharedDataCGM *CATCGMContainer::GetDefinition() const
{  return _SHARED; }


INLINE const CATTolerance &CATCGMContainer::GetToleranceObject() const
{
  return ( ! _SHARED || !_SHARED->_GMTolerance )? ( ::CATGetDefaultTolerance() ): * _SHARED->_GMTolerance ;
}
//---------------------------------------------------------------------------
// INLINE functions : 
// CATCGMContainer::ComputeTag =>  donne un Numero Unique de l'element
//---------------------------------------------------------------------------
INLINE CATULONG32  CATCGMContainer::ComputeTag()
{
  CATULONG32  tag = 0;
  if ( _Container )
    tag = _Container->ComputeTag();
  else if ( _SHARED )
    tag = GetNextTag();
    //tag = ++_SHARED->_MaxTag;
  return tag;  
}

INLINE CATULONG32  CATCGMContainer::GetObjectsCount() const
{
  return _SHARED ?  _SHARED->_ObjectsCount : 0; 
}

INLINE CATULONG32  CATCGMContainer::GetTopologyCount() const
{
  return _SHARED ?  _SHARED->_TopologyCount : 0; 
}


INLINE CATULONG32  CATCGMContainer::GetOldestData() const
{
  return _SHARED ? _SHARED->_OldestData_CGMBuildVersion : 0; 
}

INLINE CATULONG32  CATCGMContainer::GetLastStream() const
{
  return _SHARED ? _SHARED->_LastStream_CGMBuildVersion : 0; 
}

INLINE CATULONG32  CATCGMContainer::GetSessionIdNumber() const
{
  return _SHARED ? _SHARED->_SessionId : 0; 
}

INLINE CATGemDoc *CATCGMContainer::GetGemDoc()    
{
  return _SHARED ? _SHARED->_CATGemDoc : NULL; 
}

INLINE CATCGMDocument *CATCGMContainer::GetCGMDocument()    
{
  return _SHARED ? _SHARED->_CATCGMDocument : NULL; 
}

INLINE CATExtCGMGeom *CATCGMContainer::GetExtCGMGeom()    
{
  return _SHARED ? _SHARED->_CATExtCGMGeom : NULL; 
}

INLINE CATExtCGMReplay *CATCGMContainer::GetExtCGMReplay()    
{
  return _SHARED ? _SHARED->_CATExtCGMReplay : NULL; 
}

INLINE CATCGMChain *CATCGMContainer::GetCATCGMChain()    
{
  return _SHARED ? _SHARED->_myCATCGMChain : NULL; 
}

INLINE CATULONG32 CATCGMContainer::GetMaxTag() const
{
  return _SHARED ? _SHARED->_MaxTag : 1; 
}

INLINE CATCGMTempoULONGPTR *CATCGMContainer::GetTempoULONGPTR() const
{
  return _SHARED ? _SHARED->_TempoULONGPTR : NULL; 
}

INLINE CATCGMUpDownStats* CATCGMContainer::GetUpDownStats() const
{
  return _SHARED ? _SHARED->_CATCGMUpDownStats : NULL; 
}

//-------------------------------------------------------------------------
// Pour Detection d'operation specifique sur la Factory 
//    (Sauvegarde a partir du format V5R11)
//-------------------------------------------------------------------------
INLINE void        CATCGMContainer::DefineIsDoing(const CATCGMFactoryStatus iSpecificOperation)
{
  if ( _SHARED )
    _SHARED->DefineIsDoing(iSpecificOperation);
}

INLINE CATBoolean  CATCGMContainer::HasBeenDone(const CATCGMFactoryStatus iSpecificOperation)
{
  return _SHARED ? _SHARED->HasBeenDone(iSpecificOperation) : TRUE; 
}

INLINE CATBoolean  CATCGMContainer::IsUnderIncrementalPersistencyManagement()
{
  return (_SHARED && _SHARED->_Differential_ToDelete) ? TRUE : FALSE ; 
}

// VUC : 16-10-09 Incremental Stream
INLINE CATBoolean CATCGMContainer::IsIncrementalStreamInitialized()
{
   return (_SHARED && _SHARED->_IncrementalGlobalData) ? TRUE : FALSE ; 
}

INLINE CATCGMIncrementalStreamGlobalData * CATCGMContainer::GetIncrementalGlobalData()
{
   return _SHARED ? _SHARED->_IncrementalGlobalData : NULL; 
}

//-------------------------------------------------------------------------
// SetOptimalLastModificationTime
//-------------------------------------------------------------------------
INLINE void CATCGMContainer::SetOptimalLastModificationTime()
{
  if ( ! _SHARED ) return;

  if ( CGA.IsUnstreamed == 1 )  return; // en cours d'Unstream, on ne fait rien

  if ( ! _SHARED->_RootFlags._CopyNeeded )
    _SHARED->_RootFlags._CopyNeeded = 1;

  if ( ! _SHARED->_RootFlags._DirtyForMeasure )
    _SHARED->_RootFlags._DirtyForMeasure = 1;
}

//--------------------------------------------------------------------------
// DirtyForMeasure ... Pour une gestion efficace d une evolution dans le LifeCycle d un Factory
//    --> Variation du nombre d objets
//    --> Variation sur le nombre d'elements persistants (Cf GenericNaming)
//    --> Variation sur l introduction des attributs (externes)
//-------------------------------------------------------------------------
INLINE int CATCGMContainer::IsTransientDirtyForMeasure() const  
{ return (_SHARED && _SHARED->_RootFlags._DirtyForMeasure ? 1 : 0); }

INLINE void CATCGMContainer::ResetTransientDirtyForMeasure()    
{  if (  _SHARED && _SHARED->_RootFlags._DirtyForMeasure ) _SHARED->_RootFlags._DirtyForMeasure = 0; }

INLINE void CATCGMContainer::SetTransientDirtyForMeasure()    
{ if (  _SHARED && ! _SHARED->_RootFlags._DirtyForMeasure )  _SHARED->_RootFlags._DirtyForMeasure = 1; }



#endif


