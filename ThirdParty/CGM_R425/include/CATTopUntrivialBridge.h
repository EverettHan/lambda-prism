/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATTopUntrivialBridge_H 
#define CATTopUntrivialBridge_H 
//=============================================================================
// DESCRIPTION : CATTopUntrivialBridge
//=============================================================================
// October. 09 Extension topologique for CloneManager 
//=============================================================================
#include "CATGMModelInterfaces.h"
#include "CATTopUntrivialConnectivity.h"
#include "CATBoolean.h"
 
/**
*  Class for GeometricalServices To TopologicalExtensions
*/
class ExportedByCATGMModelInterfaces CATTopUntrivialBridge
{
public :
 

  /**
  * GetServices .
  */
  static CATTopUntrivialBridge*  GetServices();
  
  /**
  * Destructor .
  */
  virtual ~CATTopUntrivialBridge();

 
  /**
  * Asynchroneous _GetMeta.
  */
  virtual void *  _GetMeta() = 0 ;

   /**
  * Asynchroneous _IsUntrivialConnectivity.
  */
  virtual CATBoolean _IsUntrivialConnectivity( CATBody *iBody, CATCell * iCell,  CATTopUntrivialConnectivity * & oConfiguration , CATBoolean   iOptimised  ) = 0 ;

   /**
  * Asynchroneous _HasAlreadyHaveDetectedUntrivialConnectivity.
  */
  virtual CATBoolean _HasAlreadyHaveDetectedUntrivialConnectivity( CATBody *iBody, CATCell * iCell )  = 0 ;
 
     /**
  * Asynchroneous _GetUntrivialConnectivities.
  */
  virtual CATBoolean _GetUntrivialConnectivities( CATBody *iBody,   CATLISTP(CATTopUntrivialConnectivity) & oUnTrivials, CATBoolean   iOptimised  )  = 0 ;



protected  :

  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATTopUntrivialBridge();

  static CATTopUntrivialBridge* _Result;

private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATTopUntrivialBridge(const CATTopUntrivialBridge &iCopy);
  CATTopUntrivialBridge& operator=(const CATTopUntrivialBridge &iCopy);
 
};


 
/**
* @nodoc
*/
extern "C" { typedef CATTopUntrivialBridge* CATTopUntrivialBridge_Creator(); }  

#endif
