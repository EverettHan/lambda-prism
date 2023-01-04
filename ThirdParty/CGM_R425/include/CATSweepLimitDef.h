#ifndef CATSweepLimitDef_h_
#define CATSweepLimitDef_h_

enum CATLimitType 
{ OffsetFromProfile, Until, NextAlongAxis, ThruNextAlongAxis, LastAlongAxis, Location};
//
enum CATLimit 
{ Start, End, StartProfile, EndProfile};
//
enum CATPropagationType
{ Single, Extrapolated, Closing, AllowPartial};

#endif /* CATSweepLimitDef_h_ */
