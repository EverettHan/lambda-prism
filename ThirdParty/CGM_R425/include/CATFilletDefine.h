#ifndef CATFilletDefine_H
#define CATFilletDefine_H

// COPYRIGHT DASSAULT SYSTEMES  2013

/**
* @CAA2Level L1
* @CAA2Usage U1
*/

//================================================================================

// --- December 2012 ---
// Created by QF2

// new data definitions for BoneFilletCGM


enum CATFilletType
{
  CATFilletIsUnknown = 0,
  CATFilletIsBitangent = 1,
  CATFilletIsTritangent = 2
};


/**
 * Defines the way the fillet radius is defined
 * @param CATFilletRadiusDefaultType
 * The value specified is the radius
 * @param CATFilletRadiusChordLengthType
 * The value specified is the chord length.
 */
enum CATFilletRadiusType
{
  CATFilletRadiusDefaultType = 0,
  CATFilletRadiusChordLengthType = 1,
  CATFilletRadiusHoldCurveType = 2
};


/**
 * Defines the fillet cross section shape
 * @param CATFilletCircularSection
 * Fillet cross sections are circle arcs
 * @param CATFilletConicalSection
 * Fillet cross sections are conic arcs
 * @param CATFilletG2Section
 * Fillet cross sections are curvature continuous arcs with the supports (Do not use, not yet available)
 */
enum CATFilletSectionType
{
  CATFilletCircularSection = 0,
  CATFilletConicalSection = 1,
  CATFilletG2Section = 2,
  CATFilletIsoparCircularSection = 3
};

#endif
