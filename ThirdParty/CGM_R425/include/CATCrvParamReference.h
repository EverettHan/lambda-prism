#ifndef CATCrvParamReference_H
#define CATCrvParamReference_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATCrvParamReference : object made to handle the global and local parameters
// on a curve. 
//
// DESCRIPTION : this object ( ~ abstract ) implements the necessary methods to 
// convert global parameters to local parameters and vice versa on a curve.
// The four pure virtual methods only should at least be overloaded, and the
// other ones if the gain of time is significant.
//
// IMPORTANT : their must be one and one only CATCrvParamReference allocated 
// for each curve that use the CATCrvParam class, so that to ensure if two
// CATCrvParam belong to the same curve, they only should a the same pointer
// on a CATCrvParamReference.
//
// IMPORTANT TOO : this object must be derived to be valid. An abstract class
// of curve should return a pointer to the CATDefaultCrvParamReference  (defined
// here) in its method GetParamReference() and this one will call the methods of
// this object and throw an exception.
// Overloead class of surface must then return an overloaded CATCrvParamReference,
// so that all will work proprely.
//
// Main Methods : ( the only ones that must absolutely be overloaded )
//    - ComputeGlobalToLocal
//    - ComputeLocalPosition
//  
//=============================================================================
// Abstract Class     : Yes
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// History
//
// Aug. 97   Jose CHILLAN (jch)    Creation            
//
// 12/05/08 NLD Ajout CATGetDefaultCrvParamReference() pour outillage de debug
//              Suppression CATDefaultCrvParamReference
//=============================================================================

#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATParamData;

class ExportedByCATCGMGeoMath CATCrvParamReference : public CATCGMVirtual
{
public:
// //------------------------------------------------------------
// // Methods to ensure compatibility of the datas ( will be soon removed)
// //-------------------------------------------------------------
//   virtual double ComputeGlobalParameter(const CATParamData & iPosition,
// 					void               * iImplementation) const;
  
//   virtual void ComputeLocalParameters(const double &iGlobalParameter,
// 				      void         *iImplementation,
// 				      CATParamData &oPosition) const;

//=============================================================================
// METHODS OF COMPUTATION
//=============================================================================
// NOTE : if not overloaded, the four following methods will throw an error
// when called.

// Methods to convert a global parameter to a local one
  virtual double ComputeGlobalParam(const CATParamData &iLocalPosition) const ;
 
// Methods to convert a local parameter to a global one
  virtual void ComputeLocalPosition(double         iGlobalParam,
				    CATParamData & oPosition) const ;
// mimize Patchnumber distance between  the output "CATParamData"
  virtual void ComputeLocalPositions(double  iGlobalLowParam,  CATParamData & oLowPosition,
				     double  iGlobalHighParam,  CATParamData & oHighPosition) const ;
//------------------------------------------------------------
// Added methods to enhance speed of certain operations
//------------------------------------------------------------
// Adding a global param to local positions
// The result may be the entry position ( to behave like += )
  virtual void AddGlobalToLocal(const CATParamData     & iPosition,
				double                   iMove,
				CATParamData           & oResult) const;

// Gives the difference between to local parameters : returns First - Second
  virtual double SubstractLocalParam(const CATParamData & iFirstParam,
				     const CATParamData & iSecondParam) const ;

// Compute the barycenter of to local parameters ( result is (1-lambda)P1 + P2)
  virtual void ComputeBarycenter(const CATParamData & iFirstParam,
				 const CATParamData & iSecondParam,
				 double               iLambda,
				 CATParamData       & oResult) const;


// Conversion of an array of Global parameters to local ones : the result
// array must have been already allocated
  virtual void ConvertGlobalToLocal(const double* iGlobalParam,
				    CATLONG32          iCountParams,
				    CATParamData *oResults) const;

// Reverse conversion of an local parameter to global ones : the output array of double
// must have been already allocated.
  virtual void ConvertLocalToGlobal(const CATParamData * iLocalPositions,
				    CATLONG32                 iCountParams,
				    double             * oGlobalParmaeters) const;
};

//------------------------------------------------------------
// Default CATSurParamReference that send an exception
//------------------------------------------------------------
//extern ExportedByCATCGMGeoMath const CATCrvParamReference CATDefaultCrvParamReference;
extern ExportedByCATCGMGeoMath const CATCrvParamReference& CATGetDefaultCrvParamReference();

#endif
