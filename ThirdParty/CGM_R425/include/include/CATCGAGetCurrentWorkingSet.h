#ifndef CATCGAGetCurrentWorkingSet_h
#define CATCGAGetCurrentWorkingSet_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/*--------------------------------------------------------------------------------------*/
/*  ELUCIDATION INSIDE Report,  for INTEGRATION OF INTERACTIVE CORE MODELING RELEASES   */
/*     midlleware integration for potential heavy commands                              */
/*      filling a gap between preliminary local functionnal components based testings   */
/*      and manual industrial integration with follow-up such as  http://pcs/           */
/*--------------------------------------------------------------------------------------*/
//
// COPYRIGHT DASSAULT SYSTEMES 2006
//
//  DO NOT USE , Under FULL CONTROL of CATCGAMeasure.h Set Of Services
//
/**
 * @level Private
 * @usage U1
 */
 
#include "CATDataType.h"
#include "CATMathematics.h"
#include "CATCGAMeasureDefine.h" 
#include "CATBoolean.h" 

extern ExportedByCATMathematics CATLONG64   CATCGAGetCurrentWorkingSet();

extern ExportedByCATMathematics void        CATCGAGetCurrentHeapCriteria( CATLONG64 HeapsCriteria[CATCGAMeasureHeap_NbCriteria], CATBoolean iForceHeapWalk = FALSE );

extern ExportedByCATMathematics void        CATCGAGetCodeDataPeaks(CATULONG64 & oWorkingSetPEAK, CATULONG64 &  oNbModules, CATULONG64 & oSizeOfModule, CATBoolean iForceGetAllMeasures = FALSE );

extern ExportedByCATMathematics CATLONG64   CATCGAGetWorkingSetPeak();

extern ExportedByCATMathematics CATLONG64   CATCGAGetCommitCharge();

#endif
