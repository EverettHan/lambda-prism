#ifndef CATBodyDatumiserLocalStatus_h_
#define CATBodyDatumiserLocalStatus_h_

// COPYRIGHT DASSAULT SYSTEMES 1999
/** @nodoc 
  *  Status of post and pre treatment during BodyDatumiser 
  *  CATCXLocalStatus_SimplificationFound              = 
  *  CATCXLocalStatus_NewDatumBodyButNotGivenInResult  = 
  *  CATCXLocalStatus_NewJournalButNotGivenInResult    =
  *  CATCXLocalStatus_ClippingHasBeenDone              = 
  *  CATCXLocalStatus_HealingHasBeenDone               = 
  *  CATCXLocalStatus_FittingHasBeenDone               =  
  *  CATCXLocalStatus_RegularizationHasBeenDone        =
  *  CATCXLocalStatus_ReframeHasBeenDone               =
*/

#define CATCXLocalStatus_SimplificationFound               0x0010
#define CATCXLocalStatus_NewDatumBodyButNotGivenInResult   0x0020
#define CATCXLocalStatus_NewJournalButNotGivenInResult     0x0040
#ifdef CATIACGMR214CAA
#define CATCXLocalStatus_ClippingHasBeenDone               0x0100
#define CATCXLocalStatus_HealingHasBeenDone                0x0200
#endif
#ifdef CATIACGMR216CAA
#define CATCXLocalStatus_FittingHasBeenDone                0x0400
#define CATCXLocalStatus_RegularizationHasBeenDone         0x0800
#define CATCXLocalStatus_ReframeHasBeenDone                0x1000
#endif

#endif
