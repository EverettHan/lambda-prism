/* -*-c++-*- */
#ifndef CATechMonitor_inline_h
#define CATechMonitor_inline_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  Inline for manager of Extract/Redo infrastructure
//-------------------------------------------------------------------------------------------------

#include "CATechHandle.h"
#include "CATechMonitor.h"
#include "CATMathInline.h"
 

//-------------------------------------------------------------------------------------
// Constructor 
//-------------------------------------------------------------------------------------
INLINE CATechHandle::CATechHandle() {} 

//-------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------
INLINE CATechHandle::~CATechHandle() { Destruction(); }

//-------------------------------------------------------------------------------------
// IsPhoenixAble 
//-------------------------------------------------------------------------------------
INLINE  HRESULT  CATechHandle::IsPhoenixAble()
{ CATechMonitor* handle = (TheRa._Handler || TheRa._Invalid) ? TheRa._Handler : _IsPhoenixAble();    
  return ( handle ? S_OK : E_FAIL);}

//-------------------------------------------------------------------------------------
// IsMonitoringEnabled 
//-------------------------------------------------------------------------------------
//INLINE HRESULT CATechHandle::IsMonitoringEnabled( const CATString & iSuffix,
//                                                  const CATechBehaviorType iBehavior)
//{ 	
//	if (CATechHandle::IsUnderControlOfPlayBack()) return E_FAIL;
//	CATechMonitor* handle = (TheRa._Handler || TheRa._Invalid) ? TheRa._Handler : _IsPhoenixAble();
//	return ( handle ? handle->IsMonitoringEnabled(iSuffix,iBehavior) : E_FAIL);
//}

 
//-------------------------------------------------------------------------------------
// GetLastPhoenixTypeRecorded 
//-------------------------------------------------------------------------------------
INLINE HRESULT CATechHandle::GetLastPhoenixTypeRecorded(CATString   & oLateType)
{ CATechMonitor* handle = (TheRa._Handler || TheRa._Invalid) ? TheRa._Handler : _IsPhoenixAble();    
  return ( handle ? handle->GetLastPhoenixTypeRecorded(oLateType) : E_FAIL);}

//-------------------------------------------------------------------------------------
// IsUnderTransaction 
//-------------------------------------------------------------------------------------
INLINE HRESULT CATechHandle::IsUnderTransaction( const CATechBehaviorType & iBehaviorType  )
{ CATechMonitor* handle = (TheRa._Handler || TheRa._Invalid) ? TheRa._Handler : _IsPhoenixAble();    
  return ( handle ? handle->IsUnderTransaction( iBehaviorType ) : E_FAIL);}


////-------------------------------------------------------------------
////  
////-------------------------------------------------------------------
//INLINE void CATechHandle::Set_UnderControlOfPlayBack(short iOptionValue)
//{
//	int Pos = _Handler ? _StackOfHandlers->Locate(_Handler) : 0;
//	if (Pos>0)
//	{
//		_UnderControlOfPlayBack = iOptionValue;
//		_StackOfUnderControlOfPlayBack[Pos] = _UnderControlOfPlayBack;	 
//	}
//}
//
////-------------------------------------------------------------------
////  
////-------------------------------------------------------------------
//INLINE short CATechHandle::IsUnderControlOfPlayBack()
//{
//	return _UnderControlOfPlayBack;
//}


#endif
