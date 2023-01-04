#ifndef CATCGMChain_h
#define CATCGMChain_h

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATCGMUnit.h"
//#include "CATListPV.h"
#include "CATCGMChainLinkManager.h"
#include  "CATICGMObject.h" 
#include "CATPGMChain.h"
#include "ListPOfCATCGMChain.h"


class CATBody;
class CATGeoFactory;
class CATCGMUnit;
class CATCGMChainLinkManager;
class CATString;
class CATCGMStream;

/*
typedef struct  
{
	CATBody *_BodyResult;    // le body qui fait le lien entre 2 operations unit
	CATCGMUnit *_UnitResult; // l'unit qui produit le _BodyResult

	CATCGMUnit *_UnitToLink; // L'unit qui demande le _BodyResult en entrée
	CATBody *_NewBody;       // le nouveau body calculé dans le dernier run du _UnitResult 
	                         // et qui doit remplacer le _BodyResult
} UnitsLink;
*/
class ExportedByCATTopologicalObjects CATCGMChain : public CATPGMChain
{
	//CATCGMVirtualDeclareClass(CATCGMChain);
 public:
   CATCGMChain(CATGeoFactory*);
   virtual ~CATCGMChain();

   //-------------------------------------------------------------------------
   // Monitoring the recording process  
   //-------------------------------------------------------------------------
   static  void         SetCurrentCATCGMChain( CATCGMChain * iChain);
   static  CATCGMChain* GetCurrentCATCGMChain();
  


   //-------------------------------------------------------------------------
   // RECORDING : Creating the chain structure  
   //-------------------------------------------------------------------------

   // @nocgmitf
   void SetFactory (CATGeoFactory* iFactory);
   // @nocgmitf
   void Append (CATCGMUnit * iUnit);
    // @nocgmitf
   virtual CATCGMUnit * CreateUnitFromName (const CATString  *iName);
   // @nocgmitf
   CATCGMUnit *         GetUnitForOperator (CATTopOperator * iOp);



   //-------------------------------------------------------------------------
   // RUN : to run the chain structure  
   //-------------------------------------------------------------------------

   
   // @nocgmitf
  // void BuildLinksBetweenUnits ();
   void Reset ();   //reset of the links !!!!
   // @nocgmitf
   HRESULT Run (CATBoolean WithFast=FALSE);
   // @nocgmitf
   HRESULT Run (int i, CATBoolean WithFast=FALSE); // one run only 
   // @nocgmitf
   void GetNewBodies (CATLISTP(CATBody)& Old, CATLISTP(CATBody)& New);
 
   //-------------------------------------------------------------------------
   // BROWSE : to dump the chain structure  
   //-------------------------------------------------------------------------
   // @nocgmitf
   void Dump (CATCGMOutput & ioWhereToWrite, int iIndent = 0);
   // @nocgmitf
   int GetNbUnits ();
   // @nocgmitf
   int GetNbInactiveUnits ();
   // @nocgmitf
   CATCGMUnit * GetUnit (int i);
   // @nocgmitf
   int GetUnitIndex (CATCGMUnit *iunit); 
    // @nocgmitf
   CATGeoFactory *      GetFactory ();
   // @nocgmitf
   void GetPrec (CATCGMUnit * iUnit, ListPOfCATCGMUnit& olist);
   // @nocgmitf
   CATULONG32  GetSessionIdentifier()const;

   //-------------------------------------------------------------------------
   // MODIFY : to modify the chain structure  
   //-------------------------------------------------------------------------

   void Inactivate (CATCGMUnit *iunit);
   void DeleteInactiveUnits ();

private :
    int _NbInactives;

 public :

   //-------------------------------------------------------------------------
   // STEAM/UNSTREAM  
   //-------------------------------------------------------------------------
	 
   // @nocgmitf
   void	 Stream (CATCGMStream * iStream);
   // @nocgmitf
   void  Unstream (CATCGMStream * iStream);


 

private :
   void WriteChainData (CATCGMStream* iStream);
   void GetLinkedGeometry (CATLISTP(CATICGMObject)&  CGMLinkedObjectList);
   void WriteGeometry(CATCGMStream *iGeoStr,  CATLISTP(CATICGMObject)& CGMLinkedObjectList);


  
   virtual CATCGMUnit*  CreateUnitFromStream  (CATCGMStream*  iStream);
   CATGeoFactory *ReadGeometry ( CATCGMStream* iStream, CATLISTP(CATICGMObject) &ioCGMLinkedObjectList);
   void ReadChainData (CATCGMStream* iStream );
   void SetlinkedObjects (CATLISTP(CATICGMObject) &iCGMLinkedObjectList);



 private:
   void GetUnitsUsingBody (CATBody *iBody, ListPOfCATCGMUnit& olist);
  // void Reset ();
   void BuildLinksBetweenUnits ();


  
private:

   CATGeoFactory * _factory;
   ListPOfCATCGMUnit _LUnit;


   CATCGMChainLinkManager _UnitLinks;  // Liste des liens UnitsLink entre les units produite dans AddNewLink

   static CATCGMChain *_Current;
  
 
};

ExportedByCATTopologicalObjects CATCGMChain* CATCreateCGMChain (CATGeoFactory*     ifactory);

#endif
