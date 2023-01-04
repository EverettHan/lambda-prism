#ifndef CATTopOperatorUtilities_H_
#define CATTopOperatorUtilities_H_

// COPYRIGHT DASSAULT SYSTEMES  2016

#include "CATErrorDef.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATGeometryType.h"
#include "CATCollec.h"
#include "ExportedByCATTopologicalObjects.h"

class CATCGMOperator;
class CATCGMJournalList;
class CATCGMJournalItem;
class CATGeometry;
class CATBody;
class CATTopology;
class CATLISTP(CATTopology);
class CATLISTP(CATBody);
class CATCGMOutput;
class CATSoftwareConfiguration;
class CATCGMContainer;

class ExportedByCATTopologicalObjects CATTopOperatorUtilities
{
public: 

   /*@nocgmitf @nodoc */
   static CATBoolean IsClosedConfig(CATSoftwareConfiguration *piSoftConfig); 

   /*@nocgmitf @nodoc */
   static CATBoolean IsAuthorizedFor_CheckUpMemorize(const CATString *piOperatorID, CATCGMContainer *piOutputContainer, CATBoolean iIsInputDiffFromOutputContainer);

   /*@nocgmitf @nodoc */
   static CATBoolean IsAuthorizedFor_JournalOfDomains(const CATString *piOperatorID);

   /*@nocgmitf @nodoc */
   static CATBoolean IsAuthorizedFor_ReOrder(const CATString *piOperatorID, CATCGMContainer *piOutputContainer);

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfDomains_Reporting_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfCells_AbsoluteCheck_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfCells_RelativeCheck_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfDomains_CheckOutput_Activated();

   /*@nocgmitf @nodoc */
   static int Get_CATTopOperator_JournalOfDomains_CheckOutput_Level();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfDomains_Computation_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfDomains_Dump_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_JournalOfDomains_CGMReplay_Activated();

   /*@nocgmitf @nodoc */
   static CATBoolean Is_CATTopOperator_ReOrderShells_Activated(unsigned int iActiv_Value);

   /*@nocgmitf @nodoc */
   static HRESULT ReorderShellInReferenceOrResultBody(CATBody *piResultBody, CATBody *piReferenceBody);

   /*@nocgmitf @nodoc */
   static void ReportJournalOfDomainsStatus(const char *pODTName,const char *pScenarioName,	const char *piOperatorID, short IsNotEmptyJournal, short JOfCellAbsoluteCheckStatus,short JOfCellRelativeCheckStatus, short JOfDomComputationStatus, short JOfDomCheckStatus, short JOfDomAdvancedCheckStatus);

   /* Data */
   static CATString SpecificOperator_NullOperatorId;
   static CATString SpecificOperator_CATCltTopoFillet;
   static CATString SpecificOperator_CATTopFrFShellUnfold;
   static CATString SpecificOperator_TopWireMultiTrim;
   static CATString SpecificOperator_CATPolygone2Surface;
   static CATString SpecificOperator_TopHelixOperator;
   static CATString SpecificOperator_DynShellBodyCGM;
   static CATString SpecificOperator_DynTransformation;
   static CATString SpecificOperator_BodyDatumiser;
   static CATString SpecificOperator_TopForeign;
   static CATString SpecificOperator_ICMCLAGlobalSurfaceOffset;
   static CATString SpecificOperator_ICMCLASurfaceOffset;
   static CATString SpecificOperator_CATTopDomainJournalOperator;
   static CATString SpecificOperator_TopCornerBiTgtRad;
   static CATString SpecificOperator_Top3DCorner;
   static CATString SpecificOperator_PolyTessBody;

private:
   /* Services Class : No Ctors */
   CATTopOperatorUtilities();
   CATTopOperatorUtilities(const CATTopOperatorUtilities& iTopJournalUtilities);
   CATTopOperatorUtilities& operator = (const CATTopOperatorUtilities& iTopJournalUtilities);

   static CATBoolean _CATTopOperator_JournalOfCells_AbsoluteCheck_Init;
   static CATBoolean _CATTopOperator_JournalOfCells_RelativeCheck_Init;
   static CATBoolean _CATTopOperator_JournalOfDomains_CheckOutput_Init; 
   static CATBoolean _CATTopOperator_JournalOfDomains_Reporting_Init; 
   static CATBoolean _CATTopOperator_JournalOfDomains_Computation_Init;
   static CATBoolean _CATTopOperator_JournalOfDomains_Dump_Init;
   static CATBoolean _CATTopOperator_JournalOfDomains_CGMReplay_Init;
   static CATBoolean _CATTopOperator_ReOrderShells_Init;

   static const char *_CATTopOperator_JournalOfCells_AbsoluteCheck; 
   static const char *_CATTopOperator_JournalOfCells_RelativeCheck; 
   static const char *_CATTopOperator_JournalOfDomains_CheckOutput; 
   static const char *_CATTopOperator_JournalOfDomains_Reporting;
   static const char *_CATTopOperator_JournalOfDomains_Computation;
   static const char *_CATTopOperator_JournalOfDomains_Dump;
   static const char *_CATTopOperator_JournalOfDomains_CGMReplay;
   static int _CATTopOperator_ReOrderShells;
};


#endif

