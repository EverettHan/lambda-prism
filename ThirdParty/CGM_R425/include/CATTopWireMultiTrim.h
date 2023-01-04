// COPYRIGHT DASSAULT SYSTEMES 2004
//================================================================================
// Creation ICE  31/08/2004
//
// Operateur de trim multi wire
// cf CATCreateWireMultiTrim.
//================================================================================

#ifndef __CATTopWireMultiTrim_h__
#define __CATTopWireMultiTrim_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATGeoFactory;
class CATTopData;

class CATBody;
class CATCell;

class CATTopWireMultiTrim: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopWireMultiTrim);
   protected:
      
      //============================
      // Constucteur et destructeurs
      //============================

      CATTopWireMultiTrim(CATGeoFactory * iFactory, CATTopData * iTopData);
       
     public:

      virtual ~CATTopWireMultiTrim();

      //========================================================
      // Methodes de parametrisation de l'operateur (INTERFACES)
      //========================================================

      virtual void SetKeepOrderOn(int iPortionNumber, CATBody * iRefBody) = 0;
  
      //========================================================
      // Methodes d'execution et de resultats (INTERFACES)
      //========================================================
 
      virtual int         Run() = 0;
  /** @nodoc @nocgmitf */
      virtual int         RunOperator() = 0;

      virtual CATBody *   GetResult() = 0;
      virtual CATBody *   GetIntermediateResult() = 0;
      virtual int         GetNumberOfIntersections(CATBody * iRefBody, CATBody * iVersusBody) = 0;
      virtual int         GetPortionNumber(CATCell * iRefCell, CATBody * iRefBody) = 0;
      virtual void        GetResultBodies( CATBody * iRefBody,CATLISTP(CATBody) & ioResultBodies ) = 0;
      virtual void        GetJournalForOneBody(CATBody * iBodyInput,CATBody * iBodyMosaicResult, CATCGMJournalList & ioJournal) = 0;
      virtual void        SetCuttingBodiesOthers(CATLISTP(CATBody) * iCuttingBodiesOthers ) = 0; 
      
      
      // vertices et shells decoupant les wires
      virtual int         GetNbVerticesOnWireTable(int iIndexWireInitial) = 0; 
      virtual void        SetVerticesOnWireTable(int iIndexWireInitial,CATListOfInt *iIndexVertexInitialList, CATLISTP(CATBody) * iNewVertexBodyList)   = 0; 
      virtual void        GetVerticesOnWireTable(int iIndexWireInitial,CATListOfInt *ioIndexVertexInitialList, CATLISTP(CATBody) * ioNewVertexBodyList) = 0; 


      virtual CATBoolean  ResultIsConnex() = 0;
      virtual CATBoolean  ResultIsManifold() = 0;
};


#endif

