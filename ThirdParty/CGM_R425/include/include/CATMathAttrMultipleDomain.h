// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathAttrMultipleDomain
// Class used to define the mode of decomposition of the dimension for
// a sampled curve, and allow to go until a max domain.
//
//=============================================================================
//
// Usage notes:
// The curve may be parametric (t->M(t)) or implicit (F(X)=0).
// This attribute allow to sample the curve until a bigger domain
// when not all the coordonates are out of the domain.
// It is usefull for the draft, the fillet and the three tangency for example.
//=============================================================================

#ifndef CATMathAttrMultipleDomain_H
#define CATMathAttrMultipleDomain_H

#include "YN000FUN.h"
#include "CATMathInline.h"
#include "CATMathAttribute.h"
class CATMathIntervalND;
//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathAttrMultipleDomain : public CATMathAttribute
{
  public:
//--------------
//  Constructors
//---------------
  // iNumber = The number of subsets that you want.
  // Tab = array of the repartition giving the count of coordinates
  // in each subset. Ex: Ex: for two subsets of 2 coordinates in dimension 4
  // Tab[0] = 2; Tab[1] = 2.

// Use this constructor if you just want to sample the curve on  several domains.
CATMathAttrMultipleDomain (const CATLONG32 iNumber, CATLONG32 *Tab,
			   const CATLONG32 iDim,const CATMathIntervalND *Domain);
// Use this constructor if you want to sample the curve until the boundaries of several domains.
// The curve won't be sampling on all its length but only until the max boundaries of specified domains.
// The domains whose saturation is mandatory are defined by TRUE in MandatorySatTab.
CATMathAttrMultipleDomain (const CATLONG32 iNumber, CATLONG32 *iTab, CATBoolean * iMandatorySatTab,
			   const CATLONG32 iDim,const CATMathIntervalND *iDomain);
// Use this constructor if you want to manage several domains,
// and a constraint.
CATMathAttrMultipleDomain (const CATLONG32 iNumber, CATLONG32 *Tab,const CATLONG32 iDim,
			   const CATLONG32 iConst,const CATMathIntervalND *Domain);
//--------------
//  Destructors
//---------------
~CATMathAttrMultipleDomain ();
//---------------
//  Other Methods
//---------------
CATMathAttrId GetType() const;
CATBoolean IsExclusive() const;
//
// 
// Return the number of domain required.
INLINE CATLONG32 GetMultipleDomainNumber () const;
// Return if a constraint in max domain is required.
INLINE CATLONG32 GetConstraints () const;
// Return the way of decomposition.
INLINE const CATLONG32 *GetMultipleDomainTab () const;
// Return the tab with the mandatory saturation requests.
INLINE const CATBoolean *GetMandatorySaturationTab () const;
// Return the values of the max domain.
INLINE const CATMathIntervalND *GetDomain () const;
//
//
  private:
    CATLONG32 _NumberOfMultipleDomain;
    CATLONG32 _Dim, _Constraints;
    CATLONG32 *_TabOfMultipleDomain;
    CATBoolean * _TabOfMandatorySaturations;
    const CATMathIntervalND *_Domain;
};

//-----------------------------------------------------------------------------
//                             INLINE
//-----------------------------------------------------------------------------
INLINE CATLONG32  CATMathAttrMultipleDomain::GetMultipleDomainNumber () const {
	return _NumberOfMultipleDomain;
}
INLINE const CATLONG32 * CATMathAttrMultipleDomain::GetMultipleDomainTab () const {
	return _TabOfMultipleDomain;
}
INLINE const CATBoolean *CATMathAttrMultipleDomain::GetMandatorySaturationTab () const
{
  return _TabOfMandatorySaturations;
}
INLINE const CATMathIntervalND * CATMathAttrMultipleDomain::GetDomain () const {
	return _Domain;
}
INLINE CATLONG32 CATMathAttrMultipleDomain::GetConstraints () const {
	return _Constraints;
}

#endif
