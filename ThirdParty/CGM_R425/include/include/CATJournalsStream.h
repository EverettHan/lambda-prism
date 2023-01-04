#ifndef CATJournalsStream
#define CATJournalsStream

//**************************************************************************************************************
// CATJournalsStream.h
//
// Utilities to stream a CATCGMJournalList.
//
//**************************************************************************************************************
// 2010 WEEK 15 CREATION                                                                                LD2
//**************************************************************************************************************
#ifndef NULL
#define NULL 0
#endif

#include "ExportedByGeometricObjects.h"

class CATGeoFactory;
class CATCGMJournal;
class CATCGMJournalList;
class CATCGMOutput;
class CATCGMStream;

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

//----------------------------------------------------------------------------------
// int CATJournalRead(CATGeoFactory * iFactory,
//                    CATCGMJournalList * oParent,
//                    istream & iStream,
//                    CATCGMOutput * oErrors = NULL);
//
// iFactory = the factory where to find elements
// oParent = the output journal
// iStream = the input stream
// oErrors = if evaluated, the error message if reading was impossible
// 
// return 1 if reading was possible
// return 0 if reading was impossible
//----------------------------------------------------------------------------------

/** @nodoc @nocgmitf */
ExportedByGeometricObjects int CATJournalRead(CATGeoFactory      * iFactory,
                                              CATCGMJournalList  * iParent,
                                              istream            * iStream,
                                              CATCGMOutput       * oErrors = NULL,
                                              CATCGMStream       * iTextualJRef = NULL);

ExportedByGeometricObjects int CATJournalRead(CATGeoFactory      * iFactoryForFirst,
                                              CATGeoFactory      * iFactoryForLast ,
                                              CATCGMJournalList  * iParent,
                                              istream            * iStream,
                                              CATCGMOutput       * oErrors = NULL,
                                              CATCGMStream       * iTextualJRef = NULL);
  
//----------------------------------------------------------------------------------
// int CATJournalWrite(CATCGMJournal * iJournal,
//                     ostream & iStream,
//                     CATCGMOutput * oErrors = NULL);
//
// iJournal = the input journal
// oStream = the output stream
// oErrors = if evaluated, the error message if writing was impossible
// 
// return 1 if writing was possible
// return 0 if writing was impossible
//----------------------------------------------------------------------------------

/** @nodoc @nocgmitf */
ExportedByGeometricObjects int CATJournalWrite(CATCGMJournal * iJournal,
                                               ostream       * iStream,
                                               CATCGMOutput  * oErrors = NULL,
                                               CATCGMStream  * iTextualJRef = NULL,
                                               short iIsInternalJournal = 0);

#endif

