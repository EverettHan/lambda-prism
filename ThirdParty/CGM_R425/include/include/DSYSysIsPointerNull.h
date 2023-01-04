
#ifndef DSYSysIsPointerNull_H
#define DSYSysIsPointerNull_H

#if defined(__clang__) || (defined (_LINUX_SOURCE) && __GNUC__ >= 6)
#include "CATSysTS.h"
/**
 * DSYSysIsPointerNull.
 * Not inline in this case to prevent the compiler from outputting an error when encountering bad code, such as:
 *    static int *p = NULL;
 *    inline int & GetAsInteger() { return *p; }
 *
 * The caller protects itself from a core dump the following way:
 * if(&GetAsInteger() == NULL)
 * // Workaround that most compilers consider legit:
 * // <=> if(&(*p) == NULL) <=> if(p == NULL)
 */
ExportedByCATSysTS bool DSYSysIsPointerNull(void *x);

#define DSYSysIsPointerNull_Impl
#else
#include "CATSysDataType.h"
inline bool DSYSysIsPointerNull(void *x) { return x == NULL; }
#endif

#endif  // DSYSysIsPointerNull_H
