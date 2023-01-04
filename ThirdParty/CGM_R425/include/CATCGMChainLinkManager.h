#ifndef CATCGMChainLinkManager_h
#define CATCGMChainLinkManager_h

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATCGMUnit.h"
#include "CATListPV.h"


class CATBody;
class CATGeoFactory;
class CATCGMUnit;

class ExportedByCATTopologicalObjects CATCGMChainLinkManager
{
 public:
   CATCGMChainLinkManager();
   virtual ~CATCGMChainLinkManager();

  
   void Dump (CATCGMOutput & ioWhereToWrite, int iIndent = 0);
 
   typedef struct  
   {
	CATBody *_BodyResult;    // le body qui fait le lien entre 2 operations unit
	CATCGMUnit *_UnitResult; // l'unit qui produit le _BodyResult

	CATCGMUnit *_UnitToLink; // L'unit qui demande le _BodyResult en entrée
	CATBody *_NewBody;       // le nouveau body calculé dans le dernier run du _UnitResult 
	                         // et qui doit remplacer le _BodyResult
   } UnitsLink;


   void AddNewLink ( CATCGMUnit *iUnitWithResult, CATBody *iResult, CATCGMUnit *iUnitToLink);
   CATBody *GetNewBody (CATBody *iOldBody);
   void UpdateLinksWithNewResult (CATBody *iOldResult, CATBody *iNewResult);
   void GetUnitPrerequisits (CATCGMUnit *iUnit, ListPOfCATCGMUnit &Prec);
   int Size ();
   void RemoveAll ();


  
 
private:
   CATListPV       _Links;   // Liste des liens UnitsLink entre les units produite dans AddNewLink
 
};


#endif
