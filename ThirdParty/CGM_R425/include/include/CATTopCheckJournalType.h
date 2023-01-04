#ifndef CATTopCheckJournalType_h
#define CATTopCheckJournalType_h

// COPYRIGHT DASSAULT SYSTEMES  2003
/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 


/**
* Defines the Copy / NoCopy mode of a journal input object.
* @param CATTopCheckNoCopy
* The input object is supposed NOT to be in the result body.
* For a Body, none of its Cells are supposed to be in the result body
* and the journal does not need to have Delete orders on these cells.
* @param CATTopCheckCopy
* All the input object is supposed to be in the result body.
* For a Body, all its Cells are supposed to be in the result body
* and the journal does not need to have Keep orders on these cells.
* @param CATTopCheckNeutral
* Do not use.
*/
enum CATTopCheckJournalType { CATTopCheckNoCopy=32, CATTopCheckCopy=33, CATTopCheckNeutral=34 };

#endif














