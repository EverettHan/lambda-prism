#ifndef CATManifoldModification_H
#define CATManifoldModification_H

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
#include "CATDRepLabelRequest.h"
#include "ListPOfCATBody.h"

class CATDRepLabel;
class CATManifoldParamId;
class CATCGMStream;
class CATMathStream;
class CATICGMContainer;
class CATSoftwareConfiguration;
class CATManifold;
class CATManifoldModificationCGM;
class CATOneDRepModification;


// class ExportedByCATGMModelInterfaces CATManifoldModification : public CATBaseUnknown
class ExportedByCATGMModelInterfaces CATManifoldModification : virtual public CATDRepLabelRequest
{
  // CATDeclareClass;

public:
 /* ------------------------------------------------------------------
  *    Life Cycle Object Management
  *  ------------------------------------------------------------------
  *   - ULONG  AddRef()  
  *   - ULONG  Release()   
  **/

  // virtual const CATDRepLabel  * GetDRepLabel()       const = 0;
  
  virtual CATManifoldParamId  * GetManifoldParamId() const = 0;
  virtual HRESULT GetBodies(ListPOfCATBody & oSystemBodies) const = 0;

  // (without ParamId value)
  // Voir avec JUZ si necessaire.
  virtual HRESULT StreamWithoutParamValue(CATMathStream & ioStream) const=0;

  // virtual void Stream(CATMathStream & ioStream) const = 0;
  // virtual void Dump(CATCGMOutput& Output) const = 0;

  // GetAs()
  virtual CATManifoldModification * GetAsManifoldModification() const;


  // CGM Internl Use only
  virtual const CATOneDRepModification * GetAsOneDRepModification() const = 0;
  virtual const CATManifoldModificationCGM & GetImpl() const = 0;

protected : 

	/**
	* Default constructor.
	* <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
	**/
	CATManifoldModification();

	/**
	* Copy constructor. 
	**/
	CATManifoldModification(CATManifoldModification const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATManifoldModification& operator=(CATManifoldModification const& iOther); 

	/**
	* Destructor.
  * Strictly Forbiden.
	**/
	virtual ~CATManifoldModification();

};

// ----------------------------------------------------------------------------------------------
//   << Official CATCreate method >>
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATManifoldModification * CATCreateManifoldModification(const ListPOfCATBody      & iSystemBodies, 
                                                                                       const CATDRepLabel        * ipDRepLabel, 
                                                                                       CATManifoldParamId        * ipManifoldParamId,
                                                                                       CATSoftwareConfiguration * ipConfig=NULL);

// ----------------------------------------------------------------------------------------------
//   << CGM Constructor Reserved >>
// Internal Use for ODT
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATManifoldModification * CATCreateManifoldModification(const ListPOfCATBody      & iSystemBodies, 
                                                                                       CATManifold               * ipManifold, 
                                                                                       CATManifoldParamId        * ipManifoldParamId,
                                                                                       CATSoftwareConfiguration * ipConfig);


// ----------------------------------------------------------------------------------------------
//   << Official Unsteaming method >>
//       (without ParamID value)
// ----------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATLoadManifoldModifWithoutValue(CATMathStream &ioStream, CATICGMContainer *iFactory, CATManifoldModification *& oLoadManifoldModif);

// UnStream for CGMReplay
ExportedByCATGMModelInterfaces CATManifoldModification * CATLoadManifoldModification(CATCGMStream &ioStream, CATICGMContainer *iFactory, CATSoftwareConfiguration *ipConfig);

#endif 

