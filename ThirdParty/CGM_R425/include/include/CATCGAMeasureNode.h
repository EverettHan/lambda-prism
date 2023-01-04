#ifndef CATCGAMeasureNode_H
#define CATCGAMeasureNode_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// Area(s) of data
//------------------------------------------------------------ 
#include "CATDataType.h"
#include "CATCGMKernel.h"
#include "CATCGMItfName.h"

class CATCGMCockOperation;
 
#define CATCGAMeasureNodeFlag_Extract 0x000000001ULL
 
// Stack Node
class ExportedByCATCGMKernel CATCGAMeasureNode
{
public :

  // Identifier
  const char *           _Operation;
  const char *           _Domain;
  void       *           _Object;

  int                    _CurrentEvent;
  int                    _Step;

  // _Self Described Stack Level (Working 
  CATLONG64              _SelfDescribedStackLevel; 
  int                    _SelfBeforeOneShotAfter;

  // 0x01 : With extraction on Filtered Type 
  CATULONG64             _FlagManagement;

  CATCGMCockOperation *  _CurrentOperation;

  // ItfName (Be carefull, Not Transferable)
  CATCGMItfName       *  _WorkingFeature;  

  // ...
  const char *           _StaticName;
  CATLONG64              _DiskSize;
 
  INLINE CATCGAMeasureNode() 
  {  
    _Operation = NULL;
	  _Domain = NULL;
	  _Object = NULL;
	  _CurrentEvent = 0;
    _Step = 0;
    _SelfDescribedStackLevel = 0;
    _SelfBeforeOneShotAfter = 0;

	  _CurrentOperation = NULL;
    _WorkingFeature = 0;
    _FlagManagement = 0;
    _StaticName = 0;
    _DiskSize = 0;
  }

  INLINE CATCGAMeasureNode( const char * iKindOfOperation, const char * iDataDomain, void * iObject)
  {
    _Operation = NULL;
	  _Domain = NULL;
	  _Object = NULL;
	  _CurrentEvent = 0;
    _Step = 0;
    _SelfDescribedStackLevel = 0;
    _SelfBeforeOneShotAfter = 0;
 
	  _CurrentOperation = NULL;
    _WorkingFeature = 0;
    _StaticName = 0;
    _DiskSize = 0;

    _Operation=iKindOfOperation; _Domain=iDataDomain; _Object=iObject; 
  }

  INLINE CATCGAMeasureNode( const int  iBeforeOneShotAfter,  const char * iKindOfOperation, const char * iDataDomain, void * iObject)
  { 
    _Operation = NULL;
	  _Domain = NULL;
	  _Object = NULL;
	  _CurrentEvent = 0;
    _Step = 0;
    _SelfDescribedStackLevel = 0;
    _SelfBeforeOneShotAfter = 0;
 
	  _CurrentOperation = NULL;
    _WorkingFeature = 0;
    _StaticName = 0;
    _DiskSize = 0;

    _SelfBeforeOneShotAfter=iBeforeOneShotAfter; _Operation=iKindOfOperation; _Domain=iDataDomain; _Object=iObject; 
  }

  INLINE CATCGAMeasureNode( const int  iBeforeOneShotAfter,  const char * iKindOfOperation, const char * iDataDomain, const char * iName, void * iObject)
  { 
    _Operation = NULL;
	  _Domain = NULL;
	  _Object = NULL;
	  _CurrentEvent = 0;
    _Step = 0;
    _SelfDescribedStackLevel = 0;
    _SelfBeforeOneShotAfter = 0;
 
	  _CurrentOperation = NULL;
    _WorkingFeature = 0;

    _SelfBeforeOneShotAfter=iBeforeOneShotAfter; _Operation=iKindOfOperation; _Domain=iDataDomain; _Object=iObject; 
    _StaticName = iName;
    _DiskSize = 0;
  }



  INLINE ~CATCGAMeasureNode()
  {
    if ( _WorkingFeature ) { delete _WorkingFeature; _WorkingFeature = NULL; } 

    _CurrentOperation = NULL;
    _Operation = NULL;
    _Domain = NULL;
    _Object = NULL;
    _StaticName = 0;
    _DiskSize = 0;
  }
 
	INLINE CATCGAMeasureNode(const CATCGAMeasureNode &iCopy)  
	{
    _Operation = iCopy._Operation;
	  _Domain = iCopy._Domain;
	  _Object = iCopy._Object;
	  _CurrentEvent = iCopy._CurrentEvent;
    _Step  = iCopy._Step;
    _SelfDescribedStackLevel = iCopy._SelfDescribedStackLevel;
    _SelfBeforeOneShotAfter = iCopy._SelfBeforeOneShotAfter;

    _CurrentOperation = iCopy._CurrentOperation;
    _WorkingFeature = iCopy._WorkingFeature;    if ( iCopy._WorkingFeature ) { ((CATCGAMeasureNode*)&iCopy)->_WorkingFeature = NULL; };
    _FlagManagement = iCopy._FlagManagement;
    _StaticName = iCopy._StaticName;
    _DiskSize   = iCopy._DiskSize;
  }


  INLINE CATCGAMeasureNode& operator=(const CATCGAMeasureNode &iCopy)
  {
    _Operation = iCopy._Operation;
    _Domain = iCopy._Domain;
    _Object = iCopy._Object;
    _CurrentEvent = iCopy._CurrentEvent;
    _Step  = iCopy._Step;
    _SelfDescribedStackLevel = iCopy._SelfDescribedStackLevel;
    _SelfBeforeOneShotAfter = iCopy._SelfBeforeOneShotAfter;

    _CurrentOperation = iCopy._CurrentOperation;
    if ( _WorkingFeature != iCopy._WorkingFeature ) 
    {
      if ( _WorkingFeature ) { delete _WorkingFeature; _WorkingFeature = NULL; } 
      _WorkingFeature = iCopy._WorkingFeature;  if ( iCopy._WorkingFeature ) { ((CATCGAMeasureNode*)&iCopy)->_WorkingFeature = NULL; };
    }
    _FlagManagement = iCopy._FlagManagement;
    _StaticName = iCopy._StaticName;
    _DiskSize   = iCopy._DiskSize;
		return *this;
	}


  //------------------------------------------------------------------------
  // Restricted under CATCGMeasure::_Monitored
  //------------------------------------------------------------------------
  static CATCGAMeasureNode * GetWorkingTransactionalNode() ;

  //------------------------------------------------------------------------
  // GetBegin GetEnd
  //------------------------------------------------------------------------
  static CATCGAMeasureNode & GetBegin() ;
  static CATCGAMeasureNode & GetEnd() ;
  static CATCGAMeasureNode & NoMoreFactoryV5() ;
  static CATCGAMeasureNode & StartFactoryV5() ;


  /** 
  * Filtering Capability depending on current possible workspace,
	*
	*   Default   Inclusive Management  :
	*      -> Forbidden Node are explicitly identified by specific declarative 
	*          
	*   Customised Exclusive Management :
	*     -> Only explicit Node are kept 
	*
  */ 
  CATBoolean IsEnable();
 
};

 
#endif
