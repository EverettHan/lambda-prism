#ifndef CATIPGMDRepGroupThread_H
#define CATIPGMDRepGroupThread_H

// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// ======================================================================================
//
// Created on october 2015
//
// Responsable LAP/QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  : Interface Child Class. This object represent an amount of data attached to a group of topological cells.
*                 Use CATCreate methode to instanciate this object. 
*                 Do not call delete operand. This is a shared object between CATIA Application and CGMModel.
* @nodoc
* Interface Class dedicated to Thread and Hole in NaturalShape Application. 
* Purpose : Carrying numerical data beetween CGMModeler and the Application. 
*/

// --------------------------------------------------------------------------------------

#include "CATGMModelInterfaces.h"
#include "CATIPGMDRepGroup.h"
#include "ListPOfCATCellManifold.h"


class CATDRepGroupThread;
class CATMathAxis;
class CATString;

/*
* 
* This class is designed to be used with CATCreate constructor. 
*
* Warning : Users have to respect the LifeCycle of this object.
* Delete operand is forbidden and cannot be called. Use AddRef() and Release().
*
**/
class ExportedByCATGMModelInterfaces CATIPGMDRepGroupThread : public CATIPGMDRepGroup
{

  CATDeclareClass;

public:
 
  virtual void  GetAxis(CATMathAxis &oThreadAxis) const = 0;
  virtual void  GetNumericalParam (double &oDepth, double &oDiameter, double &oNominalDiameter, double &oPitch, int &oSens, double &oSupportDiameter) const = 0;
  virtual void  GetDescriptionParam (CATString &oThreadDescription, int &oThreadType, int &oDisplayInDrafting, CATString &oKeyOfThread) const = 0;

  
  virtual CATIPGMDRepGroupThread * GetAsPGMDRepGroupThread();


protected :

	/**
	* Default constructor.
	* <br><b>Role:</b> Constructs object in an invalid state - needed so that instances of this class can be streamed.
	**/
	CATIPGMDRepGroupThread();

	/**
	* Copy constructor. 
	**/
	CATIPGMDRepGroupThread(CATIPGMDRepGroupThread const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATIPGMDRepGroupThread& operator=(CATIPGMDRepGroupThread const& iOther); 

	/**
	* Destructor. External use is strictly forbidden. 
  *
  * Use AddRef and Release 
	**/
	virtual ~CATIPGMDRepGroupThread();


};


ExportedByCATGMModelInterfaces CATIPGMDRepGroupThread * CATIPGMCreateDRepGroupThread(const CATLISTP(CATCellManifold) &iCellManifoldGroup, 
                                                                            const CATLISTP(CATCellManifold) &iCellManifoldContext, CATMathAxis &iAxis, 
                                                                            double iDepth, double iDiameter, double iNominalDiameter, double iPitch, int iSens, double iSupportDiameter, 
                                                                            CATString &iThreadDescription, int iThreadType, int iDisplayInDrafting, CATString &iKeyOfThread);


#endif 

