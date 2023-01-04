#ifndef CATNewBuffer_H
#define CATNewBuffer_H
// COPYRIGHT : DASSAULT SYSTEMES 1997
#include "CATArrayBuffer.h"
 
#define CATNewBuffer(Type, Variable, NeededSize, HardSize)  CATArrayBufferNew(Type, Variable, HardSize, NeededSize ) 
#define CATRemoveBuffer(Variable)                           CATArrayBufferDelete(Variable)

#endif
