#ifndef CATSysGetLoadsList_H
#define CATSysGetLoadsList_H

#include <stdio.h>
#include "JT0TRCBK.h"
/****
 *** This service permits to obtain the list of current list loaded shared library
 *** objects
 *** 
 *** In the current implementation it is supported on windows platforms only
 *** 
 *** Internal clients of this service may find a sample of use in 
 *** tCATSysGetLoadsList.m in System.tst
 ***
 *** Please note that this service is tremendously expensive in CPU AND
 *** in elapse time
 *** So it must be used only internally and exclusively for debugging purposes
 ***
 ***  -------------------------------------------------------------------------
 ***  ARGUMENTS 
 ***  -------------------------------------------------------------------------
 ***  oNbList           (out)  (int)      if( !null) gives the number of
 ***                                      currently loaded shared libraries
 ***                                      
 ***  oNbNewLoads       (out)  (int)      if( !null) gives the delta  number
 ***                                      of libraries since last time
 ***                                      
 ***  oLoadList         (out)  (char ***) if( !null) returns with an array  of
 ***                                      load names corresponding to the 
 ***                                      library names
 ***                                      the pointer elements of this array 
 ***                                      must be be tested before use
 ***                                      This array is allocated in memory 
 ***                                      heap and must be deleted with
 ***                                      CATSysDelLoadsList
 ***                                      
 ***                                      The caller of CATSysGetLoadsList is
 ***                                      in charge of this deletion
 ***                                      
 ***  iFileOut          (in)    (FILE)    if( !null) CATSysGetLoadList will 
 ***                                      print the load names into the stream
 ***                                      pointed by iFileOut
 ***  -------------------------------------------------------------------------
 ***  RETURN VALUE
 ***  -------------------------------------------------------------------------
 ***  if  worked OK r                     returns 0
 ***  if  arguments were invalid          returns 1
 ***  if  allocations problem occured     returns 2
 ***  if  low level system calls occured  returns 3
 ***  if  unsupported                     returns 4
 *** 
 ****/

ExportedByJT0TRCBK int  CATSysGetLoadsList( int *oNbLibs,
                                            int *oNbNewLoads=NULL, 
                                            char ***oLoadList=NULL, 
                                            FILE *iFileOut=NULL,
                                            int iPrintFlags=0);
/****
 *** Free a load list allocated by CATSysGetLoadList
 *** reset the iLoadsList pointer on success
 ****/
ExportedByJT0TRCBK int  CATSysDelLoadsList( char ***iLoadsList ,int iNb);

#endif
