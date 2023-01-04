#ifndef CATNestingOptimizationTarget_h_
#define CATNestingOptimizationTarget_h_

enum CATNestingOptimizationTarget
{
	NoOptimization,
  Nesting2D,
	MinimizeLength = Nesting2D, // Legacy
  MaximizeNbPart,
	MaximizeNbPartWithRegularity,  // cardboard
  Nesting3D,
  Nesting2D5
};

#endif /* CATNestingOptimizationTarget_h_ */
