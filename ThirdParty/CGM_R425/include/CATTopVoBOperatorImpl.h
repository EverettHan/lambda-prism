// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation JHN  23/05/2011
//
// VoB check creation. tool to check body result of operations. 
// This chack can allow us to know specific configurations of body which are not expected by customer
//
//=============================================================================

#ifndef __CATTopVoBOperatorImpl_h__
#define __CATTopVoBOperatorImpl_h__

// #include "CATListPOfCATCheckDiagnoses.h"
#include "CATTopVoBOperator.h"
#include "CATCGMVoBResult.h"

// class CATCheckDiagnosisList;
struct CATCGMVoBTool;
class CATExtTopOperator;


class CATTopVoBOperatorImpl: public CATTopVoBOperator
{
   CATCGMVirtualDeclareClass(CATTopVoBOperatorImpl);
public: // Methodes a usage externe

   //============================
   // Constucteur et destructeurs
   //============================

   CATTopVoBOperatorImpl(CATGeoFactory    * iFactory,
                  CATTopData       * iData,
                  CATExtTopOperator * iExtensible);

   virtual ~CATTopVoBOperatorImpl();
   virtual int RunOperator();
   virtual void SetJournalForCreation(CATCGMJournalList * iJournalObBodyToCheck);
   virtual void SetInputBodies(CATLISTP(CATBody) * iInputBodies);
   virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) & oLisOfResults);
   virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) & iFailureResults, CATBoolean iBlock, CATBoolean &iCompletion);
   virtual int RunInBackground();

   //======================================
   // Methodes specifiques a CATTopOperator
   //======================================


//   virtual void                  Dump(ostream& iOutput) const;

protected:
   /** @nodoc @nocgmitf */
    const CATString * GetOperatorId();

   /** @nodoc @nocgmitf */
   CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

   /** @nodoc @nocgmitf */
   void              WriteInput(CATCGMStream  & ioStream);

   /** @nodoc @nocgmitf */
   void              RequireDefinitionOfInputAndOutputObjects();

   /** @nodoc @nocgmitf */
   void              Dump(CATCGMOutput& os);

	 /** @nodoc @nocgmitf */
   void              DumpOutput(CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   void              WriteOutput(CATCGMStream &ioStream);

   /** @nodoc @nocgmitf */
   void              WriteTopOutput(CATCGMStream &ioStream);

   /** @nodoc @nocgmitf */
   CATTopCheckJournal* ReadTopOutput(CATCGMStream &Str);

   /** @nodoc @nocgmitf */
   CATBoolean        ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

   /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
	CATBoolean        ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   /** @nodoc @nocgmitf */
   void              DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

};

#endif
