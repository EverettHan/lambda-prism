// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNativeAttributes.h
//
//===================================================================
// May 2011  Creation: NDO
//===================================================================
#ifndef CATPolyBodyNativeAttributes_H
#define CATPolyBodyNativeAttributes_H

#include "PolyBodyTools.h"
#include "CATPolyBodyBaseAttributes.h"
#include "CATBoolean.h"

class CATPolyBody;
class CATIPolyPrimitiveSupport;


/*
 * Default attribute class for a CATPolyBody.
 * These attributes may be used by non-native CATPolyBody instances.
 *
 * For native CATPolyBody instances, use CATPolyBodyNativeAttributes.
 * @see CATPolyBodyNativeAttributes
 */
class ExportedByPolyBodyTools CATPolyBodyDefaultAttributes : public CATPolyBodyBaseAttributes
{

public:

  CATPolyBodyDefaultAttributes (const CATPolyBody& iPolyBody);
  ~CATPolyBodyDefaultAttributes ();

public:

  /*
   * Sets the ID of the CATPolyBody.
   */
  inline void SetID (const unsigned int iID);

  /*
   * Sets the sag of the CATPolyBody.
   */
  inline void SetSag (const double iSag);

  /**
   * Specifies whether a CATPolyBody contains domains of a specific dimension (0, 1, 2 or 3).
   */
  void SetDomainDimension (unsigned int dim, CATBoolean iTrueOrFalse);

public:

  HRESULT GetID (unsigned int& oID) const;

  HRESULT GetSag (double& oSag) const;

  HRESULT GetSupport (CATIPolyPrimitiveSupport*& oSupport) const;

  HRESULT SetSupport (CATIPolyPrimitiveSupport* iSupport);

  HRESULT GetStreamer (CATIPolyBodyStreamer*& oStreamer) const;

  CATBoolean IsStreamable (const CATMathStream& iStream) const;

public:

  static const CATPolyBodyDefaultAttributes* Cast (const CATIPolyBodyAttributes* iAttributes);
  static CATPolyBodyDefaultAttributes* Cast (CATIPolyBodyAttributes* iAttributes);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

private:

  double _Sag;
  unsigned int _ID;

  CATIPolyPrimitiveSupport* _Support;

  static const CLSID _ClassID;

};

inline void CATPolyBodyDefaultAttributes::SetID (const unsigned int iID)
{
  _ID = iID;
}

inline void CATPolyBodyDefaultAttributes::SetSag (const double iSag)
{
  _Sag = iSag;
}


/*
 * Attribute class for native CATPolyBody instances.
 * A native CATPolyBody instance refers to polyhedral surfaces, curves and points exclusive to the PolyhedralObjects framework.
 */
class ExportedByPolyBodyTools CATPolyBodyNativeAttributes : public CATPolyBodyDefaultAttributes
{

public:

  CATPolyBodyNativeAttributes* CastAsNativeAttributes () { return this; }
  const CATPolyBodyNativeAttributes* CastAsNativeAttributes () const { return this; }

  inline static const CATPolyBodyNativeAttributes* Cast (const CATIPolyBodyAttributes* iAttributes);
  inline static CATPolyBodyNativeAttributes* Cast (CATIPolyBodyAttributes* iAttributes);

private:

  CATPolyBodyNativeAttributes (const CATPolyBody& iPolyBody) : CATPolyBodyDefaultAttributes (iPolyBody) {}

  friend class CATPolyBody;

};

const CATPolyBodyNativeAttributes* CATPolyBodyNativeAttributes::Cast (const CATIPolyBodyAttributes* iAttributes)
{
  return iAttributes ? iAttributes->CastAsNativeAttributes () : 0;
}

CATPolyBodyNativeAttributes* CATPolyBodyNativeAttributes::Cast (CATIPolyBodyAttributes* iAttributes)
{
  return iAttributes ? iAttributes->CastAsNativeAttributes () : 0;
}

#endif // !CATPolyBodyNativeAttributes_H
