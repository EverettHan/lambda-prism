#ifndef CATIPGMDRepGroup_H
#define CATIPGMDRepGroup_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2015
//
// Responsable LAP/QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  : Interface Top Mother Class. This interface object represent an amount of data attached to a group of topological cells.
*                 It cannot be instanciated by any constructor. 
*
*                 Use CATCreate of the child class constructor.
*                 Do not call delete operand. This is a shared object between CATIA Application and CGMModel.
*
* Interface Mother Class dedicated to Thread and Hole in NaturalShape Application. 
* Purpose : Carrying numerical data beetween CGMModeler and the Application. 
*
*
* Warning : Users have to respect the LifeCycle of this object.
* Delete operand is forbidden and cannot be called. Use AddRef and Release().
*
**/


#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfShort.h"

class CATIPGMDRepGroupThread;
class CATDRepGroup;


class ExportedByCATGMModelInterfaces CATIPGMDRepGroup : public CATBaseUnknown
{

  CATDeclareClass;

public:

  virtual void GetCellManifoldGroup (CATLISTP(CATCellManifold) &oCellManifolGroup) const = 0;
  
  virtual void GetContextualGroup (CATLISTP(CATCellManifold) &oContextualCellManifolds, CATListOfShort &oListOfContextType) const = 0;
  
 
  virtual CATIPGMDRepGroupThread * GetAsPGMDRepGroupThread();

  /**
	* @nodoc
	* For internal use only.
	**/
	virtual const CATDRepGroup & GetDRepGroupImpl() const = 0;

protected :

	/**
	* Default constructor.
	* <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
	**/
	CATIPGMDRepGroup();

	/**
	* Copy constructor. 
	**/
	CATIPGMDRepGroup(CATIPGMDRepGroup const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATIPGMDRepGroup& operator=(CATIPGMDRepGroup const& iOther); 

	/**
	* Destructor.
  * Strictly Forbiden.
	**/
	virtual ~CATIPGMDRepGroup();


};


#endif 

