#ifndef CATManifoldBaseParameter_H
#define CATManifoldBaseParameter_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2015
//
// Responsable LAP/QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  :  Abstract child class representing shared object beethween CDM and CGM departement. 
*                  It carries data for Intergration Knowledge project in NaturalShape Application.
*
*
* Warning : Users have to respect the LifeCycle of this object.
* Delete operand is forbidden and cannot be called. Use AddRef and Release().
*
**/

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

class CATManifoldParamId;
class CATManifoldParameter;


#ifndef CATManifoldParamDescription
#define CATManifoldParamDescription int
#endif


class ExportedByCATGMModelInterfaces CATManifoldBaseParameter : public CATBaseUnknown
{
  CATDeclareClass;

public:

  virtual int GetKey() const = 0;

  virtual CATManifoldParamDescription GetDescription() const = 0;

  virtual CATBoolean GetActive() const = 0;

  virtual HRESULT Check() const = 0;

 /* ------------------------------------------------------------------
  *    Life Cycle Object Management
  *  ------------------------------------------------------------------
  *   - ULONG  AddRef()  
  *   - ULONG  Release()   
  **/

  virtual CATManifoldParamId   * GetAsManifoldParamId() const;
  virtual CATManifoldParameter * GetAsManifoldParameter() const;

protected :

  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATManifoldBaseParameter();

  /**
  * Copy constructor. 
  **/
  CATManifoldBaseParameter(CATManifoldBaseParameter const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATManifoldBaseParameter& operator=(CATManifoldBaseParameter const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATManifoldBaseParameter();

};


#endif 

