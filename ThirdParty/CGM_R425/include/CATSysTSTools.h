// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATSysTSTools.h
// Header definition CATSysTSTools
//
//===================================================================
//
//
//===================================================================
//
//  Apr 2004  Creation: Code Created		  CKT
//===================================================================
#ifndef __CATSysTSTools_H__
#define __CATSysTSTools_H__



#define CHECK_FAILED(in_rc,in_Message) \
if(FAILED(in_rc)) { \
	CATSysTS_T(CATSysTS_TRACE<<CATSysTS_METH<<in_Message<<CATSysTSEndL); \
	rc = in_rc; \
	goto Fin; \
}

#define CHECK_NULL(in_object,in_status, in_Message) \
if(NULL == in_object) { \
	CATSysTS_T(CATSysTS_TRACE<<CATSysTS_METH<<in_Message<<CATSysTSEndL); \
        rc = in_status; \
        goto Fin; \
}

/*

#define PLMCfgTraceBegin(methode) \
	CATSysTS_TRCMET(methode); \
	CATSysTS_T(CATSysTS_TRACE<<TRACE_CN<<">>"<<methode<<CATSysTSEndL); \


#define PLMCfgTraceEnd(methode) \
	CATSysTS_T(CATSysTS_TRACE<<TRACE_CN<<"<<"<<methode<<CATSysTSEndL); \


#define PLMCfgTRACE(message) \
	CATSysTS_T(CATSysTS_TRACE<<TRACE_CN<<message<<CATSysTSEndL); \
*/

#endif  /* __CATSysTSTools_H__ */
