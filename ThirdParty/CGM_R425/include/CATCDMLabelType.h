//===================================================================
// COPYRIGHT Dassault Systemes 2017
//===================================================================
// CATCDMLabelType.h
//===================================================================
// definit le type de de contrat
//===================================================================

#ifndef CATCDMLabelType_H
#define CATCDMLabelType_H

#define CDMLabelType_Card 3
enum CDMLabelType : int // used for stream / unstream
{
  _CDMBasicLabel_ = 0, _CDMAxisLabel_=1, _CDMCenterLabel_=2, _CDMDirectionLabel_=3
};


#endif
