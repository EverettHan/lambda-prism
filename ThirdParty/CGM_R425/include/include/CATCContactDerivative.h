// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2000
//
// Auteur  : Nicolas Lafont, le 29/06/2000
// Rajout d'une implementation par defaut pour les fonctions D0(D1,D2)Derivative
// par differences finies
//           version CATIA


#ifndef CATCContactDerivative_h
#define CATCContactDerivative_h

#include "CATGMOperatorsInterfaces.h"
 
#include "CATICContact.h"


class ExportedByCATGMOperatorsInterfaces CATCContactDerivative : public CATICContact
{
public :
	int IsAKindOf(const char *iName) const;

	// To have the parametrics bounds of the Contact
	CATLONG32 Bounds(double * oTmin, double * oTmax) const = 0;

	// This methode give if a contact of order <iorder> is defined
	CATLONG32   HasContact(const short iorder, 
						CATBoolean * oHasContact) const =0;

	// This methode give the contact type of order <iorder> 
	CATLONG32   IsGeometricalContact(const short iorder, 
								  CATBoolean * oIsGeometricalContact) const =0;

	//These methodes returns the values contact 
	CATLONG32  D0(double iu, CATMathPoint * oP) = 0;
	// Renvoie la derivee de D0 au parametre it pour un contact G0
	CATLONG32  D0Derivative(int iOrdreDerivation,
						 double it,
						 CATMathVector * oD0t);

	//HRESULT D1(double iu, CATMathPoint * oP,
	//		   CATMathVector * oD1u, CATMathVector * oD1v) = 0;
	// Renvoie les derivees de D0 et de D1 au parametre it pour un contact G1 
	/*HRESULT D1Derivative(int iOrdreDerivation,
						 double it, 
						 CATMathVector * oD0t,
						 CATMathVector * oD1tx,
					     CATMathVector * oD1ty);*/

	CATLONG32  D2(double iu, CATMathPoint * oP,
			   CATMathVector * oD1u, CATMathVector * oD1v,
			   CATMathVector * oD2u, CATMathVector * oD2v, 
			   CATMathVector * oD2uv) =0;

	virtual double GetLength();
	// Renvoie les derivees de D0, D1 et D2 au parametre it pour un contact G2
	/*HRESULT D2Derivative(int iOrdreDerivation,
						 double it,
						 CATMathVector * oD0t,
						 CATMathVector * oD1tx,
						 CATMathVector * oD1ty,
						 CATMathVector * oD2tx,
						 CATMathVector * oD2ty, 
						 CATMathVector * oD2tz);*/
	//These methodes returns information, on potential discontinities 
	virtual CATLONG32 GetNbKnots() const;
	virtual const double * GetKnots()  const;

	// These methodes gives tolerances associated with the contact 
	CATLONG32 ToleranceG0(const double iu, double * oTolG0) const =0;
	CATLONG32 ToleranceG1(const double iu, double * oTolG1) const =0;
	CATLONG32 ToleranceG2(const double iu, double * oTolG2) const =0;

	virtual void SetToleranceG0( const double& iTolG0 ) { }
  void SetToleranceG2( const double& iTolG2 ) {  }
};

#endif
