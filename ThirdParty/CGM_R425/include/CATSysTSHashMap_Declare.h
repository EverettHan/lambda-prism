// CATSysTSHashMap_Declare.h


// no include guard is intended


// if CATSYSTS_CTNR_FULL is defined (to declare a nested class)
#undef CATSYSTS_HASH_MAP_FULL
#ifdef CATSYSTS_CTNR_FULL
    #define CATSYSTS_HASH_MAP_FULL CATSYSTS_CTNR_FULL
#else
    #include "CATSysTSDataType.h"
    #include "CATSysTSLinkedAbstractCtnr.h"
    #include "CATSysTSArrayListAbstractCtnr.h"
    #define CATSYSTS_HASH_MAP_FULL CATSYSTS_CTNR
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



class ExportedBy CATSYSTS_CTNR
{
public:
    //---------------------------------------------
    // declare LinkedMapOfKeyVal
    //---------------------------------------------
    #undef  CATSYSTS_NOT_BASIC_CNTR_DECL
    #define CATSYSTS_NOT_BASIC_CNTR_DECL

    #undef  CATSYSTS_MAP
    #define CATSYSTS_MAP LinkedMapOfKeyVal
    // no need to define others because they are the same as for HASH_MAP

    #include "CATSysTSLinkedMap_Declare.h"



public:
    //---------------------------------------------
    // declare ArrayListOfLinkedMapOfKeyVal
    //---------------------------------------------
    #undef  CATSYSTS_NOT_BASIC_CNTR_DECL
    #define CATSYSTS_NOT_BASIC_CNTR_DECL

    #undef CATSYSTS_LIST
    #undef CATSYSTS_EL_T
    #undef CATSYSTS_EL_T_FULL
    #undef CATSYSTS_T_HAS_COMPARE_OP
    #undef CATSYSTS_T_HAS_LESS_OP
    #undef CATSYSTS_T_IS_PTR
    #undef CATSYSTS_T_IS_BUILT_IN_TYPE

    #define CATSYSTS_LIST                ArrayListOfLinkedMapOfKeyVal
    #define CATSYSTS_EL_T                LinkedMapOfKeyVal
    #define CATSYSTS_EL_T_FULL           LinkedMapOfKeyVal
    #define CATSYSTS_T_HAS_COMPARE_OP    0
    #define CATSYSTS_T_HAS_LESS_OP       0
    #define CATSYSTS_T_IS_PTR            0
    #define CATSYSTS_T_IS_BUILT_IN_TYPE  0

    #include "CATSysTSArrayList_Declare.h"



public:
    typedef LinkedMapOfKeyVal::Entry Entry;
    typedef LinkedMapOfKeyVal::Node_KV Node_KV;


public:
    //---------------------------------------------
    // set CATSYSTS_MAP = CATSYSTS_CTNR
    //---------------------------------------------
    #undef  CATSYSTS_MAP
    #define CATSYSTS_MAP CATSYSTS_CTNR



    class ExportedBy const_iterator
    {
    public:
        // Always declare basic const_iterator functions
		#include "CATSysTSMapInterface_ConstIterator_BASIC.h"

    public:
        // Hash implementation details
        const_iterator(CATSYSTS_MAP& ioMap);

    public:
        // Hash implementation details
        CATSYSTS_MAP* m_pMap;
        ArrayListOfLinkedMapOfKeyVal::iterator m_tableItr;
        LinkedMapOfKeyVal::iterator m_linkedMapItr;

    public:
        void GoToNonEmptyLinkedMap();
    };


    class ExportedBy iterator : public const_iterator
    {
    public:
        // Always declare basic iterator functions
		#include "CATSysTSMapInterface_Iterator_BASIC.h"

    public:
        // Hash implementation details
        iterator(CATSYSTS_MAP& ioMap);
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
    // Hash implementation details
    ArrayListOfLinkedMapOfKeyVal m_table;
    int m_length;
    float m_fCapaMult;

public:
    // Hash implementation details
    void Init(int iCapacity, float ifLoadFactor);
    void Fill(const CATSYSTS_MAP& iMap);
    int GetMinimumTableLength(int iCapacity) const;
    CATUINT32 Hash(const CATSYSTS_KEY_DECL_IN_CTNR& iKey) const;
    LinkedMapOfKeyVal& GetLinkedMap(const CATSYSTS_KEY_DECL_IN_CTNR& iKey);
    const LinkedMapOfKeyVal& GetLinkedMap(const CATSYSTS_KEY_DECL_IN_CTNR& iKey) const;


};







