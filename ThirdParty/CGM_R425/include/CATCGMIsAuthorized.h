/* -*-C++-*-*/
//=======================================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2000
// detection of the context : Replay ODT
//    --> integration of a special treatment
//
// If there is an InputData file corresponding to the nomenclature
//          Authorized.suffix
// then, a special treatment is applied,
// except if the current ODT  is explicitely identified in the authorized.suffix file.
//
//=======================================================================================
#ifndef CATCGMIsAuthorized_H
#define CATCGMIsAuthorized_H

#include <stddef.h>
#include <stdlib.h>
#include "CATMathConstant.h"
#include "CATBoolean.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ifstream;
#endif

class ExportedByCATMathematics CATCGMIsAuthorized
{
public :

  /**
   * HardTreatment : Compute is a deviation is detected between current context and previously stored referential
   *
   * @param suffix
   *   CurrentScenarioName
   *
   * @param DefaultMeansHard
   *   helpers for return value, in case no input data file of specified suffix is detected
   *
   * @param pMaximalValue
   *    As autorisation table is about (Name,IntegerValue)
   *        where integer value in referential file define the highest autorised value
   *    the current value is provided in that
   *
   * @param iWithScenarioName
   *   request to take into account the scenarii Name as completion name in the first column
   *
   * @param iAsDirectory
   *    helpers for fullName completion for the caracter between : Authorized and Suffix
   *    if iAsDirectory is set to FALSE :   "Authorized.${iSuffix}"
   *    if iAsDirectory is set to TRUE  :   "Authorized${ADL_ODT_SLASH}${iSuffix}"
   *
   *
   * @return
   *   +------------------+------------------+----------------------------------------+
   *   ! DefaultMeansHard !   pMaximalValue  !              Return value              !
   *   !                  !                  +-------------------+--------------------+
   *   !                  !                  ! If a line matches ! If no line matches !
   *   !                  !                  !    in the file    !    in the file     !
   *   +------------------+------------------+-------------------+--------------------+
   *   ! TRUE             ! NULL or not NULL ! FALSE             ! TRUE               !
   *   +------------------+------------------+-------------------+--------------------+
   *   ! TRUE or FALSE    ! NULL             ! FALSE             ! TRUE               !
   *   +------------------+------------------+-------------------+--------------------+
   *   ! FALSE            ! not NULL         ! TRUE              ! FALSE              !
   *   +------------------+------------------+-------------------+--------------------+
   */
    static CATBoolean HardTreatment(const char       *suffix,
                                   const CATBoolean  DefaultMeansHard = FALSE,
                                   size_t           *pMaximalValue    = NULL,
                                   const CATBoolean  iWithScenarioName = FALSE,
                                   const CATBoolean  iAsDirectory      = FALSE);

  /**
   * FrameworkWithHardTreatment : Detect if current validation is under control of a specified domain
   *   is associated to validation test framework with enhanced control.
   *
   *   See CATCGMIsAuthorized  for public usage
   *
   * @param iSuffix
   *   name of InputData file
   *
   * @param iopInputData
   *   if set, request for opening as  ifstream the input file
   *
   * @param iAsDirectory
   *    helpers for fullName completion for the caracter between : Authorized and Suffix
   *    if iAsDirectory is set to FALSE :   "Authorized.${iSuffix}"
   *    if iAsDirectory is set to TRUE  :   "Authorized${ADL_ODT_SLASH}${iSuffix}"
   *
   * @return
   *      TRUE if request succeeded <br>
   *      FALSE if request failed <br>
   */
   static CATBoolean FrameworkWithHardTreatment(const char  *suffix,
                                               ifstream *pInputData = NULL,
                                               const CATBoolean  iAsDirectory = FALSE );

};
#endif
