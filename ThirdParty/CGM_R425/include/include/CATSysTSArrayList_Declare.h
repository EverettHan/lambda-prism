// CATSysTSArrayList_Declare.h
  
// no include guard is intended
  

// if ArrayList is not used as implementation of HashMap
#ifndef CATSYSTS_NOT_BASIC_CNTR_DECL

    #undef  CATSYSTS_LIST
    #define CATSYSTS_LIST CATSYSTS_CTNR

    // if CATSYSTS_LIST_FULL is defined (to declare a nested class)
    #undef CATSYSTS_LIST_FULL
    #ifdef  CATSYSTS_CTNR_FULL
        #define CATSYSTS_LIST_FULL CATSYSTS_CTNR_FULL
    #else
		#include "CATSysTSArrayListAbstractCtnr.h"
        #define CATSYSTS_LIST_FULL CATSYSTS_CTNR
    #endif

#endif

// if CATSYSTS_EL_T_FULL is not defined (if EL_T is not a nested class)
#ifndef CATSYSTS_EL_T_FULL
    #define CATSYSTS_EL_T_FULL CATSYSTS_EL_T
#endif

// if CATSYSTS_EL_T_DECL_IN_CTNR is not defined
#ifndef CATSYSTS_EL_T_DECL_IN_CTNR
    #define CATSYSTS_EL_T_DECL_IN_CTNR  CATSYSTS_EL_T_FULL
#endif

#ifdef CATSYSTS_FULL_TS
	#include "CATMutex.h"
#endif

class ExportedBy CATSYSTS_LIST
{
public:
    class ExportedBy const_iterator
    {
    public:
        // Always declare basic const_iterator functions
		#include "CATSysTSListInterface_ConstIterator_BASIC.h"

    public:
        // ArrayList implementation details
        const_iterator(CATSYSTS_LIST& ioList, int iIndex);
 
    public:
        // ArrayList implementation details
        CATSYSTS_LIST* m_pList;
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
        // ArrayList implementation details
        iterator(CATSYSTS_LIST& ioList, int iIndex);
    };
 

public:
    // Always declare basic list functions
    #include "CATSysTSListInterface_BASIC.h"

    // Optionally create n list-constructors with 1 to n elements as arguments
    #ifdef CATSYSTS_LIST_WITH_N_CONSTRUCTORS
        #include "CATSysTSListInterface_N_CONSTRUCTORS.h"
    #endif

    // Optionally declare list functions that require T::operator==
    #if CATSYSTS_T_HAS_COMPARE_OP == 1
        #include "CATSysTSListInterface_T_HAS_COMPARE_OP.h"
    #endif

    // Optionally declare list functions that require T::operator<
    #if CATSYSTS_T_HAS_LESS_OP == 1
        #include "CATSysTSListInterface_T_HAS_LESS_OP.h"
    #endif

    // Optionally declare list functions that require a custom compare method
    #if CATSYSTS_T_HAS_CUSTOM_COMP_METH == 1
        #include "CATSysTSListInterface_T_HAS_CUSTOM_COMP_METH.h"
    #endif

    // Optionally declare list functions that require T to be a ptr
    #if CATSYSTS_T_IS_PTR == 1
        #include "CATSysTSListInterface_T_IS_PTR.h"
    #endif


private:
    // ArrayList implementation details
	CATSysTSArrayListAbstractCtnr m_AC;
	
#ifdef CATSYSTS_FULL_TS
	CATMutex m_Mutex;
#endif

public:
	// -------------------------------------  Do not use -------------------------------------
    // 
	// ArrayList implementation details. 
    void Destroy(int iIndex);
    void DestroyRange(int iBegin, int iEnd);
    CATSYSTS_EL_T_DECL_IN_CTNR* pT(int iIndex);
    const CATSYSTS_EL_T_DECL_IN_CTNR* pT(int iIndex) const;
    void BuildRangeFromRange(int iInsertIndex, const CATSYSTS_LIST& iList, int iRangeBegin, int iRangeEnd);
    void BuildRangeFromList(int iInsertIndex, const CATSYSTS_LIST& iList);
    void BuildRangeFromBuffer(int iInsertIndex, const CATSYSTS_EL_T_DECL_IN_CTNR* ipEl, int iLength);
#ifdef CATSYSTS_FULL_TS
	void Lock() const;
	void Unlock() const;
#endif
	// -------------------------------------- Do not use --------------------------------------------

};
