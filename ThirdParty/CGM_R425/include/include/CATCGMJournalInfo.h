#ifndef CATCGMJournalInfo_h_
#define CATCGMJournalInfo_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YP00IMPL.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATString;
class CATCGMOutput;
class CATCGMStream;

#include "CATCGMNewArray.h"
#include "CATDataType.h"
#include "CATMathInline.h"

/**
 * Defines an additional information associated with an journal item.
 * <br>This data is a CATLONG32. If a journal information is used by a journal, it is
 * automatically deleted with that journal.
 */

class ExportedByYP00IMPL CATCGMJournalInfo
{
public:
/**
 * Constructs a journal information.
 * @param iInfo
 * The value of the additional information.
 */
  CATCGMJournalInfo(CATLONG32 iInfo) ;
  virtual ~CATCGMJournalInfo();
  /** @nodoc */
  CATCGMNewClassArrayDeclare;

/**
 * Copy constructor.
 */
  CATCGMJournalInfo(const CATCGMJournalInfo& iToCopy);

/**
 * Affectation operator.
 */
  CATCGMJournalInfo& operator = (const CATCGMJournalInfo& iToCopy);

/** @nodoc */
  virtual void Dump(ostream& os) const ;

/**
 * @nodoc
 * Dumps the content of <tt>this</tt> journal information.
 * @param iWhereToWrite
 * The output to write the journal information.
 */
  virtual void Dump(CATCGMOutput& iWhereToWrite) const;
  
/**
 * Returns value of <tt>this</tt> item information.
 * @return
 * The value.
 */
  CATLONG32 GetNumber() const ;

/**
 * Replaces the value of <tt>this</tt> item information.
 * @param iVal
 * The value.
 */
  void SetNumber(CATLONG32 iVal);

/**
* Retrieves <tt>this</tt> item information as a string.
* @param iName
* The information value as a string.
*/
  virtual void GetName(CATString& iName) const;
  
/** @nodoc */	
  INLINE CATULONG32   IncCounter();
/** @nodoc */	
  INLINE CATULONG32   DecCounter();

	/**
	* @nodoc
	* True Stream management
	*/
  virtual void Stream(CATCGMStream &os);

	/**
	* @nodoc
	* True Stream management
	*/
  static CATCGMJournalInfo *UnStream(CATCGMStream & os);


protected:
  /** @nodoc */
  CATLONG32  _number;

  /** @nodoc */
  CATULONG32  _Counter;

	/**
	* @nodoc
	* True Stream management
	*/
  virtual void _UnStream(CATCGMStream & os);
};

ExportedByYP00IMPL CATULONG32   CATCGMJournalInfo::IncCounter()
{
  return ++_Counter;
}

ExportedByYP00IMPL CATULONG32   CATCGMJournalInfo::DecCounter()
{
  return --_Counter;
}

#endif
