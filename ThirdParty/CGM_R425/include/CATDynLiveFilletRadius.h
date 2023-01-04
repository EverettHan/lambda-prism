// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : VB7 
//
//
//=============================================================================
// Creation VB7 april 2013
//
//=============================================================================

#ifndef CATDynLiveFilletRadius_H
#define CATDynLiveFilletRadius_H

#include "CATDynFilletRadius.h"
#include "CATManifoldBaseParameter.h"
#include "CATGMOperatorsInterfaces.h"

class CATHVertex;

class ExportedByCATGMOperatorsInterfaces CATDynLiveFilletRadius : public CATDynFilletRadius
{
public:

  // Constructor
  CATDynLiveFilletRadius(double iRadius,
                         CATHVertex* iHVertex,
                         CATCell*    iLocation  = NULL, 
                         double*     iRatio     = NULL,
                         CATAngle*   iDirection = NULL);

  // Destructor
  virtual ~CATDynLiveFilletRadius();

  CATHVertex* GetHVertex() const;
  void SetHVertex(CATHVertex* iHVertex);

  void SetDirection(const CATAngle* iDirection);

  CATDynLiveFilletRadius* GetAsCATDynLiveFilletRadius();

  // ----------------------------------------------------------------------------
  // Private section
  // ----------------------------------------------------------------------------
  void SetThroughJointContext(const int iContextIndex);
  int GetThroughJointContext() const;
  void SetManifoldParameterDescription(const CATManifoldParamDescription iDescription);
  CATManifoldParamDescription GetManifoldParameterDescription() const;

private:
  CATHVertex * _HVertex;
  int          _ThroughJointContext; // Not streamed data, for communication between Redo & rebuild DRep, indicates whether & which HVertex context has crossed a Joint
  CATManifoldParamDescription _Description;  // Not streamed data, for communication between Redo & rebuild DRep, indicates the description to be assigned to new local specs
};

#endif
