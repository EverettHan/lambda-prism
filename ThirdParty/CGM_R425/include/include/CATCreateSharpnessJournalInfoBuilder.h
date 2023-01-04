/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 * @fullreview  HCN TCX 02:10:18
 */

/* -*-C++-*- */

#ifndef __CATCreateSharpnessJournalInfoBuilder_H__ 
#define __CATCreateSharpnessJournalInfoBuilder_H__ 

//=============================================================================
// METHOD : CATCreateSharpnessJournalInfoBuilder
//
//
// DESCRIPTION : 
// Creation of an operator for differenciating contiguous G1 cells in a
// topological journal by adding different journal informations to
// the creation orders.
//
// Oct. 02  Creation                                                      HCN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopSharpnessJournalInfoBuilder.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"

class CATGeoFactory;
class CATTopData;
class CATBody;

/**
* Creates an operator for differenciating contiguous G1 cells in a
* topological journal by adding different journal informations to
* the creation orders.
* @param iTopData
* A pointer to the topological data containing the journal to be operated on.
* @param iBody
* A pointer to the body to be analysed.
* The body can be made of shell or wire domains.
* @param iJournalInfoInitMode
* The way the added CATCGMJournalInfo values are initialised.
* <dl><dt>CATTopSharpnessJournalInfoBuilder::CATJournalInfo_Next</dt><dd> Starts at (the maximum value found in the journal + iJournalInfoStep) or 1.
*     <dt>CATTopSharpnessJournalInfoBuilder::CATJournalInfo_Value</dt><dd> Starts at iJournalInfoInitValue </dl>
* @param iJournalInfoInitValue = 0,
* Used to initialise the added CATCGMJournalInfo values if iJournalInfoInitMode
* is set to CATTopSharpnessJournalInfoBuilder::CATJournalInfo_Value.
* @param iJournalInfoStep
* Used to increment the added CATCGMJournalInfo values.
* @param iMinSharpAngle
* Minimum angle value considered as SHARP, in rad.
* @return
* The pointer to the created operator. You must <tt>delete</tt> this operator after use.
*/
ExportedByCATTopologicalObjects
CATTopSharpnessJournalInfoBuilder* CATCreateSharpnessJournalInfoBuilder(
  CATTopData*                                               ipTopData,
  CATBody*                                                  ipBody,
  CATTopSharpnessJournalInfoBuilder::CATJournalInfoInitMode iJournalInfoInitMode = CATTopSharpnessJournalInfoBuilder::CATJournalInfo_Next,
  CATLONG32                                                      iJournalInfoInitValue = 0,
  CATLONG32                                                      iJournalInfoStep = 1,
  CATAngle                                                  iMinSharpAngle = CATTopSharpAngle);


#endif






