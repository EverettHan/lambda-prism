#ifndef CATSurTo2DMapping_H
#define CATSurTo2DMapping_H

/** @CAA2Required */

// 
// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATSurTo2DMapping:
// Virtual class of mapping between CATsurface and 2 coordinates
//
//==========================================================================
//
// Usage notes:
//      This virtual Object describes the mapping between one CATSurface and a
//       virtual  2 dimension space 
//       The derivation of this Object is generally created with derivation of 
//        CATSurTo2DGlobalMapping 
//        
//       
//	Methods :
//             - Eval     ( CATSurface to 2D space , first derivatives optionnal)
//             - InvEval  (   2D space to CATSurface, first derivatives optionnal)
//             - Get Reference    
//
//==========================================================================
#include "Connect.h"

#include "CATSurParam.h"
#include "CATSurface.h"
#include "CATMathVector2D.h" 
#include "CATSurLimits.h" 
#include "CATMathInterval2D.h" 
#include "CATCGMVirtual.h"

#include "CATIAV5Level.h"
#include "CATCGMOperator.h"
#include "CATMappingValidity.h"

//-----------------------------------------------------------------------------
class ExportedByConnect CATSurTo2DMapping : public CATCGMOperator

  {
  CATCGMVirtualDeclareClass(CATSurTo2DMapping);
public :
  //-------------
  // Constructor
  //-------------
  CATSurTo2DMapping(CATGeoFactory *iFactory, const CATSurface * iReference, const CATSurLimits * iLimOnRef=0);
  //-------------
  // Destructor
  //-------------
  virtual ~CATSurTo2DMapping();
  //-------------
  // Evaluators
  //-------------
  //  Returned Boolean value is 0 if evalution (or inverse) is possible.
  //                            1 if not (outside bound evaluation for example).
  //  Direct evaluation 
  //   You can use either CATSurParam or GlobalParameter on CATSurface ( consistent with GetGlobalEquation )
  virtual CATBoolean Eval(const CATSurParam & iParam, double &oX,double &oY ) const ;
  
  virtual CATBoolean Eval(const CATSurParam & iParam,
                          double &oX,double &oY,
                          double &oDXDU,double &oDXDV,  
                          double &oDYDU,double &oDYDV ) const ;
  
  virtual CATBoolean Eval(const double iU, const double iV,
                          double &oX,double &oY ) const = 0;
  
  virtual CATBoolean Eval(const double iU, const double iV,
                          double &oX,double &oY,
                          double &oDXDU,double &oDXDV,  
                          double &oDYDU,double &oDYDV ) const = 0;
  
  //  Inverse evaluation 
  //   You can use either CATSurParam or GlobalParameter on CATSurface ( consistent with GetGlobalEquation )  
  virtual CATBoolean InvEval(const double iX,const double iY, CATSurParam &oParam  ) const ;
  
  virtual CATBoolean InvEval(const double iX,const double iY,
                             CATSurParam &oParam,
                             CATMathVector2D &oDX ,
                             CATMathVector2D &oDY ) const ;
  
  virtual CATBoolean InvEval(const double iX, const double iY, double &oU, double &oV ) const = 0;
  
  virtual CATBoolean InvEval(const double iX,const double iY,
                             double &oU,double &oV,
                             double &oDUDX,double &oDUDY,
                             double &oDVDX,double &oDVDY ) const = 0;
  
  //----------------------
  // Validity of the mapping . Describe information regarding local validity of Mapping
  //---------------------- 
  
  enum CATMappingValidity{ ValidOnDomain = CATMappingValidOnDomain, PartiallyValidOnDomain = CATMappingPartiallyValidOnDomain, NotValidOnDomain = CATMappingNotValidOnDomain} ;
  
  //return TRUE if the image can be computed. 
  //Else the Interval doesn't necesarly contain the true image.
  virtual CATBoolean ComputeImage(CATMathInterval2D & oImage);
  
  //return TRUE if inverse functions are well defined on iImage.
  //(Only in DevDev case with radiantness).
  virtual CATBoolean CheckInvImage(CATMathInterval2D & iImage);
  
  //----------------------
  // Set and Get Methods 
  //---------------------- 
  inline void GetReference(const CATSurface * &oReference)  const ;
  
  inline void GetReferenceLimits(CATSurLimits &oLimits)  const ;
  
  inline CATSurTo2DMapping::CATMappingValidity GetValidity()  const ;
  
  
protected :
  
  //----------------------
  // DATA 
  //---------------------- 
  const CATSurface * _Reference;
  CATSurLimits       _LimRef;
  const CATMathFunctionXY * _RefFx,* _RefFy,* _RefFz;
  CATMappingValidity _Validity;
  
};
//
// ------------------------------------------------------------------------------
//
// Inlines
//
// ------------------------------------------------------------------------------
//
inline void CATSurTo2DMapping::GetReference(const CATSurface * &oReference)  const
{
  oReference = _Reference;
}

inline void CATSurTo2DMapping::GetReferenceLimits(CATSurLimits &oLimits)  const
{
  oLimits=_LimRef;
}

inline CATSurTo2DMapping::CATMappingValidity CATSurTo2DMapping::GetValidity()  const
{
  return _Validity;
}
#endif
