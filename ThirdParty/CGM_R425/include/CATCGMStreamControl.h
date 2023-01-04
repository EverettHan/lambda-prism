#ifndef CATCGMStreamControl_h_
#define CATCGMStreamControl_h_

#include "CATCGMStreamVersion.h"
#include "CATMathStream.h"

class CATMathStreamImpl;

class ExportedByCATMathStream CATCGMStreamControl 
{
public: 
	CATCGMStreamVersion   _VersionNumber;
	CATULONG64 _ControlFlag;

  // LoselessCompression Options
  static  CATBoolean _LoselessCompression_Maximal;
  static  CATBoolean _NoLoselessCompression_Desactivate;
  static  CATBoolean _NoLoselessCompressionInit;

  static void SetStaticLoselessCompressionOption();

	// constructor by default
	CATCGMStreamControl();
	~CATCGMStreamControl();

	CATCGMStreamControl& operator=(const CATCGMStreamControl& iOther);
	CATCGMStreamControl (const CATCGMStreamControl & iOther);

  int operator == (const CATCGMStreamControl & iToCompare) const;
  int operator != (const CATCGMStreamControl & iToCompare) const;


	void StreamAndSet(CATMathStream* Str, CATCGMStreamVersion iVersion);
  void UnstreamAndSet(CATMathStream* Str, CATCGMStreamVersion iVersion);

	void InitControlFlag(CATCGMStreamVersion iVersion, CATBoolean LoselessCompression_Maximal, CATULONG64 & oCoreMathStream);

	// remplacer la methode ResetDynamicVersions()
	void ResetStreamControl();

  INLINE int  IsSmallHeader() const;
  INLINE void SetSmallHeader();
	INLINE void ResetSmallHeader();

  INLINE int  IsScalableInteger() const;
  INLINE void SetScalableInteger();
	INLINE void ResetScalableInteger();

  INLINE int  IsRelativeTagValue() const;
  INLINE void SetRelativeTagValue();
	INLINE void ResetRelativeTagValue();

  INLINE int  IsObfuscation2009() const;
  INLINE void SetObfuscation2009();
	INLINE void ResetObfuscation2009();

  INLINE int  IsFixNbLinked() const;
  INLINE void SetFixNbLinked();
	INLINE void ResetFixNbLinked();

  INLINE int  IsRelativeTagObject() const;
  INLINE void SetRelativeTagObject();
	INLINE void ResetRelativeTagObject();

  INLINE int  IsNurbsCompact() const;
  INLINE void SetNurbsCompact();
	INLINE void ResetNurbsCompact();

  INLINE int  IsPOEC() const;
  INLINE void SetPOEC();
	INLINE void ResetPOEC();

  INLINE int  IsEdgeCompact() const;
  INLINE void SetEdgeCompact();
	INLINE void ResetEdgeCompact();

  INLINE int  IsLoopCompact() const;
  INLINE void SetLoopCompact();
	INLINE void ResetLoopCompact();

  INLINE int  IsAxisValue() const;
  INLINE void SetAxisValue();
	INLINE void ResetAxisValue();

  INLINE int  IsKnotVector() const;
  INLINE void SetKnotVector();
	INLINE void ResetKnotVector();

  INLINE int  IsShellCompact() const;
  INLINE void SetShellCompact();
	INLINE void ResetShellCompact();

  INLINE int  IsEdgeCurve() const;
  INLINE void SetEdgeCurve();
	INLINE void ResetEdgeCurve();

	INLINE int  IsSingleLoad() const;
  INLINE void SetSingleLoad();
	INLINE void ResetSingleLoad();

  INLINE int  IsLimitCompact() const;
  INLINE void SetLimitCompact();
	INLINE void ResetLimitCompact();

  INLINE int  IsNeutralEndian() const;
  INLINE void SetNeutralEndian();
	INLINE void ResetNeutralEndian();

	INLINE int  IsEndianConversion() const; 
  INLINE void SetEndianConversion();
	INLINE void ResetEndianConversion();

  INLINE int  IsFaceCompact() const; 

  INLINE int  IsLoopCompact2011() const; 

  INLINE int  IsPSplineCompact() const; 
  INLINE void SetPSplineCompact();

  INLINE int  IsNurbsCompact2011() const; 
  INLINE void SetNurbsCompact2011();

  INLINE int  IsLimitCompact2012Spring() const; 
  INLINE void SetLimitCompact2012Spring();
  INLINE void ResetLimitCompact2012Spring();

  INLINE int  IsCompactCoreAttribute() const; 
  INLINE void SetCompactCoreAttribute();

  INLINE int  IsPNurbsCompact() const; 
  INLINE void SetPNurbsCompact();

  INLINE int  IsKnotVector2012() const; 
  INLINE void SetKnotVector2012();

  INLINE int  IsPlaneCompact() const; 
  INLINE void SetPlaneCompact();

	INLINE int  IsNurbsCompact2015() const; 
  INLINE void SetNurbsCompact2015();

  

	void StreamOnly(CATMathStreamImpl* Str, CATCGMStreamVersion iVersion);

};



INLINE int CATCGMStreamControl::IsSmallHeader() const
{ return _ControlFlag & 0x01ULL; }
INLINE void CATCGMStreamControl::SetSmallHeader()
{ _ControlFlag |= 0x01ULL; }
INLINE void CATCGMStreamControl::ResetSmallHeader()
{ _ControlFlag &= ~(0x01ULL); }

INLINE int CATCGMStreamControl::IsScalableInteger() const
{ return _ControlFlag & 0x02ULL;}
INLINE void CATCGMStreamControl::SetScalableInteger()
{ _ControlFlag |= 0x02ULL; }
INLINE void CATCGMStreamControl::ResetScalableInteger()
{ _ControlFlag &= ~(0x02ULL); }

INLINE int CATCGMStreamControl::IsRelativeTagValue() const
{ return _ControlFlag & 0x04ULL;}
INLINE void CATCGMStreamControl::SetRelativeTagValue()
{ _ControlFlag |= 0x04ULL; }
INLINE void CATCGMStreamControl::ResetRelativeTagValue()
{ _ControlFlag &= ~(0x04ULL); }

INLINE int CATCGMStreamControl::IsObfuscation2009() const
{ return _ControlFlag & 0x08ULL;}
INLINE void CATCGMStreamControl::SetObfuscation2009()
{ _ControlFlag |= 0x08ULL; }
INLINE void CATCGMStreamControl::ResetObfuscation2009()
{ _ControlFlag &= ~(0x08ULL); }

INLINE int CATCGMStreamControl::IsFixNbLinked() const
{ return _ControlFlag & 0x10ULL;}
INLINE void CATCGMStreamControl::SetFixNbLinked()
{ _ControlFlag |= 0x10ULL; }
INLINE void CATCGMStreamControl::ResetFixNbLinked()
{ _ControlFlag &= ~(0x10ULL); }

INLINE int CATCGMStreamControl::IsRelativeTagObject() const
{ return _ControlFlag & 0x20ULL;}
INLINE void CATCGMStreamControl::SetRelativeTagObject()
{ _ControlFlag |= 0x20ULL; }
INLINE void CATCGMStreamControl::ResetRelativeTagObject()
{ _ControlFlag &= ~(0x20ULL); }

INLINE int CATCGMStreamControl::IsNurbsCompact() const
{ return _ControlFlag & 0x40ULL;}
INLINE void CATCGMStreamControl::SetNurbsCompact()
{ _ControlFlag |= 0x40ULL; }
INLINE void CATCGMStreamControl::ResetNurbsCompact()
{ _ControlFlag &= ~(0x40ULL); }

INLINE int CATCGMStreamControl::IsPOEC() const
{ return _ControlFlag & 0x80ULL;}
INLINE void CATCGMStreamControl::SetPOEC()
{ _ControlFlag |= 0x80ULL; }
INLINE void CATCGMStreamControl::ResetPOEC()
{ _ControlFlag &= ~(0x80ULL); }

INLINE int CATCGMStreamControl::IsLoopCompact() const
{ return _ControlFlag & 0x100ULL;}
INLINE void CATCGMStreamControl::SetLoopCompact()
{ _ControlFlag |= 0x100ULL; }
INLINE void CATCGMStreamControl::ResetLoopCompact()
{ _ControlFlag &= ~(0x100ULL); }

INLINE int CATCGMStreamControl::IsEdgeCompact() const
{ return _ControlFlag & 0x200ULL;}
INLINE void CATCGMStreamControl::SetEdgeCompact()
{ _ControlFlag |= 0x200ULL; }
INLINE void CATCGMStreamControl::ResetEdgeCompact()
{ _ControlFlag &= ~(0x200ULL); }

INLINE int CATCGMStreamControl::IsShellCompact() const
{ return _ControlFlag & 0x400ULL;}
INLINE void CATCGMStreamControl::SetShellCompact()
{ _ControlFlag |= 0x400ULL; }
INLINE void CATCGMStreamControl::ResetShellCompact()
{ _ControlFlag &= ~(0x400ULL); }

INLINE int CATCGMStreamControl::IsLimitCompact() const
{ return _ControlFlag & 0x800ULL;}
INLINE void CATCGMStreamControl::SetLimitCompact()
{ _ControlFlag |= 0x800ULL; }
INLINE void CATCGMStreamControl::ResetLimitCompact()
{ _ControlFlag &= ~(0x800ULL); }

INLINE int CATCGMStreamControl::IsKnotVector() const
{ return _ControlFlag & 0x1000ULL;}
INLINE void CATCGMStreamControl::SetKnotVector()
{ _ControlFlag |= 0x1000ULL; }
INLINE void CATCGMStreamControl::ResetKnotVector()
{ _ControlFlag &= ~(0x1000ULL); }

INLINE int CATCGMStreamControl::IsAxisValue() const
{ return _ControlFlag & 0x2000ULL;}
INLINE void CATCGMStreamControl::SetAxisValue()
{ _ControlFlag |= 0x2000ULL; }
INLINE void CATCGMStreamControl::ResetAxisValue()
{ _ControlFlag &= ~(0x2000ULL); }

INLINE int CATCGMStreamControl::IsEdgeCurve() const
{ return _ControlFlag & 0x4000ULL;}
INLINE void CATCGMStreamControl::SetEdgeCurve()
{ _ControlFlag |= 0x4000ULL; }
INLINE void CATCGMStreamControl::ResetEdgeCurve()
{ _ControlFlag &= ~(0x4000ULL); }

INLINE int CATCGMStreamControl::IsSingleLoad() const
{ return _ControlFlag & 0x8000ULL; }
INLINE void CATCGMStreamControl::SetSingleLoad()
{ _ControlFlag |= 0x8000ULL; }
INLINE void CATCGMStreamControl::ResetSingleLoad()
{ _ControlFlag &= ~(0x8000ULL); }


INLINE int CATCGMStreamControl::IsNeutralEndian() const
{ return _ControlFlag & 0x10000ULL;}
INLINE void CATCGMStreamControl::SetNeutralEndian()
{ _ControlFlag |= 0x10000ULL; }
INLINE void CATCGMStreamControl::ResetNeutralEndian()
{ _ControlFlag &= ~(0x10000ULL); }

INLINE int CATCGMStreamControl::IsEndianConversion() const
{ return _ControlFlag & 0x20000ULL; }
INLINE void CATCGMStreamControl::SetEndianConversion()
{ _ControlFlag |= 0x20000ULL; }
INLINE void CATCGMStreamControl::ResetEndianConversion()
{ _ControlFlag &= ~(0x20000ULL); }

INLINE int CATCGMStreamControl::IsFaceCompact() const
{ return _ControlFlag & 0x40000ULL; }
 
INLINE int CATCGMStreamControl::IsLoopCompact2011() const
{ return _ControlFlag & 0x80000ULL; }
 

INLINE int CATCGMStreamControl::IsPSplineCompact() const
{ return _ControlFlag & 0x100000ULL; }
INLINE void CATCGMStreamControl::SetPSplineCompact()
{ _ControlFlag |= 0x100000ULL; }
 
INLINE int CATCGMStreamControl::IsNurbsCompact2011() const
{ return _ControlFlag & 0x200000ULL; }
INLINE void CATCGMStreamControl::SetNurbsCompact2011()
{ _ControlFlag |= 0x200000ULL; }

INLINE int CATCGMStreamControl::IsLimitCompact2012Spring() const
{ return _ControlFlag & 0x400000ULL; }
INLINE void CATCGMStreamControl::SetLimitCompact2012Spring()
{ _ControlFlag |= 0x400000ULL; }
INLINE void CATCGMStreamControl::ResetLimitCompact2012Spring()
{ _ControlFlag &= ~(0x400000ULL);}

INLINE int CATCGMStreamControl::IsCompactCoreAttribute() const
{ return _ControlFlag & 0x800000ULL; }
INLINE void CATCGMStreamControl::SetCompactCoreAttribute()
{ _ControlFlag |= 0x800000ULL; }



INLINE int CATCGMStreamControl::IsKnotVector2012() const
{ return _ControlFlag & 0x1000000ULL; }
INLINE void CATCGMStreamControl::SetKnotVector2012()
{ _ControlFlag |= 0x1000000ULL; }

INLINE int CATCGMStreamControl::IsPlaneCompact() const
{ return _ControlFlag & 0x2000000ULL; }
INLINE void CATCGMStreamControl::SetPlaneCompact()
{ _ControlFlag |= 0x2000000ULL; }

INLINE int CATCGMStreamControl::IsPNurbsCompact() const
{ return _ControlFlag & 0x4000000ULL; }
INLINE void CATCGMStreamControl::SetPNurbsCompact()
{ _ControlFlag |= 0x4000000ULL; }

INLINE int CATCGMStreamControl::IsNurbsCompact2015() const
{ return _ControlFlag & 0x8000000ULL; }
INLINE void CATCGMStreamControl::SetNurbsCompact2015()
{ _ControlFlag |= 0x8000000ULL; }

#endif


