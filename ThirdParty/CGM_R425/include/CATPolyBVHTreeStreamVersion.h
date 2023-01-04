// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTreeStreamVersion.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Apr 2011 Creation: JXO
//===================================================================
#ifndef CATPolyBVHTreeStreamVersion_h
#define CATPolyBVHTreeStreamVersion_h


/**
 * Memo versions
 */

/** 
 * 0   : Initial
 * 1, 2: With float OBB
 * 3   : Type of node is streamed first thing
 * 4   : For PolyBodyBVHTreeStream
 * 5   : Limits of cylinders
 * 6   : Get back to doubles in OBBs for large scale compliance
 */

#define CURRENT_BVHTREE_STREAM_VERSION 6

#endif // CATPolyBVHTreeStreamVersion_H

