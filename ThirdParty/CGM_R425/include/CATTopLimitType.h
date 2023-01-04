#ifndef CATTopLimitType_H
#define CATTopLimitType_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The behavior of an extremity of the extrusion.
 * @param  CatLimOffsetFromProfile
 * The extremity is offsetted from the initial profile.
 * @param  CatLimUntil
 * The profile is extruded until the specified geometry or topology.
 * @param  CatLimNextAlongAxis
 * The profile is extruded until the first complete cut with the trimming body.
 * @param  CatLimLastAlongAxis
 * The profile is extruded until the last complete cut with the trimming body.
 * @param CatLimThruNextAlongAxis
 * The profile is extruded until the first complete cut, or the next, if  
 * the first one does not define an extrusion thru the trimming body. 
 */
enum CATTopLimitType 
{ 
  CatLimOffsetFromProfile = 0, 
  CatLimUntil             = 1, 
  CatLimNextAlongAxis     = 2,  
  CatLimLastAlongAxis     = 3, 
  CatLimThruNextAlongAxis = 4
};

#endif


