//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCGMBucketsDcl:
// Macro to declare a class to manage an array with a dynamic size with a buckets mechanism.
//==============================================================================================================
// 14-Nov-2002 - JLH - Nouvelle gestion memoire (appel aux services CATCGMem***).
// 17-Sep-2002 - JLH - Ajout de la methode "int Add (const int iNbItems, const TheItem* iItems)"
//                     Commentaires.
// ??-Nov-1999 - JLH - Creation
// 28-Aou-2003 - FDS - Transfert dans Mathematics ( CATCldBucket* -> CATCGMBucket* )
//==============================================================================================================

/**
 * Generic class to manage an array with a dynamic size with a buckets mechanism.<br>
 * The number of cells by block is defined by a power of 2 to increase the performances of the functions
 * retreiving the block and cell indices for a given index by replacing the divisions by a shift and a mask.<br>
 * <br>
 * The instantiated class will have the following header : <br>
 * <pre><tt>
 * class CATCGMBucketsOfXXX
 * {
 * public:
 *   CATCGMBucketsOfXXX () ;
 *   CATCGMBucketsOfXXX (const CATCGMBucketsOfXXX& iOther) ;
 *   virtual ~CATCGMBucketsOfXXX() ;
 *    
 *   void operator= (const CATCGMBucketsOfXXX& iOther) ;
 *    
 *   void Init (const unsigned int iPower,
 *              const unsigned int iFirstNbBlocks,
 *              const unsigned int iNextNbBlocks) ;
 *    
 *   int NbItems() const ;
 *    
 *   int Add (const TheItem &iItem) ;
 *   int Add (const int iNbItems, const TheItem* iItems) ;
 *    
 *   const TheItem& operator[] (const int iNoItem) const ;
 *         TheItem& operator[] (const int iNoItem) ;
 *    
 *   CATBoolean Set (const int iNoItem, const TheItem &iItem) ;
 *   CATBoolean Get (const int iNoItem,       TheItem &oItem) const ;
 *    
 *   CATBoolean SetNbItems (const int iNewNbItems) ;
 *    
 *   size_t GetDynamicMemoryBytes () const ;
 * } ;
 * </tt></pre>
 * <br>
 * Use examples :
 * <ul>
 * <li>1. Nested class in a <tt>CATUpperClass</tt> class :<br>
 * <ul>
 * <li>1.a. Declaration in the <tt>CATUpperClass.h</tt> file :<br>
 * <pre><tt>
 * include "CATCGMGenBucketsDcl.h"
 * class CATUpperClass
 * {
 *   ...
 *   typedef data_type ... ;
 *   ...
 *   CATCGMGenBucketsDeclare (Datas, data_type) ;
 *   // The name of the instanciated class will be 'CATCGMBucketsOfDatas'.
 *   ...
 *   CATCGMBucketOfDatas _Datas ;
 *   ...
 * }
 * </tt></pre>
 * <li>1.b. Definition in the <tt>CATUpperClass.cpp</tt> file :<br>
 * <pre><tt>
 * include "CATUpperClass.h"
 * include "CATCGMGenBucketsDef.h"
 * CATCGMGenBucketsDefine (CATUpperClass, Datas, data_type) ;
 * </tt></pre>
 * </ul>
 * <li>2. Simple class <tt>CATBucketsOfDatas</tt> :<br>
 * <ul>
 * <li>2.a. Declaration in the <tt>CATCGMBucketsOfDatas.h</tt> file :<br>
 * <pre><tt>
 * include "CATCGMGenBucketsDcl.h"
 * typedef data_type ... ;
 * CATCGMGenBucketsDeclare (Datas, data_type) ;
 * // The name of the instanciated class will be 'CATCGMBucketsOfDatas'.
 * </tt></pre>
 * <li>2.b. Definition in the <tt>CATCGMBucketsOfDatas.cpp</tt> file :<br>
 * <pre><tt>
 * include "CATCGMBucketsOfDatas.h"
 * include "CATCGMGenBucketsDef.h"
 * #define UPPER_CLASS
 * CATCGMGenBucketsDefine (UPPER_CLASS, Datas, data_type) ;
 * </tt></pre>
 * </ul>
 * <li>3. Use of such generic class :<br>
 * <pre><tt>
 * CATCGMBucketsOfDatas Dummy1 ;
 * CATCGMBucketsOfDatas* Dummy2 = new CATCGMBucketsOfDatas() ;
 * </tt></pre>
 * <li>4. First obligatory call on such object :<br>
 * <pre><tt>
 * CATCGMBucketsOfDatas Datas ;
 * Datas.Init (Power, NbPages1, NbPagesN) ;
 * </tt></pre>
 * with :<br>
 * <pre><tt>
 * Power    : Page size in power of 2 (for ex. 1024 = 2^10).
 * NbPages1 : Size of the header for the first allocation.
 * NbPagesN : Increment for the next allocations (NbPages += NbPagesN).
 * </tt></pre>
 * <li>5. The range of the elements is <tt>[1,NbItems()]</tt>.<br>
 * So, an exception could be raised if an indice is out of range.
 * <li>6. The method "<tt>int Add (const int iNbItems, const TheItem* iItems) ;</tt>"
 * will raised an exception if <tt>iNbItems</tt> is greater than the block size.
 * </ul>
 */

// Exception libraries
#include "CATThrowForNullPointer.h"

#include "CATCGMIndexOutOfRange.h"
#include "CATCGMVirtual.h"

#ifdef CATCGMBucketsDeclare
#undef CATCGMBucketsDeclare
#endif

#include "CATMathInline.h"

#define CATCGMBucketsDeclare(TheName,TheItem) \
  class CATCGMBucketsOf##TheName  : public CATCGMVirtual  \
{ \
public: \
\
  CATCGMBucketsOf##TheName () ; \
\
  CATCGMBucketsOf##TheName (const CATCGMBucketsOf##TheName& iOther) ; \
\
  virtual ~CATCGMBucketsOf##TheName() ; \
\
  void operator= (const CATCGMBucketsOf##TheName& iOther) ; \
\
  INLINE void Init (const unsigned int iPower, \
                    const unsigned int iFirstNbBlocks, \
                    const unsigned int iNextNbBlocks) { \
    CATCGMValidateRange (iPower, 1, 32) ; \
    _NbItemsByBlock = 1 << iPower ; \
    _FirstNbBlocks  = iFirstNbBlocks ; \
    _NextNbBlocks   = iNextNbBlocks ; \
    _Shift          = iPower ; \
    _Mask           = (1 << iPower) - 1 ; \
  } \
\
  INLINE int NbItems() const { \
    return ((int) _NbItems) ; \
  } \
\
  int Add (const TheItem &iItem) ; \
\
  int Add (const int      iNbItems, \
           const TheItem* iItems) ; \
\
  INLINE const TheItem& operator[] (const int iNoItem) const { \
    unsigned int NoItem = (unsigned int) iNoItem ; \
    CATCGMValidateRange (NoItem, 1, (_NbItems+1)) ; \
    unsigned int blk = NumBlock (NoItem) ; \
    unsigned int icl = NumCell  (NoItem) ; \
    if (_Blocks[blk] == NULL) CATCGMnull (NULL, 0) ; \
    return _Blocks[blk][icl] ; \
  } \
\
  INLINE TheItem& operator[] (const int iNoItem) { \
    unsigned int NoItem = (unsigned int) iNoItem ; \
    CATCGMValidateRange (NoItem, 1, (_NbItems+1)) ; \
    unsigned int blk = NumBlock (NoItem) ; \
    unsigned int icl = NumCell  (NoItem) ; \
    if (_Blocks[blk] == NULL) CATCGMnull (NULL, 0) ; \
    return _Blocks[blk][icl] ; \
  } \
\
  CATBoolean Set (const int      iNoItem, \
                  const TheItem &iItem) ; \
\
  INLINE CATBoolean Get (const int  iNoItem, \
                         TheItem   &oItem) const { \
    unsigned int NoItem = (unsigned int) iNoItem ; \
    if (NoItem < 1 || _NbItems < NoItem) return FALSE ; \
    unsigned int blk = NumBlock (NoItem) ; \
    unsigned int icl = NumCell  (NoItem) ; \
    if (_Blocks[blk] == NULL) return FALSE ; \
    oItem = _Blocks[blk][icl] ; \
    return TRUE ; \
  } \
\
  CATBoolean SetNbItems (const int iNewNbItems) ; \
\
  INLINE size_t GetDynamicMemoryBytes () const { \
    size_t Size = 0 ; \
    Size += _NbBlocks * sizeof (TheItem *) ; \
    unsigned int blk ; \
    for (blk = 0 ; blk < _NbBlocks ; blk++) { \
      if (_Blocks[blk]) Size += _NbItemsByBlock * sizeof (TheItem) ; \
    } \
    return Size ; \
  } \
\
private: \
\
  CATBoolean Alloc () ; \
  CATBoolean ReAlloc () ; \
  CATBoolean Free () ; \
\
  INLINE unsigned int NumBlock (const unsigned int iNoItem) const { \
    return ((iNoItem - 1) >> _Shift) ; \
  } \
\
  INLINE unsigned int NumCell  (const unsigned int iNoItem) const { \
    return ((iNoItem - 1) & _Mask) ; \
  } \
\
  unsigned int _NbItemsByBlock ; \
  unsigned int _FirstNbBlocks ; \
  unsigned int _NextNbBlocks ; \
  unsigned int _Shift ; \
  unsigned int _Mask ; \
  unsigned int _NbItems ; \
  unsigned int _NbBlocks ; \
  TheItem** _Blocks ; \
\
}
