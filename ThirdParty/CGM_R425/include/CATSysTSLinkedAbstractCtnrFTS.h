// CATSysTSLinkedAbstractCtnrFTS.h
// 
// Class that factorizes code that does not rely on contained objects type
// This class is used in LinkedList containers as a delegation

#ifndef _CATSysTSLinkedAbstractCtnrFTS_h_
#define _CATSysTSLinkedAbstractCtnrFTS_h_


#include "CATSysTS.h"
#include "CATSysTSDataType.h"
#include "CATMutex.h"


class ExportedByCATSysTS CATSysTSLinkedAbstractCtnrFTS
{
public:
    class ExportedByCATSysTS Node
    {	
    public:
	    Node* m_pNext;
	    Node* m_pPrev;
    };

public:
    CATSysTSLinkedAbstractCtnrFTS();

    void Init();

    // Insert
    void InsertNodeBetween(Node* io_pBeforeNode, Node& io_newNode, Node* io_pAfterNode);

    // Remove
    Node* RemoveNode(Node& io_node);
    Node* RemoveNodeGetNext(Node& io_node);
    Node* RemoveNodeGetPrev(Node& io_node);

    // Get At Index
    Node* GetNode(int in_index) const;

    // Pop
    Node* PopFirstNode();
    Node* PopLastNode();
    Node* PopNode(int in_index);

    HRESULT GetNodeRange(int iBegin, int iEnd, Node*& opBeginAN, Node*& opEndAN) const;

public:
	int m_length;
	Node* m_pFirst;
    Node* m_pLast;

private :
	CATMutex m_lock;
};



#endif


