/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

#ifndef CATCGMStreamImpl_H_
#define CATCGMStreamImpl_H_

//=============================================================================
// DESCRIPTION : Class implementing CATCGMStream
//=============================================================================
// Apr.  05 HCN Creation                                                    HCN
// Nov.  09 VUC Optional argument for the UnStreamAttributesRead method : 
//              for IncrementalStream
// 19/06/19 NLD Ajout Init()
//=============================================================================

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
#include "CATMathStream.h"
#include "CATMathStreamImpl.h"
 

#include "YP0LOGRP.h"
#include "CATBoolean.h"
#include "CATMathStreamDef.h"
#include "CATCollec.h"
#include "CATListOfCATICGMObjects.h"

#include "CATGeometricObjectsErrors.h"
#include "CATGeometricObjectsInternalError.h"
#include "CATCGMNewArray.h"

#include "CATGeometryType.h"

#include "CATCGMStreamData.h"
#include "CATCGMPartialStreamData.h"
#include "CATMathInline.h"

#include "CATCGMStreamExtendedReplay.h"
#include "CATRootSharedDataCGM.h"
 
#include "LimitCompactInfoForIncStr.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif

class CATCGMStream;

class CATICGMObject;
class CATICGMUnknown;
class CATCGMAttribute;
class CATBaseUnknown;

class CATParamData;
class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;
class CATKnotVector;
class CATCurve;
class CATSurface;
class CATGeoFactory;
class CATICGMContainer;
class CATExtCGMReplay;
class CATCGMStreamAttrObj;
class CATCGMMapCATULONGPTR;
class CATStream;
class CATRootContainerCGM;
class CATCGMHashTable;
class CATCGMObject;
struct CATCGMHeaderObjectStream;
class CATCGMStreamCGMImpl;
class CATCGMSafeHashTable;
class CATCGMObject;
class CATExtGeoOperator;
class CATGeoPolyObjectsStreamManager;
class CATGeoPolyObjectsUnstreamManager;

class CATCGMObject;
 


/**
 *  Class defining the stream to use for the stream and unstream of a single geometric object.
 * <b>Role</b>: This stream class is specially designed to deal with a list of linked objects.
 * The list of linked objects must be written/read prior to any other write/read operation.
 * <br>This class is used when you define the stream or unstream of your own CGM attribute, but you only has
 * to use it as a CATMathStreamImpl. In fact, if you have linked objects, use @href CATCGMStreamAttribute#AddLink. 
 * and  the stream/unstream of your linked objects will be automatic.
 * @see CATMathStreamImpl
 */
class ExportedByYP0LOGRP CATCGMStreamImpl : public CATMathStreamImpl 
{
 public:
 


  virtual ~CATCGMStreamImpl();
  
  CATCGMNewClassArrayDeclare;

//-----------------------------------------------------------------------------
// Cast...
//-----------------------------------------------------------------------------
  
  virtual CATCGMStream* CastToCATCGMStream();

  virtual CATCGMStreamImpl* CastToCATCGMStreamImpl();

  virtual CATCGMStreamCGMImpl* CastToCATCGMStreamCGMImpl() = 0;

//-----------------------------------------------------------------------------
// Version...
//-----------------------------------------------------------------------------  
  
  CATULONG32 GetCGMBuildVersion();

//-----------------------------------------------------------------------------
// Position...
//-----------------------------------------------------------------------------

 /**
  * Returns the number of bytes that remains to read.
  * @return
  * The number of bytes still to read, considering what has been already read
  */
  size_t GetNumberOfBytesToRead() const;

//-----------------------------------------------------------------------------
// CATCrvParam...
//-----------------------------------------------------------------------------
  
  void WriteCrvParam(const CATCrvParam&, const char iLabelReserved[] = "");
  
  void ReadCrvParam(CATCrvParam& ioCrvParam, CATCurve*, const char iLabelReserved[] = "");
  
//-----------------------------------------------------------------------------
// CATCrvLimits...
//-----------------------------------------------------------------------------
  
  void WriteCrvLimits(const CATCrvLimits&, const char iLabelReserved[] = "");
  
  void ReadCrvLimits(CATCrvLimits& ioCrvLimits, CATCurve*, const char iLabelReserved[] = "");
  
//-----------------------------------------------------------------------------
// CATSurParam...
//-----------------------------------------------------------------------------
  
  void WriteSurParam(const CATSurParam&, const char iLabelReserved[] = "");
  
  void ReadSurParam(CATSurParam& ioSurParam, CATSurface*, const char iLabelReserved[] = "");

//-----------------------------------------------------------------------------
// CATSurLimits...
//-----------------------------------------------------------------------------
  
  void WriteSurLimits(const CATSurLimits&, const char iLabelReserved[] = "");
  
  void ReadSurLimits(CATSurLimits& ioSurLimits, CATSurface*, const char iLabelReserved[] = "");
 
//-----------------------------------------------------------------------------
// CATKnotVector...
//-----------------------------------------------------------------------------
  
  void WriteKnotVector(const CATKnotVector&, const char iLabelReserved[] = "");
  
  void ReadKnotVector(CATKnotVector& ioKnotVector, const char iLabelReserved[] = "");

  void WriteKnotVectorRegular(const CATKnotVector&, const char iLabelReserved[] = "");
  
  void ReadKnotVectorRegular(CATKnotVector& ioKnotVector, const char iLabelReserved[] = "");


  //-----------------------------------------------------------------------------
  // CATCGMReplay integration with explicit Factory integration ...
  //
  //    OpenFactoryForWrite - CloseFactoryForWrite : WriteListOfLinkedObjects
  //    OpenFactoryForRead  - CloseFactoryForRead  : WriteListOfLinkedObjects
  //-----------------------------------------------------------------------------

 /**
  * Writes a (partial or total) list of linked objects. 
  * <br>Refer to  @href CATCGMStreamImpl#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  */
  void WriteListOfLinkedObjects(const CATICGMObject* iObject, const CATLISTP(CATICGMObject)& iLinkedObjects, const char iLabelReserved[] = "",
                                const CATBoolean iAllowedNullObject = FALSE);

 /**
  * Reads the total list of linked objects.
  * @param ioLinkedObjects
  * The list of linked objects. This list does not need to be empty in order 
  * to make the concatenation easier.
  */
  void ReadListOfLinkedObjects(CATLISTP(CATICGMObject)& ioLinkedObjects, const char iLabelReserved[] = "", int iStaticLinkedObjectNb=0);

#ifdef CATIACGMR216Code
  /**
  * @nodoc @nocgmitf
  */
  void ReadListOfLinkedObjects(CATICGMContainer * iForcedFactory, 
                               CATLISTP(CATICGMObject)& ioLinkedObjects, const char iLabelReserved[] = "", int iStaticLinkedObjectNb=0);
#endif

  void OpenFactoryForWrite(CATICGMContainer* iFactory, size_t& oWhere, short& oLevel, 
                           CATBoolean iForExternalWeakLinks = FALSE);

  
  void CloseFactoryForWrite(const size_t iWhere, const short iLevel, 
                           CATBoolean iForExternalWeakLinks = FALSE);

  
  void OpenFactoryForRead(CATICGMContainer* iFactory, size_t& oWhere,short& oLevel, 
                           CATBoolean iForExternalWeakLinks = FALSE);

  
  void CloseFactoryForRead(const size_t iWhere, const short iLevel, 
                           CATBoolean iForExternalWeakLinks = FALSE);



 /** @nodoc
  * Only during the Stream/Unstream transaction,
  *  Returns a pointer to the assciated explicit CATGeoFactory 
  *  Dedicated to CATCGMStreamAttribute Stream/Unstream operations
  */
  CATICGMContainer* GetAssociatedContainer() const;

//-----------------------------------------------------------------------------
// Object...
//-----------------------------------------------------------------------------
    
  CATBoolean IsAllowedToStream(CATICGMUnknown* iICGMObject) const;

  void ResetToObjectUnstreaming();

 /**
  *  Prepares the object streaming.
  * <br>This function forces the order of write operations:
  * <ol>
  *    <li>Indicates the linked objects count for the objects to stream.
  *        <br>(thru a call to <tt>WriteLinkedObjectsCount</tt>)
  *        <br>
  *        <b>This step is mandatory, even if there is no link.</b>
  *    <li>Writes the list of linked objects for object to be streamed, combining :
  *    <ul>
  *        <li>call(s) to <tt>WriteListOfLinkedObjects</tt>,
  *        <li>call(s) to <tt>WriteObject</tt>.
  *    </ul>
  *    <li>Write other informations (numbers and strings).
  * </ol>
  * <br>It must be called anytime, even if there is no link. (use an empty list in such case)
  */
  INLINE void PrepareToObjectStreaming();

 /**
  *    Prepares the object unstreaming.
  *
  * <br>This function will force the order of read operations:
  * <ol>
  *    <li>Gets the linked objects for the objects to unstream:
  *    <ul>
  *        <li>Either read the linked objects count for object to be streamed.
  *            <br>(in one shot, thru a call to 'ReadListOfLinkedObjects').
  *            <br>Extract then only what you need: Do not make any assumptions on list's size,
  *                 as upcoming versions may add later linked objects to the modelization.
  *        <li>Either read the count, then read individually each linked object.
  *            <br>You must forecast to skip linked objects possibly added by upcoming versions.
  *            <br>(thru a call to 'ReadLinkedObjectsCount',
  *                 followed by as many calls as required to 'ReadObject',
  *                 ended by a call to 'SkipRemainingLinkedObjectsToRead').
  *    </ul>
  *        <br><b>This step is mandatory, even if there is no link.</b>
  *    <li>Read other informations (numbers and strings).
  * </ol>
  * <br>It must be called anytime, even if there is no link. (use an empty list in such case)
  */
  INLINE void PrepareToObjectUnstreaming();

  INLINE void ResetToObjectStart(size_t iObjectStart, size_t iObjectSize);

 /**
  * Prepares the stream to process an object.
  * <br>This resets the flags that control the order of read/write operations.
  * <br>It must be called before streaming/unstreaming an object.
  * @param iObjectSize
  * The size of the object to be unstreamed (useless when streaming).
  */
  INLINE void PrepareToProcessAnObject(size_t iObjectSize = 0);
 
    
  //-----------------------------------------------------------------------------
    // Returns the PolyhedralObjects Stream/Unstream Manager
  //-----------------------------------------------------------------------------
  virtual CATGeoPolyObjectsStreamManager   * GetGeoPolyObjectsStreamManager() = 0;
  virtual CATGeoPolyObjectsUnstreamManager * GetGeoPolyObjectsUnstreamManager() = 0;

 
//-----------------------------------------------------------------------------
// Linked Object  ( INTERNAL NCGM , do not used for CATCGMReplay) ...
//-----------------------------------------------------------------------------

 /**
  */
  void WriteLinkedObjectsCount(const CATCGMObject* iObject, CATULONG32 iLinkedObjectsCount, CATBoolean iStaticValue = FALSE);

 /**
  */
  void ReadLinkedObjectsCount(const CATCGMObject* iObject, CATULONG32& ioLinkedObjectsCount, int iStaticLinkedObjectNb = 0);

 /**
  * Writes a linked object.
  * <br>Refer to @href CATCGMStreamImpl#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  */
  void WriteObject(const CATICGMObject* iObject, CATICGMUnknown* iLinkedObject, const char iLabelReserved[] = "",
                   const CATBoolean iAllowedNullObject = FALSE);

  /**
  * Writes a linked object.
  * <br>Refer to @href CATCGMStreamImpl#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  */
  void WriteObject(const CATICGMObject* iObject, CATICGMUnknown** iLinkedObject, const CATLONG32 NbCell, const char iLabelReserved[] = "",
                   const CATBoolean iAllowedNullObject = FALSE);

 /**
  * Reads a linked object.
  * @param ioLinkedObject
  * Retrieves the current linked object.
  */
  void ReadObject(CATICGMUnknown   * & ioLinkedObject, 
                  const char           iLabelReserved[] = "", 
                  const CATBoolean     iAllowFactory = FALSE,
                  CATGeoFactory    *   iForcedFactory = NULL);

 /**
  * Skips over remaining linked objects to read.
  */
  void SkipRemainingLinkedObjectsToRead();

 /**
  * Skips over remaining informations to read.
  *
  * <br>(i.e. what follows the linked objects sequence)
  */
  void SkipRemainingInformationsToRead();

 /**
  * Resets the stream to raw behaviour.
  * <br>This removes checks on the stream use (i.e. when no object streaming/unstreaming).
  */
  INLINE void ResetToRawBehaviour();

//-----------------------------------------------------------------------------
// Format compact
//-----------------------------------------------------------------------------

  void WriteObjectTag(CATICGMObject* iLinkedObject, CATULONG32* ipBaseTag, const char iLabelReserved[] = "");

  void ReadObjectTag(CATULONG32& ioTag, CATULONG32* ipBaseTag, const char iLabelReserved[] = "");
  
  void ReadListOfLinkedObjectTags(CATULONG32* ioArrayTags, const CATLONG32 iNbObjects, CATULONG32 iMainObjectTag, const char iLabelReserved[] = "");
 
  void ReadListOfLinkedCommonDataObjects(int                      iNbCommonDataObjects,
                                         CATLISTP(CATICGMObject)& ioLinkedObjects,
                                         unsigned char&           ioSimilarityMask,
                                         const char               iLabelReserved[] = "");
 
  void WriteRelativeTag(const CATULONG32 & iReferenceTag, const CATULONG32 iNbTag, CATULONG32 iTargetTag[]);

  void ReadRelativeTag(const CATULONG32 & iReferenceTag, const CATULONG32 iNbTag, CATULONG32* oTargetTag);


//-----------------------------------------------------------------------------
// Gestion du nombre d'objets participant au Stream
//-----------------------------------------------------------------------------
  
  INLINE void ResetNumberOfObjects();
  
  INLINE void AddAnotherObject();
  
  INLINE CATULONG32 GetExpectedNumberOfObjects() const;

//-----------------------------------------------------------------------------
// CATBack
//-----------------------------------------------------------------------------
  
  INLINE short IsStreamingForBackwardCompatibility() const;
    
  INLINE void SetDedicatedToBackwardCompatibility(short isStreaming);

//-----------------------------------------------------------------------------
// Unstream by injection
//-----------------------------------------------------------------------------
   
  INLINE CATCGMMapCATULONGPTR* IsDedicatedToUnstreamByInjection() const;
  
  void SetDedicatedToUnstreamByInjection(CATCGMMapCATULONGPTR* iMapping);

//-----------------------------------------------------------------------------
// CGMReplay...
//-----------------------------------------------------------------------------
  
  INLINE CATExtCGMReplay* GetAssociatedCGMReplay();

  void SetAssociatedCGMReplay(CATExtCGMReplay* iReplay);

  //-----------------------------------------------------------------------------
  // Extended Run() management ...
  //     with cache management also on CATCGMStream
  //-----------------------------------------------------------------------------

  INLINE CATCGMStreamMultipleRun IsMultipleRun(CATCGMStreamExtendedReplay& ioMultipleRun);

  // dedicated for Operator implement inside WriteInput for dedicated save of variational parameters
  INLINE CATBoolean UnderExtendedReplay(CATCGMStreamExtendedReplay& ioParams);

  // Otherwise dedicated for Operator implement inside WriteInput with already saved variational parameters
  INLINE CATBoolean WithoutVariationalParameters(CATCGMStreamExtendedReplay& ioParams);
 

  // When saving variational parameters, must be followed by ResetExtendedReplay(); 
  void WriteExtendedReplay(CATExtGeoOperator *iReservedForAfterWriteInput, const CATCGMStreamExtendedReplay &iParams, const char iLabelReserved[] = "");
  // When loading variational parameters, must be followed by ResetExtendedReplay(); 
  void ReadExtendedReplay(CATCGMStreamExtendedReplay& ioParams, const char iLabelReserved[] = "");

  void       ResetExtendedReplay(CATExtGeoOperator *iReservedForAfterWriteInput = NULL ); 

  //-----------------------------------------------------------------------------
  // Internal
  //-----------------------------------------------------------------------------
  void       ResetWithoutVariationalParameters(); 


  //-----------------------------------------------------------------------------
  // Control Version and Compression Options
  //-----------------------------------------------------------------------------
  void StreamControlGet(CATCGMStreamVersion & iOldForceVersion,CATCGMStreamControl & iOldControl );
  void StreamControlWriteAndSet();
  void StreamControlReadAndSet();
  void StreamControlReset(const CATCGMStreamVersion iOldForceVersion,const CATCGMStreamControl & iOldControl );


  //-----------------------------------------------------------------------------
  // LoadingUnderExtendedRun management
  //-----------------------------------------------------------------------------
  INLINE void       SetLoadingUnderExtendedRun();
  INLINE void       ResetLoadingUnderExtendedRun();
  INLINE CATBoolean IsLoadingUnderExtendedRun();


  INLINE void        SetNoExpliciteWrite();
  INLINE CATBoolean  ExpliciteWrite();

  INLINE void        SetCATCGMChain();
  INLINE CATBoolean  IsCATCGMChain();


//--------------------------------------------------------------------------
// Stream partiel
//--------------------------------------------------------------------------
  void SetPartialStream(const CATLISTP(CATICGMObject)* Objects, CATCGMSafeHashTable* SafeHashTable, CATBoolean StoreIntoTable);

  CATICGMObject* ExtFindObjectFromTag(CATULONG32        iTag,
                                   CATGeometricType iType = CATGeometryType);

  //--------------------------------------------------------------------------
  // Rattrap
  //--------------------------------------------------------------------------
  virtual void  RegisterExceptionalRattrap(CATCGMObject * iCGMObject) = 0;

    
  //--------------------------------------------------------------------------
  // IncrementalStream : 
  //  returns TRUE if this CATCGMStreamImpl is used in Incremental Stream Mode
  //--------------------------------------------------------------------------
  virtual CATBoolean IsIncrementalStreamActivated() = 0;

  //--------------------------------------------------------------------------
  // IncrementalStream : 
  //  returns TRUE if this CATCGMStreamImpl is used during a check incrementalstream
  //--------------------------------------------------------------------------
  virtual CATBoolean IsIncrementalCheckActivated() = 0;

  virtual CATCGMIncrementalStreamGlobalData* GetIncrementalStreamGlobalData() = 0;

  virtual CATBoolean SpecificUnStreamForIncementalStream(CATCGMObject* Object, LimitCompactInfo& SupportObjectLimitInfo) = 0;

 
  //-----------------------------------------------------------------------------
  // Enhanced Persistency Management for Foreign Geometry...
  //----------------------------------------------------------------------------- 
  static const CATBoolean _EnhancedForeignManagement;

  INLINE CATBoolean IsPartialLoad();
  INLINE void       SetPartialLoad();

  INLINE CATBoolean IsComplementaryLoad();
  INLINE void       SetComplementaryLoad();
  INLINE void       ResetLoadMode();

  INLINE CATBoolean IsMProcContext();
  INLINE void       SetMProcContext();

  INLINE CATBoolean IsCheckSumActive();
  INLINE void       InactiveCheckSum();

  unsigned char     GetAuthenticatedMode();
  void              SetAuthenticatedMode(unsigned char iMode);

protected :
  

  //--------------------------------------------------------------------------
  //  Protected (For Geometrical private implementation)
  //      IR D0663181
  //--------------------------------------------------------------------------

  /**
  * Constructs CATCGMStreamImpl for stream operation (read and write acces are allowed).
  */
  CATCGMStreamImpl(CATCGMStream* ipItf);

  /**
  * Constructs CATCGMStreamImpl for read only stream operation.
  * @param iBuffer
  *  The memory area directly acceded for the read operation.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>.
  */
  CATCGMStreamImpl(void*         iBuffer,
    size_t        iSizeBuffer,
    CATCGMStream* ipItf);

  /**
  * Constructs CATCGMStreamImpl for write only stream operation.
  * @param ioFile
  * The stream on which the stream is saved.
  * @param iInitialNumberOfBytes
  *  The initial memory size of internal buffer in bytes.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt>.
  */
  CATCGMStreamImpl(ostream&         ioFile,
    size_t           iInitialNumberOfBytes,
    const CATBoolean iEnableByAddress,
    CATCGMStream*    ipItf);

  /**
  * Constructs CATCGMStreamImpl for read only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * <br>The first acces of the stream may be done with <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseWriteStreamHeader</tt>.
  */
  CATCGMStreamImpl(istream&      ioFile,
    CATCGMStream* ipItf);

  /**
  * Constructs CATCGMStreamImpl for read only or write only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStreamImpl.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  */
  CATCGMStreamImpl(const char*            iFilename,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

  /**
  * Constructs CATCGMStreamImpl for stream operation.
  * @param iInitialNumberOfBytes
  *  The initial number of bytes for internal buffer.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStreamImpl.
  */
  CATCGMStreamImpl(size_t                 iInitialNumberOfBytes,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

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
  CATCGMStreamImpl(CATStream&             iDirectStreaming,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

  /**
  * @nodoc
  * Constructs CATCGMStreamImpl for read only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read.
  * @param iSizeStream
  *  The size in bytes of <tt>iDirectStreaming</tt>.
  */
  CATCGMStreamImpl(CATStream&    iDirectStreaming,
    size_t        iSizeStream,
    CATCGMStream* ipItf);
 

 
//-----------------------------------------------------------------------------
// Gestion des attributs ..
//-----------------------------------------------------------------------------
  virtual void  ObjectWithSharpnessData(CATCGMObject *cgmobject) = 0;

   virtual void  ObjectWithLyingOnStream(CATCGMObject *cgmobject)  = 0;

//-----------------------------------------------------------------------------
// Checks...
//-----------------------------------------------------------------------------
  
  virtual void CheckLinksWrittenError() const;
  
  virtual void CheckLinksReadError() const;



protected :

  //-----------------------------------------------------------------------------
  // Donnees membres de la classe
  //-----------------------------------------------------------------------------
  CATCGMStreamData*           _pSTR;
  CATCGMPartialStreamData*    _pPartial; // Donnees stream partiel
  
  CATBoolean                  _NoExpliciteWrite;
  CATBoolean                  _IsCATCGMChain; // ?  

  CATBoolean                  _WithExtendedReplay; // ExtendedReplay 
  CATBoolean                  _WithoutVariationalParameters; // First ExtendedReplay
  CATBoolean                  _LoadingUnderExtendedRun; // First ExtendedReplay

  CATCGMStreamExtendedReplay  _ExtendedReplay; // ExtendedReplay 
  CATCGMStreamExtendedReplay  _ExtendedVariationalParameters; // First ExtendedReplay 
 
  
  static short                _HasInitAvailableStreaming; 

  CATBoolean                  _IsPartialLoad;
  CATBoolean                  _IsComplementaryLoad;

  CATBoolean                  _IsMProcContext;
  CGMAuthenticatedMode        _AuthenticatedMode;

private :

  static void InitAvailableStreaming();  

  void UnstreamInvalidOperationStatus();

  void UnstreamInvalidObjectOperation();
    
  friend class CATCGMObject;
  friend class CATCGMFusion;
  friend class CATCGMContainer;
  friend class CATExtCGMReplay;
  
  friend ExportedByYP0LOGRP void StreamAttributeDefs(CATCGMStreamImpl& Str);
  friend ExportedByYP0LOGRP void StreamAttributes(CATCGMStreamImpl& Str);
  friend ExportedByYP0LOGRP void StreamAttribute(CATCGMStreamImpl& Str, CATCGMAttribute* Attr);

 

private :

  /**
   * @nodoc
   */
   CATCGMStreamImpl(const CATCGMStreamImpl &iCopy);

  /**
   * @nodoc
   */
   CATCGMStreamImpl& operator=(const CATCGMStreamImpl &iCopy);

   void Init();
};

//-----------------------------------------------------------------------------
// PrepareToObjectStreaming
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::PrepareToObjectStreaming()
{
  _ObjectOperation = StreamObject;
}

//-----------------------------------------------------------------------------
// PrepareToObjectUnstreaming
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::PrepareToObjectUnstreaming()
{
   _ObjectOperation = UnstreamObject; 
}



//-----------------------------------------------------------------------------
// LoadingUnderExtendedRun management
//-----------------------------------------------------------------------------
INLINE void       CATCGMStreamImpl::SetLoadingUnderExtendedRun() 
{
  _LoadingUnderExtendedRun = TRUE; 
}

//-----------------------------------------------------------------------------
INLINE void       CATCGMStreamImpl::ResetLoadingUnderExtendedRun() 
{
  _LoadingUnderExtendedRun = FALSE; 
}

//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsLoadingUnderExtendedRun() 
{
  return _LoadingUnderExtendedRun; 
}

//-----------------------------------------------------------------------------
// SetNoExpliciteWrite : only for cvm 
//   we don't want to change the _explicit flag in cga object in writegeometryv5
// Query ExpliciteWrite : 
//   Used in CATCXStreamGeometryV5::writegeometryv5 to change the function of this method
//   for cvm : we don't want to change the flags on the saved objects
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::SetNoExpliciteWrite()
{
  _NoExpliciteWrite = TRUE;   //
}
 
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::ExpliciteWrite()
{
  return !_NoExpliciteWrite;
}

//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::SetCATCGMChain()
{
   _IsCATCGMChain = TRUE; 
}
 
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsCATCGMChain()
{
  return _IsCATCGMChain; 
}



//-----------------------------------------------------------------------------
// UnderExtendedReplay
//-----------------------------------------------------------------------------
 

INLINE CATCGMStreamMultipleRun CATCGMStreamImpl::IsMultipleRun(CATCGMStreamExtendedReplay& ioMultipleRun)
{ 
  if ( _WithExtendedReplay  ) 
  {
    if ( _WithoutVariationalParameters ) 
    { ioMultipleRun = _ExtendedReplay;    return CatCGMStreamMultipleRun_Create; }
    else  
    { ioMultipleRun = _ExtendedVariationalParameters;  return CatCGMStreamMultipleRun_Update; } 
  }
  else
  { ioMultipleRun = CATCGMStreamExtendedReplay();    return CatCGMStreamMultipleRun_Others; }
}
 

//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::UnderExtendedReplay(CATCGMStreamExtendedReplay& ioParams)
{
  if ( _WithExtendedReplay ) ioParams = _ExtendedReplay; return _WithExtendedReplay;  
}
 
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::WithoutVariationalParameters(CATCGMStreamExtendedReplay& ioParams)
{
   if ( _WithoutVariationalParameters ) ioParams = _ExtendedVariationalParameters; return _WithoutVariationalParameters;  
}
 
//-----------------------------------------------------------------------------
// PrepareToProcessAnObject
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::PrepareToProcessAnObject(size_t iObjectSize)
{
  if (_pSTR)
  {
    _pSTR->_ObjectStart     = GetCurrentPosition();
    _pSTR->_ObjectSize      = iObjectSize;
    _pSTR->_LinksToProcess  = 0;
    _pSTR->_ProcessedLinks  = 0;
  }
  
  _OperationStatus = ExpectingLinksCount;
}

//-----------------------------------------------------------------------------
// PrepareToProcessAnObject
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::ResetToObjectStart(size_t iObjectStart, size_t iObjectSize)
{
  SetCurrentPosition(iObjectStart);

  if (_pSTR)
  {
    _pSTR->_ObjectStart     = iObjectStart;
    _pSTR->_ObjectSize      = iObjectSize;
  }
  if ( _ObjectOperation == UnstreamObject )
    _OperationStatus = LinksCompleted ;
  
}

//-----------------------------------------------------------------------------
// ResetToRawBehaviour
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::ResetToRawBehaviour()
{
  _ObjectOperation = NotSpecified;
}

//-----------------------------------------------------------------------------
// ResetNumberOfObjects
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::ResetNumberOfObjects()
{
  if (_pSTR)
    _pSTR->_NumberOfObjects = 0;
}

//-----------------------------------------------------------------------------
// AddAnotherObject
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::AddAnotherObject()
{
  if (_pSTR)
    _pSTR->_NumberOfObjects++;
}

//-----------------------------------------------------------------------------
// GetExpectedNumberOfObjects
//-----------------------------------------------------------------------------
INLINE CATULONG32   CATCGMStreamImpl::GetExpectedNumberOfObjects() const
{
  if (_pSTR)
    return _pSTR->_NumberOfObjects;
  else
    return 0;
}

//-----------------------------------------------------------------------------
// IsStreamingForBackwardCompatibility
//-----------------------------------------------------------------------------
INLINE short CATCGMStreamImpl::IsStreamingForBackwardCompatibility() const
{
  if (_pSTR)
    return _pSTR->_IsStreamingForBackwardCompatibility;
  else
    return 0;
}

//-----------------------------------------------------------------------------
// SetDedicatedToBackwardCompatibility
//-----------------------------------------------------------------------------
INLINE void CATCGMStreamImpl::SetDedicatedToBackwardCompatibility(short isStreaming) 
{
  if (_pSTR)
    _pSTR->_IsStreamingForBackwardCompatibility = isStreaming ? 1 : 0;
}


//-----------------------------------------------------------------------------
// GetAssociatedCGMReplay : Gestion Document CGMReplay associee
//-----------------------------------------------------------------------------
INLINE CATExtCGMReplay* CATCGMStreamImpl::GetAssociatedCGMReplay()
{
  if (!_pSTR) CATThrowForNullPointerReturnValue(NULL);

  return _pSTR->_pAssociatedReplay;
}

//-----------------------------------------------------------------------------
// IsDedicatedToUnstreamByInjection
//-----------------------------------------------------------------------------
INLINE CATCGMMapCATULONGPTR* CATCGMStreamImpl::IsDedicatedToUnstreamByInjection() const
{
  if (_pSTR)
    return _pSTR->_ForUnstreamByInjection;
  else
    return NULL;
}
 
//-----------------------------------------------------------------------------
// IsPartialLoad/SetPartialLoad
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsPartialLoad()
{
  return _IsPartialLoad; 
}

//-----------------------------------------------------------------------------
INLINE void  CATCGMStreamImpl::SetPartialLoad()
{
  _IsPartialLoad = TRUE; 
}

//-----------------------------------------------------------------------------
// IsComplementaryLoad/SetComplementaryLoad
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsComplementaryLoad()
{
  return _IsComplementaryLoad; 
}
  
//-----------------------------------------------------------------------------
INLINE void  CATCGMStreamImpl::SetComplementaryLoad()
{
  _IsComplementaryLoad = TRUE;
}
 

//-----------------------------------------------------------------------------
INLINE void  CATCGMStreamImpl::ResetLoadMode()
{
  _IsPartialLoad       = FALSE; 
  _IsComplementaryLoad = FALSE; 
}

//-----------------------------------------------------------------------------
// IsMProcContext/SetMProcContext
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsMProcContext()
{
  return _IsMProcContext; 
}
  
//-----------------------------------------------------------------------------
INLINE void  CATCGMStreamImpl::SetMProcContext()
{
  _IsMProcContext = TRUE; 
}

//-----------------------------------------------------------------------------
// IsCheckSumActive/InactiveCheckSum
//-----------------------------------------------------------------------------
INLINE CATBoolean CATCGMStreamImpl::IsCheckSumActive()
{
  CATCGMStreamControl SingleStreamControl;
  if(IsMProcContext() || IsSingleStreamControl(SingleStreamControl) )
    return FALSE;
  else
    return TRUE;
}


#endif
