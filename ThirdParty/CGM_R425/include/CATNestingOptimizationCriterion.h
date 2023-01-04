#ifndef CATNestingOptimizationCriterion_H
#define CATNestingOptimizationCriterion_H

// Minimization criterion for nesting 2D

#ifndef _AIX_SOURCE

enum class CATNestingOptimizationCriterion
{
  // Minimize x length of filled box (default)
  X,
  // Maximize filled area / filled box perimeter
  // As theorical maximum for 2D surface is a circle, result will looks like a square
  AreaPerimeterRatio 
};

#else

class CATNestingOptimizationCriterion
{
public:
  enum E
  {
    X,
    AreaPerimeterRatio
  };
};

#endif
#endif
