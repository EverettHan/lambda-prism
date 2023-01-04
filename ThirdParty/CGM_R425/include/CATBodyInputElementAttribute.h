#ifndef CATBodyInputElementAttribute_h
#define CATBodyInputElementAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007
//Creation EYL Mai 2010
//Cette classe est un attribut de CATBody permettant de savoir quels sont les
//Bodies dont est issu le body attaché.
//Utilisé pour le traitement des groupes dans la simplification de résultat d'une union booleenne.

#include "CATCGMAttribute.h"
#include "PersistentCell.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATPersistentBodies.h"
class CATBody;
class CATPersistentCellInfra;
class CATCGMJournalList;
class CATCDMBaseServices;
class ExportedByPersistentCell CATBodyInputElementAttribute : public CATCGMAttribute
{
  public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATCGMDeclareAttribute (CATBodyInputElementAttribute, CATCGMAttribute);


  static CATBodyInputElementAttribute* GetInputElementAttribute(CATBody *iBody);

  CATBodyInputElementAttribute();
  virtual ~CATBodyInputElementAttribute();
	
  static CATBodyInputElementAttribute* CreateBodyInputElementAttribute(CATBody &iBody);


  // --------------------------------------------------------------------------
  // Data access
  // --------------------------------------------------------------------------
  //virtual CATBody* GetBody();
	virtual void SetBody(CATBody *iBody);
  
	//---------------------------------------------------------------------------
	// Utilities
	//---------------------------------------------------------------------------
	virtual void AddInputElements(ListPOfCATBody &iBodies);
	virtual void RemoveInputElements(ListPOfCATBody &iBodies);
	virtual void GetInputElements(ListPOfCATBody &oBodies);
	virtual void AddInputElements(ListPOfCATPersistentBodies &iPBodies);
	virtual void RemoveInputElements(ListPOfCATPersistentBodies &iPBodies);
	virtual void GetInputElements(ListPOfCATPersistentBodies &oPBodies);
	virtual void SetJournalSinceInputs(CATCGMJournalList *iJournal);
	virtual CATCGMJournalList *GetJournalSinceInputs();
  virtual void SetPersistentInfra(CATPersistentCellInfra *iPersistentInfra);
  virtual CATPersistentCellInfra *GetPersistentInfra();
  virtual void SetCDMBaseServices(CATCDMBaseServices  *iBaseServices);
  virtual CATCDMBaseServices * GetCDMBaseServices();

private:
	CATBody *_Body;
	ListPOfCATBody _InputElements;
  ListPOfCATPersistentBodies _InputPersistentElements;
	CATCGMJournalList *_JournalSinceInputs;
  CATCDMBaseServices * _CDMBaseServices;
  CATPersistentCellInfra       * _PersistentInfra;
};
#endif
  
