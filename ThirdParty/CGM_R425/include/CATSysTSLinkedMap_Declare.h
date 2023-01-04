// CATSysTSLinkedMap_Declare.h

// no include guard is intended


// if LinkedMap is not used as implementation of HashMap
#ifndef CATSYSTS_NOT_BASIC_CNTR_DECL

    #undef  CATSYSTS_MAP
    #define CATSYSTS_MAP CATSYSTS_CTNR


    // if CATSYSTS_LIST_FULL is defined (to declare a nested class)
    #undef CATSYSTS_MAP_FULL
    #ifdef  CATSYSTS_CTNR_FULL
        #define CATSYSTS_MAP_FULL CATSYSTS_CTNR_FULL
    #else
        #include "CATSysTSLinkedAbstractCtnr.h"
        #define CATSYSTS_MAP_FULL CATSYSTS_CTNR
    #endif

#endif


// if CATSYSTS_KEY_FULL is not defined (if KEY is not a nested class)
#ifndef CATSYSTS_KEY_FULL
    #define CATSYSTS_KEY_FULL          CATSYSTS_KEY
#endif


// if CATSYSTS_KEY_DECL_IN_CTNR is not defined
#ifndef CATSYSTS_KEY_DECL_IN_CTNR
    #define CATSYSTS_KEY_DECL_IN_CTNR  CATSYSTS_KEY_FULL
#endif


// if CATSYSTS_VAL_FULL is not defined (if VAL is not a nested class)
#ifndef CATSYSTS_VAL_FULL
    #define CATSYSTS_VAL_FULL          CATSYSTS_VAL
#endif


// if CATSYSTS_VAL_DECL_IN_CTNR is not defined
#ifndef CATSYSTS_VAL_DECL_IN_CTNR
    #define CATSYSTS_VAL_DECL_IN_CTNR  CATSYSTS_VAL_FULL
#endif



class ExportedBy CATSYSTS_MAP
{
public:
    class ExportedBy Entry
    {
    public:
        CATSYSTS_KEY_DECL_IN_CTNR m_key;
        CATSYSTS_VAL_DECL_IN_CTNR m_val;

        Entry(const CATSYSTS_KEY_DECL_IN_CTNR& iKey, const CATSYSTS_VAL_DECL_IN_CTNR& iVal) : m_key(iKey), m_val(iVal) {}

        Entry(const Entry& iEntry) : m_key(iEntry.m_key), m_val(iEntry.m_val) {}
    };

public:
    // Linked implementation details
    class ExportedBy Node_KV : public CATSysTSLinkedAbstractCtnr::Node
    {
    public:
        Entry m_entry;

        // Destructor is not virtual on purpose

        Node_KV(const CATSYSTS_KEY_DECL_IN_CTNR& iKey, const CATSYSTS_VAL_DECL_IN_CTNR& iVal) : m_entry(iKey, iVal) {}

        Node_KV(const Entry& iEntry) : m_entry(iEntry) {}

        Node_KV(const Node_KV& iNode_KV) : m_entry(iNode_KV.m_entry) {}
    };


public:
    class ExportedBy const_iterator
    {
    public:
        // Always declare basic const_iterator functions
		#include "CATSysTSMapInterface_ConstIterator_BASIC.h"

    public:
        // Linked implementation details
        const_iterator(CATSYSTS_MAP& ioMap, CATSysTSLinkedAbstractCtnr::Node* iopAN);

    public:
        // Linked implementation details
        CATSYSTS_MAP* m_pMap;
        CATSysTSLinkedAbstractCtnr::Node* m_pAN;
    };


    class ExportedBy iterator : public const_iterator
    {
    public:
        // Always declare basic iterator functions
		#include "CATSysTSMapInterface_Iterator_BASIC.h"

    public:
        // Linked implementation details
        iterator(CATSYSTS_MAP& ioMap, CATSysTSLinkedAbstractCtnr::Node* iopAN);
    };


public:
    // Always declare basic Map functions
    #include "CATSysTSMapInterface_BASIC.h"

    // Optionally declare Map functions that require V::operator==
    #if CATSYSTS_VAL_HAS_COMPARE_OP == 1
    #include "CATSysTSMapInterface_VAL_HAS_COMPARE_OP.h"
    #endif

    // Optionally declare Map functions that require V to be a ptr
    #if CATSYSTS_VAL_IS_PTR == 1
    #include "CATSysTSMapInterface_VAL_IS_PTR.h"
    #endif

public:
    // Linked implementation details
    CATSysTSLinkedAbstractCtnr m_ANC;

public:
    // Linked implementation details
    CATSysTSLinkedAbstractCtnr::Node* FindNode(const CATSYSTS_KEY_DECL_IN_CTNR& iKey) const;
    void CopyMap(const CATSYSTS_MAP& iMap);
};







