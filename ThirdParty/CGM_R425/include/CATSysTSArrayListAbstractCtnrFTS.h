// CATSysTSArrayListAbstractCtnrFTS.h

#ifndef _CATSysTSArrayListAbstractCtnrFTS_h_
#define _CATSysTSArrayListAbstractCtnrFTS_h_


#include "CATSysTS.h"
#include "CATSysTSDataType.h"
#include "CATMutex.h"


class ExportedByCATSysTS CATSysTSArrayListAbstractCtnrFTS
{

public:
    CATSysTSArrayListAbstractCtnrFTS(int iSizeof_T);
    CATSysTSArrayListAbstractCtnrFTS(const CATSysTSArrayListAbstractCtnrFTS& iAC);

    ~CATSysTSArrayListAbstractCtnrFTS();

    void ReInit();

    void ReInit(int iLength);

    void Move(int iDest, int iSrc, int iNb);

    void IncreaseLength(int iSize);

    HRESULT CheckIndex(int iIndex) const;

    HRESULT CheckRange(int iBegin, int iEnd) const;

    HRESULT MakeRoom(int iIndex, int iNb);

    void SetCapacity(int iCapacity);


private:
    void ReAllocate();
	CATMutex m_lock;

public:
    char* m_pArray;
    int m_length;
    int m_capacity;
    int m_sizeof_T;
	
};


#endif



