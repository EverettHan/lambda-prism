// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//______________________________________________________________________
//
// CATCGMConvertMultiBodyToPoly.h
//
//______________________________________________________________________
//
// Usage notes:
//
// Bridge to convert multiple exact CATTopologies to polyhedral CATTopologies.
// The input topologies must be in the same CATGeoFactory.
// The factory given to CATCreateConvertMultiBodyToPoly can be different.
//
//______________________________________________________________________
//
// 20180116 WMN Creation
//______________________________________________________________________

#ifndef CATCGMConvertMultiBodyToPoly_h
#define CATCGMConvertMultiBodyToPoly_h

#include "CATGeometricObjects.h" // ExportedBy
#include "CATCollec.h"
#include "CATBoolean.h"

class CATICGMObject;
class CATLISTP(CATICGMObject);

/** @nodoc @nocgmitf (do not create any specific interface) */
class ExportedByCATGeometricObjects CATCGMConvertMultiBodyToPoly
{
public:

 /**
  * Destructor. Please, delete after use.
  */  
  virtual ~CATCGMConvertMultiBodyToPoly() {};

public:
  /**
   * Convert the given topologies.
   */
  virtual int ConvertTopologies()=0;

  /**
   * Add a topology to the set that will be converted.
   */
  virtual void AddTopology(CATICGMObject & iTopo)=0;

  /**
   * Add a list of topologies to the set that will be converted.
   */
  virtual void AddTopologyList(CATLISTP(CATICGMObject) & iTopoList)=0;

  /**
   * Clear the set of topologies to be converted.
   */
  virtual void ClearTopologyList()=0;

  /**
   * Specify a sag value for the conversion. Default value is 0.1mm at normal scale.
   */
  virtual void SetSag(double iSag)=0;

  /**
   * Allow invalid polyhedral CATBodies to be generated. Default value is FALSE.
   */
  virtual void AllowInvalidResults(CATBoolean iAllow)=0;

  /**
   * Retrieve the image of a topology. NULL if the input topology is an infinite object or if it could not be converted.
   */
  virtual CATICGMObject * ReadImage(CATICGMObject * iTopo)=0;
};

#endif // CATCGMConvertMultiBodyToPoly_H
