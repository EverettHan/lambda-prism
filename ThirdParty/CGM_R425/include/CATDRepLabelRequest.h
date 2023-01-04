#ifndef CATDRepLabelRequest_H
#define CATDRepLabelRequest_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on March 2019
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

class CATDRepLabel;
class CATMathStream;
class CATICGMContainer;
class CATSoftwareConfiguration;
class CATManifold;
class CATManifoldModification;
class CATBody;
class CATCGMOutput;


class ExportedByCATGMModelInterfaces CATDRepLabelRequest : public CATBaseUnknown
{
  // CATDeclareClass;

public:
 /* ------------------------------------------------------------------
  *    Life Cycle Object Management
  *  ------------------------------------------------------------------
  *   - ULONG  AddRef()  
  *   - ULONG  Release()   
  **/

  virtual const CATDRepLabel  * GetDRepLabel()  const = 0;
  virtual CATBody             * GetBody()       const = 0;   
  virtual CATManifold         * GetManifold()   const = 0;


  virtual HRESULT Stream(CATMathStream & ioStream) const = 0;
  virtual void Dump(CATCGMOutput& Output) const = 0;

  // GetAs
  // --------------------------------------------------------
  virtual CATManifoldModification * GetAsManifoldModification() const;
  

protected : 

	/**
	* Default constructor.
	* <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
	**/
	CATDRepLabelRequest();

	/**
	* Copy constructor. 
	**/
	CATDRepLabelRequest(CATDRepLabelRequest const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATDRepLabelRequest& operator=(CATDRepLabelRequest const& iOther); 

	/**
	* Destructor.
  * Strictly Forbiden.
	**/
	virtual ~CATDRepLabelRequest();

};

// ----------------------------------------------------------------------------------------------
//   << Official CATCreate method >>
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATDRepLabelRequest * CATCreateDRepLabelRequest(CATBody                    * ipBody, 
                                                                                const CATDRepLabel        * ipDRepLabel, 
                                                                                CATSoftwareConfiguration  * ipConfig);

// ----------------------------------------------------------------------------------------------
//   << CGM Constructor Reserved >>
// Internal Use for ODT
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATDRepLabelRequest * CATCreateDRepLabelRequest(CATBody                    * ipBody, 
                                                                                CATManifold                * ipManifold, 
                                                                                CATSoftwareConfiguration   * ipConfig); 


// ----------------------------------------------------------------------------------------------
//   << Official Unsteaming method >>
//       (without ParamID value)
// ----------------------------------------------------------------------------------------------

// UnStream for CGMReplay
ExportedByCATGMModelInterfaces CATDRepLabelRequest * CATLoadDRepLabelRequest(CATMathStream &iStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *ipConfig);

#endif 

