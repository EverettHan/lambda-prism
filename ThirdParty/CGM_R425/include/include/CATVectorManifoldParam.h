#ifndef CATVectorManifoldParam_H
#define CATVectorManifoldParam_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2019
//
// Responsable QF2
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

// ++ Include ++ 
#include "CATGMModelInterfaces.h"
#include "CATManifoldParamId.h"

// +++ Predeclaration +++ 
class CATMathVector;

/**
 * Abstract class for the CATVectorManifoldParam object.
 */
class ExportedByCATGMModelInterfaces CATVectorManifoldParam : public CATManifoldParamId
{
  CATDeclareClass;

public:

   virtual HRESULT SetValue (const CATMathVector & iNewValue) = 0;

   virtual HRESULT GetValue(CATMathVector & oChangedValue) const = 0;

   /* ------------------------------------------------------------------
   *    Life Cycle Object Management
   *  ------------------------------------------------------------------
   *   - ULONG  AddRef()  
   *   - ULONG  Release()   
   **/

  /**
  * @nodoc
  * For internal use only.
  **/

protected :
 
  virtual CATVectorManifoldParam * GetAsVectorManifoldParam() const;



  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATVectorManifoldParam();

  /**
  * Copy constructor. 
  **/
  CATVectorManifoldParam(CATVectorManifoldParam const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATVectorManifoldParam& operator=(CATVectorManifoldParam const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATVectorManifoldParam();


};


/**
* --------------------------------------------------------------------------
*  Official Constructor
*---------------------------------------------------------------------------
**/
ExportedByCATGMModelInterfaces CATVectorManifoldParam * CATCreateVectorManifoldParam(int iKey, int iDescription, const CATMathVector & iValue);


#endif 

