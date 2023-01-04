#ifndef DSYSysTSDico_H
#define DSYSysTSDico_H

#include "CATSysDataType.h"
#include "CATSysErrorDef.h"
#include "CATHttp.h"
#include "DSYString.h"
#include "CATSysSimpleHashTable.h"


//Only used in DSYSysHTTPCommunication


//CATResourceLock			_ArgsLock;


class DSYSysTSDicoElem
{
public:
	DSYSysTSDicoElem(const CATUnicodeString &Key);
	DSYSysTSDicoElem(const CATUnicodeString &Key, void* Val);
	DSYSysTSDicoElem() : _Key(0), _Value(0), _Hash(0) {};
	virtual ~DSYSysTSDicoElem();


	unsigned int ComputeHashKey();

	static int Compare(void *iA,  void *iB);
	static unsigned int Hash (void *iA);

	// La clef de recherche ie nom de l'argument sans le - pour ceux passe en ligne de commande
	CATUnicodeString	_Key;
	void				*_Value;
	unsigned int		_Hash;	
};



class ExportedByJS0HTTP DSYSysTSDico
{       
public :
	DSYSysTSDico();
	DSYSysTSDico(const DSYSysTSDico& iCopy);
	~DSYSysTSDico();

	// INSERT        (if already exists, 0 is returned)
	HRESULT	Insert(const CATUnicodeString& iName, void* iAdd);

	// FIND AN ITEM
	void*	Locate(const CATUnicodeString& iLocate);

	// NEXT ITEM
//	void* NextItem(int& ioBucket, int& ioPosition) const;
//	void* Next(int& ioBucket, int& ioPosition, CATUnicodeString* iPName = 0);
//	void* Next(const CATUnicodeString* iFrom, CATUnicodeString* iPName = 0) const;

	// REMOVE
	void	Remove(const CATUnicodeString& iRemove);
	void	RemoveAll();
	void	RemoveAllAndFreeElem();
	void	RemoveAllAndDeleteElem();
	void	RemoveAllAndDeleteTableElem();

private :
	unsigned int			_Size;		
	CATSysSimpleHashTable	*_DSYSysTSDicoTb;
};

#endif

