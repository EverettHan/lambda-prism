#ifndef CATSurParamReference_H
#define CATSurParamReference_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATSurParamReference : object made to handle the global and local parameters
// on a surface. 
//
// DESCRIPTION : this object ( ~ abstract ) implements the necessary methods to 
// convert global parameters to local parameters and vice versa on a surface.
// Theire are four virtual methods only should at least be overloaded, to ensure
// the function and the other ones if the gain of time is significant.
//
// IMPORTANT : their must be one and one only CATSurParamReference allocated 
// for each Surface that use the CATSurParam class, so that to ensure if two
// CATSurParam belong to the same surface, they only should a the same pointer
// on a CATSurParamReference.
//
// IMPORTANT TOO : this object must be derived to be valid. An abstract class
// of Surface should return a pointer to the CATDefaultSurParamReference in its
// method GetParamReference() and this one will call the methods of this object
// and throw an exception.
// Overloead class of surface must then return an overloaded CATSurParamReference,
// so that all will work proprely.
//
// Main Methods : ( the only ones that must absolutely be overloaded )
//    - ComputeGlobalToLocalU
//    - ComputeGlobalToLocalV
//    - COmputeLocalPositionU
//    - COmputeLocalPositionV
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
// 12/05/08 NLD Ajout CATGetDefaultSurParamReference() pour outillage de debug
//              Suppression CATDefaultSurParamReference
//
//=============================================================================

#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATMathPoint2D;
class CATParamData;
class CATCGMStreamCGMImpl;

class ExportedByCATCGMGeoMath CATSurParamReference : public CATCGMVirtual
{
public:
// //=============================================================================
// // Other methods used for the moment to ensure compatibility : will dissapear
// //=============================================================================
// // Those are kept to ensure compability
//   virtual double ComputeGlobalParameterU(const CATParamData & iPosition,
//                 void               * iImplementation) const;
  
//   virtual void ComputeLocalParametersU(const double &iGlobalParameter,
//                    void         *iImplementation,
//                    CATParamData &oPosition) const;

//   virtual double ComputeGlobalParameterV(const CATParamData & iPosition,
//                 void               * iImplementation) const;
  
//   virtual void ComputeLocalParametersV(const double &iGlobalParameter,
//                    void         *iImplementation,
//                    CATParamData &oPosition) const;

//=============================================================================
// METHODS OF COMPUTATION
//=============================================================================
// NOTE : if not overloaded, the four following methods will throw an error
// when called.
// Method to identify surface defined with only one patch 
  virtual CATLONG32 IsMonoPatch() const ;

// Methods to convert a global parameter to a local one
  virtual double ComputeGlobalParamU(const CATParamData &iLocalPosition) const ;
  virtual double ComputeGlobalParamV(const CATParamData &iLocalPosition) const ;
  virtual void   ComputeGlobalParams(const CATParamData &iLocalPositionU,  double &oGlobalParamU,
                                    const CATParamData &iLocalPositionV,  double &oGlobalParamV) const ;

// Methods to convert a local parameter to a global one
  virtual void ComputeLocalPositionU(double         iGlobalParam,
                 CATParamData & oPosition) const ;

  virtual void ComputeLocalPositionV(double         iGlobalParam,
                 CATParamData & oPosition) const ;

  virtual void ComputeLocalPositions(double iGlobalParamU, CATParamData &oPositionU, 
                            double iGlobalParamV, CATParamData &oPositionV) const ;

// mimize Patchnumber distance between  the output "CATParamData"
  virtual void ComputeLocalPositionU(double  iGlobalLowParam,  CATParamData & oLowPosition,
                 double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
  virtual void ComputeLocalPositionV(double  iGlobalLowParam,  CATParamData & oLowPosition,
                 double  iGlobalHighParam,  CATParamData & oHighPosition,
                 CATCGMStreamCGMImpl *iStream = NULL) const ;
//------------------------------------------------------------
// Added methods to enhance speed of certain operations
//------------------------------------------------------------
// Adding a global param to local positions
// The result may be the entry position ( to behave like += )
  virtual void AddGlobalToLocalU(const CATParamData     & iPositionU,
             double                   iMove,
             CATParamData           & oResultU) const;
  virtual void AddGlobalToLocalV(const CATParamData     & iPositionV,
             double                   iMove,
             CATParamData           & oResultV) const;

// Gives the difference between to local parameters : returns First - Second
  virtual double SubstractLocalParamU(const CATParamData & iFirstParam,
                  const CATParamData & iSecondParam) const ;
  virtual double SubstractLocalParamV(const CATParamData & iFirstParam,
                  const CATParamData & iSecondParam) const ;

// Conversion of an array of Global parameters to local ones : the result
// array must have been already allocated. The Global parameters are
// defined as two-dimensional points
  virtual void ConvertGlobalToLocal(const CATMathPoint2D* iGlobalParameters,
                CATLONG32          iCountParams,
                CATParamData *oResultsU,
                CATParamData *oResultsV) const;

// Reverse conversion of an local parameter to global ones : the output array of
// CATMathPoint2D must have been already allocated.
  virtual void ConvertLocalToGlobal(const CATParamData * iLocalPositionU,
                const CATParamData * iLocalPositionV,
                CATLONG32                 iCountParams,
                CATMathPoint2D     * oGlobalParmaeters) const;

};

//------------------------------------------------------------
// Default CATSurParamReference that send an exception
//------------------------------------------------------------
//extern ExportedByCATCGMGeoMath const CATSurParamReference CATDefaultSurParamReference;
extern ExportedByCATCGMGeoMath const CATSurParamReference& CATGetDefaultSurParamReference();


#endif
