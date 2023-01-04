// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
// ======================================================================================
//
// Created on october 2015
//
// Responsable QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  : Top Mother Abstract Class Implementation of CATIPGMDRepGroup.
*                 This object must remain attached to its Interface CATIPGMDRepGroup. 
*                 It has no lifecycle management.
*
*                 Transporte des CellManifolds ainsi que des données numeriques sous forme d'attribut. 
**/

#ifndef CATDRepGroup_H
#define CATDRepGroup_H

#include "PersistentCell.h"
#include "CATCGMVirtual.h"
// #include "CATlsoMetaObject.h"
#include "CATDeclarativeOriginModeler.h"
#include "ListPOfCATCellManifold.h"
#include "CATGroupSpecParams.h"
#include "CATListOfShort.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMODTScaleManager;
class CATDRepGroupThread;
class CATCGMStream;
class CATIPGMDRepGroup;

// MACRO
#define LSOMacro_CreateDRepGroup(iChild) \
{\
   CATDRepGroup * pDRepGroup = new iChild ();\
   return pDRepGroup;\
}


class ExportedByPersistentCell CATDRepGroup : public CATCGMVirtual
{

public:

  //TYCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  void GetCellManifoldGroup (CATLISTP(CATCellManifold) &oCellManifolGroup) const;

  void GetContextualGroup (CATLISTP(CATCellManifold) &oContextualCellManifolds, CATListOfShort &oListOfContextType) const;
  
  const CATGroupSpecParams * GetGroupSpecParams () const;

  // GroupThread
  // ------------------------------------------------------------------
  virtual CATDRepGroupThread * GetAsDRepGroupThread();

  // For CGMReplay only
  static  CATIPGMDRepGroup   * CATLoadDRepGroupItf(CATCGMStream & ioStr, CATCGMODTScaleManager *iODTScaleManager=NULL);


  // << Stream >>
  // ==========================================
  virtual void Stream(CATCGMStream & ioStr) const;
  virtual void UnStream(CATCGMStream & ioStr, CATCGMODTScaleManager *iODTScaleManager=NULL);
  virtual void Dump(CATCGMOutput& os) const;
  
protected :
    
  // << UnStream Mandatory >>
  // ==========================================  
  virtual CATString            GetStreamType() const = 0;
  virtual CATGroupSpecParams * UnStreamParam(CATCGMStream & ioStr) const = 0;

  /*  Constructor **
  */
  CATDRepGroup(const CATLISTP(CATCellManifold) &iCellManifoldGroup, CATGroupSpecParams *iGroupSpecParam);
  CATDRepGroup(const CATLISTP(CATCellManifold) &iCellManifoldGroup, const ListPOfCATCellManifold &iContextualCellManifolds, CATListOfShort *iListOfContextType, CATGroupSpecParams *iGroupSpecParam);

   /**
   * Destructor
   */ 
  virtual ~CATDRepGroup();

  // forbiden constructors
  CATDRepGroup();
  CATDRepGroup(const CATDRepGroup &iCopy);
  CATDRepGroup& operator=(const CATDRepGroup &iCopy);


private :

  void SetGroupSpecParams(CATGroupSpecParams * iGroupSpecParams);



  // Internal Input Data
  // ----------------------
  ListPOfCATCellManifold   _GroupOfCellManifolds;
  ListPOfCATCellManifold   _ContextualManifoldList;
  CATListOfShort           _ListOfContextType;

  CATGroupSpecParams     * _GroupSpecParams;

};



#endif
