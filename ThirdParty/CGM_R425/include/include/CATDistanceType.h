#ifndef CATDistanceType_H
#define CATDistanceType_H

// COPYRIGHT DASSAULT SYSTEMES 2000
/** @CAA2Required */
 
/**
 * The type of distance computation.
 * @param CATAbsoluteMinDist
 * The lowest minimum distance computation.
 * @param CATAbsoluteMaxDist
 * Not yet implemented.
 * @param CATLocalMinDist
 * The local minimum distances computation..
 * @param CATLocalMaxDist
 * Not yet implemented.
 */
typedef enum {
	CATAbsoluteMinDist = 0,
	CATAbsoluteMaxDist = 1,
	CATLocalMinDist    = 2,
	CATLocalMaxDist    = 3
} CATDistanceType;


#endif
