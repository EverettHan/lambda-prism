/* -*-c++-*- */
#ifndef CATechBehavior_h
#define CATechBehavior_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//   Interface for operators' adhesion on Extract/Redo paradigm
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"
#include "CATechDefine.h"
 
class CATString;
class CATechMeta;
class CATechCheckPoint;
class CATMathBox;
  
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATechBehavior;
#else
extern "C" const IID IID_CATechBehavior ;
#endif

/**
* Interface to manage a Redo pattern
*/
class ExportedByCATTechTools CATechBehavior : public CATBaseUnknown
{
  CATDeclareInterface;

public:

 
 
  /** 
  * ImplementBehavior : Delegate Event management to Operator
  *   Be carefull, extension/implementation may be already associated to an operation, so ..
  *
  *  @param iOperation    : Context of operator understandable only in context of the Late Type 
  *
  *  @param iBehaviorType : Kind of behavior.
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT ImplementBehavior(void * iOperation,  const CATechBehaviorType & iBehaviorType)  = 0 ;
 
 
  /** 
  * CheckPointToArea :   
  *   Delegate to operator how to determine if possible a  limitation by 3D Box 
  *   associated to a particular context 
  *
  *  @param iBreakPoint : RuntimeContext
  *
  *  @param CATMathBox  : 3D Limits about area concerned by current CheckPoint
  *
  * @return
  *      S_OK   if Box 3D could be defined<br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT CheckPointToArea(const CATechCheckPoint & iRuntimeContext ,
                                   CATMathBox                 & oContext3D      )  = 0 ;
 
};


CATDeclareHandler( CATechBehavior, CATBaseUnknown ) ;

#endif



