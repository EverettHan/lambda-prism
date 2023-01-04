#ifndef CATCX_AuthorizedAnomaliesForCGMOperator_H
#define	CATCX_AuthorizedAnomaliesForCGMOperator_H

// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATCX_AuthorizedAnomaliesForCGMOperator
//---------------------------------------------------------------------------  
//
//  
//
//
//
//
//===========================================================================   

#include "ExportedByCATCGMFusion.h"
#include "CATCollec.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"

//class CATUnicodeString;

/** @nodoc @nocgmitf */
/**
* 
*
**/
class ExportedByCATCGMFusion CATCX_AuthorizedAnomaliesForCGMOperator
{
public :
	
	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   CATCX_AuthorizedAnomaliesForCGMOperator();

	/** @nodoc @nocgmitf */
	//CATCX_AuthorizedAnomaliesForCGMOperator(CATUnicodeString &iOperatorID);
   
	/** @nodoc @nocgmitf */
	virtual ~CATCX_AuthorizedAnomaliesForCGMOperator();

	/** @nodoc @nocgmitf */
	void Set_DoAssemblyParameter(int  iDoAssemblyParameter);

	/** @nodoc @nocgmitf */
   void Set_PreviewParameter(CATBoolean  iPreviewParameter);

   /** @nodoc @nocgmitf */
   void Set_ToleranceG0Parameter(double iToleranceG0Parameter);

      /** @nodoc @nocgmitf */
   void Set_ToleranceSmoothSharpness(double iToleranceSmoothSharpness);

   /** @nodoc @nocgmitf */
   CATBoolean IsDoAssemblyParameterActivated();

   /** @nodoc @nocgmitf */
   CATBoolean IsPreviewParameterActivated();

   /** @nodoc @nocgmitf */
   CATBoolean IsToleranceG0ParameterActivated();

   /** @nodoc @nocgmitf */
   CATBoolean IsToleranceSmoothSharpnessParameterActivated();

   /** @nodoc @nocgmitf */
   void Activate_DoAssemblyParameter(CATBoolean iTurnOnOff);

   /** @nodoc @nocgmitf */
   void Activate_PreviewParameter(CATBoolean iTurnOnOff);

   /** @nodoc @nocgmitf */
   void Activate_ToleranceG0Parameter(CATBoolean iTurnOnOff);

   /** @nodoc @nocgmitf */
   void Activate_ToleranceSmoothSharpness(CATBoolean iTurnOnOff);


   /** @nodoc @nocgmitf */
   int GetDoAssemblyParameter();

   /** @nodoc @nocgmitf */
   CATBoolean GetPreviewParameterActivated();

   /** @nodoc @nocgmitf */
   double GetToleranceG0Parameter();

      /** @nodoc @nocgmitf */
   double GetToleranceSmoothSharpness();

private:	
	/** @nodoc @nocgmitf */
	CATCX_AuthorizedAnomaliesForCGMOperator(const CATCX_AuthorizedAnomaliesForCGMOperator& iAuthorizedAnomaliesForCGMOperator);
	/** @nodoc @nocgmitf */
	CATCX_AuthorizedAnomaliesForCGMOperator& operator = (const CATCX_AuthorizedAnomaliesForCGMOperator& iAuthorizedAnomaliesForCGMOperator);

	// Data
	//CATUnicodeString _OperatorID;

   //
	CATBoolean  _DoAssemblyParameterActivated;
   CATBoolean  _PreviewParameterActivated;
   CATBoolean  _ToleranceG0ParameterActivated;
   CATBoolean  _ToleranceSmoothSharpnessActivated;

   //
   int         _DoAssemblyParameter;
   CATBoolean  _PreviewParameter;
   double      _ToleranceG0Parameter;
   double      _ToleranceSmoothSharpness;
};

#endif
