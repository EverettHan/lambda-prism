// CATSysTSArrayListAbstractCtnrFC.h

#ifndef _CATSysTSArrayListAbstractCtnrFC_h_
#define _CATSysTSArrayListAbstractCtnrFC_h_


#include "CATSysTS.h"
#include "CATSysTSDataType.h"



class ExportedByCATSysTS CATSysTSArrayListAbstractCtnrFC
{

public:
    CATSysTSArrayListAbstractCtnrFC(int iSizeof_T);
    CATSysTSArrayListAbstractCtnrFC(const CATSysTSArrayListAbstractCtnrFC& iAC);

    ~CATSysTSArrayListAbstractCtnrFC();

    void ReInit();

    void ReInit(int iLength);

    void Move(int iDest, int iSrc, int iNb);

    void IncreaseLength(int iSize);

    HRESULT CheckIndex(int iIndex) const;

    HRESULT CheckRange(int iBegin, int iEnd) const;

    HRESULT MakeRoom(int iIndex, int iNb);

    void SetCapacity(int iCapacity);

	void FreezeContent();
	void UnFreezeContent();

private:
    void ReAllocate();
	int m_frozencontent;

public:
    char* m_pArray;
    int m_length;
    int m_capacity;
    int m_sizeof_T;
	
};


#endif



