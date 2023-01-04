#ifndef CATCellManifoldPatternNavigatorInterface_H
#define CATCellManifoldPatternNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATPatternType.h"
#include "CATCollec.h"
#include "CATListOfShort.h"
#include "CATMathPoint.h"
#include "CATPatternActivationStatus.h"


class CATCellManifoldPatternNavigator;
class CATCellManifoldSHMNavigator;
class CATCellManifold;
class CATMathVector;
class CATMathLine;
class CATMathTransformation;
class CATCellManifoldGroup;
class CATCell;
class CATLISTP(CATCell);

class ExportedByCATGMModelInterfaces CATCellManifoldPatternNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldPatternNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldPatternNavigatorInterface();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldPatternNavigatorInterface * GetAsPatternNavigatorInterface();

  
  //-------------------------------------------------
  //    Methodes globales
  //-------------------------------------------------

  // Renvoie le group qui contient tout le pattern. 
  //------------------------------------------------
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const=0;

  // Renvoie un point qui permet de visualiser le centre de la reference. 
  //----------------------------------------------------------------------
  virtual HRESULT GetOriginPoint(CATMathPoint & oOriginPoint) const = 0;

  // Renvoie le type du pattern (Linear, Circular, ...)
  //-----------------------------------------------------
  virtual HRESULT GetPatternType(CATPatternType &oType) const=0;
  
  // Renvoie la transformation qui permet de passer d'une instance l'instance suivante.
  //-------------------------------------------------------------------------------------
  virtual HRESULT GetUnitaryTransformation(CATMathTransformation &ioUnitaryTransfo) const=0;



  //-------------------------------------------------
  //     Methodes traitants des Cell Manifolds
  //-------------------------------------------------


  // Renvoie les CellManifolds qui ont la meme CellManifold de reference que iCellManifold
  //----------------------------------------------------------------------------------------
  virtual HRESULT GetSisterCellManifolds(CATCellManifold * iCellManifold, ListPOfCATCellManifold & oSisterCellManifolds)=0;

  // Renvoie les CellManifolds / Cell de l'instance iInstance (commence a 0)
  //-------------------------------------------------------------------------
  virtual HRESULT GetInstanceCellManifolds(int iInstance, CATLISTP(CATCellManifold) &oInstanceCellManifolds)=0;
  virtual HRESULT GetInstanceCells(int iInstance, CATLISTP(CATCell) &oCells)=0;

  // Renvoie toutes les CellManifolds / Cell du pattern
  //----------------------------------------------------
  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oCellManifolds) const=0;
  virtual HRESULT GetAllCells(CATLISTP(CATCell) & oCellList)=0;

  // Test si la CellManifold / Cell appartient au pattern, et renvoie son instance 
  // ( -1 pour une CM/Cell qui est partagee entre plusieurs instances, 0 ... NbInstance - 1 si appartient a une instance)
  //-----------------------------------------------------------------------------------------------------------------------
  virtual CATBoolean BelongsToPattern(CATCellManifold * iCM, short & oInstance)=0;
  virtual CATBoolean BelongsToPattern(CATCell * iCell, short & oInstance)=0;

  

  //-------------------------------------------------
  //     Methodes traitant des Instances
  //-------------------------------------------------


  // Renovie le nombre d'instances 
  //-------------------------------
  virtual HRESULT GetNumberOfInstances(short &oNbInstances) const=0;

  // Renvoie la transformation qui permet de passer de la reference a l'instance.
  //--------------------------------------------------------------------------------
  virtual HRESULT GetInstanceTransformation(short iInstance, CATMathTransformation &oInstanceTransfo) const=0;

  // Renvoie la transformation qui permettrait de passer de la reference si on changeait la transfo unitaire par iTransfoToTest .
  // Necessaire dans le cas pattern de pattern.
  //--------------------------------------------------------------------------------------------------------------------------------
  virtual HRESULT ComputeInstanceTransformationWithChangedUnitaryTransfo(short iInstance, CATMathTransformation &iUnitaryTransfo, CATMathTransformation &oInstanceTransfo) const=0;

  // Renvoie la transformation secondaire qui decale une instance par rapport a la position qu'elle devrait avoir normalement.
  //--------------------------------------------------------------------------------------------------------------------------
  virtual HRESULT GetSecondaryTransformation(short iInstance, CATMathTransformation &oInstanceTransfo) const=0;

  // Renvoie la liste des numeros d'instances actives
  //---------------------------------------------------
  virtual HRESULT GetActiveInstances(CATListOfShort &oActiveInstances) const=0;

  // Renvoie les instances inactivees et le type de desactivation associe ( User, System, ... )
  //---------------------------------------------------------------------------------------------
  virtual HRESULT GetActivationStatus(CATListOfShort & InactivatedInstances, CATListOfShort & InactivationTypes) = 0;

  // Renvoie le status d'activation de l'instance
  //------------------------------------------------
  virtual HRESULT GetActivationStatus(int iInstance, CATPatternActivationStatus & oActivationStatus) = 0;



  //-------------------------------------------------
  //    Methodes pour pattern lineaire
  //-------------------------------------------------
  
  // Renvoie le vecteur de la l'unitary transformation
  //-----------------------------------------------------
  virtual HRESULT GetTranslationVector(CATMathVector &ioTranslationVector) const=0;



  //-------------------------------------------------
  //    Methodes pour pattern circulaire
  //-------------------------------------------------

  // Renvoie le vecteur de la l'unitary transformation
  //-----------------------------------------------------
  virtual HRESULT GetRotationData(CATMathLine &ioRotationAxis, double &ioRotationAngle) const=0;

  // Test si le pattern est complet (les instances sont equireparties autour de l'axe de rotation)
  //-------------------------------------------------------------------------------------------------
  virtual CATBoolean IsPatternComplete()=0;

  void Dump(CATCGMOutput& Output);

private:
  virtual HRESULT GetAllInstanceCells(int iInstance, CATLISTP(CATCell) & oCellList)=0; // une ancienne methode, a supprimer si non utilisee.

};


#endif
