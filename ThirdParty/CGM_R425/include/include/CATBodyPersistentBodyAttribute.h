#ifndef CATBodyPersistentBodyAttribute_h
#define CATBodyPersistentBodyAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007
//Creation EYL Janvier 2011
//Cette classe est un attribut de CATBody permettant de savoir quel CATPersistentBody
//est relié au CATBody
//Utilisé pour le traitement des groupes dans la simplification de résultat d'opérateurs Live et des Patterns.

#include "PersistentCell.h"
#include "CATCGMAttribute.h"
#include "ListPOfCATBody.h"
#include "CATBody.h"
#include "CATBoolean.h"
//#include "PersistentCell.h"
#include "ListPOfCATPersistentFaces.h"

class CATPersistentCellInfra;
class PersistentCell;
class CATBody;
class CATPersistentBody;
class CATPersistentFace;

class ExportedByPersistentCell CATBodyPersistentBodyAttribute : public CATCGMAttribute
{
  public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATCGMDeclareAttribute (CATBodyPersistentBodyAttribute, CATCGMAttribute);


  static CATBodyPersistentBodyAttribute* GetPersistentBodyAttribute(CATBody *iBody);

  CATBodyPersistentBodyAttribute();
  virtual ~CATBodyPersistentBodyAttribute();
	virtual void SetInputs(CATBody *iBody,CATPersistentBody *iPersistentBody,CATPersistentCellInfra *iInfra);
	
  static CATBodyPersistentBodyAttribute* CreateBodyPersistentBodyAttribute(CATBody &iBody,CATPersistentBody &iPersistentBody,CATPersistentCellInfra *iInfra);

  // --------------------------------------------------------------------------
  // Data access
  // --------------------------------------------------------------------------
  //virtual CATBody* GetBody();
  
	//---------------------------------------------------------------------------
	// Utilities
	//---------------------------------------------------------------------------

	virtual CATPersistentBody* GetPersistentBody();
	virtual CATPersistentCellInfra* GetPersistentCellInfra();
	virtual void SetPersistentFacesForFuturePattern(ListPOfCATPersistentFaces & iPersistentPatternFaces);
  virtual void GetFuturePersistentPatternFaces(ListPOfCATPersistentFaces &oPersistentPatternFaces);

private:
	CATBody *_Body;
	CATPersistentBody *_PersistentBody;
	CATPersistentCellInfra *_Infra;
  ListPOfCATPersistentFaces _PersistentPatternFaces;
};
#endif
  
