#ifndef CATIntManifoldParam_H
#define CATIntManifoldParam_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on november 2015
//
// Responsable QF2 (LAP)
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

class CATDRepGroup;
class CATUnicodeString;
class CATManifold;


class ExportedByCATGMModelInterfaces CATIntManifoldParam : public CATManifoldParamId
{
  CATDeclareClass;

public:

   virtual HRESULT SetValue (int iNewValue) = 0;
   virtual HRESULT GetValue (int & oChangedValue) const = 0;
   // deprecated
   virtual int  GetValue () const = 0;

   /* ------------------------------------------------------------------
   *    Life Cycle Object Management
   *  ------------------------------------------------------------------
   *   - AddRef()  
   *   - Release()   
   **/

  /**
  * @nodoc
  * For internal use only.
  **/
  

protected :

  virtual CATIntManifoldParam * GetAsIntManifoldParam() const;


  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATIntManifoldParam();

  /**
  * Copy constructor. 
  **/
  CATIntManifoldParam(CATIntManifoldParam const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATIntManifoldParam& operator=(CATIntManifoldParam const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATIntManifoldParam();

};

/**
* --------------------------------------------------------------------------
*  Official Constructor
*---------------------------------------------------------------------------
**/
ExportedByCATGMModelInterfaces CATIntManifoldParam * CATCreateIntManifoldParam(int iKey, int iDescription, int iValue);


#endif 

