/* -*-c++-*- */
#ifndef CATCGMContainerServices_h
#define CATCGMContainerServices_h
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CGMCreateRootContainer:
//  Creates a new container for CGM CXRN objects.
//
// CGMLoadRootContainer:
//  Creates a new container for CGM CXRN objects and loads its contents from a file (ifstream)
//
// CGMCloseRootContainer:
//=============================================================================
// Usage notes:
//
//  CGMCreateRootContainer:
//    This container has to be created before geometric or topological objects creation.
//    This methods returns a factory for creating such objects.
//    
//=============================================================================
// Mar. 97   Creation                                   R. Rorato R. Aymard
// Jul. 98   Add Unit                                   R. Rorato 
//=============================================================================

#include "YP0LOGRP.h"     
#include "CATBaseUnknown.h" 
#include "CATMathDef.h"
#include "CATMathInline.h"

#include "CATCGMDebug.h"
#include "CATCGMScaleCategoryDef.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
class CATGeoFactory;
class CATCGMStream;
class CATCGMVersionDefinition;

ExportedByYP0LOGRP CATBaseUnknown* CGMCreateRootContainer( void* iInto,
                                                          CATClassId iAsA,
                                                          const CATCGMScaleCategory iScale);  

ExportedByYP0LOGRP CATBaseUnknown* CGMCreateRootContainer( void* iInto,
                                                          CATClassId iAsA,
                                                          const CATPositiveLength iUnitInMeter=.001 );  //@NumValidated. Temporary & for upward compatibility

ExportedByYP0LOGRP CATBaseUnknown* CGMLoadRootContainer(istream& streamarea,
                                                        CATClassId iAsA,
                                                        const CATCGMVersionDefinition **iVersion =NULL);

INLINE void CGMCloseRootContainer(CATGeoFactory *iFact)
{ CATCGMDebug::CATCloseCGMContainer(iFact); }


// internal use only 
INLINE CATGeoFactory* CGMLoadRootContainer(CATCGMStream &streamarea,
                                           const CATCGMVersionDefinition **ptrUnstreamVersion =NULL)
{ return CATCGMDebug::CGMLoadRootContainer(streamarea,ptrUnstreamVersion); }

#endif
