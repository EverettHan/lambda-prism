/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATCGMStreamCGMImpl_H_
#define CATCGMStreamCGMImpl_H_
//=============================================================================
// DESCRIPTION : Class implementing CATCGMStreamImpl
//=============================================================================
// Apr.  09     Creation
// Oct.  09 VUC IncrementalStream : _LocalData
// Nov.  09 VUC Remove of the withTass argument of the stream methods 
//  (now use the method SetCleanAuthorization)
// Oct.  15 DPS PolyhedralObjects Stream/Unstream management
// Nov.  15 DPS PolyhedralObjects management rearchitecture
// 19/06/19 NLD Ajout Init()
//=============================================================================

#include "CATCGMStreamImpl.h"
#include "ExportedByCATCGMFusion.h"
#include "CATCGMStreamVersion.h"
#include "CATCGMContainer.h"
#include "CATCGMVersionDefinition.h"
#include "CATCGMStream.h"
#include "CATCGMListOfCATULONGPTR.h"
// #include "CATCGMMapCATULONGPTR.h"
#include "CATOGM_STREAM.h"
#include "CATCGMPackedArrayOfPointers.h"
#include "CATListOfInt.h"
#include "CATOGMCoreSet.h"
#include "CATRootContainerCGM.h"
#include "CATRootSharedDataCGM.h"

class CATCGMObjectHashTable;
class CATCGMContainer;
class CATRootSharedDataCGM;
class CATCGMStream;
class CATCGMContainer;
class CATGeoBehavior;
class CATCGMDebugImpl;
class CATCGMContainer;
class CATCGMObject;
class CATCGMIncrementalStreamLocalData;
class CATCGMGeomImpl;
class CATCGMStreamAttribute;
class CATCGMAttributeDef;
class CATCGM_STREAM;
class CATHashDico;
class CATWakeUpGMUI;
class CATGeometry;
class CATGeoPolyObjectsStreamManager;
class CATGeoPolyObjectsUnstreamManager;

class CATCGMStreamCGMImpl;
extern "C" { typedef void CATWakeUpGMUI_BootType(CATCGMStreamCGMImpl *iCATCGMStreamCGMImpl); }  

#include "CATListOfCATCGMStream.h"
#include "CATListOfCATCGMObjects.h"
//#include "CATCGMIncrementalStreamLocalData.h"

//#define DisablePolyObjectsInCGMStream

/**
*  Class defining the stream to use for the stream and unstream of a single geometric object.
* <b>Role</b>: This stream class is specially designed to deal with a list of linked objects.
* The list of linked objects must be written/read prior to any other write/read operation.
* <br>This class is used when you define the stream or unstream of your own CGM attribute, but you only has
* to use it as a CATMathStreamImpl. In fact, if you have linked objects, use @href CATCGMStreamAttribute#AddLink. 
* and  the stream/unstream of your linked objects will be automatic.
* @see CATMathStreamImpl
*/
class ExportedByCATCGMFusion CATCGMStreamCGMImpl : public CATCGMStreamImpl 
{
public:

   
  //-----------------------------------------------------------------------------
  // Gestion des attributs ..
  //-----------------------------------------------------------------------------
  virtual void  ObjectWithSharpnessData(CATCGMObject *cgmobject) ;

  virtual void  ObjectWithLyingOnStream(CATCGMObject *cgmobject ) ;
  //---------------------------------------------------------------------------
  // Transient Management of LyingOn 
  //---------------------------------------------------------------------------

  CATCGMObjectHashTable      * _ObjectsWithLyingOnUnStreamed; 

  //---------------------------------------------------------------------------
  // Gestion des objets avec SharpnessData au Stream/UnStream 
  //---------------------------------------------------------------------------

  CATCGMObjectHashTable      * _ObjectsWithSharpnessDataForStream; 
  CATCGMHashTable            * _SharpnessDataUnStreamed;

  //---------------------------------------------------------------------------
  // Gestion des CATCGMStreamAttribute au Stream/UnStream 
  //---------------------------------------------------------------------------

  CATCGMHashTable            * _AttributesUnStreamed; 


  CATCGMListOfCATULONGPTR    * _OrderedListofObjectsWithLyingOn; 

  //-----------------------------------------------------------------------------
  // CATPart persistency Management 
  //-----------------------------------------------------------------------------

  //
  // CATPart persistency Management 
  //
  void Serialize_CGMGeom(       CATCGMStream          & Str,
                          const CATCGMStreamVersion     iVersionToSave,
                          const CATRootSharedDataCGM  * iShared,
                          const CATCGMStreamControl   * pOriginalStreamControl = NULL);

  //
  // NCGM persistency Management 
  //
  void Serialize_AllContents(       CATCGMStream          & Str,
                              const CATRootSharedDataCGM  * iShared,
                              const CATCGMStreamVersion     iWantingVersion,
                              const CATCGMStreamControl   * pOriginalStreamControl = NULL);

  //
  // CATPart/NCGM persistency Management 
  //
  void Unserialize_CGMGeom(       CATCGMStream                & Str,
                                  CATCGMUnserialize             iHowToLoad,
                            const CATRootSharedDataCGM        * iShared,
                                  CATBoolean                    RealtryPartialLoad,
                                  CATCGMListOfCATULONGPTR     * oIncrementalTags);

  //
  // Incremental persistency Management
  //
  void Unserialize_Incremental(      CATLISTP(CATCGMStream)  & Str,
                               const CATRootSharedDataCGM   *  iShared);

  void Serialize_Incremental(      CATCGMStream          & Str,
                             const CATRootSharedDataCGM  * iShared,
                             const CATCGMStreamVersion     iWantingVersion,
                                   CATBoolean              iFirstSave);


  //
  // Warm Start (AutoSave & Multi process)
  //

  void Unserialize_Injection(       CATCGMStream               & Str,
                                    CATCGMUnstreamByInjection  * iUnstreamByInjection ,
                              const CATRootSharedDataCGM       * iShared,
                                    CATCGMListOfCATULONGPTR    * oIncrementalTags,
                              const CATBoolean                 avoidAnyRattrap   = FALSE);


  //-----------------------------------------------------------------------------
  //     
  // Extract/Save Partial (CGMReplay like, NoTass, Same Factory)
  //     No Tass, No CATBack
  //-----------------------------------------------------------------------------

  void Serialize_Federators(      CATCGMStream              & Str,
                            const CATLISTP(CATICGMObject)   & iFederators,
                            const CATCGMStreamVersion         iWantingVersion,
                            const CATLISTP(CATICGMObject)   * iLightFederators = NULL,
                            const CATBoolean                  iAlreadySetPartialStream = FALSE,
                            const CATCGMStreamControl       * pOriginalStreamControl = NULL);

  //-----------------------------------------------------------------------------
  // VUC : 2009-11-3
  // Enables/Disables garbage collector functionalities of the stream
  // by default the cleaning steps are executed 
  //-----------------------------------------------------------------------------

  INLINE void SetCleanAuthorization(CATBoolean iIsAuthorized);
  INLINE CATBoolean IsCleanAuthorized();


  //-----------------------------------------------------------------------------
  // Access to the PolyhedralObjects Stream/Unstream Manager
  //-----------------------------------------------------------------------------
  virtual CATGeoPolyObjectsStreamManager * GetGeoPolyObjectsStreamManager();
  virtual CATGeoPolyObjectsUnstreamManager * GetGeoPolyObjectsUnstreamManager();


public :
  INLINE void SetDifferedWrite(CATBoolean iIsAuthorized);
  INLINE CATBoolean IsWriteDiffered();
  INLINE void GetDifferedWrite (CATLISTP(CATICGMObject) &objects);
  INLINE void AddDifferedWrite (CATLISTP(CATICGMObject) &ibjects);

  INLINE void SetDifferedRead(CATBoolean iIsAuthorized, CATGeoFactory* iReadFactory);
  INLINE CATBoolean IsReadDiffered();
  // INLINE void GetDifferedRead (CATListOfInt & otags );
  //INLINE void AddDifferedRead (CATULONG32  * itags, int inumber);
  INLINE CATGeoFactory* GetDifferedReadFactory ();
  //INLINE void AddDifferedRead (int [] itags, int inumber);

  // 
  INLINE void SetWithPartialManagementOfUnexpectedLost();
  INLINE CATBoolean IsWithPartialManagementOfUnexpectedLost();


private :

  CATLISTP(CATICGMObject) _DifferedWrite;
  CATBoolean              _WriteDiffered;
  //CATListOfInt _DifferedRead;
  CATBoolean              _ReadDiffered;
  CATBoolean              _WithPartialManagementOfUnexpectedLost;

  
  CATGeoFactory* _ReadFactory;
public :
  //-----------------------------------------------------------------------------
  //  Sets/Gets for IncrementalStream        (see VUC)
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // VUC : 16-10-09
  // returns TRUE if this CATCGMStreamCGMImpl is used in IncrementalStream Mode
  //-----------------------------------------------------------------------------
  INLINE CATBoolean IsIncrementalStreamActivated();

  INLINE CATCGMIncrementalStreamLocalData* GetIncrementalLocalData();

  //-----------------------------------------------------------------------------
  // VUC: 2009-12-3
  // returns TRUE if this CATCGMStreamCGMImpl is used during an IncrementalStream Check
  // whether it is using incrementalstream or not
  //-----------------------------------------------------------------------------

  INLINE CATBoolean IsIncrementalCheckActivated();
  INLINE void SetIncrementalCheckActivated(CATBoolean);

  //-----------------------------------------------------------------------------
  // VUC: 2010-02-05
  // sets a list of federators on the incrementalstream 
  // use only with incrementalstream 
  //-----------------------------------------------------------------------------

  void SetIncrementalFederatorsList(CATLISTP(CATCGMObject) &iBodies);

  // YL3
  INLINE CATCGMIncrementalStreamGlobalData* GetIncrementalStreamGlobalData();

  CATBoolean SpecificUnStreamForIncementalStream(CATCGMObject* Object, LimitCompactInfo & SupportObjectLimitInfo);

  //-----------------------------------------------------------------------------
  //    GreyBox (YL3)
  //-----------------------------------------------------------------------------
  CATBoolean IsGreyBox();

  static INLINE CATBoolean IsNewGreyBoxForbidden();
  static INLINE void       SetNewGreyBoxForbidden();

  //-----------------------------------------------------------------------------
  // TCX : 2010-02-05
  //  DuplicateCGMOperator
  //-----------------------------------------------------------------------------
  CATBoolean                    _IsDuplicateCGMOperator;
  CATCGMPackedArrayOfPointers * _KeptPackedObjects;

  //-------------------------------------------------------------------------------------------------------
  // Save current limit of some supports(curve or surface) during partial load to enable LimitCompact (YL3) 
  //-------------------------------------------------------------------------------------------------------
  void  SaveLimitData_Partial     (CATICGMObject * iObject, double * iLimits, CATLONG32 * iPartNumber);
  void  GetLimitData_Complementary(CATICGMObject * iObject, double * Limits,  CATLONG32 * PartNumber, CATBoolean & oIsStored);

  void ResetForMultipleFactories();

  //---------------------------------------------------------------------------
  //  GeomUtils
  //---------------------------------------------------------------------------
  void ActivateGeomUtil();
  CATBoolean IsGeomUtilActivated();
  void RegisterGeomUtil(short iType);
  void RegisterGeomUtil(short iType, unsigned char* value, CATULONG32 Tag);

private :

  void Init();
  //-----------------------------------------------------------------------------
  // Secure Version Header Management  Read/Write 
  //-----------------------------------------------------------------------------

  void ReadHeaderVersion( CATCGMStream  & Str, const short iStep_0Begin_1End, 
    CATGeoFactory * iFactory, 
    size_t  & ioWhere, short  & ioLevel,
    const CATCGMVersionDefinition * & VersionUsedToStream,
    size_t             InitialSize);

  void WriteHeaderVersion(  CATCGMStream  & Str, const short iStep_0Begin_1End,
    CATGeoFactory * iFactory,
    size_t  & ioWhere, short  & ioLevel,
    const CATCGMStreamVersion newMathStreamVersionNumber,
    const CATCGMStreamControl * pOriginalStreamControl = NULL);

  //-----------------------------------------------------------------------------
  // Elementary Object Write Management
  //-----------------------------------------------------------------------------

  /**
  * WriteHeadAndLinks
  */
  void  WriteHeadAndLinks(CATCGMHeaderObjectStream  & ioElemStream,  const short iType, CATCGMObject * iCGMObject, size_t  & owhereHeader);

  /**
  * WriteDataEnd
  */
  void  WriteDataEnd(CATCGMHeaderObjectStream  & ioElemStream, const short iType, CATCGMStream & Str, CATCGMObject * iCGMObject,
                     const size_t iwhereHeader, const CATBoolean iOldLinkedObjectStreamStage);


  /**
  * CreateObjectUnStream
  */
  void  CreateObjectUnStream( CATCGMContainer               * iContainer,
    CATCGMObject                * & newobjImpl,
    const CATCGMVersionDefinition     *   iVersion, 
    const int                             iNewTag,
    const CATCGMHeaderObjectStream      & ElemStream,
    int                             iShiftDumpIsActive);


  /**
  * UnStreamObject
  */
  void  UnStreamObject( CATCGMStream            & Str, 
    CATCGMContainer         * iContainer,
    short                     ObjType,
    CATCGMObject            * Object,
    CATLISTP(CATICGMObject)& ListDependencies,
    const CATCGMVersionDefinition * iVersion);



  //-----------------------------------------------------------------------------
  // Integration 
  //-----------------------------------------------------------------------------


  /**
  * @nodoc
  */
  virtual CATCGMStreamCGMImpl* CastToCATCGMStreamCGMImpl();

  /**
  * @nodoc
  */
  virtual ~CATCGMStreamCGMImpl();

  CATCGMNewClassArrayDeclare;


  /**
  * Constructs CATCGMStreamCGMImpl for stream operation (read and write acces are allowed).
  */
  CATCGMStreamCGMImpl(CATCGMStream* ipItf);

  /**
  * Constructs CATCGMStreamCGMImpl for read only stream operation.
  * @param iBuffer
  *  The memory area directly acceded for the read operation.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>.
  */
  CATCGMStreamCGMImpl(  void          * iBuffer,
    size_t          iSizeBuffer,
    CATCGMStream  * ipItf);

  /**
  * Constructs CATCGMStreamCGMImpl for write only stream operation.
  * @param ioFile
  * The stream on which the stream is saved.
  * @param iInitialNumberOfBytes
  *  The initial memory size of internal buffer in bytes.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt>.
  */
  CATCGMStreamCGMImpl(  ostream       & ioFile,
    size_t          iInitialNumberOfBytes,
    const CATBoolean      iEnableByAddress,
    CATCGMStream  * ipItf);

  /**
  * Constructs CATCGMStreamCGMImpl for read only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * <br>The first acces of the stream may be done with <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseWriteStreamHeader</tt>.
  */
  CATCGMStreamCGMImpl(  istream       & ioFile,
    CATCGMStream  * ipItf);

  /**
  * Constructs CATCGMStreamCGMImpl for read only or write only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStreamCGMImpl.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  */
  CATCGMStreamCGMImpl(  const char              * iFilename,
    const CATCGMStreamType    iAcces,
    const CATBoolean          iEnableByAddress,
    CATCGMStream            * ipItf);

  /**
  * Constructs CATCGMStreamCGMImpl for stream operation.
  * @param iInitialNumberOfBytes
  *  The initial number of bytes for internal buffer.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStreamCGMImpl.
  */
  CATCGMStreamCGMImpl(  size_t              iInitialNumberOfBytes,
    const CATCGMStreamType    iAcces,
    const CATBoolean          iEnableByAddress,
    CATCGMStream      * ipItf);

  /**
  * @nodoc
  * Constructs CATMathStreamImpl for read only or write only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read or writen.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStreamImpl.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  */
  CATCGMStreamCGMImpl(  CATStream         & iDirectStreaming,
    const CATCGMStreamType    iAcces,
    const CATBoolean          iEnableByAddress,
    CATCGMStream      * ipItf);

  /**
  * @nodoc
  * Constructs CATCGMStreamCGMImpl for read only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read.
  * @param iSizeStream
  *  The size in bytes of <tt>iDirectStreaming</tt>.
  */
  CATCGMStreamCGMImpl(  CATStream     & iDirectStreaming,
    size_t          iSizeStream,
    CATCGMStream  * ipItf);

  /**
  * RegisterExceptionalRattrap && TryExceptionalRattrap
  */
  void  RegisterExceptionalRattrap(CATCGMObject * iCGMObject);

  void  TryExceptionalRattrap(CATCGMStream& Str);

  void  ResetExceptionalRattrap();

  INLINE CATBoolean  WithExceptionalRattrap() const;

  //-----------------------------------------------------------------------------
  // Serialize/Unserialize : Contents  
  //-----------------------------------------------------------------------------

  void Serialize_Contents(  CATCGMStream            & Str,
    CATCGMContainer         * container,
    const CATCGMVersionDefinition * iVersion,
    CATICGMUnknown          * iPublishSession,
    const CATCGMSerializeSelect     iSelection,
    CATLISTP(CATICGMObject) * iFederators = NULL);

  void  Unserialize_Contents( CATCGMStream            & Str,
    CATCGMUnserialize         iHowToLoad,
    CATRootSharedDataCGM    * iShared,
    CATBoolean                tryPartialLoad,
    const CATCGMVersionDefinition * iVersion,
    CATCGMListOfCATULONGPTR * oIncrementalTags);

  void  Unserialize_ContentsFull( CATCGMStream            & Str,
    CATRootSharedDataCGM    * iShared,
    const CATCGMVersionDefinition * iVersion,
    CATULONG32                ObjectsCount,
    size_t                    oldFactoryLength,
    CATICGMUnknown          * pPublishObject);

  //-----------------------------------------------------------------------------
  // Unstream  incremental
  //-----------------------------------------------------------------------------

  //unstream contents of the increments
  void Unserialize_ContentsIncremental( CATCGMStream            & Str,
    CATRootSharedDataCGM    * iShared,
    const CATCGMVersionDefinition * iVersion,
    CATULONG32                ObjectsCount,
    size_t                    oldFactoryLength,
    CATICGMUnknown          * pPublishObject);  

  //-----------------------------------------------------------------------------
  // Light Special Steps 
  //-----------------------------------------------------------------------------

  void  Unserialize_ContentsLighPartial(  CATCGMStream            & Str,
    CATRootSharedDataCGM    * iShared,
    CATBoolean                tryPartialLoad,
    const CATCGMVersionDefinition * iVersion,
    CATULONG32                ObjectsCount,
    CATCGMListOfCATULONGPTR * incrementalOpen,
    size_t                    oldFactoryLength,
    CATICGMUnknown          * pPublishObject);

  void  Unserialize_ContentsLighComplementary(  CATCGMStream            & Str,
    CATRootSharedDataCGM    * iShared,
    CATBoolean                tryPartialLoad,
    const CATCGMVersionDefinition * iVersion,
    CATULONG32                ObjectsCount,
    size_t                    oldFactoryLength,
    CATICGMUnknown          * pPublishObject);

  //-----------------------------------------------------------------------------
  // Injection
  //-----------------------------------------------------------------------------

  //
  //  AutoSave and CATCGMStreamOperatorCGM::ReadObjects
  //

  void Unserialize_TrueInjection(CATCGMStream                   & Str,
    CATCGMUnstreamByInjection      * iUnstreamByInjection ,
    CATRootSharedDataCGM           * iShared,
    CATBoolean                       tryPartialLoad,
    const CATCGMVersionDefinition  * iVersion,
    CATCGMListOfCATULONGPTR        * oIncrementalTags,
    const CATBoolean                avoidAnyRattrap);

  void  Unserialize_ContentsInjection( CATCGMStream            & Str,
    CATCGMUnstreamByInjection               *iUnstreamByInjection ,
    CATRootSharedDataCGM    * iShared,
    const CATCGMVersionDefinition * iVersion,
    CATULONG32                ObjectsCount,
    size_t                    oldFactoryLength,
    CATICGMUnknown          * pPublishObject,
    const CATBoolean iMustUnstreamFactory,
    const CATBoolean                avoidAnyRattrap);

  //-----------------------------------------------------------------------------
  // Light Special
  //-----------------------------------------------------------------------------
  void  LightAbnormalMap(CATULONGPTR & iodxMAPPED, CATULONGPTR  iTag);
  void  LightAbnormalIndex(CATULONGPTR  iTag);

  //-----------------------------------------------------------------------------
  //  Serialize_Contents True  
  //-----------------------------------------------------------------------------

  void  Serialize_TrueContents( CATCGMStream            & Str,
    CATCGMContainer         * container,
    const CATCGMVersionDefinition * iVersion,
    const CATCGMSerializeSelect     iSelection,
    CATICGMUnknown          * PublishSession);

  CATCGMObject   *  Unserialize_TrueContents( CATCGMStream            & Str, 
    CATCGMContainer         * container,
    const size_t                    Index,
    const CATCGMVersionDefinition * iVersion, 
    const int                       WithLinkedObjectsFirst, 
    CATICGMUnknown          * pPublishObject,
    CATCGMHashTableWithAssoc * fullUnstreamMAPPING,
    const size_t                  * ipNextObjIdx ) ;

  //  unstream the true contents of only the objects that must be unstreamed(in incremental context), pass the others
  /* CATCGMObject   * Unserialize_TrueContents_Incremental(  CATCGMStream            & Str, 
  CATCGMContainer         * container,
  const size_t                    Index,
  const CATCGMVersionDefinition * iVersion, 
  const int                       withLinkedObjectsFirst, 
  CATICGMUnknown          * pPublishObject,
  CATCGMMapCATULONGPTR    * FullMapping,
  const size_t                  * ipNextObjIdx ) ;*/

  //unstream of the container in the incremental context
  void UnstreamContainerIncremental(CATCGMStream& Str,CATCGMContainer* container,const CATCGMVersionDefinition  * iVersion,CATICGMUnknown* pPublishObject);


  CATCGMObject   * Unserialize_TrueContentsOfAnObject(CATCGMStream                  & Str, 
    CATCGMContainer * container,
    const size_t                    Index,
    const CATCGMVersionDefinition * iVersion, 
    const int                       withLinkedObjectsFirst, 
    CATICGMUnknown                * pPublishObject,
    CATCGMHashTableWithAssoc      * FullMapping,
    const size_t                  * ipNextObjIdx,
    size_t        iDataSize,
    CATULONG32    iObjTag,
    short         iObjType) ;

  //-----------------------------------------------------------------------------
  //  Serialize_Contents sub dependancies
  //-----------------------------------------------------------------------------

  void Serialize_Tass(  CATCGMStream    & Str,
    CATCGMContainer * container);


  void  Serialize_ComputeDependancies(  CATCGMStream          & Str,
    const CATLISTP(CATICGMObject) * iFederators,
    const CATLISTP(CATICGMObject) * iLightFederators,
    CATCGMContainer       * container ,
    const CATCGMSerializeSelect   iSelection);

  void  Serialize_CATBack(  CATCGMStream        & Str, 
    CATCGMContainer     * container,
    CATCGMStreamVersion   newMathStreamVersionNumber, 
    CATCGMStreamVersion   partVersion );

  void Unserialize_Correct( CATCGMStream            & Str,
    CATCGMContainer         * container,
    CATRootSharedDataCGM    * iShared,
    const CATCGMVersionDefinition * iVersion);

  void  Unserialize_BigScaleRattrap(  CATCGMContainer       * container, 
    CATRootSharedDataCGM  * iShared );

  void  Unserialize_CATGeoClean( CATCGMContainer * container, CATGeoBehavior  & ioBehavior );
  void  Unserialize_UnExtrapolate( CATCGMContainer * container );




  CATCGMObject*  Unserialize_Object(  CATCGMStream            & Str,
    CATCGMContainer         * container,
    const CATCGMVersionDefinition * iVersion, 
    const size_t                    Idx,
    const int                       iNewTag,
    CATCGMHeaderObjectStream        & ElemStream);

  //unstream only the objects that must be unstreamed, pass the others
  CATCGMObject*  Unserialize_ObjectIncremental( CATCGMStream            & Str,
    CATCGMContainer         * container,
    const CATCGMVersionDefinition * iVersion, 
    const size_t                    Idx,
    const int                       iNewTag,
    CATCGMHeaderObjectStream        & ElemStream);

  //-----------------------------------------------------------------------------
  //  Select_Dependancies
  //-----------------------------------------------------------------------------

  void Select_Dependancies_All(CATCGMStream  & Str, CATCGMContainer * object);

  void Select_Dependancies_Persistent(CATCGMStream & Str, CATCGMContainer * object);

  void Select_Dependancies(CATCGMStream    & Str, CATCGMObject * object);

  //for Stream incremental : save only modified objects
  void Select_Dependancies_Modified(CATCGMStream & Str, CATCGMContainer * object);

  //return TRUE if the object is to be modified//depending on the modified of its dependances
  //and recursively do so for every dependance
  CATBoolean Select_Dependancies_Modified_Linked(CATCGMStream    & Str, CATCGMObject * object);

  //set every object as not modify
  void Select_Dependancies_Modified_Clean(CATCGMStream    & Str, CATCGMObject * object);

  //select the object in argument and not its dependancies 
  void Select_WithoutDependancies(CATCGMStream    & Str, CATCGMObject * object);

  //-----------------------------------------------------------------------------
  //  SpecificAttributes
  //-----------------------------------------------------------------------------
  void  Unserialize_SpecificAttributes(  CATCGMStream          & Str,
    CATRootSharedDataCGM  * iShared,
    CATCGMContainer       * container,
    CATBoolean              tryPartialLoad,
    const CATCGMStreamVersion     CurrentVersionStream,
    CATICGMUnknown        *  pPublishObject );

  void  Serialize_SpecificAttributes(  CATCGMStream          & Str,
    CATRootSharedDataCGM  * iShared,
    CATCGMContainer       * container,
    const CATCGMStreamVersion     newMathStreamVersionNumber,
    CATICGMUnknown        *  pPublishObject );


  void  Serialize_LyingOn(  CATCGMStream    & Str,
    CATCGMContainer * container,
    CATICGMUnknown  * pPublishObject );

  void  Serialize_SharpnessData(  CATCGMStream    & Str,
    CATCGMContainer * container,
    CATICGMUnknown  * pPublishObject );

  void  Unserialize_LyingOn(  CATCGMStream    & Str,
    CATCGMContainer * container,
    CATICGMUnknown  * pPublishObject,
    const CATRootSharedDataCGM *  iShared,
    CATULONG32  NbObjectsWithLyingOn,
    CATBoolean TryPartiallyLoadR12);


  void  Unserialize_SharpnessData(  CATCGMStream    & Str,
    CATCGMContainer * container,
    CATICGMUnknown  * pPublishObject,
    CATULONG32  NbObjectsWithSharpnessData,
    CATBoolean TryPartiallyLoadR12 );

  //-----------------------------------------------------------------------------
  //  CGMAttributes
  //-----------------------------------------------------------------------------

  void  Serialize_CGMAttributes(  CATCGMStream          & Str,
    CATRootSharedDataCGM  * iShared,
    CATCGMContainer       * container,
    const CATCGMStreamVersion     newMathStreamVersionNumber,
    CATICGMUnknown        *  pPublishObject );

  void Unserialize_Attributes_Foundation(  CATCGMStream          & Str,
    const CATCGMStreamVersion  CurrentVersionStream,
    CATCGMContainer       * container,
    CATICGMUnknown        * pPublishObject,
    CATRootSharedDataCGM  * iShared,
    CATBoolean              TryPartiallyLoadR12 );


  void Unserialize_Attributes_Applied(  CATCGMStream          & Str,
    const CATCGMStreamVersion        CurrentVersionStream,
    CATCGMContainer                * container,
    CATBoolean                       TryPartiallyLoadR12 );


  void Serialize_Attributes(  CATCGMStream    & Str,
    CATCGMContainer * container,
    CATICGMUnknown  * pPublishObject );


  //-----------------------------------------------------------------------------
  // Gestion des attributs ..
  //-----------------------------------------------------------------------------

  /** @nodoc
  *  intializes the data structure used by StreamAttributesToDO, StreamAttributesWrite
  */
  void StreamAttributesInit();

  /** @nodoc
  *  signales that /CurAttr is an attribute of CurElem and this Attribute will be streamed
  */
  void StreamAttributesToDo(CATICGMUnknown* CurElem, CATCGMAttribute* CurAttr);


  void Serialize_AttributesDefinitions(CATICGMUnknown* iPublishObject);
  void Serialize_AttributesContents(CATRootSharedDataCGM  * iShared, CATICGMUnknown* iPublishObject);
  void Serialize_WithAttributes(CATRootSharedDataCGM  * iShared, CATICGMUnknown* iPublishObject);

  void Unserialize_AttributesDefinitions(CATCGMContainer* iContainer );
  void Unserialize_AttributesContents(CATCGMContainer* iContainer,   const CATBoolean     iTryPartialLoad, 
                                      int & ioNbUnstreamForThisLoad, CATICGMUnknown* iPublishObject);
  void Unserialize_WithAttributes(CATULONG32  nummaxattr, CATULONG32  storedAttr, CATCGMContainer* iContainer,   const CATBoolean     iTryPartialLoad, 
                                  int & ioNbUnstreamForThisLoad, CATICGMUnknown* iPublishObject);

  //------------------------------------------------------------------------------------------------------ 
  //   iCode = 1 / Foreign
  //   iCode = 2 / Applicative
  //   iCode = 3 / according to { _CATWakeUpPendingTODO, _CATWakeUpPendingAttributeType }    set CATWakeUp=GM
  //------------------------------------------------------------------------------------------------------ 
  void Unserialize_AttributesValues(const short iCode,CATCGMStream & Str,const CATBoolean  iTryPartialLoad);
 
  virtual int NumberOfAttributesToStream(); 


  //-----------------------------------------------------------------------------
  // PolyObjects Stream/Unstream Management
  //-----------------------------------------------------------------------------
  void Select_PolyObjects_Dependencies(CATCGMStream & iStr, CATGeometry & iPolyGeometryCGM);
  void Serialize_PolyObjects(CATCGMStream & Str, const CATCGMStreamVersion &iNewMathStreamVersionNumber);
  void Unserialize_PolyObjects(CATCGMStream & Str, const CATCGMStreamVersion &iNewMathStreamVersionNumber);


  //-----------------------------------------------------------------------------
  // Other
  //-----------------------------------------------------------------------------

  void Unserialize_Nothing();
  void Unserialize_Unset();
  static void Slow_FindObjectFromTag();

  void Clear_AttributesManagement();

  //-----------------------------------------------------------------------------
  //  Common Tools / Debug / ...
  //-----------------------------------------------------------------------------

  void CleanTemporary(  CATCGMContainer * container, 
    short             i0Serialize_1Unserialize,
    short             iAvoidClean = 0);


  //-----------------------------------------------------------------------------
  //   Serialize_Debug
  //-----------------------------------------------------------------------------
  void Serialize_Debug(       CATCGMStream                  & Str,
                              int                             i_0Begin_1EndOkay_2EndKO,
                              CATCGMContainer               * container,
                        const CATCGMVersionDefinition       * iVersion,
                        const CATCGMContainer::CATCGMWrite    iWritemode,
                              CATICGMUnknown              * & PublishSession );


  void  Unserialize_IsFilenamed(  CATRootSharedDataCGM     * iShared );

  //-----------------------------------------------------------------------------
  //  ....
  //-----------------------------------------------------------------------------

  CATCGMObjectHashTable      * _ExceptionalRattraps; 

  CATCGMListOfCATULONGPTR    *  _LightObjects;

  //-----------------------------------------------------------------------------
  //  Incremental Context data for Incremental Unstream
  //-----------------------------------------------------------------------------
  //Unstream the Deleted Tags header of every increment
  void PrepareHeaderIncremental(CATLISTP(CATCGMStream)  & Str);

  //Stream/Unstream the list of tags of the deleted objects since last increment
  void ReadIncrementalHeader(CATCGMStream                & Str);

  void WriteIncrementalHeader(  CATCGMStream                & Str,
    const CATRootSharedDataCGM *  iShared);

  //Stream/Unstream the list of tags of the objects in the increment
  void WriteIncrementalObjectsHeader();
  void ReadIncrementalObjectsHeader();

  //append a tag to the list of objects to stream
  void AppendObjectTag(CATCGMObject* object);

  //deletes an object that shouldn't have been unstreamed : olk
  void RemoveObjectFromUnstream(CATCGMObject*& Object,CATCGMContainer* container);

  void LinkAll(CATLISTP(CATCGMStream) &List);

  void UnlinkAll(CATLISTP(CATCGMStream) &List);

  void SetIncrementalStreamActivated(CATBoolean iIsIncrementalStreamActivated);
  CATCGMStream* GetLastIncrement();  
  void GetIncrementalFederatorsList(CATLISTP(CATCGMObject) &Bodies);

  CATCGMIncrementalStreamLocalData* _IncrementalStreamLocalData;

  //TRUE if we are under an incrementalstream function(even for the first full increment)
  CATBoolean _IsIncrementalStreamActivated;

  //TRUE if this object is currently under incrementalstreamcheck
  CATBoolean _CheckIncrementalStreamActivated;
  //**//

  //authorizes/forbids the clean of unused objects
  CATBoolean _CleanAuthorized;


  //-----------------------------------------------------------------------------
  // Tableaux de Travail Locaux a la methode
  //-----------------------------------------------------------------------------
  int                        _NbAttr;
  int                        _NbAttrAvoided;

  CATCGMStreamAttribute * *  _Attr;
  size_t                  *  _AttrPosition;
  size_t                  *  _AttrLength;
  int                        _NbDef;
  CATCGMAttributeDef    * *  _Def;

  static CATBoolean          _NewGreyBoxForbidden;

  CATBoolean              *  _HasGreyBox;
  CATCGMStreamControl     *  _GreyBoxStrControl;

  CATWakeUpGMUI_BootType  * _CATWakeUpGMUI_Boot;
  CATHashDico             * _CATWakeUpDefTODO ;
  int                       _CATWakeUpPendingTODO ;
  CATUnicodeString          _CATWakeUpPendingAttributeType;
  short                   * _AttrJustUnstream; // array by _NbAttr 


  CATHashDico            *  _Recovery_MlcBB;

  //---------------------------------------------------------------------------
  //  Initial Root of persistency (First Open and 
  //---------------------------------------------------------------------------
  CATOGMCoreSet          *  _Serialize_PersistencyRoots;

  CATULONG64                _CheckSum;   


  //---------------------------------------------------------------------------
  //  Polyhedral objects Stream/Unstream delegation management
  //---------------------------------------------------------------------------
  CATGeoPolyObjectsStreamManager   * _PolyObjStreamManager;
  CATGeoPolyObjectsUnstreamManager * _PolyObjUnstreamManager;

  //---------------------------------------------------------------------------
  //  GeomUtils
  //---------------------------------------------------------------------------
  void       InitializeGeomUtilBuffer(CATCGMContainer* ipContainer);
  void       FinalizeGeomUtilBuffer(CATCGMContainer* ipContainer);
  void       ReadGeomUtilBuffer(size_t iNbBits, unsigned char * oCurrentBuffer);
  void       WriteGeomUtilBuffer(size_t iBufferIndex, size_t iNbBits, unsigned char * iCurrentBuffer);
  void       MappingBufferIndexWithTag(short iType, CATULONG32 iTag);
  short      GetGeomUtilSize(short iType);

  CATBoolean                _GeomUtilActivated;
  size_t                    _CurrentReadIndexGeoUtilBuffer;
  size_t                    _GeomUtilSize;
  unsigned char          *  _GeomUtilBuffer;
  size_t					_GeomUtilHashTabSize;
                     
  CATCGMHashTableWithAssoc *  _GeomUtilTagIndexMapping;
  CATCGMHashTableWithAssoc *  _GeomUtilMapping;


  /**
  * @nodoc
  */
  CATCGMStreamCGMImpl(const CATCGMStreamCGMImpl &iCopy);

  /**
  * @nodoc
  */
  CATCGMStreamCGMImpl& operator=(const CATCGMStreamCGMImpl &iCopy);



  /**
  * @nodoc
  */
  static void  CorruptedContainerThrow();


  /**
  * CreateObject  @nodoc
  */
  CATBaseUnknown*  CreateObject( CATCGMContainer * iContainer , int iType, const CATCGMVersionDefinition* ipVersionDef );


  /**
  * Serialize_Object  @nodoc
  */
  void Serialize_Object(CATCGMStream& Str,CATCGMObject * iCGMObject  );

  /**
  * @nodoc
  */
  friend class CATCGMDebugImpl;
  friend class CATCGMContainer;
  friend class CATCGMObject;
  friend class CATCGMGeomImpl;
  friend class CATCGM_STREAM;
  friend class CATWakeUpGMUI;
 
};

//-----------------------------------------------------------------------------
// WithExceptionalRattrap
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamCGMImpl::WithExceptionalRattrap() const
{
  return _ExceptionalRattraps ? TRUE : FALSE; 
}

//-----------------------------------------------------------------------------
INLINE CATCGMIncrementalStreamLocalData* CATCGMStreamCGMImpl::GetIncrementalLocalData()
{
  return _IncrementalStreamLocalData;
}

//-----------------------------------------------------------------------------
INLINE CATCGMIncrementalStreamGlobalData* CATCGMStreamCGMImpl::GetIncrementalStreamGlobalData()
{
  CATCGMIncrementalStreamGlobalData* result = NULL;
  if(_pSTR && _pSTR->_pAssociatedContainer)
  {
    CATRootContainerCGM* root = (CATRootContainerCGM*)_pSTR->_pAssociatedContainer->GetImplementCGM();
    if(root)
    {
      const CATRootSharedDataCGM* SharedData = root->GetDefinition();
      if(SharedData)
        result = SharedData->_IncrementalGlobalData;
    }
  }
  return result;
}

//-----------------------------------------------------------------------------
//VUC : 2009-11-3
INLINE CATBoolean  CATCGMStreamCGMImpl::IsCleanAuthorized()
{
  return _CleanAuthorized; 
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetCleanAuthorization(CATBoolean iIsAuthorized)
{
  _CleanAuthorized = iIsAuthorized; 
}

//-----------------------------------------------------------------------------
//JMA : 2010-04-15
INLINE CATBoolean  CATCGMStreamCGMImpl::IsWriteDiffered()
{
  return _WriteDiffered; 
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetDifferedWrite(CATBoolean iIsAuthorized)
{
  _WriteDiffered = iIsAuthorized; 
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::GetDifferedWrite (CATLISTP(CATICGMObject) &objects)
{
  objects.Append (_DifferedWrite);
}
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::AddDifferedWrite (CATLISTP(CATICGMObject) &ibjects)
{
  _DifferedWrite.Append (ibjects);
}
//-----------------------------------------------------------------------------
//JMA : 2010-04-25
INLINE CATBoolean  CATCGMStreamCGMImpl::IsReadDiffered()
{
  return _ReadDiffered; 
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetDifferedRead(CATBoolean iIsAuthorized, CATGeoFactory* iReadFactory)
{
  _ReadDiffered = iIsAuthorized; 
  _ReadFactory = iReadFactory;
}


//-----------------------------------------------------------------------------
//For JUZ : 2011-10-05
INLINE CATBoolean  CATCGMStreamCGMImpl::IsWithPartialManagementOfUnexpectedLost()
{
  return _WithPartialManagementOfUnexpectedLost; 
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetWithPartialManagementOfUnexpectedLost()
{
  _WithPartialManagementOfUnexpectedLost = TRUE; 
}
 


/*
INLINE void CATCGMStreamCGMImpl::GetDifferedRead (CATListOfInt & otags)
{
  otags.Append (_DifferedRead);
  _DifferedRead.RemoveAll ();
  _ReadFactory = NULL;
}
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::AddDifferedRead (CATULONG32  * itags, int inumber)
{
  int i;
  for (i = 0; i < inumber; i++)
    _DifferedRead.Append (itags [i]);
}
*/

//-----------------------------------------------------------------------------
INLINE CATGeoFactory* CATCGMStreamCGMImpl::GetDifferedReadFactory ()
{
  return _ReadFactory;
}

//-----------------------------------------------------------------------------
//VUC : 2009-11-23
INLINE CATBoolean CATCGMStreamCGMImpl::IsIncrementalStreamActivated()
{
  return (_IsIncrementalStreamActivated) ;
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetIncrementalStreamActivated(CATBoolean iIsActivated)
{_IsIncrementalStreamActivated = iIsActivated;}

//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamCGMImpl::IsIncrementalCheckActivated()
{
  return (_CheckIncrementalStreamActivated);
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetIncrementalCheckActivated(CATBoolean iIsActivated)
{
  _CheckIncrementalStreamActivated = iIsActivated;
}

 
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamCGMImpl::IsNewGreyBoxForbidden()
{
  return (_NewGreyBoxForbidden);
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamCGMImpl::SetNewGreyBoxForbidden()
{
  _NewGreyBoxForbidden = TRUE;
}

INLINE short CATCGMStreamCGMImpl::GetGeomUtilSize(short iType)
{
	short value = 0;
	if (iType == 510)
		value = 6;
	else if (iType == 521 && (IsScalableInteger() || IsNeutralEndian()))
		value = 4;
	else if (191 <= iType && iType <= 193)
		value = 4;
	return value;
}

INLINE CATBoolean CATCGMStreamCGMImpl::IsGeomUtilActivated()
{
	return _GeomUtilActivated;
}
#endif
