/* -*-c++-*- */
#ifndef CATPrimitivesErrors_H
#define CATPrimitivesErrors_H
//#include "TopologicalOperatorsErrors.h" 
//#include "TopologicalOperatorsInputError.h" 
//#include "TopologicalOperatorsInternalError.h"
#include "CATTopOpInError.h" 
#include "CATTopOpIntError.h" 

#define ThrowIfNullInput(ptr)                                                \
if (!ptr)                                                                    \
 { CATTopOpInError * Error =                                                 \
      new  CATTopOpInError (TopOpInNull,"TopOpInNull",TopOpInFile);          \
      CATThrow (Error);  } 

#define ThrowBadTopology                                                     \
 { CATTopOpIntError * Error =   new  CATTopOpIntError                        \
       (TopOpIntBadTopology,"TopOpIntBadTopology",TopOpIntFile);             \
      CATThrow (Error);  } 

#define ThrowBadGeometry                                                     \
 { CATTopOpIntError * Error =   new  CATTopOpIntError                        \
       (TopOpIntBadGeometry,"TopOpIntBadGeometry",TopOpIntFile);             \
      CATThrow (Error);  } 

//#define primitives_debug

#ifdef primitives_debug
#define PrintTitle(title)             \
	cgmout<<title<<cgmendl;
#else
#define PrintTitle(title)
#endif

#endif





