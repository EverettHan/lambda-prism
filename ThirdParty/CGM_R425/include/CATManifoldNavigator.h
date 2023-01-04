#ifndef CATManifoldNavigator_H
#define CATManifoldNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDeclarativeType.h"
#include "ListPOfCATCell.h"
#include "CATCGMStream.h"
#include "CATCGMStreamAttribute.h"
#include "CATCGMAttributeDef.h"
#include "CATCGMAttribute.h"
#include "CATIAV5Level.h"

class CATCellManifoldGroupNavigator;
class CATDRepNavigator;
class CATDRepNavigatorInterface;
class CATManifoldRibbonNavigator;
class CATManifoldRibbonNavigatorInterface;
class CATCellManifoldPatternNavigator;
class CATCellManifoldPatternNavigatorInterface;
class CATCellManifoldBRepCopyNavigatorInterface;
class CATCellManifoldSHMNavigator;
class CATCellManifoldCRTWallNavigator;
class CATCellManifoldCRTBendNavigator;
class CATCellManifoldCRTGlueNavigator;
class CATCGMOutput;
class CATGeoFactory;
class CATGMLiveShapeButtonNavigator;
class CATGMLiveShapeButtonNavigatorInterface;
class CATGMLiveShapeGlobalButtonNavigatorInterface;
class CATGMLiveShapeGlobalButtonNavigator;
class CATGMLiveShapeButtonData;

// -----------------------------------------------------------------------------------------------
// Macros dedicated to implementation of child classes
// -----------------------------------------------------------------------------------------------
#define CATCGMDeclareManifoldNavigator(iChild, iParent) \
CATCGMDeclareAttribute(iChild,iParent);             \
CATCGMNewClassArrayDeclare;     

#define CATCGMImplManifoldNavigator(iChild, iParent)      \
CATCGMImplAttribute(iChild,iParent,CGM_DRep_Navigator,1); \
CATCGMNewClassArray(iChild,3,catcgmPoolTEMP)          

#define CATCGMImplManifoldNavigatorForeign(iChild, iParent, iAppName)      \
CATCGMImplAttribute(iChild,iParent,CGM_DRep_Navigator,iAppName,1); \
CATCGMNewClassArray(iChild,3,catcgmPoolTEMP)

class ExportedByCATGMModelInterfaces CATManifoldNavigator : public CATCGMStreamAttribute
{
public:

  // Attribute Declaration
  CATCGMDeclareAttribute(CATManifoldNavigator, CATCGMStreamAttribute);

  // Constructor
  CATManifoldNavigator(); 

  // Destructor
  virtual ~CATManifoldNavigator();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation


  virtual CATCellManifoldGroupNavigator *             GetAsGroupNavigator();
  virtual CATCellManifoldPatternNavigator *           GetAsPatternNavigator();
  virtual CATCellManifoldPatternNavigatorInterface *  GetAsPatternNavigatorInterface(); 
  virtual CATCellManifoldSHMNavigator *               GetAsSHMNavigator();
  virtual CATManifoldRibbonNavigator *                GetAsRibbonNavigator();
  virtual CATManifoldRibbonNavigatorInterface *       GetAsRibbonNavigatorInterface();
  virtual CATCellManifoldBRepCopyNavigatorInterface * GetAsBRepCopyNavigatorInterface();
  virtual CATDRepNavigator *                          GetAsDRepNavigator();
  virtual CATDRepNavigatorInterface *                 GetAsDRepNavigatorInterface();
  virtual CATGMLiveShapeButtonNavigator *             GetAsButtonNavigator() const;
  virtual CATGMLiveShapeButtonNavigatorInterface *    GetAsButtonNavigatorInterface();
  virtual CATGMLiveShapeGlobalButtonNavigator *       GetAsGlobalButtonNavigator();
  virtual CATGMLiveShapeGlobalButtonNavigatorInterface * GetAsGlobalButtonNavigatorInterface();
  virtual CATGMLiveShapeButtonData *                  GetAsButtonData() const;
#ifdef CATIAR417
  virtual CATCellManifoldCRTWallNavigator*            GetAsCRTWallNavigator();
  virtual CATCellManifoldCRTBendNavigator*            GetAsCRTBendNavigator();
  virtual CATCellManifoldCRTGlueNavigator*            GetAsCRTGlueNavigator();
#endif

  virtual void Dump(CATCGMOutput& Output);
  virtual void DiGraphDump(CATCGMOutput& Output); // Do not use

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
  virtual HRESULT GetCells(ListPOfCATCell& oCells) const;

  // Stream Unstream
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  virtual void UnStream( CATCGMStream& ioStr );
  virtual void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

  // For CGMReplay only
  static CATManifoldNavigator* CreateNavigatorFromStream(const int iVersion, CATGeoFactory* iFactory, CATCGMStream& Str);
  static void StreamNavigator(const int iVersion, const CATManifoldNavigator* iAgent, CATCGMStream& Str);

};

//ExportedByCATGMModelInterfaces CATManifoldNavigator * CATLoadManifoldNavigator(CATCGMStream & Str, const short iLevelOfRuntime, const short iVersionOfStream);


#endif
