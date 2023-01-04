
#ifndef CATLISTV_CATechMeta_H_
#define CATLISTV_CATechMeta_H_

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    GMTk journaling idea is to collect an history of operations
*        in one zip auto-described file with data meaningfull for a GM support.
*    It enables some preliminary analysis of a scenario focusing on GM domain.
*     (forcasting availability inside CGMOFF/CGMPRJ workspace is about collect of end week 42 of year 2010)
* 
*    Objective is to ease some debug/support with application based upon GMTk.
*        by mean of an auto-described zip files containing a all-in-one list of GM operations or data.
*     Remarks 1) not all GM operations may have implemented GMTkJournaling mecanisms (with underlining CGMReplay file).
*     Remarks 2) GMTkJournaling is also gathering information about scenarios
*                   (some statistics on I/O operations, or intermediate operation data (CATCX_NCGM))
* 
*   About some known limitations : structure of zip may changed at any software iteration.
*       -each type of file has its own data compatibility management (NCGM,CGMReplay)
*       -CSV file has no defined compatibility management 
* 
1)	What is CGMTkJournaling technology ?
       CGMTkJournaling is a collaboration tool aims to ease support 
               between an application software and prerequisite GM functionalities with developers ready to provide answers.
       CGMTkJournaling main purpose is to enable partial replay of scenario  
              by a set of stand-alone (generally one shot run) GM operations.
       CGMTkJournaling is technics based on data exchange (self described zip file suffixed *.CATechSet.zip)
              rather than software sample extractions,
               this is a result of complex objects and algorithms underlining the running operations.

2)	What is old about CGMTkJournaling technology  ?
       CGMTkJournaling incorporates traces of previous technological tools
            "CATCX_NCGM" (1998) for some services (3D Boolean CutBodies for instance)
            "CGMReplay" (2000) for CGM operators
            "CATPhoenix" (2008) for some mesh operations (but with very partial restrictive reuse)

      CGMTkJournaling address data which can be attached documents in maintenance, but does not address at all
            internal debugging introspection (checkpoint, textual or graphical representations)
            internal delivery process (ODT referential, checking inputs and outputs, …) 

3)	What is new about CGMTkJournaling technology ?

     Functionnality is provided through A.P.I (small S.D.K, see chapter 5) 
         -> no more any environnement variable.
         -> for internal GM, interactive functionnality is demonstated through c:cgm\S.O.S 
          
     CGMTkJournaling captures as all-in-one set  the heterogeneous history of events/operations
          -> conceptual interfaces has been developed to capture the generalization to make it simple to use.

     CGMTkJournaling runs from commercial packaging 
         -> it induces some limitations:
              as legacy Debug NCGM,CGMReplay workbench unavailable
              as Visualisation A.P.I are not available to make a presentation of result
              as XML parser is under debate 

4)	What are provided materials ?
              
     CGMtkJournalingWriter.cpp :  it shows simply how journaling is start/stop/save/empty from an in-process management
           (Data_Site.tst\CATCGMtkJournalingWriter.m\src\CGMtkJournalingWriter.cpp)

     CGMtkJournalingReader.cpp :  it shows how stored journaling is recovered and replayed again
           (NewTopologicalObjects\CATCGMtkJournalingReader.m\src\CGMtkJournalingReader.cpp)
*/
#include "CATCGMKernel.h"

class CATechMeta;
 
/** ------------------------------------------------------------------------
 *      System/PublicInterfaces/CATLISTV_Declare.h 

              CtorFromArrayVals
              CtorFromArrayPtrs
              AppendList
              InsertAfter
              InsertBefore
              InsertAt
              ReSize
              Locate
              RemoveValue
              RemoveList
              RemovePosition
              RemoveDuplicatesExtract
              RemoveDuplicatesCount
              eqOP
              neOP
              leOP
              geOP
              ltOP
              gtOP
              Compare
              Replace
              Swap
              QuickSort
              ArrayVals
              ArrayPtrs
              NbOccur
              Intersection
              ApplyMemberFunct
              ApplyMemberFunctConst
              ApplyGlobalFunct

 ------------------------------------------------------------------------ */

#include "CATLISTV_Clean.h"

#define CATLISTV_Append
#define CATLISTV_Locate
#define CATLISTV_QuickSort
#define CATLISTV_ReSize
#define CATLISTV_AppendList

#include "CATLISTV_Declare.h"
 

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCGMKernel

CATLISTV_DECLARE(CATechMeta)


typedef CATLISTV(CATechMeta) CATechMetas;

 
#endif
