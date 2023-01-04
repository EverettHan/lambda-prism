/* -*-c++-*- */
#ifndef CATechInspector_h
#define CATechInspector_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  Interface for open adhesion of CheckPoint/Inspector infrastructure
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATDataType.h"
 
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATechInspector;
#else
extern "C" const IID IID_CATechInspector ;
#endif

class CATechCheckPoint;
class CATMathBox;

//------------------------------------------------------------------------
// CATechInspector
//    - For Small Open Infrastructure for CheckPoint/Inspector paradigm 
//    - Interface analogue dans l'esprist a CATICheckObject/CATICleanObject
// Adhesion should be given :
//    through CATechInspectorExt extension mecanisms.
//------------------------------------------------------------------------

class ExportedByCATTechTools CATechInspector : public CATBaseUnknown
{
  CATDeclareInterface;

public:
 
  /**
   * Inspect
   *
   * @param iSensitiveCheckPoints.
   *     Sensitive CheckPoints.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT Inspect(const CATechCheckPoint  & ichkPt) = 0;


  /**
   * CheckPointToBox3D.  : Let the operation to compute current usefull working area
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
                                    CATMathBox                  & oBox3DFilter ) = 0; 


};


CATDeclareHandler( CATechInspector, CATBaseUnknown ) ;

#endif
