#ifndef __CATSysMacroPrt_H
#define __CATSysMacroPrt_H

// COPYRIGHT DASSAULT SYSTEMES 2001

/**
* Macros used to delete or release objects 
*/

/**
* Macro used to release an object
* Parameter: Ptr the pointer to the object
*/
#ifndef CATSysReleasePtr
# define CATSysReleasePtr(Ptr) { if (Ptr) { (Ptr)->Release(); Ptr = 0; } }
#endif  // CATSysReleasePtr

/**
* Macro used to delete an object
* Parameter: Ptr the pointer to the object
*/
#ifndef CATSysDeletePtr
#define CATSysDeletePtr(Ptr) { if (Ptr) { delete Ptr; Ptr =0; } }
#endif  // CATSysDeletePtr

/**
* Macro used to delete an array of objects
* Parameter: Ptr the pointer to the array
*/
#ifndef CATSysDeleteTab
#define CATSysDeleteTab(Ptr) { if (Ptr) { delete[] Ptr; Ptr = 0; } }
#endif  // CATSysDeleteTab

#endif //__CATSysMacroPrt_H
