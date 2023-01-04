// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBaseAttributes.h
//
//===================================================================
// May  2011  Creation: NDO
// June 2014  Modification JXO: Geometric diagnosis
// Nov  2018  Modification JXO: Certificate
//===================================================================
#ifndef CATPolyBodyBaseAttributes_H
#define CATPolyBodyBaseAttributes_H

#include "PolySupports.h"
#include "CATIPolyBodyAttributes.h"
#include "CATPolyBodyFlags.h"
#include "CATPolyBodyDiagnosis.h"
#include "CATPolyBodyGeoDiagnosis.h"
#include "CATBoolean.h"

class CATPolyBody;
class CATPolyBodyCertificate;


/*
 * Generic implementation of an attribute class.
 * Implementation of specific attributes can derive from this class.
 */
class ExportedByPolySupports CATPolyBodyBaseAttributes : public CATIPolyBodyAttributes
{

public:

  CATPolyBodyBaseAttributes (const CATPolyBody& iPolyBody);
  ~CATPolyBodyBaseAttributes ();

public:

/** @name Methods to override in derived classes.
    Default implementation of these methods does not do anything.
    @{ */

  virtual HRESULT GetID (unsigned int& oID) const;

  virtual HRESULT GetSag (double& oSag) const;

  virtual HRESULT GetTolerance (const CATTolerance*& oTolerance) const;

  virtual HRESULT GetSupport (CATIPolyPrimitiveSupport*& oSupport) const;
  virtual HRESULT SetSupport (CATIPolyPrimitiveSupport* iSupport);

  virtual HRESULT GetDiagnosis (CATPolyBodyDiagnosis*& oDiagnosis);
  virtual HRESULT GetGeoDiagnosis (CATPolyBodyGeoDiagnosis*& oDiagnosis);

  virtual int DoesBodyContainDomainsOfDimension (unsigned int iDimension) const;

  virtual HRESULT GetStreamer (CATIPolyBodyStreamer*& oStreamer) const;

  virtual CATBoolean IsStreamable (const CATMathStream& iStream) const;

/** @} */

public:

/** @name Methods with a meaningful default implementation.
    @{ */

  virtual HRESULT IsValid () const;

  virtual HRESULT IsTopologicallyWatertight () const;

  virtual HRESULT IsGeometricallyWatertight () const;

  virtual HRESULT HasFaceEdges () const;

  virtual unsigned int SizeOf () const;

  inline static CATPolyBodyBaseAttributes* Cast (CATIPolyBodyAttributes* iAttributes);
  inline static const CATPolyBodyBaseAttributes* Cast (const CATIPolyBodyAttributes* iAttributes);

/** @} */

protected:

  CATPolyBodyBaseAttributes* CastAsBaseAttributes () {return this;}
  const CATPolyBodyBaseAttributes* CastAsBaseAttributes () const { return this; }

protected:
  friend class CATPolyBodyGeoServicesHelper;
  friend class CATPolyBodyGeoChecker;
  CATPolyBodyFlags & GetFlags() const;

protected:
  const CATPolyBody& _PolyBody;
  mutable CATPolyBodyFlags _Flags;
  mutable CATPolyBodyDiagnosis _Diagnosis;
  mutable CATPolyBodyGeoDiagnosis _GeoDiagnosis;
private:
  /** No addref/release */
  CATPolyBodyCertificate * GetCertificate();
private:
  mutable CATPolyBodyCertificate * m_certificate;
};

inline CATPolyBodyBaseAttributes* CATPolyBodyBaseAttributes::Cast (CATIPolyBodyAttributes* a)
{
  return a ? a->CastAsBaseAttributes () : 0;
}

inline const CATPolyBodyBaseAttributes* CATPolyBodyBaseAttributes::Cast (const CATIPolyBodyAttributes* a)
{
  return a ? a->CastAsBaseAttributes () : 0;
}

#endif // !CATPolyBodyBaseAttributes_H
