// CATSysTSArrayListAbstractCtnr.h

#ifndef _CATSysTSArrayListAbstractCtnr_h_
#define _CATSysTSArrayListAbstractCtnr_h_


#include "CATSysTS.h"
#include "CATSysTSDataType.h"



class ExportedByCATSysTS CATSysTSArrayListAbstractCtnr
{

public:
    CATSysTSArrayListAbstractCtnr(int iSizeof_T); 
    ~CATSysTSArrayListAbstractCtnr();   

    HRESULT ReInit(int iMinCapacity = 0);

    HRESULT Move(int iDest, int iSrc, int iNb);

    HRESULT CheckIndex(int iIndex) const;

    HRESULT CheckRange(int iBegin, int iEnd) const;

	// iIndex should be between 0 and m_length. 
	// iNb is the number of element to reserve. m_length is incremented by iNb
	// m_capacity can be incremented if needed
    HRESULT MakeRoom(int iIndex, int iNb);
	
    HRESULT SetCapacity(int iNewCapacity);


private:
	CATSysTSArrayListAbstractCtnr(const CATSysTSArrayListAbstractCtnr& iAC); // Not implemented	
	CATSysTSArrayListAbstractCtnr& operator= (const CATSysTSArrayListAbstractCtnr &iAC); // Not implemented	   

public:
    char* m_pArray;
    int m_length;
    int m_capacity;
    int m_sizeof_T;
};


#endif



