#ifndef CATIContact_h
#define CATIContact_h

#include "CATBaseUnknown.h"
#include "CATMathDef.h"

class CATMathPoint ;
class CATMathVector ;


 class CATICContact : public CATBaseUnknown
 {
 public :

   // To have the parametrics bounds of the Contact
   virtual  CATLONG32 Bounds(double * oTmin, double * oTmax) const = 0;

   // This methode give if a contact of order <iorder> is defined
   virtual  CATLONG32  HasContact(const short iorder, 
	                            CATBoolean * oHasContact) const =0;

   // This methode give the contact type of order <iorder> 
   virtual  CATLONG32  IsGeometricalContact(const short iorder, 
	                                      CATBoolean * oIsGeometricalContact) const =0;

   //These methodes returns the values contact 
   virtual  CATLONG32 D0(double iu, CATMathPoint * oP) = 0;
   virtual  CATLONG32 D1(double iu, CATMathPoint * oP,
                     CATMathVector * oD1u, CATMathVector * oD1v) = 0;
   virtual  CATLONG32 D2(double iu, CATMathPoint * oP,
                     CATMathVector * oD1u, CATMathVector * oD1v,
                     CATMathVector * oD2u, CATMathVector * oD2v, 
					 CATMathVector * oD2uv) =0;

	virtual	CATLONG32 D0Derivative(int iOrdreDerivation,
								 double it,
								 CATMathVector * oD0t) = 0;

	//These methodes returns information, on potential discontinities 
	virtual CATLONG32 GetNbKnots() const = 0;

	virtual const double * GetKnots()  const = 0;


	// Renvoie les derivees de D0 et de D1 au parametre it pour un contact G1 
/*	virtual	HRESULT D1Derivative(int iOrdreDerivation,
								 double it, 
								 CATMathVector * oD0t,
								 CATMathVector * oD1tx,
								 CATMathVector * oD1ty) = 0;*/
	
	// Renvoie les derivees de D0, D1 et D2 au parametre it pour un contact G2
	/*virtual HRESULT D2Derivative(int iOrdreDerivation,
								 double it,
								 CATMathVector * oD0t,
								 CATMathVector * oD1tx,
								 CATMathVector * oD1ty,
								 CATMathVector * oD2tx,
								 CATMathVector * oD2ty, 
								 CATMathVector * oD2tz) = 0;*/
   // These methodes gives tolerances associated with the contact 
   virtual  CATLONG32 ToleranceG0(const double iu, double * oTolG0) const =0;
   virtual  CATLONG32 ToleranceG1(const double iu, double * oTolG1) const =0;
   virtual  CATLONG32 ToleranceG2(const double iu, double * oTolG2) const =0;

   virtual void SetToleranceG2( const double& iTolG2 ) = 0;
 };
#endif
