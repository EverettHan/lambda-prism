#ifndef CATCGMContainerMngt_h
#define CATCGMContainerMngt_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"
#include "CATGeometricObjects.h"
#include "CATMathDef.h"
#if defined (CATIAR417) && defined (CATIACGMR217CAA)
#include "CATCGMScaleCategoryDef.h"
#endif

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATGeoFactory;

/**
 * Creates a new CGM container.
 * @param iUnitInMeter
 *   WARNING: Always use the default value.
 * @return
 * The pointer to the created container which is a factory.
 */
ExportedByCATGeometricObjects CATGeoFactory* CATCreateCGMContainer (const CATPositiveLength iUnitInMeter=.001); 

#if defined (CATIAR417) && defined (CATIACGMR217CAA)
/**
 * Creates a new CGM container.
 * Note that the Extreme Scale capability is not available in V5. It is available in V6 from V6R417.
 * @param iScaleCategory
 *   Defines the ScaleCategory to be associated with the container to create
 * @return
 * The pointer to the created container which is a factory.
 */
ExportedByCATGeometricObjects CATGeoFactory* CATCreateCGMContainer (const CATCGMScaleCategory iScaleCategory);

#endif
/**  
 * Creates a new CGM container and loads its contents from a file.
 * <br>
 * <b>Sample Windows</b> : 
 * <pre>
 *   ifstream ifile(FileName, ios::binary ) ;
 *   CATGeoFactory* Factory = CATLoadCGMContainer(ifile);
 *   ifile.close();
 * </pre>
 * <b>Sample UNIX</b> : 
 * <pre>
 *   ifstream ifile(FileName) ;
 *   CATGeoFactory* Factory = CATLoadCGMContainer(ifile);
 *   ifile.close();
 * </pre>
 * @param iStreamArea
 * The stream from which the factory is read.
 * @return iFact
 * The pointer to the created geometry factory.
 */
ExportedByCATGeometricObjects CATGeoFactory* CATLoadCGMContainer   (istream& iStreamArea);


/**
 * Saves a CGM container into a file .
 * <br>
 * <b>Sample Windows</b> : 
 * <pre>
 *   ofstream ofile(FileName, ios::binary ) ;
 *   CATSaveCGMContainer(Factory,ofile);
 *   ofile.close();
 * </pre>
 * <b>Sample UNIX</b> : 
 * <pre>
 *   ofstream ofile(filename,ios::out,filebuf::openprot) ;
 *   CATSaveCGMContainer(Factory,ofile);
 *   ofile.close();
 * </pre>
 * @param iFact
 * The pointer to the factory to save.
 * @param ioStreamArea
 * The stream on which the factory is saved.
 *
 */
ExportedByCATGeometricObjects void           CATSaveCGMContainer   (const CATGeoFactory* iFact,  ostream& ioStreamArea);


/**
 * Closes a CGM container.
 * @param iFact
 * The pointer to the factory to close.
 */
ExportedByCATGeometricObjects void           CATCloseCGMContainer  (CATGeoFactory* iFact);


#endif
