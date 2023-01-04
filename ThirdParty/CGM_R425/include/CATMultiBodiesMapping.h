//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//=========================================================================
#ifndef CATMultiBodiesMapping_H
#define CATMultiBodiesMapping_H

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATBody.h"
#include "CATBody.h"

class CATBody;

class ExportedByCATTopologicalObjects CATMultiBodiesMapping
{

public :

	 // Constructeur with list of reference bodies to be mapped
	 // on list of resulting bodies mapped bodies
     CATMultiBodiesMapping ( CATTopData    * iTopData             ,
                             ListPOfCATBody* iReferenceBodiesList , 
		                     ListPOfCATBody* iResultBodiesList    );

	 // Constructeur with list of reference bodies to be mapped
	 // on list of resulting bodies mapped bodies
     CATMultiBodiesMapping ( ListPOfCATBody* iReferenceBodiesList , 
		                     ListPOfCATBody* iResultBodiesList    );

     virtual ~CATMultiBodiesMapping();

	 // Methode to set the tolerance for Multi Body mapping
	 void SetTolerance ( const double iTolerance );
	 
     virtual void Run();

	 // Global diagnostic of mapping

     enum CATMultiMappingDiag { OK = 0, KO };

     virtual CATMultiBodiesMapping::CATMultiMappingDiag GetDiagnostic() const;

	 // Get equivalent body or NULL if mapping has failed
     CATBody* GetEquivalentBody ( CATBody*  iReferenceBody ) const;

private :

     CATTopData   * _TopData;
	 int            _NbBodyToMap;
	 double         _Tolerance;

     ListPOfCATBody _ReferenceBodiesList;
     ListPOfCATBody _ResultBodiesList;
     ListPOfCATBody _EquivalentBodiesList;

     CATMultiBodiesMapping::CATMultiMappingDiag _MultiMappingDiag;

};


ExportedByCATTopologicalObjects CATMultiBodiesMapping *CATCreateMultiBodiesMapping(
                                                 CATTopData    * iTopData             ,
			                                     ListPOfCATBody* iReferenceBodiesList , 
		                                         ListPOfCATBody* iResultBodiesList    );

ExportedByCATTopologicalObjects CATMultiBodiesMapping *CreateMultiBodiesMapping(
			                                     ListPOfCATBody* iReferenceBodiesList , 
		                                         ListPOfCATBody* iResultBodiesList    );

ExportedByCATTopologicalObjects void Remove(CATMultiBodiesMapping *&ioMultiBodiesMapPointer);

#endif
