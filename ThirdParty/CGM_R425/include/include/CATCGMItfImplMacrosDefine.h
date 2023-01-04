#include "CATCGMItfInternalData.h"

/**
 * Macros for defining implementations of CGM interfaces.
 * @param CATCGM_ITF_CONCRETE_CLASS
 *   Name of the concrete class to be interfaced.<br>
 *   Example: <tt>CATSpecialOperator</tt>
 * @param CATCGM_ITF_CONCRETE_METACLASS
 *   Name of the concrete class' method to call in order to get the concrete static meta class.<br>
 *   Example: <tt>CATSpecialOperator_MetaClass</tt>
 * @param CATCGM_ITF_CLASS
 *   Name of the interface.<br>
 *   Example: <tt>CATICGMSpecialOperator</tt>
 * @param CATCGM_ITF_METACLASS
 *   Name of the method to call in order to get the interface's static meta class.<br>
 *   Example: <tt>CATICGMSpecialOperator_MetaClass</tt><br>
 *   Pay attention: this method is handled by the implementation of the interface,
 *   and not by the interface itself: it's useless to expose more of our internal data.
 * @param CATCGM_ITF_IMPL_CLASS
 *   Name of the implementation class of the interface = the class to be defined.
 * @param CATCGM_ITF_PARENT_ITF_METACLASS
 *   Full name of the method to call in order to get the parent interface's static meta class.<br>
 *   Example: <tt>CATICGMVirtualImpl::CATICGMVirtual_MetaClass</tt><br>
 * @param CATCGM_ITF_EXPORTED_BY
 *   Macro used to export symbols of the module.<br>
 *   Example: <tt>ExportedByMyModule</tt>
 */

#undef CATCGM_ITF_CONCRETE_CLASS
#undef CATCGM_ITF_CONCRETE_METACLASS

#undef CATCGM_ITF_CLASS
#undef CATCGM_ITF_METACLASS
#undef CATCGM_ITF_CLASS_IID

#undef CATCGM_ITF_IMPL_CLASS
#undef CATCGM_ITF_PARENT_ITF_METACLASS
#undef CATCGM_ITF_EXPORTED_BY
