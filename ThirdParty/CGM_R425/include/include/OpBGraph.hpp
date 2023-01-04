// COPYRIGHT DASSAULT SYSTEMES 2013
#ifndef OpBGraph_HPP
#define OpBGraph_HPP
/* 
*  Ligth Interfaces Binding (For scalable and simple generic purpose)
*
*   For ZERO FootPrint (excluding live infrastructure prerequisite such as Fw System !! )
*      -> a kind of design ready for Fw SpecialAPI embedded :-)
*
*   and on demand Monitoring (some similary with V5PCSToolsPrivate )
*       but for more oriented for explicit applied domains indicators 
*       (rather than external Operating System capacity and scalability indicators) 
*/
#include "CATOpDataItf.hpp"
#include "OpIGraph.hpp"


namespace OpDataInterfaces
{

  /**
  * CATOpDataItf_GetDefaultModeler() : access default factory
  */
  extern "C" ExportedByCATOpDataItf  OpIFactory * CATOpDataItf_GetDefaultModeler();

} ;


 
#endif
