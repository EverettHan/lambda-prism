
/*
=============================================================================

 COPYRIGHT   : DASSAULT SYSTEMES 2004
 
 DESCRIPTION : LayDown For Parallal method
               LayDown a wire for parallel and give an error if not nay down and build a journal
               without laydown on shell

=============================================================================
*/
#ifndef CATBooleanCleanerForOperator_H
#define CATBooleanCleanerForOperator_H

#include "ExportedByCATTopologicalObjects.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATTopOperator;

ExportedByCATTopologicalObjects void CATBooleanCleanerForOperator(CATGeoFactory * iFacto, CATTopData * iData,CATBody * iSupport, CATTopOperator * iOpe);

#endif


