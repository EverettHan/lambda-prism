#ifndef CATCellManifoldPatternAdvancedNavigator_H
#define CATCellManifoldPatternAdvancedNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldPatternNavigator.h"
#include "ListPOfCATCellManifoldPatternAdvancedNavigator.h"

class CATTopData;
class CATLiveBody;
class CATCellManifoldGroup;
class CATDRepNavigator;

class ExportedByPersistentCell CATCellManifoldPatternAdvancedNavigator : public CATCellManifoldPatternNavigator
{
public:

  // Constructor
  CATCellManifoldPatternAdvancedNavigator(const CATTopData &iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup, int iInstanceNumber = 0); 
  CATCellManifoldPatternAdvancedNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup* iNetworkGroup); 
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldPatternAdvancedNavigator();

  // Compute Inactivated Instances
  // Utilise dans la construction de Pattern de Pattern.
  // Donne les instances inactivees par l'etage N.
  // On suppose que les etages inferieurs sont bien construits.
  // Utilise dans la Carrier pour la mise a jour des etages a transportes et dans le Creator pour l'etage finale.
  HRESULT ComputeInactivatedInstances(CATListOfShort &oInactiveInstances);

  // Iterateur sur les groupes instance du niveau N.
  CATCellManifoldGroup * NextInstance(CATCellManifoldGroup * iPatternGroup = NULL);

  // Revoie les AdvancedNavigators du niveau N-1.
  HRESULT GetSubLevelNavigators(ListPOfCATCellManifoldPatternAdvancedNavigator & oNavigators); 

  // Methodes pour interroger facilement des donnees d'un attribut
  int GetPatternNumber(CATCellManifoldGroup * iPatternGroup);

  // Renvoie toutes les instances avec les numeros d'instance associes.
  HRESULT GetAllInstances(ListPOfCATCellManifoldGroup & oInstances, CATListOfShort & oInstanceNumbers);

  // Renvoie le niveau du Pattern :
  // 1 pour Pattern normale,
  // 2 pour Pattern de Pattern,
  // 3 pour Pattern de Pattern de Pattern,
  // etc..
  int GetLevel();

  int GetInstanceNumber();

  // le code doit remplacer a terme celui de  HRESULT GetNumberOfInstances(short &oNbInstances) const;
  // La méthode sera alors supprimee.
  HRESULT GetTotalNumberOfInstances(short &oNbInstances) const;




};
#endif
