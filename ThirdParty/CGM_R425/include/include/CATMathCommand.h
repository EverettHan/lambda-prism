#ifndef CATMathCommand_h
#define CATMathCommand_h

// COPYRIGHT DASSAULT SYSTEMES  1999

typedef enum
{
  CommandEval = 0,
  CommandEvalInterval,
  CommandEvalFirstDerivInterval,
  CommandEvalFirstDerivXInterval,
  CommandEvalFirstDerivYInterval,
  CommandEvalSecondDerivInterval,
  CommandEvalSecondDerivX2Interval,
  CommandEvalSecondDerivXYInterval,
  CommandEvalSecondDerivY2Interval,
  CommandEvalThirdDerivInterval,
  CommandEvalThirdDerivX3Interval,
  CommandEvalThirdDerivX2YInterval,
  CommandEvalThirdDerivXY2Interval,
  CommandEvalThirdDerivY3Interval
}
CATMathCommand;

#endif
