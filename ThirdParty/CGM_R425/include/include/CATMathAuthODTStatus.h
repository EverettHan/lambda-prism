#ifndef CATMathAuthODTStatus_h
#define CATMathAuthODTStatus_h

/**
 * Status for an ODT.
 * @param CATMathAuthODTStatusNotFound
 *   The ODT is not found in the file FwTst/InputData/Authorized.xxx or FwTst/InputData/Authorized/xxx
 * @param CATMathAuthODTStatusFoundWithNoValue
 *   The ODT is found in the file, but no value is associated with it.
 * @param CATMathAuthODTStatusFoundWithValue
 *   The ODT is found in the file and a value is associated with it.
 */
enum CATMathAuthODTStatus
{
  CATMathAuthODTStatusNotFound,
  CATMathAuthODTStatusFoundWithNoValue,
  CATMathAuthODTStatusFoundWithValue
};

#endif /* CATMathAuthODTStatus_h */
