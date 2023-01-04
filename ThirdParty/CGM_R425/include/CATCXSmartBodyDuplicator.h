/* -*-c++-*- */
#ifndef CATCXSmartBodyDuplicator_H
#define CATCXSmartBodyDuplicator_H
// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATCXSmartBodyDuplicator :
// 
//
//=============================================================================
// Usage Notes:
//
// 
//=============================================================================
// Apr. 1 98   Creation                                                     rad
// Fev.   02   Donnees de vivicite sur les vertices                         HCN
// Apr.   04   Optimisation du clean des attributs (_DuplicatedObj)         FDN
//=============================================================================

#include "CXMODEL.h"
#include "CATSmartBodyDuplicator.h"
#include "CATString.h"
#include "CATListOfCATCXVertices.h"
#include "CATListOfCATCXTopology.h"

class CATCXVertex;
class CATCXBody;
class CATCXTopology;


#define CATMaxTopoFilters 14
#include "CATCGMNewArray.h"

#include "CATCGMHashTableWithAssoc.h"

//-----------------------------------------------------------------------
//   Association Table
//-----------------------------------------------------------------------  
class CATCXSmartAssociationTable : protected CATCGMHashTableWithAssoc
{
public:
  CATCXSmartAssociationTable();
  ~CATCXSmartAssociationTable();
  CATCGMNewClassArrayDeclare;

  int             Insert(CATCXTopology* OldObj, CATCXTopology* NewObj);
  CATCXTopology*  Locate(CATCXTopology* OldObj);
  void            RemoveAll();

  void            GetTouchedCells(CATLISTP(CATCXTopology) & ioTouchedTopo);
};

 

  //-----------------------------------------------------------------------
  //- CATSmartBodyDuplicator implementation
  //-----------------------------------------------------------------------  

class ExportedByCXMODEL CATCXSmartBodyDuplicator : public CATSmartBodyDuplicator
{  
public :
  CATCXSmartBodyDuplicator(CATGeoFactory* iFactory, CATCXBody* iInitialBody,CATCXBody* iFinalBody,const CATTopData & iData);
  CATCXSmartBodyDuplicator(CATGeoFactory* iFactory, CATCXBody* iInitialBody,CATCXBody* iFinalBody, CATCGMJournalList *iJournal);

  virtual ~CATCXSmartBodyDuplicator();
  CATCGMNewClassArrayDeclare;

  // External Methods 
  virtual CATCell*    GetDuplicatedCell(CATCell*)     const ;
  virtual CATCell*    GetDuplicatedCellOldVersion(CATCell*)     const ;
  virtual CATDomain*  GetDuplicatedDomain(CATDomain*) const ;
  virtual int Run() ;

  // Set Optimized InCaseOfNoTouch
  CATBoolean  IsOptimizedInCaseOfNoTouch();


  virtual void  ResetLogFilter() ;
  virtual void  AddLogFilter(CATGeometricType iTypeToFilter);

  // Internal Methods
  void           LogDuplication(CATCXTopology* OldObj, CATCXTopology* NewObj) ;
  CATCXTopology* FindNext(CATCXTopology* Obj) const;
  CATCXBody*     GetDuplicatedCXBody() const;

  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };

  // Donnees de vivicite sur les vertices
  void AddVertexWithSharpnessData(CATCXVertex* ipVertex);
  CATLISTP(CATCXVertex)* GetListOfVerticesWithSharpnessData();

  void GetTouchedCells(CATLISTP(CATCXTopology)* oTouchedTopo); 

  CATBoolean  GetActivationVIF();
  void        SetActivationVIF(CATBoolean value);

  CATBoolean GetVolumeJournalling() { return _VolumeJournalling;};
  void        SetVolumeJournalling(CATBoolean value) { _VolumeJournalling = value; };

protected :

  /** @nodoc CATTopCheckJournal   */
  virtual void RequireDefinitionOfInputAndOutputObjects();

  /** @nodoc more appropriate association table ...   */
  CATCXSmartAssociationTable *  _SmartTable;
  
  // all filters possible : CATGeometryType + CATCellType + CATDomainType + 11 other deriving interfaces
  CATGeometricType  *_Filters;
  short              _NumberOfFilters;

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
 protected:

	const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  void WriteInput(CATCGMStream  & ioStream);
  void WriteOutput(CATCGMStream & ioStream);
	CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os);
  void Dump( CATCGMOutput& os ) ;
  void DumpOutput(CATCGMOutput &os);

  int RunOperator();


private:


  static CATString _OperatorId;
  CATBoolean _DoActivationVIF;
  CATBoolean _VolumeJournalling;

  // Donnees de vivicite sur les vertices
  CATLISTP(CATCXVertex) _ListOfVerticesWithSharpnessData;
};

#endif
