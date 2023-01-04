#ifndef CATGeoFactoryMngt_h
#define CATGeoFactoryMngt_h

// COPYRIGHT DASSAULT SYSTEMES  2009

/**
 */ 

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "IUnknown.h"
 
class CATGeoFactory;
class CATCGMStream;

/**  
 * Creates a new CGM container and loads its contents from a CATCGMStream.
 * <br>
 *
 * <b>Sample Buffer</b> : 
 * <pre>
 *   char   Buffer[] = ...; // To be defined 
 *   size_t BufferLength = XXX; // To be defined 
 *
 *   CATCGMStream StreamBuffer(Buffer,BufferLength) ; // ReadOnly Buffer
 *   CATGeoFactory* Factory = CATLoadCGMContainer(StreamBuffer);
 * </pre>
 *
 * <b>Sample from a File Name</b> : 
 * <pre>
 *   CATCGMStream   FileStream(FileName) ;
 *   CATGeoFactory* Factory = CATLoadCGMContainer(FileStream);
 * </pre>
 *
 * @param FileStream
 *   The stream from which the factory is read.
 * @return oFactory
 *   The pointer to the created geometry factory.
 */
ExportedByCATGMOperatorsInterfaces HRESULT CATLoadCGMContainer(CATCGMStream & iStreamArea, CATGeoFactory* & oFactory);
 


/**
 * Saves a CGM container into a CATCGMStream .
 * <br>
 *
 * <b>Sample Buffer</b> : 
 * <pre>
 *   CATCGMStream StreamBuffer(0,CatCGMStreamWriteOnly) ;
 *   CATSaveCGMContainer(Factory,StreamBuffer);
 *
 *   size_t BufferLength = StreamBuffer.GetLength();
 *   char * Buffer       = new char [BufferLength];
 *   if ( Buffer )
 *   {
 *     StreamBuffer.GetMemoryCopy(BufferLength,Buffer,BufferLength);
 *
 *     delete [] Buffer;
 *     Buffer = NULL;
 *   }
 * </pre>
 *
 * @param iFact
 *   The pointer to the factory to save.
 * @param ioStreamArea
 *   The stream on which the factory is saved.
 *
 */
ExportedByCATGMOperatorsInterfaces HRESULT  CATSaveCGMContainer(const CATGeoFactory* iFact,  CATCGMStream & ioStreamArea);
 


#endif
