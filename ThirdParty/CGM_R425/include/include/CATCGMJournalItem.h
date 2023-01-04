#ifndef CATCGMJournalItem_h_
#define CATCGMJournalItem_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"
#include "YP00IMPL.h"
#include "CATCGMJournal.h"
#include "CATListOfCATGeometries.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"

class CATCGMJournalInfo;

/**
 * Class defining a single line in the journal.
 * <br>
 * The journal items are created when you report new events inside the
 * journal list (@href CATCGMJournalList#Report, @href CATCGMJournalList#ReportUnspecModify).
 * Do not directly use the item journal constructor. The journal
 * items are deleted with the journal list in which they are imbedded, except if you have directly
 * created an item, without inserting it inside a journal list.
 * The journal information is also deleted with the journal it informs.
 */
class ExportedByYP00IMPL CATCGMJournalItem : public CATCGMJournal
{
public:
/** 
 * Constructs a journal item.
 * <br> Do not directly construct an item by this constructor, use 
 * the  @href CATCGMJournalList#Report methods to create an item inside a list.
 */
  CATCGMJournalItem(CATCGMJournalList          * iList,
                   CATCGMJournal::Type           iType,
                   const CATLISTP(CATGeometry) & iBefore,
                   const CATLISTP(CATGeometry) & iAfter,
                   CATCGMJournalInfo           * iInfo = NULL);

/** 
 * Constructs a <tt>Keep</tt> or <tt>Deletion</tt> journal item .
 * <br> Do not directly construct an item by this constructor, use 
 * the  @href CATCGMJournalList#Report methods to create an item inside a list.
 */
  CATCGMJournalItem(CATCGMJournalList * iList,
                    CATCGMJournal::Type iType,
                    CATGeometry       * iObject,
                    CATCGMJournalInfo * info = NULL);
  
  
  virtual ~CATCGMJournalItem();
  /** @nodoc */
  CATCGMNewClassArrayDeclare;

/**
 * Returns the type of <tt>this</tt> journal item.
 * @return
 * The type of the item.
 */
  virtual CATCGMJournal::Type GetType() const;

/** 
 *  Casts <tt>this</tt> into a journal item.
 * @return
 * The casted pointer.
 */
  virtual CATCGMJournalItem * CastToReportItem();
  
/** @nodoc */
  virtual void Dump(ostream & ioStream, int iIndent = 0);

/**
 * @nodoc
 * Dumps the content of <tt>this</tt> journal item.
 * @param iWhereToWrite
 * The output to write the journal item.
 * @param iIndent
 * The number of blanks before writing of the item.
 */
  virtual void Dump(CATCGMOutput & ioWhereToWrite, int iIndent = 0);

/** @nodoc */
  void DumpTags(ostream & ioStream, const CATLISTP(CATGeometry) & iGeometry) const;

/** @nodoc */
  void DumpTags(CATCGMOutput & ioWhereToWrite,
                const CATLISTP(CATGeometry) & iGeometry) const;


/** 
 * Returns the associated information with <tt>this</tt> journal item.
 * @return
 * A pointer to the associated information.
 */
  const CATCGMJournalInfo * GetAssociatedInfo() const;

/**
 * Replaces the information associated with <tt>this</tt> journal item.
 * @param iNewInfo
 * A pointer to the new information. 
 */
  void SetAssociatedInfo(const CATCGMJournalInfo * iNewInfo);

/** 
 * Retrieves the list of construction objects for a creation item.
 * @return
 * A pointer to the list of objects that lead to the creation of another one.
 */
  const CATLISTP(CATGeometry) * GetConstructionObjects() const;

/** 
 * Retrieves a pointer to the created object for a creation item.
 * @return
 * A pointer to the created object.
 */
  CATGeometry * GetConstructedObject() const;
  
/** 
 * Returns the list of objects before a modification or an absorption.
 * @return
 * A pointer to the list of objects before a modification or an absorption.
 */
  const CATLISTP(CATGeometry) * GetOldObjects() const;

/** 
 * Returns the list of objects after a modification or an absorption.
 * @return
 * A pointer to the list of objects after a modification or an absorption.
 */
  const CATLISTP(CATGeometry) * GetNewObjects() const;
  
/** 
 * Returns the kept object (Keep item).
 * @return
 * A pointer to the kept object.
 */
  CATGeometry * GetKeptObject() const;
  
/** 
 * Returns the deleted objects (Deletion item).
 * @return
 * A pointer to the list of deleted objects.
 */
  const CATLISTP(CATGeometry) * GetDeletedObjects() const;
 
/** 
 * Returns the copied object (for a copy/nocopy item).
 * @return
 * A pointer to the copied object.
 */
  CATGeometry * GetCopiedObject() const;
  
/**
 * Returns the resulting object (for a copy/nocopy item).
 * @return
 * A pointer to the resulting object.
 */
  CATGeometry * GetCopiedIntoObject() const;

/** 
 *  Returns the initial objects (all item types).
 * @param ioBefore
 * The list of the objects before the operation described by <tt>this</tt> item.
 */
  void GetFirstObjs(CATLISTP(CATGeometry) & ioBefore) const;

/** 
 *  Returns the resulting objects (all item types).
 * @param ioAfter
 * The list of the objects after the operation described by <tt>this</tt> item.
 */
  void GetLastObjs(CATLISTP(CATGeometry) & ioAfter) const;

/** 
 * Automatically reports the attributes pointed by the objects before the operation on the 
 * objects after the operation.
 * <br>Not available for a creation item.
 * @param iAttr
 * The type of attribute to report. If the objects before the operation point an attribute of this
 * type, the attribute will also be shared by the objects after modification.
 */
  void MakeAttributesFollow(const CATCGMAttrId * iAttribute);

/** 
 * Discards a list of objects from the topological journal. 
 * This method is to be used with caution. Only objects 
 * which are not required by the backtracking mechanism can be discarded.
 * If not used properly, this method can lead to an invalid journal.
 * @param iToSimplify
 * The list of objects to be discarded from the journal.
 * @return
 * 0 if the objects can be removed - otherwise 1
 */
  int ForgetObjects(const CATLISTP(CATGeometry) & iObjects);
/** 
 * @nodoc
 * Internal use.
 */
  void ForgetConstructionObjects();
/** 
 * @nodoc
 * Internal use.
 */
  void ChangeType(CATCGMJournal::Type);

/** @nodoc */
  CATCGMJournal * DuplicateItem(CATCGMJournalList * iReport) const;

/**
 * @nodoc
 * Internal use.
 */
  CATULONG32  GetDebugIdentifier();

	/**
	* @nodoc
	* True Stream management
	*/
  virtual void  Stream  (CATCGMStream &os);

	/**
	* @nodoc
	* True Stream management
	*/
  static CATCGMJournalItem *UnStream(CATCGMJournalList * iList, CATGeoFactory *iFactory, CATCGMStream &iStr);
#ifdef CATIACGMR216Code
	/**
	* @nodoc @nocgmitf
	* True Stream management
	*/
  static CATCGMJournalItem *UnStream(CATCGMJournalList * iList, CATGeoFactory *iFactoryForFirst
                                                              , CATGeoFactory *iFactoryForLast, CATCGMStream &iStr);
#endif
	/**
	* @nodoc
	* Deletion management for Generic Naming
	*/
	void SetKeptForGN();

	/**
	* @nodoc
	* Deletion management for Generic Naming
	*/
	int	IsKeptForGN() const;

protected:
/**
 * Copy constructor.
 */
  CATCGMJournalItem(const CATCGMJournalItem & iToCopy);

/**
 * Affectation operator.
 */
  CATCGMJournalItem & operator = (const CATCGMJournalItem & iToCopy);

  friend class ExportedByYP00IMPL CATCGMJournalList;

/** @nodoc */
  virtual CATCGMJournal * Duplicate(CATCGMJournalList * iReport, int iCopyNext = 1) const;

	/**
	* @nodoc
	* True Stream management
	*/
  virtual void _UnStream(CATCGMStream & os);


  int CheckCellTypes(CATLISTP(CATGeometry) &iListOfBadGeometry, int iWithTraces = 0);


private:


  /** @nodoc */
  // un bloc de 32 bits ...
  struct
  {
    // Generic Naming needs to know about deletion events.
    // But these events should not be taken into account by CATTopCheckJournal
    // Journal tassing will set the following member to TRUE
    unsigned            _KeptForGN : 1;
    CATCGMJournal::Type _Type      :31; 
  } _DataItem;

  CATLISTP(CATGeometry) _FirstElements;
  CATLISTP(CATGeometry) _LastElements;
  CATCGMJournalInfo*    _pAssocInfo;

  CATULONG32          _SessionId ;
  static CATULONG32   _SessionBorn ;
};

#endif
