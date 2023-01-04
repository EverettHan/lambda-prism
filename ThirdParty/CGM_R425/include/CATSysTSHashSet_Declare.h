// CATSysTSHashSet_Declare.h

// no include guard is intended

// 
// A HashSet class declared thanks to this header and implemented thanks to CATSysTSHashSet_Define.h is a container that stores unique elements.
// Despite the interface name, the current implementation is not optimized by a hash mechanism, it's a simple linked list. 
// Then the methods Put, Remove and Find have a complexity in O(n) in the worst case.
// 

#undef  CATSYSTS_SET
#define CATSYSTS_SET CATSYSTS_CTNR


// if CATSYSTS_CTNR_FULL is defined (to declare a nested class)
#undef CATSYSTS_SET_FULL
#ifdef CATSYSTS_CTNR_FULL
    #define CATSYSTS_SET_FULL CATSYSTS_CTNR_FULL
#else
    #include "CATSysTSLinkedAbstractCtnr.h"
    #define CATSYSTS_SET_FULL CATSYSTS_CTNR
#endif


// if CATSYSTS_EL_T_FULL is not defined (if EL_T is not a nested class)
#ifndef CATSYSTS_EL_T_FULL
    #define CATSYSTS_EL_T_FULL          CATSYSTS_EL_T
#endif


// if CATSYSTS_EL_T_DECL_IN_CTNR is not defined
#ifndef CATSYSTS_EL_T_DECL_IN_CTNR
    #define CATSYSTS_EL_T_DECL_IN_CTNR  CATSYSTS_EL_T_FULL
#endif



class ExportedBy CATSYSTS_SET
{
public:
    // Hash implementation details
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
		#include "CATSysTSSetInterface_ConstIterator_BASIC.h"

    public:
        // Linked implementation details
        const_iterator(CATSYSTS_SET& ioSet, CATSysTSLinkedAbstractCtnr::Node* iopAN);

    public:
        // Hash implementation details
        CATSYSTS_SET* m_pSet;
        CATSysTSLinkedAbstractCtnr::Node* m_pAN;
    };


public:
    // Always declare basic Set functions
    #include "CATSysTSSetInterface_BASIC.h"

    // Optionally declare Set functions that require T to be a ptr
    #if CATSYSTS_T_IS_PTR == 1
    #include "CATSysTSSetInterface_T_IS_PTR.h"
    #endif

public:
    // Hash implementation details
    CATSysTSLinkedAbstractCtnr m_ANC;

public:
    // Hash implementation details
    CATSysTSLinkedAbstractCtnr::Node* FindNode(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl) const;
    void CopySet(const CATSYSTS_SET& iSet);
};







