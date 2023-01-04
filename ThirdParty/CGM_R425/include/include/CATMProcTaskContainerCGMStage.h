// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcTaskContainerCGMStage_H
#define CATMProcTaskContainerCGMStage_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

#include "CATMProcTaskContainerCGM.h"

class ExportedByCATGeometricObjects_MProc CATMProcTaskContainerCGMStage : public CATMProcTaskContainerCGM
{
public:

  CATMProcTaskContainerCGMStage();

  virtual ~CATMProcTaskContainerCGMStage();

  CATBoolean TasksCancelled();

private:

  CATMProcTaskContainerCGMStage(const CATMProcTaskContainerCGMStage& iOneOf);
  CATMProcTaskContainerCGMStage& operator =(const CATMProcTaskContainerCGMStage& iOneOf);
};

#endif

#endif
