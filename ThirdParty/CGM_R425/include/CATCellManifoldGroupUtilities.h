#ifndef CATCellManifoldGroupUtilities_H
#define CATCellManifoldGroupUtilities_H

//======================================================================================
// 27/06/19 NLD Pour deploiement de la configuration, suppression de la déclaration static pour
//              RunGroupOperatorForOneGroup()
//              Généralisation préventive aux autres méthodes à envisager
//======================================================================================
#include "CATCGMNewArray.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATFace.h"
#include "CATListOfCATCells.h"
#include "CATCellManifoldGroup.h"
#include "CATCellManifoldGroupOperator.h"


class CATSoftwareConfiguration;
class CATManifoldGroupAttribute;
class CATCellManifoldsManager;

class ExportedByPersistentCell CATCellManifoldGroupUtilities
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

                                     CATCellManifoldGroupUtilities(  CATSoftwareConfiguration      *  iConfig       );
  virtual                           ~CATCellManifoldGroupUtilities();

         HRESULT                     RunGroupOperatorForOneGroup(    CATCellManifoldGroupOperator  *  iGroupOperator,
                                                                     CATCellManifoldGroup          *& oCreatedGroup );

  static HRESULT                     GetColor                 (const CATCellManifoldGroup           & iGroup   ,
                                                                     int                            & oR       ,
                                                                     int                            & oG       ,
                                                                     int                            & oB       );

  static void                        GetCoord                 (      ListPOfCATCell                 & iCells   ,
                                                                     float                            oCoord[3]);

  static CATManifoldGroupAttribute * GetManifoldGroupAttribute(      CATCellManifoldGroup           * iGroup);

  static CATManifoldGroupAttribute * GetManifoldGroupAttribute(      ListPOfCATCellManifoldGroup    & iGroupList);

  static CATBoolean                  IsValidContexts          (const CATLISTP(CATCellManifoldGroup) & iParentGroupList       ,
                                                               const CATCellManifoldGroup           & iImageCellManifoldGroup,
                                                                     CATCellManifoldsManager        & iCellManifoldsManager  );

  static CATCellManifoldGroup      * UpdateExistingGroupContext(
                                                                     CATLiveBody                    & iLiveBody,
                                                                     CATCellManifoldGroup           & iParentCellManifoldGroup,
                                                                     ListPOfCATCellManifold         & iParentLeavesImages, 
                                                                     CATListOfShort                 * iParentLeavesImagesType, 
                                                                     ListPOfCATCellManifold         & iParentContextsImages, 
                                                                     CATListOfShort                 & iParentContextsImagesType, 
                                                                     CATCellManifoldGroupLayer      & iGroupLayer,
                                                                     CATCellManifoldsManager        & iCMManager,
                                                                     CATBoolean                     & oNeedToUpdateManifoldAttribute);

private:

  CATSoftwareConfiguration * _SoftwareConfiguration;

  
};

#endif 

