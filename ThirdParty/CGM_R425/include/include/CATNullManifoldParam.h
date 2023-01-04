#ifndef CATNullManifoldParam_H
#define CATNullManifoldParam_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2015
//
// Responsable LAP/QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  :  Instanciable child class representing shared object beethween CDM and CGM departement. 
*                  It carries data for Intergration Knowledge project in NaturalShape Application.
*
*
* Warning : Users have to respect the LifeCycle of this object.
* Delete operand is forbidden and cannot be called. Use AddRef and Release().
*
**/


#include "CATGMModelInterfaces.h"
#include "CATManifoldParamId.h"


class ExportedByCATGMModelInterfaces CATNullManifoldParam : public CATManifoldParamId
{
  CATDeclareClass;

public:

   /* ------------------------------------------------------------------
   *    Life Cycle Object Management
   *  ------------------------------------------------------------------
   *   - ULONG  AddRef()  
   *   - ULONG  Release()   
   **/

  /**
  * @nodoc 
  **/
  virtual CATNullManifoldParam * GetAsNullManifoldParam() const;


protected :
 
  
  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATNullManifoldParam();

  /**
  * Copy constructor. 
  **/
  CATNullManifoldParam(CATNullManifoldParam const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATNullManifoldParam& operator=(CATNullManifoldParam const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATNullManifoldParam();


};


/**
* --------------------------------------------------------------------------
*  Official Constructor
*---------------------------------------------------------------------------
**/
ExportedByCATGMModelInterfaces CATNullManifoldParam * CATCreateNullManifoldParam(int iKey, int iDescription);


#endif 

