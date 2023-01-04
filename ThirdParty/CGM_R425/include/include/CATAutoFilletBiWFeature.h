// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : RR
//
// DESCRIPTION  : Set of Ribbons. Class dedicated to fillet BiW parts.
// This class is dedicated to provide the application with the information necessary to create de fillet features.
//
//=============================================================================
// Creation RR April 2017
//=============================================================================
#ifndef CATAutoFilletBiWFeature_H
#define CATAutoFilletBiWFeature_H

#include "CATCGMVirtual.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATEdge.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListOfDouble.h"
#include "CATCGMNewArray.h"
#include "CATAutoFilletBiW_Defines.h"

class ExportedByCATGMOperatorsInterfaces CATAutoFilletBiWFeature: public CATCGMVirtual 
{
public:

  // Returns Edges to be input as Edges to be filleted to the Fillet Feature
  virtual void GetEdges(const int iType, ListPOfCATEdge& oEdgesToFillet) const = 0; // iType=0 => initial edges, iType=1 => propagated edges

  // Returns Edges to be input as Keep Edges to the Fillet Feature
  virtual  void GetKeepEdges(ListPOfCATEdge& oKeepEdges) const = 0;

  // Returns synchronized lists of radii and locations to be specified to the Fillet feature
  virtual void GetRadii(CATListOfDouble& oRadii, CATLISTV(CATMathPoint)& oRadiusPositions) const = 0;

  // Returns whether Variable Fillet Feature as to be used
  virtual CATBoolean IsConstant(double& oConstantRadius) const = 0;

  // Returns whether ImplicitKeepEdge Mode has to be assigned to the Fillet Feature
  virtual CATBoolean IsCliffEdge() const = 0;

  // Returns whether SetCreateZeroSetbackDiabolo Mode has to be assigned to the Fillet Feature
  virtual CATBoolean IsDiabolo() const = 0;

  // Returns the type of the first specification
  virtual CATAutoFilletBiW_SpecType GetType() const = 0;

  // Returns the name of the first specification
  virtual CATUnicodeString GetName() const = 0;

  // Dump contents to oStream for debug purpose
  virtual void Dump(CATCGMOutput& oStream) const = 0;

protected:
  CATAutoFilletBiWFeature();
  virtual ~CATAutoFilletBiWFeature();
private:
  CATCGMNewClassArrayDeclare; // Pool allocation
};

//----------------------------------------------------------------------------

#endif
