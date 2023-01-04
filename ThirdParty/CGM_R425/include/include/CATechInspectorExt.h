/* -*-c++-*- */
#ifndef CATechInspectorExt_h
#define CATechInspectorExt_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  Extension for implementation of manager of Extract/Redo infrastructure
//    manipulated through CATechHandle 
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"

#include "CATechInspector.h"

 
 
//------------------------------------------------------------------------
// CATechInspector
//   For Small Open Infrastructure for CheckPoint/Inspector paradigm 
//       CATICleanObject vs CATICheckObject
//------------------------------------------------------------------------
class ExportedByCATTechTools CATechInspectorExt : public CATechInspector
{ 
public:
  CATechInspectorExt();

 
  /**
   * Inspect. defines checkpoints where
   *
   * @param ichkPt.
   *     Sensitive CheckPoint.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT Inspect(const CATechCheckPoint  & ichkPt) = 0;


  /**
   * CheckPointToBox3D.  : Let the operation to compute current usefull working area
   *    default beahvior is allowed with a non filering criteria ..
   *
   * @param ichkPt. Context
   *      CheckPoints.
   *
   * @param oBox3DFilter.  Associated (usefull) Box3DContext
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT CheckPointToBox3D(const CATechCheckPoint  & ichkPt, 
                                    CATMathBox                  & oBox3DFilter ) ;




  //------------------------------------------------------------------------
  //         AddRef()        Release()       QueryInterface()
  //------------------------------------------------------------------------


  /** 
  * origin : DEBUG AddRef()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual ULONG   __stdcall  AddRef();

  /** 
  * origin : DEBUG Release()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual ULONG   __stdcall  Release();

  /** 
  * origin : DEBUG QueryInterface()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT __stdcall  QueryInterface(const IID &iIID, void **oPPV);

 
protected :

   /** 
  * origin : ChangeComponentState 
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
 virtual  HRESULT ChangeComponentState(ComponentState iFromState, 
                                       ComponentState iToState,  
                                       const CATSysChangeComponentStateContext * iContext);



  /** 
  * origin : protected 
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  ~CATechInspectorExt();
 
private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATechInspectorExt(const CATechInspectorExt &iCopy);
  CATechInspectorExt& operator=(const CATechInspectorExt &iCopy);

};

//------------------------------------------------------------------------
// CATechInspectors .. 
//------------------------------------------------------------------------

 
extern "C"
{
  typedef HRESULT  CATechInspectorCreator(CATechInspectorExt * & oSpatialInspector);
};


extern void  CATechInspectors_Reset(CATechInspectorExt *iLifeCycle);

 


#endif



