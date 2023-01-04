/* -*-c++-*- */
#ifndef CATCGMArrayManagement_H
#define CATCGMArrayManagement_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//Mode de gestion de  CATCGMArrayOfOrientedObjects
//============================================================================
typedef unsigned int CATCGMArrayManagement;

// Par defaut 
#define CATCGMArrayManagement_NoNullNoDupNoAddRef       0x00000000


// DuplicationAuthorized
#define CATCGMArrayManagement_DuplicationAuthorized     0x00000001

// NullAuthorized
#define CATCGMArrayManagement_NullAuthorized            0x00000002

// AddRefReleaseManagement
#define CATCGMArrayManagement_AddRefReleaseManagement   0x00000010

#endif
