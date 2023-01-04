#ifndef CATTopModify_h
#define CATTopModify_h
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// Methode: CATTopModify
//
// Auteurs: TCX        Date: 09/07/2002
//
// Description: 
//   Operateur d'enrichissement de la definition d'un Body 
//     a partir d'objets topologiques externes ayant une equivalence explicite 
//     sur des constituants internes du Body 
//
//
//=============================================================================
// Oct. 03 GetExtRefMappedCell(...),
//         Argument CATTopGeometricalMapType iVertexMapType               HCN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATString.h"
#include "CATTopGeometricalMapType.h"

class CATTopology;
class CATBody;

class ExportedByCATTopologicalObjects CATTopModify : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopModify);
   public:
     
      //=======================================================================================================
      // Rajout d'une reference externe qui n'appartient pas au Body
      //  et qui porte les informations de Pose-Sur que l'on souhaite injecter sur le Body ...
      // Par un mapping geometrique, on doit retrouver des equivalents topologiques f 
      //========================================================================================================
      virtual void AddExternalReference(CATTopology * iExternalReference) = 0;

     
      //=======================================================================================
      // Specification d'un traitement de rajout de liens Pose Sur, On demande la recopie/report 
      //    des liens pose sur iBody (une tierce partie) portes par les references externes
      //    sur leur constituant equivalent du Body
      //=======================================================================================
      virtual void SetAddCopyLyingOnLinksFrom(CATBody *iBody) = 0;


      //=======================================================================================
      // Commodite pour l'integration CATCGMReplay
      //=======================================================================================
  /** @nodoc @nocgmitf */
      const CATString * GetOperatorId(); 

      //=======================================================================================
      // Pour debug : verification du mapping de body
      //=======================================================================================
      virtual const CATCell* GetExtRefMappedCell(const CATCell* ipCell) = 0;


   protected:

      //==============================
      // Seul constructeur admissible 
      //==============================
      CATTopModify(CATGeoFactory*           iFactory,
                   const CATTopData&        iTopData);    
      

      //=======================================================================================
      // Commodite pour l'integration CATCGMReplay
      //=======================================================================================
      static CATString _OperatorId;
};


//========================================================================================
// Creation de l'operateur en identifiant le Body en Input (mode Copy)
// argument iVertexMapType : CatTopGeometricalMap_VertexAsSinglePoint ou CatTopGeometricalMap_VertexAsCloudOfPoints
// => voir CATTopGeometricalMapType.h
//========================================================================================
ExportedByCATTopologicalObjects CATTopModify *CATCreateModify(CATBody*                 iCopyBody,
                                                              const CATTopData&        iTopData,
                                                              CATTopGeometricalMapType iVertexMapType = CatTopGeometricalMap_VertexAsSinglePoint);


#endif
