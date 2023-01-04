#ifndef CATDrivenChamferRecognizer_H
#define CATDrivenChamferRecognizer_H

#include "CATChamferAdvancedRecognizer.h"

#include "ListPOfListPOfCATGMLiveFilletPiece.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathInline.h"

class CATPCurve;
class CATCrvLimits;
class CATSurface;
class CATGMLiveFilletRibbonPiece;
class CATChamferTool;
class CATIPGMChamferTool;

class ExportedByPersistentCell CATDrivenChamferRecognizer : public CATChamferAdvancedRecognizer
{
public:
  CATCGMDeclareManifoldAgent(CATDrivenChamferRecognizer, CATChamferAdvancedRecognizer)
	
	// Constructor
  CATDrivenChamferRecognizer(const CATChamferTool* iTool
                             , const CATLISTP(CATFace)& iRefSupportFacesParents
                             , const CATLISTP(CATFace)& iOtherSupportFacesParents
                             , const CATLISTP(CATCell)& iCandidateChamferCellsParents);


  CATDrivenChamferRecognizer(CATIPGMChamferTool* iTool
                             , const CATLISTP(CATFace)& iRefSupportFacesParents
                             , const CATLISTP(CATFace)& iOtherSupportFacesParents
                             , const CATLISTP(CATCell)& iCandidateChamferCellsParents);
	
  // Destructor
	virtual ~CATDrivenChamferRecognizer();

  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);

  void GetChamferSpecs(CATLISTP(CATFace)& oRefSupportFaces, CATLISTP(CATFace)& oOtherSupportFaces
                      ,const CATChamferTool*& oTool);

  INLINE virtual CATDeclarativeManifoldAgent* Clone();
  virtual CATBoolean AllowSamePriorityAgent();

  CATDrivenChamferRecognizer(); //default constructor for unstream 

  virtual void Stream(CATCGMStream& Str) const;  
  void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig);  

  virtual void Dump(CATCGMOutput &os);

protected:
  CATLISTP(CATFace) _ParentSupports[2];
  CATLISTP(CATCell) _CandidateCells;
  CATChamferTool* _ChamferTool;

};

INLINE CATDeclarativeManifoldAgent* CATDrivenChamferRecognizer::Clone()
{
  return new CATDrivenChamferRecognizer(_ChamferTool,_ParentSupports[0],_ParentSupports[1],_CandidateCells);
}

#endif
