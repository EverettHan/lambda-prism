#ifndef CATTransfoManifoldParam_H
#define CATTransfoManifoldParam_H

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
class CATMathTransformation;

/**
 * Abstract class for the CATTransfoManifoldParam object.
 */
class ExportedByCATGMModelInterfaces CATTransfoManifoldParam : public CATManifoldParamId
{
  CATDeclareClass;

public:

   virtual HRESULT SetValue (const CATMathTransformation & iNewValue) = 0;

   virtual HRESULT GetValue(CATMathTransformation & oChangedValue) const = 0;

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
 
  virtual CATTransfoManifoldParam * GetAsTransfoManifoldParam() const;



  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATTransfoManifoldParam();

  /**
  * Copy constructor. 
  **/
  CATTransfoManifoldParam(CATTransfoManifoldParam const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATTransfoManifoldParam& operator=(CATTransfoManifoldParam const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATTransfoManifoldParam();


};


/**
* --------------------------------------------------------------------------
*  Official Constructor
*---------------------------------------------------------------------------
**/
ExportedByCATGMModelInterfaces CATTransfoManifoldParam * CATCreateTransfoManifoldParam(int iKey, int iDescription, const CATMathTransformation & iValue);


#endif 

