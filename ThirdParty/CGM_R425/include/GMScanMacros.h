#ifndef GMScanMacros_h
#define GMScanMacros_h

//*******************************************************************************************

#define CATCGMHashTableBegin(AAA, CCC, TTT)                                                      \
{                                                                                                \
  int __##CCC##Index;                                                                            \
  int __##CCC##Size = (AAA).Size();                                                              \
  for (__##CCC##Index = 0; __##CCC##Index < __##CCC##Size; __##CCC##Index ++)                    \
  {                                                                                              \
    TTT CCC = (TTT)(AAA).Get(__##CCC##Index);                                                    \
    if (CCC)                                                                                     \
    {

//*******************************************************************************************

#define CATCGMHashTableEnd                                                                       \
    }                                                                                            \
  }                                                                                              \
}

//*******************************************************************************************

#endif
