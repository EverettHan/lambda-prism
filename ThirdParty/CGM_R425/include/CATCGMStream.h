#ifndef CATCGMStream_H_
#define CATCGMStream_H_
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
#include "CATMathStream.h"       

#include "YP0LOGRP.h"
#include "CATCollec.h"
#include "CATListOfCATICGMObjects.h"
#include "CATMathInline.h"

class CATICGMObject;
class CATCurve;
class CATSurface;
class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;
class CATKnotVector;
class CATICGMContainer;
class CATCGMStreamImpl;
class CATCGMHashTable;

/**
*  Class defining the stream to use for the stream and unstream of a single geometric object.
* <b>Role</b>: This stream class is specially designed to deal with a list of linked objects.
* The list of linked objects must be written/read prior to any other write/read operation.
* <br>This class is used when you define the stream or unstream of your own CGM attribute, but you only has
* to use it as a CATMathStream. In fact, if you have linked objects, use @href CATCGMStreamAttribute#AddLink , 
* and  the stream/unstream of your linked objects will be automatic.
* @see CATMathStream
*/
class ExportedByYP0LOGRP CATCGMStream : public CATMathStream 
{
 public:
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  
 /**
  * Constructs CATCGMStream for stream operation (read and write acces are allowed).
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(CATCGMStreamImpl* ipImpl = NULL);

 /**
  * Constructs CATCGMStream for read only stream operation.
  * @param iBuffer
  *  The memory area directly acceded for the read operation.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(void*             iBuffer,
               size_t            iSizeBuffer,
               CATCGMStreamImpl* ipImpl = NULL);
  
 /**
  * Constructs CATCGMStream for write only stream operation.
  * @param ioFile
  * The stream on which the stream is saved.
  * @param iInitialNumberOfBytes
  *  The initial memory size of internal buffer in bytes.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt>.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(ostream&          ioFile,
               size_t            iInitialNumberOfBytes = 0,
               const CATBoolean  iEnableByAddress = FALSE,
               CATCGMStreamImpl* ipImpl = NULL);
  
 /**
  * Constructs CATCGMStream for read only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * <br>The first acces of the stream may be done with <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseWriteStreamHeader</tt>.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(istream&          ioFile,
               CATCGMStreamImpl* ipImpl = NULL);

 /**
  * Constructs CATCGMStream for read only or write only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStream.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(const char*            iFilename,
               const CATCGMStreamType iAcces,
               const CATBoolean       iEnableByAddress = FALSE,
               CATCGMStreamImpl*      ipImpl = NULL);

 /**
  * Constructs CATCGMStream for stream operation.
  * @param iInitialNumberOfBytes
  *  The initial number of bytes for internal buffer.
  * @param iAcces
  *  The kind of acces allowed on the CATCGMStream.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(size_t                 iInitialNumberOfBytes,
               const CATCGMStreamType iAcces,
               const CATBoolean       iEnableByAddress = FALSE,
               CATCGMStreamImpl*      ipImpl = NULL);

 /**
  * @nodoc
  * Constructs CATMathStream for read only or write only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read or writen.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStream.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(CATStream&             iDirectStreaming,
               const CATCGMStreamType iAcces,
               const CATBoolean       iEnableByAddress = FALSE,
               CATCGMStreamImpl*      ipImpl = NULL);

 /**
  * @nodoc
  * Constructs CATCGMStream for read only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read.
  * @param iSizeStream
  *  The size in bytes of <tt>iDirectStreaming</tt>.
  * @param CATCGMStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATCGMStream(CATStream&        iDirectStreaming,
               size_t            iSizeStream,
               CATCGMStreamImpl* ipImpl = NULL);

 /**
  * Destructor
  */
  virtual ~CATCGMStream();

 /**
  * Writes a CATCrvParam.
  * @param ioCrvParam
  * The CATCrvParam to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteCrvParam(const CATCrvParam& ioCrvParam, const char iLabelReserved[] = "");

 /**
  * Reads a CATCrvParam.
  * @param ioCrvParam
  * The read CATCrvParam.
  * @param ipCurve
  * The CATCurve with which the CATCrvParam is associated.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadCrvParam(CATCrvParam& ioCrvParam, CATCurve* ipCurve, const char iLabelReserved[] = "");
  
 /**
  * Writes a CATCrvLimits.
  * @param ioCrvLimits
  * The CATCrvLimits to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteCrvLimits(const CATCrvLimits& ioCrvLimits, const char iLabelReserved[] = "");
 
 /**
  * Reads a CATCrvLimits.
  * @param ioCrvLimits
  * The read CATCrvLimits.
  * @param ipCurve
  * The CATCurve with which the CATCrvLimits is associated.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadCrvLimits(CATCrvLimits& ioCrvLimits, CATCurve* ipCurve, const char iLabelReserved[] = "");
  
 /**
  * Writes a CATSurParam.
  * @param ioSurParam
  * The CATSurParam to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteSurParam(const CATSurParam& ioSurParam, const char iLabelReserved[] = "");

 /**
  * Reads a CATSurParam.
  * @param ioSurParam
  * The read CATSurParam.
  * @param ipSurface
  * The CATSurface with which the CATSurParam is associated.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadSurParam(CATSurParam& ioSurParam, CATSurface* ipSurface, const char iLabelReserved[] = "");
  
 /**
  * Writes a CATSurLimits.
  * @param ioSurLimits
  * The CATSurLimits to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteSurLimits(const CATSurLimits& ioSurLimits, const char iLabelReserved[] = "");

 /**
  * Reads a CATSurLimits.
  * @param ioSurLimits
  * The read CATSurLimits.
  * @param ipSurface
  * The CATSurface with which the CATSurLimits is associated.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadSurLimits(CATSurLimits& ioSurLimits, CATSurface* ipSurface, const char iLabelReserved[] = "");
    
 /**
  * Writes a CATKnotVector.
  * @param ioKnotVector
  * The CATKnotVector to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteKnotVector(const CATKnotVector& ioKnotVector, const char iLabelReserved[] = "");

 /**
  * Reads a CATKnotVector.
  * @param ioKnotVector
  * The read CATKnotVector.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadKnotVector(CATKnotVector& ioKnotVector, const char iLabelReserved[] = "");

 /**
  * Resets the stream to raw behaviour.
  * <br>This removes checks on the stream use (i.e. when no object streaming/unstreaming).
  */
  void ResetToRawBehaviour();

 /**
  * Opens the stream for writing the content of a CATGeoFactory.
  * @param iFactory
  *  A pointer to the CATGeoFactory to be written.
  * @param oWhere
  *  internal parameter you must give back to <tt>CloseFactoryForWrite</tt>.
  * @param oLevel
  *  internal parameter you must give back to <tt>CloseFactoryForWrite</tt>.
  * @param iForExternalWeakLinks
  *  Internal use only. Do not change the default value.
  */
  void OpenFactoryForWrite(CATICGMContainer* iFactory, size_t& oWhere, short& oLevel, CATBoolean iForExternalWeakLinks = FALSE);

 /**
  * Closes the stream after writing of the content of a CATGeoFactory.
  * @param iWhere
  *  internal parameter given by <tt>OpenFactoryForWrite</tt>.
  * @param iLevel
  *  internal parameter given by <tt>OpenFactoryForWrite</tt>.
  * @param iForExternalWeakLinks
  *  Internal use only. Do not change the default value.
  */
  void CloseFactoryForWrite(const size_t iWhere, const short iLevel, CATBoolean iForExternalWeakLinks = FALSE);

 /**
  * Opens the stream for reading the content of a CATGeoFactory.
  * @param iFactory
  *  A pointer to the CATGeoFactory to be read.
  * @param oWhere
  *  internal parameter you must give back to <tt>CloseFactoryForRead</tt>.
  * @param oLevel
  *  internal parameter you must give back to <tt>CloseFactoryForRead</tt>.
  * @param iForExternalWeakLinks
  *  Internal use only. Do not change the default value.
  */
  void OpenFactoryForRead(CATICGMContainer *iFactory, size_t &oWhere, short &oLevel, CATBoolean iForExternalWeakLinks = FALSE);

 /**
  * Closes the stream after reading of the content of a CATGeoFactory.
  * @param iWhere
  *  internal parameter given by <tt>OpenFactoryForRead</tt>.
  * @param iLevel
  *  internal parameter given by <tt>OpenFactoryForRead</tt>.
  * @param iForExternalWeakLinks
  *  Internal use only. Do not change the default value.
  */
  void CloseFactoryForRead(const size_t iWhere, const short iLevel, CATBoolean iForExternalWeakLinks = FALSE);

 /**
  * Returns the CATGeoFactory used with a OpenFactoryForWrite/CloseFactoryForWrite or OpenFactoryForRead/CloseFactoryForRead operation.
  * @return
  * A CATICGMContainer pointer to the associated CATGeoFactory.
  */
  CATICGMContainer* GetAssociatedContainer() const;

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
  void PrepareToObjectStreaming();

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
  void PrepareToObjectUnstreaming();

 /**
  * Prepares the stream to process an object.
  * <br>This resets the flags that control the order of read/write operations.
  * <br>It must be called before streaming/unstreaming an object.
  * @param iObjectSize
  * The size of the object to be unstreamed (useless when streaming).
  */
  void PrepareToProcessAnObject(size_t iObjectSize = 0);

 /**
  *  Writes the linked objects count. 
  * <br>Refer to the @href CATCGMStream#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  */
  void WriteLinkedObjectsCount(CATULONG32 iLinkedObjectsCount);

 /**
  * Reads the linked objects count. 
  * @param ioLinkedObjectsCount
  * The number of linked objects that are requsted by <tt>this</tt>.
  */
  void ReadLinkedObjectsCount(CATULONG32& ioLinkedObjectsCount);

 /**
  * Writes a linked object.
  * <br>Refer to @href CATCGMStream#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteObject(CATICGMObject* iLinkedObject, const char iLabelReserved[] = "");
  
 /**
  * Reads a linked object.
  * @param ioLinkedObject
  * Retrieves the current linked object.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadObject(CATICGMObject*& ioLinkedObject, const char iLabelReserved[] = "");
  
 /**
  * Writes a (partial or total) list of linked objects. 
  * <br>Refer to  @href CATCGMStream#PrepareToObjectStreaming method for explanations
  * about the write functions sequence.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteListOfLinkedObjects(const CATLISTP(CATICGMObject)& iLinkedObjects, const char iLabelReserved[] = "");

 /**
  * Reads the total list of linked objects.
  * @param ioLinkedObjects
  * The list of linked objects. This list does not need to be empty in order 
  * to make the concatenation easier.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadListOfLinkedObjects(CATLISTP(CATICGMObject)& ioLinkedObjects, const char iLabelReserved[] = "");

 /**
  * Skips over remaining linked objects to read.
  */
  void SkipRemainingLinkedObjectsToRead();

 /**
  * Writes an array of CGM objects.
  * @param geometry
  * A pointer to the array of CATICGMObjects to write.
  * @param iNbGeometry
  * The number of CATICGMObjects to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteGeometryV5(CATICGMObject** geometry, const CATLONG32 iNbGeometry, const char iReservedLabel[] = "");

 /**
  * Read an array of CGM objects.
  * @param geometry
  * A pointer to the array of read CATICGMObjects.
  * @param iNbGeometry
  * The number of CATICGMObjects to read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadGeometryV5(CATICGMObject** geometry, const CATLONG32 iNbGeometry, const char iReservedLabel[] = "");

 /**
  * Skips over remaining informations to read.
  *
  * <br>(i.e. what follows the linked objects sequence)
  */
  void SkipRemainingInformationsToRead();

 /**
  * Returns the number of bytes that remains to read.
  * @return
  * The number of bytes still to read, considering what has been already read
  */
  size_t GetNumberOfBytesToRead() const;

 /**
  * @nodoc
  */
  CATCGMNewClassArrayDeclare;


private :

  /** @nodoc  forbidden functionnality */
  CATCGMStream(const CATCGMStream&);

  /** @nodoc   forbidden functionnality */
  CATCGMStream& operator=(const CATCGMStream&);


};


#endif
