//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMConstraint
//===================================================================

// Interface on a CDMConstraint, dedicated for applications that may not require CDMModel framework,
// and do not accept to use CATICDMConstraint interface 
// These objects are twins of CDMConstraint, their lifecycles are identical

//===================================================================
//  2010/07/12 Creation: chu
//===================================================================
#ifndef CATGMConstraint_H
#define CATGMConstraint_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATGMRelation.h"
#include "CATCDMRelationEnum.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMConstraint;
class CDMRelation;
class CATBody;
class CDMLabelContract;
class CATMathPoint;
class CATGeometry;
class CATGMSupport;

class ExportedByCATCDMBaseInterfaces CATGMConstraint: public CATGMRelation
{
public:

  // Lifecycle
  virtual ~CATGMConstraint();

  // Investigate the constraint
	virtual CATCDMRelationEnum::CstMode GetCstMode() = 0;

  // Get ieme support
  virtual HRESULT GetGMSupport(int iNumber, CATGMSupport*& oSupport) = 0;
  // to be removed
  virtual HRESULT GetCellManifoldsSupport( int i, CATLISTP(CATCellManifold) & oCellManifoldsList, CATLISTP(CATBody) & oBodiesList) = 0;

  // Get or set the help-point associated with a support, if any (Get method returns E_FAIL if none exists)
  virtual HRESULT GetHelpPoint(int iNumber, CATMathPoint & oHelpPoint) = 0;
  virtual HRESULT SetHelpPoint(int iNumber, CATMathPoint & iHelpPoint) = 0;
  virtual HRESULT UnsetHelpPoint(int iNumber) = 0;

  // Set a parameter value (distance or angle, according to the constraint type)
  virtual HRESULT SetCstDoubleParameter(double iVal) = 0;

  // Get the parameter (distance or angle, according to the constraint type), and its variation interval if any
  virtual double GetCstDoubleParameter() = 0;
  virtual CATBoolean HasMaximum(double * oMaximum = 0) = 0;
  virtual CATBoolean HasMinimum(double * oMinimum = 0) = 0;

  // Change Mode (Status, Orientation and activity are handled by baseclass CATGMRelation)
	virtual HRESULT SetCstMode(CATCDMRelationEnum::CstMode  iMode) = 0;

  // Internal Use
  virtual CDMRelation & GetAssociatedRelation() = 0;

  virtual HRESULT GetFixedIfPossibleSupportNumber(int& oSupportNumber) = 0;

  // Introspecting the Permanent Geometry for FixConstraints
  virtual HRESULT GetPermanentCellsSupport(CATListPtrCATCell & oCellsList, CATLISTP(CATBody) & oBodiesList)=0;

  //For Power Copy
  virtual HRESULT GetReferenceCst(CATGMConstraint *& oCstRef)=0;
  
  // iNumSupport : from 1 to 3
  // oChir 
  //       0 : unset
  //       1 : same chirality
  //       -1 : other side
  virtual HRESULT GetReferenceCstChirality(int &iNumSupport, int & oChir)=0;

protected:

  CATGMConstraint();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMConstraint (CATGMConstraint &);
  CATGMConstraint& operator=(CATGMConstraint&);

};

//-----------------------------------------------------------------------
#endif
