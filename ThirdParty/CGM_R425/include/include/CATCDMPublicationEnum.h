//===================================================================
// COPYRIGHT Dassault Systemes 2014
//===================================================================
// CATCDMPublicationEnum.h
//===================================================================
//
// Enumerators used by CDMConstraint and CDMEquation components

// They are copied from XVMConstraint original class, where they were already copied from CDS.
// The semantics attached to these values are unused by CDM, fully used by CDS, and partially used by
// the application (e.g. LiveShape), CDM acts as a repository model between the user interface and CDS

//===================================================================
#ifndef CATCDMPublicationEnum_H
#define CATCDMPublicationEnum_H

#include "CATCDMBaseInterfaces.h"
class CATUnicodeString;

class ExportedByCATCDMBaseInterfaces CATCDMPublicationEnum
{
public:
  
  enum PublishMode {
    pmUnknown=0
    ,pmLiveDriven = 1 
    ,pmLiveDriving
  };
  
  enum FunctionDescription {
    fdUnknown = 0
    ,fdRelationActivity = 1 // tous les paramètres concernant la relation compris entre 1 et 999
    ,fdConstraintDistanceParam = 1000                        // tous les paramètres concernant la contrainte compris entre 1000 et 1999
    ,fdConstraintLengthParam
    ,fdConstraintRadiusParam
    ,fdConstraintMinorRadiusParam
    ,fdConstraintMajorRadiusParam
    ,fdConstraintAngleParam
    ,fdConstraintApexAngleParam
  };

};

#endif
