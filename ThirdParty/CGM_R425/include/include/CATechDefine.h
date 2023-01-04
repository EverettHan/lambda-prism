/* -*-c++-*- */
#ifndef CATechDefine_h
#define CATechDefine_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//   Various constants.
//-------------------------------------------------------------------------------------------------
 
#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATString.h"


class CATechBehavior;
class CATechMonitor;
class CATechChannel;
class CATechHandle;
class CATechExt;


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATech ;
#else
extern "C" const IID IID_CATech ;
#endif

extern ExportedByCATTechTools  const CATString  CATechChannel_Default;

/**
  * Definition of underlying design pattern implementation .
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>CATechBehavior_BeforeExecute</tt>  <dd>BeforeExecute .    
  * @param <tt>CATechBehavior_AfterExecute</tt>   <dd>AfterExecute .    
  * @param <tt>CATechBehavior_Reload</tt>         <dd>Reload .
  * @param <tt>CATechBehavior_Redo</tt>           <dd>Redo .
  * @param <tt>CATechBehavior_CleanMemory</tt>    <dd>CleanMemory .
  * </dl>
  */
typedef unsigned int CATechBehaviorType;

#define CATechBehavior_BeforeExecute        0x01000000
#define CATechBehavior_AfterExecute         0x02000000
#define CATechBehavior_Reload               0x04000000
#define CATechBehavior_Redo                 0x08000000
#define CATechBehavior_CleanMemory          0x10000000
#define CATechBehavior_Preview              0x20000000
#define CATechBehavior_HistoryFile          0x40000000
#define CATechBehavior_CheckPoints          0x80000000
 
#define CATechBehavior_MaskCoreBehavior     0xFF000000

/**
  * Definition of underlying design pattern implementation .
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>CATCGMOperator</tt>      <dd>legacy CATCGMOperator .    
  * @param <tt>Phoenix</tt>   <dd>simple Extract Redo pattern .
  * </dl>
  */
enum CATech_ImplementPattern 
{
  CatPhoenixPattern_CATCGMOperator     =  0, 
  CatPhoenixPattern_Phoenix            =  1  
};


 /**
  * Keys For History Reporting.
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>CatPhoenixKey_InputsName</tt>      <dd> . 

  * @param <tt>CatPhoenixKey_NbInput_Dim3</tt>    <dd> .    
  * @param <tt>CatPhoenixKey_NbInput_Dim2</tt>    <dd> .    
  * @param <tt>CatPhoenixKey_NbInput_Dim1</tt>    <dd> .    
  * @param <tt>CatPhoenixKey_NbInput_Dim0</tt>    <dd> .

  * @param <tt>CatPhoenixKey_NbOutput_Dim3</tt>   <dd> .     
  * @param <tt>CatPhoenixKey_NbOutput_Dim2</tt>   <dd> .     
  * @param <tt>CatPhoenixKey_NbOutput_Dim1</tt>   <dd> .     
  * @param <tt>CatPhoenixKey_NbOutput_Dim0</tt>   <dd> .     

  * @param <tt>CatPhoenixKey_TimeCpu</tt>   <dd> .     
  * </dl>
  */
enum CATechKeysForHistory 
{ 
  CatPhoenixKey_InputsName      = 0, 

  CatPhoenixKey_NbInput_Dim3    = 1, 
  CatPhoenixKey_NbInput_Dim2    = 2, 
  CatPhoenixKey_NbInput_Dim1    = 3,
  CatPhoenixKey_NbInput_Dim0    = 4,

  CatPhoenixKey_NbOutput_Dim3   = 5, 
  CatPhoenixKey_NbOutput_Dim2   = 6, 
  CatPhoenixKey_NbOutput_Dim1   = 7,
  CatPhoenixKey_NbOutput_Dim0   = 8,
 

  CatPhoenixKey_TimeCpu         = 13
};
 
 

/**
  * Definition of underlying design pattern implementation .
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>CatPhoenixFlux_send</tt>      <dd>send .    
  * @param <tt>CatPhoenixFlux_receive</tt>   <dd>receive .
  * </dl>
  */
enum CATech_Flux 
{
  CatPhoenixFlux_send    =  0, 
  CatPhoenixFlux_receive =  1  
};


/**
*  CATechChannelCreator
*/
extern "C"
{
  typedef HRESULT  CATechChannelCreator(CATechExt ** oPPV);
};




/**
  * Statut/SetUp of LOG contents management.
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>CATechLOGFlag_Root</tt>  <dd>Root (OneShot or FirstLevel Begin/End transaction).    
  * </dl>
  */
typedef unsigned int CATechLOGFlags;

#define CATechLOGFlag_Root        0x01000000

#endif
