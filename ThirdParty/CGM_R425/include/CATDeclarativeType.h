#ifndef CATDeclarativeType_H
#define CATDeclarativeType_H

typedef enum
{
  CATDeclarativeUndef = 0,
  CATDeclarativeCanonic = 1,
  CATDeclarativeFillet = 2,
  CATDeclarativeChamfer = 3,
  CATDeclarativePadPocket = 4,
  CATDeclarativeDraft = 5,
  CATDeclarativeOffset = 6,
  CATDeclarativeRoundedSlot = 7,
  CATDeclarativeRectangularSlot = 8,
  CATDeclarativeNotch = 9,
  CATDeclarativePattern = 10,
  CATDeclarativeSimpleHole = 11,
  CATDeclarativeCounterBoreHole = 12,
  CATDeclarativeCounterSunkHole = 13,
  CATDeclarativeTaperedHole = 14,
  CATDeclarativeCounterDrilledHole = 15,
  CATDeclarativeGeneralHole = 16,
  CATDeclarativeButton = 17
}
CATDeclarativeType;

#endif
