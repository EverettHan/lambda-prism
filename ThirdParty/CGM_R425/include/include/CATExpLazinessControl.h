//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-07-22 - T6L : Creation
//==============================================================================================================


#ifndef CATExpLaziness_H
#define CATExpLaziness_H  


#include "CATExpIntersectionPredicates.h"


class CATExpLazinessControl
{
public:

  /// use them to ask for computations in the corresponding levels of precision
  CATExpLazinessControl(bool dynamic, bool interval, bool exact)
  : attempt_dynamic(dynamic), attempt_interval(interval), attempt_exact(exact) { ResetStatistics(); }

  void ResetStatistics ()
  {
    for (int i = 0; i < kNbLevels_; ++i)
      intersections_counter_[i] = crossings_counter_[i] = comparisons_counter_[i] = 0;
  }

  void IncrementIntersections (int level)
  { ++(intersections_counter_[level]); }

  void IncrementCrossings (int level)
  { ++(crossings_counter_[level]); }

  void IncrementComparisons (int level)
  { ++(comparisons_counter_[level]); }

  void ExportedByCATExpIntersectionPredicates PrintStatistics ();

  /// use them to ask for computations in the corresponding level of precision
  bool attempt_dynamic, attempt_interval, attempt_exact;

private:
  static const int kNbLevels_ = 3;

  //CATExpLevel_t deepest_reached_level_;
  unsigned intersections_counter_[kNbLevels_];
  unsigned crossings_counter_[kNbLevels_];
  unsigned comparisons_counter_[kNbLevels_];
};



#endif
