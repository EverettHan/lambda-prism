// ======================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
// ======================================================================================
//
// Created on october 2015
//
// Responsable QF2
//
// --------------------------------------------------------------------------------------
/* DESCRIPTION  : Implementation Class for CATIPGMDRepGroupThread (see description there).
*                 This object implements CATIPGMDRepGroupThread.
*                 It has no lifecycle management and must remain attached to its interface CATIPGMDRepGroupThread.
*                 
*                 Do not use new CATDRepGroupThread(). Use CATCreatePGMDRepGroupThread interface creation method. 
*                 
*                 Transporte des CellManifolds ainsi que des données numeriques sous forme d'attribut. ( voir projet thread)
**/

#ifndef CATDRepGroupThread_H
#define CATDRepGroupThread_H

#include "CATDRepGroup.h"
#include "CATDeclarativeOriginModeler.h"
#include "ListPOfCATCellManifold.h"
#include "CATThreadSpecParams.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMODTScaleManager;
class CATString;
class CATIPGMDRepGroupThreadImpl;

class CATDRepGroupThread : public CATDRepGroup
{
  friend class CATIPGMDRepGroupThreadImpl;

public:

  //TYCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;
  
  // Official Constructor 
  CATDRepGroupThread(const CATLISTP(CATCellManifold) &iCellManifoldGroup, const CATLISTP(CATCellManifold) &iCellManifoldContext, CATThreadSpecParams *iThreadSpecParam);

  // Destructor   
  virtual ~CATDRepGroupThread();

  // Getter
  void  GetAxis(CATMathAxis &oThreadAxis) const;
  void  GetNumericalParam (double &oDepth, double &oDiameter, double &oNominalDiameter, double &oPitch, int &oSens, double &oSupportDiameter) const;
  void  GetDescriptionParam (CATString &oThreadDescription, int &oThreadType, int &oDisplayInDrafting, CATString &oKeyOfThread) const;


  virtual CATDRepGroupThread * GetAsDRepGroupThread();
  
protected :
  
  virtual CATString      GetStreamType() const;
  virtual CATGroupSpecParams * UnStreamParam(CATCGMStream & ioStr) const;

  CATDRepGroupThread();
  CATDRepGroupThread(const CATDRepGroupThread &iCopy);
  CATDRepGroupThread& operator=(const CATDRepGroupThread &iCopy);

  const CATThreadSpecParams * GetThreadSpecParam() const;

};


#endif
