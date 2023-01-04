
#include "CATIACGMLevel.h" 

#ifndef CATExtrudeLimitName_H
#define CATExtrudeLimitName_H

#include "CATExtrudeLimitSide.h"
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

#include "CATGMOperatorsInterfaces.h"

/**
 * @nodoc
 * Structure to name and describe each intersection between a contextual limit and the extrusion
 * @attribute  _Side
 * Define whether the limit at this intersection has the same orientation than the extrusion direction or the opposite
 * @attribute  _IntersectionNumber
 * Define which intersection in the direction of extrusion is requested. The extruded profile is considered as the "origin".
 * If NULL, no intersection number is requested
 */
struct CATExtrudeLimitName
{
   CATExtrudeLimitSide _Side;
   int *               _IntersectionNumber;

   CATExtrudeLimitName () 
   {
      _Side = CATExtrudeLimitSideUnset;
      _IntersectionNumber = NULL;
   };
};

#ifdef CATIACGMR418CAA 
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMOperatorsInterfaces
#endif

/**
 * @nodoc
 * List of CATExtrudeLimitName
 */
CATLISTPP_DECLARE(CATExtrudeLimitName)
typedef CATLISTP(CATExtrudeLimitName) CATListPOfCATExtrudeLimitName;

#endif

