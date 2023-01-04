#ifndef CATSimplifyOperator_h
#define CATSimplifyOperator_h

// COPYRIGHT DASSAULT SYSTEMES 1999

class CATBody;
class CATDomain;

class CATGeoFactory;
class CATCGMJournalList;
class CATTopData;
class CATCellTagHashTable;
class CATString;

#include "CATCellHashTable.h"
#include "CATTopOperator.h"
#include "BOOPER.h"
#include "CATCGMAttrId.h"
#include "CATSimplifyOperatorDef.h"

/**
* Class representing the operator that simplifies a whole body or selected cells of a body.
*
* This operator does not follow the general scheme of topological operator :
* - He takes a modifiable body as input and modify it.
* - He is in fact a sub operator to be called as the last step of another operator
*   to simplify the result before the "freeze" operation.
*
* The external view of the operator is the CATTopSimplify CAA operator which follow the
* general scheme of the topological operator.
*/

class ExportedByBOOPER CATSimplifyOperator : public CATTopOperator
{

  CATCGMVirtualDeclareClass(CATSimplifyOperator);
public :
// -----

  // Constructor
  CATSimplifyOperator ( CATGeoFactory * iFactory , CATTopData * iTopData );

  //  Destructor
  ~CATSimplifyOperator();

  //  Run
  int Run();

  // Set Body and optionnaly domain to simplify
  // ( this service is mandatory and has to be called first )
  void SetBody ( CATBody   * iBody          ,
                 CATDomain * iDomain = NULL );

  // Defines the cells to simplify.
  // This restricts the simplification to these cells only.
  // ( this service is exclusive with the SimplifyByCells service ).
  void SimplifyCells ( CATCellHashTable * iCellsToSimplify );

  // Defines the cells to remove during simplification.
  // This restricts the simplification to the cells bounded to these cells only.
  // ( this service is exclusive with the SimplifyCells service ).
  void SimplifyByCells ( CATCellHashTable * iCellsToRemove );

  // Define the cells which will be used as reference for geometric simplification :
  // - This means that the geometry of theses cells will be considered as reference and
  // used for support of the new simplified cells.
  // - If this geometry can not be used , simplification will not be done locally.
  // - This service is restricted today to faces ( for selection of surfaces to used
  // as support of the simplified faces )
  void SetReferenceCells ( CATCellHashTable * iReferenceCells );

  // Define a specific journal for edge simplification reporting
  void SetEdgeReporting ( CATCGMJournalList * iEdgeReport );

  /* do not use */
  void SetSpecialMode ( const int iSpecialMode );

  // When replacing canonical supports during geometric simplification step
  // the geometric replacement will be only local to the simplified cells
  // and not global.
  // This option is not recommanded because we try to reduce the total number
  // of differents surfaces within a part.
  // This option is only useful for specific performance needs when adding new geometric
  // ( Draft / Fillet case ).
  void SetLocalGeometricSimplificationMode ();

	// SetDimensionToSimplify :
	// - set Mask for specific dimension simplification 
	// - This is a combinaison of MASK_SIMPLIFY_EDGE , MASK_SIMPLIFY_FACE and MASK_SIMPLIFY_VOLUME
	// - by default , all dimension are simplified
	void SetDimensionToSimplify ( const unsigned int iMaskForDimensionToSimplify );

	// Specific method for shell for attribute transfert ( restricted , do note use ) @nocgmitf
	static void SetAttributeKeyToTransfert ( const CATBoolean     iIsShellAttributeKeyInitialized ,
		const CATLONG32      iShellOldAttributeKey           , 
		const CATCGMAttrId * iShellNewAttributeId            );

	//KY1 : 03-01-2010

	/**	@nodoc @nocgmitf*/ 
	static const  CATString  *GetDefaultOperatorId();

	// HandleRemoteEdgesWithSameGeometry :
	// - Set a flag to have the simplify operator to attempt simplification of edge(s) 
	// - in the equivalence class that share the same underlying geometry with edge(s)
	// - outside of the given equivalence class (e.g. topologically disconnected edges)
	void HandleRemoteEdgesWithSameGeometry( CATBoolean iHandleRemoteEdgesWithSameGeometry );

	// EnableTolerantSimplification :
	// - Set a flag to have the simplify operator to attempt to run in tolerant simplify mode
	void EnableTolerantSimplification( double iRelativeTolerance );

protected:

	//KY1 : 03-01-2010
	/**	@nodoc*/
	int RunOperator();
protected:
	/**	@nodoc @nocgmitf */
	static  CATString  _OperatorId;
	/**	@nodoc @nocgmitf */
	const  CATString  *GetOperatorId();
	/**  @nodoc @nocgmitf */
	void   RequireDefinitionOfInputAndOutputObjects();


protected :
// --------

  void CleanUp();

  void SimplifyDomain ( CATDomain * iManifold );

  void SimplifyOnlyCells ( CATDomain           * iManifold        , 
                           CATCellTagHashTable * iCellsToSimplify );

  void SimplifyRemoveCells ( CATDomain           * iManifold      ,
                             CATCellTagHashTable * iCellsToRemove );

  void SimplifyRemoveCellsWithinLump ( CATDomain           * iManifold       , 
                                       CATCellTagHashTable * ioCellsToRemove );

  void GetNextCellsAndDomainToSimplify ( CATCellTagHashTable& ioAllCellsToSimplify ,
                                         CATCellTagHashTable& oCellsToSimplify     ,
                                         CATDomain*&          oDomainToSimplify    ,
										 const int            iToRemove            );
  
  void SimplifyCellsOfOneDomain ( const int             iDimension             ,
                                  CATDomain           * iDomain                ,
                                  CATCellTagHashTable * iSimplificationCells   ,
                                  CATCellTagHashTable * iNextSimplificationCells     = NULL);

  void RemoveUselessDomainFull( CATBody* Body, CATCellHashTable* CellsToSimplify, CATCellHashTable* CellsToRemove);
  void RemoveFullShells( CATBody* Body, CATCellHashTable* CellsToSimplify, CATCellHashTable* CellsToRemove);

  CATBody           * _Body;                       // Body to simplify
  CATCellHashTable  * _CellsToSimplify;            // Cells to simplify
  CATCellHashTable  * _CellsToRemove;              // Cells to remove
  CATCellHashTable  * _ReferenceCells;             // Reference cells for geometric simplification
  CATCGMJournalList * _EdgeReport;                 // Edge Report
  double              _Resolution;                 // Resolution
  int                 _SpecialMode;                // Special Mode
  unsigned int        _MaskForDimensionToSimplify; // Mask for specific dimension simplification 
  int                 _LocalSimplificationMode;    // Local geometric simplification mode
  short               _LevelForSimplify;           // Versionning
  short               _FatEdges;                   // Activation simplif avancee des edges
  CATBoolean          _HandleRemoteEdgesWithSameGeometry;
  CATBoolean          _DoTolerantSimplify;
  double			  _RelativeTolerance;
  
};

#endif
