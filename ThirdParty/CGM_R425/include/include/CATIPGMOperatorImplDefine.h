#include "CATIPGMVirtualImplDefine.h"
#include "CATThrowForNullPointer.h"
#include "CATCGMItfProtectedServices.h"
#include "CATICGMOperator.h"

// ---------- CATCGMOperator

int CATCGM_ITF_IMPL_CLASS::Run()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATCGMOperator &)HandledObject).Run(); // OVERRIDEN IN CATTopCheckJournal
}

CATGeoFactory *CATCGM_ITF_IMPL_CLASS::GetFactory() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATCGMOperator &)HandledObject).GetFactory(); // OVERRIDEN IN CATSolidPrimitive
}

const CATString *CATCGM_ITF_IMPL_CLASS::GetOperatorId()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATCGMOperator &)HandledObject).GetOperatorId(); // OVERRIDEN IN CATLayDownOperatorImpl
}

void CATCGM_ITF_IMPL_CLASS::SetOperatorId(const CATString iOperatorName)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetOperatorId(iOperatorName);
}

void CATCGM_ITF_IMPL_CLASS::EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.EnableInterrupt(ipInterruptFunction);
}

CATSoftwareConfiguration *CATCGM_ITF_IMPL_CLASS::GetSoftwareConfiguration() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSoftwareConfiguration();
}

CATIPGMTopOperator *CATCGM_ITF_IMPL_CLASS::IsTopological()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  CATTopOperator *pOperator = ((CATCGMOperator &)HandledObject).IsTopological(); // OVERRIDEN IN CATTopOperator...
  if (pOperator == NULL)
    return NULL; // <<<<<<<<
  else if (pOperator == (CATTopOperator *)&HandledObject)
    return (CATIPGMTopOperator *)this; // <<<<<<<< QueryInterface can't be used because the returned object won't be released...
  else
    CATThrowForNullPointerReturnValue(NULL);return NULL;//NLD071211 pour compilation OK si macro CATThrowForNullPointerReturnValue vide
}

void CATCGM_ITF_IMPL_CLASS::DefineFactory(CATGeoFactory *Factory)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.DefineFactory(Factory);
}

CATULONG32 CATCGM_ITF_IMPL_CLASS::GetSessionIdentifier()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSessionIdentifier();
}

void CATCGM_ITF_IMPL_CLASS::SetWarningMode(CATCGMWarning iMode)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetWarningMode(iMode);
}

CATCGMWarning CATCGM_ITF_IMPL_CLASS::GetWarningMode() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetWarningMode();
}

void CATCGM_ITF_IMPL_CLASS::GetResultStatus(short &ioValidation, short &ioModifiable) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetResultStatus(ioValidation, ioModifiable);
}

void CATCGM_ITF_IMPL_CLASS::SetResultStatus(const short iValidation, const short iModifiable)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetResultStatus(iValidation, iModifiable);
}

short CATCGM_ITF_IMPL_CLASS::GetNumberOfReplay()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetNumberOfReplay();
}
 
CATExtGeoOperator *CATCGM_ITF_IMPL_CLASS::GetExtensible(CATBoolean iRequired) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetExtensible(iRequired);
}

HRESULT CATCGM_ITF_IMPL_CLASS::DumpObjects(
    const unsigned int iOptions,
    CATechAttribute *iOutput,
    CATechSet *iJournaling)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.DumpObjects(
    iOptions,
    iOutput,
    iJournaling);
}

