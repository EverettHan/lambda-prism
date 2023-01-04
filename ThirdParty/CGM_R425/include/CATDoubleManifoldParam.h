#ifndef CATDoubleManifoldParam_H
#define CATDoubleManifoldParam_H

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


class ExportedByCATGMModelInterfaces CATDoubleManifoldParam : public CATManifoldParamId
{
  CATDeclareClass;

public:

   virtual HRESULT SetValue (double iNewValue) = 0;

   virtual HRESULT GetValue(double & oChangedValue) const = 0;
   // @deprecated 
   virtual double GetValue () const = 0;

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
 
  virtual CATDoubleManifoldParam * GetAsDoubleManifoldParam() const;



  /**
  * Default constructor.
  * <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
  **/
  CATDoubleManifoldParam();

  /**
  * Copy constructor. 
  **/
  CATDoubleManifoldParam(CATDoubleManifoldParam const& iOther);
  
  /**
  * Assignment operator.
  **/
  CATDoubleManifoldParam& operator=(CATDoubleManifoldParam const& iOther); 

  /**
  * Destructor.
  * Strictly Forbiden.
  **/
  virtual ~CATDoubleManifoldParam();


};


/**
* --------------------------------------------------------------------------
*  Official Constructor
*---------------------------------------------------------------------------
**/
ExportedByCATGMModelInterfaces CATDoubleManifoldParam * CATCreateDoubleManifoldParam(int iKey, int iDescription, double iValue);


#endif 

