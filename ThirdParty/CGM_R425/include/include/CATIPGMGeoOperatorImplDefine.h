#include "CATIPGMOperatorImplDefine.h"

// ---------- CATGeoOperator

/* Already defined in a parent class
int CATCGM_ITF_IMPL_CLASS::Run()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.Run();
}
*/

CATGeoOpTimer *CATCGM_ITF_IMPL_CLASS::GetTimer()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATGeoOperator &)HandledObject).GetTimer(); // OVERRIDEN IN CATPConicsComputation
}

/* Already defined in a parent class
CATIPGMTopOperator *CATCGM_ITF_IMPL_CLASS::IsTopological()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsTopological();
}
*/
