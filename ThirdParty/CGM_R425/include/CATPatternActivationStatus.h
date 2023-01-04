#ifndef CATPatternActivationStatus_H
#define CATPatternActivationStatus_H

typedef enum 
{
  CATPatternActivated = 1,
  CATPatternUnknown = 0,
  CATPatternAutoDesactivated = -1,
  CATPatternUserDesactivated = -2,
  CATPatternEraserEffectDesactivated = -3
}
CATPatternActivationStatus;

#endif
