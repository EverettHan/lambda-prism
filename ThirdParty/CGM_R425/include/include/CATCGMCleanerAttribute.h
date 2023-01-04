/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//-----------------------------------------------------------------------------
// Usage :
//
// Ensemble des flags de regle CGMCleaner associés à un objet :
// 
// Avr 04 : Creation                                                        FDN
//=============================================================================

#ifndef CATCGMCleanerAttribute_H
#define CATCGMCleanerAttribute_H

#include "CATCGMStreamAttribute.h"                                 
#include "CATGeoClnIDs.h"       
#include "CATListPV.h"

class CATCGMCleanerAttribute;
class CATICGMObject;
class CATError;


ExportedByYP0LOGRP CATCGMCleanerAttribute*  CATCreateCheckAttribute(CATICGMObject * iObject);

class ExportedByYP0LOGRP CATCGMCleanerAttribute : public CATCGMStreamAttribute
{

public :

  // Definition of the attribute (constructor, destructor, stream etc...)
  CATCGMCleanerAttribute();
  ~CATCGMCleanerAttribute();

  CATCGMDeclareAttribute (CATCGMCleanerAttribute,CATCGMStreamAttribute);
  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);

  // Set/Unset/read if the rule is to skip
  void SetRuleToSkip(CATGeoClnIDs::RuleID iRuleID);
  void UnsetRuleToSkip(CATGeoClnIDs::RuleID iRuleID);
  CATBoolean IsRuleToSkip(CATGeoClnIDs::RuleID iRuleID);

  // Set/Unset/read if the rule is KO accroding to the object
  void SetRuleStatusKO(CATGeoClnIDs::RuleID iRuleID);
  void UnsetRuleStatusKO(CATGeoClnIDs::RuleID iRuleID);
  CATBoolean IsRuleStatusKO(CATGeoClnIDs::RuleID iRuleID);

private :

  // Definition of the rule flags. This struct MUST be 32 bits
  struct RuleFlag
  {
    unsigned ID       : 16; // must remain to 16
    unsigned ToSkip   : 1;
    unsigned IsKO     : 1;
    unsigned Libre    : 14; // reserve for future flags
  };

  // List of the rules flags
  CATListPV _RuleFlagList;

  // Read one rule in the list (= NULL if not in the list)
  CATCGMCleanerAttribute::RuleFlag * ReadRule(CATGeoClnIDs::RuleID iRuleID);

  // Get one rule in the list (create and initialise it if not present in the list)
  CATCGMCleanerAttribute::RuleFlag * GetRule(CATGeoClnIDs::RuleID iRuleID);

  // Init the flags of a rule
  void InitFlags(RuleFlag * iRF);
};

#endif
