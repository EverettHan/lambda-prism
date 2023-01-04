// CATSysTSLinkedList_Declare.h

// no include guard is intended


#undef  CATSYSTS_LIST
#define CATSYSTS_LIST CATSYSTS_CTNR


// if CATSYSTS_CTNR_FULL is defined (to declare a nested class)
#undef CATSYSTS_LIST_FULL
#ifdef CATSYSTS_CTNR_FULL
    #define CATSYSTS_LIST_FULL CATSYSTS_CTNR_FULL
#else
	#include "CATSysTSLinkedAbstractCtnr.h"
    #define CATSYSTS_LIST_FULL CATSYSTS_CTNR
#endif


// if CATSYSTS_EL_T_FULL is not defined (if EL_T is not a nested class)
#ifndef CATSYSTS_EL_T_FULL
    #define CATSYSTS_EL_T_FULL          CATSYSTS_EL_T
#endif


// if CATSYSTS_EL_T_DECL_IN_CTNR is not defined
#ifndef CATSYSTS_EL_T_DECL_IN_CTNR
    #define CATSYSTS_EL_T_DECL_IN_CTNR  CATSYSTS_EL_T_FULL
#endif



class ExportedBy CATSYSTS_LIST
{
public:
    // Linked implementation details
    class ExportedBy Node_T : public CATSysTSLinkedAbstractCtnr::Node
    {
    public:
	    CATSYSTS_EL_T_DECL_IN_CTNR m_el;
        // Destructor is not virtual on purpose
        Node_T(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl) : m_el(iEl) {}
    };


public:
    class ExportedBy const_iterator
    {
    public:
        // Always declare basic const_iterator functions
		#include "CATSysTSListInterface_ConstIterator_BASIC.h"

    public:
        // Linked implementation details
        const_iterator(CATSYSTS_LIST& ioList, CATSysTSLinkedAbstractCtnr::Node* iopAN, int iIndex);

    public:
        // Linked implementation details
        CATSYSTS_LIST* m_pList;
        CATSysTSLinkedAbstractCtnr::Node* m_pAN;
        int m_index;
    };

 
    class ExportedBy iterator : public const_iterator
    {
    public:
        // Always declare basic iterator functions
		#include "CATSysTSListInterface_Iterator_BASIC.h"

        // Optionally declare iterator functions that require T to be a ptr
        #if CATSYSTS_T_IS_PTR == 1
            #include "CATSysTSListInterface_Iterator_T_IS_PTR.h"
        #endif


    public:
        // Linked implementation details
        iterator(CATSYSTS_LIST& ioList, CATSysTSLinkedAbstractCtnr::Node* ipAN, int iIndex);
    };


public:
    // Always declare basic list functions
    #include "CATSysTSListInterface_BASIC.h"

    // Optionally declare list functions that require T::operator==
    #if CATSYSTS_T_HAS_COMPARE_OP == 1
        #include "CATSysTSListInterface_T_HAS_COMPARE_OP.h"
    #endif

    // Optionally declare list functions that require T::operator<
    #if CATSYSTS_T_HAS_LESS_OP == 1
        #include "CATSysTSListInterface_T_HAS_LESS_OP.h"
    #endif

    // Optionally declare list functions that require T to be a ptr
    #if CATSYSTS_T_IS_PTR == 1
        #include "CATSysTSListInterface_T_IS_PTR.h"
    #endif

public:
    // Linked implementation details
		CATSysTSLinkedAbstractCtnr m_ANC;


public:
    // Linked implementation details
    void InsertElementBeforeNode(CATSysTSLinkedAbstractCtnr::Node& ioAN, const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);
   
    void InsertListBeforeNode(CATSysTSLinkedAbstractCtnr::Node& ioAN, const CATSYSTS_LIST& iList);
    
    void PutBackNodeRange(CATSysTSLinkedAbstractCtnr::Node* ipBeginAN, 
                          CATSysTSLinkedAbstractCtnr::Node* ipEndAN);
    
    void InsertNodeRangeBeforeNode(CATSysTSLinkedAbstractCtnr::Node& ioInsertAN, 
                                   CATSysTSLinkedAbstractCtnr::Node* ipBeginAN, 
                                   CATSysTSLinkedAbstractCtnr::Node* ipEndAN);
};


