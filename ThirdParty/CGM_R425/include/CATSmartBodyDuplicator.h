#ifndef CATSmartBodyDuplicator_H
#define CATSmartBodyDuplicator_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "YI00IMPL.h"
#include "ListPOfCATBody.h"
#include "CATGeometryType.h"
#include "CATTopOperator.h"
#include "CATCGMDuplicateLyingOn.h"


class CATBody;
class CATCell;
class CATDomain;
class CATCGMJournalList;
class CATSmartBodyDuplicator;
class CATExtTopOperator;


/** @nodoc */
extern ExportedByYI00IMPL void CATSmartBodyDuplicator_SetOptimizedInCaseOfNoTouch(CATSmartBodyDuplicator & iToModify);
/** @nodoc */
extern ExportedByYI00IMPL void CATSmartBodyDuplicator_ForbidOptimizedInCaseOfNoTouch(CATSmartBodyDuplicator & iToModify);

//--------------------------------------------------------------------------------------------------
// Constructeur de l'outil topologique
//--------------------------------------------------------------------------------------------------

/**
 * Class defining an operator that duplicates the touched cells (and the cells depending on these
 * touched cells) of a body.
 * <br>This is used in the context of the "smart mechanism".
 * After its creation a CATToplogy is modifiable.
  *   It becomes non-modifiable when a body containing it is frozen.
  *   The smart duplicator only duplicates the touched cells and 
  *   the domains impacted by the touched cells.
	*<br>As any operator, the duplicator is created, run, read,and deleted.
	* Sample:
	* <pre>// anEdge is a cell belonging to FrozenBody.
	*	anEdge->Touch(FrozenBody);
	* //  Create an empty body to input the duplicated cells
	* CATBody * NewBody= CATGeoCreateBody(GeoFactory);
	*	CATSmartBodyDuplicator * SmartDupl=NewBody->CreateSmartDuplicator(FrozenBody);
	*	SmartDupl->Run();
	* // Retrieves the mapping between the touched edge and its copy:
	* CATEdge * DuplicatedEdge = (CATEdge *)	(SmartDupl->GetDuplicatedCell(anEdge));
	* // clean the memory
	*	delete SmartDupl;</pre>
    * <br>NOTE:
    * <br>Throughout this header documentation, 
    * the term "lying on link" refers to a piece of information which is contained in
    * the cell to be duplicated. This piece of information gives a clue as to whether
    * the duplicated cell is lying on the cell the original cell was lying on (the link).  
    *  . 
  */
class ExportedByYI00IMPL CATSmartBodyDuplicator  : public CATTopOperator
{  
  CATCGMVirtualDeclareClass(CATSmartBodyDuplicator);
public :
  

#ifdef CATIACGMR419CAA
  /**
  * Constructs a body duplicator.
  * @param iFactory
  * The factory where objects are created.
  * @param iTopData
  * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
  * @param iExtensible
  * The optional dedicated extension object to delegate the computation (mandatory for polyhedral management)
  */
  CATSmartBodyDuplicator(CATGeoFactory* iFactory, const CATTopData & iData, CATExtTopOperator * iExtensible=NULL);
#else
  /**
  * Constructs a body duplicator.
  * @param iFactory
  * The factory where objects are created.
  * @param iTopData
  * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
  */
  CATSmartBodyDuplicator(CATGeoFactory* iFactory, const CATTopData & iData);
#endif
  
  virtual ~CATSmartBodyDuplicator();

  /**
   * Adds another body to compute the impacts of a touched CATTopology.
	 * @param iNewInitialBody
	 * The pointer to another body to take into account.
	 */
  void               AddInitialBody    (CATBody* NewInitialBody);

	/**
	 * Retrieves the list of the bodies that are taken into account by <tt>this</tt> duplicator.
	 * @param ioResult
	 * The list of the bodies. As part of the class, this list must not be directly deleted.
	 */
  void               GetInitialBodies  (CATLISTP(CATBody)& ioResult) const;

	/**
	 * Returns the pointer to the body inside which the duplicated cells are created.
	 * @return
	 * The pointer to the body, tha must be not frozen.
	 */
  CATBody*           GetDuplicatedBody ()                           const;

	/**
	 * Returns the pointer to the journal of <tt>this</tt> iterator.
	 * @return
	 * The pointer to the journal.
	 */
  CATCGMJournalList* GetJournal        () ;

  /** 
	 * Returns the mapping between a touched cell and its copy.
	 * @param iBeforeDuplication
	 * The pointer to the touched cell.
	 * @return
	 * The pointer to the corresponding duplicated cell.
   */
  virtual CATCell*    GetDuplicatedCell  (CATCell* iBeforeDuplication)   const = 0;

	/**
	 * Returns the mapping between a touched domain and its copy.
	 * @param iBeforeDuplication
	 * The pointer to the touched domain.
	 * @return
	 * The pointer to the corresponding duplicated domain.
	 */
  virtual CATDomain*  GetDuplicatedDomain(CATDomain* iBeforeDuplication) const = 0;

  /** 
	* Resets the filter on the cells for the journal.
	* <br> By default, all cells and domains are logged.
    */
  virtual void  ResetLogFilter() = 0;

	/**
	 *Adds a new type to be logged inside the journal of <tt>this</tt> duplicator.
	 * @param iTypeToFilter
	 * The type of geometry to add to the log.
   * <br>Sample: After <tt>ResetLogFilter + AddLogFilter(CATEdgeType) </tt>, only edges are logged. 
	 * After <tt>ResetLogFilter + AddLogFilter(CATEdgeType) + AddLogFilter(CATShellType)</tt>, 
   *              edges and shells are logged.
	 */
  virtual void  AddLogFilter(CATGeometricType iTypeToFilter) = 0;

  /** 
	 * Specifies how the edges and vertices are to be duplicated by <tt>this</tt>.
	 * @param iMode
	 * The mode of duplication.
	 * <br><b>Legal values</b>:
	 * <dl>
   * <dt><tt>0</tt></dt><dd>Default mode: the touched edges and vertices are not duplicated when they bound faces.
   * <dt><tt>1</tt></dt><dd>Full duplication: all the touched cells and their impacts are duplicated.
	 * </dl>
   */
  void  SetFullDuplication(short iMode);

	/**
	 * Returns a value indicating how the edges and vertices are duplicated by <tt>this</tt>.
	 * @return
	 * The duplication mode.
	 * <br><b>Legal values</b>:
	 * <dl>
   * <dt><tt>0</tt></dt><dd>Default mode: the touched edges and vertices are not duplicated when they bound faces.
   * <dt><tt>1</tt></dt><dd>Full duplication: all the touched cells and their impacts are duplicated.
	 * </dl>
	 */
  short GetFullDuplication() const;

 

  /** 
	 * Specifies the lying on link of a duplicated cell. 
	 * @param iMode
	 * The mode of lying on links duplication.
	 * <br><b>Legal values</b>:
	 * <dl>
   * <dt><tt>CatCGMLyingOnNoCopy</tt></dt><dd>A duplicated cell contains no lying on link.
   * <dt><tt>CatCGMLyingOnDuplicated</tt><dd>Lying on links are duplicated on a duplicated cell.
   * <dt><tt>CatCGMLyingOnTransfered</tt><dd>Lying on links are transfered from an original cell to the duplicated cell.
	 * </dl>
   */
  void  SetDuplicateLyingOn(CATCGMDuplicateLyingOn iMode);


	/**
	 * Returns the lying on link of a duplicated cell.
	 * @return
	 * The mode of duplication.
	 * <br><b>Legal values</b>:
	 * <dl>
   * <dt><tt>CatCGMLyingOnNoCopy</tt></dt><dd>A duplicated cell contains no lying on link.
   * <dt><tt>CatCGMLyingOnDuplicated</tt><dd>Lying on links are duplicated on a duplicated cell.
   * <dt><tt>CatCGMLyingOnTransfered</tt><dd>Lying on links are transfered from an original cell to the duplicated cell.
	 * </dl>
	 */
  CATCGMDuplicateLyingOn GetDuplicateLyingOn() const;

  /** @nodoc
   * @nocgmitf
   */
  void TransferTouch(CATBoolean transfert);
  /** @nodoc
   * @nocgmitf
   */
  CATBoolean TransferTouch();
  /** @nodoc
   * @nocgmitf
   */
  virtual CATCell *GetDuplicatedCellOldVersion(CATCell*) const = 0;

 
#if defined ( CATIACGMR214CAA )
  /** 
   *@nodoc
	 *   Specifies a specific optimal smart topology sharing 
   *    when no touched topology has been registered avoiding duplication of higher domain. 
   */
  void  SetOptimizedInCaseOfNoTouch();
#endif


protected :

  /** @nodoc */
  friend ExportedByYI00IMPL void CATSmartBodyDuplicator_SetOptimizedInCaseOfNoTouch(CATSmartBodyDuplicator & iToModify);

  /** @nodoc */
  friend ExportedByYI00IMPL void CATSmartBodyDuplicator_ForbidOptimizedInCaseOfNoTouch(CATSmartBodyDuplicator & iToModify);
 

  CATLISTP(CATBody)  _InitialBodies;
		/** @nodoc */
  CATBody*           _DuplicatedBody;
		/** @nodoc */
  CATCGMJournalList* _Journal;
		/** @nodoc */
  short                   _FullDuplication;
		/** @nodoc */
  CATCGMDuplicateLyingOn  _LyingOnDuplication;


		/** @nodoc */
  CATBoolean _TransferTouch;
  
  /** @nodoc */
  CATBoolean _OptimizedInCaseOfNoTouch;
 
  
  /** @nodoc */
  CATSmartBodyDuplicator(CATGeoFactory* iFactory, CATCGMJournalList* iJournal);
};

#endif
