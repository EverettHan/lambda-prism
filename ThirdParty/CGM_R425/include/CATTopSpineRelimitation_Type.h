#ifndef CATTopSpineRelimitation_Type_h_
#define CATTopSpineRelimitation_Type_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The relimitations on the extremity profiles.
 * @param CATTopSpineRelimitation_Off
 * The spine is not relimited on the extremity profiles.
 * @param CATTopSpineRelimitation_OnLimitProfiles
 * The spine is relimited on the extremity profiles
 * @param CATTopSpineRelimitation_OnFirstProfile
 * The spine is relimited only on the first input profile (NOT YET AVAILABLE)
 * @param CATTopSpineRelimitation_OnLastProfile
 * The spine is relimited only on the last input profile (NOT YET AVAILABLE)
 */
typedef enum { CATTopSpineRelimitation_Off            = 0,
               CATTopSpineRelimitation_OnLimitProfiles,
               CATTopSpineRelimitation_OnFirstProfile ,
               CATTopSpineRelimitation_OnLastProfile  }
               CATTopSpineRelimitation_Type ;

#endif /* CATTopSpineRelimitation_Type_h_ */
